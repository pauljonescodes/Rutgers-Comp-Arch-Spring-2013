/*
 * calc.c
 *
 * Paul Jones
 * Professor Brian Russell
 * Computer Architecture (01:198:211)
 * Rutgers University
 *
 * February 26th, 2013
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "calc.h"

#define DEVELOPMENT false

char * single_digit_dec_to_bin (char dec_dig) {
    switch (dec_dig) {
        case '0':
			return "0000";
			break;
		case '1':
			return "0001";
			break;
            
		case '2':
			return "0010";
			break;
            
		case '3':
			return "0011";
			break;
            
		case '4':
			return "0100";
			break;
            
		case '5':
			return "0101";
			break;
            
		case '6':
			return "0110";
			break;
            
		case '7':
			return "0111";
			break;
            
		case '8':
			return "1000";
			break;
            
		case '9':
			return "1001";
			break;
        default:
            return "0000";
            break;
            
    }
}

char * pad_bin (char * bin, int n) {
	int bin_len = (int)strlen(bin);
	int dif = n - bin_len;
	char * new_bin = malloc(n + 1);
	int i = 0;
	int j = 0;
	
	memset(new_bin,0,n+1);
	if (DEVELOPMENT) {
		printf("-   pad_bin(%s)\n", bin);
		printf("\t\t-   binlen: %i\n", bin_len);
	}
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
    
	if (DEVELOPMENT)
		printf("-   after padding: %s\n", new_bin);
    
	return new_bin;
}

char * flip_da_bits(char * flip) {
	int i = 0;
    
	if (DEVELOPMENT)
		printf("flippin' da bits on %s\n", flip);
    
	for (; i < (int) strlen(flip); i++) {
		if (flip[i] == '1')
			flip[i] = '0';
		else
			flip[i] = '1';
	}
    
	if (DEVELOPMENT)
		printf("flipped  da bits on %s\n", flip);
    
	return flip;
}

bool first_is_greater(char * bin_one, char * bin_two) {
	int i = (int) strlen(bin_one) - 1;
    
	if (strlen(bin_one) > strlen(bin_two)) {
		return true;
	} else if (strlen(bin_two) > strlen(bin_one)) {
		return false;
	} else {
		for (; i >= 0; i--) {
			if (bin_one[i] == '1' && bin_two[i] == '0') {
				return true;
			} else if (bin_one[i] == '0' && bin_two[i] == '1') {
				return false;
			}
		}
	}
    
	return false;
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


int main (int argc, char *argv[]) {
    
	/* This is enumerating all the variables I'll need */
    
	/* For the first number inputted */
	char * number_one;
	bool number_one_is_negative = false;
	char number_one_base_char = 'x';
	int number_one_significant_digits = 0;
	bool number_one_is_greater = false;
    
	/* For the second number inputted */
	char * number_two;
	bool number_two_is_negative = false;
	char number_two_base_char = 'x';
	int number_two_significant_digits = 0;
	bool number_two_is_greater;
    
	/* What we're sending out */
	char * output;
	char output_base;
	char output_operation = ' ';
	bool output_is_negative;
    
	char *tmp;
    
	/* These are the counters I'll need */
	/* I'm sorry they're ambiguous, but there just counters */
    
	int i = 0;
	int j = 0;
	int k = 0;
    
	/* Some simple error checking */
    
	if (argc < 5) {
		fprintf(stderr, "%s", "you inputted too few arguments");
		return 1;
	}
    
	if (DEVELOPMENT) {
		printf("-   main\n");
	}
    
    
	/* Right let's boogey.
	 * Or process some arguments!
	 * Whatever. */
    
	for (; i < argc; i++) {
		char const *arg =  argv[i];
        
		switch (i) {
			case 0:
				break;
			case 1:
				output_operation = arg[0];
				break;
			case 2:
				number_one_is_negative = arg[0] == '-' ? true : false;
				number_one_base_char = number_one_is_negative ? arg[1] : arg[0];
				number_one_significant_digits = (int)(number_one_is_negative ? strlen(arg) - 2: strlen(arg) - 1);
				k = number_one_is_negative ? 2 : 1;
				number_one = malloc(number_one_significant_digits+1);
				number_one[number_one_significant_digits] = '\0';
				j = 0;
                
				for (; k < strlen(arg); k++) {
					char current_digit = arg[k];
					number_one[j] = current_digit;
					j++;
				}
                
				number_one[j] = '\0';
                
				break;
			case 3:
				number_two_is_negative = arg[0] == '-' ? true : false;
				number_two_base_char = number_two_is_negative ? arg[1] : arg[0];
				number_two_significant_digits = (int)(number_two_is_negative ? strlen(arg) - 2 : strlen(arg) - 1);
				k = number_two_is_negative ? 2 : 1;
				number_two = malloc(number_two_significant_digits+1);
				number_two[number_two_significant_digits] = '\0';
				j = 0;
                
				for (; k < strlen(arg); k++) {
					char current_digit = arg[k];
					number_two[j] = current_digit;
					j++;
				}
                
				number_two[j] = '\0';
                
				break;
			case 4:
				output_base = arg[0];
				break;
			default:
				fprintf(stderr, "%s", "you inputted too many arguments");
				return 1;
		}
	}
    
	/* Let's find out if I did that right */
	if (DEVELOPMENT) {
		printf("\t-   Number one: %s\n", number_one);
		printf("\t\t-   is negative: %i\n\t\t-   base: %c\n\t\t-   significant digits: %i\n", number_one_is_negative, number_one_base_char, number_one_significant_digits);
        
		printf("\t-   Number two: %s\n", number_two);
		printf("\t\t-   is negative: %i\n\t\t-   base: %c\n\t\t-   significant digits: %i\n", number_two_is_negative, number_two_base_char, number_two_significant_digits);
	}
    
	/* Looks good */
	/* Right now let's do the actual work */
	tmp = number_one;
	switch (number_one_base_char) {
		case 'b':
			break;
		case 'o':
			number_one = oct_to_bin(number_one);
			break;
		case 'd':
			number_one = dec_to_bin(number_one);
			break;
		case 'h':
		case 'x':
			number_one = hex_to_bin(number_one);
			break;
		default:
			fprintf(stderr, "you inputted a base that I do not recognize\n");
	}
    
	tmp = number_two;
	switch (number_two_base_char) {
		case 'b':
			break;
		case 'o':
			number_two = oct_to_bin(number_two);
			break;
		case 'd':
			number_two = dec_to_bin(number_two);
			break;
		case 'h':
		case 'x':
			number_two = hex_to_bin(number_two);
			break;
		default:
			fprintf(stderr, "you inputted a base that I do not recognize\n");
	}
	
    number_one_is_greater = first_is_greater(number_one, number_two);
	number_two_is_greater = first_is_greater(number_two, number_one);
    
	if (DEVELOPMENT) {
		printf("\t-   first_is_greater: %i\n", number_one_is_greater);
		printf("\t-   secon_is_greater: %i\n", number_two_is_greater);
	}
    
	/* At this point you can assume you have two
	 * valid binary representations of your two numbers
	 * They will be of the same length */
    
	if (strlen(number_one) > strlen(number_two)) {
		number_two = pad_bin(number_two, (int)strlen(number_one));
	} else if (strlen(number_two) > strlen(number_one)) {
		number_one = pad_bin(number_one, (int)strlen(number_two));
	}
    
	if (DEVELOPMENT) {
		printf("\t-   %iNumber one binary: \n\t\t%s\n", (int)strlen(number_one), number_one);
		printf("\t-   %iNumber two binary: \n\t\t%s\n", (int)strlen(number_two), number_two);
	}
    
	if (output_operation == '+') {
        if (number_one_is_negative && number_two_is_negative) {
            if (DEVELOPMENT) {printf("both are negative and you're adding, so add and make it negative.\n");}
            output = bin_add(number_one, number_two);
            output_is_negative = true;
        } else if (!number_one_is_negative && !number_two_is_negative) {
            if (DEVELOPMENT) {printf("Neither are negative and you're adding, so I add and do not display as negative.\n");}
			output = bin_add(number_one, number_two);
		} else if (number_one_is_negative) {
            if (!number_one_is_greater && !number_two_is_greater) {
                if (DEVELOPMENT) {printf("Neither has a greater absolute value and number one is negative, output is zero. \n");}
				output = strdup("0");
				output_is_negative = false;
			} else if (number_two_is_greater) {
                if (DEVELOPMENT) {printf("Number two has a greater absolute value and number one is negative, so output is subtraction displayed negative");}
                number_one = flip_da_bits(number_one);
				number_one = bin_add(pad_bin("1", (int)strlen(number_one)), number_one);
				output = bin_add(number_one, number_two);
				output[0] = '0';
				output_is_negative = false;
            } else if (number_one_is_greater) {
                if (DEVELOPMENT) {printf("Number one has a greater absolute value and number one is negative, output is number one minus number two displayed negative.\n");}
                number_two = flip_da_bits(number_two);
                number_two = bin_add(pad_bin("1", (int)strlen(number_two)), number_two);
                output = bin_add(number_one, number_two);
                output[0] = '0';
                output_is_negative = true;
            }
		} else if (number_two_is_negative) {
            if (DEVELOPMENT) {printf("Number two is negative, ");}
			if (!number_one_is_greater && !number_two_is_greater) {
                if (DEVELOPMENT) {printf("and neither is greater in value, output zero.\n");}
				output = strdup("0");
				output_is_negative = false;
			} else if (number_one_is_greater) {
                if (DEVELOPMENT) {printf("and number one is greater in value, subtract two from one and display negative");}
				number_two = flip_da_bits(number_two);
                number_two = bin_add(pad_bin("1", (int)strlen(number_two)), number_two);
                output = bin_add(number_one, number_two);
                output[0] = '0';
                output_is_negative = false;
			} else if (number_two_is_greater) {
                if (DEVELOPMENT) {printf("and number two is greater in value");}
				number_one = flip_da_bits(number_one);
				number_one = bin_add(pad_bin("1", (int)strlen(number_one)), number_one);
				output = bin_add(number_two, number_one);
				output[0] = '0';
				output_is_negative = true;
			}
		} 
	} else if (output_operation == '-') {
        if (DEVELOPMENT) {printf("The operation is subtraction");}
        if (number_one_is_negative && number_two_is_negative) {
            if (DEVELOPMENT) {printf(", and both numbers ares negative");}
            if (!number_one_is_greater && !number_two_is_greater) {
                if (DEVELOPMENT) {printf(", but neither number has a greater absolute value, so zero.\n");}
                output = strdup("0");
                output_is_negative = false;
            } else if (number_one_is_greater) {
                if (DEVELOPMENT) { printf(", and number one is greater.");}
                number_two = flip_da_bits(number_two);
                number_two = bin_add(pad_bin("1", (int)strlen(number_two)), number_two);
                output = bin_add(number_one, number_two);
                output[0] = '0';
                output_is_negative = true;
            } else if (number_two_is_greater) {
                number_one = flip_da_bits(number_one);
				number_one = bin_add(pad_bin("1", (int)strlen(number_one)), number_one);
				output = bin_add(number_two, number_one);
				output[0] = '0';
				output_is_negative = false;
            }
        } else if (!number_one_is_negative && !number_two_is_negative) {
			if (DEVELOPMENT) { printf("sub, neither are negative\n"); }
			if (!number_one_is_greater && !number_two_is_greater) {
				output = strdup("0");
				output_is_negative = false;
			} else if (number_one_is_greater) {
				number_two = flip_da_bits(number_two);
				number_two = bin_add(pad_bin("1", (int)strlen(number_two)), number_two);
				output = bin_add(number_one, number_two);
				output[0] = '0';
				output_is_negative = false;
			} else if (number_two_is_greater) {
				number_one = flip_da_bits(number_one);
				number_one = bin_add(pad_bin("1", (int)strlen(number_one)), number_one);
				output = bin_add(number_two, number_one);
				output[0] = '0';
				output_is_negative = true;
			}
		} else if (number_one_is_negative) {
			output = bin_add(number_one, number_two);
			output_is_negative = true;
		} else if (number_two_is_negative) {
			output = bin_add(number_one, number_two);
			output_is_negative = false;
		}
	}
    
	/* Right, now we should have
     a binary number that has been
     succesfully added or subtracted.
     
     Time to convert it back to what you want. */
    
	if (DEVELOPMENT) {
		printf("\t-   Binary number after operation: \n\t\t%s\n", output);
	}
	tmp = output;
	switch (output_base) {
		case 'b':
			break;
		case 'o':
			output = bin_to_even_base(output, 3);
			break;
		case 'd':
			if (output_is_negative)
				printf("%c", '-');
			printf("%c", output_base);
			bin_to_dec(output);
			break;
		case 'h':
			output = bin_to_even_base(output, 4);
			break;
		default:
			fprintf(stderr, "you inputted a base that I do not recognize\n");
	}
	if (output_base != 'd') {
		if (output_is_negative)
			printf("%c", '-');
        
		printf("%c", output_base);
        
		printf("%s\n", output);
	}

    
	return 0;
}


char * bin_add (char * bin_one, char * bin_two) {
	int i;
	bool shouldCarry;
    
	char * bin_added = malloc(strlen(bin_two) + 1 + 1);
	bin_added[strlen(bin_two)] = '\0';
	i = (int)strlen(bin_two) - 1;
	shouldCarry = false;
	memset(bin_added,0,strlen(bin_two)+1+1);
    
	if (DEVELOPMENT) {
		printf("-   bin_add(%s, %s) %li, %i\n", bin_one, bin_two, strlen(bin_two) + 1, (int)strlen(bin_added));
	}
    
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

char * oct_to_bin (char * oct) {
	char * bin = malloc(strlen(oct) * 3 +1);
	int i = 0;
	memset(bin,0,strlen(oct)*3+1);
    
	for (i = 0; i < strlen(oct); i++) {
		bin = strcat(bin, single_digit_oct_to_bin(oct[i]));
	}
    
	return bin;
}

char * hex_to_bin (char * hex) {
	char * bin = malloc(strlen(hex) * 4+1);
	int i = 0;
	bin[strlen(hex)*4] = '\0';
	if (DEVELOPMENT)
		printf("-   `hex_to_bin(%s)`\n", hex);
    
	for (i = 0; i < strlen(hex); i++) {
		if (DEVELOPMENT)
			printf("\t-   `hex[%i] = %c -> %s`\n",i, hex[i],single_digit_hex_to_bin(hex[i]));
		bin = strcat(bin, single_digit_hex_to_bin(hex[i]));
	}
    
	return bin;
}

char * dec_to_bin (char * dec) {
	int i;
	int k;
	int j = 0;
	int n = atoi(dec);
	char * bin = malloc(32+1);
	bool leadingZeros = true;
	bin[32] = '\0';
	for (i = 31; i >= 0; i--) {
		k = n >> i;
        
		if (k & 1) {
			bin[j] = '1';
			j++;
			leadingZeros = false;
		} else if (!leadingZeros) {
			bin[j] = '0';
			j++;
		}
	}
    
	bin[j] = '\0';
    
	return bin;
}

int parse_int(const char *s,int *i)
{
	char *ep;
	long l;
    
	l=strtol(s,&ep,0);
    
	if(*ep!=0)
		return 0;
    
	*i=(int)l;
	return 1;
}

void bin_to_dec (char * bin) {
	int i = 0;
	int power = (int)strlen(bin) - 1;
	long double value = 0;
    
	for (i = 0; i < (int)strlen(bin); i++) {
        
		if (bin[i] == '1') {
			value += pow(2, power);
		}
        
		power--;
	}
    
	printf("%.0Lf\n", value);
}

char * bin_to_even_base (char * bin, int size_of_digit) {
	int offset = 0;
	int i = 0;
	int j = 4;
	int k = 0;
	int number_of_hex_digits = 0;
	char* substr;
	char * out;
	int r = 0;
    
    
	while(((strlen(bin) + offset) % size_of_digit) != 0) {
		offset++;
	}
    
	out = malloc((strlen(bin) + offset) / size_of_digit+1);
	out[(strlen(bin)+offset)/size_of_digit] = '\0';
    
	r = (int)strlen(bin) + offset;
	
	bin = pad_bin(bin, r);
	number_of_hex_digits = (int)strlen(bin)/size_of_digit;
    
	if (DEVELOPMENT) {
		printf("-   `bin_to_hex(%s)`, (`number_of_hex_digits = %i`)\n", bin,number_of_hex_digits);
	}
    
	while (k < number_of_hex_digits) {
		substr = strndup(bin+i, j);
		substr[size_of_digit] = '\0';
        
		if (DEVELOPMENT)
			printf("\t-   Subtring from `%i` to `%i`: `%s`, Counter: %i\n", i, j, substr, k);
        
		i = i + size_of_digit;
		j = j + size_of_digit;
        
		if (size_of_digit == 4) {
			out[k] = single_digit_bin_to_hex(substr);
		} else if (size_of_digit == 3) {
			out[k] = single_digit_bin_to_oct(substr);
		}
		free(substr);
		k++;
	}
	free(bin);
	out[k] = '\0';
	return out;
}

char single_digit_bin_to_oct (char * bin_dig) {
	if (strcmp(bin_dig, "000") == 0) {
		return '0';
	} else if (strcmp(bin_dig, "001") == 0) {
		return '1';
	} else if (strcmp(bin_dig, "010") == 0) {
		return '2';
	} else if (strcmp(bin_dig, "011") == 0) {
		return '3';
	} else if (strcmp(bin_dig, "100") == 0) {
		return '4';
	} else if (strcmp(bin_dig, "101") == 0) {
		return '5';
	} else if (strcmp(bin_dig, "110") == 0) {
		return '6';
	} else {
		return '7';
	}
}

char single_digit_bin_to_hex (char *bin_dig) {
	if (DEVELOPMENT) {
		printf("-   `single_digit_hex_to_bin(%s)` returned `", bin_dig);
	}
    
	if (strcmp(bin_dig, "0000") == 0) {
		if (DEVELOPMENT) {
			printf("0`\n");
		}
        
		return '0';
	} else if (strcmp(bin_dig, "0001") == 0) {
		if (DEVELOPMENT) {
			printf("1`\n");
		}
        
		return '1';
	} else if (strcmp(bin_dig, "0010") == 0) {
		if (DEVELOPMENT) {
			printf("2`\n");
		}
        
		return '2';
	} else if (strcmp(bin_dig, "0011") == 0) {
		if (DEVELOPMENT) {
			printf("3`\n");
		}
        
		return '3';
	} else if (strcmp(bin_dig, "0100") == 0) {
		if (DEVELOPMENT) {
			printf("4`\n");
		}
        
		return '4';
	} else if (strcmp(bin_dig, "0101") == 0) {
		if (DEVELOPMENT) {
			printf("5`\n");
		}
        
		return '5';
	} else if (strcmp(bin_dig, "0110") == 0) {
		if (DEVELOPMENT) {
			printf("6`\n");
		}
        
		return '6';
	} else if (strcmp(bin_dig, "0111") == 0) {
		if (DEVELOPMENT) {
			printf("7`\n");
		}
        
		return '7';
	} else if (strcmp(bin_dig, "1000") == 0) {
		if (DEVELOPMENT) {
			printf("8`\n");
		}
        
		return '8';
	} else if (strcmp(bin_dig, "1001") == 0) {
		if (DEVELOPMENT) {
			printf("9`\n");
		}
        
		return '9';
	} else if (strcmp(bin_dig, "1010") == 0) {
		if (DEVELOPMENT) {
			printf("A`\n");
		}
        
		return 'A';
	} else if (strcmp(bin_dig, "1011") == 0) {
		if (DEVELOPMENT) {
			printf("B`\n");
		}
        
		return 'B';
	} else if (strcmp(bin_dig, "1100") == 0) {
		if (DEVELOPMENT) {
			printf("C`\n");
		}
        
		return 'C';
	} else if (strcmp(bin_dig, "1101") == 0) {
		if (DEVELOPMENT) {
			printf("D`\n");
		}
        
		return 'D';
	} else if (strcmp(bin_dig, "1110") == 0) {
		if (DEVELOPMENT) {
			printf("E`\n");
		}
        
		return 'E';
        
        
	} else if (strcmp(bin_dig, "1111") == 0){
		if (DEVELOPMENT) {
			printf("F`\n");
		}
        
		return 'F';
	} else {
		fprintf(stderr, "inputted a non-hex digit to single_digit_hex_to_bin");
		return 'X';
	}
}
/* 0010 0111 0111 0100 */
/* 2      7    7   4 */

char single_digit_bin_to_dec (char *dec_dig) {
	if (strcmp(dec_dig, "0001") == 0) {
		return '1';
	} else if (strcmp(dec_dig, "0010") == 0) {
		return '2';
	} else if (strcmp(dec_dig, "0011") == 0) {
		return '3';
	} else if (strcmp(dec_dig, "0100") == 0) {
		return '4';
	} else if (strcmp(dec_dig, "0101") == 0) {
		return '5';
	} else if (strcmp(dec_dig, "0110") == 0) {
		return '6';
	} else if (strcmp(dec_dig, "0111") == 0) {
		return '7';
	} else if (strcmp(dec_dig, "1000") == 0) {
		return '8';
	} else {
		return '9';
	}
}

char * single_digit_oct_to_bin (char oct_dig) {
	switch (oct_dig) {
		case '0':
			return "000";
			break;
		case '1':
			return "001";
			break;
            
		case '2':
			return "010";
			break;
            
		case '3':
			return "011";
			break;
            
		case '4':
			return "100";
			break;
            
		case '5':
			return "101";
			break;
            
		case '6':
			return "110";
			break;
            
		case '7':
			return "111";
			break;
            
		default:
			fprintf(stderr, "you inputted a non-digit character in one of your number string");
			return "";
			break;
	}
}

char * single_digit_hex_to_bin (char hex_dig) {
    
	switch (hex_dig) {
		case '0':
			return "0000";
			break;
		case '1':
			return "0001";
			break;
            
		case '2':
			return "0010";
			break;
            
		case '3':
			return "0011";
			break;
            
		case '4':
			return "0100";
			break;
            
		case '5':
			return "0101";
			break;
            
		case '6':
			return "0110";
			break;
            
		case '7':
			return "0111";
			break;
            
		case '8':
			return "1000";
			break;
            
		case '9':
			return "1001";
			break;
		case 'A':
		case 'a':
			return "1010";
			break;
		case 'B':
		case 'b':
			return "1011";
			break;
		case 'C':
		case 'c':
			return "1100";
			break;
		case 'D':
		case 'd':
			return "1101";
			break;
		case 'E':
		case 'e':
			return "1110";
			break;
		case 'F':
		case 'f':
			return "1111";
			break;
		default:
			fprintf(stderr, "you inputted a non-digit character in one of your number string");
			return "";
			break;
	}
}
