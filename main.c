#include <stdio.h>

/*
 *	testbed for Mr Woo's magic integer square root
 */
main(argc, argv)
char **argv;
{
	int i;

	if (argc < 2) {
		while (scanf("%d", &i) == 1) printf("%d\n", sqrt(i));
	} else {
		for (i=1; i<argc; i++) printf("%d\n", sqrt(atoi(argv[i])));
	}

	exit(0);
}
