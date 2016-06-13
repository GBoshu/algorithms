/*
 *      18. 4Sum
 *
 *      tag: [hash]
 *      level: [medium]
 *      file: 18_fourSum.cpp
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

typedef vector<int> T_PARAM1;
typedef int T_PARAM2;
typedef vector<vector<int>> T_OUT;

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
namespace first {
class Solution : public Runable {
public:
    string getName() { return "my first method"; }

    T_OUT run(CASETYPE &c) {
        return fourSum(c.i1, c.i2);
    }

    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int size = static_cast<int>(nums.size());

        for (int i = 0; i < size - 3; ++i) {
            if (i != 0 && nums[i - 1] == nums[i]) continue;

            /* If we give a second thought, we will note that it exists some break condition. */
            /* If the sum of four smallest numbers is bigger than the target, we won't search any more. */
            if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break;
            /* If the sum of four biggest numbers is smaller than the target, we have to start a new round. */
            if (nums[i] + nums[size - 3] + nums[size - 2] + nums[size - 1] < target) continue;

            for (int j = i + 1; j < size - 2; ++j) {
                if (j != i + 1 && nums[j - 1] == nums[j]) continue;
                if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) break;
                if (nums[i] + nums[j] + nums[size - 2] + nums[size - 1] < target) continue;

                int sum = target - nums[i] - nums[j];
                int lo = j + 1;
                int hi = size - 1;

                while (lo < hi) {

                    if (nums[lo] + nums[hi] == sum) {
                        res.push_back(vector<int>{nums[i], nums[j], nums[lo], nums[hi]});

                        while (lo < hi && nums[lo] == nums[lo + 1]) ++lo;
                        while (lo < hi && nums[hi] == nums[hi - 1]) --hi;
                        ++lo; --hi;
                    } else if (nums[lo] + nums[hi] > sum) {
                        --hi;
                    }
                    else {
                        ++lo;
                    }
                }
            }
        }

        return res;
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
        if (a.size() != b.size()) return false;

        unordered_set<string> hash_set;

        for (auto it = a.begin(); it != a.end(); ++it) {
            hash_set.insert(vec2str(*it));
            //cout << vec2str(*it) << endl;
        }

        for (auto it = b.begin(); it != b.end(); ++it) {
            auto idx = hash_set.find(vec2str(*it));

            if (idx == hash_set.end()) return false;

            hash_set.erase(idx);
        }

        return true;
    }

    string vec2str(vector<int> &v) {
        string res;

        for (auto it = v.begin(); it != v.end(); ++it) {
            res.append(to_string(*it));
            res.append(",");
        }

        return res;
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
    CASETYPE case0;
    case0.i1 = {1, 0, -1, 0, -2, 2};
    case0.i2 = 0;
    case0.o1 = {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}};
    utbox.addCase(&case0);

    /* case define */
    CASETYPE case1;
    case1.i1 = {};
    case1.i2 = 0;
    case1.o1 = {};
    utbox.addCase(&case1);

    /* case define */
    CASETYPE case2;
    case2.i1 = {0, 0, 0, 0, 1};
    case2.i2 = 0;
    case2.o1 = {{0, 0, 0, 0}};
    utbox.addCase(&case2);

    /* case define */
    CASETYPE case3;
    case3.i1 = {0, 0, 0, 0, 1};
    case3.i2 = 1;
    case3.o1 = {{0, 0, 0, 1}};
    utbox.addCase(&case3);

    utbox.runAll();
}

