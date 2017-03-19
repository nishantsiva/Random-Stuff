#include <stdio.h>
#include <stdlib.h>

#define MAX(x,y) (((x)>(y))?(x):(y))

struct IntNode {
	int low, high, max, count;
	struct IntNode *left, *right;
};

struct IntNode *Tree;

int compare (const void * p1, const void * p2)
{
	return ( *(int*)p1 - *(int*)p2 );
}

int findMax (struct IntNode *node) {
	int max = node->max;
	if (node->left != NULL) {
		max = MAX(max, node->left->max);
	}
	if (node->right != NULL) {
		max = MAX(max, node->right->max);
	}
	return max;
}

struct IntNode* insertInTree (struct IntNode *node, struct IntNode *curr) {
	if (node == NULL) {
		curr->max = curr->high;
		return curr;
	}
	if (curr->low <= node->low) {
		node->left = insertInTree(node->left, curr);
	}
	else {
		node->right = insertInTree(node->right, curr);
	}
	node->max = findMax(node);
	return node;
}

void inorder (struct IntNode *node) {
	if (node == NULL) {
		return;
	}printf("%d %d %d %d\n", node->low, node->high, node->count, node->max);
	inorder(node->left);
	
	inorder(node->right);
}
void createTree (struct IntNode *nodeArr, int low, int high) {
	int mid = (high + low) / 2;
	if (high < low) {
		return;
	}
	Tree = insertInTree(Tree, &(nodeArr[mid]));
	createTree(nodeArr, low, mid-1);
	createTree(nodeArr, mid+1, high);
}

int main (int argc, char *argv[]) {
	struct IntNode *start;
	int cases, N, i;
	scanf("%d",&cases);
	while (cases--) {
		Tree = NULL;
		scanf("%d",&N);
		start = (struct IntNode*)malloc(sizeof(struct IntNode) * N);
		for (i = 0; i < N; i += 1) {
			scanf("%d %d %d", &start[i].low, &start[i].high, &start[i].count);
			start[i].left = start[i].right = NULL;
		}
		qsort (start, N, sizeof(struct IntNode), compare);
		for (i = 0; i < N; i += 1) {
			//printf("%d %d %d\n", start[i].low, start[i].high, start[i].count);
		}
		createTree(start, 0, N-1);
		inorder(Tree);
	}
	return 0;
}
