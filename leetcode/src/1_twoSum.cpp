/*
 *      1. Two Sum
 *
 *      tag: [hash]
 *      level: [easy]
 *      file: 1_twoSum.cpp
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

typedef TreeNode * T_PARAM1;
typedef bool T_OUT;

struct CaseType {
    T_PARAM1 i1;
    T_PARAM1 i2;
    T_OUT o1;
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
    string getName() { return "In-order method"; }

    T_OUT run(CASETYPE &c) {
        return isSameTree(c.i1, c.i2);
    }

    bool isSameTree(TreeNode* p, TreeNode* q) {
    }
};
}

/*************************************************************************/

class UTbox {
public:
    bool runCase(Runable &s, CASETYPE &c) {
        T_OUT &expect = c.o1;

        T_OUT out = s.run(c);

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
                clock_t start, end;
                start = clock();

                if (runCase(*s, *(cases[i]))) {
                    end = clock();
                    cout << "case " << i << " passed: " << end - start << endl;
                } else {
                    cout << "case " << i << " failed" << endl;
                }
            }
            cout << "--------------------------" << endl;
        }
    }

private:
    bool isSame(T_OUT &a, T_OUT &b) {
        //cout << a << " " << b << endl;
        return a == b;
    }

private:
    vector<Runable *> solutions;
    vector<CASETYPE *> cases;
};

/*************************************************************************/

int main() {
    UTbox utbox;

    first::Solution s1;
    utbox.addSolution(&s1);

    /* case define */

}

