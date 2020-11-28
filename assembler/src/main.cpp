#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::string strip(std::string& s, const std::string trim_str) {
    std::string result;

    std::string::size_type left = s.find_first_not_of(trim_str);
    if (left != std::string::npos) {
        std::string::size_type right = s.find_last_not_of(trim_str);
        result = s.substr(left, right - left + 1);
    }
    return result;
}

string asmcode_to_bits(const string asmcode) { return asmcode; }

int main(int argc, char** argv) {
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
    }
    return 0;
}
