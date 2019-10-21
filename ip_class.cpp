#include "ip_class.h"

//функция сравнения ip адресов
//возвращает true, если первый адрес больше
//иначе false.
bool ip_cmp(ip a, ip b) {
    for(unsigned int i = 0; i < a.size(); i++) {
        if(a[i].compare(b[i]) > 0) return true;
        else if(a[i].compare(b[i]) < 0) return false;
    }
    return false;
};
