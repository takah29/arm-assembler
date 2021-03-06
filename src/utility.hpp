#ifndef _UTILITY_H
#define _UTILITY_H

#include <algorithm>
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

template <typename T>
T rotl(const T n, const uint32_t s) {
    if (!(0 <= s and s <= sizeof(T) * 8)) {
        throw std::runtime_error("the shift size is too large.");
    }
    return (n << s) | (n >> (sizeof(T) * 8 - s));
}

template <typename T>
T rotr(const T n, const uint32_t s) {
    if (!(0 <= s and s <= sizeof(T) * 8)) {
        throw std::runtime_error("the shift size is too large.");
    }
    return (n >> s) | (n << (sizeof(T) * 8 - s));
}

template <class T, class S>
std::vector<std::tuple<T, S>> zip(std::vector<T> container1, std::vector<S> container2) {
    size_t min_size = std::min({container1.size(), container2.size()});
    std::vector<std::tuple<T, S>> result{};

    for (size_t i = 0; i < min_size; i++) {
        result.emplace_back(container1[i], container2[i]);
    }

    return result;
}

std::string strip(const std::string& string);
std::string unit_space(const std::string s);
std::vector<size_t> find_all(const std::string str, const std::string substr);
std::vector<std::string> split_reg(const std::string& s, const std::string regex_delim);
std::string replace_all(const std::string str, const std::string from_str, const std::string to_str);
std::vector<std::string> loadtxt(std::string filepath);

#endif
