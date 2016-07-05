/*
 *      3. Longest Substring Without Repeating Characters
 *
 *      tag: [string]
 *      level: [medium]
 *      file: 3_lengthOfLongestSubstring.cpp
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
typedef int T_OUT;

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
        return lengthOfLongestSubstring(c.i1);
    }

    int lengthOfLongestSubstring(string s) {
        int beginning = -1;
        int maxLen = 0;
        map<char, int> charTable;

        int i = 0;
        for (; i < s.size(); i++) {
            auto idx = charTable.find(s[i]);
            if (idx != charTable.end() && idx->second >= beginning) {
                beginning = idx->second;
            }
            charTable[s[i]] = i;
            maxLen = maxLen < i - beginning? i - beginning: maxLen;
        }

        return maxLen;
    }
};
}

/*************************************************************************/

namespace second {
class Solution : public Runable {
public:
    string getName() { return "my second method"; }

    T_OUT run(CASETYPE &c) {
        return lengthOfLongestSubstring(c.i1);
    }

    int lengthOfLongestSubstring(string s) {
        int beginning = -1;
        int maxLen = 0;
        unordered_map<char, int> charTable;

        int i = 0;
        for (; i < s.size(); i++) {
            auto idx = charTable.find(s[i]);
            if (idx != charTable.end() && idx->second >= beginning) {
                beginning = idx->second;
            }
            charTable[s[i]] = i;
            maxLen = maxLen < i - beginning? i - beginning: maxLen;
        }

        return maxLen;
    }
};
}

/*************************************************************************/

namespace third {
class Solution : public Runable {
public:
    string getName() { return "my third method"; }

    T_OUT run(CASETYPE &c) {
        return lengthOfLongestSubstring(c.i1);
    }

    int lengthOfLongestSubstring(string s) {
        int beginning = -1;
        int maxLen = 0;
        int charTable[256];

        memset(charTable, -1, sizeof(charTable));

        int i = 0;
        for (; i < s.size(); i++) {
            int c = static_cast<int>(s[i]);
            if (charTable[c] != -1 && charTable[c] >= beginning) {
                beginning = charTable[c];
            }
            charTable[c] = i;
            maxLen = maxLen < i - beginning? i - beginning: maxLen;
        }

        return maxLen;
    }
};
}

/*************************************************************************/

int main() {
    UTbox utbox;

    first::Solution s1;
    utbox.addSolution(&s1);

    second::Solution s2;
    utbox.addSolution(&s2);

    second::Solution s3;
    utbox.addSolution(&s3);

    /* case define */
    CASETYPE case1;
    case1.i1 = "abcabcbb";
    case1.o1 = 3;
    utbox.addCase(&case1);

    CASETYPE case2;
    case2.i1 = "bbbbb";
    case2.o1 = 1;
    utbox.addCase(&case2);

    CASETYPE case3;
    case3.i1 = "pwwkew";
    case3.o1 = 3;
    utbox.addCase(&case3);

    CASETYPE case4;
    case4.i1 = "";
    case4.o1 = 0;
    utbox.addCase(&case4);

    CASETYPE case5;
    case5.i1 = "c";
    case5.o1 = 1;
    utbox.addCase(&case5);

    utbox.runAll();
}

