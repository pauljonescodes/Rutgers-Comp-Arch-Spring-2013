#include <stdio.h>
#include <stdlib.h>
#include "nCr.h"

int main(int argc, const char * argv[])
{
	if (argv[1][0] == '-' && argv[1][1] == 'h') {
		printf("Usage: formula <positive integer>");
	} else {
		int n = atoi(argv[1]);
		
		for (int k = 0; k <= n; k++) {
			printf("%i x^%i ", choose(n, k), k);
			
			if (k != n)
				printf("+ ");
		}
	}
}

