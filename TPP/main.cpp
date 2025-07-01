#include "registry_actions.h"
#include<string>
#include<iostream>

const std::string SHARED_MUTEX_NAME = "MANAGEMENT-SHARED-MUTEX";

const HKEY AUTORUN_REG_HKEY = HKEY_CURRENT_USER;
const std::string AUTORUN_REG_PATH = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
const std::string AUTORUN_ENTRY_NAME = "Management-App";

/*
* Displays a Message Box onto the screen.
* 
* @param title [IN] The title of the window.
* @param body [IN] The body of the messagebox in the opened window.
*/
void showMessageBox(std::string title, std::string body)
{
    MessageBoxA(NULL, body.c_str(), title.c_str(), MB_OKCANCEL);
}

/*
* Validates if the given program path is in the registry entry.
* If not it adds it.
* 
* @param programPath [IN] The path for the executable to add.
*/
void validateEntry(char* programPath)
{
    if (!isEntryExists(AUTORUN_REG_HKEY, AUTORUN_REG_PATH, AUTORUN_ENTRY_NAME))
    {
        addRegEntry(AUTORUN_REG_HKEY, AUTORUN_REG_PATH, AUTORUN_ENTRY_NAME, std::string(programPath));
    }
}

/*
* The start of the program, it calls the registy validation and is the real entry of the program.
* 
* @param argc [IN] The number of arguments given.
* @param argv [IN] The arguments.
*/
void start(int argc, char** argv)
{
    HANDLE programMutex = CreateMutexA(NULL, FALSE, SHARED_MUTEX_NAME.c_str());

    // Meaning there is already a running instance.
    if (programMutex == NULL)
    {
        programMutex = OpenMutexA(SYNCHRONIZE, TRUE, SHARED_MUTEX_NAME.c_str());

        if (programMutex == NULL)
        {
            throw std::exception("Cannot create or open the shared mutex!");
        }
    }

    WaitForSingleObject(programMutex, INFINITE);
    validateEntry(argv[0]);
    showMessageBox("INFO", "MANAGEMENT PROGRAM IS UP");
    ReleaseMutex(programMutex);
}

void main(int argc, char** argv)
{
    start(argc, argv);
}