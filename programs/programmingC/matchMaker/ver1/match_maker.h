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
