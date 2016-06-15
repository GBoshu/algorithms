/*
 *      49. Group Anagrams
 *
 *      tag: [hash]
 *      level: [medium]
 *      file: 49_groupAnagrams.cpp
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
typedef vector<vector<string>> T_OUT;

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
        return fourSum(c.i1, c.i2);
    }

    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<unordered_set<string>> tmpRes;
        vector<vector<string>>        res;
        unordered_map<string>         hash_map;
        char                          sum[26];

        for (auto it = strs.begin(); it != strs.end(); ++it) {
            memset(sum, 0, 26 * sizeof(char));

            for (int i = 0; i < it->size(); ++i) {
                ++sum[it[i] - 'a'];
            }

            string key;
            for (int i = 0; i < 26; ++i) {
                if (sum[i] != 0) {
                    key.push_back(i + 'a');
                    key.append(itoa(sum[i]));
                }
            }

            cout << key << endl;

            if (hash_map.find(key) == hash_map.end()) {
                hash_map[key] = hash_map.size();
            }

            if (tmpRes.size() < hash_map[key] + 1) {
                tmpRes.push_back(unordered_set<sting>());
            }
            tmpRes[hash_map[key]].insert(*it);
        }

        for (auto it = tmpRes.begin(); it != tmpRes.end(); ++it) {
            res.push_back(vector<string>(it->begin(), it->end()));
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



    utbox.runAll();
}

