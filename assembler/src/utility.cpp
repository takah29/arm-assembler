#include "utility.hpp"

#include <string>
#include <vector>

void print() { std::cout << std::endl; }

std::string strip(std::string &s, const std::string trim_str) {
    std::string result;

    std::string::size_type left = s.find_first_not_of(trim_str);
    if (left != std::string::npos) {
        std::string::size_type right = s.find_last_not_of(trim_str);
        result = s.substr(left, right - left + 1);
    }
    return result;
}

std::vector<size_t> find_all(const std::string str, const std::string substr) {
    std::vector<size_t> result;

    int subStrSize = substr.size();
    size_t pos = str.find(substr);

    while (pos != std::string::npos) {
        result.push_back(pos);
        pos = str.find(substr, pos + subStrSize);
    }

    return result;
}
