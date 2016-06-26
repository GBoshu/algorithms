# 49. Group Anagrams

## Description
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:

```
[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]

```
Note: All inputs will be in lower-case.

## Solution 1
### Analysis
"All inputs will be in lower=case" reminds me that maybe I can use hash and make sorted string as key.
I caculated the key with a 26 charactors array.
Key is combined the char and the times which is show up. For example, the key of "aab" will be "a2b1".
I'll use a hash table to store the key and the index of the result vector.

### Code
```
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>>        res;
    unordered_map<string, int>    hash_map;
    char                          sum[26];

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

        if (hash_map.find(key) == hash_map.end()) {
            int value = hash_map.size();
            hash_map[key] = value;
        }

        if (res.size() < hash_map[key] + 1) {
            res.push_back(vector<string>());
        }
        res[hash_map[key]].push_back(*it);
    }

    return res;
}
```

### Think
This is not a good method. 
Calculating key takes too much time. 
And the performance of unordered_set in this case may be not good as set.

## Solution 2
### Analysis
We will still use hash map, but the key will be calcalated by sort().

### Code

```
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
```

### Think
This is method is very straight. 
The performance is better than the first one.


## Solution 3
### Analysis
Let's try to improve the Solution 2. This time I'll try to use map.

### Code
```
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
```

### Think
Indeed, the performance is improved. But why?



