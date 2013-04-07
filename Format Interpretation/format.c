#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

char * pad_bin (char * bin, int n) {
	int bin_len = (int)strlen(bin);
	int dif = n - bin_len;
	char * new_bin = malloc(n + 1);
	int i = 0;
	int j = 0;
	
	memset(new_bin,0,n+1);
	if (n == 0) {
		return bin;
	} else for (;i <= n; i++) {
		if (i < dif) {
			new_bin[i] = '0';
		} else {
			new_bin[i] = bin[j];
			j++;
		}
	}
    
	return new_bin;
}



char * flip_da_bits(char * flip) {
	int i = 0;
    
		printf("flippin' da bits on %s\n", flip);
    
	for (; i < (int) strlen(flip); i++) {
		if (flip[i] == '1')
			flip[i] = '0';
		else
			flip[i] = '1';
	}
    
		printf("flipped  da bits on %s\n", flip);
    
	return flip;
}



void reverse(char *string)
{
	int length, c;
	char *begin, *end, temp;
    
	length = (int)strlen(string);
    
	begin = string;
	end = string;
    
	for ( c = 0 ; c < ( length - 1 ) ; c++ )
		end++;
    
	for ( c = 0 ; c < length/2 ; c++ )
	{
		temp = *end;
		*end = *begin;
		*begin = temp;
        
		begin++;
		end--;
	}
}

char * bin_add (char * bin_one, char * bin_two) {
	int i;
	bool shouldCarry;
    
	char * bin_added = malloc(strlen(bin_two) + 1 + 1);
	bin_added[strlen(bin_two)] = '\0';
	i = (int)strlen(bin_two) - 1;
	shouldCarry = false;
	memset(bin_added,0,strlen(bin_two)+1+1);
    
	for (; i >= 0; i--) {
		if (!shouldCarry) {
			if (bin_one[i] == '0' && bin_two[i] == '0') {
				bin_added = strcat(bin_added, "0");
				shouldCarry = false;
			} else if ((bin_one[i] == '0' && bin_two[i] == '1') ||
                       (bin_one[i] == '1' && bin_two[i] == '0')) {
				bin_added = strcat(bin_added, "1");
				shouldCarry = false;
			} else if (bin_one[i] == '1' && bin_two[i] == '1') {
				bin_added = strcat(bin_added, "0");
				shouldCarry = true;
			}
		} else {
			if (bin_one[i] == '0' && bin_two[i] == '0') {
				bin_added = strcat(bin_added, "1");
				shouldCarry = false;
			} else if ((bin_one[i] == '0' && bin_two[i] == '1') ||
                       (bin_one[i] == '1' && bin_two[i] == '0')) {
				bin_added = strcat(bin_added, "0");
				shouldCarry = true;
			} else if (bin_one[i] == '1' && bin_two[i] == '1') {
				bin_added = strcat(bin_added, "1");
				shouldCarry = true;
			}
		}
	}
    
	if (shouldCarry)
		bin_added = strcat(bin_added, "1");
    
	reverse(bin_added);
    
	return bin_added;
}

char * bin_sub(char * bin_one, char * bin_two) {
	bin_two = flip_da_bits(bin_two);
	bin_two = bin_add(pad_bin("1", (int)strlen(bin_two)), bin_two);
	return bin_add(bin_one, bin_two);
}

int bin_to_dec (char * bin, int flip) {
	int i = 0;
	int power = (int)strlen(bin) - 1;
	int value = 0;
	int flipped = 0;
    
	if (bin[0] == '1' && flip) {
		flip_da_bits(bin);
		flipped = 1;
	}
    
	for (i = 0; i < (int)strlen(bin); i++) {
		
		if (bin[i] == '1') {
			value += (int) pow(2, power);
		}
		
		power--;
	}
	
	if (flipped){
		value++;
	}
	
	return value;
}

double process_mantissa (char * bin) {
	int i = 0;
	int power = -1;
	double value = 0;
    
	for (i = 0; i < (int)strlen(bin); i++) {
		
		if (bin[i] == '1') {
			value += pow(2, power);
		}
		
		power--;
	}
	
	return value;
}

void process_float(char * floatstr) {
	int i = 0;
	int flipped = 0;
	
	reverse(floatstr);
	
	char * exponent_str = malloc(8 + 1);
	memset(exponent_str, 0, 8);
	exponent_str[8] = '\0';
	
	char * fraction = malloc(23 + 1);
	memset(fraction, 0, 23);
	fraction[23] = '\0';
	
	for (; i < (int)strlen(floatstr); i++) {
		
		if (i == 0) {
			if (floatstr[i] == '1')
				flipped = 1;
		} else if (i >= 1 && i <= 8) {
			exponent_str[i - 1] = floatstr[i];
		} else {
			fraction[i-9] = floatstr[i];
		}
	}
	
	int sign_int = floatstr[0] == '0' ? 1 : -1;
	
	//printf("Exponent-str: %s\n", exponent_str);
	
	double exponent_int = bin_to_dec(exponent_str, 0) - 127;
	
	//printf("Exponent-int: %f\n", exponent_int);
	
	exponent_int = pow(2, exponent_int);
	double fraction_double = 1 + process_mantissa(fraction);
	
	//printf("Sign: %i\n", sign_int);
	//printf("Exponent: %f \n", exponent_int);
	//printf("Fraction: %f \n", fraction_double);
	
	double value = sign_int * exponent_int * fraction_double;
	int power = 0;
	
	if (value < 1) {
		while (value < 1) {
			value *= 10;
			power--;
		}
	} else if (value > 9) {
		while (value > 9) {
			value /= 10;
			power++;
		}
	}
	
	printf("%fe%i", value, power);
}



int main (int argc, char *argv[]) {
	
	char * tmp = malloc(strlen(argv[2] + 1));
	tmp[(int)strlen(argv[2])] = '\0';
	if (strcmp(argv[2], "int") == 0) {
		printf("%i", bin_to_dec(argv[1], 1));
	} else if (strcmp(argv[2], "float") == 0) {
		
		if (strcasecmp(argv[1], "10000000000000000000000000000000") == 0) {
			tmp = "-0.0e0";
			printf("%s", tmp);
		} else {
			tmp = strcpy(tmp, argv[1]);
			reverse(tmp);
			process_float(tmp);
		}
	} else {
		fprintf(stderr, "I don't recognize the 2nd argument you inputted.");
	}
	
	return 0;
}
