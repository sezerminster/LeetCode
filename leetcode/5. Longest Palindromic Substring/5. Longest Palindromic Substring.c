#include <stdio.h>
#include <string.h>

char *longestPalindrome(char *s)
{
    int n = strlen(s);
    int start = 0, max_len = 1;
    int arr[n][n];
    memset(arr, 0, sizeof arr);

    for (int i = 0; i < n; i++)
    {
        arr[i][i] = 1;
        for (int j = 0; j < i; j++)
        {
            if (s[j] == s[i] && (i - j <= 2 || arr[j + 1][i - 1]))
            {
                arr[j][i] = 1;
                if (i - j + 1 > max_len)
                {
                    start = j;
                    max_len = i - j + 1;
                }
            }
        }
    }

    char *result = malloc(max_len + 1);
    strncpy(result, s + start, max_len);
    result[max_len] = '\0';
    return result;
}
