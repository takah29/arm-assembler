#ifndef _UTILITY_H
#define _UTILITY_H

#include <array>
#include <iostream>
#include <string>
#include <vector>

// デバッグ用print関数
void print();

/**
 * 可変長引数、任意型
 */
template <class Head, class... Tail>
void print(Head&& head, Tail&&... tail) {
    std::cout << head;
    if (sizeof...(tail) != 0) std::cout << " ";
    print(std::forward<Tail>(tail)...);
}

/**
 * 1次元vectorをスペース区切りで表示する
 */
template <class T>
void print(std::vector<T>& vec) {
    for (auto& a : vec) {
        std::cout << a;
        if (&a != &vec.back()) std::cout << " ";
    }
    std::cout << std::endl;
}

/**
 * 2次元vectorを改行とスペース区切りで表示する
 */
template <class T>
void print(std::vector<std::vector<T>>& df) {
    for (auto& vec : df) {
        print(vec);
    }
}
std::string strip(std::string& s, const std::string trim_str);
std::string unit_space(const std::string s);
std::vector<size_t> find_all(const std::string str, const std::string substr);
std::vector<std::string> split_reg(const std::string& s, const std::string regex_delim);
std::string replace_all(const std::string str, const std::string from_str, const std::string to_str);
#endif
