#include "utility.hpp"

std::string strip(std::string &s, const std::string trim_str) {
    std::string result;

    std::string::size_type left = s.find_first_not_of(trim_str);
    if (left != std::string::npos) {
        std::string::size_type right = s.find_last_not_of(trim_str);
        result = s.substr(left, right - left + 1);
    }
    return result;
}
