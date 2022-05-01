#include "utils.h"


// delimit line but with a single character delim (old version)
vector<string> utils::delimitLine(const string line, const char delim) {
    const vector<char> chars = { delim };
    return delimitLine(line, chars);
}

// takes a line of the csv and separates each value into a vector
vector<string> utils::delimitLine(const string line, const vector<char>& delims) {
    vector<string> separated;
    separated.push_back("");
    // checks each character and either adds a new elements to vector or adds the character to the last element
    for (char c : line) {
        bool foundDelim = false;
        for (const char& delim : delims) {
            if (c == delim) {
                separated.push_back("");
                foundDelim = true;
                break;
            }
        }
        if (!foundDelim) {
            separated.back() += c;
        }
    }
    return separated;
}


string utils::removeChar(const string line, const char c) {
    const vector<char> chars = { c };
    return removeChar(line, chars);
}

string utils::removeChar(const string line, const vector<char>& cs) {
    string output;
    for (const char& c : line) {
        bool foundDelim = false;
        for (const char& ch : cs) {
            if (c == ch) {
                foundDelim = true;
                break;
            }
        }
        if (!foundDelim) {
            output += c;
        }
    }
    return output;
}