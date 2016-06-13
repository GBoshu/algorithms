# 1. Two Sum

## Description
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution.

Example:
```
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

```

## Solution 1
### Analysis
Hash map comes out at the very beginning. But we need to focus on when we will  create the hash map, which impact on the performance.

### Code
```
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash_map;
        vector<int> res;

        for (int i = 0; i < nums.size(); ++i) {
            auto idx = hash_map.find(target - nums[i]);
            if (idx != hash_map.end()) {
                res.push_back(idx->second);
                res.push_back(i);
                break;
            }

            hash_map.insert(std::make_pair(nums[i], i));
        }

        return res;
    }
```



