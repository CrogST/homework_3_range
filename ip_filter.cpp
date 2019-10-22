#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

//#include "ip_class.h"

using ip_t = std::vector<std::string>;
using ip_list = std::vector<ip_t>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char delim)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(delim);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(delim, start);
    }

    r.push_back(str.substr(start));

    return r;
}

bool ip_cmp(ip_t ip1, ip_t ip2) {
    for(unsigned int i = 0; i < ip1.size(); i++) {
        auto a = ip1[i];
        auto b = ip2[i];
        if(a.size() != b.size()) {
            if(a.size() > b.size())
                return true;
            else
                return false;
        } else {
            if(a.compare(b) > 0)
                return true;
            else if(a.compare(b) < 0)
                return false;
        }
    }
    return false;
}

/* итерации вручную, чтобы понять как свернуть в vt. */
//в С# есть region, можно сворачивать куски кода. А в с++ нет. А было бы здорово.

//auto filter(ip_list ip, int val) {
//    decltype (ip) ip_out;
//    for(const auto & n : ip) {
//        if(n[0].compare(std::to_string(val)) == 0)
//            ip_out.push_back(n);
//    }
//    return ip_out;
//}

//auto filter(ip_list ip, int val1, int val2) {
//    decltype (ip) ip1 = filter(ip, val1);
//    decltype (ip) ip2;
//    for(const auto & n : ip1) {
//        if(n[1].compare(std::to_string(val2)) == 0)
//            ip2.push_back(n);
//    }
//    return ip2;
//}

//auto filter(ip_list ip, int val1, int val2, int val3) {
//    decltype (ip) ip1 = filter(ip, val1, val2);
//    decltype (ip) ip2;
//    for(const auto & n : ip1) {
//        if(n[2].compare(std::to_string(val3)) == 0)
//            ip2.push_back(n);
//    }
//    return ip2;
//}

auto _filter(ip_list list, ip_t::size_type) {
    return list;
}

template <typename T, typename ...Args>
auto _filter(ip_list list, ip_t::size_type cnt, T val, Args... args) {
    decltype (list) ip1 = _filter(list, cnt+1, args...);
    //или можно было бы без конечной функции:
    //decltype (list) ip1;
    //if(cnt == list.size() - 1) ip1 = list;
    //else ip1 = _filter(list, cnt+1, args...);
    decltype (list) ip2;
    for(const auto & n : ip1) {
        if(n[cnt].compare(val) == 0)
            ip2.push_back(n);
    }
    return ip2;
}

template <typename ...Args>
auto filter(ip_list list, Args... args) {
    return _filter(list, 0, std::to_string(args)...);
}

auto filter_any(ip_list list, int val) {
    decltype (list) list_out;
    auto sval = std::to_string(val);
    //пробегаемся по ip
    for(const auto & ip : list) {
        //пробегаемся по элементам текущего ip
        for(const auto & n : ip) {
            if(n.compare(sval) == 0) {
                list_out.push_back(ip);
                break;
            }
        }
    }
    return list_out;
}

/* std::any_of - true если в коллекции есть хотя бы одно значение...
 * std::equal - сравнивает две коллекции поэлементно. Может использовать переданный предикат.
 * std::copy_if
 * */

int main(/*int argc, char const *argv[]*/)
{
    try
    {
        ip_list ip_pool;

#       if 1 //штатная работа

        //чтение файла построчно
        //формирование вектора ip адресов.
        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

#       else //отладка

        //конечно #if некрасиво использовать, знаю есть что-то другое, но надо искать и разбираться.
        //пока другого не знаю.

        ip_pool = {
            {"1", "1", "3", "4"},
            {"10", "2", "3", "4"},
            {"1", "2", "3", "3"},
            {"1", "2", "2", "4"},
            //            {"9", "1", "2", "3"},
            //            {"10", "1", "2", "4"},
            //            {"100", "1", "2", "4"},
            //            {"0", "1", "2", "4"},
            //            {"0", "1", "2", "14"},
        };
#       endif

        auto ip_list_out = [](ip_list ip_pool) {
            for(ip_list::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
            {
                for(ip_t::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
                {
                    if (ip_part != ip->cbegin())
                    {
                        std::cout << ".";

                    }
                    std::cout << *ip_part;
                }
                std::cout << std::endl;
            }
        };

        // reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), ip_cmp);
        ip_list_out(ip_pool);

        auto ip_filter = filter(ip_pool, 1);
        ip_list_out(ip_filter);

        ip_filter = filter(ip_pool, 46, 70);
        ip_list_out(ip_filter);

        // TODO filter by any byte and output
        ip_filter = filter_any(ip_pool, 46);
        ip_list_out(ip_filter);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
