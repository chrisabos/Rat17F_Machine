#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rat17f_instructions.h"

typedef struct entry_instruction_table
{
	int addr;
	char operator[10];
	int argument;
} entry_instruction_table;

entry_instruction_table * instruction_table;
int * memory;
int * stack;

int instruction_table_size = 0;
int stack_size = 0;
int program_counter = 0;

int main(int argc, char* argv[])
{
	FILE *fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	instruction_table = malloc(sizeof(entry_instruction_table) * atoi(argv[1]));
	memory = malloc(sizeof(int) * atoi(argv[2]));
	stack = malloc(sizeof(int) * atoi(argv[3]));

	fp = fopen(argv[4], "r");

	if(fp == NULL)
	{
		printf("Invalid file.\n");
		return 0;
	}

	while ((read = getline(&line, &len, fp)) != -1) {
		//printf("Retrieved line of length %zu :\n", read);
		//printf("%s\n", line);

		entry_instruction_table eit;
		eit.addr = ++instruction_table_size;

		if(strstr(line, "PUSHI") - line == 0)
		{
			memcpy(eit.operator, "PUSHI", 6);
			eit.argument = atoi(strchr(line, '\t'));

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "PUSHM") - line == 0)
		{
			memcpy(eit.operator, "PUSHM", 6);
			eit.argument = atoi(strchr(line, '\t'));

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "POPM") - line == 0)
		{
			memcpy(eit.operator, "POPM", 5);
			eit.argument = atoi(strchr(line, '\t'));

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "STDOUT") - line == 0)
		{
			memcpy(eit.operator, "STDOUT", 7);
			eit.argument = -1;

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "STDIN") - line == 0)
		{
			memcpy(eit.operator, "STDIN", 6);
			eit.argument = -1;

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "ADD") - line == 0)
		{
			memcpy(eit.operator, "ADD", 4);
			eit.argument = -1;

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "SUB") - line == 0)
		{
			memcpy(eit.operator, "SUB", 4);
			eit.argument = -1;

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "MUL") - line == 0)
		{
			memcpy(eit.operator, "MUL", 4);
			eit.argument = -1;

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "DIV") - line == 0)
		{
			memcpy(eit.operator, "DIV", 4);
			eit.argument = -1;

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "GRT") - line == 0)
		{
			memcpy(eit.operator, "GRT", 4);
			eit.argument = -1;

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "LES") - line == 0)
		{
			memcpy(eit.operator, "LES", 4);
			eit.argument = -1;

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "EQU") - line == 0)
		{
			memcpy(eit.operator, "EQU", 4);
			eit.argument = -1;

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "GEQ") - line == 0)
		{
			memcpy(eit.operator, "GEQ", 4);
			eit.argument = -1;

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "LEQ") - line == 0)
		{
			memcpy(eit.operator, "LEQ", 4);
			eit.argument = -1;

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "NEQ") - line == 0)
		{
			memcpy(eit.operator, "NEQ", 4);
			eit.argument = -1;

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "JUMPZ") - line == 0)
		{
			memcpy(eit.operator, "JUMPZ", 6);
			eit.argument = atoi(strchr(line, '\t'));

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "JUMP") - line == 0)
		{
			memcpy(eit.operator, "JUMP", 5);
			eit.argument = atoi(strchr(line, '\t'));

			instruction_table[instruction_table_size] = eit;
		}
		else if(strstr(line, "LABEL") - line == 0)
		{
			memcpy(eit.operator, "LABEL", 6);
			eit.argument = -1;

			instruction_table[instruction_table_size] = eit;
		}
	}

	int i;
	for(i = 1; i <= instruction_table_size; i++)
	{
		printf("Addr: %d \tOp: %s", instruction_table[i].addr, instruction_table[i].operator);
		if(instruction_table[i].argument != -1)
		{
			printf(",\tArg: %d\n", instruction_table[i].argument);
		}
		else
		{
			printf("\n");
		}
	}

	//run
	while(program_counter < instruction_table_size)
	{
		++program_counter;
		printf("PC: %d \t(%d)", program_counter, stack_size);

		int i;
		for(i = 1; i <= stack_size; i++)
		{
			printf(" %d", stack[i]);
		}

		printf("\n  %s", instruction_table[program_counter].operator);

		if(instruction_table[program_counter].argument != -1)
		{
			printf(" %d", instruction_table[program_counter].argument);
		}

		printf("\n\n");

		if(strcmp(instruction_table[program_counter].operator, "PUSHI") == 0)
		{
			stack_size++;
			stack[stack_size] = instruction_table[program_counter].argument;
		}
		else if(strcmp(instruction_table[program_counter].operator, "PUSHM") == 0)
		{
			stack_size++;
			stack[stack_size] = memory[instruction_table[program_counter].argument - 10000];
		}
		else if(strcmp(instruction_table[program_counter].operator, "POPM") == 0)
		{
			memory[instruction_table[program_counter].argument - 10000] = stack[stack_size];
			stack_size--;
		}
		else if(strcmp(instruction_table[program_counter].operator, "STDOUT") == 0)
		{
			printf("%d\n", stack[stack_size]);
			stack_size--;
		}
		else if(strcmp(instruction_table[program_counter].operator, "STDIN") == 0)
		{
			stack_size++;
			scanf("%d", &stack[stack_size]);
		}
		else if(strcmp(instruction_table[program_counter].operator, "ADD") == 0)
		{
			//pop 1st
			int a = stack[stack_size];
			stack_size--;
			//pop 2nd
			int b = stack[stack_size];
			//add
			b = b + a;
			//push 2nd
			stack[stack_size] = b;
		}
		else if(strcmp(instruction_table[program_counter].operator, "SUB") == 0)
		{
			//pop 1st
			int a = stack[stack_size];
			stack_size--;
			//pop 2nd
			int b = stack[stack_size];
			//subtract
			b = b - a;
			//push 2nd
			stack[stack_size] = b;
		}
		else if(strcmp(instruction_table[program_counter].operator, "MUL") == 0)
		{
			//pop 1st
			int a = stack[stack_size];
			stack_size--;
			//pop 2nd
			int b = stack[stack_size];
			//multiply
			b = b * a;
			//push 2nd
			stack[stack_size] = b;
		}
		else if(strcmp(instruction_table[program_counter].operator, "DIV") == 0)
		{
			//pop 1st
			int a = stack[stack_size];
			stack_size--;
			//pop 2nd
			int b = stack[stack_size];
			//divide
			b = b / a;
			//push 2nd
			stack[stack_size] = b;
		}
		else if(strcmp(instruction_table[program_counter].operator, "GRT") == 0)
		{
			//pop 1st
			int a = stack[stack_size];
			stack_size--;
			//pop 2nd
			int b = stack[stack_size];
			//compare
			if(b > a)
			{
				//push 1
				stack[stack_size] = 1;
			}
			else
			{
				//push 0
				stack[stack_size] = 0;
			}
		}
		else if(strcmp(instruction_table[program_counter].operator, "LES") == 0)
		{
			//pop 1st
			int a = stack[stack_size];
			stack_size--;
			//pop 2nd
			int b = stack[stack_size];
			//compare
			if(b < a)
			{
				//push 1
				stack[stack_size] = 1;
			}
			else
			{
				//push 0
				stack[stack_size] = 0;
			}
		}
		else if(strcmp(instruction_table[program_counter].operator, "EQU") == 0)
		{
			//pop 1st
			int a = stack[stack_size];
			stack_size--;
			//pop 2nd
			int b = stack[stack_size];
			//compare
			if(b == a)
			{
				//push 1
				stack[stack_size] = 1;
			}
			else
			{
				//push 0
				stack[stack_size] = 0;
			}
		}
		else if(strcmp(instruction_table[program_counter].operator, "GEQ") == 0)
		{
			//pop 1st
			int a = stack[stack_size];
			stack_size--;
			//pop 2nd
			int b = stack[stack_size];
			//compare
			if(b >= a)
			{
				//push 1
				stack[stack_size] = 1;
			}
			else
			{
				//push 0
				stack[stack_size] = 0;
			}
		}
		else if(strcmp(instruction_table[program_counter].operator, "LEQ") == 0)
		{
			//pop 1st
			int a = stack[stack_size];
			stack_size--;
			//pop 2nd
			int b = stack[stack_size];
			//compare
			if(b <= a)
			{
				//push 1
				stack[stack_size] = 1;
			}
			else
			{
				//push 0
				stack[stack_size] = 0;
			}
		}
		else if(strcmp(instruction_table[program_counter].operator, "NEQ") == 0)
		{
			//pop 1st
			int a = stack[stack_size];
			stack_size--;
			//pop 2nd
			int b = stack[stack_size];
			//compare
			if(b != a)
			{
				//push 1
				stack[stack_size] = 1;
			}
			else
			{
				//push 0
				stack[stack_size] = 0;
			}
		}
		else if(strcmp(instruction_table[program_counter].operator, "JUMPZ") == 0)
		{
			if(stack[stack_size] == 0)
			{
				program_counter = instruction_table[program_counter].argument - 1;// - 1 because program counter is incremented at the start of the next loop
			}
			stack_size--;
		}
		else if(strcmp(instruction_table[program_counter].operator, "JUMP") == 0)
		{
			program_counter = instruction_table[program_counter].argument - 1;// - 1 because program counter is incremented at the start of the next loop
		}
		else if(strcmp(instruction_table[program_counter].operator, "LABEL") == 0)
		{
			//empty
		}
	}


	fclose(fp);
	if (line)
		free(line);

	free(instruction_table);
	free(memory);
	free(stack);
}