#include <string>
#include <vector>

enum class InstructionType { DataProcessing, Memory, Branch };

class Assembler {
   public:
    Assembler();
    ~Assembler();

    std::string convert(const std::string asmcode);

   private:
    std::vector<std::string> tokenize(const std::string asmcode);
};
