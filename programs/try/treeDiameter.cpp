#include <iostream>
using namespace std;

void insert(int *A, int val, int cur){
	if(A[cur] == -1){
		A[cur] = val;
		return;
	}
	if(val < A[cur])
		insert(A, val, cur*2+1);
	else
		insert(A, val, cur*2+2);
}

int path(int *A, int num, int cur){
	if(A[cur] == num)
		return 1;
	if(num < A[cur])
		return 1 + path(A, num, cur*2+1);
	return 1 + path(A, num, cur*2+2);

}

int length(int *A, int num1, int num2, int cur){
	if(num1 < A[cur] && num2 < A[cur]){
		return length(A, num1, num2, cur*2+1);
	}
	if(num1 > A[cur] && num2 > A[cur]){
		return length(A, num1, num2, cur*2+2);
	}
	if(num1 == A[cur]){
		return path(A, num2, cur*2+2);
	}
	if(num2 == A[cur]){
		return path(A, num1, cur*2+1);
	}
	return path(A, num1, cur*2+1) + path(A, num2, cur*2+2);
}

int main(int argc, char const *argv[])
{
	int N, val, num1, num2;
	int A[10000];
	for (int i = 0; i < 10000; ++i)
	{
		A[i] = -1;
	}
	cin>>N;
	for (int i = 0; i < N; ++i)
	{
		cin>>val;
		insert(A,val,0);
	}
	cin>>num1>>num2;
	if(num2 < num1){
		int t = num1;
		num1 = num2;
		num2 = t;
	}
	if(num1 == num2)
		cout<<0<<endl;
	else
		cout<<length(A, num1, num2, 0)<<endl;
	return 0;
}