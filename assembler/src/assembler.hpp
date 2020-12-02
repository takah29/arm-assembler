#include <string>
#include <unordered_map>
#include <vector>

enum class InstructionType { DataProcessing, Memory, Branch };

class Assembler {
   public:
    Assembler();
    ~Assembler();

    std::string convert(const std::string asmcode);

   private:
    std::array<std::string, 27> dataproc_insts;
    std::array<std::string, 2> memory_insts;
    std::array<std::string, 2> branch_insts;

    std::vector<std::string> tokenize(const std::string asmcode);
};
