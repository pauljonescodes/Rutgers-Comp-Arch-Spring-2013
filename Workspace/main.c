//
//  main.c
//  Workspace
//
//  Created by Paul Jones on 3/30/13.
//  Copyright (c) 2013 Rutgers University. All rights reserved.
//

#include <stdio.h>

int Factorial(int n) {
	int ret = 1;
	
	while (n > 0) {
		ret = ret * n;
		n--;
	}
	
	return ret;
}


int nCr(int n, int r) {
	int nFactorial = Factorial(n);
	
	if (nFactorial == -1)
		return -1;
	
	int rFactorial = Factorial(r);
	
	if (rFactorial == -1) {
		return -1;
	}
	
	int nmrFactorial = Factorial(n - r);
	
	if (nmrFactorial == -1) {
		return -1;
	}
	
	int denomiator = rFactorial * nmrFactorial;
	int returnValue = nFactorial / denomiator;
	
	return returnValue;
}

int main(int argc, const char * argv[])
{
	//printf("%i", Factorial(12));
	printf("%i", nCr(10, 2));
    return 0;
}