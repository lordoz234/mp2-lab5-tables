#include <iostream>
#include "../include/polinom.h"
#include "../include/unsorted_table.h"
#include "../include/sorted_table.h"
#include "../include/hash_table.h"
#include "../include/table.h"

int main() {
    std::cout << "Enter size of table: ";
    int size;
    std::cin >> size;
    table vl(size);
    while (true) {
        std::cout << "Choose operation: " << std::endl;
        std::cout << "1. Insert" << std::endl;
        std::cout << "2. Delete" << std::endl;
        std::cout << "3. Find" << std::endl;
        std::cout << "4. If you want exit" << std::endl;
        int a;
        std::cin >> a;
        if (a == 1) {
            std::cout << "Enter the name of Polinom" << std::endl;
            std::string s;
            std::cin >> s;
            std::cout << "Enter Polinom" << std::endl;
            Polinom b;
            std::cin >> b;
            vl.inserts(s, b);
        }
        else if (a == 2) {
            std::cout << "Enter the name of Polinom" << std::endl;
            std::string s;
            std::cin >> s;
            vl.erases(s);
        }
        else if (a == 3) {
            std::cout << "Enter the name of Polinom" << std::endl;
            std::string s;
            std::cin >> s;
            Polinom temp = vl.finds(s);
            Polinom temp1;
            if (temp == temp1) {
                std::cout << "Not Found Polinom" << std::endl;
            }
            else {
                std::cout << "Found Polinom is " << temp << std::endl;
            }
        }
        else if (a == 4) {
            return 0;
        }
        else {
            std::cout << "Incorect Input";
            return 1;
        }
    }
    return 0;
}
