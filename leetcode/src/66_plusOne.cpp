/*
 *      66. Plus One
 *
 *      tag: [array]
 *      level: [easy]
 *      file: 66_plusOne.cpp
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
#include <map>

#include <time.h>

using namespace std;

typedef string T_PARAM1;
typedef int T_PARAM2;
typedef vector<string> T_OUT;

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

#ifdef DEBUG
#define MYDEBUG(x) do { std::cerr << x << endl; } while (0)
#else
#define MYDEBUG(x)
#endif

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
        return a == b;
    }

private:
    vector<Runable *> solutions;
    vector<CASETYPE *> cases;
};

/*************************************************************************/

namespace first {
class Solution : public Runable {
public:
    string getName() { return "my first method"; }

    T_OUT run(CASETYPE &c) {
        return plusOne(c.i1);
    }

    vector<int> plusOne(vector<int>& digits) {
        if (digits.empty()) return digits;

        int     i = digits.size() - 1;
        int carry = 1;

        for (; i >= 0 && carry != 0; --i) {
            int val = (digits[i] + carry) % 10;
            carry = (digits[i] + carry) / 10;
            digits[i] = val;
        }

        if (i < 0 && carry != 0) {
            digits.insert(digits.begin(), carry);
        }

        return digits;
    }
};
}

/*************************************************************************/

namespace second {
class Solution : public Runable {
public:
    string getName() { return "most voted method"; }

    T_OUT run(CASETYPE &c) {
        return plusOne(c.i1);
    }

    vector<int> plusOne(vector<int>& digits) {
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] == 9) {
                digits[i] = 0;
            } else {
                digits[i]++;
                return digits;
            }
        }

        /* add new element */
        digits[0] = 1;
        digits.push_back(0);
        
        return digits;
    }
};
}

/*************************************************************************/
/* testcase
[9]
*/
/*************************************************************************/
int main() {
    UTbox utbox;

    utbox.runAll();
}

