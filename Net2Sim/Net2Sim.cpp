///////////////////////////////////////////////
//
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//
//  A simulation package for digital circuits
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
    try {

    /////////////////////////////////////
    // Evaluate command line arguments //
    /////////////////////////////////////
    if (argc <= 1) {
        cout << "Usage:" << endl;
        cout << argv[0] << " <options> kicad-netfile" << endl;
        cout << " -c filename  :  Name of generated  .cpp-file (default netfile.cpp)" << endl;
        cout << " -h filename  :  Name of generated  .h-file (default netfile.h)"     << endl;
        cout << " -s subsheet  :  Generate code for specific subsheet (default /)   " << endl;
        cout << " -v           :  Verbose output" << endl;
        exit(1);
    }
    string net_file;
    string c_file;
    string h_file;
    string subsheet = "/";
    bool   read_c_file   = false;
    bool   read_h_file   = false;
    bool   read_subsheet = false;
    bool   verbose       = false;

    for (int i=1; i < argc; ++i) {
        if (read_c_file)      { c_file   = argv[i]; read_c_file   = false; continue; }
        if (read_h_file)      { h_file   = argv[i]; read_h_file   = false; continue; }
        if (read_subsheet)    { subsheet = argv[i]; read_subsheet = false; continue; }
        string arg = argv[i];
        if      (arg == "-c") { read_c_file   = true; }
        else if (arg == "-h") { read_h_file   = true; }
        else if (arg == "-s") { read_subsheet = true; }
        else if (arg == "-v") { verbose       = true; }
        else {
            net_file = argv[i];
            if ((i+1) != argc) {
                cerr << "Too many arguments: " << argv[i+1] << " -> Exit!" << endl;
                exit(1);
            }
        }
    }
    if (net_file.empty()) {
        cerr << "No input filename given. Exit!" << endl;
        exit(1);
    }

    /////////////////////////////////////
    // Fill filenames with default values
    /////////////////////////////////////
    size_t colon_pos = net_file.find('.');
    if (h_file.empty()) {
        if (colon_pos != string::npos) {
            h_file = net_file.substr(0, colon_pos) + ".h";
        } else {
            h_file = net_file + ".h";
        }
    }
    if (c_file.empty()) {
        if (colon_pos != string::npos) {
            c_file = net_file.substr(0, colon_pos) + ".cpp";
        } else {
            c_file = net_file + ".cpp";
        }
    }

    //////////////////////
    // Open the input file
    //////////////////////
    ifstream net_ifs(net_file);
    if (!net_ifs.good()) {
        cerr << "Could not open input file " << net_file << " -> Exit!" << endl;
        exit(1);
    }

    ////////////////////////
    // Open the output files
    ////////////////////////
    h_ofs.open(h_file);
    if (!h_ofs.good()) {
        cerr << "Could not open output file " << h_file << " -> Exit!" << endl;
        exit(1);
    }
    c_ofs.open(c_file);
    if (!c_ofs.good()) {
        cerr << "Could not open output file " << c_file << " -> Exit!" << endl;
        exit(1);
    }

    ///////////////////////
    // Parse the *.net file
    ///////////////////////
    Node      tree;
    NetParser parser;
    if (verbose) cout << "Parsing file " << net_file << endl;
    parser.parse(net_ifs, tree);

    ////////////////
    // Find subsheet
    ////////////////
    if (verbose) cout << "Locating subsheet " << subsheet << endl;
    string classname;
    Node * design = tree.find_Node("design");
    for (Node & sheet : design->_children) {
        if (sheet._name == "sheet") {
            // Get the path name of the sheet
            string name = sheet.get_attr("name");
            if (name == subsheet) {
                // Found it! Get the source name,
                // remove the .sch ending and set
                // the remainder as the class name
                classname = sheet.find_Node("source")->_value;
                size_t pos = classname.find(".sch");
                classname.erase(pos);
                name2var(classname);
                break;
            }
        }
    }
    if (classname.empty()) {
        // We did not find the subsheet and did not set a class name.
        // Show all available subsheets and exit.
        cerr << "Subsheet '" << subsheet << "' not found!" << endl;
        cerr << "Available subsheets are:" << endl;
        for (Node & sheet : design->_children) {
            if (sheet._name == "sheet") {
                cerr << sheet.get_attr("name") << endl;
            }
        }
        exit(1);
    }

    //////////////////////////////
    // Store all needed components
    //////////////////////////////
    vector<component_entry> used_components;
    map<string, int>        needed_refs;
    // Loop over all components
    Node * components = tree.find_Node("components");
    for(auto comp = components->_children.begin(); comp != components->_children.end();) {
        // Get the sheet path and the part name
        string path = comp->find_Node("sheetpath")->get_attr("names");
        string part = comp->find_Node("libsource")->get_attr("part");
        if (path.find(subsheet) != 0) {
            // Delete the component because it is not needed
            comp = components->_children.erase(comp);
        } else {
            // The entry to store
            component_entry ce;
            // Compute component value
            ce.value = comp->get_attr("value");
            // Compute reference base name and index
            ce.ref_base = comp->get_attr("ref");
            name2var(ce.ref_base);
            // Store the full reference as a needed one
            needed_refs[ ce.ref_base ]++;
            // Split reference in base and index
            split_name_index(ce.ref_base, ce.ref_idx);
            // Compute part and possible argument
            ce.part = part;
            split_name_index(ce.part, ce.part_arg);
            // Check if part is a build-in gate
            if ( (ce.part == "AND")  ||
                 (ce.part == "NAND") ||
                 (ce.part == "OR")   ||
                 (ce.part == "NOR")  ||
                 (ce.part == "EOR")  ||
                 (ce.part == "INH") ) {
                // Leave the part arg entry as it is.
                // The part argument will be the template parameter.
            } else {
                // Part was not a build-in part. Reset the part
                // name to the original value (no template type!)
                ce.part     = part;
                ce.part_arg = "";
            }
            // Store the entry
            used_components.push_back(ce);
            ++comp;
        }
    }

    //////////////////////////////
    // Calculate all include files
    //////////////////////////////
    map<string, int> included_components;
    for (component_entry & ce: used_components) {
        included_components[ ce.part ]++;
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
            string ref = node->get_attr("ref");
            name2var( ref );
            if(needed_refs.count( ref ) == 0) {
                node = net->_children.erase(node);
            } else {
                ++node;
            }
        }
    }

    /////////////////////////////////////////////////////
    // Output include guards, components and class header
    /////////////////////////////////////////////////////
    if (verbose) cout << "Generating file " << h_file << endl;
    h_ofs << "//" << endl;
    h_ofs << "// This file was generated with ** Net2Sim **!" << endl;
    h_ofs << "// DO NOT EDIT - CHANGES MIGHT BE OVERWRITTEN!" << endl;
    h_ofs << "//" << endl;
    h_ofs << "#ifndef _" << classname << "_H_" << endl;
    h_ofs << "#define _" << classname << "_H_" << endl;
    h_ofs << endl;
    h_ofs << "#include <string>"  << endl;
    h_ofs << "#include \"Pin.h\"" << endl;
    h_ofs << "#include \"Bus.h\"" << endl;
    for (auto comp : included_components) {
        string c = comp.first;
        name2var(c);
        h_ofs << "#include \"" << c << ".h\"";
        if (c.size() < 3) h_ofs << "\t";
        h_ofs << "\t" << "// " << comp.second << " parts" << endl;
    }
    h_ofs << endl
        << "class "  << classname << " " << "{" << endl
        << "public:" << endl;

    ///////////////////////////////////////////
    // Generate private attributes (components)
    ///////////////////////////////////////////

    // Sort the components by reference
    std::sort(used_components.begin(), used_components.end(),
            [] (component_entry & lhs, component_entry & rhs) {
        if (lhs.ref_base == rhs.ref_base)
            return stoi(lhs.ref_idx) < stoi(rhs.ref_idx);
        else
            return lhs.ref_base < rhs.ref_base;
    });

    // Output part attributes
    h_ofs << "    // Components" << endl;
    for (component_entry & ce : used_components) {
        name2var(ce.part);
        if (ce.part_arg == "") {
            // Standard part without template argument
            h_ofs << "    " << ce.part;
            if (ce.part.size() < 4) h_ofs << "\t";
        } else {
            // Build-in part with template argument
            h_ofs << "    " << ce.part << "<" << ce.part_arg << ">";
        }
        h_ofs << "\t" << ce.ref_base << ce.ref_idx << ";" << endl;
    }

    ///////////////
    // Prepare Nets
    ///////////////
    vector<net_entry> found_nets;
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
            [] (net_entry & lhs, net_entry & rhs) {
        if (lhs.base == rhs.base)
            return stoi(lhs.index) < stoi(rhs.index);
        else
            return lhs.base < rhs.base;
    });

    h_ofs << "    // Nets" << endl;

    //////////////////////////////////
    // Find busses in the sorted nets.
    // Generate Pins and Busses
    //////////////////////////////////
    vector<string> base_names;
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
        base_names.push_back(first.base);
        first = next;
        isBus = false;
    }
    define_bus(first.base, first.index, isBus);
    base_names.push_back(first.base);

    ////////////////////////////
    // Generate CTOR declaration
    ////////////////////////////
    h_ofs << endl << "public:" << endl;
    h_ofs << "    " << classname << "(std::string name);" <<endl;
    h_ofs << "};" << endl;

    /////////////////////
    // Output final endif
    /////////////////////
    h_ofs << endl;
    h_ofs << "#endif\t// _" << classname << "_H_" << endl;
    h_ofs.close();

    /////////////////////////////////////////////////////
    // Output include guards, components and class header
    /////////////////////////////////////////////////////
    if (verbose) cout << "Generating file " << c_file << endl;
    c_ofs << "//" << endl;
    c_ofs << "// This file was generated with ** Net2Sim **!" << endl;
    c_ofs << "// DO NOT EDIT - CHANGES MIGHT BE OVERWRITTEN!" << endl;
    c_ofs << "//" << endl;

    string hfile = h_file;
    const size_t last_slash_idx = hfile.find_last_of("/");
    if (string::npos != last_slash_idx)  hfile.erase(0, last_slash_idx + 1);
    c_ofs << "#include \"" << hfile << "\""<< endl;

    ///////////////////////////
    // Generate CTOR definition
    ///////////////////////////
    c_ofs << endl << classname << "::" << classname << "(std::string name) :" <<endl;
    for (size_t i = 0; i < used_components.size(); ++i) {
        string ref = used_components[i].ref_base + used_components[i].ref_idx;
        if (used_components[i].part == "R" ||
            used_components[i].part == "VSOURCE" ||
            used_components[i].part == "ISOURCE")
        {
            c_ofs << "    NAME(" << ref << ", "
                  << readValue(used_components[i].value) << ")";
        } else {
            c_ofs << "    NAME(" << ref << ")";
        }
        if ((i+1 != used_components.size()) || base_names.size()) c_ofs << ",";
        c_ofs << endl;
    }
    for (size_t i = 0; i < base_names.size(); ++i) {
        c_ofs << "    NAME(" << base_names[i] << ")";
        if (i+1 != base_names.size()) c_ofs << ",";
        c_ofs << endl;
    }

    ///////////////////////
    // Generate connections
    ///////////////////////
    c_ofs << "{" << endl;
    vector<string> net_output;
    for (Node & net : nets->_children) {
        string name = net.get_attr("name");
        // Check if net was deleted
        if (name.empty()) continue;
        for(Node & n : net._children) {
            if (n._name == "node") {
                string ref = n.get_attr("ref");
                name2var( ref );
                string pin = n.get_attr("pin");
                change_to_bus(name, found_nets);
                string s = "    ";
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
    for (string s : net_output) c_ofs << s;
    c_ofs << "}" << endl;
    c_ofs.close();

    } catch(Net2SimException & ex) {
        cerr << "Error: " << ex.info << " -> Exit!" << endl;
        exit(1);
    }

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
        h_ofs << "    Bus<" << stoi(index)+1 << ">\t"
             << base << ";" << endl;
    } else {
        h_ofs << "    Pin  \t" << base;
        if (!index.empty()) h_ofs << index;
        h_ofs << ";" << endl;
    }
}


void Net2Sim::change_to_bus(string & net, vector<net_entry> & found_nets) {
    for(auto entry : found_nets) {
        if (net == (entry.base + entry.index)) {
            if (entry.isBus) {
                net = entry.base + "[" + entry.index + "]";
            }
        }
    }
}

float Net2Sim::readValue(string s) {
    bool    shift_mode = true;
    float   res;
    float   factor;
    string  units = "AVRFH";

    for(int i=0; i < s.size(); ++i) {
        // Skip physical units and symbols
		if (units.find(s[i]) != string::npos) {
            continue;
        }
        if (shift_mode) {
            // Shift mode
            if (isdigit(s[i])) {
                res *= 10.0;
                res += (s[i]-'0');
            } else {
                switch(s[i]) {
                    // Decimal point
                    case '.': { res *= 1e0;  factor = 1e-1; break; }
                    // Kilo: Factor 10^3
                    case 'k':
                    case 'K': { res *= 1e3;  factor = 1e2;  break; }
                    // Mega: Factor 10^6
                    case 'M': { res *= 1e6;  factor = 1e5;  break; }
                    // Giga: Factor 10^9
                    case 'G': { res *= 1e9;  factor = 1e8;  break; }
                    // Milli: Factor 10^-3
                    case 'm': { res *= 1e-3; factor = 1e-4; break; }
                    // Micro: Factor 10^-6
                    case 'u': { res *= 1e-6; factor = 1e-7; break; }
                    // Nano: Factor 10^-12Unnamed resistors have 1k default...
                    case 'n': { res *= 1e-9; factor = 1e-10; break; }
                    // Unnamed resistors have 1k default...
                    case 'p': { res *= 1e-12; factor = 1e-13; break; }
                    default: throw Net2SimException("Wrong Value format: " + s);
                }
                shift_mode = false;  
            }            
        } else {
            // Factor mode
            if (isdigit(s[i])) {
                res += (s[i]-'0') * factor;
                factor /= 10;
            } else {
                throw Net2SimException("Wrong Value format: " + s);
            }
        }
    }
    return res;
}

