/*
 *      347. Top K Frequent Elements
 *
 *      tag: [heap] [hash]
 *      level: [medium]
 *      file: 347_topKFrequent.cpp
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
    string getName() { return "using minheap"; }

    T_OUT run(CASETYPE &c) {
    }

private:
    struct bigger{
        bool operator()(pair<int, int> &one, pair<int, int>two){
            return one.second > two.second;
        }
    };

public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        /* Use unordered_map and priority_queue(minheap) solution.
         *
         * Use unordered_map to avoid red-black hash implement, which takes almost O(n*lgn).
         * We build a min heap with size k, so the time complexity is O(nlgk).
         */
        unordered_map<int, int> num_count;
        for(const auto &n: nums){
            num_count[n] += 1;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, bigger> frequent_heap;
        // Build the min-heap with size k.
        for(auto it = num_count.begin(); it != num_count.end(); it++){
            if(frequent_heap.size() < k){
                frequent_heap.push(*it);
            }
            else if(it->second >= frequent_heap.top().second){
                frequent_heap.pop();
                frequent_heap.push(*it);
            }
        }

        vector<int> ans;
        while(!frequent_heap.empty()){
            auto top = frequent_heap.top();
            frequent_heap.pop();
            ans.push_back(top.first);
        }
        return ans;
    }

};
}

/*************************************************************************/

namespace second {
class Solution : public Runable {
public:
    string getName() { return "based on bucket sort"; }

    T_OUT run(CASETYPE &c) {
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        for (int num : nums)
            ++m[num];
        
        vector<vector<int>> buckets(nums.size() + 1); 
        for (auto p : m)
            buckets[p.second].push_back(p.first);
        
        vector<int> ans;
        for (int i = buckets.size() - 1; i >= 0 && ans.size() < k; --i) {
            for (int num : buckets[i]) {
                ans.push_back(num);
                if (ans.size() == k)
                    break;
            }
        }
        return ans;
    }

};
}

/*************************************************************************/

namespace third {

class Solution : public Runable {

public:   
    string getName() { return "based on quickselect"; }

    T_OUT run(CASETYPE &c) {}

    vector<int> topKFrequent(vector<int>& nums, int k) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        unordered_map<int, int> cnt;
        for (auto num : nums) cnt[num]++;
        for (auto kv : cnt) {
            pq.push({kv.second, kv.first});
            while (pq.size() > k) pq.pop();
        }
        vector<int> res;
        while (!pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
        }
        return res;
    }
    
};

}


/*************************************************************************/
/* testcase
[]
[]

[1, 2, null, 3]
[1, 2,  3]

[2,1,3]
[-2147483648]
*/
/*************************************************************************/
int main() {
    UTbox utbox;

    utbox.runAll();
}

