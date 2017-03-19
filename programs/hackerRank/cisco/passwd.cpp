#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int cases, M, m;
    int MAX = 1000000;
    scanf("%d", &cases);
    while (cases--) {
        scanf("%d %d", &m, &M);
        if (m == M && M == 6)
        {
            printf("NO\n");
        }
        else if (M >= 6)
        {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
}