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

int strCompare(char *s1,char *s2){
	int i;
	for(i=0;s1[i]!='\0'&&s2[i]!='\0';i++){
		if(s1[i]!=s2[i])
			return s1[i]-s2[i];
	}
	return s1[i]-s2[i];
}

void strCopy(char *source, char *dest){
	int i = 0; int j = 0;
	do{
		dest[i] = source[i];
	}while(source[i++] != '\0');
}

void trim(char *s){
	int i,j,len;
	for(len=0;s[len]!='\0';len++);
	for(i=len-1;i>=0;i--){
		if(s[i]==' ' || s[i]=='\n')
			s[i] = '\0';
		else
			break;
	}
	for(i=0;s[i]!='\0';i++){
		if(s[i]=='\n' || s[i]==' '){
			for(j=i;s[j]!='\0';j++)
				s[j] = s[j+1];
			i--;
		}
		else
			break;
	}
}

int term_tokenizer_v1( struct TextLine *line ){
	int iter = 0,iterc = 0,i;
	int count = 0,found = 0;
	char temp[100];
	if(line->text[iter] == '\0')
		return -1;
	do{
		if(line->text[iter] == '\0' || line->text[iter] == ','){
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
			if(found == 0){
				trim(temp);
				strCopy( temp, line->terms[count++]);
			}
		}
		else
			temp[iterc++] = line->text[iter];
	}while(line->text[iter++] != '\0');
	line->num_terms = count;
}

int term_tokenizer_v2( struct TextLine *vocabulary, struct TextLine *line ){
	int iter = 0,iterc = 0,i;
	int count = 0,found = 0;
	char temp[100];
	if(line->text[iter] == '\0')
		return -1;
	do{
		if(line->text[iter] == '\0' || line->text[iter] == ','){
			if(iterc == 0)
				continue;
			temp[iterc] = '\0';
			trim(temp);
			iterc = 0;found = 0;
			for(i = 0; i<count; i++){
				if(strCompare(temp,line->terms[i]) == 0){
					found = 1;
					break;
				}
			}
			if(found == 0){
				for(i = 0; i<vocabulary->num_terms; i++){
					if(strCompare(temp,vocabulary->terms[i]) == 0){
						found = 1;
						break;
					}
				}
				if(found == 1)	
					strCopy( temp, line->terms[count++]);
			}
		}
		else
			temp[iterc++] = line->text[iter];
	}while(line->text[iter++] != '\0');
	line->num_terms = count;
}

int load_corpus( char *file_name, struct Corpus *corpus ){
	int i=0;
	FILE *fp;
	char *line = NULL;
	char inputArr[50];
	size_t len = 0;
	ssize_t read;
	fp = fopen(file_name, "r");
	if ((read = getline(&line, &len, fp)) != -1) {
		corpus->vocabulary = (struct TextLine*)malloc(sizeof(struct TextLine));
		trim(line);
		strCopy(line,corpus->vocabulary->text);
		term_tokenizer_v1(corpus->vocabulary);
	}
	while ((read = getline(&line, &len, fp)) != -1) {
		corpus->corpus_lines[i] = (struct TextLine*)malloc(sizeof(struct TextLine));
		trim(line);
		strCopy(line,corpus->corpus_lines[i]->text);
		term_tokenizer_v2(corpus->vocabulary,corpus->corpus_lines[i]);
		i++;
	}
	corpus->num_lines = i;
}

float term_matcher( struct TextLine *target_line, struct TextLine *corpus_line ,int *p, int *q){
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
	*p = count;
	*q = total;
	return corpus_line->match_score;
}

void corpus_calculater(struct Target *target, struct Corpus *corpus, FILE *opt){
	int i,j,p,q,_p,_q;
	struct TextLine *highest;
	float max_score = 0.0,temp;
	for(i=0;i<corpus->num_lines;i++){
		temp = term_matcher(target->target_line[0],corpus->corpus_lines[i],&_p,&_q);
		if(temp>max_score){
			max_score = temp;
			highest = corpus->corpus_lines[i];
			p = _p;
			q = _q;
		}
	}
	//printf("%s;%d/%d=%.2f;%s\n",target->target_line[0]->text,p,q,max_score,highest->text);
	fprintf(opt,"%s;%d/%d=%.2f;%s\n",target->target_line[0]->text,p,q,max_score,highest->text);
}

main(){
	int i;
	struct Corpus corpus;
	struct Target target;
	FILE *fp,*fp_match;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	load_corpus("./corpus.txt",&corpus);
	
	fp = fopen("./target.txt", "r");
	fp_match = fopen("./matches.txt", "w");
	while ((read = getline(&line, &len, fp)) != -1) {
		target.target_line[0] = (struct TextLine *)malloc(sizeof(struct TextLine));
		trim(line);
		strCopy(line,target.target_line[0]->text);
		term_tokenizer_v2(corpus.vocabulary,target.target_line[0]);
		corpus_calculater(&target,&corpus,fp_match);
		free(target.target_line[0]);
	}
}
