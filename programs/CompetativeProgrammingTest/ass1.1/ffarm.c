#include<stdio.h>

int
nextpalindrome(int a){
	int val[4],i,j;
	if(a>=999 || a<0){
		return -1;
	}
	if(a==0){
		return 1;
	}
	if(a==9){
		return 11;
	}
	if(a==99){
		return 101;
	}
	for(i=0;a>0;i++){
		val[i] = a%10;
		a = a/10;
	}
	switch(i){
		case 1: return val[0]+1;
		case 2: if(val[0] < val [1]) val[0] = val[1];
				else
					val[0] = val[1] = val[1] + 1;
				break;
		case 3: if(val[0] < val [2]) val[0] = val[2];
				else{
					val[1]++;
					if(val[1]>9){
						val[1] = 0;
						val[2]++;
					}
					val[0] = val[2];
				}
				break;
	}
	a = 0;
	for(j=i-1;j>=0;j--){
		a = a*10 + val[j];
	}
	return a;
}



int
main (int argc, char *argv[])
{
	int T,i,a,b,l;
	int aans,bans,maxans;
	int atmp,btmp,maxtmp,ltmp;
	scanf("%d",&T);
	for(i=0;i<T;i++){
		scanf("%d %d %d",&a,&b,&l);
		aans = bans = nextpalindrome(a-1);
		if(aans > b || aans < 1 || l < 1){
			printf("Barren Land.\n");
			continue;
		}
		maxans = 1;
		
		atmp = aans;
		btmp = nextpalindrome(aans);
		
		maxtmp = 1;
		while(btmp != -1){
			ltmp = btmp - atmp + 1;
			if(ltmp > l || btmp > b){
				atmp = nextpalindrome(atmp);
				btmp = nextpalindrome(atmp);
				maxtmp = 1;
				continue;
			}
			maxtmp++;
			if(maxtmp > maxans){
				maxans = maxtmp;
				aans = atmp;
				bans = btmp;
			}
			btmp = nextpalindrome(btmp);
		}
		printf("%d %d\n",aans,bans);
	}
	return 0;
}
