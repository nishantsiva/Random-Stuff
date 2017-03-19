#include<stdio.h>
#include<stdlib.h>

int main(){
    int T,N,*height,*width;
    int *arrInc,*arrDec,bestInc,bestDec;
	int i,j,t;
    scanf("%d",&T);
    for(t = 1; t <= T; t++){
        scanf("%d",&N);
		height = (int*)malloc(sizeof(int)*N);
		width = (int*)malloc(sizeof(int)*N);
		arrInc = (int*)malloc(sizeof(int)*N);
		arrDec = (int*)malloc(sizeof(int)*N);
        for(i = 0; i < N; i++){
			scanf("%d",&height[i]);
		}
        for(i = 0; i < N; i++){
			scanf("%d",&width[i]);
		}
        bestInc = bestDec = 0;
        for(i = 0; i < N; i++){
            arrInc[i] = arrDec[i] = width[i];
            for(j = 0; j < i; j++){
                if(height[j]<height[i] && width[i]+arrInc[j]>arrInc[i]){
                    arrInc[i] = width[i]+arrInc[j];
                }
            }
            for(j = 0;j < i; j++){
                if(height[j]>height[i] && width[i]+arrDec[j]>arrDec[i]){
                    arrDec[i] = width[i]+arrDec[j];
                }
            }
            if(arrInc[i] > arrInc[bestInc]){
				bestInc = i;
			}
			if(arrDec[i] > arrDec[bestDec]){
				bestDec = i;
			}
        }
        if(arrInc[bestInc] >= arrDec[bestDec]){
			printf("Case %d. Increasing (%d). Decreasing (%d).\n",t,arrInc[bestInc],arrDec[bestDec]);
		}
        else{
			printf("Case %d. Decreasing (%d). Increasing (%d).\n",t,arrDec[bestDec],arrInc[bestInc]);
		}
		free(height);
		free(width);
		free(arrInc);
    	free(arrDec);
    }
}
