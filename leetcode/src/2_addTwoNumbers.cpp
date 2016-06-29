/*
 *      2. addTwoNumbers
 *
 *      tag: [list]
 *      level: [medium]
 *      file: 2_addTwoNumbers.cpp
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

/*
 * Suppose the first node is a valid one.
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

typedef vector<int> T_PARAM1;
typedef vector<int> T_PARAM2;
typedef ListNode * T_OUT;

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

    static ListNode *createList(const vector<int> &values) {
        ListNode *head = NULL;

        for (auto it = values.rbegin(); it != values.rend(); ++it) {
            ListNode *ptr = new ListNode(*it);
            ptr->next = head;
            head = ptr;
        }

        return head;
    }

private:
    bool isSame(T_OUT &a, T_OUT &b) {
        ListNode *ptrA, *ptrB;
        ptrA = a;
        ptrB = b;

        while (ptrA && ptrB) {
            MYDEBUG("isSame "<< ptrA->val << ":" << ptrB->val);
            if (ptrA->val != ptrB->val) return false;
            ptrA = ptrA->next;
            ptrB = ptrB->next;
        }

        if (ptrA != ptrB) return false;
        
        return true;
    }

private:
    vector<Runable *> solutions;
    vector<CASETYPE *> cases;
};

/*************************************************************************/

namespace first {
class Solution : public Runable {
public:
    string getName() { return "my first method (iterative)"; }

    T_OUT run(CASETYPE &c) {
        return addTwoNumbers(UTbox::createList(c.i1), UTbox::createList(c.i2));
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode *l2) {
        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;

        ListNode *head = NULL;
        ListNode **ptr = &head;

        int high = 0;
        while (l1 || l2 || high) {
            int v1 = l1 != NULL? l1->val: 0;
            int v2 = l2 != NULL? l2->val: 0;
            int low = (v1 + v2 + high) % 10;
            high = (v1 + v2 + high) / 10;

            *ptr = new ListNode(low);
            ptr = &((*ptr)->next);

            l1 = l1 == NULL? NULL : l1->next;
            l2 = l2 == NULL? NULL : l2->next;
        }

        return head;
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
    case1.i1 = vector<int>({2, 4, 3});
    case1.i2 = vector<int>({5, 6, 4});
    case1.o1 = UTbox::createList(vector<int>({7, 0, 8}));
    utbox.addCase(&case1);

    CASETYPE case2;
    case2.i1 = vector<int>({2, 4, 3});
    case2.i2 = vector<int>({});
    case2.o1 = UTbox::createList(vector<int>({2, 4, 3}));
    utbox.addCase(&case2);

    CASETYPE case3;
    case3.i1 = vector<int>({2, 4, 3});
    case3.i2 = vector<int>({9, 6});
    case3.o1 = UTbox::createList(vector<int>({1, 1, 4}));
    utbox.addCase(&case3);

    CASETYPE case4;
    case4.i1 = vector<int>({2, 4});
    case4.i2 = vector<int>({9, 6});
    case4.o1 = UTbox::createList(vector<int>({1, 1, 1}));
    utbox.addCase(&case4);

    utbox.runAll();
}

