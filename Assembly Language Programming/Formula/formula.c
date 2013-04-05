#include <stdio.h>
#include <stdlib.h>
#include "nCr.h"
#include <time.h>
#include <sys/time.h>

int main(int argc, const char * argv[])
{
	int k = 0;
	int n;
	int c;

	struct timeval start, end;

	if (argv[1][0] == '-' && argv[1][1] == 'h') {
		printf("Usage: formula <positive integer>");
	} else {
		n = atoi(argv[1]);
		
		gettimeofday(&start, NULL);

		printf("(1 + x)^%i = ", n);

		if (n == 0)
			printf("0");

		for (; k <= n; k++) {

			c = nCr(n, k);

			if (c == -1) {
				printf("Multiplication overflow. \n");
				return 1;
			} else {
				if (k != 0)
					printf("%i x^%i ",c , k);
				
				if (k != n && k != 0)
					printf("+ ");
			}
		}

		gettimeofday(&end, NULL);

	}

	printf("\n%ld microseconds\n", ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));

	return 0;
}

