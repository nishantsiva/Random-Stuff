#include<stdio.h>
#include<stdlib.h>

#define INPUT 	"./input.in"
#define OUTPUT 	"./output.out"
#define FALSE   0
#define TRUE    1

typedef struct{
	int a;
	int b;
	int count,size;
	int *arr;
}table;

table **HashTable;
int length;
int p,a,b;

int isqrt(int number) {  
  	int n  = 1;  
  	int n1 = (n + number/n) >> 1;  
  	while(abs(n1 - n) > 1) {  
    	n  = n1;  
    	n1 = (n + number/n) >> 1;  
  	}  
  	while(n1*n1 >= number)  
    	n1--;
  	while(n1*n1 < number)  
    	n1++;   
  	return n1;  
} 

int nextprime(int inval) {
    int perhapsprime;
    int testfactor;
    int found;
    int sqroot;
    perhapsprime = (inval + 1) | 1; //next odd number
    for (found = FALSE; found != TRUE; perhapsprime += 2) {
        // Check factors from 3 up to sqrt(perhapsprime) 
        sqroot = isqrt(perhapsprime);
        for (testfactor = 3; testfactor <= sqroot; testfactor += 1) {
            found = TRUE; 
            if ((perhapsprime % testfactor) == 0){
                found = FALSE;
                break;
            }
        }
        if (found == TRUE)
			return (perhapsprime);
    }
}

int randomPrime(int val){
	int randNo,i;
	srand(time(NULL));
	randNo = ( rand() % 5 ) + 1;
	for(i = 0; i<randNo; i++)
		val = nextprime(val);
	return val;
}

table* createHashNode(){
	table *ptr;
	ptr = (table*)malloc(sizeof(table));
	//srand(time(NULL));
	ptr->a = ( rand() % p ) + 1;
	ptr->b = ( rand() % p ) + 1;
	return ptr;
}

void setupTable(char *inputFile){
	int index,num,i;int max = 0;
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
    ssize_t read;
	
	HashTable = (table**)malloc(length*sizeof(table*));
	for(i = 0; i<length; i++) HashTable[i] = NULL;
	//srand(time(NULL));
	a = ( rand() % p ) + 1;
	b = ( rand() % p ) + 1;
	fp = fopen(inputFile, "r");
	
	while ((read = getline(&line, &len, fp)) != -1) {
		num = atoi(line);
		index = (((long long int)a*num + b)%p)%length;
		if(HashTable[index] == NULL){
			HashTable[index] = createHashNode();
			HashTable[index]->count = 1;
		}
		else
			HashTable[index]->count++;
	}
	close(fp);
	for(index = 0; index<length; index++){
		if(HashTable[index] != NULL){
			HashTable[index]->size = HashTable[index]->count * HashTable[index]->count;
			HashTable[index]->arr = (int*)malloc(HashTable[index]->size * sizeof(int));
			for(i = 0; i<HashTable[index]->size; i++) HashTable[index]->arr[i] = 0;
		}
	}
}

void rehash(table *tbPtr,int count,int num){
	int i,j,index,collision = TRUE;
	int a[count];
	for(i = 0; i < count; i++) a[i] = 0;
	
	for(i = 0, j = 0; i < tbPtr->size; i++){
		if(tbPtr->arr[i] != 0){
			a[j] = tbPtr->arr[i];
			tbPtr->arr[i] = 0;
			j++;
		}
	}
	a[j] = num;
	
	while(collision){
		tbPtr->a = ( rand() % p ) + 1;
		tbPtr->b = ( rand() % p ) + 1;
		for(i = 0; i < count; i++){
			if(a[i] == 0) continue;
			index = (((long long int)tbPtr->a*a[i] + tbPtr->b)%p)%tbPtr->size;
			if(tbPtr->arr[index] == 0){
				tbPtr->arr[index] = a[i];
			}
			else{
				for(j = 0; j < tbPtr->size; j++) tbPtr->arr[j] = 0;
				break;
			}
		}
		if(i == count)
			collision = FALSE;
	}
}

insertToTable(char *inputFile){
	int num,index,index2,aj,bj,sj,count = 0;
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
    ssize_t read;
    
    fp = fopen(inputFile, "r");
    while ((read = getline(&line, &len, fp)) != -1) {
		num = atoi(line);
		index = (((long long int)a*num + b)%p)%length;
		aj = HashTable[index]->a;
		bj = HashTable[index]->b;
		sj = HashTable[index]->size;
		index2 = (((long long int)aj*num + bj)%p)%sj;
		if(HashTable[index]->arr[index2] == 0)
			HashTable[index]->arr[index2] = num;
		else{
			if(HashTable[index]->arr[index2] == num){
				printf("Duplicate found : %d\n",num);
				continue;
			}
			rehash(HashTable[index],HashTable[index]->count,num);
		}
	}
	close(fp);
}

int searchHash(int val, int *index1, int *index2){
	*index1 = (((long long int)a*val + b)%p)%length;
	*index2 = (((long long int)HashTable[*index1]->a*val + HashTable[*index1]->b)%p)%HashTable[*index1]->size;
	if(HashTable[*index1]->arr[*index2] == val)
		return 0;
	return -1;
}

void search(char *inputFile,char *outputFile){
	FILE *fo,*fi;
	char *line = NULL;
	size_t len = 0;
    ssize_t read;
    int index1,index2,num;
	fi = fopen(inputFile, "r");
	fo = fopen(outputFile, "w");
	while ((read = getline(&line, &len, fi)) != -1) {
		num = atoi(line);
		if(searchHash(num,&index1,&index2) == 0)
			fprintf(fo, "%d %d %d\n",num,index1,index2);
		else
			printf("%d not found in hash table.",num);
	}
}	

main(){
	int num,largest = 0,count = 0,i;
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
    ssize_t read;
	fp = fopen(INPUT, "r");
	length = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		largest = (largest > atoi(line))?largest:atoi(line);
		length++;
	}
	close(fp);
	p = randomPrime(largest);
	setupTable(INPUT);
	insertToTable(INPUT);
	search(INPUT,OUTPUT);
}
