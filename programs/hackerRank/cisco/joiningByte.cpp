#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct block
{
	char s[1002];
	int adj[3001];
	int nAdjs, used;
};

block blocks[1000];
int N;

void insertAdj (int cur, int adj) {
	blocks[cur].adj[blocks[cur].nAdjs++] = adj;
}

int isPalindrome (char *s1, char *s2) {
	std::string str = std::string(s1) + std::string(s2);
	int flag = 0;
	for (int i = 0, j = str.length()-1;i < j;i++, j--)
    {
        if (str[i] != str[j])
        {
            flag = 1;
        }
    }
	if(flag == 0) {
		return 1;
	}
	str = std::string(s2) + std::string(s1);
	flag = 0;
	for (int i = 0, j = str.length()-1;i < j;i++, j--)
    {
        if (str[i] != str[j])
        {
            flag = 1;
        }
    }
	if(flag == 0) {
		return 1;
	}
	return 0;
}

void findAdj () {
	for (int i = 0; i < N; ++i)
	{
		for (int j = i+1; j < N; ++j)
		{
			if (isPalindrome(blocks[i].s, blocks[j].s) == 1)
			{
				insertAdj(i, j);
				insertAdj(j, i);
			}
		}
	}
}

void removeFromNode (int cur, int from) {
	if (blocks[from].used == 1)
	{
		return;
	}
	int i = 0;
	while (i < blocks[from].nAdjs && blocks[from].adj[i] != cur)
	{
		i++;
	}
	for (; i < blocks[from].nAdjs-1; ++i)
	{
		blocks[from].adj[i] = blocks[from].adj[i+1];
	}
	blocks[from].nAdjs--;
}

int findMinBlocks () {
	int flag = 1, count = 0;
	while (1) {
		int minIndex = -1, minAdj, minAdjIndex, minInAdj;
		flag = 0;
		for (int i = 0; i < N; ++i)
		{
			if (blocks[i].used == 1)
			{
				continue;
			}
			if (blocks[i].nAdjs == 0)
			{
				count ++;
				blocks[i].used = 1;
				continue;
			}
			flag = 1;
			if (minIndex == -1 || blocks[i].nAdjs < minAdj)
			{
				minAdj = blocks[i].nAdjs;
				minIndex = i;
				minAdjIndex = -1;
				for (int j = 0; j < blocks[i].nAdjs; ++j)
				{
					if (minAdjIndex == -1 || blocks[blocks[i].adj[j]].nAdjs < minInAdj)
					{
						minInAdj = blocks[blocks[i].adj[j]].nAdjs;
						minAdjIndex = blocks[i].adj[j];
					}
				}
				continue;
			}
			if (blocks[i].nAdjs == minAdj)
			{
				for (int j = 0; j < blocks[i].nAdjs; ++j)
				{
					if (blocks[blocks[i].adj[j]].nAdjs < minInAdj)
					{
						minInAdj = blocks[blocks[i].adj[j]].nAdjs;
						minAdjIndex = blocks[i].adj[j];
						minIndex = i;
					}
				}
			}
		}
		if (flag == 0)
		{
			break;
		}
		count++;
		blocks[minIndex].used = 1;
		blocks[minAdjIndex].used = 1;
		for (int i = 0; i < minAdj; ++i)
		{
			removeFromNode (minIndex, blocks[minIndex].adj[i]);
		}
		for (int i = 0; i < minInAdj; ++i)
		{
			removeFromNode (minAdjIndex, blocks[minAdjIndex].adj[i]);
		}
	}
	return count;
}

int main() {
	while (scanf("%d", &N) == 1) {
    	for (int i = 0; i < N; ++i)
    	{
    		scanf("%s", blocks[i].s);
    		blocks[i].nAdjs = 0;
    		blocks[i].used = 0;
    	}
    	findAdj();
    	printf("%d\n", findMinBlocks());
    }
    return 0;
}
