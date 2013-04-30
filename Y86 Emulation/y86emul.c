/*
 * Paul Jones
 * Professor Brian Russel
 * Computer Architecture
 * April 16th, 2013
 *
 * y86emul.c
 *
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "y86emul.h"
#include "hex_converting.h"

char * strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);
    if (d == NULL) return NULL;
    strcpy (d,s);
    return d;
}

char * substr(const char *inpStr, char *outStr, size_t startPos, size_t strLen) {
	strncpy(outStr, inpStr + startPos, strLen);
	outStr[strLen] = '\0';
	return outStr;
}

char * file_to_string(const char * filename) {
	char * buffer = 0;
	long length;
	FILE * f = fopen (filename, "rb");
	
	if (f) {
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = malloc (length);
		
		if (buffer) {
			fread (buffer, 1, length, f);
		}
		
		fclose (f);
	} else {
		printf("That file does not exist.\n");
	}
	
	if (buffer) {
		return buffer;
	} else {
		printf("There is something wrong with your program (perhaps it's empty). \n");
		return "";
	}
}

int execute_loaded_memory(unsigned char * bytes, cpu * cpu) {
	
	while(cpu->program_counter < cpu->size) {
		switch (bytes[cpu->program_counter]) {
			case 0x00: /* nop */
				cpu->program_counter++;
				break; /* done */
			case 0x10: /* halt */
				fprintf(stderr, HLT);
				return 0;
				break; /* done */
			case 0x20: /* rrmovl */
				break;
			case 0x30: /* irmovl */
				break;
			case 0x40: /* rmmovl */
				break;
			case 0x50: /* mrmovl */
				break;
			case 0x60: /* addl */
				break;
			case 0x61: /* subl */
				break;
			case 0x62: /* andl */	
				break;
			case 0x63: /* xorl */
				break;
			case 0x70: /* jmp */
				break;
			case 0x71: /* jle */
				break;
			case 0x72: /* jl */
				break;
			case 0x73: /* je */
				break;
			case 0x74: /* jne */
				break;
			case 0x75: /* jge */
				break;
			case 0x76: /* jg */
				break;
			case 0x80: /* call */
				break;
			case 0x90: /* ret */
				break;
			case 0xa0: /* pushl */
				break;
			case 0xb0: /* popl */
				break;
			default:
				cpu->program_counter++;
				break;
		}
	}

	return 0;
}

int process_program(char * program) {
	char * dup = strdup(program);
	char * tok = strtok(dup, "\t\n");

	int size; /* will store the size directive */

	int i; /* used for counters */
	int j; 

	char * directive; /* every time I get a directive, I store it in this. */
	char * hex_address; /* every time I get a hex address, I store it in this. */
	char * argument; /* every time I get an argument, I store it in this. */

	int long_argument;

	char * sub_argument;

	cpu * cpu; /* this struct represents my cpu, with registers and all */
	unsigned char * bytes; /* this is an array of integer values representing instructions and values */

	/*
	 * Find size directive
	 */
	while (tok) {
		if (strcmp(tok, ".size") == 0) {
			tok = strtok(NULL, "\t\n");
			size = hex_to_dec(tok);
		} else {
			tok = strtok(NULL, "\t\n");
		}
	}

	free(dup);

	/*
	 * Load into memory
	 */

	cpu = malloc(sizeof *cpu);

	cpu->program_counter = -1;
	cpu->size = size;

	bytes = malloc((size + 1) * sizeof(unsigned char));

	for (i = 0; i < size; i++) {
		bytes[i] = 0;
	}

	dup = strdup(program );
	tok = strtok(dup, "\t\n");

	i = 0;

	while (tok) {
		if (strcmp(tok, ".size") == 0) {
			tok = strtok(NULL, "\t\n"); /* skip .size directive */
			tok = strtok(NULL, "\t\n"); /* skip .size argument */
		} else if (strcmp(tok, ".string") == 0 || 
				strcmp(tok, ".long") == 0 || 
				strcmp(tok, ".bss") == 0 || 
				strcmp(tok, ".byte") == 0 || 
				strcmp(tok, ".text") == 0) { /* if it's a valid command: */

			directive = strdup(tok); /* get directive */
			tok = strtok(NULL, "\n\t"); /* move past directive */

			hex_address = strdup(tok); /* for the hex address */
			tok = strtok(NULL, "\n\t"); /* move past the hex address */

			argument = strdup(tok); /* the actual string itself */
			tok = strtok(NULL, "\n\t"); /* to move past the string */

			if (strcmp(directive, ".string") == 0) {
				i = hex_to_dec(hex_address);
				j = 1;

				while (j < strlen(argument) - 1) {
					bytes[i] = (unsigned char) argument[j];

					i++;
					j++;
				}
			} else if ( strcmp(directive, ".text") == 0) { 
				i = hex_to_dec(hex_address);
				j = 0;
				
				if (cpu->program_counter == -1) {
					cpu->program_counter = i;
				} else if (cpu->program_counter != -1) {
					fprintf(stderr, INS);
					return 1;
				}

				while (j < strlen(argument)) {
					/* in substrings of length 2 from 0 to n */
					sub_argument = substr(argument, sub_argument, j, 2);
					/* convert it to decimal */
					bytes[i] = (unsigned char) hex_to_dec(sub_argument);

					i++;
					j = j + 2;
				}
			} else if (strcmp(directive, ".bss") == 0) { /* .bss directive */
				i = atoi(argument); /* in decimal */
				j = hex_to_dec(hex_address); /* in hex */

				for (; i > 0; i--) {
					bytes[j] = (unsigned char)0; /* make them all zeroes! */
					j++;
				}
			} else if (strcmp(directive, ".long") == 0) { /* .long directive */
				long_argument = atoi(argument);
				j = hex_to_dec(hex_address);
				*(unsigned int*)(bytes+j) = long_argument;
				/*(unsigned int*)(bytes+j) = (((long_argument & 0xff000000) >> 24) | ((long_argument & 0x00ff0000) >> 8) | ((long_argument & 0x0000ff00) << 8) | ((long_argument & 0x000000ff) << 24)); */
/*				bytes[j + 3] = (long_argument & 0xff000000) >> 24;
				bytes[j + 2] = (long_argument & 0x00ff0000) >> 16;
				bytes[j + 1] = (long_argument & 0x0000ff00) >> 8 ;
				bytes[j + 0] = (long_argument & 0x000000ff);*/

			} else if (strcmp(directive, ".byte") == 0) { /* .byte directive */
				bytes[hex_to_dec(hex_address)] = (unsigned char)hex_to_dec(argument);
			}

			free(hex_address); /* free the stuff we're done with */
			free(argument);
			free(directive);
			hex_address = 0; 
		} else {
			fprintf(stderr, INS); /* if an unknown directive is found */
			return 1;
		}
	}

	free(dup);
	free(tok);
	
	for (i = 0; i < 0x30; i++) {
		printf("%x\t%x\n", i, (int)bytes[i]);
	} 

	return execute_loaded_memory(bytes, cpu); 
}

int main(int argc, const char * argv[]) {
	return process_program(file_to_string(argv[1]));
}
