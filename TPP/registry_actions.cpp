#include "registry_actions.h"

#include <iostream>

bool isRegEntryExists(HKEY regKey, const std::string& path, const std::string& entryName)
{
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

LSTATUS addRegEntry(HKEY regKey, const std::string& path, const std::string& entryName, const std::string& entryValue)
{
    HKEY newValueKey;
    LSTATUS openKeyStatus = RegOpenKeyExA(regKey, path.c_str(), 0, KEY_SET_VALUE, &newValueKey);
    if (openKeyStatus != ERROR_SUCCESS) {
        return openKeyStatus;
    }

    LSTATUS setNewValueStatus = RegSetValueExA(newValueKey, entryName.c_str(), 0, REG_SZ,
                (const BYTE*)("\"" + entryValue + "\"").c_str(), entryValue.length() + 3);
    
    LSTATUS closeNewValueKey = RegCloseKey(newValueKey);
    if (setNewValueStatus != ERROR_SUCCESS) {
        return setNewValueStatus;   
    }

    return closeNewValueKey;
}

void addRegEntryIfNotExists(const std::string& path, const std::string& entryName, const std::string& entryValue)
{
    if (!isRegEntryExists(HKEY_CURRENT_USER, path, entryName)) {
        addRegEntry(HKEY_CURRENT_USER, path, entryName, entryValue);
    }
}