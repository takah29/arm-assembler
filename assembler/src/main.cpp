#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
        cout << asmcode << " -> " << asmcode_to_bits(asmcode) << endl;
    }
    return 0;
}
