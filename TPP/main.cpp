#include<Windows.h>
#include<stdio.h>

#define LIBRARY "C:\\TPP.dll"
#define SUCCESS (0)
#define ERROR (-1)

/**
* Loads the defiend DLL.
*/
void load_dll() {
    HMODULE hModule = LoadLibraryA(LIBRARY);
    if (NULL == hModule)
    {
        printf("Failed to load DLL\n");
        DWORD error_code =  GetLastError();
        exit(ERROR);
    }
}

int main() {
    load_dll();
    printf("I am the main program, i prob just loaded a DLL!\n");
    return SUCCESS;
}