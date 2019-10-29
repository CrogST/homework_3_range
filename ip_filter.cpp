#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "ip_class.h"

auto split(const std::string &str, char delim)
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

int main()
{
    try
    {
        ip_list ip_pool;

        //чтение файла построчно
        //формирование вектора ip адресов.
        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            auto ip_str = split(v.at(0), '.');
            ip_t ip;
            for(const auto & s : ip_str)
                ip.push_back(std::stoi(s));
            ip_pool.push_back(ip);
        }

        //вывод списка адресов
        auto ip_list_out = [](ip_list ip_pool) {
            for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
            {
                for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
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
        std::sort(ip_pool.begin(), ip_pool.end(), ip_class::ip_cmp);
        ip_list_out(ip_pool);

        auto ip_filter = ip_class::filter(ip_pool, 1);
        ip_list_out(ip_filter);

        ip_filter = ip_class::filter(ip_pool, 46, 70);
        ip_list_out(ip_filter);

        ip_filter = ip_class::filter_any(ip_pool, 46);
        ip_list_out(ip_filter);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
