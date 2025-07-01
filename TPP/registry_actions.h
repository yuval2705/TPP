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
bool isRegEntryExists(HKEY regKey, std::string path, std::string entryName);


/*
* @brief Adds the given string entry to the registry.
* 
* @param regKey [IN] The main registry key desired.
* @param path [IN] The path in the registry to the desired key.
* @param entryName [IN] The name of the desired entry.
* @param value [IN] The value of the entry.
* @return LSTATUS of the actions.
*/
LSTATUS addRegEntry(HKEY regKey, std::string path, std::string entryName, std::string value);



/*
 * @brief Adds if the given program path is in the registry entry.
 * If not it adds it.
 *
 * @param path [IN] The path in the registry to the desired key.
 * @param entryName [IN] The name of the desired entry.
 * @param programPath [IN] The path for the executable to add.
 */
void addRegEntryIfNotExists(std::string path, std::string entryName, std::string programPath);