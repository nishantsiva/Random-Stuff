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
int isModified = 0;

int build(FILE *filePtr){
	int i,j,val;
	if(filePtr == NULL){
		printf("Error opening file.\n");
		return FALSE;
	}
	fscanf(filePtr,"%d",&input);
	size = input * input;
	board = (struct Entry**)malloc(size * sizeof(struct Entry*));
	for(i=0;i<size;i++){
		board[i] = (struct Entry*)malloc(size * sizeof(struct Entry));
	}
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			if(fscanf(filePtr,"%d",&val) <= 0 || val < 0 || val > size){
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
		if(board[row][i].val == value) return FALSE;
		if(board[i][col].val == value) return FALSE;
		if(board[(row/input)*input + (i%input)][(col/input)*input + (i/input)].val == value) return FALSE;
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

int searchNdel(struct Link **node,int value){
	struct Link *ptr1,*ptr2;
	if(*node == NULL)
		return 0;
	ptr1 = *node;
	ptr2 = (*node)->next;
	if(ptr1->data == value){
		*node = ptr1->next;
		free(ptr1);
		return 1;
	}
	while(ptr2 != NULL){
		if(ptr2->data == value){
			ptr1->next = ptr2->next;
			free(ptr2);
			return 1;
		}
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}
	return 0;
}

int removeFromNeighb(int row,int col,int value){
	int i,j,ret;
	for(i=0;i<size;i++){
		if(board[row][i].val == 0){
			if(searchNdel(&(board[row][i].possibles),value) == 0)
				continue;
			if(--board[row][i].no_possibles == 0)
				return FALSE;
		}
	}
	for(i=0;i<size;i++){
		if(board[i][col].val == 0){
			if(searchNdel(&(board[i][col].possibles),value) == 0)
				continue;
			if(--board[i][col].no_possibles == 0)
				return FALSE;
		}
	}
	for(i=(row/input)*input;i<(row/input)*input+input;i++){
		for(j=(col/input)*input;j<(col/input)*input+input;j++){
			if(board[i][j].val == 0){
				if(searchNdel(&(board[i][j].possibles),value) == 0)
					continue;
				if(--board[i][j].no_possibles == 0)
					return FALSE;
			}
		}
	}
	return TRUE;
}

int insertValue(int row,int col,int value){
	struct Link *ptr1,*ptr = board[row][col].possibles;
	board[row][col].val = value;
	filled++;
	while(ptr != NULL){
		ptr1 = ptr->next;
		free(ptr);
		ptr = ptr1;
	}
	board[row][col].possibles = NULL;
	return removeFromNeighb(row,col,board[row][col].val);
}

int singleCandidate(){
	int row,col;
	for(row = 0; row < size; row++){
		for(col = 0; col < size; col++){
			if(board[row][col].val == 0 && board[row][col].no_possibles == 1){
				if(insertValue(row,col,board[row][col].possibles->data) == FALSE)
					return FALSE;
				isModified = 1;
			}
		}
	}
	return TRUE;
}

int singleSquare(){
	int arr[size+1][3];
	int i,j,k,boxi,boxj;
	struct Link *ptr;
	for(i=0;i<size+1;i++) arr[i][0] = 0;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(board[i][j].val != 0) continue;
			ptr = board[i][j].possibles;
			while(ptr){
				arr[ptr->data][0]++;
				arr[ptr->data][1] = i;
				arr[ptr->data][2] = j;
				ptr = ptr->next;
			}
		}
		for(k=1;k<size+1;k++){
			if(arr[k][0] == 1){
				if(insertValue(arr[k][1],arr[k][2],k) == FALSE)
					return FALSE;
				isModified = 1;
			}
			arr[k][0] = 0;
		}
	}
	for(j=0;j<size;j++){
		for(i=0;i<size;i++){
			if(board[i][j].val != 0) continue;
			ptr = board[i][j].possibles;
			while(ptr){
				arr[ptr->data][0]++;
				arr[ptr->data][1] = i;
				arr[ptr->data][2] = j;
				ptr = ptr->next;
			}
		}
		for(k=1;k<size+1;k++){
			if(arr[k][0] == 1){
				if(insertValue(arr[k][1],arr[k][2],k) == FALSE)
					return FALSE;
				isModified = 1;
			}
			arr[k][0] = 0;
		}
	}
	for(boxi = 0; boxi < input; boxi += input){
		for(boxj = 0; boxj < input; boxj += input){
			for(i = boxi; i < boxi+input; i++){
				for(j = boxj; j < boxj+input; j++){
					if(board[i][j].val != 0) continue;
					ptr = board[i][j].possibles;
					while(ptr){
						arr[ptr->data][0]++;
						arr[ptr->data][1] = i;
						arr[ptr->data][2] = j;
						ptr = ptr->next;
					}
				}
			}
			for(k=1;k<size+1;k++){
				if(arr[k][0] == 1){
					if(insertValue(arr[k][1],arr[k][2],k) == FALSE)
						return FALSE;
					isModified = 1;
				}
				arr[k][0] = 0;
			}
		}
	}
	return TRUE;
}

int numberClaim(){
	int arr[size];
	int boxi,boxj,row,col,i,j,k;
	struct Link *ptr;
	for(i=0;i<size+1;i++) arr[i] = 0;
	for(boxi = 0; boxi < size; boxi += input){
		for(boxj = 0; boxj < size; boxj += input){
			for(row = boxi; row < boxi+input; row++){		//remove from rest of row
				for(j = boxj; j < boxj+input; j++){
					if(board[row][j].val != 0) continue;
					ptr = board[row][j].possibles;
					while(ptr){
						arr[ptr->data] = 1;
						ptr = ptr->next;
					}
				}
				for(i = boxi; i < boxi+input; i++){
					if(i==row) continue;
					for(j = boxj; j < boxj+input; j++){
						if(board[i][j].val != 0) continue;
						ptr = board[i][j].possibles;
						while(ptr){
							if(arr[ptr->data] == 1)
								arr[ptr->data] = 0;
							ptr = ptr->next;
						}
					}
				}
				for(k=1;k<size+1;k++){
					if(arr[k] == 1){
						for(j = 0; j < size; j++){
							if(j == boxj){
								j += input - 1;
								continue;
							}
							if(searchNdel(&(board[row][j].possibles),k) == 0)
								continue;
							isModified =1;
							if(--board[row][j].no_possibles == 0)
								return FALSE;
						}
					}
					arr[k] = 0;
				}
			}
			for(col = boxj; col < boxj+input; col++){		//remove from rest of col
				for(i = boxi; i < boxi+input; i++){
					if(board[i][col].val != 0) continue;
					ptr = board[i][col].possibles;
					while(ptr){
						arr[ptr->data] = 1;
						ptr = ptr->next;
					}
				}
				for(j = boxj; j < boxj+input; j++){
					if(j==col) continue;
					for(i = boxi; i < boxi+input; i++){
						if(board[i][j].val != 0) continue;
						ptr = board[i][j].possibles;
						while(ptr){
							if(arr[ptr->data] == 1)
								arr[ptr->data] = 0;
							ptr = ptr->next;
						}
					}
				}
				for(k=1;k<size+1;k++){
					if(arr[k] == 1){
						for(i = 0; i < size; i++){
							if(i == boxi){
								i += input - 1;
								continue;
							}
							if(searchNdel(&(board[i][col].possibles),k) == 0)
								continue;
							isModified =1;
							if(--board[i][col].no_possibles == 0)
								return FALSE;
						}
					}
					arr[k] = 0;
				}
			}
			for(row = boxi; row < boxi+input; row++){	//remove from rest of box due to row
				for(j=0;j<size;j++){
					if(j==boxj){
						j+=input-1;
						continue;
					}
					if(board[row][j].val != 0){
						arr[board[row][j].val]++;
						continue;
					}
				
					ptr = board[row][j].possibles;
					while(ptr){
						arr[ptr->data]++;
						ptr = ptr->next;
					}
				}
				for(k=1;k<size+1;k++){
					if(arr[k] == 0){
						for(i = boxi; i < boxi+input; i++){
							if(i == row) continue;
							for(j = boxj; j < boxj+input; j++){
								if(searchNdel(&(board[i][j].possibles),k) == 0)
									continue;
								isModified =1;
								if(--board[i][j].no_possibles == 0)
									return FALSE;
							}
						}
					}
					arr[k] = 0;
				}
			}
			for(col = boxj; col < boxj+input; col++){	//remove from rest of box due to col
				for(i=0;i<size;i++){
					if(i==boxi){
						i+=input-1;
						continue;
					}
					if(board[i][col].val != 0){
						arr[board[i][col].val]++;
						continue;
					}
					ptr = board[i][col].possibles;
					while(ptr){
						arr[ptr->data]++;
						ptr = ptr->next;
					}
				}
				for(k=1;k<size+1;k++){
					if(arr[k] == 0){
						for(j = boxj; j < boxj+input; j++){
							if(j == col) continue;
							for(i = boxi; i < boxi+input; i++){
								if(searchNdel(&(board[i][j].possibles),k) == 0)
									continue;
								isModified =1;
								if(--board[i][j].no_possibles == 0)
									return FALSE;
							}
						}
					}
					arr[k] = 0;
				}
			}
		}
	}
	return TRUE;
}

int lockedSet(){
	int row,col,i,j,k,l,iter1,iter2,boxi,boxj,count,ncount,found;
	int arr[size + 1],values[size],positions[size];
	struct Link *ptr;
	for(count = 2; count < size; count++){
		for(row = 0; row < size; row++){
			for(col = 0; col < size; col++){
				if(board[row][col].val != 0 || board[row][col].no_possibles != count) continue;
				for(i = 1; i <= size; i++) arr[i] = values[i-1] = positions[i] = 0;
				ptr = board[row][col].possibles;
				k = 0;
				while(ptr){
					arr[ptr->data]++;
					values[k++] = ptr->data;
					ptr = ptr->next;
				}
				positions[col] = 1;
				ncount = 1;
				for(j = col+1; j < size; j++){
					if(board[row][j].val != 0 || board[row][j].no_possibles != count) continue;
					ptr = board[row][j].possibles;
					found = 0;
					while(ptr){
						if(arr[ptr->data] == 0) break;
						found ++;
						ptr = ptr->next;
					}
					if(found == count){
						positions[j] = 1;
						if(++ncount == count)
							break;
					}
				}
				if(ncount == count){
					for(j = 0; j < size; j++){
						if(board[row][j].val != 0 || positions[j] == 1) continue;
						for(k = 0; k < count; k++){
							if(searchNdel(&(board[row][j].possibles),values[k]) == 0)
								continue;
							isModified =1;
							if(--board[row][j].no_possibles == 0)
								return FALSE;
						}
					}
				}
			}
		}
	}

	for(count = 2; count < size; count++){
		for(col = 0; col < size; col++){
			for(row = 0; row < size; row++){
				if(board[row][col].val != 0 || board[row][col].no_possibles != count) continue;
				for(i = 1; i <= size; i++) arr[i] = values[i-1] = positions[i] = 0;
				ptr = board[row][col].possibles;
				k = 0;
				while(ptr){
					arr[ptr->data]++;
					values[k++] = ptr->data;
					ptr = ptr->next;
				}
				positions[row] = 1;
				ncount = 1;
				for(i = row+1; i < size; i++){
					if(board[i][col].val != 0 || board[i][col].no_possibles != count) continue;
					ptr = board[i][col].possibles;
					found = 0;
					while(ptr){
						if(arr[ptr->data] == 0) break;
						found ++;
						ptr = ptr->next;
					}
					if(found == count){
						positions[i] = 1;
						if(++ncount == count)
							break;
					}
				}
				if(ncount == count){
					for(i = 0; i < size; i++){
						if(board[i][col].val != 0 || positions[i] == 1) continue;
						for(k = 0; k < count; k++){
							if(searchNdel(&(board[i][col].possibles),values[k]) == 0)
								continue;
							isModified =1;
							if(--board[i][col].no_possibles == 0)
								return FALSE;
						}
					}
				}
			}
		}
	}
	
	for(count = 2; count < size; count++){
		for(boxi = 0; boxi < input; boxi++){
			for(boxj = 0; boxj < input; boxj++){
				for(iter1 = 0; iter1 < size; iter1++){
					row = boxi*input + iter1/input;
					col = boxj*input + iter1%input;
					if(board[row][col].val != 0 || board[row][col].no_possibles != count) continue;
					for(i = 1; i <= size; i++) arr[i] = values[i-1] = positions[i] = 0;
					ptr = board[row][col].possibles;
					k = 0;
					while(ptr){
						arr[ptr->data]++;
						values[k++] = ptr->data;
						ptr = ptr->next;
					}
					positions[iter1] = 1;
					ncount = 1;
					for(iter2 = iter1+1; iter2 < size; iter2++){
						row = boxi*input + iter2/input;
						j = boxj*input + iter2%input;
						if(board[row][j].val != 0 || board[row][j].no_possibles != count) continue;
						ptr = board[row][j].possibles;
						found = 0;
						while(ptr){
							if(arr[ptr->data] == 0) break;
							found ++;
							ptr = ptr->next;
						}
						if(found == count){
							positions[iter2] = 1;
							if(++ncount == count)
								break;
						}
					}
					if(ncount == count){
						for(iter2 = 0; iter2 < size; iter2++){
							row = boxi*input + iter2/input;
							j = boxj*input + iter2%input;
							if(board[row][j].val != 0 || positions[iter2] == 1) continue;
							for(k = 0; k < count; k++){
								if(searchNdel(&(board[row][j].possibles),values[k]) == 0)
									continue;
								isModified =1;
								if(--board[row][j].no_possibles == 0)
									return FALSE;
							}
						}
					}
				}
			}
		}
	}
	return TRUE;
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
			printf("Error: Value missmatch!!!\n");
		}
		ptr = ptr->right;
	}while(ptr != solnHead);
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
			while(lptr || (tempval > 0)){
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

int solve_exact_cover(){
	struct node *ptr,*curCol,*rowInCol,*nodeInRow;
	int minCount;
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
	if(minCount < 1) {
		return FALSE;
	}
	cover(curCol);
	for(rowInCol = curCol->down; rowInCol != curCol; rowInCol = rowInCol->down){
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

int backtrack(){
	build_exact_cover();
	if(solve_exact_cover() == FALSE) return FALSE;
	fillSolved();
}

void fillBlankBoard(){
	int i,j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			board[i][j].val = (i*input + i/input + j) % (size) + 1;
		}
	}
}

int isFilled(){
	if(size*size - (filled + nonzero) == 0)
		return TRUE;
	return FALSE;
}

int solve(){
	if(nonzero == 0){
		fillBlankBoard();
	}
	else{
		if(fillPossibles() == FALSE)
			return FALSE;
		do{
			isModified = 0;
			if(singleCandidate() == FALSE) 	return FALSE; if(isFilled() == TRUE) return TRUE; if(isModified == 1) continue;
			if(singleSquare() == FALSE)		return FALSE; if(isFilled() == TRUE) return TRUE; if(isModified == 1) continue;
			if(lockedSet() == FALSE) 		return FALSE; if(isFilled() == TRUE) return TRUE; if(isModified == 1) continue;
			if(numberClaim() == FALSE) 		return FALSE; if(isFilled() == TRUE) return TRUE; if(isModified == 1) continue;	
		}while(isModified == 1);
		if(size*size - (filled + nonzero) != 0) 
			if(backtrack() == FALSE) return FALSE;
	}
	return TRUE;
}

usage(){
	printf("Usage : \n\t1. ./a.out\n\t2. ./a.out {input file}\n");	
}

int main (int argc, char *argv[]){
	FILE *inputFile;
	if(argc == 1)
		inputFile = stdin;
	else if(argc == 2)
		inputFile = fopen(argv[1],"r");
	else {
		usage();
		return 0;
	}
	if(!build(inputFile)) return 0;
	if(solve() == TRUE){
		printBoard();
	}
	else{
		printf("Can't solve..\n");
	}
	return 0;
}
