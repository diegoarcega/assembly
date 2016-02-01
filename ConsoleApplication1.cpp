/* 

Name: Diego Casas de Arcega
Student ID: 201027179
D.Casas-De-Arcega@student.liverpool.ac.uk
Group H

*/

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	char msg1[] = "How many numbers do you want? \nYour answer: "; // display message to ask for how many times the program should loop
	char loopMsg[] = "\n\nType a number. \nYour answer: "; // asking for the numbers to be added up later on
	
	char resultPositives[] = "\n\nTotal for positives: "; // message to be displayed at the end of the execution
	char resultNegatives[] = "\nTotal for negatives: "; // message to be displayed at the end of the execution

	char format[] = "%d"; // format string for the scanf function

	int postot; // variable where the addition for all the positive numbers will be stored
	int negot; // variable where the addition for all the negative numbers will be stored

	int qtdNumbers; // times the program will loop asking for numbers
	int number; // variable where all the numbers in the loop will be stored to be compared 

	_asm
	{
			lea eax, msg1 //load the msg into the stack
			push eax // push the msg into the stack
			call printf // print the message on the screen
			add esp, 4 // clean the stack by 4 bits

			lea eax, qtdNumbers // choosing a place to store the user input
			push eax // push this place into the stack
			lea eax, format // load the format for scanning user input
			push eax 
			call scanf // scan user input
			add esp, 8 // clean the stack by 8 bits

			mov postot, 0 // initialize the variable for the positive numbers addition
			mov negot, 0 // initialize the variable for the negative numbers addition
			mov ecx, qtdNumbers // set how many times the loop will run qtdNumbers holds the number of times
			readLoop :
				push ecx // push this quantity of times into the stack
				
				lea eax, loopMsg // print a message to the user so he know what to type next
				push eax
				call printf
				add esp, 4

				lea eax, number // choosing a place to store the user input
				push eax
				lea eax, format
				push eax
				call scanf // read in the number for later comparison

				add esp, 8 
				
				mov eax, number // move the input  into the register so it can be compared 
				cmp eax, 0 // comparing the input stored into the register and checking whether it is positive
				jg addPositives // jumping to the addPositives subroutine
				jmp addNegatives // jumping to the addNegative subroutine
				afterAddition: // setting a label so that the subroutines can jump to after executing
				pop ecx // decrease the counter for the loop
				loop readLoop // loop the instruction readLoop if ecx counter > 0
			
			jmp showResult // if the loop is over, jump to showResult instruction that will end the program

			   addPositives : add postot, eax // adding the value in eax to the variable postot
						      jmp afterAddition // jumping back to the loop

		       addNegatives : add negot, eax // adding the value in eax to the variable negot
							  jmp afterAddition //jumping back to the loop
		   

			   showResult : lea eax, resultPositives // the output routine, loading the header message for the positive numbers
							push eax 
							call printf
							add esp, 4

							push postot //push the value in the variable to be displayed in the results
							lea eax, format // pushing the format for the string
							push eax
							call printf
							add esp, 8 // clear the stack 
							
							lea eax, resultNegatives // the header message for the negative numbers
							push eax
							call printf 
							add esp, 4

							push negot //push the variable value into the stack 
							lea eax, format //loading the format for outputting the number
							push eax 
							call printf
							add esp, 8 // clear the stack by 8 bytes


							jmp finish // finish the program

		  finish :
	}

	return 0;
}
