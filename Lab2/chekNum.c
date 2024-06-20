#include <stdio.h>
#include <stdlib.h>
//function declaration
void Error(char* msg);
//argc : number recived argument
//argv[0] : name of program
//argv[1] : num
//argv[2] and argv[3] : first two numbers in list
int main(int argc, char* argv[]) {
	// Check if there are enough arguments: program name, num, and 2 other numbers
	if (argc < 4)
		Error("bad number of parameters\n");
	// Convert the first argument (num) to an integer
	int num = atoi(argv[1]);
	int i, j;
	// Iterate through the numbers to find pairs whose sum equals num
	for (i = 2; i < argc - 1; ++i)
	{
		for (j = i + 1; j < argc; ++j)
		{
			int numA = atoi(argv[i]); //conver to int first number
			int numB = atoi(argv[j]); //conver to int second number
			if (numA + numB == num)
			{
				// Print the first pair found and finish
				printf("2 numbers exist: %d + %d = %d\n", numA, numB, num);
				return 0; //finish
			}
		}
	}
	// If no if no sum of 2 numbers found, print massege and finish
	printf("2 numbers do not exist\n");
	return 0; // Exit successfully
}
void Error(char* msg) {
	fprintf(stderr, "Error: %s\n", msg); //stderr Error output
	exit(1); // Exit with error status
}
