import sys

class Solution:
    def coinChange(self, coins, amount):
        """
        :type coins: List[int]
        :type amount: int
        :rtype: int
        """
        dp = [-1] * (amount + 1)
        dp[0] = 0
        for i in range(1, amount + 1):
            min_val = -1
            for coin in coins:
                if coin <= i and dp[i - coin] != -1:
                    if min_val == -1:
                        min_val = dp[i - coin] + 1
                    else:
                        min_val = min(min_val, dp[i - coin] + 1)
            dp[i] = min_val
        return dp[amount]


if __name__ == "__main__":
    sol = Solution()
    print(sol.coinChange([1, 2, 5], 11))
    print(sol.coinChange([3, 6, 405, 436], 8839))
    print(sol.coinChange([22], 3))
