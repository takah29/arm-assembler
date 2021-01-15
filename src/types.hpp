#ifndef _TYPES_H
#define _TYPES_H

#include <cstdint>
#include <unordered_map>

using std::int8_t;
using std::uint8_t;
using std::int16_t;
using std::uint16_t;
using std::int32_t;
using std::uint32_t;
using std::int64_t;
using std::uint64_t;

using OpcodeInfo = std::unordered_map<std::string, std::unordered_map<std::string, uint32_t>>;
using LabelInfo = std::unordered_map<std::string, int>;

#endif
