#include "server.h"

#include "registry_actions.h"

#include <string>
#include <iostream>

const std::string SHARED_MUTEX_NAME = "MANAGEMENT-SHARED-MUTEX";

const std::string AUTORUN_REG_PATH = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
const std::string AUTORUN_ENTRY_NAME = "Management-App";

const std::string MESSAGE_BOX_TITLE = "INFO";
const std::string MESSAGE_BOX_BODY = "MANAGEMENT PROGRAM IS UP";

const int MILLISECOND = 1000;
const int SECOND = 1 * MILLISECOND;
const int MINUTE = SECOND * 60;
const int HOUR = MINUTE * 60;
const int SLEEPING_DURATION = HOUR;

const int RET_CODE_ERROR = -1;
const int RET_CODE_SUCCESS = 0;

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
    int retValue = RET_CODE_ERROR;
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
        retValue = RET_CODE_SUCCESS;

    } catch (std::exception& exception) {
        std::cout << exception.what() << std::endl;
        retValue = RET_CODE_ERROR;
    }
    
    if (programMutex != NULL) {
        ReleaseMutex(programMutex);
        CloseHandle(programMutex);
    }
    return retValue;
}
