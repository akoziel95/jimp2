#include"readfiles.h"
#include"generator.h"
#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>

char *usage="Aby poprawnie uruchomić program należy podać argumenty:\n"
"-d plik z danymi wejsciowymi\n" 
"-o plik wyjsciowy"
"-g plik z n-gramami(w przypadku generowania tekstu bez użycia plików bazowych) \n"
"-w ilość wygenerowanych słów(domyślnie 100)\n"
"-c ilość wygenerowanych akapitów(domyślnie 2)\n" 
"-s nazwa pliku ze statystykami \n"
"-n stopien n-gramu";
int main(int argc, char **argv)
{	
	int opt;
	char *inp = NULL;
	char *ingr = NULL;
	char *outc = NULL;
	char *progname= argv[0];
	int w = 100;
	int c = 2;
	char *stat;
	int n=3;

	while ((opt = getopt (argc, argv, "d:o:g:w:c:s:n:")) != -1) {
    switch (opt) {
    case 'd':
      inp = optarg;
      break;
    case 'o':
      outc = optarg;
      break;
    case 'g':
      ingr = optarg;
      break;
    case 'w':
      w = atoi (optarg);
      break;
    case 'c':
      c = atoi(optarg);
      break;
    case 's':
      stat = optarg;
      break;
    case 'n':
	n=atoi(optarg);
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
	/*else {
		inf = fopen(ingr, "r");
		if (inf == NULL) {
      		fprintf (stderr, "%s Blad otwierania pliku z bazą n-gramów %s\n\n", argv[0], inp);
      		exit (EXIT_FAILURE);
    	}
	}*/
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
generate(tab, *l, out, w, c);

free(tab);
close(inf);
close(out);
//tutaj zaczyna się wywoływanie funkcji odczytu i generacji tekstu
return 0;
}
