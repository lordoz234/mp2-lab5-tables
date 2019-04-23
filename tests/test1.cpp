#include <gtest/gtest.h>
#include "../../pch/include/pch.h"
#include <random>

TEST(test1, tr) {
    sorted_table a;
}
std::random_device rd;
std::mt19937 gen(rd());

class sorted_table_test : public testing::TestWithParam<int> {
    public:
        sorted_table_test() {
            value = GetParam();
        }

        void test_sorted() {
            auto random_string = [&](int k){
                std::uniform_int_distribution<> dis(1, 26);
                std::string s;
                for (int i = 0; i < k; i++) {
                    char m = 'a' + dis(gen);
                    s += m;
                }
                return s;
            };
            auto generate_polinom = [&] () {
                std::uniform_int_distribution<> dis1(100, 999);
                Polinom gener;
                gener.ins(1.0, dis1(gen));
                return gener;
            };
            sorted_table a;
            for (int i = 0; i < value; i++) {
                a.inserts(random_string(i + 1), generate_polinom());
            }
            int s_size = a.getsize();
            ASSERT_EQ(value, s_size);
        }
    private:
        int value;
};

class unsorted_table_test : public testing::TestWithParam<int> {
    public:
        unsorted_table_test() {
            value = GetParam();
        }

        void test_unsorted() {
            auto random_string = [&](int k){
                std::uniform_int_distribution<> dis(1, 26);
                std::string s;
                for (int i = 0; i < k; i++) {
                    char m = 'a' + dis(gen);
                    s += m;
                }
                return s;
            };
            auto generate_polinom = [&] () {
                std::uniform_int_distribution<> dis1(100, 999);
                Polinom gener;
                gener.ins(1.0, dis1(gen));
                return gener;
            };
            unsorted_table a;
            for (int i = 0; i < value; i++) {
                a.inserts(random_string(i + 1), generate_polinom());
            }
            int s_size = a.getsize();
            ASSERT_EQ(value, s_size);
        }
    private:
        int value;
};

class hash_table_test : public testing::TestWithParam<int> {
    public:
        hash_table_test() {
            value = GetParam();
        }

        void test_hash() {
            auto random_string = [&](int k){
                std::uniform_int_distribution<> dis(1, 26);
                std::string s;
                for (int i = 0; i < k; i++) {
                    char m = 'a' + dis(gen);
                    s += m;
                }
                return s;
            };
            auto generate_polinom = [&] () {
                std::uniform_int_distribution<> dis1(100, 999);
                Polinom gener;
                gener.ins(1.0, dis1(gen));
                return gener;
            };
            hash_table a(value + 1);
            for (int i = 0; i < value; i++) {
                std::string s = random_string(i + 1);
                a.inserts(s, generate_polinom());
            }
            int s_size = a.getsize();
        }
    private:
        int value;
};

std::vector <int> generate(int start, int end) {
    std::vector <int> res;
    for (int i = 0; i < 30; i++) {  // upper bound was equal to 10
        res.push_back(std::uniform_int_distribution<int>(start, end)
                            (gen));
    }
    return res;
}

std::vector <int> wash = generate(0, 50);

TEST_P(sorted_table_test, first) {
    test_sorted();
}

TEST_P(unsorted_table_test, first) {
    test_unsorted();
}

TEST_P(hash_table_test, first) {
    test_hash();
}


INSTANTIATE_TEST_SUITE_P(sorted_test, sorted_table_test,
                    testing::ValuesIn(wash));


INSTANTIATE_TEST_SUITE_P(unsorted_test, unsorted_table_test,
                    testing::ValuesIn(wash));

INSTANTIATE_TEST_SUITE_P(hash_test, hash_table_test,
                    testing::ValuesIn(wash));




