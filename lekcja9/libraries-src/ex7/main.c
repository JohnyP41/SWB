#include <stdio.h>


int authenticate(const char *);

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		puts("Provide password as a parameter.");
		return 1;
	}
	if (authenticate(argv[1]))
	{
		puts("Access GRANTED.");
	}
	else
	{
		puts("Access REFUSED.");
	}
	return 0;
}
