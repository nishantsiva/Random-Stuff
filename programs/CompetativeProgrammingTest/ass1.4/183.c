#include<stdio.h>
#include<stdlib.h>

int
fillBitmapD(int **mat,char *input,int index,int rowL,int colL,int rowU,int colU){
	char ch;
	int i,j,used = 0;
	ch = input[index++];
	if(ch == '0' || ch == '1'){
		for(i = rowL; i <= rowU; i++){
			for(j = colL; j <= colU; j++){
				mat[i][j] = (int)(ch - '0');
			}
		}
		return 1;
	}
	if(ch == 'D'){
		used += fillBitmapD(mat,input,index,rowL,colL,(rowL + rowU) / 2,(colL + colU) / 2);
		if(colL != colU){
			used += fillBitmapD(mat,input,index+used,rowL,(colL + colU) / 2 + 1,(rowL + rowU) / 2,colU);
		}
		if(rowL != rowU){
			used += fillBitmapD(mat,input,index+used,(rowL + rowU) / 2 + 1,colL,rowU,(colL + colU) / 2);
			if(colL != colU){
				used += fillBitmapD(mat,input,index+used,(rowL + rowU) / 2 + 1,(colL + colU) / 2 + 1,rowU,colU);
			}
		}
		return used+1;
	}
	return 0;
}

void
printInD(int **mat,int rowL,int colL,int rowU,int colU){
	int i,j,bit,DFlag = 0;
	bit = mat[rowL][colL];
	for(i = rowL; i <= rowU; i++){
		for(j = colL; j <= colU; j++){
			if(mat[i][j] != bit){
				DFlag = 1;
				break;
			}
		}
		if(DFlag == 1) break;
	}
	if(DFlag == 0){
		printf("%d",bit);
	}
	else{
		printf("D");
		printInD(mat,rowL,colL,(rowL + rowU) / 2,(colL + colU) / 2);
		if(colL != colU){
			printInD(mat,rowL,(colL + colU) / 2 + 1,(rowL + rowU) / 2,colU);
		}
		if(rowL != rowU){
			printInD(mat,rowU / 2 + 1,colL,rowU,(colL + colU) / 2);
			if(colL != colU){
				printInD(mat,(rowL + rowU) / 2 + 1,(colL + colU) / 2 + 1,rowU,colU);
			}
		}
	}
}

int
main (int argc, char *argv[])
{
	int **mat,i,j,k,row,col;
	char input[60],line1[25],line2[60];
	char tokens[5][5];
	fgets(line1,25,stdin);
	i=0;j=0;k=0;
	do{
		if(line1[i] == ' ' || line1[i] == '\t' || line1[i] == '\0'){
			if(k != 0){
				tokens[j][k] = '\0';
				k=0;j++;
			}
			continue;
		}
		tokens[j][k++] = line1[i];
	}while(line1[i++] != '\0');
	while(tokens[0][0] != '#'){
		row = atoi(tokens[1]);
		col = atoi(tokens[2]);
		mat = (int**)malloc(sizeof(int*)*row);
		for(i=0;i<row;i++){
			mat[i] = (int*)malloc(sizeof(int)*col);
		}
		fgets(input,60,stdin);
		for(i=0,j=0;input[i] != '\0'; i++){
			if(input[i] == '1' || input[i] == '0' || input[i] == 'D'){
				line2[j++] = input[i];
			}
		}
		line2[j] = '\0';
		if(tokens[0][0] == 'B'){
			k=0;
			for(i=0;i<row;i++){
				for(j=0;j<col;j++){
					mat[i][j] = (int)line2[k++] - '0';
				}
			}
			printf("D %d %d\n",row,col);
			printInD(mat,0,0,row-1,col-1);
			printf("\n");
		}
		else{
			fillBitmapD(mat,line2,0,0,0,row-1,col-1);
			printf("B %d %d\n",row,col);
			for(i=0;i<row;i++){
				for(j=0;j<col;j++){
					printf("%d",mat[i][j]);
				}
			}
			printf("\n");
		}
		fgets(line1,25,stdin);
		i=0;j=0;k=0;
		do{
			if(line1[i] == ' ' || line1[i] == '\t' || line1[i] == '\0'){
				if(k != 0){
					tokens[j][k] = '\0';
					k=0;j++;
				}
				continue;
			}
			tokens[j][k++] = line1[i];
		}while(line1[i++] != '\0');
	}
	return 0;
}
