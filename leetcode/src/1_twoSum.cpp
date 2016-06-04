/*
 *      1. Two Sum
 *
 *      tag: [hash]
 *      level: [easy]
 *      file: 1_twoSum.cpp
 *      complie: g++ -std=c++11
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <tuple>
#include <cstring>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <climits>
#include <utility>

#include <time.h>

using namespace std;

typedef vector<int> T_PARAM1;
typedef int T_PARAM2;
typedef vector<int> T_OUT;

struct CaseType {
    T_PARAM1 i1;
    T_PARAM2 i2;
    T_OUT o1;
    clock_t time_span;
};
typedef struct CaseType CASETYPE;

class Runable {
public:
    virtual string getName() { return "Runable"; }
    virtual T_OUT run(CASETYPE &c) = 0;
};

/*************************************************************************/

namespace first {
class Solution : public Runable {
public:
    string getName() { return "my stupid method"; }

    T_OUT run(CASETYPE &c) {
        return twoSum(c.i1, c.i2);
    }

    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash_map;
        vector<int> res;

        for (int i = 0; i < nums.size(); ++i) {
            hash_map.insert(std::make_pair(nums[i], i));
        }

        /* no need to search for the last one */
        for (int i = 0; i < nums.size() - 1; ++i) {
            auto idx = hash_map.find(target - nums[i]);
            /* find match */
            if (idx != hash_map.end()) {
                /* skip the same one */
                if (i == idx->second) continue;

                if (i < idx->second) {
                    res.push_back(i);
                    res.push_back(idx->second);
                } else {
                    res.push_back(idx->second);
                    res.push_back(i);
                }
                break;
            }
        }

        return res;
    }
};
}

/*************************************************************************/
namespace second {
class Solution : public Runable {
public:
    string getName() { return "hash method"; }

    T_OUT run(CASETYPE &c) {
        return twoSum(c.i1, c.i2);
    }

    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash_map;
        vector<int> res;

        for (int i = 0; i < nums.size(); ++i) {
            auto idx = hash_map.find(target - nums[i]);
            if (idx != hash_map.end()) {
                res.push_back(idx->second);
                res.push_back(i);
                break;
            }

            hash_map.insert(std::make_pair(nums[i], i));
        }

        return res;
    }
};
}
/*************************************************************************/

class UTbox {
public:
    bool runCase(Runable &s, CASETYPE &c) {
        T_OUT &expect = c.o1;
        clock_t start, end;
        start = clock();

        T_OUT out = s.run(c);

        end = clock();
        c.time_span = end - start;

        return isSame(out, expect);
    }

    void addSolution(Runable *item) {
        solutions.push_back(item);
    }

    void addCase(CASETYPE *cs) {
        cases.push_back(cs);
    }

    void runAll() {
        for (auto s : solutions) {
            cout << "UT for " << s->getName() << endl;
            cout << "--------------------------" << endl;
            for (int i = 0; i != static_cast<int>(cases.size()); ++i) {

                if (runCase(*s, *(cases[i]))) {
                    cout << "case " << i << " passed: " << (cases[i])->time_span << endl;
                } else {
                    cout << "case " << i << " failed" << endl;
                }
            }
            cout << "--------------------------" << endl;
        }
    }

private:
    bool isSame(T_OUT &a, T_OUT &b) {
        return (a[0] == b[0] && a[1] == b[1]);
    }

private:
    vector<Runable *> solutions;
    vector<CASETYPE *> cases;
};

/*************************************************************************/

int main() {
    UTbox utbox;

    first::Solution s1;
    //utbox.addSolution(&s1);

    second::Solution s2;
    utbox.addSolution(&s2);

    /* case define */
    CASETYPE case1;
    case1.i1 = {2, 7, 11, 5};
    case1.i2 = 9;
    case1.o1 = {0, 1};
    utbox.addCase(&case1);

    CASETYPE case2;
    case2.i1 = {3, 2, 4};
    case2.i2 = 6;
    case2.o1 = {1, 2};
    utbox.addCase(&case2);

    CASETYPE case3;
    case3.i1 = {0, 2, 4, 0};
    case3.i2 = 0;
    case3.o1 = {0, 3};
    utbox.addCase(&case3);

    utbox.runAll();
}

