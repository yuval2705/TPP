#include "registry_actions.h"
#include <string>
#include <iostream>

const std::string SHARED_MUTEX_NAME = "MANAGEMENT-SHARED-MUTEX";

const std::string AUTORUN_REG_PATH = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
const std::string AUTORUN_ENTRY_NAME = "Management-App";

#define ERROR (-1)

/*
* @brief Displays a Message Box onto the screen.
* 
* @param title [IN] The title of the window.
* @param body [IN] The body of the messagebox in the opened window.
* @return The returncode of the WINAPI function used.
*/
int showMessageBox(const std::string& title, const std::string& body) {
    return MessageBoxA(NULL, body.c_str(), title.c_str(), MB_OKCANCEL);
}


/*
* @brief The start of the program, it calls the registy validation and is the real entry of the program.
* 
* @param argc [IN] The number of arguments given.
* @param argv [IN] The arguments.
*/
int main(int argc, char** argv) {
    HANDLE programMutex;
    try {
        programMutex = CreateMutexA(NULL, FALSE, SHARED_MUTEX_NAME.c_str());

        // Can still meaning there is already a running instance.
        if (programMutex == NULL) {
            programMutex = OpenMutexA(SYNCHRONIZE, FALSE, SHARED_MUTEX_NAME.c_str());

            if (programMutex == NULL) {
                throw std::exception((std::string("Cannot create or open the shared mutex with error: ") +
                                      std::to_string(GetLastError())).c_str());
            }
        }
    }
    catch (std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
    WaitForSingleObject(programMutex, INFINITE);
    addRegEntryIfNotExists(AUTORUN_REG_PATH, AUTORUN_ENTRY_NAME, argv[0]);

    std::string messageBoxTitle = "INFO";
    std::string messageBoxBody = "MANAGEMENT PROGRAM IS UP";
    int messageBoxCode = showMessageBox(messageBoxTitle, messageBoxBody);

    ReleaseMutex(programMutex);

    return messageBoxCode;
}
