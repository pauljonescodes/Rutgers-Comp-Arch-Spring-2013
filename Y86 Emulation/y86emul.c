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

int execute_loaded_memory(char * bytes, cpu * cpu) {
	return 0;
}

int process_program(char * program) {
	char * dup = strdup(program);
	char * tok = strtok(dup, "\t\n");

	int size;

	int i; /* used for counters */
	int j; 

	char * directive; /* every time I get a directive, I store it in this. */
	char * hex_address; /* every time I get a hex address, I store it in this. */
	char * argument; /* every time I get an argument, I store it in this. */

	char * sub_argument;

	cpu * cpu; /* this struct represents my cpu, with registers and all */
	char * bytes; /* this is an array of integer values representing instructions and values */

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

	size = (size / 8);
	bytes = malloc(size * sizeof *bytes);

	for (; i > 0; i--) {
		bytes[j] = (char)0;
		j++;
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

			if (strcmp(directive, ".string") == 0 || 
				strcmp(directive, ".text") == 0) { /* string and texts are the same, 
								    * but one gets the program counter */
				i = hex_to_dec(hex_address);
				j = 0;

				if (cpu->program_counter == -1 && strcmp(directive, ".text") == 0) {
					cpu->program_counter = i;
					printf("%i\n", i);
				}

				while (j < strlen(argument)) {
					/* in substrings of length 2 from 0 to n */
					sub_argument = substr(argument, sub_argument, j, 2);
					/* convert it to decimal */
					bytes[i] = (char)hex_to_dec(sub_argument);
					
					i++;
					j = j + 2;
				}
			} else if (strcmp(directive, ".bss") == 0) { /* .bss directive */
				i = atoi(argument); /* in decimal */
				j = hex_to_dec(hex_address); /* in hex */

				for (; i > 0; i--) {
					bytes[j] = (char)0; /* make them all zeroes! */
					j++;
				}
			} else if (strcmp(directive, ".long") == 0) { /* .long directive */
				bytes[hex_to_dec(hex_address)] = (char)atoi(argument);
			} else if (strcmp(directive, ".byte") == 0) { /* .byte directive */
				bytes[hex_to_dec(hex_address)] = (char)hex_to_dec(argument);
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
	
	for (i = 0; i < size; i++) {
		printf("%i %i \n", i, (int)bytes[i]);
	}

	return execute_loaded_memory(bytes, cpu);
}

int main(int argc, const char * argv[]) {
	char * program = file_to_string(argv[1]);
	return process_program(program);
}
