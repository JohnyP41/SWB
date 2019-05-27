void _start() __attribute__((alias("main")));

int storage;

int get_return_code();

int main()
{
	storage = get_return_code();
	return my_exit(storage);
}
