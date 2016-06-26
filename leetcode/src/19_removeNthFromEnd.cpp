/*
 *      19. Remove Nth Node From End of List
 *
 *      tag: [list]
 *      level: [easy]
 *      file: 19_removeNthFromEnd.cpp
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
typedef int T_PARAM2;
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
    string getName() { return "my first method(Two pointer)"; }

    T_OUT run(CASETYPE &c) {
        return removeNthFromEnd(UTbox::createList(c.i1), c.i2);
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == NULL) return head;

        ListNode *first, *second;
        second = first = head;

        for (; n > 0; n--) {
            first = first->next;
        }

        if (first == NULL) return head->next;

        while (first->next) {
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;

        return head;
    }
};
}

/*************************************************************************/

namespace second {
class Solution : public Runable {
public:
    string getName() { return "good method(Two pointer)"; }

    T_OUT run(CASETYPE &c) {
        return removeNthFromEnd(UTbox::createList(c.i1), c.i2);
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == NULL) return head;

        ListNode *first, **second;
        first = head;
        second = &head;

        /* Given n will always be valid. */
        for (; n-- > 0; ) {
            first = first->next;
        }

        while (first) {
            first = first->next;
            second = &((*second)->next);
        }

        MYDEBUG("Before: " << (*second)->val);
        *second = (*second)->next;

        return head;
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

    /* case define */
    CASETYPE case1;
    case1.i1 = vector<int>({1, 2, 3, 4, 5});
    case1.i2 = 2;
    case1.o1 = UTbox::createList(vector<int>({1, 2, 3, 5}));
    utbox.addCase(&case1);

    CASETYPE case2;
    case2.i1 = vector<int>({1, 2});
    case2.i2 = 1;
    case2.o1 = UTbox::createList(vector<int>({1}));
    utbox.addCase(&case2);

    CASETYPE case3;
    case3.i1 = vector<int>({1});
    case3.i2 = 1;
    case3.o1 = UTbox::createList(vector<int>({}));
    utbox.addCase(&case3);

    utbox.runAll();
}

