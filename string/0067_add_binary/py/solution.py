from itertools import zip_longest

class Solution:
    def addBinary(self, a: str, b: str) -> str:
        ans = ''
        carry_flag = 0
        for i, j in zip_longest(reversed(a), reversed(b), fillvalue='0'):
            ans += str((int(i) + int(j) + carry_flag) % 2)
            if int(i) + int(j) + carry_flag > 1:
                carry_flag = 1
            else:
                carry_flag = 0
        if carry_flag:
            ans += '1'
        return ''.join(reversed(ans))