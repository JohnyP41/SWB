void _start() __attribute__((alias("main")));

int main()
{
	__asm__("mov $42, %rdi\n\t");
	__asm__("mov $60, %rax\n\t");
	__asm__("syscall\n\t");
}
