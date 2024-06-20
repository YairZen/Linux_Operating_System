#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
void Error(char* msg) {
	fprintf(stderr, "Error: %s\n", msg); //stderr Error output
	exit(1); // Exit with error status
}
// Function to convert a character to uppercase
char Upper(char c) {
	if (c >= 'a' && c <= 'z') {
		return c - ('a' - 'A');
	}
	return c;
}
//argc : number recived argument (2)
//argv[0] : name of program
//argv[1] : string
int main(int argc, char* argv[]) {
	// Check if there is exactly one argument (besides the program name)
	if (argc != 2)
		Error("invalid number of arguments\n");
	char* input = argv[1]; // the given string
	int length = strlen(input);
	// Iterate through the string and print substrings separated by '_'
	for (int i = 0; i < length; ++i)
	{
		if (input[i] == '_')
			printf("\n");
		else
			printf("%c", Upper(input[i]);
	}
	printf("\n");
	return 0;
}
