///////////////////////////////////////////////
//
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//
//  (c) 2020  A. Terstegge
//
///////////////////////////////////////////////
//
#include "Net2Sim.h"
#include "NetParser.h"
#include <iostream>
#include <map>
#include <algorithm>
using std::cout;
using std::cerr;
using std::endl;
using std::map;

int Net2Sim::main(int argc, char* argv[])
{
    /////////////////////////////////////
    // Evaluate command line arguments //
    /////////////////////////////////////
    if (argc <= 1) {
        cout << "Usage:" << endl;
        cout << argv[0] << " -i <net-file> [-o <out-file>] [-s <subsheet>]" << endl;
        exit(1);
    }
    string net_file;
    string out_file;
    string subsheet = "/";
    bool   read_net_file = false;
    bool   read_out_file = false;
    bool   read_subsheet = false;
    bool   verbose       = false;

    for (int i=1; i < argc; ++i) {
        if (read_net_file)    { net_file = argv[i]; read_net_file = false; continue; }
        if (read_out_file)    { out_file = argv[i]; read_out_file = false; continue; }
        if (read_subsheet)    { subsheet = argv[i]; read_subsheet = false; continue; }
        string arg = argv[i];
        if      (arg == "-i") { read_net_file = true; }
        else if (arg == "-o") { read_out_file = true; }
        else if (arg == "-s") { read_subsheet = true; }
        else if (arg == "-v") { verbose       = true; }
        else {
            cerr << "Unknown command line option: " << arg << " -> Exit!" << endl;
            exit(1);
        }
    }
    if (net_file.empty()) {
        cerr << "No input filename given. Exit!" << endl;
        exit(1);
    }
    if (out_file.empty()) {
        size_t pos = net_file.find('.');
        if (pos != string::npos) {
            out_file = net_file.substr(0, pos) + ".h";
        }
    }

    ///////////////////////
    // Open the output file
    ///////////////////////
    _out.open(out_file);
    if (!_out.good()) {
        cerr << "Can not open output file " << out_file << " -> Exit!" << endl;
        exit(1);
    }

    ///////////////////////
    // Parse the *.net file
    ///////////////////////
    Node      tree;
    NetParser parser;
    if (verbose) cout << "Parsing file " << net_file << endl;
    try {
        parser.parse(net_file, tree);
    } catch(ParseException & ex) {
        cerr << "Error: " << ex.info << " -> Exit!" << endl;
        exit(1);
    }

    ////////////////
    // Find subsheet
    ////////////////
    if (verbose) cout << "Locating subsheet " << subsheet << endl;
    string classname;
    Node * design = tree.find_Node("design");
    for (Node & sheet : design->_children) {
        if (sheet._name == "sheet") {
            string name = sheet.get_attr("name");
            if (name == subsheet) {
                classname = sheet.find_Node("source")->_value;
                size_t pos = classname.find(".sch");
                classname.erase(pos);
                name2var(classname);
                break;
            }
        }
    }
    if (classname.empty()) {
        cerr << "Subsheet '" << subsheet << "' not found!" << endl;
        cerr << "Available subsheets are:" << endl;
        for (Node & sheet : design->_children) {
            if (sheet._name == "sheet") {
                cerr << sheet.get_attr("name") << endl;
            }
        }
        exit(1);
    }

    /////////////////////////////////
    // Delete all unneeded components
    /////////////////////////////////
    map<string, int> needed_refs;
    map<string, int> included_components;
    Node * components = tree.find_Node("components");
    for(auto comp = components->_children.begin(); comp != components->_children.end();) {
        string path = comp->find_Node("sheetpath")->get_attr("names");
        string part = comp->find_Node("libsource")->get_attr("part");
        if (path.find(subsheet) != 0) {
            comp = components->_children.erase(comp);
        } else {
            needed_refs[ comp->get_attr("ref") ]++;
            included_components[ part ]++;
            ++comp;
        }
    }

    ////////////////////////////////////////
    // Delete all unneeded nodes in all nets
    ////////////////////////////////////////
    Node * nets = tree.find_Node("nets");
    for(auto net = nets->_children.begin(); net != nets->_children.end(); ++net) {
        for (auto node = net->_children.begin(); node != net->_children.end();) {
            if (node->_name != "node") {
                ++node;
                continue;
            }
            if(needed_refs.count( node->get_attr("ref") ) == 0) {
                node = net->_children.erase(node);
            } else {
                ++node;
            }
        }
    }

    /////////////////////////////////////////////////////
    // Output include guards, components and class header
    /////////////////////////////////////////////////////
    if (verbose) cout << "Generating file " << out_file << endl;
    _out << "//" << endl;
    _out << "// This file was generated with ** Net2Sim **!" << endl;
    _out << "// DO NOT EDIT - CHANGES MIGHT BE OVERWRITTEN!" << endl;
    _out << "//" << endl;
    _out << "#ifndef _" << classname << "_H_" << endl;
    _out << "#define _" << classname << "_H_" << endl;
    _out << endl;
    _out << "#include <string>"  << endl;
    _out << "#include \"Pin.h\"" << endl;
    _out << "#include \"Bus.h\"" << endl;
    for (auto comp : included_components) {
        string c = comp.first;
        name2var(c);
        _out << "#include \"" << c << ".h\"";
        _out << "\t" << "// " << comp.second << " parts" << endl;
    }
    _out << endl
        << "class " << classname << " " << "{" << endl
        << "private:" << endl;

    ///////////////////////////////////////////
    // Generate private attributes (components)
    ///////////////////////////////////////////
    struct foo { string part; string ref; string idx; };
    vector< foo > needed_components;
    for (Node & component : components->_children) {
        string ref  = component.get_attr("ref");
        string part = component.find_Node("libsource")->get_attr("part");
        string path = component.find_Node("sheetpath")->get_attr("names");
        if (path.find(subsheet) == 0) {
            string idx;
            split_name_index(ref, idx);
            foo bar = {part, ref, idx};
            needed_components.push_back(bar);
        }
    }
    std::sort(needed_components.begin(), needed_components.end(),
            [] (foo & lhs, foo & rhs) {
        if (lhs.ref == rhs.ref)
            return stoi(lhs.idx) < stoi(rhs.idx);
        else
            return lhs.ref < rhs.ref;
    });
    for (auto a : needed_components) {
        name2var(a.part);
        _out << "    " << a.part << "\t" << a.ref << a.idx << ";" << endl;
    }

    ///////////////
    // Prepare Nets
    ///////////////
    vector<NetEntry> found_nets;
    nets = tree.find_Node("nets");
    for (Node & net : nets->_children) {
        string name = net.get_attr("name");
        // Skip not connected Pins (no name, only one Pin)
        if (name.substr(0,5) == "Net-(" && net.count_attr("node") == 1) {
            net.set_attr("name", "");
            continue;
        }
        // Skip nets with no Pins
        if (net.count_attr("node") == 0) {
            net.set_attr("name", "");
            continue;
        }
        // Check if net name can be shortened
        int pos_subsheet = name.find(subsheet);
        if (pos_subsheet == 0) {
            name = name.substr(subsheet.size());
        }

        string index;
        name2var(name);
        net.set_attr("name", name.c_str());

        // Divide Net into base name and index, if possible
        int i = name.size()-1;
        bool index_found = false;
        while(isdigit(name[i]) && (i >= 0)) {
            index_found = true;
            --i;
        }
        // Check if index was found
        if (index_found) {
            index = name.substr(i+1);
            name  = name.substr(0,i+1);
        }
        found_nets.emplace_back(name, index, false);
    }

    std::sort(found_nets.begin(), found_nets.end(),
            [] (NetEntry & lhs, NetEntry & rhs) {
        if (lhs.base == rhs.base)
            return stoi(lhs.index) < stoi(rhs.index);
        else
            return lhs.base < rhs.base;
    });

    _out << endl << "public:" << endl;

    //////////////////////////////////
    // Find busses in the sorted nets.
    // Generate Pins and Busses
    //////////////////////////////////
    auto it     = found_nets.begin();
    auto first  = *it;
    bool isBus  = false;
    while (it != found_nets.end()) {
        it++;
        if (it == found_nets.end()) break;
        auto next = *it;
        if (first.base    == next.base) { //}&&
            //stoi(first.index)+1 == stoi(next.index)) {
            isBus         = true;
            it->isBus     = true;
            (it-1)->isBus = true;
            first = next;
            continue;
        }
        define_bus(first.base, first.index, isBus);
        first = next;
        isBus = false;
    }
    define_bus(first.base, first.index, isBus);

    ///////////////////////////////////////////
    // Generate CTOR calls with component names
    ///////////////////////////////////////////
    _out << endl << "    " << classname << "(std::string n) :" <<endl;
    for (size_t i = 0; i < needed_components.size(); ++i) {
        string ref = needed_components[i].ref + needed_components[i].idx;
        _out << "        " << ref << "(\"" << ref << "\")";
        if (i+1 !=needed_components.size()) _out << ",";
        _out << endl;
    }

    ///////////////////////
    // Generate connections
    ///////////////////////
    _out << "    {" << endl;
    vector<string> net_output;
    for (Node & net : nets->_children) {
        string name = net.get_attr("name");
        // Check if net was deleted
        if (name.empty()) continue;
        for(Node & n : net._children) {
            if (n._name == "node") {
                string ref = n.get_attr("ref");
                string pin = n.get_attr("pin");
                change_to_bus(name, found_nets);
                string s = "        ";
                s += name;
                s += ".connect_to(";
                s += ref + ".";
                s += "p[" + pin + "]";
                //                s += get_pin_name(tree, ref.c_str(), pin.c_str());
                s += ");\n";
                net_output.push_back(s);
            }
        }
    }
    std::sort(net_output.begin(), net_output.end());
    for (string s : net_output) _out << s;
    _out << "    }" << endl
         << "};" << endl;

    /////////////////////
    // Output final endif
    /////////////////////
    _out << endl;
    _out << "#endif\t// _" << classname << "_H_" << endl;
    return 0;
}


void Net2Sim::name2var(string & s) {
    std::replace(s.begin(),  s.end(), '/', '_');
    std::replace(s.begin(),  s.end(), '-', '_');
    std::replace(s.begin(),  s.end(), '~', 'n');
    std::replace(s.begin(),  s.end(), '(', '_');
    std::replace(s.begin(),  s.end(), ')', '_');
    if (!(std::isalpha(s[0]) || s[0] == '_')) s = "_" + s;
}


bool Net2Sim::split_name_index(string & name, string & idx) {
    int i = name.size()-1;
    bool index_found = false;
    while(isdigit(name[i]) && (i >= 0)) {
        index_found = true;
        --i;
    }
    // Check if index was found
    if (index_found) {
        idx  = name.substr(i+1);
        name = name.substr(0,i+1);
    }
    return index_found;
}


void Net2Sim::define_bus(string base, string index, bool isBus) {
    if (isBus) {
        _out << "    Bus<" << stoi(index)+1 << ">\t"
             << base << ";" << endl;
    } else {
        _out << "    Pin  \t" << base;
        if (!index.empty()) _out << index;
        _out << ";" << endl;
    }
}


void Net2Sim::change_to_bus(string & net, vector<NetEntry> & found_nets) {
    for(auto entry : found_nets) {
        if (net == (entry.base + entry.index)) {
            if (entry.isBus) {
                net = entry.base + "[" + entry.index + "]";
            }
        }
    }
}

