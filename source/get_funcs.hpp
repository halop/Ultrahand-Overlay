/********************************************************************************
 * File: get_funcs.hpp
 * Author: ppkantorski
 * Description:
 *   This header file contains functions for retrieving information and data
 *   from various sources, including file system and JSON files. It includes
 *   functions for obtaining overlay module information, reading file contents,
 *   and parsing JSON data.
 *
 *   For the latest updates and contributions, visit the project's GitHub repository.
 *   (GitHub Repository: https://github.com/ppkantorski/Ultrahand-Overlay)
 *
 *   Note: Please be aware that this notice cannot be altered or removed. It is a part
 *   of the project's documentation and must remain intact.
 * 
 *  Licensed under CC-BY-4.0
 *  Copyright (c) 2023 ppkantorski
 ********************************************************************************/

#pragma once
#include <sys/stat.h>
#include <dirent.h>
#include <fnmatch.h>
#include <jansson.h>
#include "debug_funcs.hpp"
#include <string_funcs.hpp>

// Constants for overlay module
constexpr int OverlayLoaderModuleId = 348;
constexpr Result ResultSuccess = MAKERESULT(0, 0);
constexpr Result ResultParseError = MAKERESULT(OverlayLoaderModuleId, 1);

/**
 * @brief Retrieves overlay module information from a given file.
 *
 * @param filePath The path to the overlay module file.
 * @return A tuple containing the result code, module name, and display version.
 */
std::tuple<Result, std::string, std::string> getOverlayInfo(std::string filePath) {
    FILE* file = fopen(filePath.c_str(), "r");
    
    NroHeader nroHeader;
    NroAssetHeader assetHeader;
    NacpStruct nacp;
    
    // Read NRO header
    fseek(file, sizeof(NroStart), SEEK_SET);
    if (fread(&nroHeader, sizeof(NroHeader), 1, file) != 1) {
        fclose(file);
        return { ResultParseError, "", "" };
    }
    
    // Read asset header
    fseek(file, nroHeader.size, SEEK_SET);
    if (fread(&assetHeader, sizeof(NroAssetHeader), 1, file) != 1) {
        fclose(file);
        return { ResultParseError, "", "" };
    }
    
    // Read NACP struct
    fseek(file, nroHeader.size + assetHeader.nacp.offset, SEEK_SET);
    if (fread(&nacp, sizeof(NacpStruct), 1, file) != 1) {
        fclose(file);
        return { ResultParseError, "", "" };
    }
    
    fclose(file);
    
    // Return overlay information
    return {
        ResultSuccess,
        std::string(nacp.lang[0].name, std::strlen(nacp.lang[0].name)),
        std::string(nacp.display_version, std::strlen(nacp.display_version))
    };
}


/**
 * @brief Reads the contents of a file and returns it as a string.
 *
 * @param filePath The path to the file to be read.
 * @return The content of the file as a string.
 */
std::string getFileContents(const std::string& filePath) {
    std::string content;
    FILE* file = fopen(filePath.c_str(), "rb");
    if (file) {
        struct stat fileInfo;
        if (stat(filePath.c_str(), &fileInfo) == 0 && fileInfo.st_size > 0) {
            content.resize(fileInfo.st_size);
            fread(&content[0], 1, fileInfo.st_size, file);
        }
        fclose(file);
        
        // Normalize line endings to '\n'
        content.erase(std::remove(content.begin(), content.end(), '\r'), content.end());
    }
    return content;
}



/**
 * @brief Concatenates the provided directory and file names to form a destination path.
 *
 * @param destinationDir The directory where the file should be placed.
 * @param fileName The name of the file.
 * @return The destination path as a string.
 */
std::string getDestinationPath(const std::string& destinationDir, const std::string& fileName) {
    return destinationDir + "/" + fileName;
}

/**
 * @brief Extracts the value part from a string line containing a key-value pair.
 *
 * @param line The string line containing a key-value pair (e.g., "key=value").
 * @return The extracted value as a string. If no value is found, an empty string is returned.
 */
std::string getValueFromLine(const std::string& line) {
    size_t equalsPos = line.find('=');
    if (equalsPos != std::string::npos) {
        std::string value = line.substr(equalsPos + 1);
        return trim(value);
    }
    return "";
}

/**
 * @brief Extracts the name from a file path, including handling directories.
 *
 * @param path The file path from which to extract the name.
 * @return The extracted name as a string. If the path indicates a directory, it extracts the last directory name.
 * If the path is empty or no name is found, an empty string is returned.
 */
std::string getNameFromPath(const std::string& path) {
    size_t lastSlash = path.find_last_of('/');
    if (lastSlash != std::string::npos) {
        std::string name = path.substr(lastSlash + 1);
        if (name.empty()) {
            // The path ends with a slash, indicating a directory
            std::string strippedPath = path.substr(0, lastSlash);
            lastSlash = strippedPath.find_last_of('/');
            if (lastSlash != std::string::npos) {
                name = strippedPath.substr(lastSlash + 1);
            }
        }
        return name;
    }
    return path;
}

/**
 * @brief Extracts the file name from a URL.
 *
 * @param url The URL from which to extract the file name.
 * @return The extracted file name.
 */
std::string getFileNameFromURL(const std::string& url) {
    size_t lastSlash = url.find_last_of('/');
    if (lastSlash != std::string::npos)
        return url.substr(lastSlash + 1);
    return "";
}



/**
 * @brief Extracts the name of the parent directory from a given file path at a specified level.
 *
 * @param path The file path from which to extract the parent directory name.
 * @param level The level of the parent directory to extract (0 for immediate parent, 1 for grandparent, and so on).
 * @return The name of the parent directory at the specified level.
 */
std::string getParentDirNameFromPath(const std::string& path, size_t level = 0) {
    // Split the path into individual directories
    std::vector<std::string> directories;
    size_t pos = 0;
    while (pos != std::string::npos) {
        size_t nextPos = path.find('/', pos + 1);
        directories.push_back(path.substr(pos + 1, nextPos - pos - 1));
        pos = nextPos;
    }

    // Calculate the index of the desired directory
    size_t targetIndex = directories.size() - 2 - level; // Adjusted to get parent directory

    // Check if the target index is valid
    if (targetIndex < directories.size() - 1) {
        // Extract the directory name at the target index
        std::string targetDir = directories[targetIndex];

        // Check if the directory name contains spaces or special characters
        if (targetDir.find_first_of(" \t\n\r\f\v") != std::string::npos) {
            // If it does, return the directory name within quotes
            return "\"" + targetDir + "\"";
        }

        // If it doesn't, return the directory name as is
        return targetDir;
    }

    // If the path format is not as expected or the target directory is not found,
    // return an empty string or handle the case accordingly
    return "";
}


/**
 * @brief Extracts the parent directory path from a given file path.
 *
 * @param path The file path from which to extract the parent directory path.
 * @return The parent directory path.
 */
std::string getParentDirFromPath(const std::string& path) {
    size_t lastSlash = path.find_last_of('/');
    if (lastSlash != std::string::npos) {
        std::string parentDir = path.substr(0, lastSlash + 1);
        return parentDir;
    }
    return path;
}



/**
 * @brief Gets a list of subdirectories in a directory.
 *
 * @param directoryPath The path of the directory to search.
 * @return A vector of strings containing the names of subdirectories.
 */
std::vector<std::string> getSubdirectories(const std::string& directoryPath) {
    std::vector<std::string> subdirectories;
    
    DIR* dir = opendir(directoryPath.c_str());
    if (dir != nullptr) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            std::string entryName = entry->d_name;
            
            // Exclude current directory (.) and parent directory (..)
            if (entryName != "." && entryName != "..") {
                struct stat entryStat;
                std::string fullPath = directoryPath + "/" + entryName;
                
                if (stat(fullPath.c_str(), &entryStat) == 0 && S_ISDIR(entryStat.st_mode)) {
                    subdirectories.push_back(entryName);
                }
            }
        }
        
        closedir(dir);
    }
    
    return subdirectories;
}

/**
 * @brief Recursively retrieves a list of files from a directory.
 *
 * @param directoryPath The path of the directory to search.
 * @return A vector of strings containing the paths of the files.
 */
std::vector<std::string> getFilesListFromDirectory(const std::string& directoryPath) {
    std::vector<std::string> fileList;
    
    DIR* dir = opendir(directoryPath.c_str());
    if (dir != nullptr) {
        dirent* entry;
        std::string entryName, entryPath;
        std::vector<std::string> subDirFiles;
        while ((entry = readdir(dir)) != nullptr) {
            entryName = entry->d_name;
            entryPath = directoryPath;
            if (entryPath.back() != '/')
                entryPath += '/';
            entryPath += entryName;
            
            // Skip directories "." and ".."
            if (entryName != "." && entryName != "..") {
                if (isDirectory(entryPath)) {
                    // Recursively retrieve files from subdirectories
                    subDirFiles = getFilesListFromDirectory(entryPath);
                    fileList.insert(fileList.end(), subDirFiles.begin(), subDirFiles.end());
                } else {
                    fileList.push_back(entryPath);
                }
            }
        }
        closedir(dir);
    }

    return fileList;
}


/**
 * @brief Gets a list of files and folders based on a wildcard pattern.
 *
 * @param pathPattern The wildcard pattern to match files and folders.
 * @return A vector of strings containing the paths of matching files and folders.
 */
std::vector<std::string> getFilesListByWildcard(const std::string& pathPattern) {
    std::string dirPath = "";
    std::string wildcard = "";
    
    size_t wildcardPos = pathPattern.find('*');
    if (wildcardPos != std::string::npos) {
        size_t slashPos = pathPattern.rfind('/', wildcardPos);
        
        if (slashPos != std::string::npos) {
            dirPath = pathPattern.substr(0, slashPos + 1);
            wildcard = pathPattern.substr(slashPos + 1);
        } else {
            dirPath = "";
            wildcard = pathPattern;
        }
    } else {
        dirPath = pathPattern + "/";
    }
    
    //logMessage("dirPath: " + dirPath);
    //logMessage("wildcard: " + wildcard);
    
    std::vector<std::string> fileList;
    
    bool isFolderWildcard = wildcard.back() == '/';
    if (isFolderWildcard) {
        wildcard = wildcard.substr(0, wildcard.size() - 1);  // Remove the trailing slash
    }
    
    //logMessage("isFolderWildcard: " + std::to_string(isFolderWildcard));
    
    DIR* dir = opendir(dirPath.c_str());
    if (dir != nullptr) {
        dirent* entry;
        
        std::string entryName, entryPath, prefix, suffix;
        bool isEntryDirectory;
        size_t wildcardPos;
        
        while ((entry = readdir(dir)) != nullptr) {
            entryName = entry->d_name;
            entryPath = dirPath + entryName;
            
            isEntryDirectory = isDirectory(entryPath);
            
            //logMessage("entryName: " + entryName);
            //logMessage("entryPath: " + entryPath);
            //logMessage("isFolderWildcard: " + std::to_string(isFolderWildcard));
            //logMessage("isEntryDirectory: " + std::to_string(isEntryDirectory));
            
            if (isFolderWildcard && isEntryDirectory && fnmatch(wildcard.c_str(), entryName.c_str(), FNM_NOESCAPE) == 0) {
                if (entryName != "." && entryName != "..") {
                    fileList.push_back(entryPath+"/");
                }
            } else if (!isFolderWildcard && !isEntryDirectory) {
                wildcardPos = wildcard.find('*');
                if (wildcardPos != std::string::npos) {
                    prefix = wildcard.substr(0, wildcardPos);
                    if (entryName.find(prefix) == 0) {
                        suffix = wildcard.substr(wildcardPos + 1);
                        if (entryName.size() >= suffix.size() && entryName.compare(entryName.size() - suffix.size(), suffix.size(), suffix) == 0) {
                            fileList.push_back(entryPath);
                        }
                    }
                } else if (fnmatch(wildcard.c_str(), entryName.c_str(), FNM_NOESCAPE) == 0) {
                    fileList.push_back(entryPath);
                }
            }
        }
        closedir(dir);
    }
    
    //std::string fileListAsString;
    //for (const std::string& filePath : fileList) {
    //    fileListAsString += filePath + "\n";
    //}
    //logMessage("File List:\n" + fileListAsString);
    
    return fileList;
}

/**
 * @brief Gets a list of files and folders based on a wildcard pattern.
 *
 * This function searches for files and folders in a directory that match the
 * specified wildcard pattern.
 *
 * @param pathPattern The wildcard pattern to match files and folders.
 * @return A vector of strings containing the paths of matching files and folders.
 */
std::vector<std::string> getFilesListByWildcards(const std::string& pathPattern) {
    std::vector<std::string> fileList;
    
    // Check if the pattern contains multiple wildcards
    size_t wildcardPos = pathPattern.find('*');
    if (wildcardPos != std::string::npos && pathPattern.find('*', wildcardPos + 1) != std::string::npos) {
        std::string dirPath = "";
        std::string wildcard = "";
        
        // Extract the directory path and the first wildcard
        size_t slashPos = pathPattern.rfind('/', wildcardPos);
        if (slashPos != std::string::npos) {
            dirPath = pathPattern.substr(0, slashPos + 1);
            wildcard = pathPattern.substr(slashPos + 1, wildcardPos - slashPos - 1);
        } else {
            dirPath = "";
            wildcard = pathPattern.substr(0, wildcardPos);
        }
        
        // Get the list of directories matching the first wildcard
        std::vector<std::string> subDirs = getFilesListByWildcard(dirPath + wildcard + "*/");
        
        std::string subPattern;
        std::vector<std::string> subFileList;
        
        // Process each subdirectory recursively
        for (const std::string& subDir : subDirs) {
            subPattern = subDir + removeLeadingSlash(pathPattern.substr(wildcardPos + 1));
            subFileList = getFilesListByWildcards(subPattern);
            fileList.insert(fileList.end(), subFileList.begin(), subFileList.end());
        }
    } else {
        // Only one wildcard present, use getFilesListByWildcard directly
        fileList = getFilesListByWildcard(pathPattern);
    }
    
    return fileList;
}



const char* getStringFromJson(json_t* root, const char* key) {
    json_t* value = json_object_get(root, key);

    if (value && json_is_string(value)) {
        return json_string_value(value);
    } else {
        return ""; // Key not found or not a string, return empty string/char*
    }
}
