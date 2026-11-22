// Pointers to functions and to a label in a PE for x86-64.
// Build with the callback-flag.exe rule in the Makefile. The program is not made to run.

typedef void (*signal_handler)(int);
signal_handler signal(int number, signal_handler handler);
int puts(const char *text);

static int counter;

__attribute__((noinline)) static void callback_handler(int number)
{
	counter += number;
}

__attribute__((noinline)) static int callback_first(int value)
{
	return value + 1;
}

__attribute__((noinline)) static int callback_second(int value)
{
	return value * 3;
}

static int (*const callback_table[2])(int) = { callback_first, callback_second };

__attribute__((noinline)) void callback_register(void)
{
	signal(2, callback_handler);
}

__attribute__((noinline)) int callback_dispatch(int index, int value)
{
	return callback_table[index & 1](value);
}

__attribute__((noinline)) int callback_direct(int value)
{
	return callback_first(value) + callback_second(value);
}

__attribute__((noinline)) const void *callback_label(int value)
{
	if(value)
		goto other;
	puts("first");
	return &&other;
other:
	puts("second");
	return 0;
}

int callback_main(void)
{
	callback_register();
	callback_label(counter);
	return callback_dispatch(counter, 2) + callback_direct(counter);
}
