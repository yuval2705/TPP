#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS (0)
#define ERROR (-1)
char DLL_PATH[] = "C:\\my_awesome_dll.dll";


/**
* Opens a new thread in the given process and inside loads the DLL.
* 
* @param hProcess [IN] Handle to the target process to open the thread in.
*/
void invoke_remote_thread_creation(HANDLE hProcess)
{
    LPVOID target_memory = VirtualAllocEx(hProcess, NULL, sizeof(DLL_PATH), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(hProcess, target_memory, DLL_PATH, sizeof(DLL_PATH), NULL);
    
    HMODULE hKernel22 = LoadLibraryA("kernel32.dll");
    // This can happen because kernel32 usally loads to the same address!
    FARPROC load_module_addr = GetProcAddress(hKernel22, (LPCSTR)"LoadLibraryA");



    HANDLE new_thread_handle = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)load_module_addr, target_memory, 0, NULL);
    
    if (new_thread_handle == NULL)
    {
        printf("Failed to invoke new remote thread!\n");
        DWORD error_code = GetLastError();
        printf("Couldn't open thread. Error code is: %d\n", error_code);
        exit(ERROR);
    }
    printf("Created the new thread!\n");
    
    DWORD thread_ret_val = 1;
    GetExitCodeThread(new_thread_handle, &thread_ret_val);
    while (thread_ret_val == STILL_ACTIVE)
    {
        GetExitCodeThread(new_thread_handle, &thread_ret_val);
    }
    printf("Thread exit value is: %d\n", thread_ret_val);
}


int main(int argc, char** argv)
{
    DWORD target_pid = GetCurrentProcessId();
    if (argc == 2)
    {
        target_pid = atoi(argv[1]);
    }

    HANDLE target_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, target_pid);

    if (target_handle == NULL)
    {
        printf("Failed to get %d handle!\n", target_pid);
        DWORD error_code = GetLastError();
        printf("%d\n", error_code);
        exit(ERROR);
    }

    invoke_remote_thread_creation(target_handle);

    return SUCCESS;
}