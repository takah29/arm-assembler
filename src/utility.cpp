#include "utility.hpp"

#include <fstream>
#include <regex>
#include <string>
#include <vector>

void print() { std::cout << std::endl; }

std::string strip(const std::string& s) {
    auto remove_chars = " \t\v\r\n";
    std::string result = s;

    auto left = s.find_first_not_of(remove_chars);
    if (left != std::string::npos) {
        auto right = s.find_last_not_of(remove_chars);
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

std::string unit_space(const std::string s) {
    std::string ret = s.substr(0, 1);

    for (size_t i = 1; i < s.size(); i++) {
        if (s[i - 1] != ' ' or s[i] != ' ') {
            ret += s[i];
        }
    }
    return ret;
}

std::vector<std::string> split_reg(const std::string& s, const std::string regex_delim) {
    std::vector<std::string> v;

    std::regex separator{regex_delim};
    auto ite = std::sregex_token_iterator(s.begin(), s.end(), separator, -1);
    auto end = std::sregex_token_iterator();
    while (ite != end) {
        v.push_back(*ite++);  // 分割文字列を格納
    }
    return v;
}

std::string replace_all(const std::string str, const std::string from_str, const std::string to_str) {
    auto tmp_str = str;
    while (1) {
        auto pos = tmp_str.find(from_str);
        if (pos == std::string::npos) break;
        tmp_str.replace(pos, from_str.size(), to_str);
    }
    return tmp_str;
}

std::vector<std::string> loadtxt(std::string filepath) {
    std::vector<std::string> result{};
    std::string line;
    std::ifstream infile(filepath);

    while (getline(infile, line)) {
        result.emplace_back(line);
    }

    return result;
}