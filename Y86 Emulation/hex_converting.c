#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hex_converting.h"

int single_digit_hex_to_dec(char hex_dig) {
	switch (hex_dig) {
		case '0':
			return 0;
			break;
		case '1':
			return 1;
			break;
            
		case '2':
			return 2;
			break;
            
		case '3':
			return 3;
			break;
            
		case '4':
			return 4;
			break;
            
		case '5':
			return 5;
			break;
            
		case '6':
			return 6;
			break;
            
		case '7':
			return 7;
			break;
            
		case '8':
			return 8;
			break;
            
		case '9':
			return 9;
			break;
		case 'A':
		case 'a':
			return 10;
			break;
		case 'B':
		case 'b':
			return 11;
			break;
		case 'C':
		case 'c':
			return 12;
			break;
		case 'D':
		case 'd':
			return 13;
			break;
		case 'E':
		case 'e':
			return 14;
			break;
		case 'F':
		case 'f':
			return 15;
			break;
		default:
			fprintf(stderr, "you inputted a non-digit character in one of your number string \n");
			return 0;
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
			fprintf(stderr, "you inputted a non-digit character in one of your number string \n");
			return "";
			break;
	}
}

char * hex_to_bin (char * hex) {
	char * bin = malloc(strlen(hex) * 4+1);
	int i = 0;
	bin[strlen(hex)*4] = '\0';
    
	for (i = 0; i < strlen(hex); i++) {
		bin = strcat(bin, single_digit_hex_to_bin(hex[i]));
	}
    
	return bin;
}

int bin_to_dec (char * bin) {
	int i = 0;
	int power = (int)strlen(bin) - 1;
	int value = 0;
    
	for (i = 0; i < (int)strlen(bin); i++) {
        
		if (bin[i] == '1') {
			value += (int)pow(2, power);
		}
        
		power--;
	}
    
	return value;
}

int hex_to_dec(char * hex) { 
	char * bin = hex_to_bin(hex);
	return bin_to_dec(bin);
}
