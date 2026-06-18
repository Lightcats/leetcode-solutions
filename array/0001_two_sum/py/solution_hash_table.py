from typing import List

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        seen = {} # hash table
        for i, num in enumerate(nums):
            complement = target - num
            if complement in seen: # O(1)
                return [seen[complement], i]
            seen[num] = i