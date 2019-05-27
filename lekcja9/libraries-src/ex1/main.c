#include <stdio.h>


long long give_me_power(long long a, long long b);
double square_root(double x);

int main()
{
	long long n = give_me_power(2,26);
	printf("%lld\n", n);
	double s = square_root((double) n);
	printf("%lf\n", s);

	return 0;
}
