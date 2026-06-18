#include <vector>
#include <iostream>
using namespace std;

// ==================================================
// Brute force (O(n^2))
// ==================================================
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }
};
// ==================================================

int main() {
    Solution solution;
    vector<int> nums = {1, 2, 5, 4, 3, 8, 6, 7};
    int target = 15;
    vector<int> ans = solution.twoSum(nums, target);
    cout << ans[0] << " " << ans[1] << endl;
    return 0;
}