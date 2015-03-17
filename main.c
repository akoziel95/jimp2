#include"readfiles.h"
#include<stdio.h>
#include <stdlib.h>
#include <getopt.h>

char *usage="Aby poprawnie uruchomi� program nale�y poda� argumenty:\n"
"-d plik z danymi wejsciowymi\n" 
"-o plik wyjsciowy"
"-g plik z n-gramami(w przypadku generowania tekstu bez u�ycia plik�w bazowych) \n"
"-w ilo�� wygenerowanych s��w(domy�lnie 100)\n"
"-c ilo�� wygenerowanych akapit�w(domy�lnie 2)\n" 
"-s nazwa pliku ze statystykami \n"

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


	while ((opt = getopt (argc, argv, "d:o:g:w:c:s:")) != -1) {
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
      c = optarg;
      break;
    case 'd':
      stat = optarg;
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
	else {
		inf = fopen(ingr, "r");
		if (inf == NULL) {
      		fprintf (stderr, "%s Blad otwierania pliku z baz� n-gram�w %s\n\n", argv[0], inp);
      		exit (EXIT_FAILURE);
    	}
	}
FILE *out = fopen (outc, "w");
    if (out == NULL) {
      fprintf (stderr, "%s Blad otwierania pliku do zapisu tekstu %s\n\n", argv[0], outc);
	fclose(inf);
      exit (EXIT_FAILURE);
    }


//tutaj zaczyna si� wywo�ywanie funkcji odczytu i generacji tekstu
