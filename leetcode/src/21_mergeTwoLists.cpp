/*
 *      21. Merge Two Sorted Lists
 *
 *      tag: [list]
 *      level: [easy]
 *      file: 21_mergeTwoLists.cpp
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
        return mergeTwoLists(UTbox::createList(c.i1), UTbox::createList(c.i2));
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode *l2) {
        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;

        if (l1->val > l2->val) return mergeTwoLists(l2, l1);

        ListNode *head = l1;
        ListNode *ptr = head;
        l1 = l1->next;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                ptr->next = l1;
                l1 = l1->next;
            } else {
                ptr->next = l2;
                l2 = l2->next;
            }
            ptr = ptr->next;
        }

        ptr->next = l1 == NULL? l2 : l1;

        return head;
    }
};
}

/*************************************************************************/

namespace second {
class Solution : public Runable {
public:
    string getName() { return "my second method (recursive)"; }

    T_OUT run(CASETYPE &c) {
        return mergeTwoLists(UTbox::createList(c.i1), UTbox::createList(c.i2));
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode *l2) {
        ListNode *head;

        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;

        if (l1->val < l2->val) {
            head = l1;
            l1 = l1->next;
        } else {
            head = l2;
            l2 = l2->next;
        }

        head->next = mergeTwoLists(l1, l2);

        return head;

    }
};
}

/*************************************************************************/

namespace third {
class Solution : public Runable {
public:
    string getName() { return "third method (recursive)"; }

    T_OUT run(CASETYPE &c) {
        return mergeTwoLists(UTbox::createList(c.i1), UTbox::createList(c.i2));
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode *l2) {
        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;

        if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
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

    third::Solution s3;
    utbox.addSolution(&s3);

    /* case define */
    CASETYPE case1;
    case1.i1 = vector<int>({1, 3, 5});
    case1.i2 = vector<int>({2, 4});
    case1.o1 = UTbox::createList(vector<int>({1, 2, 3, 4, 5}));
    utbox.addCase(&case1);

    CASETYPE case2;
    case2.i1 = vector<int>({1, 2, 3});
    case2.i2 = vector<int>({5, 6});
    case2.o1 = UTbox::createList(vector<int>({1, 2, 3, 5, 6}));
    utbox.addCase(&case2);

    CASETYPE case3;
    case3.i1 = vector<int>({});
    case3.i2 = vector<int>({5, 6});
    case3.o1 = UTbox::createList(vector<int>({5, 6}));
    utbox.addCase(&case3);

    CASETYPE case4;
    case4.i1 = vector<int>({});
    case4.i2 = vector<int>({});
    case4.o1 = UTbox::createList(vector<int>({}));
    utbox.addCase(&case4);

    CASETYPE case5;
    case5.i1 = vector<int>({1});
    case5.i2 = vector<int>({2});
    case5.o1 = UTbox::createList(vector<int>({1, 2}));
    utbox.addCase(&case5);

    utbox.runAll();
}

