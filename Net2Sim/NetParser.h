///////////////////////////////////////////////
//
//  This file is part of
//     ___  ____  __  __  ___    __    ____
//    / __)(_  _)(  \/  )/ __)  /__\  (  _ \
//    \__ \ _)(_  )    (( (__  /(__)\  )(_) )
//    (___/(____)(_/\/\_)\___)(__)(__)(____/
//
//  A simulation package for electronic circuits
//
//  (c) 2022  Andreas Terstegge
//
///////////////////////////////////////////////
//
// NetParser is a class to parse a KiCad Eeschema
// *.net file. The result is a tree of Node objects.
//
#ifndef _NET_PARSER_H_
#define _NET_PARSER_H_

#include "Net2SimException.h"
#include "Node.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using std::ifstream;
using std::string;
using std::vector;

class NetParser {
public:

    // Parse a Eeschema *.net file.
	// The first parameter is the input file stream.
	// The second parameter is the root of the result tree.
	// The top-level elements in the *.net file will be
	// stored as children of the root node.
	// Throws an exception if e.g. file not found.
    void parse(ifstream & fs, Node & tree);

private:
    // Recursive method to parse all Nodes in the file
    void parse_node(std::vector<Node> & n, ifstream & ifs, int level=0);

    // Read a single word from the ifstream. Words
    // are terminated by white spaces or braces.
    // String literals are handled correctly
    std::string get_word(ifstream & fs);
};

#endif // _NET_PARSER_H_
