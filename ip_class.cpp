#include "ip_class.h"

//функция сравнения ip адресов
//возвращает true, если первый адрес больше, иначе false.
bool ip_class::ip_cmp(ip_t ip1, ip_t ip2) {
    for(unsigned int i = 0; i < ip1.size(); i++) {
        auto a = ip1[i];
        auto b = ip2[i];
        if(a != b) return a > b;
    }
    return false;
}
