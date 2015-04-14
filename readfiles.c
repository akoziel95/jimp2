#include"readfiles.h"
#define BUFFERSIZE 2048
void pusharray(char **tab, int size)
{
int i;
for(i=0; i < size-1;i++)
strcpy(tab[i],tab[i+1]);

}
ngram *inittab(){
	ngram *p=malloc(sizeof(p)*5);
	return p;
}
int resize(ngram *tab, int size){
	size*=2;
	tab= realloc(tab, sizeof(tab)*size);
	return tab==NULL;
}
int sumlength(char **tab, int size)
{	int i,e=0;
	for(i=0; i<size; i++)
		e+=strlen(tab[i]);
return e+size;
}
ngram *readfile(FILE *in, ngram *tab, int *size, int n, int *counter)
{
	
	// nl char = 10
	int l=0;// licznik odczytanych ngramow
	int i=0,wczyt_tabc=1,j;
	int c;
	char *lastspace;
	char *space;
	char *tabc[n];
	char buf[BUFFERSIZE];
	char wyraz[32];
while(fgets(buf, BUFFERSIZE, in)!=NULL)
{
	space=buf;
	lastspace=space;
	if(wczyt_tabc)//odczytuje pierwsze n-slow
	{	
		for(i; i <n; i++)
		{
			tabc[i]=malloc(sizeof(char)*32);
			space=strchr(lastspace,' ');
				if(space){
					substring(lastspace,tabc[i], 1 ,space-lastspace );
			}
			else{
			space=strchr(lastspace,10);
                        	if(space){
                                	substring(lastspace, tabc[i], 1 ,space-lastspace );
					break;//jezeli koniec lini to przerywam petle wczytujaca slowa
				}
			
			}

			lastspace=space+1;//przesuwam pointer lastpace za ostatnio znaleziona spacje albo znak NL
		}
	}
	if(i==n)//jeżeli wczytane zostalo i wyrazow to 		
	wczyt_tabc=0;
	else continue;//przeskocz instrukcje bo linia i tak juz jest pusta


	while(lastspace!=NULL){ 
	space=strchr(lastspace,' ');
	if(l==*size) //resize struktury
	{	
	//ngram *w=tab;
	//	printf("%d %d ", *size, l);
		tab= realloc(tab, (*size)*2*sizeof*tab);
	(*size)*=2;
	//	free(w);
	}
	//printf(": %s\n", tab[l-1].text);
         if(space){
         	substring(lastspace, wyraz, 1 ,space-lastspace ); 		//odczytuje kolejny wyraz
		c=addngram(tab, &l, tabc, n);
		//printf("%s\n", tab[l-1].text);
		if(tab[c-1].sufixc==tab[c-1].sufixsize){
			tab[c-1].sufixsize*=2;
			tab[c-1].sufixes = realloc(tab[c-1].sufixes,tab[c-1].sufixsize*sizeof(char*));			
			}
		tab[c-1].sufixes[tab[c-1].sufixc]= malloc(sizeof(char)*strlen(wyraz));	//dodaje ostatnie n slow jako ngram
		strcpy(tab[c-1].sufixes[tab[c-1].sufixc++], wyraz);			//dodaje sufiks
		pusharray(tabc, n);						//przesuwam wyrazy w tablicy i dodaje "wyraz"
		strcpy(tabc[i-1],wyraz);
	//	printf("%s\n", tab[l-1].sufixes[tab[l-1].sufixc-1]);
	//	printf("%s\n", wyraz);
                }
         else{
        	space=strchr(lastspace,10);	// 10- to znak konca linii
                if(space)
		{
                	substring(lastspace, wyraz, 1 ,space-lastspace );
			c=addngram(tab, &l, tabc, n);
			if(tab[c-1].sufixc==tab[c-1].sufixsize){
                        	tab[c-1].sufixsize*=2;
	                        tab[c-1].sufixes = realloc(tab[c-1].sufixes, tab[c-1].sufixsize*sizeof(char*));
                        }
			tab[c-1].sufixes[tab[c-1].sufixc]= malloc(sizeof(char)*strlen(wyraz));
			strcpy(tab[c-1].sufixes[tab[c-1].sufixc++],wyraz);
	                pusharray(tabc, n);
			strcpy(tabc[i-1],wyraz);
			break;
                }
                
             }
	lastspace=space+1;
	  }
	}
	
	//printf("%s\n", tab[0].text);
	//printf("OUUUUT\n");
	*counter =l;
	return tab;
}

int readfile_from_ngrams(FILE in, ngram *tab, int *size){
	return 0;
}


void substring(char s[], char sub[], int p, int l) {
   int c = 0;
 
   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}
int addngram(ngram *tab, int *l, char **tabc, int sizec)
{
	
	int i=sumlength(tabc, sizec);
	char *napis=malloc(sizeof(char)*i);
	tab[*l].text= malloc(sizeof(char)*i);
		
		napis=strcpy(napis, tabc[0]);
	for(i=1; i<sizec; i++){
		strcat(napis, " ");	
		strcat(napis, tabc[i]);
	}
	for(i=0; i<*l; i++)
	{
		if(strcmp(napis,tab[i].text)==0)
			return i+1;
	}
	if(napis[0]<91&&napis[0]>65)
		tab[*l].start=1;
	else tab[*l].start=0;
	strcpy(tab[*l].text,napis);
	tab[*l].sufixc=0;
	tab[*l].sufixes = malloc(20*sizeof(char*));
	tab[*l].sufixsize = 20;
	//printf("%s\n", tab[*l].text); //wypisuje n-gram kontrolnie
	(*l)++;
	free(napis);
	return *l;
	
}
