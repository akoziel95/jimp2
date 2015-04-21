#include"readfiles.h"
#include"generator.h"
#include<stdio.h>


int main(int argc, char **argv)
{
FILE *in = fopen(argv[1], "r");
FILE *out= fopen("wynik", "w");
FILE *baza= fopen("bazan", "r");
int b=100;

ngram *tab=malloc(sizeof*tab*b);
int *l=malloc(sizeof(int));
printf("Zaczynam czytać\n");
tab=readfile(in, tab, &b, 3,l);
int i,j;
printf("Zaczynam readfile_from_ngrams\n");

/*tab=readfile_from_ngrams(baza, tab, &b, l);

for(i=0; i<*l;i++){
printf("\n%s\tsufixes:", tab[i].text);
	for(j=0;j<tab[i].sufixc; j++)
		printf("%s", tab[i].sufixes[j]);
}	*/

int max=tab[0].occur;
for(i=0;i<*l;i++)
	if(max<tab[i].occur){
		max=tab[i].occur;
	printf("%d\t%s\n", tab[i].occur,tab[i].text);}
close(baza);
generate(tab,*l,out, 5000, 50);

baza=fopen("bazan", "w");
zapisz_do_pliku(tab, *l, baza);
close(baza);
free(tab);
close(in);
close(out);


return 0;
}
