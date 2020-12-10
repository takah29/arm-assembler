#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "assembler.hpp"
#include "utility.hpp"

using namespace std;

int main(int argc, char **argv) {
    std::vector<std::string> args(argv, argv + argc);

    if (argc < 2 or 3 < argc) {
        printf("Error: Wrong number of arguments.\n");
        printf("Usage: assembler <textfile> [option -d]");
        return 1;
    }

    string asmfile_path = args[1];
    bool debug_flag = (args[2] == "-d") ? true : false;
    ifstream infile(asmfile_path);

    if (infile.fail()) {
        printf("Error: Failed to open assembly file.\n");
        return 1;
    }

    Assembler assembler{};
    string asmcode;
    while (getline(infile, asmcode)) {
        asmcode = strip(asmcode, " ");
        if (asmcode == "" or asmcode[0] == '#') {
            continue;
        }
        auto machine_code = assembler.convert(asmcode, debug_flag);
        if (debug_flag) {
            cout << asmcode << " -> ";
        }
        cout << bitset<32>(machine_code) << endl;
    }
    return 0;
}
