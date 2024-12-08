#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int i;
	printf("Number of argument: %d.\n", argc);

	for(int i = 0; i < argc; i++)
	{
		printf("Argument number %d: %s \n", i, argv[i]);
	}
	return 0;
}
