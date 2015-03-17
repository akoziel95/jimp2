

typedef struct ngram{
	char text;
	char **sufixes;
	int *probs;
	int start=0;	
};

int readfile(FILE in, ngram ngrams);

