#include <stdio.h>
#include <stdlib.h>

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
	struct TextLine *vocabulary;
	struct TextLine *corpus_lines[MAXLINES];
	int num_lines;
	float overall_match;
};

struct Target{
	struct TextLine *target_line[MAXTARGETS];
	float match_score;
};

//int load_corpus( char *file_name, struct Corpus *corpus );
int load_corpus( struct Corpus *corpus );
int load_target( struct Target *targer );
int term_tokenizer_v1( struct TextLine *line );
int term_tokenizer_v2( struct TextLine *vocabulary, struct TextLine *line );
int term_matcher( struct TextLine *target_line, struct TextLine *corpus_line );
void print_result( struct Target *target );
//void clean_up( Corpus *corpus );
void print_result_corpus(struct Corpus *corpus);
int strCompare(char *s1,char *s2);
void strCopy(char *source, char *dest);

int strCompare(char *s1,char *s2){
	int i;
	for(i=0;s1[i]!='\0'&&s2[i]!='\0';i++){
		if(s1[i]!=s2[i])
			return s1[i]-s2[i];
	}
	return s1[i]-s2[i];
}

void strCopy(char *source, char *dest){
	int i = 0;
	do{
		dest[i] = source[i];
	}while(source[i++] != '\0');
}

int term_tokenizer_v1( struct TextLine *line ){
	int iter = 0,iterc = 0,i;
	int count = 0,found = 0;
	char temp[20];
	if(line->text[iter] == '\0')
		return -1;
	do{
		if(line->text[iter] == '\0' || line->text[iter] == ' '){
			if(iterc == 0)
				continue;
			temp[iterc] = '\0';
			iterc = 0;found = 0;
			for(i = 0; i<count; i++){
				if(strCompare(temp,line->terms[i]) == 0){
					found = 1;
					break;
				}
			}
			if(found == 0)
				strCopy( temp, line->terms[count++]);
		}
		else
			temp[iterc++] = line->text[iter];
	}while(line->text[iter++] != '\0');
	line->num_terms = count;
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
	term_tokenizer_v1(target->target_line[0]);
}

void print_result(struct Target *target){
	printf("%s\n",target->target_line[0]->text);
}


void print_result_corpus(struct Corpus *corpus){
	int i;
	for(i = 0; i<corpus->num_lines; i++){
		printf("%.2f:%s\n",corpus->corpus_lines[i]->match_score,
				corpus->corpus_lines[i]->text);
	}
}

int term_matcher( struct TextLine *target_line, struct TextLine *corpus_line ){
	int i,j;
	int count = 0,total;
	for(i = 0; i<corpus_line->num_terms; i++){
		for(j = 0; j<target_line->num_terms; j++){
			if(strCompare(corpus_line->terms[i],
						target_line->terms[j])==0){
				count++;
			}
		}
	}
	total = corpus_line->num_terms+target_line->num_terms-count;
	corpus_line->match_score = count / (float)total;
}

main(){
	int i;
	struct Corpus corpus;
	struct Target target; 
	load_target(&target);
	print_result(&target);
	load_corpus(&corpus);
	for(i = 0; i<corpus.num_lines; i++)
		term_matcher(target.target_line[0],corpus.corpus_lines[i]);
	print_result_corpus(&corpus);
}
