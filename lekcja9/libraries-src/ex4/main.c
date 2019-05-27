#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Please provide a numeric parameter, e.g.:\n\t");
		printf("%s 8\n", argv[0]);
		return 0;
	}
	printf("%lf\n", log2((double) atoi(argv[1])));

	return 0;
}
