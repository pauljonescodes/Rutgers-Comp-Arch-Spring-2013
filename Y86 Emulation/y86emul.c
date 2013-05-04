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

#define DEVELOPMENT false

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
	
	unsigned char one;
	unsigned char two;

	char in;
	int iin;
	
	int  val;
	unsigned int  dst;

	cpu->cont = true;

	while(cpu->cont) {
		switch (bytes[cpu->program_counter]) {

			case 0x00: /* nop */
				if (DEVELOPMENT) 
					printf("%x\tnop\n", cpu->program_counter);

				cpu->program_counter++;
				break; 
			case 0x10: /* halt */
				printf(HLT);
				printf(AOK);
				cpu->cont = false;
				return 0;
				break; 
			case 0x20: /* rrmovl */
				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);
				
				if (DEVELOPMENT) {
					printf("%x\trrmovl", cpu->program_counter);
					printf("\trA:%x\trB:%x\n", one, two);
				}

				cpu->registers[two] = cpu->registers[one];

				cpu->program_counter += 2;

				break;
			case 0x30: /* irmovl */

				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);

				val =    bytes[cpu->program_counter + 2] 
				      + (bytes[cpu->program_counter + 3] << 8)
				      + (bytes[cpu->program_counter + 4] << 16)
				      + (bytes[cpu->program_counter + 5] << 24);

				if (DEVELOPMENT) { 
					printf("%x\tirmovl", cpu->program_counter);
					printf("\tf:%x\trB:%x\tV:%x\n", one, two, val);
				}

				cpu->registers[two] = val;

				cpu->program_counter += 6;

				break;
			case 0x40: /* rmmovl */
				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);
				
				dst =    bytes[cpu->program_counter + 2] 
				      + (bytes[cpu->program_counter + 3] << 8)
				      + (bytes[cpu->program_counter + 4] << 16)
				      + (bytes[cpu->program_counter + 5] << 24);

				if (DEVELOPMENT) {
					printf("%x\trmmvol", cpu->program_counter);
					printf("\trA:%x\trB:%x\tD:%x\n", one, two, dst);
				}

				bytes[two + dst] = one;

				cpu->program_counter += 6;

				break;
			case 0x50: /* mrmovl */
				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);
				
				dst =    bytes[cpu->program_counter + 2] 
				      + (bytes[cpu->program_counter + 3] << 8)
				      + (bytes[cpu->program_counter + 4] << 16)
				      + (bytes[cpu->program_counter + 5] << 24);

				if (DEVELOPMENT) {
					printf("%x\tmrmovl", cpu->program_counter);
					printf("\trA:%x\trB:%x\tD:%x\n", one, two, dst);
				}

				cpu->registers[one] = bytes[cpu->registers[two] + dst];
			
				cpu->program_counter += 6;

				break;
			case 0x60: /* addl */
				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);

				cpu->overflow = false;
				cpu->negative = false;
				cpu->zero     = false;

				val = cpu->registers[one] + cpu->registers[two];

				if ((cpu->registers[one] > 0 && cpu->registers[two] > 0 && val < 0) || 
					(cpu->registers[one] < 0 && cpu->registers[two] < 0 && val > 0)) {
					cpu->overflow = true;
				}

				if (val == 0) {
					cpu->zero = true;
				}

				if (val < 0) {
					cpu->negative = true;
				}

				if (DEVELOPMENT) {
					printf("%x\taddl", cpu->program_counter);
					printf("\trA:%x\trB:%x", one, two);
					printf("\t(%i = %i + %i (%i))\n", val, cpu->registers[one], cpu->registers[two], cpu->overflow);
				}

				cpu->registers[two] = val;
				cpu->program_counter += 2;

				break;
			case 0x61: /* subl */
				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);

				cpu->overflow = false;
				cpu->negative = false;
				cpu->zero     = false;

				val = cpu->registers[two] - cpu->registers[one];

				if ((cpu->registers[one] < 0 && cpu->registers[two] > 0 && val < 0) || 
					(cpu->registers[one] > 0 && cpu->registers[two] < 0 && val > 0))
					cpu->overflow = true;

				if (val == 0) {
					cpu->zero = true;
				}

				if (val < 0) {
					cpu->negative = true;
				}

				if (DEVELOPMENT) {
					printf("%x\tsubl", cpu->program_counter);
					printf("\trA:%x\trB:%x", one, two);
					printf("\t(%i = %i - %i (%i))\n", val, cpu->registers[one], cpu->registers[two], cpu->overflow);
				}

				cpu->registers[two] = val;
				cpu->program_counter += 2;

				break;
			case 0x62: /* imull */	
				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);

				cpu->overflow = false;
				cpu->negative = false;
				cpu->zero     = false;

				val = cpu->registers[one] - cpu->registers[two];

				if ((cpu->registers[one] > 0 && cpu->registers[two] > 0 && val < 0) ||
					(cpu->registers[one] < 0 && cpu->registers[two] < 0 && val < 0) ||
					(cpu->registers[one] < 0 && cpu->registers[two] > 0 && val > 0)) {
					cpu->overflow = true;
				}

				if (val == 0) {
					cpu->zero = true;
				}

				if (val < 0) {
					cpu->negative = true;
				}

				if (DEVELOPMENT) {
					printf("%x\timull", cpu->program_counter);
					printf("\trA:%x\trB:%x", one, two);
					printf("\t(%i = %i * %i (%i))\n", val, cpu->registers[one], cpu->registers[two], cpu->overflow);
				}

				cpu->registers[two] = cpu->registers[one] * cpu->registers[two];
				cpu->program_counter += 2;

				break;
			case 0x63: /* xorl */
				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);

				if (DEVELOPMENT) {
					printf("%x\txorl", cpu->program_counter);
					printf("\trA:%x\trB:%x\n", one, two);
				}

				cpu->program_counter += 2;

				break;
			case 0x70: /* jmp */
				dst =    bytes[cpu->program_counter + 1] 
				      + (bytes[cpu->program_counter + 2] << 8)
				      + (bytes[cpu->program_counter + 3] << 16)
				      + (bytes[cpu->program_counter + 4] << 24);

				if (DEVELOPMENT) {
					printf("%x\tjmp\tD:%x\n", cpu->program_counter, dst);
				}

				cpu->program_counter = dst;

				break;
			case 0x71: /* jle */
				dst =    bytes[cpu->program_counter + 1] 
				      + (bytes[cpu->program_counter + 2] << 8)
				      + (bytes[cpu->program_counter + 3] << 16)
				      + (bytes[cpu->program_counter + 4] << 24);

				if (DEVELOPMENT) 
					printf("%x\tjle\tD:%x\n", cpu->program_counter, dst);

				if (cpu->negative != cpu->overflow || cpu->zero)
					cpu->program_counter = dst;
				else
					cpu->program_counter += 5;

				break;
			case 0x72: /* jl */
				dst =    bytes[cpu->program_counter + 1] 
				      + (bytes[cpu->program_counter + 2] << 8)
				      + (bytes[cpu->program_counter + 3] << 16)
				      + (bytes[cpu->program_counter + 4] << 24);

				if (DEVELOPMENT) 
					printf("%x\tjl\tD:%x\n", cpu->program_counter, dst);
				
				if (cpu->negative != cpu->overflow)
					cpu->program_counter = dst;
				else
					cpu->program_counter += 5;

				break;
			case 0x73: /* je */		
				dst =    bytes[cpu->program_counter + 1] 
				      + (bytes[cpu->program_counter + 2] << 8)
				      + (bytes[cpu->program_counter + 3] << 16)
				      + (bytes[cpu->program_counter + 4] << 24);

				if (DEVELOPMENT) 
					printf("%x\tje\tD:%x\n", cpu->program_counter, dst);

				if (cpu->zero)
					cpu->program_counter = dst;
				else
					cpu->program_counter += 5;

				break;
			case 0x74: /* jne */
				dst =    bytes[cpu->program_counter + 1] 
				      + (bytes[cpu->program_counter + 2] << 8)
				      + (bytes[cpu->program_counter + 3] << 16)
				      + (bytes[cpu->program_counter + 4] << 24);

				if (DEVELOPMENT) 
					printf("%x\tjne\tD:%x\n", cpu->program_counter, dst);

				if (!cpu->zero)
					cpu->program_counter = dst;
				else
					cpu->program_counter += 5;

				break;
			case 0x75: /* jge */
				dst =    bytes[cpu->program_counter + 1] 
				      + (bytes[cpu->program_counter + 2] << 8)
				      + (bytes[cpu->program_counter + 3] << 16)
				      + (bytes[cpu->program_counter + 4] << 24);

				if (DEVELOPMENT) 
					printf("%x\tjge\tD:%x\n", cpu->program_counter, dst);

				if (cpu->negative == cpu->overflow)
					cpu->program_counter = dst;
				else
					cpu->program_counter += 5;

				break;
			case 0x76: /* jg */
				dst =    bytes[cpu->program_counter + 1] 
				      + (bytes[cpu->program_counter + 2] << 8)
				      + (bytes[cpu->program_counter + 3] << 16)
				      + (bytes[cpu->program_counter + 4] << 24);

				if (DEVELOPMENT) 
					printf("%x\tjg\tD:%x\n", cpu->program_counter, dst);

				if (cpu->negative == cpu->overflow && !cpu->zero)
					cpu->program_counter = dst;
				else
					cpu->program_counter += 5;

				break;
			case 0x80: /* call */
				dst =    bytes[cpu->program_counter + 1] 
				      + (bytes[cpu->program_counter + 2] << 8)
				      + (bytes[cpu->program_counter + 3] << 16)
				      + (bytes[cpu->program_counter + 4] << 24);

				if (DEVELOPMENT) 
					printf("%x\tcall\tD:%x\t%x", cpu->program_counter, dst,cpu->registers[ESP]);

				cpu->registers[ESP] -= 4;
				iin = cpu->program_counter + 5; 
				val = 0;
				for (; val < 4; val++) {
					bytes[cpu->registers[ESP] + dst + val] = iin % 256;
					iin /= 256;
				}

				if (DEVELOPMENT)
					printf("\t%x\n", bytes[cpu->registers[ESP]]);

				cpu->program_counter = dst;

				break;
			case 0x90: /* ret */
				if (DEVELOPMENT) 
					printf("%x\tret\t%x\n", cpu->program_counter, bytes[cpu->registers[ESP - 4]]);

				cpu->program_counter = bytes[cpu->registers[ESP]];
				cpu->registers[ESP] += 4;

				break;
			case 0xa0: /* pushl */
				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);

				if (DEVELOPMENT) {
					printf("%x\tpushl", cpu->program_counter);
					printf("\trA:%x\tf:%x\tesp:%x\n", one, two, cpu->registers[ESP]);
				}

				cpu->registers[ESP] -= 4;
				bytes[cpu->registers[ESP]] = cpu->registers[one];

				cpu->program_counter += 2;
				break;
			case 0xb0: /* popl */
				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);

				if (DEVELOPMENT) {
					printf("%x\tpopl", cpu->program_counter);
					printf("\trA:%x\tf:%x\n", one, two);
				}
				
				cpu->registers[one] = bytes[cpu->registers[ESP]];
				cpu->registers[ESP] += 4;
				cpu->program_counter += 2;
				break;
			case 0xc0: /* readb */
				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);
				
				dst =    bytes[cpu->program_counter + 2] 
				      + (bytes[cpu->program_counter + 3] << 8)
				      + (bytes[cpu->program_counter + 4] << 16)
				      + (bytes[cpu->program_counter + 5] << 24);

				if (DEVELOPMENT) {
					printf("%x\treadb", cpu->program_counter);
					printf("\trA:%x\trB:%x\tD:%x\n", one, two, dst);
				}

				scanf("%c", &in);

				bytes[cpu->registers[one] + dst] = in;

				cpu->program_counter += 6;
				cpu->zero = false;
				break;
			case 0xc1: /* readw */

				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);
				
				dst =    bytes[cpu->program_counter + 2] 
				      + (bytes[cpu->program_counter + 3] << 8)
				      + (bytes[cpu->program_counter + 4] << 16)
				      + (bytes[cpu->program_counter + 5] << 24);

				if (DEVELOPMENT) {
					printf("%x\treadw", cpu->program_counter);
					printf("\trA:%x\trB:%x\tD:%x\n", one, two, dst);
				}

				scanf("%i", &iin);

				val = 0;

				for (; val < 4; val++) {
					bytes[cpu->registers[one] + dst + val] = iin % 256;
					iin /= 256;
				}

				cpu->program_counter += 6;
				cpu->zero = false;

				break;
			case 0xd0: /* writeb */
				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);
				dst =    bytes[cpu->program_counter + 2] 
				      + (bytes[cpu->program_counter + 3] << 8)
				      + (bytes[cpu->program_counter + 4] << 16)
				      + (bytes[cpu->program_counter + 5] << 24);

				if (DEVELOPMENT) 
					printf("%i\twriteb bytes[%x + %x] - ", 
						cpu->program_counter, 
						cpu->registers[one], 
						dst);

				printf("%c",bytes[cpu->registers[one] + dst]);

				if (DEVELOPMENT) 
					printf("\n");

				cpu->program_counter += 6;

				break;
			case 0xd1: /* writew */
				if (DEVELOPMENT) 
					printf("%x\twriteb\n", cpu->program_counter);
				one = (bytes[cpu->program_counter + 1] & 0xf0) >> 4;
				two = (bytes[cpu->program_counter + 1] & 0x0f);
				
				dst =    bytes[cpu->program_counter + 2] 
				      + (bytes[cpu->program_counter + 3] << 8)
				      + (bytes[cpu->program_counter + 4] << 16)
				      + (bytes[cpu->program_counter + 5] << 24);

				
				printf("%i",bytes[cpu->registers[one] + dst]);

				cpu->program_counter += 6;
				break;
			default:
				if (DEVELOPMENT) 
					printf("%x\terr\n", cpu->program_counter);

				fprintf(stderr, INS); /* if an unknown directive is found */
				return 1;

				break;
		}
	
		val = 0;
		dst = 0;
		one = 0;
		two = 0;
	}

	fprintf(stderr, ADR);
	return 1;
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

	for (i = 0; i < 9; i++) {
		cpu->registers[i] = 0;
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

				while (j <= strlen(argument)) {
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
				*(unsigned int*)(bytes+j) = long_argument; /* this is so freakin' cool */
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
	
	/*for (i = 0; i < 0x1800; i++) {
		printf("%i\t%x\n", i, (int)bytes[i]);
	} */

	return execute_loaded_memory(bytes, cpu); 
}

int main(int argc, const char * argv[]) {
	return process_program(file_to_string(argv[1]));
}
