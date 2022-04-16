#pragma once
// all files depend on utils, so put all needed includes here
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <istream>
#include <iostream>
#include <ostream>
#include <stdexcept>

using namespace std;

struct utils {
    // helper function to separate a line into a vector by delims
    static vector<string> delimitLine(const string line, const vector<char>& delims);
    static vector<string> delimitLine(const string line, const char delim);

    // helper function to remove certain characters from a string
    static string removeChar(const string line, const vector<char>& cs);
    static string removeChar(const string line, const char c);
};