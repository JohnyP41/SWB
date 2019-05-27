void _start() __attribute__((alias("main")));

extern int storage;

int main(int argc, char *argv[])
{
	return my_exit(storage);
}
