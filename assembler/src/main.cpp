#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utility.hpp"

using namespace std;

vector<string> tokenize(const string asmcode) {
    vector<string> tokens{};
    size_t left_pos = 0, right_pos = 0;
    bool in_brackets = false;

    for (size_t i = 1; i < asmcode.size(); i++) {
        if (in_brackets == true) continue;

        if (asmcode[i] == ' ') {
            if (asmcode[i - 1] == ',') {
                right_pos = left_pos = i;
            } else if (asmcode[i - 1] != ' ') {
                right_pos = i;
                tokens.push_back(asmcode.substr(left_pos, right_pos - left_pos));
                left_pos = i;
            }
        } else if (asmcode[i] == '[' or asmcode[i] == '{') {
            in_brackets = true;
            left_pos = right_pos = i;
        } else if (asmcode[i] == ']' or asmcode[i] == '}') {
            in_brackets = false;
            right_pos = i;
            tokens.push_back(asmcode.substr(left_pos, right_pos - left_pos + 1));
            left_pos = i;
        } else if (asmcode[i] == ',') {
            right_pos = i;
            tokens.push_back(asmcode.substr(left_pos, right_pos - left_pos));
            left_pos = i;
        } else if (asmcode[i] != ' ' and asmcode[i - 1] == ' ') {
            left_pos = right_pos = i;
        }
    }

    tokens.push_back(asmcode.substr(left_pos, asmcode.size() - left_pos + 1));

    return tokens;
}

string asmcode_to_bits(const string asmcode) { return asmcode; }

int main(int argc, char **argv) {
    std::vector<std::string> args(argv, argv + argc);

    if (argc != 2) {
        printf("Error: Wrong number of arguments.\n");
        printf("Usage: assembler <textfile>");
        return 1;
    }

    string asmfile_path = args[1];
    ifstream infile(asmfile_path);

    if (infile.fail()) {
        printf("Error: Failed to open assembly file.\n");
        return 1;
    }

    string asmcode;
    while (getline(infile, asmcode)) {
        asmcode = strip(asmcode, " ");
        if (asmcode == "" or asmcode[0] == '#') {
            continue;
        }
        cout << asmcode << " -> " << asmcode_to_bits(asmcode) << endl;
        for (auto x : tokenize(asmcode)) {
            cout << x << ' ' << x.size() << endl;
        }
    }
    return 0;
}
