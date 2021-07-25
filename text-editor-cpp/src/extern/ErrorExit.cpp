#include <Windows.h>
#include <cstdio>

void ErrorExit(const char* message)
{
    fprintf(stderr, "%s\n", message);
    ExitProcess(0);
}
