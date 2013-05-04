#define AOK "everything is fine\n"
#define HLT "halt instruction has been encountered\n"
#define ADR "some sort of invalid address\n"
#define INS "an invalid instruction\n"

#define EAX 0
#define ECX 1
#define EDX 2
#define EBX 3
#define ESP 4
#define EBP 5
#define ESI 6
#define EDI 7

typedef struct cpu {
	int registers[9];

	int program_counter;
	int size;

	bool cont;
	bool overflow;
	bool zero;
	bool negative;
} cpu;
