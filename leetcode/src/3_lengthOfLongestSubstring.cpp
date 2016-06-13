/*
 *      3. Longest Substring Without Repeating Characters
 *
 *      tag: [hash]
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

#include <time.h>

using namespace std;

typedef string T_PARAM1;
typedef int T_OUT;

struct CaseType {
    T_PARAM1 i1;
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
    string getName() { return "my hash method"; }

    T_OUT run(CASETYPE &c) {
        return lengthOfLongestSubstring(c.i1);
    }

    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> hash_map;
        int size = s.size();

        if (size < 2) return size;

        int start = 0;
        int end   = start + 1;
        int max   = 0;

        hash_map[s[start]] = start;
        while (end < size) {
            auto idx = hash_map.find(s[end]);
            if (idx == hash_map.end()) {
                hash_map[s[end]] = end;
            } else {
                /* This condition is not duplicate char, so we just update the index. */
                if (idx->second < start) {
                    idx->second = end;
                } else {
                    max = end - start > max? end - start: max;
                    start = idx->second + 1;
                    idx->second = end;
                }
            }
            ++end;
        }

        /* please don't forget this situaion */
        if (end >= size) max = size - start > max ? size - start: max;

        return max;
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
    case5.i1 = "au";
    case5.o1 = 2;
    utbox.addCase(&case5);

    utbox.runAll();
}

