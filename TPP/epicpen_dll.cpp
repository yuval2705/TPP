#include <Windows.h>
#include <stdio.h>
#define DLL_EXPORT
#include "epicpen_dll.h"

#define WINDOW_NAME ("Random Window")
#define EXE_PATH ("C:\\Users\\yuval\\Desktop\\epicpen.exe")

#define ERROR (-1)

typedef void (*PFUNC)(void);

extern "C"
{
    void call_my_function()
    {
        HMODULE epicpen_exe = LoadLibraryA(EXE_PATH);
        
        if (epicpen_exe == NULL)
        {
            printf("Failed Loading %s with error %d\n", EXE_PATH, GetLastError());
            exit(ERROR);
        }

        FARPROC my_epic_function_addr = GetProcAddress(epicpen_exe, "my_epic_function");
        printf("Loaded %s\nThe relevent function is at: %p\n", EXE_PATH, my_epic_function_addr);
        //((PFUNC)my_epic_function_addr)();
        MessageBoxA(NULL, "blablabla", "Random Message Box", MB_OKCANCEL);
    }

}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        call_my_function();
        FARPROC my_epic_function_addr = GetProcAddress((HMODULE)hModule, "my_epic_function");
        printf("Loaded %s\nThe relevent function is at: %p\n", EXE_PATH, my_epic_function_addr);
        break;
    default:
        break;
    }
    return TRUE;
}