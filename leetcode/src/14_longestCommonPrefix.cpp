/*
 *      14.Longest Common Prefix 
 *
 *      tag: [string]
 *      level: [easy]
 *      file: 14_longestCommonPrefix.cpp
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

typedef vector<string> T_PARAM1;
typedef int T_PARAM2;
typedef string T_OUT;

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
        return longestCommonPrefix(c.i1);
    }

    string longestCommonPrefix(vector<string>& strs) {
        string comPrefix("");
        bool matchFlag = true;
        int i = 0;

        while (matchFlag) {
            char target = '\0';
            for (auto str : strs) {
                if (i >= str.size()) {
                    matchFlag = false;
                    break;
                }

                if (target == '\0') {
                    target = str[i];
                } else {
                    //MYDEBUG(target << ":" << str[i]);
                    if (target != str[i]) {
                        matchFlag = false;
                        break;
                    }
                }
            }

            if (target == '\0') break;

            if (matchFlag) {
                //MYDEBUG(target);
                comPrefix.push_back(target);
                ++i;
            }
        }

        return comPrefix;
    }
};
}

/*************************************************************************/

int main() {
    UTbox utbox;

    first::Solution s1;
    utbox.addSolution(&s1);

    /* case define */
    CASETYPE case1;
    vector<string> str1({"abc", "abd"});
    case1.i1 = str1;
    case1.o1 = "ab";
    utbox.addCase(&case1);

    CASETYPE case2;
    vector<string> str2({});
    case2.i1 = str2;
    case2.o1 = "";
    utbox.addCase(&case2);

    utbox.runAll();
}

