// A string in a writable section and a string in a read-only section in a PE for x86-64.
// Build with the writable-string.exe rule in the Makefile. The program is not made to run.

int puts(const char *text);

static char banner[16] = "hello world";

__attribute__((noinline)) void writable_banner(void)
{
	banner[0] = 'J';
	puts(banner);
}

__attribute__((noinline)) void writable_constant(void)
{
	puts("constant text");
}

int writable_main(void)
{
	writable_banner();
	writable_constant();
	return 0;
}
