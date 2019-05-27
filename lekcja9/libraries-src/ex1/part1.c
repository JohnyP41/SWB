
long long give_me_product(long long a, long long b);

long long give_me_power(long long a, long long b)
{
	long long ret = 1;
	while (b--)
	{
		ret = give_me_product(a, ret);
	}
	return ret;
}
