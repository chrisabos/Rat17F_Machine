# Rat17F_Machine

This machine executes the Rat17F Machine code.

## Execution

	make
	./machine <instruction table size> <memory size> <stack size> <file>

## Rat17F Machine Code

	PUSHI	{Integer Value} Pushes the {Integer Value} onto the Top of the Stack (TOS)
	PUSHM	{ML - Memory Location} Pushes the value stored at {ML} onto TOS
	POPM	{ML} Pops the value from the top of the stack and stores it at {ML}
	STDOUT	Pops the value from TOS and outputs it to the standard output
	STDIN	Get the value from the standard input and place in onto the TOS
	ADD	Pop the first two items from stack and push the sum onto the TOS
	SUB	Pop the first two items from stack and push the difference onto the TOS ( Second item - First item)
	MUL	Pop the first two items from stack and push the product onto the TOS
	DIV	Pop the first two items from stack and push the result onto the TOS ( Second item /  First item and ignore the remainder)
	GRT	Pops two items from the stack and pushes 1 onto TOS if second item is larger otherwise push 0
	LES	Pops two items from the stack and pushes 1 onto TOS if the second item is smaller than first item otherwise push 0
	EQU	Pops two items from the stack and pushes 1 onto TOS if they are equal otherwise push 0
	JUMPZ	{IL - Instruction Location} Pop the stack and  if the value is 0 then jump to {IL}
	JUMP	{IL} Unconditionally jump to {IL}
	LABEL	Empty Instruction; Provides the instruction location to jump to

## Test Case

	testcase_rat17f_machine.ratasm is a sample test case to make sure the machine is working.
	its execution is equivelent to the rat17f code in testcase_rat17f_machine.rat17f

	Example:
	./machine 100 100 100 testcase_rat17f_machine.ratasm

Rat17F was developed by Song-James Choi, Ph.D. of California State University, Fullerton.
All this program does is executes his hypothetical language.
