/*
 *      15. 3Sum
 *
 *      tag: [hash]
 *      level: [medium]
 *      file: 15_threeSum.cpp
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
typedef vector<vector<int>> T_OUT;

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
    string getName() { return "my first method"; }

    T_OUT run(CASETYPE &c) {
        return threeSum(c.i1);
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        unordered_map<int, int> hash_map;
        unordered_set<string> uniq_result;
        vector<vector<int>> res;

        for (int i = 0; i < nums.size(); ++i) {
            hash_map.insert(std::make_pair(nums[i], i));
        }

        for (int i = 0; i < nums.size() - 1; ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                int target = -(nums[i] + nums[j]);
                auto idx = hash_map.find(target);

                /* match */
                if (idx != hash_map.end()) {
                    /* skip the existing index */
                    if (idx->second == i || idx->second == j) {
                        continue;
                    }
                    /* now I need to handle duplicate result */
                    vector<int> tmp_result = {nums[i], nums[j], target};
                    /* this is how to sort three int */
                    if (tmp_result[0] > tmp_result[1]) {
                        tmp_result[0] = tmp_result[0] ^ tmp_result[1];
                        tmp_result[1] = tmp_result[0] ^ tmp_result[1];
                        tmp_result[0] = tmp_result[0] ^ tmp_result[1];
                    }
                    if (tmp_result[1] > tmp_result[2]) {
                        tmp_result[1] = tmp_result[1] ^ tmp_result[2];
                        tmp_result[2] = tmp_result[1] ^ tmp_result[2];
                        tmp_result[1] = tmp_result[1] ^ tmp_result[2];
                    }
                    if (tmp_result[0] > tmp_result[1]) {
                        tmp_result[0] = tmp_result[0] ^ tmp_result[1];
                        tmp_result[1] = tmp_result[0] ^ tmp_result[1];
                        tmp_result[0] = tmp_result[0] ^ tmp_result[1];
                    }
                    
                    string strRes; 
                    strRes.append(to_string(tmp_result[0]));
                    strRes.append(",");
                    strRes.append(to_string(tmp_result[1]));
                    strRes.append(",");
                    strRes.append(to_string(tmp_result[2]));

                    if (uniq_result.find(strRes) == uniq_result.end()) {
                        cout << strRes << endl;
                        uniq_result.insert(strRes);
                        res.push_back(tmp_result);
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
    CASETYPE case1;
    case1.i1 = {-1, 0, 1, 2, -1, -4};
    case1.o1 = {{-1, 0, 1}, {-1, -1, 2}};
    utbox.addCase(&case1);

    utbox.runAll();
}

