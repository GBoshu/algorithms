/*
 *      215. Kth Largest Element in an Array
 *
 *      tag: [heep] [divide and conquer]
 *      level: [medium]
 *      file: 215_findKthLargest.cpp
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
    string getName() { return "using sort"; }

    T_OUT run(CASETYPE &c) {
    }

    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        return nums[k - 1];
    }   

};
}

/*************************************************************************/

namespace second {
class Solution : public Runable {
public:
    string getName() { return "based on quickselect"; }

    T_OUT run(CASETYPE &c) {
    }

    int partition(vector<int>& nums, int left, int right) {
        int pivot = nums[left];
        int l = left + 1, r = right;
        while (l <= r) {
            if (nums[l] < pivot && nums[r] > pivot)
                swap(nums[l++], nums[r--]);
            if (nums[l] >= pivot) l++; 
            if (nums[r] <= pivot) r--;
        }
        swap(nums[left], nums[r]);
        return r;
    }
    
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        while (true) {
            int pos = partition(nums, left, right);
            if (pos == k - 1) return nums[pos];
            if (pos > k - 1) right = pos - 1;
            else left = pos + 1;
        }
    }

};
}

/*************************************************************************/

namespace third {

class Solution : public Runable {

public:   
    string getName() { return "based on maxheap"; }

    T_OUT run(CASETYPE &c) {}

    inline int left(int idx) {
        return (idx << 1) + 1;
    }

    inline int right(int idx) {
        return (idx << 1) + 2;
    }

    void max_heapify(vector<int>& nums, int idx) {
        int largest = idx;
        int l = left(idx), r = right(idx);
        if (l < heap_size && nums[l] > nums[largest]) largest = l;
        if (r < heap_size && nums[r] > nums[largest]) largest = r;
        if (largest != idx) {
            swap(nums[idx], nums[largest]);
            max_heapify(nums, largest);
        }
    }

    void build_max_heap(vector<int>& nums) {
        heap_size = nums.size();
        for (int i = (heap_size >> 1) - 1; i >= 0; i--)
            max_heapify(nums, i);
    }

    int findKthLargest(vector<int>& nums, int k) {
        build_max_heap(nums);
        for (int i = 0; i < k; i++) {
            swap(nums[0], nums[heap_size - 1]);
            heap_size--;
            max_heapify(nums, 0);
        }
        return nums[heap_size];
    }

private:
    int heap_size;
}

}

/*************************************************************************/
namespace fourth {

class Solution : public Runable {

public:   
    string getName() { return "based on priority_queue"; }

    T_OUT run(CASETYPE &c) {}

    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int> > pq;
        
        for(int i = 0; i < nums.size(); i++)
        {
            if(pq.size() == k)
            {
                int x = pq.top();
                if(nums[i] > x)
                {
                    pq.pop();
                    pq.push(nums[i]);
                }
            }
            else 
            {
                pq.push(nums[i]);
            }
            
        }
        return pq.top();
    }
};
}

/*************************************************************************/

namespace fifth {

class Solution : public Runable {

public:   
    string getName() { return "based on quicksort"; }

    T_OUT run(CASETYPE &c) {}

    int partition(vector<int>& nums, int left, int right) {
        int i, j;

        i = left;
        j = right  + 1;

        while (1) {
            while (nums[++i] < nums[left] && i < right);
            while (nums[--j] > nums[left] && j > left);

            if (i >= j) break;
            swap(&nums[i], &nums[j]);
        }

        swap(&nums[left], &nums[j]);
        return j;
    }
    
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        while (true) {
            int pos = partition(nums, left, right);
            if (pos == k - 1) return nums[pos];
            if (pos > k - 1) right = pos - 1;
            else left = pos + 1;
        }
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

