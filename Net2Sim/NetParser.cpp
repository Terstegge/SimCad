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
#include "NetParser.h"

void NetParser::parse(ifstream & fs, Node & tree)
{
    parse_node(tree._children, fs);
}


void NetParser::parse_node(std::vector<Node> & nodes,
                           ifstream & fs, int level)
{
    char c;
    // Check for empty vector
    if (nodes.empty()) nodes.emplace_back();
    while(fs.good()) {
        // Get current node
        Node & n = nodes.back();
        // Get next character
        fs >> std::ws >> c;
        if (c != '(') {
            throw Net2SimException("Expected '('");
            return;
        }
        // Get Name
        n._name = get_word(fs);
        // Check next char
        if (fs.peek() == '(') {
            parse_node(n._children, fs, level+1);
        }
        // Get Value
        n._value = get_word(fs);
        fs >> c;
        if (c != ')') {
            throw Net2SimException("Expected ')'");
            return;
        }
        // Check next char
        fs >> std::ws;
        if (fs.peek() != '(') return;
        nodes.emplace_back();
    }
}

string NetParser::get_word(ifstream & fs)
{
    string result;
    char c;
    // Skip whitespace
    fs >> std::ws;
    // Check for string literals
    if (fs.peek() == '"') {
        fs >> c;    // Skip quotes
        getline(fs, result, '"');
    } else {
        c = fs.peek();
        while(fs.good() &&
              c != '('  && c != ')'  && c != ' ' &&
              c != '\n' && c != '\r' && c != '\t')
        {
            fs >> c;
            result += c;
            c = fs.peek();
        }
    }
    fs >> std::ws;
    return result;
}

