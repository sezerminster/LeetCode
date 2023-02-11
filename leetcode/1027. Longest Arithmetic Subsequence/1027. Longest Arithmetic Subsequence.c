#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int longestArithSeqLength(int* nums, int numsSize) {
    int dp[numsSize][10001];
    int maxLen = 2;
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < i; j++) {
            int diff = nums[i] - nums[j] + 5000;
            dp[i][diff] = max(dp[i][diff], dp[j][diff] + 1);
            maxLen = max(maxLen, dp[i][diff] + 1);
        }
    }
    return maxLen;
}
