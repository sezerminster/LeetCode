#include <math.h>
#include <stdio.h>

int numSquares(int n) {
    int arr[n + 1];
    arr[0] = 0;
    for (int i = 1; i <= n; i++) {
        arr[i] = i;  // initialize the minimum number of squares to i
        for (int j = 1; j <= sqrt(i); j++) {
            int square = j * j;
            if (square > i) {
                break;
            }
            arr[i] = fmin(arr[i], arr[i - square] + 1);  // update the minimum number of squares
        }
    }
    return arr[n];
}
