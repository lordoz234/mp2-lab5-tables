#ifndef _POLINOM_H_
#define _POLINOM_H_

#include <iostream>

struct Monom {
    double coef;
    int pow;
    Monom *next;
    Monom *prev;
};

class Polinom {
public:
    Monom* pol;
    Polinom();
    void ins(double coef, int pow);
    void del(double coef, int pow);
    void ins_at_end(double coef, int pow);
    void del_dublicate();
    Polinom operator*(double v) const;
    Polinom operator+(const Polinom& p) const;
    Polinom operator-(const Polinom& p) const;
    Polinom operator*(const Polinom& p) const;
    bool operator==(const Polinom& p) const;
    bool operator!=(const Polinom& p) const;
    
    friend std::ostream& operator << (std::ostream& os, const Polinom& p);
    friend std::istream& operator >> (std::istream& is, Polinom& p);
};

double eps = 1e-8;

Polinom::Polinom() {
    Monom *temp = new Monom;
    temp->next = nullptr;
    temp->prev = nullptr;
    temp->coef = 0.0;
    temp->pow = -1;
    pol = temp;
}

void Polinom::ins(double coef, int pow) {
    if (pow < 0 || pow > 999) {
        throw("Error");
    }
    Monom *ins = new Monom;
    ins->coef = coef;
    ins->pow = pow;
    Monom *temp = pol;
    if (temp->next == nullptr) {
        ins->next = nullptr;
        ins->prev = temp;
        temp->next = ins;
    }
    else {
        temp = temp->next;
        if (temp->next == nullptr) {
            if (temp->pow == pow) {
                temp->coef = temp->coef + coef;
            }
            else if (temp->pow > pow) {
                temp->next = ins;
                ins->prev = temp;
                ins->next = nullptr;
            }
            else {
                Monom *t1 = temp->prev;
                temp->prev->next = ins;
                ins->prev = t1;
                temp->prev = ins;
                ins->next = temp;
            }
        }
        else {
            bool f = true;
            while (temp->next != nullptr) {
                if (temp->pow < pow) {
                    Monom *t1 = temp->prev;
                    temp->prev->next = ins;
                    ins->prev = t1;
                    temp->prev = ins;
                    ins->next = temp;
                    f = false;
                    break;
                }
                else if (temp->pow == pow) {
                    temp->coef = temp->coef + coef;
                    break;
                }
                temp = temp->next;
            }
            if (f) {
                if (temp->pow == pow) {
                    temp->coef = temp->coef + coef;
                }
                else if (temp->pow > pow) {
                    temp->next = ins;
                    ins->prev = temp;
                    ins->next = nullptr;
                }
                else {
                    Monom *t1 = temp->prev;
                    temp->prev->next = ins;
                    ins->prev = t1;
                    temp->prev = ins;
                    ins->next = temp;
                }
            }
        }
    }
}

void Polinom::ins_at_end(double coef, int pow) {
    if (pow < 0 || pow > 999) {
        throw("Error");
    }
    Monom *temp = pol->next;
    Monom *ins = new Monom;
    ins->coef = coef;
    ins->pow = pow;
    if (temp == nullptr) {
        pol->next = ins;
        ins->prev = pol;
        ins->next = nullptr;
    }
    else {
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = ins;
        ins->prev = temp;
        ins->next = nullptr;
    }
}

void Polinom::del(double coef, int pow) {
    Monom *temp = pol;
    while (temp->next != nullptr) {
        if (temp->coef == coef && temp->pow == pow) {
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            delete temp;
        }
        temp = temp->next;
    }
    if (temp->coef == coef && temp->pow == pow) {
        temp->prev->next = temp->next;
        delete temp;
    }
}

void Polinom::del_dublicate() {
    Monom *a = pol->next;
    while (a != nullptr && a->next != nullptr) {
        Monom* b = a;
        while (b->next != nullptr) {
            if (a->pow == b->next->pow) {
                double coef = a->coef + b->next->coef;
                a->coef = coef;
                Monom *temp = b->next;
                if (temp->next == nullptr) {
                    temp->prev->next = temp->next;
                    delete temp;
                }
                else {
                    temp->next->prev = temp->prev;
                    temp->prev->next = temp->next;
                    delete temp;
                }
            }
            else {
                b = b->next;
            }
        }
        a = a->next;
    }
}

Polinom Polinom::operator*(double v) const {
    Polinom ans;
    if (v < eps) return ans;
    ans = *this;
    Monom* temp = ans.pol->next;
    while (temp != nullptr) {
        temp->coef = temp->coef * v;
        temp = temp->next;
    }
    return ans;
}

Polinom Polinom::operator+(const Polinom& p) const {
    Polinom ans;
    Monom* a = pol->next;
    Monom* b = p.pol->next;
    while (true) {
        if (a == nullptr) {
            if (b == nullptr) {
                break;
            }
            else {
                while (b != nullptr) {
                    ans.ins(b->coef, b->pow);
                    b = b->next;
                }
                break;
            }
        }
        else if (b == nullptr) {
            while (a != nullptr) {
                ans.ins(a->coef, a->pow);
                a = a->next;
            }
            break;
        }
        else {
            if (a->pow == b->pow) {
                double coef = a->coef + b->coef;
                if (coef < eps) {
                    a = a->next;
                    b = b->next;
                }
                else {
                    ans.ins(coef, a->pow);
                    a = a->next;
                    b = b->next;
                }
            }
            else if (a->pow > b->pow) {
                ans.ins(a->coef, a->pow);
                a = a->next;
            }
            else {
                ans.ins(b->coef, b->pow);
                b = b->next;
            }
        }
    }
    return ans;
}

Polinom Polinom::operator-(const Polinom &p) const {
    return *this + p*(-1.0);
}

Polinom Polinom::operator*(const Polinom &p) const {
    Polinom ans;
    Monom* a = pol->next;
    Monom* b = p.pol->next;
    while (a != nullptr) {
        Monom* temp = b;
        while (temp != nullptr) {
            int pow_x = (a->pow) / 100 + (temp->pow) / 100;
            int pow_y = ((a->pow) / 10 % 10) + ((temp->pow) / 10 % 10);
            int pow_z = (a->pow) % 10 + (temp->pow) % 10;
            if (pow_x > 9 || pow_y > 9 || pow_z > 9) throw "Error";
            int pow = pow_x * 100 + pow_y * 10 + pow_z;
            double coef = a->coef * temp->coef;
            ans.ins(coef, pow);
            temp = temp->next;
        }
        a = a->next;
    }
    ans.del_dublicate();
    return ans;
}

bool Polinom::operator==(const Polinom &p) const {
    Monom* temp = pol;
    Monom* temp1 = p.pol;
    while (temp -> next != nullptr || temp1 -> next != nullptr) {
        if (temp -> coef != temp1 -> coef) {
            return false;
        }
        if (temp -> pow != temp1 -> pow) {
            return false;
        }
    }
    if (temp -> next == nullptr && temp1 -> next == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

bool Polinom::operator!=(const Polinom &p) const {
    return !(*this == p);
}

std::ostream& operator << (std::ostream& os, const Polinom& p) {
    Monom* temp = p.pol->next;
    while (temp != nullptr) {
        int pow_x = (temp->pow) / 100;
        int pow_y = (temp->pow) / 10 % 10;
        int pow_z = (temp->pow) % 10;
        double coef = temp->coef;
        bool f = true;
        if (coef != 1) {
            f = false;
            os << coef;
        }
        if (pow_x == 1)
        {
            if (!f) os << "*x";
            else os << "x";
        }
        else if (pow_x != 0)
        {
            if (!f) os << "*x^" << pow_x;
            else os << "x^" << pow_x;
        }
        if (pow_y == 1) os << "*y";
        else if (pow_y != 0) os << "*y^" << pow_y;
        if (pow_z == 1) os << "*z";
        else if (pow_z != 0) os << "*z^" << pow_z;
        if (temp->next != nullptr) {
            os << " " << "+" << " ";
        }
        temp = temp->next;
    }
    return os;
}

std::istream& operator >> (std::istream& is, Polinom& p) {
    std::cout << "Vvedite kol-vo monomov v polinome" << "\n";
    int n;
    is >> n;
    for (int i = 0; i < n; i++) {
        std::cout << i + 1 << " " << "monom" << "\n";
        std::cout << "Vvedite koef" << "\n";
        double coef;
        is >> coef;
        if (coef < eps) {
            continue;
        }
        std::cout << "Vvedite power x" << "\n";
        int pow_x;
        is >> pow_x;
        if (pow_x < 0 || pow_x > 9) throw("Error");
        std::cout << "Vvedite power y" << "\n";
        int pow_y;
        is >> pow_y;
        if (pow_y < 0 || pow_y > 9) throw("Error");
        std::cout << "Vvedite power z" << "\n";
        int pow_z;
        is >> pow_z;
        if (pow_z < 0 || pow_z > 9) throw("Error");
        p.ins(coef, pow_x * 100 + pow_y * 10 + pow_z);
    }
    return is;
}


#endif
