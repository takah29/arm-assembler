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
        printf("Usage: assembler <textfile> [option -d]\n");
        return 1;
    }

    string asmfile_path = args[1];
    bool debug_flag = (argc == 3 and args[2] == "-d") ? true : false;
    ifstream infile(asmfile_path);

    if (infile.fail()) {
        printf("Error: Failed to open assembly file.\n");
        return 1;
    }

    Assembler assembler{};
    string asmcode;
    while (getline(infile, asmcode)) {
        asmcode = unit_space(strip(asmcode));
        if (asmcode == "" or asmcode.substr(0, 2) == "//") {
            continue;
        }
        auto machine_code = assembler.convert(asmcode);
        if (debug_flag) {
            cout << asmcode << " -> ";
        }
        cout << bitset<32>(machine_code) << endl;
    }
    return 0;
}
