#include "registry_actions.h"
#include <iostream>

bool isRegEntryExists(HKEY regKey, std::string path, std::string entryName) {
    DWORD entryType;
    PCHAR entryValue;
    DWORD valueSize;

    LSTATUS regEntryStatus =
        RegGetValueA(regKey, path.c_str(), entryName.c_str(), RRF_RT_ANY, &entryType, NULL, &valueSize);

    if (regEntryStatus != ERROR_SUCCESS) {
        return false;
    }

    return true;
}

LSTATUS addRegEntry(HKEY regKey, std::string path, std::string entryName, std::string value) {
    HKEY newValueKey;
    LSTATUS openKeyStatus = RegOpenKeyExA(regKey, path.c_str(), 0, KEY_SET_VALUE, &newValueKey);
    if (openKeyStatus != ERROR_SUCCESS) {
        return openKeyStatus;
    }

    LSTATUS setNewValueStatus = RegSetValueExA(newValueKey, entryName.c_str(), 0, REG_SZ,
                                              (const BYTE*)("\"" + value + "\"").c_str(), value.length() + 3);
    
    LSTATUS closeNewValueKey = RegCloseKey(newValueKey);
    if (setNewValueStatus != ERROR_SUCCESS) {
        return setNewValueStatus;   
    }

    return closeNewValueKey;
}

void addRegEntryIfNotExists(std::string path, std::string entryName, std::string programPath) {
    if (!isRegEntryExists(HKEY_CURRENT_USER, path, entryName)) {
        addRegEntry(HKEY_CURRENT_USER, path, entryName, programPath);
    }
}