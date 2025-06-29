#include <Windows.h>
#include <stdio.h>
#define DLL_EXPORT
#include "TPP.h"

#define WINDOW_NAME ("Random Window")
extern "C"
{
    void open_random_message_box() {
        printf("opening a random message box!\n");
        MessageBoxA(NULL, "blablabla", "Random Message Box", MB_OKCANCEL);
    }
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        open_random_message_box();
        break;
    default:
        break;
    }
    return TRUE;
}