#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>

#define DLLEXPORT __declspec(dllexport)

extern "C"
{
    DLLEXPORT long Sqr(long x) {
        return x * x;
    }

    DLLEXPORT long Cub(long x) {
        return x * x * x;
    }

    DLLEXPORT int Sum(int x, int y) {
        return x + y;
    }

    DLLEXPORT void dec2hex(const char* dec, char* hex) {
        _itoa(atoi(dec), hex, 16);
    }
    DLLEXPORT void hex2dec(char* hex, char* dec) {
        char* end;
        _itoa(strtol(hex, &end, 16), dec, 10);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}