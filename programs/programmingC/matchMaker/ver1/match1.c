#include <stdio.h>
#include <stdlib.h>
//#include "match_maker.h"
#define LINESIZE 100
#define MAXTERMS 20
#define TERMSIZE 20
#define MAXLINES 100
#define MAXTARGETS 1

struct TextLine{
	char text[LINESIZE];
	char terms[TERMSIZE][MAXTERMS];
	int num_terms;
	float match_score; // Applicable only if TextLine is a TARGET_LINE
};

struct Corpus{
	struct TextLine *corpus_lines[MAXLINES];
	int num_lines;
	float overall_match;
};

struct Target{
	struct TextLine *target_line[MAXTARGETS];
	float match_score;
};

int strCompare(char *s1,char *s2){
	int i;
	for(i=0;s1[i]!='\0'&&s2[i]!='\0';i++){
		if(s1[i]!=s2[i])
			return s1[i]-s2[i];
	}
	return 0;
}


int term_tokenizer_v1( struct TextLine *line ){
	int i,j,k;
	for(i = 0, j = 0, k = 0; line->text[i] != '\0'; i++){
		if(line->text[i] == ' '){
			line->terms[j][k] = '\0';
			j++;k=0;
			continue;
		}
		line->terms[j][k++] = line->text[i];
	}
	line->num_terms = j+1;
}

int load_corpus( struct Corpus *corpus ){
	int i=0;
	char inputArr[50];
	for(i=0;!feof(stdin);i++){
		corpus->corpus_lines[i] = (struct TextLine*)malloc(sizeof(struct TextLine));
		scanf(" %[^\n]s",corpus->corpus_lines[i]->text);
		term_tokenizer_v1(corpus->corpus_lines[i]);
	}
	corpus->num_lines = i-1;
}

int load_target( struct Target *target ){
	target->target_line[0] = (struct TextLine*)malloc(sizeof(struct TextLine));
	scanf("%[^\n]s",target->target_line[0]->text);
}

void print_result(struct Target *target){
	printf("%s\n",target->target_line[0]->text);
}


void print_result1(struct Corpus *corpus){
	int i,j;
	for(i = 0;i < corpus->num_lines;i++){
		printf("%s\n",corpus->corpus_lines[i]->text);
		for(j=0;j<corpus->corpus_lines[i]->num_terms;j++)
			printf("\t%s\n",corpus->corpus_lines[i]->terms[j]);
	}
}

main(){
	int flag = 1;
	struct Corpus corpus;
	struct Target target; 
	load_target(&target);
	print_result(&target);
	load_corpus(&corpus);
	printf("\n");
	print_result1(&corpus);
}
