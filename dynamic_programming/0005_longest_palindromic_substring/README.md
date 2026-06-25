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

### 解法1：动态规划

对于一个字符串`S`而言，如果它是回文串，那么其首尾再加上相同的字符也同样是回文串，如`aba`是回文串，那么`cabac`也是回文串。

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

其中 $i$ 代表字符串的左边界， $j$ 代表字符串的右边界， $dp[i][j]$ 代表从 i 到 j 的字符串是否为回文串。

状态转移方程出来了，接下来我们需要研究循环的起始位置了。

从中我们可以看到， $dp[i][j]$ 主要看两个东西，一个是自己本身的 $i,j,s[i],s[j]$ ，另一个就是 $dp[i+1][j-1]$ 了。

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
```

---

### 解法2：中心扩散法（zhouye提供）

对于回文串来说，可以按照 **对称位置** 分为两种情况：

- **中心对称：** 如 `aba` ， `abcba` 等。
- **镜面对称：** 如 `abba` ， `abccba` 等。

因此我们可以通过确定 **中心位置** 来暴力遍历所有符合条件的字符串。

中心位置同对称位置分为两种， `单字符` 和 `双字符` ，用 `left` 和 `right` 来指向中心位置的首尾索引。

$$
right = 
\begin{cases}
left, & 单字符 \\
left + 1, & 双字符 \\
\end{cases}
$$

遍历中心起始位置 `left` ，按照中心位置向两边扩散，每次扩散时判断首尾两个字符是否相同，相同则继续扩散，不相同则停止扩散。

- **单字符（中心对称）：** `a` 然后向两边扩散，如 `bab` ， `cbabc` 。
- **双字符（镜面对称）：** `aa` 然后向两边扩散，如 `baab` ， `cbaabc` 。

相关AC代码如下：

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        string maxstr = "";
		for (int i = 0; i < s.size(); i++) {
			string x = huiwen(s, i, i); // 中心对称
			string y = huiwen(s, i, i + 1); // 镜面对称
			if (x.size() > maxstr.size()) {
				maxstr = x;
			} 
			if (y.size() > maxstr.size()) {
				maxstr = y;
			} 
		}
		return maxstr;
	}
    string huiwen(string s, int l, int r) {
		while (l >= 0 && r < s.size() && s[l] == s[r]) { 
			l--;
			r++; // 扩散
		}
		return s.substr(l + 1, r - l - 1);
	}
};
```

然而，聪明的你可以想到，我们可以通过每两个字符之间插入同一字符把镜面对称给转化成中心对称来减轻负担。

如：

- `abccba` 变成 `#a#b#c#c#b#a#` 。
- `abcba` 变成 `#a#b#c#b#a#` 。

优化后的 **python** 代码如下：

```python
class Solution:
    def longestPalindrome(self, s: str) -> str:
        t = "#" + "#".join(s) + "#"
        n = len(t)
        maxstr = ""
        for i in range(n):
            l, r = i, i
            while l > 0 and r < n - 1 and t[l - 1] == t[r + 1]:
                l -= 1
                r += 1
            start = l // 2
            length = (r - l) // 2
            if length > len(maxstr):
                maxstr = s[start:start + length]
        return maxstr
```