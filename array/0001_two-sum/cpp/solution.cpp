#include <vector>
#include <algorithm>
using namespace std;

// 
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans(2);
        bool flag = false;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    ans[0] = i;
                    ans[1] = j;
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        return ans;
    }
};

// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         vector<int> ans(2);
//         sort(nums.begin(), nums.end());
//         int left = 0, right = nums.size() - 1;
//         while (left < right) {
//             int sum = nums[left] + nums[right];
//             if (sum == target) {
//                 ans[0] = left;
//                 ans[1] = right;
//                 break;
//             } else if (sum < target) {
//                 left++;
//             } else {
//                 right--;
//             }
//         }
//         return ans;
//     }
// };