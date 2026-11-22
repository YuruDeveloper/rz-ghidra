// Calls of imported functions through thunks in a PE for x86-64.
// Build with the import-noargs.exe rule in the Makefile. The program is not made to run.
// GetTickCount has a signature without args in the type database. api_unknown has no signature.

unsigned long GetTickCount(void);
int api_unknown(int value);

__attribute__((noinline)) unsigned long noargs_tick(void) {
	return GetTickCount() + 1;
}

__attribute__((noinline)) int noargs_unknown(int value) {
	return api_unknown(value) + 1;
}

int noargs_main(void) {
	return (int)noargs_tick() + noargs_unknown(3);
}
