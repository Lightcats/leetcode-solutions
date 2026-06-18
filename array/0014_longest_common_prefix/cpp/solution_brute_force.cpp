#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int max_str_len = 0;
        for (const auto& str : strs) {
            max_str_len = max(max_str_len, (int)str.size());
        }
        int common_len = 0;
        bool flag = true;
        while (flag) {
            for (const auto& str : strs) {
                if (str.size() < common_len || str[common_len] != strs[0][common_len]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                common_len++;
            }
        }
        return strs[0].substr(0, common_len);
    }
};