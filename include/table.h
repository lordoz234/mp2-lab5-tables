#ifndef _TABLE_
#define _TABLE_

#include "hash_table.h"
#include "sorted_table.h"
#include "unsorted_table.h"
#include "polinom.h"
#include <iostream>

class table {
    private:
        hash_table a;
        sorted_table b;
        unsorted_table c;
    public:
        table(int _size) : a(_size) {};
        ~table() {};
        void inserts(std::string name, Polinom a);
        void erases(std::string name);
        Polinom finds(std::string name);
};

void table::inserts(std::string name, Polinom k) {
    a.inserts(name, k);
    std::cout << "Insert Hash Table" << " " << a.p_count() << std::endl;
    b.inserts(name, k);
    std::cout << "Insert Sorted Table" << " " << b.p_count() << std::endl;
    c.inserts(name, k);
    std::cout << "Insert Unsorted Table" << " " << c.p_count() << std::endl;
}

Polinom table::finds(std::string name) {
    Polinom r;
    r = a.finds(name);
    std::cout << "Find Hash Table" << " " << a.p_count() << std::endl;
    r = b.finds(name);
    std::cout << "Find Sorted Table" << " " << b.p_count() << std::endl;
    r = c.finds(name);
    std::cout << "Find Unorted Table" << " " << c.p_count() << std::endl;
    return r;
}

void table::erases(std::string name) {
    a.erases(name);
    std::cout << "Erase Hash Table" << " " << a.p_count() << std::endl;
    b.erases(name);
    std::cout << "Erase Sorted Table" << " " << b.p_count() << std::endl;
    c.erases(name);
    std::cout << "Erase Unsorted Table" << " " << c.p_count() << std::endl;
}

#endif
