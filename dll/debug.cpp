#include "debug.h"
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

int debug(char *message, ...) {
#ifdef _DEBUG_LOG
	DWORD temp;
	HANDLE file;
	va_list args;
	char buf[1024];

	memset(buf, 0, sizeof(buf));
	va_start(args, message);
	wvsprintfA(buf, message, args);

	file = CreateFile(DEBUG_FILE, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE) {
		return -1;
	}

	SetFilePointer(file, 0, 0, FILE_END);
	WriteFile(file, buf, (DWORD)strlen(buf), &temp, NULL);
	CloseHandle(file);
#endif
	return 0;
}

#ifdef __cplusplus
}
#endif
