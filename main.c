#include"readfiles.h"
#include"generator.h"
#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>

char *usage="Aby poprawnie uruchomić program należy podać argumenty:\n"
"-d plik z danymi wejsciowymi\n" 
"-o plik wyjsciowy\n"
"-g plik z n-gramami(w przypadku generowania tekstu bez użycia plików bazowych) \n"
"-w ilość wygenerowanych słów(domyślnie 100)\n"
"-c ilość wygenerowanych akapitów(domyślnie 2)\n" 
"-n stopien n-gramu\n"
"-b plik wyjsciowy do zapisu ngramow\n";
int main(int argc, char **argv)
{	
	int opt;
	char *inp = NULL;
	char *ingr = NULL;
	char *outc = NULL;
	char *baza =NULL;
	char *progname= argv[0];
	int w = 100;
	int c = 2;
	int n=3;
	int uzycie_bazy=0;

	while ((opt = getopt (argc, argv, "d:o:g:w:c:n:b:")) != -1) {
    switch (opt) {
    case 'd':
      inp = optarg;
      break;
    case 'o':
      outc = optarg;
      break;
    case 'g':
      ingr = optarg;
	uzycie_bazy=1;
      break;
    case 'w':
      w = atoi (optarg);
      break;
    case 'c':
      c = atoi(optarg);
      break;
    case 'n':
	n=atoi(optarg);
     break;
    case 'b':
	baza=optarg;
     break;
    default:                   /* '?' */
      fprintf (stderr, usage, progname);
      exit (EXIT_FAILURE);
    }
 }


	if( optind < argc ) {
                fprintf( stderr, "\nBad parameters!\n" );
                for( ; optind < argc; optind++ )
                        fprintf( stderr, "\t\"%s\"\n", argv[optind] );
                fprintf( stderr, "\n" );
                fprintf( stderr, usage, progname );
                exit( EXIT_FAILURE );
    }
        
         FILE *inf = fopen (inp, "r");
    if (inf == NULL) {		
      fprintf (stderr, "%s Blad otwierania pliku z tekstem bazowym %s\n\n", argv[0], inp);
      exit (EXIT_FAILURE);
    }
	FILE *infg;
		if(uzycie_bazy){
	infg = fopen(ingr, "r");
	if (infg == NULL) {
      		fprintf (stderr, "%s Blad otwierania pliku z bazą n-gramów %s\n\n", argv[0], ingr);
      		exit (EXIT_FAILURE);
    		}
	}
	
FILE *out = fopen (outc, "w");
    if (out == NULL) {
      fprintf (stderr, "%s Blad otwierania pliku do zapisu tekstu %s\n\n", argv[0], outc);
	fclose(inf);
      exit (EXIT_FAILURE);
    }


int *l=malloc(sizeof(int));
int b=5;
ngram *tab=malloc(sizeof*tab*b);
tab=readfile(inf,tab, &b, n, l);
if(uzycie_bazy)
	tab=readfile_from_ngrams(infg, tab,&b,l);
generate(tab, *l, out, w, c);
close(out);
if(baza){
out=fopen(baza, "w");
zapisz_do_pliku(tab,*l,out);
}
FILE *stat=fopen("stats", "w");

close(inf);	
inf = fopen (inp, "r");
gen_stats(stat,inf,tab,*l);
int i,max=tab[0].occur;
fprintf(stat,"Najczesciej wystepujece %d-gramy\n", n);
for(i=0;i<*l;i++)
        if(max<tab[i].occur){
                max=tab[i].occur;
        fprintf(stat,"%d\t%s\n", tab[i].occur,tab[i].text);}

free(tab);
close(inf);
close(out);
//tutaj zaczyna się wywoływanie funkcji odczytu i generacji tekstu
return 0;
}
