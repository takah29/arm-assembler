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
    auto assemblies = loadtxt(asmfile_path);

    Assembler assembler{assemblies, debug_flag};
    auto result = assembler.convert_all();

    ofstream outfile("output.txt");
    for (auto &x : result) {
        outfile << bitset<32>(x) << endl;
    }
    outfile.close();

    return 0;
}
