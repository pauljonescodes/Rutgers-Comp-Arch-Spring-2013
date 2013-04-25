#define AOK "everything is fine"
#define HLT "halt instruction has been encountered"
#define ADR "some sort of invalid address"
#define INS "an invalid instruction"

#define EAX 0
#define ECX 1
#define EDX 2
#define EBX 3
#define ESP 4
#define EBP 5
#define ESI 6
#define EDI 7

typedef struct cpu {
	int eax; 
	int ecx; 
	int edx; 
	int ebx; 
	int esp; 
	int ebp; 
	int esi; 
	int edi;

	int program_counter;

	bool overflow;
	bool zero;
	bool negative;
} cpu;
