# 5. 最长回文子串

[题目链接](https://leetcode.cn/problems/longest-palindromic-substring/)

给你一个字符串 `s`，找到 `s` 中最长的 `回文` `子串`。

> **回文：** 如果字符串向前和向后读都相同，则它满足 **回文性**。
>
> **字串：** **子字符串** 是字符串中连续的 **非空** 字符序列。

### 示例 1：

> **输入：** s = "babad"
>
> **输出：** "bab"
>
> **解释：** "aba" 同样是符合题意的答案。

### 示例 2：

> **输入：** s = "cbbd"
>
> **输出：** "bb"

### 提示：

- $1 <= s.length <= 1000$
- `s` 仅由数字和英文字母组成

---

### 想法1：动态规划

对于一个字符串`S`而言，如果它是回文串，那么其首位再加上相同的字符也同样是回文串，如`aba`是回文串，那么`cabac`也是回文串。

按照这样的思路可以使用动态规划解决，下面给出状态转移方程。

$$
dp[i][j] = 
\begin{cases}
true, & i = j \\
true, & j - i = 1 \text{ and } s[i] = s[j] \\
true, & j - i > 1 \text{ and } s[i] = s[j] \text{ and } dp[i+1][j-1] = true \\
false, & \text{otherwise}
\end{cases}
$$

其中$i$代表字符串的左边界，$j$代表字符串的右边界，$dp[i][j]$代表从 i 到 j 的字符串是否为回文串。

状态转移方程出来了，接下来我们需要研究循环的起始位置了。

从中我们可以看到，$dp[i][j]$主要看两个东西，一个是自己本身的$i,j,s[i],s[j]$，另一个就是$dp[i+1][j-1]$了。

由此可知，我们的递推方向是从左下往右上（i递减，j递增）。

可以写出相关循环代码：

```cpp
for (int i = n - 1; i >= 0; i--) {
    for (int j = i; j < n; j++) {
        if (i == j) {
            dp[i][j] = true;
        } else if (j - i == 1 && s[i] == s[j]) {
            dp[i][j] = true;
        } else if (j - i > 1 && s[i] == s[j] && dp[i+1][j-1]) {
            dp[i][j] = true;
        } else {
            dp[i][j] = false;
        }
    }
}
```

简化代码：

```cpp
for (int i = n - 1; i >= 0; i--) {
    for (int j = i; j < n; j++) {
        if (i == j || s[i] == s[j] && (j - i == 1 || dp[i+1][j-1])) {
            dp[i][j] = true;
        } else {
            dp[i][j] = false;
        }
    }
}
```

**AC代码：**

- **cpp：**

```cpp
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