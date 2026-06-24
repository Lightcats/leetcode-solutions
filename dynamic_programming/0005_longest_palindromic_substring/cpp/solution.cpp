#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        int ans_i = -1, ans_len = 0;
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (i == j || s[i] == s[j] && (j - i == 1 || dp[i+1][j-1])) {
                    dp[i][j] = true;
                    if (j - i + 1 > ans_len) {
                        ans_i = i;
                        ans_len = j - i + 1;
                    }
                } else {
                    dp[i][j] = false;
                }
            }
        }
        return s.substr(ans_i, ans_len);
    }
};