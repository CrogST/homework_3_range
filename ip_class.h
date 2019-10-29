#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using ip_t = std::vector<int>;
using ip_list = std::vector<ip_t>;

class ip_class {

    static auto _filter(ip_list list, ip_t::size_type) {
        return list;
    }

    template <typename T, typename ...Args>
    static auto _filter(ip_list list, ip_t::size_type oct_ind, T val, Args... args) {
        ip_list ip_list1 = _filter(list, oct_ind+1, args...);
        ip_list ip_list2;
        std::copy_if(ip_list1.begin(), ip_list1.end(), std::back_inserter(ip_list2), [oct_ind, val](ip_t ip) {
            return ip[oct_ind] == val;
        });
        return ip_list2;
    }

public:

    static bool ip_cmp(ip_t a, ip_t b);

    template <typename ...Args>
    static auto filter(ip_list list, Args... args) {
        return _filter(list, 0, args...);
    }

    static auto filter_any(ip_list list, int val) {
        ip_list list_out;
        auto cmp_oct = [val](int oct) {
            return (oct == val);
        };
        auto cmp_ip = [val, &cmp_oct](ip_t ip)
        {
            return std::any_of(ip.begin(), ip.end(), cmp_oct);
        };
        std::copy_if(list.begin(), list.end(), std::back_inserter(list_out), cmp_ip);
        return list_out;
    }

};
