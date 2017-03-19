#include<stdio.h>
#include<stdlib.h>

#define	TRUE	1
#define	FALSE	0

struct node
{
	struct node *left,*right,*up,*down,*colHeader;
	int row,col,val,reg,count;
};

struct Link
{
	int data;
	struct Link *next;
};

struct Entry
{
	int val,no_possibles;
	struct Link *possibles;
};

struct Solution
{
	struct node *solnRow;
	struct Solution *left,*right;
};

struct Entry **board;
struct node *root;
struct Solution *solnHead = NULL,*solnTail = NULL;
int input,size;
int filled = 0;
int nonzero = 0;
int meshRows = 0;


int build(){
	int i,j,val;
	scanf("%d",&input);
	size = input * input;
	board = (struct Entry**)malloc(size * sizeof(struct Entry*));
	for(i=0;i<size;i++){
		board[i] = (struct Entry*)malloc(size * sizeof(struct Entry));
	}
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			if(scanf("%d",&val) <= 0 || val < 0 || val > size){
				printf("Error in Input!!!\n");
				return FALSE;
			}
			if(val != 0) nonzero++; //NISH
			board[i][j].val = val;
			board[i][j].possibles = NULL;
			board[i][j].no_possibles = 0;
		}
	}
	return TRUE;
}

void printBoard(){
	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			printf("%2d  ",board[i][j].val);
		}
		printf("\n");
	}
}

void insertLink(struct Link **node,int val){
	struct Link *ptr;
	if(*node == NULL){
		*node = (struct Link *)malloc(sizeof(struct Link));
		(*node)->data = val;
		(*node)->next = NULL;
		return;
	}
	ptr = *node;
	while(ptr->next != NULL){
		ptr = ptr->next;
	}
	ptr->next = (struct Link *)malloc(sizeof(struct Link));
	ptr->next->data = val;
	ptr->next->next = NULL;
}

int ispossible(int value,int row,int col){
	int i,j;
	for(i=0;i<size;i++){
		if(board[row][i].val == value)
			return FALSE;
	}
	for(i=0;i<size;i++){
		if(board[i][col].val == value)
			return FALSE;
	}
	for(i=(row/input)*input;i<(row/input)*input+input;i++){
		for(j=(col/input)*input;j<(col/input)*input+input;j++){
			if(board[i][j].val == value)
				return FALSE;
		}
	}
	return TRUE;
}
			

int fillPossibles_util(int row, int col){
	int i;
	if(board[row][col].val != 0)
		return TRUE;
					for(i=1;i<=size;i++){
		if(ispossible(i,row,col) == TRUE){
			insertLink(&(board[row][col].possibles),i);
			board[row][col].no_possibles++;
		}
	}
	if(board[row][col].no_possibles == 0){
		return FALSE;
	}
	return TRUE;
}
			
int fillPossibles(){
	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(fillPossibles_util(i,j) == FALSE)
				return FALSE;
		}
	}
	return TRUE;
}

printpossibles(){
	int i,j;
	struct Link *ptr;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			printf("(%d,%d) : ",i,j);
			ptr = board[i][j].possibles;
			while(ptr){
				printf("%d ",ptr->data);
				ptr = ptr->next;
			}
			printf("\n");
		}
	}
}

struct node* insertNode(struct node *colHdr,struct node *prevPtr,int row,int col,int val,int reg){
	struct node *ptr;
	ptr = (struct node*)malloc(sizeof(struct node));
	ptr->down = colHdr;
	ptr->up = colHdr->up;
	ptr->up->down = ptr;
	colHdr->up = ptr;
	if(prevPtr == NULL){
		ptr->right = ptr->left = ptr;
	}
	else{
		ptr->right = prevPtr->right;
		ptr->left = prevPtr;
		ptr->right->left = ptr;
		prevPtr->right = ptr;
	}
	ptr->colHeader = colHdr;
	ptr->row = row;
	ptr->col = col;
	ptr->val = val;
	ptr->reg = reg;
	colHdr->count++;
	return ptr;
}
	
void build_exact_cover(){
	int i,j,tempval,tempreg;
	struct node *ptr,*rptr,*cptr;
	struct Link *lptr;
	root = (struct node*)malloc(sizeof(struct node));
	root->left = root->right = root->up = root->down = root->colHeader = root;
	root->row = root->col = root->val = root->reg = -1;
	ptr = root;
	for(i = 0; i < size; i++){	//row x col
		for(j = 0; j < size; j++){
			ptr->right = (struct node*)malloc(sizeof(struct node));
			ptr->right->left = ptr;
			ptr = ptr->right;
			root->left = ptr;
			ptr->right = root;
			ptr->up = ptr->down = ptr->colHeader = ptr;
			ptr->row = i;
			ptr->col = j;
			ptr->val = ptr->reg = -1;
			ptr->count = 0;
		}
	}
	for(i = 0; i < size; i++){	//row x val
		for(j = 1; j <= size; j++){
			ptr->right = (struct node*)malloc(sizeof(struct node));
			ptr->right->left = ptr;
			ptr = ptr->right;
			root->left = ptr;
			ptr->right = root;
			ptr->up = ptr->down = ptr->colHeader = ptr;
			ptr->row = i;
			ptr->val = j;
			ptr->col = ptr->reg = -1;
			ptr->count = 0;
		}
	}
	for(i = 0; i < size; i++){	//col x val
		for(j = 1; j <= size; j++){
			ptr->right = (struct node*)malloc(sizeof(struct node));
			ptr->right->left = ptr;
			ptr = ptr->right;
			root->left = ptr;
			ptr->right = root;
			ptr->up = ptr->down = ptr->colHeader = ptr;
			ptr->col = i;
			ptr->val = j;
			ptr->row = ptr->reg = -1;
			ptr->count = 0;
		}
	}
	for(i = 0; i < size; i++){	//reg x val
		for(j = 1; j <= size; j++){
			ptr->right = (struct node*)malloc(sizeof(struct node));
			ptr->right->left = ptr;
			ptr = ptr->right;
			root->left = ptr;
			ptr->right = root;
			ptr->up = ptr->down = ptr->colHeader = ptr;
			ptr->reg = i;
			ptr->val = j;
			ptr->row = ptr->col = -1;
			ptr->count = 0;
		}
	}
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			tempval = -1;
			lptr = NULL;
			if(board[i][j].val != 0)
				tempval = board[i][j].val;
			else
				lptr = board[i][j].possibles;
			while(lptr || (tempval > 0)){meshRows++;
				if(tempval == -1){
					tempval = lptr->data;
					lptr = lptr->next;
				}
				tempreg = (i/input)*input + j/input;
				cptr = root->right;
										while(cptr->row != i || cptr->col != j) cptr = cptr->right;
				ptr = insertNode(cptr,NULL,i,j,tempval,tempreg);
										while(cptr->row != i || cptr->val != tempval) cptr = cptr->right;
				ptr = insertNode(cptr,ptr,i,j,tempval,tempreg);
										while(cptr->col != j || cptr->val != tempval) cptr = cptr->right;
				ptr = insertNode(cptr,ptr,i,j,tempval,tempreg);
										while(cptr->reg != tempreg || cptr->val != tempval) cptr = cptr->right;
				ptr = insertNode(cptr,ptr,i,j,tempval,tempreg);
				tempval = -1;
			}
		}
	}
}

void addToSoln(struct node *row){
	if(solnHead == NULL){
		solnHead = (struct Solution*)malloc(sizeof(struct Solution));
		solnHead->left = solnHead->right = solnHead;
		solnHead->solnRow = row;
		return;
	}
	solnHead->left->right = (struct Solution*)malloc(sizeof(struct Solution));
	solnHead->left->right->left = solnHead->left;
	solnHead->left = solnHead->left->right;
	solnHead->left->right = solnHead;
	solnHead->left->solnRow = row;
}

void popFromSoln(){
	struct Solution *ptr;
	if(solnHead->right == solnHead){
		free(solnHead);
		solnHead = NULL;
		return;
	}
	ptr = solnHead->left;
	solnHead->left = ptr->left;
	ptr->left->right = solnHead;
	free(ptr);
}

void cover(struct node *colNode)
{
	struct node *rowNode, *nodePtr;
	colNode->right->left = colNode->left;
	colNode->left->right = colNode->right;
	for( rowNode = colNode->down;  rowNode!=colNode;  rowNode =  rowNode->down)
	{
		for(nodePtr =  rowNode->right; nodePtr!= rowNode; nodePtr = nodePtr->right) 
		{
			nodePtr->up->down = nodePtr->down;
			nodePtr->down->up = nodePtr->up;
			nodePtr->colHeader->count--;
		}
	}
}

void uncover(struct node *colNode)
{
	struct node *rowNode, *LeftNode;
	for( rowNode = colNode->up;  rowNode!=colNode;  rowNode =  rowNode->up) 
	{
		for(LeftNode =  rowNode->left; LeftNode!= rowNode; LeftNode = LeftNode->left) {
			LeftNode->up->down = LeftNode;
			LeftNode->down->up = LeftNode;
			LeftNode->colHeader->count++;
		}
	}
	colNode->right->left = colNode;
	colNode->left->right = colNode;
}

int back = 0;//NISH
struct HeapNode{
	struct node *ptr;
	int val;
};
struct Heap{  
	struct HeapNode *arr;
	int count;
	int capacity;
};
int iter = 0;
void heapInsert(struct Heap *list,struct node *element, int value)
{
	int now;
	list->count++;
	list->arr[list->count].ptr = element; /*Insert in the last place*/
	list->arr[list->count].val = value;
	/*Adjust its position*/
	now = list->count;
	while(list->arr[now/2].val > value && now/2 > 0) 
	{
		list->arr[now] = list->arr[now/2];
		now /= 2;
	}
	list->arr[now].ptr = element;
	list->arr[now].val = value;
}

struct node* heapExtractMin(struct Heap *list)
{
	struct HeapNode minElement,lastElement;
	int child,now;
	if(list->count == 0){
		return NULL;
	}
	minElement = list->arr[1];
	lastElement = list->arr[list->count--];
	/* now refers to the index at which we are now */
	for(now = 1; now*2 <= list->count; now = child)
	{
		/* child is the index of the element which is minimum among both the children */ 
		/* Indexes of children are i*2 and i*2 + 1*/
		child = now*2;
		/*child!=heapSize beacuse heap[heapSize+1] does not exist, which means it has only one 
		child */
		if(child != list->count && list->arr[child].val > list->arr[child+1].val ) 
		{
			child++;
		}
		/* To check if the last element fits ot not it suffices to check if the last element
		is less than the minimum element among both the children*/
		if(lastElement.val > list->arr[child].val)
		{
			list->arr[now] = list->arr[child];
		}
		else /* It fits there */
		{
			break;
		}
	}
	list->arr[now] = lastElement;//printf(" %d",minElement.val);
	return minElement.ptr;
}

int solve_exact_cover(){
	struct node *ptr,*curCol,*rowInCol,*nodeInRow;
	struct Heap *heapList;
	int minCount,rowcount,nis;
	if(root->right == root){
		return TRUE;
	}
	minCount = -1;
	for(ptr = root->right; ptr != root; ptr = ptr->right){
		if(minCount > ptr->count || minCount == -1){
			minCount = ptr->count;
			curCol = ptr;
		}
	}
	if(minCount < 1) {back++;//NISH
		return FALSE;
	}
	
	heapList = (struct Heap*)malloc(sizeof(struct Heap));
	heapList->count = 0;
	heapList->capacity = minCount;
	heapList->arr = (struct HeapNode*)malloc((minCount+1)*sizeof(struct HeapNode));
	for(rowInCol = curCol->down; rowInCol != curCol; rowInCol = rowInCol->down){
		rowcount = 0;
		for(nodeInRow = rowInCol->right; nodeInRow != rowInCol; nodeInRow = nodeInRow->right){
			rowcount += nodeInRow->colHeader->count;
		}
		heapInsert(heapList,rowInCol,rowcount);
	}
/*	for(nis = 1;nis<=heapList->count;nis++){*/
/*		printf("%d ",heapList->arr[nis].val);*/
/*	}*/
/*	printf(" -> ");*/
/*	for(ptr = heapExtractMin(heapList); ptr!=NULL; ptr = heapExtractMin(heapList)){*/
/*		*/
/*	}*/
/*	printf("\n");*/
	cover(curCol);
	//for(rowInCol = curCol->down; rowInCol != curCol; rowInCol = rowInCol->down){
	for(rowInCol = heapExtractMin(heapList); rowInCol!=NULL; rowInCol = heapExtractMin(heapList)){
		addToSoln(rowInCol);
		for(nodeInRow = rowInCol->right; nodeInRow != rowInCol; nodeInRow = nodeInRow->right){
			cover(nodeInRow->colHeader);
		}
		if(solve_exact_cover() == TRUE)
			return TRUE;
		popFromSoln();
		for(nodeInRow = rowInCol->left; nodeInRow != rowInCol; nodeInRow = nodeInRow->left){
			uncover(nodeInRow->colHeader);	
		}
	}
	uncover(curCol);
	return FALSE;
}

void fillSolved(){
	struct Solution *ptr;
	ptr = solnHead;
	if(ptr == NULL){
		return;
	}
	do{
		if(board[ptr->solnRow->row][ptr->solnRow->col].val == 0){
			board[ptr->solnRow->row][ptr->solnRow->col].val = ptr->solnRow->val;
		}
		else if(board[ptr->solnRow->row][ptr->solnRow->col].val != ptr->solnRow->val){
			printf("Error :: Value missmatch!!!\n");
		}
		ptr = ptr->right;
	}while(ptr != solnHead);
}

int backtrack(){
	build_exact_cover();
	if(solve_exact_cover() == FALSE) return FALSE;
	fillSolved();printf("Backtrack %d\n",back);
}

int solve(){
	if(fillPossibles() == FALSE)
		return FALSE;
	if(backtrack() == FALSE)
		return FALSE;
	return TRUE;
}

int main (int argc, char *argv[]){
	if(!build()) return;
	//printf("INPUT :\n");
	//printBoard();
	if(solve() == TRUE){
		printf("\nOUTPUT :\n");
		printBoard();
	}
	else{
		printf("Can't solve..\n");
	}
	//printpossibles();
	//printmesh();
	//printf("\nAlready filled: %d\tAlg Filled: %d\tUnfilled: %d\n",nonzero,filled,size*size - (filled + nonzero));
	printf("%d\n",meshRows);
	return 0;
}
