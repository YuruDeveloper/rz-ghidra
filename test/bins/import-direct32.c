// Calls to imported functions through the import slots of a PE for x86 with 32 bits.
// Build with the import-direct32 rule in the Makefile. The program is not made to run.
// The stdcall functions remove their args from the stack. The cdecl functions do not.

__declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);
__declspec(dllimport) unsigned long __stdcall GetTickCount(void);
__declspec(dllimport) int __stdcall MessageBoxA(void *window, const char *text, const char *caption, unsigned int type);
__declspec(dllimport) int printf(const char *format, ...);
__declspec(dllimport) unsigned int fread(void *buffer, unsigned int size, unsigned int count, void *stream);

__attribute__((noinline)) int direct_mixed(void *stream) {
	char buffer[16];
	Sleep(100);
	unsigned int count = fread(buffer, 1, 16, stream);
	MessageBoxA(0, buffer, "caption", 3);
	printf("%u %lu %u", count, GetTickCount(), 7);
	Sleep(count);
	return (int)count + 1;
}

int direct_main(void) {
	return direct_mixed(0);
}
