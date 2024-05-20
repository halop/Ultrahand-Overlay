/********************************************************************************
 * File: hex_funcs.hpp
 * Author: ppkantorski
 * Description:
 *   This header file provides functions for working with hexadecimal data in C++.
 *   It includes functions for converting between ASCII and hexadecimal strings,
 *   finding hexadecimal data offsets in a file, and editing hexadecimal data in a file.
 *
 *   For the latest updates and contributions, visit the project's GitHub repository.
 *   (GitHub Repository: https://github.com/ppkantorski/Ultrahand-Overlay)
 *
 *   Note: Please be aware that this notice cannot be altered or removed. It is a part
 *   of the project's documentation and must remain intact.
 * 
 *  Licensed under both GPLv2 and CC-BY-4.0
 *  Copyright (c) 2024 ppkantorski
 ********************************************************************************/

#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
//#include <cstdio> // Added for FILE and fopen
#include <fstream>
#include <cstring> // Added for std::memcmp


size_t HEX_BUFFER_SIZE = 4096*4;


// For improving the speed of hexing consecutively with the same file and asciiPattern.
static std::unordered_map<std::string, std::string> hexSumCache; // MOVED TO main.cpp



/**
 * @brief Converts an ASCII string to a hexadecimal string.
 *
 * This function takes an ASCII string as input and converts it into a hexadecimal string.
 *
 * @param asciiStr The ASCII string to convert.
 * @return The corresponding hexadecimal string.
 */
std::string asciiToHex(const std::string& asciiStr) {
    std::string hexStr;
    hexStr.reserve(asciiStr.length() * 2); // Reserve space for the hexadecimal string
    unsigned char uc;
    char hexChar[3];
    for (char c : asciiStr) {
        uc = static_cast<unsigned char>(c); // Convert char to unsigned char
        //char hexChar[3]; // Buffer to store the hexadecimal representation (2 characters + null terminator)
        
        // Format the unsigned char as a hexadecimal string and append it to the result
        std::snprintf(hexChar, sizeof(hexChar), "%02X", uc);
        hexStr += hexChar;
    }
    
    if (hexStr.length() % 2 != 0) {
        hexStr = '0' + hexStr;
    }
    
    return hexStr;
}

/**
 * @brief Converts a decimal string to a hexadecimal string.
 *
 * This function takes a decimal string as input and converts it into a hexadecimal string.
 *
 * @param decimalStr The decimal string to convert.
 * @return The corresponding hexadecimal string.
 */
std::string decimalToHex(const std::string& decimalStr) {
    // Convert decimal string to integer
    int decimalValue = std::stoi(decimalStr);
    
    // Convert decimal to hexadecimal
    std::string hexadecimal;
    
    int _remainder;
    char hexChar;
    
    while (decimalValue > 0) {
        _remainder = decimalValue % 16;
        hexChar = (_remainder < 10) ? ('0' + _remainder) : ('A' + _remainder - 10);
        hexadecimal += hexChar;
        decimalValue /= 16;
    }
    
    // Reverse the hexadecimal string
    std::reverse(hexadecimal.begin(), hexadecimal.end());
    
    // If the length is odd, add a trailing '0'
    if (hexadecimal.length() % 2 != 0) {
        hexadecimal = '0' + hexadecimal;
    }
    
    return hexadecimal;
}

/**
 * @brief Converts a decimal string to a reversed hexadecimal string.
 *
 * This function takes a decimal string as input, converts it into a hexadecimal
 * string, and reverses the resulting hexadecimal string in groups of order.
 *
 * @param decimalStr The decimal string to convert.
 * @param order The grouping order for reversing the hexadecimal string.
 * @return The reversed hexadecimal string.
 */
std::string decimalToReversedHex(const std::string& decimalStr, int order = 2) {
    std::string hexadecimal = decimalToHex(decimalStr);
    
    // Reverse the hexadecimal string in groups of order
    std::string reversedHex;
    for (int i = hexadecimal.length() - order; i >= 0; i -= order) {
        reversedHex += hexadecimal.substr(i, order);
    }
    
    return reversedHex;
}

/**
 * @brief Finds the offsets of hexadecimal data in a file.
 *
 * This function searches for occurrences of hexadecimal data in a binary file
 * and returns the file offsets where the data is found.
 *
 * @param filePath The path to the binary file.
 * @param hexData The hexadecimal data to search for.
 * @return A vector of strings containing the file offsets where the data is found.
 */
std::vector<std::string> findHexDataOffsets(const std::string& filePath, const std::string& hexData) {
    std::vector<std::string> offsets;

    // Open the file for reading in binary mode
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        return offsets; // Return empty vector if file cannot be opened
    }

    // Get the file size
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Convert the hex data string to binary data
    std::vector<unsigned char> binaryData;
    if (hexData.length() % 2 != 0) {
        file.close();
        return offsets; // Ensure hexData has an even length
    }
    std::string byteString;
    for (size_t i = 0; i < hexData.length(); i += 2) {
        byteString = hexData.substr(i, 2);
        //unsigned char byte = static_cast<unsigned char>(std::stoi(byteString, nullptr, 16));
        binaryData.push_back(static_cast<unsigned char>(std::stoi(byteString, nullptr, 16)));
    }

    // Read the file in chunks to find the offsets where the hex data is located
    //constexpr size_t hexBufferSize = 4096*4; // Arbitrary buffer size, can be adjusted
    std::vector<unsigned char> buffer(HEX_BUFFER_SIZE);
    size_t bytesRead = 0;
    size_t offset = 0;

    while (file.read(reinterpret_cast<char*>(buffer.data()), HEX_BUFFER_SIZE)) {
        bytesRead = file.gcount();
        for (size_t i = 0; i < bytesRead; ++i) {
            if (offset + i + binaryData.size() <= fileSize && std::memcmp(buffer.data() + i, binaryData.data(), binaryData.size()) == 0) {
                offsets.push_back(std::to_string(offset + i));
            }
        }
        offset += bytesRead;
    }

    file.close();
    return offsets;
}



/**
 * @brief Edits hexadecimal data in a file at a specified offset.
 *
 * This function opens a binary file, seeks to a specified offset, and replaces
 * the data at that offset with the provided hexadecimal data.
 *
 * @param filePath The path to the binary file.
 * @param offsetStr The offset in the file to performthe edit.
 * @param hexData The hexadecimal data to replace at the offset.
 */
void hexEditByOffset(const std::string& filePath, const std::string& offsetStr, const std::string& hexData) {
    std::streampos offset = std::stoll(offsetStr);

    // Open the file for both reading and writing in binary mode
    std::fstream file(filePath, std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open()) {
        logMessage("Failed to open the file.");
        return;
    }

    // Retrieve the file size
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    if (offset >= fileSize) {
        logMessage("Offset exceeds file size.");
        return;
    }

    // Convert the hex string to binary data
    std::vector<unsigned char> binaryData(hexData.length() / 2);
    std::string byteString;
    for (size_t i = 0, j = 0; i < hexData.length(); i += 2, ++j) {
        byteString = hexData.substr(i, 2);
        binaryData[j] = static_cast<unsigned char>(std::stoi(byteString, nullptr, 16));
    }

    // Move to the specified offset
    file.seekg(offset);

    // Write the binary data directly to the file at the offset
    file.seekp(offset);
    file.write(reinterpret_cast<const char*>(binaryData.data()), binaryData.size());
    if (!file) {
        logMessage("Failed to write data to the file.");
        return;
    }
}

/**
 * @brief Edits a specific offset in a file with custom hexadecimal data.
 *
 * This function searches for a custom pattern in the file and calculates a new offset
 * based on user-provided offsetStr and the found pattern. It then replaces the data
 * at the calculated offset with the provided hexadecimal data.
 *
 * @param filePath The path to the binary file.
 * @param offsetStr The user-provided offset for the edit.
 * @param customPattern The custom pattern to search for in the file.
 * @param hexDataReplacement The hexadecimal data to replace at the calculated offset.
 * @param occurrence The occurrence/index of the data to replace (default is "0" to replace all occurrences).
 */
void hexEditByCustomOffset(const std::string& filePath, const std::string& customAsciiPattern, const std::string& offsetStr, const std::string& hexDataReplacement, size_t occurrence = 0) {
    
    // Create a cache key based on filePath and customAsciiPattern
    std::string cacheKey = filePath + '?' + customAsciiPattern + '?' + std::to_string(occurrence);
    
    int hexSum = -1;
    
    // Check if the result is already cached
    auto cachedResult = hexSumCache.find(cacheKey);
    if (cachedResult != hexSumCache.end()) {
        hexSum = std::stoi(cachedResult->second); // load sum from cache
    }
    
    if (hexSum == -1) {
        std::string customHexPattern;
        if (customAsciiPattern[0] == '#') {
            // remove #
            customHexPattern = customAsciiPattern.substr(1);
        } else {
            // Convert custom ASCII pattern to a custom hex pattern
            customHexPattern = asciiToHex(customAsciiPattern);
        }
        
        
        // Find hex data offsets in the file
        std::vector<std::string> offsets = findHexDataOffsets(filePath, customHexPattern);
        
        if (!offsets.empty()) {
            hexSum = std::stoi(offsets[occurrence]);
            
            // Convert 'hexSum' to a string and add it to the cache
            hexSumCache[cacheKey] = std::to_string(hexSum);
        } else {
            logMessage("Offset not found.");
            return;
        }
    }
    
    
    if (hexSum != -1) {
        // Calculate the total offset to seek in the file
        //int sum = hexSum + std::stoi(offsetStr);
        hexEditByOffset(filePath, std::to_string(hexSum + std::stoi(offsetStr)), hexDataReplacement);
    } else {
        logMessage("Failed to find " + customAsciiPattern + ".");
    }
}

/**
 * @brief Finds and replaces hexadecimal data in a file.
 *
 * This function searches for occurrences of hexadecimal data in a binary file
 * and replaces them with a specified hexadecimal replacement data.
 *
 * @param filePath The path to the binary file.
 * @param hexDataToReplace The hexadecimal data to search for and replace.
 * @param hexDataReplacement The hexadecimal data to replace with.
 * @param occurrence The occurrence/index of the data to replace (default is "0" to replace all occurrences).
 */
void hexEditFindReplace(const std::string& filePath, const std::string& hexDataToReplace, const std::string& hexDataReplacement, size_t occurrence = 0) {
    std::vector<std::string> offsetStrs = findHexDataOffsets(filePath, hexDataToReplace);
    if (!offsetStrs.empty()) {
        if (occurrence == 0) {
            // Replace all occurrences
            for (const std::string& offsetStr : offsetStrs) {
                //logMessage("offsetStr: "+offsetStr);
                //logMessage("hexDataReplacement: "+hexDataReplacement);
                hexEditByOffset(filePath, offsetStr, hexDataReplacement);
            }
        } else {
            // Convert the occurrence string to an integer
            if (occurrence > 0 && occurrence <= offsetStrs.size()) {
                // Replace the specified occurrence/index
                //std::string offsetStr = offsetStrs[occurrence - 1];
                //logMessage("offsetStr: "+offsetStr);
                //logMessage("hexDataReplacement: "+hexDataReplacement);
                hexEditByOffset(filePath, offsetStrs[occurrence - 1], hexDataReplacement);
            } else {
                // Invalid occurrence/index specified
                logMessage("Invalid hex occurrence/index specified.");
            }
        }
        //std::cout << "Hex data replaced successfully." << std::endl;
    }
}

/**
 * @brief Finds and replaces hexadecimal data in a file.
 *
 * This function searches for occurrences of hexadecimal data in a binary file
 * and replaces them with a specified hexadecimal replacement data.
 *
 * @param filePath The path to the binary file.
 * @param hexDataToReplace The hexadecimal data to search for and replace.
 * @param hexDataReplacement The hexadecimal data to replace with.
 * @param occurrence The occurrence/index of the data to replace (default is "0" to replace all occurrences).
 */
std::string parseHexDataAtCustomOffset(const std::string& filePath, const std::string& customAsciiPattern, const std::string& offsetStr, size_t length, size_t occurrence = 0) {
    std::string cacheKey = filePath + '?' + customAsciiPattern + '?' + std::to_string(occurrence);
    int hexSum = -1;

    auto cachedResult = hexSumCache.find(cacheKey);
    if (cachedResult != hexSumCache.end()) {
        hexSum = std::stoi(cachedResult->second);
    } else {
        std::string customHexPattern = asciiToHex(customAsciiPattern); // Function should cache its results if expensive
        std::vector<std::string> offsets = findHexDataOffsets(filePath, customHexPattern); // Consider optimizing this search
        
        if (!offsets.empty() && offsets.size() > occurrence) {
            hexSum = std::stoi(offsets[occurrence]);
            hexSumCache[cacheKey] = std::to_string(hexSum);
        } else {
            logMessage("Offset not found.");
            return "";
        }
    }
    
    std::streampos totalOffset = hexSum + std::stoll(offsetStr);
    std::vector<char> hexBuffer(length);
    std::vector<char> hexStream(length * 2);

    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        logMessage("Failed to open the file.");
        return "";
    }
    
    file.seekg(totalOffset);
    if (!file) {
        logMessage("Error seeking to offset.");
        return "";
    }

    file.read(hexBuffer.data(), length);
    if (file.gcount() == static_cast<std::streamsize>(length)) {
        const char hexDigits[] = "0123456789ABCDEF";
        for (size_t i = 0; i < length; ++i) {
            hexStream[i * 2] = hexDigits[(hexBuffer[i] >> 4) & 0xF];
            hexStream[i * 2 + 1] = hexDigits[hexBuffer[i] & 0xF];
        }
    } else {
        logMessage("Error reading data from file or end of file reached.");
        return "";
    }

    file.close();
    std::string result(hexStream.begin(), hexStream.end());
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);

    return result;
}



/**
 * @brief Finds and replaces hexadecimal data in a file.
 *
 * This function searches for occurrences of hexadecimal data in a binary file
 * and replaces them with a specified hexadecimal replacement data.
 *
 * @param filePath The path to the binary file.
 * @param hexDataToReplace The hexadecimal data to search for and replace.
 * @param hexDataReplacement The hexadecimal data to replace with.
 * @param occurrence The occurrence/index of the data to replace (default is "0" to replace all occurrences).
 */

std::string replaceHexPlaceholder(const std::string& arg, const std::string& hexPath) {
    std::string replacement = arg;
    std::string searchString = "{hex_file(";
    
    size_t startPos = replacement.find(searchString);
    size_t endPos = replacement.find(")}");
    
    if (startPos != std::string::npos && endPos != std::string::npos && endPos > startPos) {
        std::string placeholderContent = replacement.substr(startPos + searchString.length(), endPos - startPos - searchString.length());
        
        // Split the placeholder content into its components (customAsciiPattern, offsetStr, length)
        std::vector<std::string> components;
        std::istringstream componentStream(placeholderContent);
        std::string component;
        
        while (std::getline(componentStream, component, ',')) {
            components.push_back(trim(component));
        }
        
        if (components.size() == 3) {
            // Extract individual components
            std::string customAsciiPattern = components[0];
            std::string offsetStr = components[1];
            size_t length = std::stoul(components[2]);
            
            // Call the parsing function and replace the placeholder
            std::string parsedResult = parseHexDataAtCustomOffset(hexPath, customAsciiPattern, offsetStr, length);
            
            
            //std::string parsedResult = customAsciiPattern+offsetStr;
            
            // Only replace if parsedResult returns a non-empty string
            if (!parsedResult.empty()) {
                // Replace the entire placeholder with the parsed result
                replacement.replace(startPos, endPos - startPos + searchString.length() + 2, parsedResult);
            }
        }
    }
    
    return replacement;
}
