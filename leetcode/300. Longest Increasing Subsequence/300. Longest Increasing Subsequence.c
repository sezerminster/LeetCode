#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLIS(int *nums, int numsSize)
{
    int *dp = (int *)malloc(sizeof(int) * numsSize);
    memset(dp, 0, sizeof(int) * numsSize);
    int len = 0;
    for (int i = 0; i < numsSize; i++)
    {
        int left = 0, right = len;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (dp[mid] < nums[i])
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        dp[left] = nums[i];
        if (left == len)
        {
            len++;
        }
    }
    free(dp);
    return len;
}

