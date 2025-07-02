#pragma once

#include <Windows.h>

#include <string>


/*
* @brief Checks if the registry entry given exists.
* 
* @param regKey [IN] The main registry key desired.
* @param path [IN] The path in the registry to the desired key.
* @param entryName [IN] The name of the desired entry.
* @return TRUE if the entry do exists, FALSE if not.
*/
bool isRegEntryExists(HKEY regKey, const std::string& path, const std::string& entryName);


/*
* @brief Adds the given string entry to the registry.
* 
* @param regKey [IN] The main registry key desired.
* @param path [IN] The path in the registry to the desired key.
* @param entryName [IN] The name of the desired entry.
* @param entryValue [IN] The value of the entry.
*/
void addRegEntry(HKEY regKey, const std::string& path, const std::string& entryName, const std::string& entryValue);



/*
 * @brief Adds if the given program path is in the registry entry.
 * If not it adds it.
 *
 * @param path [IN] The path in the registry to the desired key.
 * @param entryName [IN] The name of the desired entry.
 * @param entryValue [IN] The path for the executable to add.
 */
void addRegEntryIfNotExists(const std::string& path, const std::string& entryName, const std::string& entryValue);