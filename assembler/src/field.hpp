#include <string>
#include <vector>

#include "types.hpp"

class DataProcessingField {
   public:
    DataProcessingField();
    ~DataProcessingField();

    void input(std::vector<std::string> asmcode_v);
    uint32_t output();

   private:
    uint32_t cond;
    uint32_t op;
    uint32_t funct;
    uint32_t rn;
    uint32_t rd;
    uint32_t src2;
}
