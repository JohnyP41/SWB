int add(int, int);

int multiply(int a, int b)
{
	int i;
	int ret = 0;
	for (i = 0; i < a; ++i)
		ret = add(ret, b);
	return ret;
}
