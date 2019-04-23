#ifndef _SORTED_TABLE_
#define _SORTED_TABLE_

#include "tables.h"

class sorted_table : public Tables{
    private:
        std::vector <std::pair<std::string, Polinom> > un;  
    public:    
        sorted_table() {};
        sorted_table(int _size) {};
        ~sorted_table() {};
        int getsize();
        bool compare (std::string s, std::string s1);
        void inserts (std::string name, Polinom a) override;
        int upper_bounds (std::string key);
        void erases (std::string name) override;
        Polinom finds (std::string name) override;
        int p_count() override;
}; 

int sorted_table::getsize() {
    return un.size();
}

bool sorted_table::compare (std::string s, std::string s1) {
    for (int i = 0; i < std::min(s.size(), s1.size()); i++) {
        if (s[i] < s1[i]) return true;
        else if (s[i] > s1[i]) return false;
    }
    if (s.size() < s1.size()) {
        return true;
    }
    else {
        return false;
    }
}

int sorted_table::upper_bounds(std::string key) {
    int left = 0, right = un.size() - 1;
    while (left <= right) {
        ++counter;
        int mid = (left + right)/2;
        if (key == un[mid].first) {
            return mid + 1;
        }
        else if (compare(key, un[mid].first)) {
            right = mid - 1;    
        }
        else {
            left = mid + 1;
        }
    }
    return left;
}

void sorted_table::inserts(std::string name, Polinom a) {
    counter = 0;
    if (un.size() == 0) {
        ++counter;
        un.push_back(make_pair(name, a));
    }
    else {
        int it = upper_bounds(name);
        if (it >= un.size()) {
            ++counter;
            un.push_back(std::make_pair(name, a));
        }
        else {
            std::pair<std::string, Polinom> mp = std::make_pair(un[un.size() - 1].first, un[un.size() - 1].second);
            std::pair<std::string,Polinom> mp1 = std::make_pair(un[it].first, un[it].second);
            un[it].second = a;
            un[it].first = name;
            for (int i = it + 1; i < un.size(); i++) {
                ++counter;
                std::pair<std::string,Polinom> temp =  std::make_pair(un[i].first, un[i].second);
                un[i] = mp1;
                mp1 = temp;
            }
            ++counter;
            un.push_back(mp);
        }
    }
}

Polinom sorted_table::finds(std::string name) {
    counter = 0;
    Polinom a;
    int it = upper_bounds(name);
    if (it < 0 || it >= un.size()) {
        return a;
    }
    else if (un[it - 1].first == name) {
        return un[it - 1].second;
    }
    else {
        return a;
    }
}

void sorted_table::erases (std::string name) {
    counter = 0;
    int it = upper_bounds(name);
    if (it < 0 || it >= un.size()) {
        return;
    }
    else if (un[it - 1].first == name) {
        ++counter;
        un.erase(un.begin() + it - 1, un.begin() + it);
    }
    else {
        return;
    }
}

int sorted_table::p_count () {
    return counter;
}

#endif
