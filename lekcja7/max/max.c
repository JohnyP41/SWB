/* Wejscie: liczba n (<= 1000) oraz ciag n liczb calkowitych.
   Wyjscie: maksimum z n liczb calkowitych. */
#include <stdio.h>

int T[1000];

int main(int argc, char *argv[])
{
	int n;
	int i;
	int m=0; //poprawka
	scanf("%d", &n);

	for (i = 0; i < n; ++i)
	{
		scanf("%d", T + i);
	}

	for (i = 0; i < n; ++i)
		if (T[i] > m)
			m = T[i];

	printf("max: %d\n", m);
	return 0;
}
