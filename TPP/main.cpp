#include "server.h"

#include "registry_actions.h"

#include <string>

#include <iostream>

const std::string SHARED_MUTEX_NAME = "MANAGEMENT-SHARED-MUTEX";

const std::string AUTORUN_REG_PATH = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
const std::string AUTORUN_ENTRY_NAME = "Management-App";

const std::string MESSAGE_BOX_TITLE = "INFO";
const std::string MESSAGE_BOX_BODY = "MANAGEMENT PROGRAM IS UP";

#define MILLISECOND (1000)
#define SECOND (1 * MILLISECOND)
#define MINUTE (SECOND * 60)
#define HOUR (MINUTE * 60)
#define SLEEPING_DURATION (HOUR)

#define ERROR (-1)
#define SUCCESS (0)

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
    int retValue = ERROR;
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

        WaitForSingleObject(programMutex, INFINITE);
        addRegEntryIfNotExists(AUTORUN_REG_PATH, AUTORUN_ENTRY_NAME, argv[0]);

        ManagementServer server = ManagementServer(DEFAULT_MANAGER_SERVER_IP, DEFAULT_MANAGER_SERVER_PORT);
        server.start();
        Sleep(SLEEPING_DURATION);
        retValue = SUCCESS;

    } catch (std::exception& exception) {
        std::cout << exception.what() << std::endl;
        retValue = ERROR;
    }
    
    if (programMutex != NULL) {
        ReleaseMutex(programMutex);
        CloseHandle(programMutex);
    }
    return retValue;
}
