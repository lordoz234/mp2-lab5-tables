#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include "tables.h"

class hash_table : public Tables{
    private:
        std::vector <std::vector <std::pair<std::string, Polinom> > > un;
        int s_size;
    public:    
        hash_table(int _size = 0) {
            size = _size;
            s_size = 0;
            un.resize(size);
        };
        ~hash_table() {};
        int getsize();
        long long hash_func (std::string s);
        void inserts (std::string name, Polinom a) override;
        void erases (std::string name) override;
        Polinom finds (std::string name) override;
        int p_count() override;
}; 

int hash_table::getsize() {
    return s_size;
}

long long hash_table::hash_func (std::string s) {
    const int p = 23;
    long long hash = 0, p_pow = 1;
    for (unsigned i = 0; i < s.size(); i++) {
        hash += abs((int)(s[i] + 1)) * p_pow;
        p_pow *= p;
        p_pow %= size; 
        if (hash >= size) {
            hash -= size;
        }
    }
    return hash % size;
}

void hash_table::inserts (std::string name, Polinom a) {
    counter = 0;
    ++s_size;
    int temp = hash_func(name);
    un[temp].push_back(std::make_pair(name, a));
    counter = 1;
}

Polinom hash_table::finds (std::string name) {
    counter = 0;
    Polinom a;
    int temp = hash_func(name);
    for (unsigned i = 0; i < un[temp].size(); i++) {
        counter++;
        if (un[temp][i].first == name) {
            return un[temp][i].second;
        }
    }
    return a;
}

void hash_table::erases (std::string name) {
    counter = 0;
    int temp = hash_func(name);
    int j = -1;
    for (unsigned i = 0; i < un[temp].size(); i++) {
        if (un[temp][i].first == name) {
            un[temp].erase(un[temp].begin() + i, un[temp].begin() + i + 1);
            j = i;
        }
    }
    counter = j + 1;
}

int hash_table::p_count() {
    return counter;
}

#endif
