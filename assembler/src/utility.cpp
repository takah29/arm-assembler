#include "utility.hpp"

#include <regex>
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

std::vector<std::string> split_reg(const std::string &s, const std::string regex_delim) {
    std::vector<std::string> v;

    std::regex separator{regex_delim};
    auto ite = std::sregex_token_iterator(s.begin(), s.end(), separator, -1);
    auto end = std::sregex_token_iterator();
    while (ite != end) {
        v.push_back(*ite++);  // 分割文字列を格納
    }
    return v;
}
