/* Wejscie: liczba n (<= 1000) oraz ciag n liczb calkowitych.
   Wyjscie: posortowany ciag n liczb z wejscia. */
#include <stdio.h>

int T[1000];

int max(int *tabl,int length) {
   int i;
   int max=tabl[0];
   for (i=0; i<length; i++)
   {
      if (max<tabl[i])
        max  =tabl[i];
   }
   return max;
}

int suma(int *tabl,int length)
{
  int j=0;
  int s=0;
  while (j<length)
  {
    s=s+tabl[j];
    j++;
  }
  return s;
}

int avg(int *tabl,int length)
{
   int i=0;
   int s=0;
   for (i=0; i<length; i++)
   {
     s = s+ tabl[i];
   }
   return s/length;
}

int main(int argc, char *argv[])
{
	int n;
	int i;
	int m=0;
	scanf("%d", &n);

	for (i = 0; i < n; ++i)
	{
		scanf("%d", T + i);
	}

	for (i = 0; i < n; ++i)
		if (T[i] > m)
			m = T[i];

	printf("max: %d\n", m);
        printf("suma: %d\n", suma(T, n));
        printf("avg: %d\n", avg(T, n));
	return 0;
}
