#pragma once

#include <string>
#include <vector>

//using vi = std::vector<int>;
//template<typename T>
//using v = std::vector<T>;
using ip_t = std::vector<std::string>;
using ip_list = std::vector<ip_t>;

extern bool ip_cmp(ip_t a, ip_t b);
