/*
 *      98. Validate Binary Search Tree
 *
 *      tag: [tree]
 *      level: [medium]
 *      file: 98_isValidBST.cpp
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

    bool isValidBST(TreeNode* root) {
    	if (!root) return true;

    	TreeNode *p = root;
    	long pre = LONG_MIN; // don't use INT_MIN, it will cause bug
    	stack<TreeNode *> tStack;

    	while (p || !tStack.empty()) {
    		if (p) {
    			tStack.push(p);
    			p = p->left;
    		} else {
    			if (tStack.top()->val <= pre) return false;
    			pre = tStack.top()->val;
    			p = tStack.top()->right;
    			tStack.pop();
    		}
    	}

    	return true;
    }

};
}

/*************************************************************************/

namespace second {
class Solution : public Runable {
public:
    string getName() { return "my second method"; }

    T_OUT run(CASETYPE &c) {
    }

};
}


/*************************************************************************/
/* testcase
[1, 1]
[1,2,3]
[2,1,3]
[-2147483648]
*/
/*************************************************************************/
int main() {
    UTbox utbox;

    utbox.runAll();
}

