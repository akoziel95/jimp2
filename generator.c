#include"readfiles.h"
#include"stdio.h"


int generate(ngram *tab, int l, FILE *out, int a, int s)
{

	srand(time(NULL));
	int ca=0, cs=0;// ca - ilosc akapitow cs- ilosc slow
	int m,ms,i;
	char current[256];
	char *napis;
	
//	do{
//	m=rand()%l;
//	}while(tab[m].start==0);	//losuje n gram ktory moze byc pocz. zdania
//	printf("jestem za losowaniem");
	int stop=s/a;//ilosc slow na akapit
	int nr=1;
	fprintf(out, "%s ", tab[m].text);cs++;
	while( cs<a)
	{
	if(cs==nr*stop)//kontrola akapitu
		{fprintf(out,"\n\t");
		nr++;ca++;}

		ms=rand()%tab[m].sufixc;
		fprintf(out, "%s ", tab[m].sufixes[ms]);cs++;
		//printf("%s ", tab[m].sufixes[ms]);	
		strcpy(current, tab[m].text);
		strcat(current, " ");	
		strcat(current, tab[m].sufixes[ms]);
		napis=strchr(current, ' ');
		napis++;
			for(i=0; i <l; i++)
				if(strcmp(napis,tab[i].text)==0)
					{m=i;
					break;}//odszukuje nowy ngram w bazie

		if(i==l)//n gram mial zero sufixow i teraz brakuje kolejnego
		{
			m=rand()%l;	
	//		printf("%s ", tab[m].text);
			fprintf(out, "%s ", tab[m].text);
			cs+=3;
		}
	if(cs%20==0)
		fprintf(out,"\n");
	}
	//printf("\nilosc slow %d ilosc akapitow %d\n", cs, ca);
 return 0;
}
