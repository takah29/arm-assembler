#ifndef _UTILITY_H
#define _UTILITY_H

#include <iostream>
#include <string>

template <class... A>
void print() {
    std::cout << std::endl;
}
template <class... A>
void prints_rest() {
    std::cout << std::endl;
}
template <class T, class... A>
void prints_rest(const T &first, const A &... rest) {
    std::cout << " " << first;
    prints_rest(rest...);
}
template <class T, class... A>
void print(const T &first, const A &... rest) {
    std::cout << first;
    prints_rest(rest...);
}

std::string strip(std::string &s, const std::string trim_str);

#endif
