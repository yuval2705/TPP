#include "registry_actions.h"
#include <iostream>

bool isEntryExists(HKEY regKey, std::string path, std::string entryName)
{
    DWORD entryType;
    PCHAR entryValue;
    DWORD valueSize;

    LSTATUS getRegEntryStatus =
        RegGetValueA(regKey, path.c_str(), entryName.c_str(), RRF_RT_ANY, &entryType, NULL, &valueSize);

    if (getRegEntryStatus != ERROR_SUCCESS)
    {
        return false;
    }

    entryValue = new char[valueSize];
    RegGetValueA(regKey, path.c_str(), entryName.c_str(), RRF_RT_ANY, &entryType, entryValue, &valueSize);

    if (getRegEntryStatus != ERROR_SUCCESS)
    {
        return false;
    }

    delete entryValue;
    return true;
}

LSTATUS addRegEntry(HKEY regKey, std::string path, std::string entryName, std::string value)
{
    HKEY newValueKey;
    LSTATUS openKeyStatus = RegOpenKeyExA(regKey, path.c_str(), 0, KEY_SET_VALUE, &newValueKey);
    if (openKeyStatus != ERROR_SUCCESS)
    {
        return openKeyStatus;
    }

    LSTATUS setNewValueStatus = RegSetValueExA(newValueKey, entryName.c_str(), 0, REG_SZ,
                                               (const BYTE*)("\"" + value + "\"").c_str(), value.length() + 3);
    return setNewValueStatus;
}