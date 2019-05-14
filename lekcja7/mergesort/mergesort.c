/* Wejscie: Liczba n, a nastepnie ciag n liczb.
   Spodziewane wyjscie: posortowany ciag wejsciowy (n liczb). */
#include <stdio.h>

int T[1000];

void merge(int * a, int ac, int * b, int bc, int * out)
{
	int i = 0, j = 0;

	while (i < ac && j < bc)
	{
		if (a[i] < b[j])
			*out++ = a[i++];
		else
			*out++ = b[j++];
	}
}

void mergesort(int * t, int n)
{
	int m = n / 2;
	int out[n];
	int i;

	if (n < 2)
		return;
	
	mergesort(t, m);
	mergesort(t + m, n - m);
	merge(t, m, t + m, n - m, out);

	for (i = 0; i < n; ++i)
		t[i] = out[i];
}

int main(int argc, char *argv[])
{
	int n;
	int i;

	scanf("%d", &n);
	for (i = 0; i < n; ++i)
		scanf("%d", T + i);
	
	mergesort(T, n);
	for (i = 0; i < n; ++i)
		printf("%d ", T[i]);
	
	return 0;
}
