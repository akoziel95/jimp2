#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef struct {
	char *text;
	char **sufixes;
	int start;
	int sufixc;
	int sufixsize;	
}ngram;

void pusharray(char **tab, int size);
int sumlength(char **tab, int size);
int addngram(ngram *tab, int *l, char **tabc, int sizec);
ngram *readfile(FILE *in, ngram *tab, int *size, int n,int *counter);

int readfile_from_ngrams(FILE in, ngram *tab, int *size);

void substring(char s[], char sub[], int p, int l);

ngram *inittab();
int resize(ngram *tab, int size);
