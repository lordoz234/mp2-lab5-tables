#ifndef _TABLES_
#define _TABLES_
#include "polinom.h"
#include <iostream>
#include <vector>
#include <utility>

class Tables {
    protected:
        int size;
        int counter;
    public:
        Tables() {}
        virtual ~Tables() {}
        virtual void inserts(std::string name, Polinom a) = 0;
        virtual void erases(std::string name) = 0;
        virtual Polinom finds(std::string name) =  0;
        virtual int p_count() = 0;
};

#endif
