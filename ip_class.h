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
    static auto _filter(ip_list list, ip_t::size_type cnt, T val, Args... args) {
        decltype (list) ip1 = _filter(list, cnt+1, args...);
        //или можно было бы без конечной функции:
        //decltype (list) ip1;
        //if(cnt == list.size() - 1) ip1 = list;
        //else ip1 = _filter(list, cnt+1, args...);
        decltype (list) ip2;
        for(const auto & n : ip1) {
            if(n[cnt] == val)
                ip2.push_back(n);
        }
        return ip2;
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
