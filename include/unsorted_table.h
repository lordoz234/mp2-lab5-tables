#ifndef _UNSORTED_TABLE_
#define _UNSORTED_TABLE_

#include "tables.h"
 
class unsorted_table : public Tables{
    private:
        std::vector <std::pair<std::string, Polinom> > un;
        std::vector <bool> used;
    public:
        unsorted_table() {}
        ~unsorted_table() {}
        int getsize();
        void inserts (std::string name, Polinom a) override;
        void erases (std::string name) override;
        Polinom finds (std::string name) override;
        int p_count () override;
}; 

int unsorted_table::getsize() {
    return un.size();
}

void unsorted_table::inserts(std::string name, Polinom a) {
    counter = 0;
    un.push_back(std::make_pair(name, a));
    counter++;
    used.push_back(true);
}

Polinom unsorted_table::finds(std::string name) {
    Polinom a;
    counter = 0;
    for (unsigned int i = 0; i < un.size(); i++) {
        ++counter;
        if (un[i].first == name && used[i]) {
            return un[i].second;
        }
    }
    return a;
}

void unsorted_table::erases(std::string name) {
    counter = 0;
    int j = -1;
    for (unsigned int i = 0; i < un.size(); i++) {
        if (un[i].first == name) {
            used[i] = false;
            j = i;
        }
    }
    counter = j + 1;
}

int unsorted_table::p_count() {
    return counter;
}


#endif
