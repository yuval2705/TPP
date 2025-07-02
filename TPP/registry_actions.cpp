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

void addRegEntry(HKEY regKey, const std::string& path, const std::string& entryName, const std::string& entryValue)
{
    HKEY newValueKey;
    LSTATUS openKeyStatus = RegOpenKeyExA(regKey, path.c_str(), 0, KEY_SET_VALUE, &newValueKey);
    if (openKeyStatus != ERROR_SUCCESS)
    {
        std::string exceptionText =
            std::string("Problem accourd in RegOpenKey with error: ") + std::to_string(GetLastError());
        throw std::exception(exceptionText.c_str());
    }

    LSTATUS setNewValueStatus =
        RegSetValueExA(newValueKey, entryName.c_str(), 0, REG_SZ,
                       reinterpret_cast<const BYTE*>(("\"" + entryValue + "\"").c_str()), entryValue.length() + 3);

    LSTATUS closeNewValueKey = RegCloseKey(newValueKey);
    if (setNewValueStatus != ERROR_SUCCESS)
    {
        std::string exceptionText =
            std::string("Problem accourd in RegSetValue with error: ") + std::to_string(GetLastError());
        throw std::exception(exceptionText.c_str());
    }

    if (closeNewValueKey != ERROR_SUCCESS)
    {
        std::string exceptionText =
            std::string("Problem accourd in RegCloseKey with error: ") + std::to_string(GetLastError());
        throw std::exception(exceptionText.c_str());
    }
}

void addRegEntryIfNotExists(const std::string& path, const std::string& entryName, const std::string& entryValue)
{
    if (!isRegEntryExists(HKEY_CURRENT_USER, path, entryName)) {
        addRegEntry(HKEY_CURRENT_USER, path, entryName, entryValue);
    }
}