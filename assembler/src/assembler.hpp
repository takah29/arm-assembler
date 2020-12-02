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
    std::array<std::string, 27> data_processing_instructions;
    std::array<std::string, 2> memory_instructions;
    std::array<std::string, 2> branch_instructions;

    std::vector<std::string> tokenize(const std::string asmcode);
};
