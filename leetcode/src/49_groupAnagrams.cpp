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
#include <stdlib.h>

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
        return groupAnagrams(c.i1);
    }

    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>>        res;
        unordered_map<string, int>    hash_map;
        char                          sum[26];

        //cout << "hash_map.size()" << hash_map.size() << endl;
        for (auto it = strs.begin(); it != strs.end(); ++it) {
            memset(sum, 0, 26 * sizeof(char));

            for (int i = 0; i < it->size(); ++i) {
                ++sum[it->at(i) - 'a'];
            }

            string key;
            for (int i = 0; i < 26; ++i) {
                if (sum[i] != 0) {
                    key.push_back(i + 'a');
                    key.append(to_string(sum[i]));
                }
            }

            //cout << key << endl;

            if (hash_map.find(key) == hash_map.end()) {
                int value = hash_map.size();
                hash_map[key] = value;
                //cout << "value:" << hash_map[key] << endl;
            }

            if (res.size() < hash_map[key] + 1) {
                res.push_back(vector<string>());
            }
            res[hash_map[key]].push_back(*it);
            //cout << *it << endl;
        }

        return res;
    }

};
}

/*************************************************************************/

namespace second {
class Solution : public Runable {
public:
    string getName() { return "hash method"; }

    T_OUT run(CASETYPE &c) {
        return groupAnagrams(c.i1);
    }

    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, unordered_multiset<string>>    hash_map;
        vector<vector<string>> res;

        for (const auto s : strs) {
            string key(s);

            sort(key.begin(), key.end());

            hash_map[key].insert(s);
        }

        for (const auto strSet : hash_map) {
            res.push_back(vector<string>(strSet.second.begin(), strSet.second.end()));
        }

        return res;
    }

};
}

/*************************************************************************/

namespace third {
class Solution : public Runable {
public:
    string getName() { return "rb tree method"; }

    T_OUT run(CASETYPE &c) {
        return groupAnagrams(c.i1);
    }

    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, multiset<string>>    rb_map;
        vector<vector<string>> res;

        for (const auto s : strs) {
            string key(s);

            sort(key.begin(), key.end());

            rb_map[key].insert(s);
        }

        for (const auto strSet : rb_map) {
            res.push_back(vector<string>(strSet.second.begin(), strSet.second.end()));
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

        vector<vector<string>> aVec;
        vector<vector<string>> bVec;

        for (const auto ai : a) {
            aVec.push_back(ai);
            sort((aVec[aVec.size() - 1]).begin(), (aVec[aVec.size() - 1]).end());
        }

        for (const auto bi : b) {
            bVec.push_back(bi);
            sort((bVec[bVec.size() - 1]).begin(), (bVec[bVec.size() - 1]).end());
        }

        sort(aVec.begin(), aVec.end(), cmpStrVec());
        sort(bVec.begin(), bVec.end(), cmpStrVec());

        for (int i = 0; i != aVec.size(); i++) {
            for (int j = 0; j != aVec[i].size(); j++) {
                //cout << aVec[i][j] << ":" << bVec[i][j] << endl;
                if ( aVec[i][j].compare(bVec[i][j]) != 0 ) return false;
            }
        }

        return true;
    }

    struct cmpStrVec {
        bool operator() (const vector<string> &a, const vector<string> &b) {
            return a[0].compare(b[0]) > 0 ? true: false;
        }
    };


private:
    vector<Runable *> solutions;
    vector<CASETYPE *> cases;
};

/*************************************************************************/

int main() {
    UTbox utbox;

    first::Solution s1;
    utbox.addSolution(&s1);

    second::Solution s2;
    utbox.addSolution(&s2);

    third::Solution s3;
    utbox.addSolution(&s3);

    CaseType case0;
    case0.i1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
    case0.o1 = { {"ate", "tea","eat"}, {"tan","nat"}, {"bat"} };
    utbox.addCase(&case0);

    utbox.runAll();
}

