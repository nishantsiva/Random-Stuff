#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int updateBestNSum(int B, int A){
    if(A > 0 && B > 0){
        return B + A;
    }
    if(A > 0 && B < 0){
        return A;
    }
    if(A < 0 && B < 0 && A > B){
        return A;
    }
    return B;
}

int main() {
    int T, N, i;
    int bestCSum, bestNSum, sum, val;
    int A[100001];
    scanf("%d", &T);
    while(T--){
        scanf("%d", &N);
        for(i = 0; i < N; i++){
            scanf("%d", &A[i]);
        }
        bestCSum = bestNSum = -100000;
        sum = 0;
        for(i = 0; i < N; i++){
            bestNSum = updateBestNSum(bestNSum, A[i]);
            sum = sum + A[i];
            if(sum > bestCSum){
                bestCSum = sum;
            }
            if(sum < 0){
                sum = 0;
            }
        }
        printf("%d %d\n", bestCSum, bestNSum);
    }
    return 0;
}