/*
 *      110. Balanced Binary Tree
 *
 *      tag: [tree]
 *      level: [easy]
 *      file: 110_isBalanced.cpp
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
    }

    bool helper(TreeNode *root, int *depth) {
        if (root == NULL) return true;
        int ld = 0;
        int rd = 0;

        if (!helper(root->left, &ld)) return false;
        if (!helper(root->right, &rd)) return false;

        if (abs(ld - rd) > 1) return false;

        *depth = max(ld, rd) + 1;

        return true;
    }

    bool isBalanced(TreeNode* root) {
        int depth = 0;
        return helper(root, &depth);
    }
};
}

/*************************************************************************/

namespace second {
class Solution : public Runable {
public:
    string getName() { return "most voted method"; }

    T_OUT run(CASETYPE &c) {
    }


};
}


/*************************************************************************/
/* testcase
[]
[1, 2]
[1, 6, 2, null, null, 4, 5]
[1, null, 2,  4, 5]
*/
/*************************************************************************/
int main() {
    UTbox utbox;

    utbox.runAll();
}

