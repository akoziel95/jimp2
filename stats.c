#include"readfiles.h"
#define BUFFERSIZE 4096


void gen_stats(FILE *out, FILE *in, ngram *tab, int l)
{
char **tabw;
int *occurs;
int n=1,i,overall=0;
int size=1000;
tabw=malloc(sizeof(tabw)*size);
tabw[0]=malloc(sizeof(char)*10);
tabw[0]="";
occurs=malloc(sizeof(occurs)*size);
char buf[BUFFERSIZE];
char wyraz[32];
char *lastspace, *space;
	while(fgets(buf, BUFFERSIZE, in)){
                        //printf("%d\n",buf[strlen(buf)-1]);

		int niepuste=1;
		space=buf;
                lastspace=space;

		while(niepuste){

			if(n==size){
                tabw=realloc(tabw, sizeof(tabw)*size*2);
                size*=2;
		occurs=realloc(occurs,sizeof(occurs)*size);}

			//printf("blabll");
                        space=strchr(lastspace,' ');
		      if (!space){
			space=strchr(lastspace, 10);
			//printf("to nie spacja %s",space);
			}
		      if(space==NULL){niepuste=0;break;}
			//jezeli nie ma spacji lub znaku konca linni to brak wyrazów
                        substring(lastspace, wyraz, 1 ,space-lastspace);//odczytuje slowo
                      for(i=0;i<n;i++)
				if(strcmp(wyraz,tabw[i])==0)
					{occurs[i]++; break;}
			if(i==n){
			tabw[n]=malloc(sizeof(char)*strlen(wyraz)); 
			occurs[n]++;
			strcpy(tabw[n],wyraz);
			n++;
			}
			printf("%s%d\n", tabw[n-1],occurs[n-1]);
			lastspace=space+1;
			overall++;
		}
	

	}
int max=occurs[0];
int k=0;
	for(i=0;i<n;i++)
		if(max<occurs[i])
			{max=occurs[i];
			k=i;
			}
	
fprintf(out,"Najczesciej wystepujace slowo to - \"%s\"\n, a jego prawdopodobienstwo wystapienia wynosi %f\n", tabw[k], (float)occurs[i]/overall);



}
