#pragma once
#include <Windows.h>
#include <string>


/*
* Checks if the registry entry given exists.
* 
* @param regKey [IN] The main registry key desired.
* @param path [IN] The path in the registry to the desired key.
* @param entryName [IN] The name of the desired entry.
* @return TRUE if the entry do exists, FALSE if not.
*/
bool isEntryExists(HKEY regKey, std::string path, std::string entryName);


/*
* Adds the given string entry to the registry.
* 
* @param regKey [IN] The main registry key desired.
* @param path [IN] The path in the registry to the desired key.
* @param entryName [IN] The name of the desired entry.
* @param value [IN] The value of the entry.
* @return LSTATUS of the actions.
*/
LSTATUS addRegEntry(HKEY regKey, std::string path, std::string entryName, std::string value);