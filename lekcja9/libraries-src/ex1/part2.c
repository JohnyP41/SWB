
long long give_me_sum(long long a, long long b);

long long give_me_product(long long a, long long b)
{
	long long ret = 0;
	while (b--)
	{
		ret = give_me_sum(a, ret);
	}
	return ret;
}
