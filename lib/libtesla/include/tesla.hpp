/********************************************************************************
 * Custom Fork Information
 * 
 * File: tesla.hpp
 * Author: ppkantorski
 * Description: 
 *   This file serves as the core logic for the Ultrahand Overlay project's custom fork
 *   of libtesla, an overlay executor. Within this file, you will find a collection of
 *   functions, menu structures, and interaction logic designed to facilitate the
 *   smooth execution and flexible customization of overlays within the project.
 *
 *   For the latest updates and contributions, visit the project's GitHub repository.
 *   (GitHub Repository: https://github.com/ppkantorski/Ultrahand-Overlay)
 *
 *   Note: Please be aware that this notice cannot be altered or removed. It is a part
 *   of the project's documentation and must remain intact.
 *
 *  Copyright (c) 2024 ppkantorski
 ********************************************************************************/

/**
 * Copyright (C) 2020 werwolv
 *
 * This file is part of libtesla.
 *
 * libtesla is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libtesla is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libtesla.  If not, see <http://www.gnu.org/licenses/>.
 */


#pragma once

#include <switch.h>

#include <stdlib.h>
#include <strings.h>
#include <math.h>

#include <algorithm>
#include <cstring>
#include <cwctype>
#include <string>
#include <functional>
#include <type_traits>
#include <mutex>
#include <memory>
#include <chrono>
#include <list>
#include <stack>
#include <map>
//#include <filesystem> // Comment out filesystem

// CUSTOM SECTION START
#include "../../../source/ini_funcs.hpp"
#include "../../../source/json_funcs.hpp"

static std::unordered_map<std::string, std::string> hexSumCache;

/**
 * @brief Shutdown modes for the Ultrahand-Overlay project.
 *
 * These macros define the shutdown modes used in the Ultrahand-Overlay project:
 * - `SpsmShutdownMode_Normal`: Normal shutdown mode.
 * - `SpsmShutdownMode_Reboot`: Reboot mode.
 */
#define SpsmShutdownMode_Normal 0
#define SpsmShutdownMode_Reboot 1

/**
 * @brief Key mapping macros for button keys.
 *
 * These macros define button keys for the Ultrahand-Overlay project to simplify key mappings.
 * For example, `KEY_A` represents the `HidNpadButton_A` key.
 */
#define KEY_A HidNpadButton_A
#define KEY_B HidNpadButton_B
#define KEY_X HidNpadButton_X
#define KEY_Y HidNpadButton_Y
#define KEY_L HidNpadButton_L
#define KEY_R HidNpadButton_R
#define KEY_ZL HidNpadButton_ZL
#define KEY_ZR HidNpadButton_ZR
#define KEY_PLUS HidNpadButton_Plus
#define KEY_MINUS HidNpadButton_Minus
#define KEY_DUP HidNpadButton_Up
#define KEY_DDOWN HidNpadButton_Down
#define KEY_DLEFT HidNpadButton_Left
#define KEY_DRIGHT HidNpadButton_Right
#define KEY_SL HidNpadButton_AnySL
#define KEY_SR HidNpadButton_AnySR
#define KEY_LSTICK HidNpadButton_StickL
#define KEY_RSTICK HidNpadButton_StickR
#define KEY_UP (HidNpadButton_Up | HidNpadButton_StickLUp | HidNpadButton_StickRUp)
#define KEY_DOWN (HidNpadButton_Down | HidNpadButton_StickLDown | HidNpadButton_StickRDown)
#define KEY_LEFT (HidNpadButton_Left | HidNpadButton_StickLLeft | HidNpadButton_StickRLeft)
#define KEY_RIGHT (HidNpadButton_Right | HidNpadButton_StickLRight | HidNpadButton_StickRRight)


// Define a mask with all possible key flags
constexpr u64 ALL_KEYS_MASK = 
    KEY_A | KEY_B | KEY_X | KEY_Y |
    KEY_DUP | KEY_DDOWN | KEY_DLEFT | KEY_DRIGHT |
    KEY_L | KEY_R | KEY_ZL | KEY_ZR |
    KEY_SL | KEY_SR |
    KEY_LSTICK | KEY_RSTICK |
    KEY_PLUS | KEY_MINUS;



static bool useCombo2 = false;
static bool updateMenuCombos = false;
/**
 * @brief Ultrahand-Overlay Input Macros
 *
 * This block of code defines macros for handling input in the Ultrahand-Overlay project.
 * These macros simplify the mapping of input events to corresponding button keys and
 * provide aliases for touch and joystick positions.
 *
 * The macros included in this block are:
 *
 * - `touchPosition`: An alias for a constant `HidTouchState` pointer.
 * - `touchInput`: An alias for `&touchPos`, representing touch input.
 * - `JoystickPosition`: An alias for `HidAnalogStickState`, representing joystick input.
 *
 * These macros are utilized within the Ultrahand-Overlay project to manage and interpret
 * user input, including touch and joystick events.
 */
#define touchPosition const HidTouchState
#define touchInput &touchPos
#define JoystickPosition HidAnalogStickState



// For improving the speed of hexing consecutively with the same file and asciiPattern.
//static std::unordered_map<std::string, std::string> hexSumCache;

//std::string highlightColor1Str = "#2288CC";;
//std::string highlightColor2Str = "#88FFFF";;

// Pre-defined symbols
static const std::string OPTION_SYMBOL = "\u22EF";
static const std::string DROPDOWN_SYMBOL = "\u25B6";
static const std::string CHECKMARK_SYMBOL = "\uE14B";
static const std::string CROSSMARK_SYMBOL = "\uE14C";
static const std::string DOWNLOAD_SYMBOL = "\u2193";
static const std::string STAR_SYMBOL = "\u2605";


//float customRound(float num) {
//    if (num >= 0) {
//        return floor(num + 0.5);
//    } else {
//        return ceil(num - 0.5);
//    }
//}

// English string definitions



float M_PI = 3.14159265358979323846;

static std::string DEFAULT_CHAR_WIDTH = "0.33";
static std::string UNAVAILABLE_SELECTION = "Not available";
static std::string OVERLAYS = "Overlays"; //defined in libTesla now
static std::string OVERLAY = "Overlay";
static std::string HIDDEN_OVERLAYS = "Hidden Overlays";
static std::string PACKAGES = "Packages"; //defined in libTesla now
static std::string PACKAGE = "Package";
static std::string HIDDEN_PACKAGES = "Hidden Packages";
static std::string HIDDEN = "Hidden";
static std::string HIDE_OVERLAY = "Hide Overlay";
static std::string HIDE_PACKAGE = "Hide Package";
static std::string LAUNCH_ARGUMENTS = "Launch Arguments";
static std::string COMMANDS = "Commands";
static std::string SETTINGS = "Settings";
static std::string MAIN_SETTINGS = "Main Settings";
static std::string UI_SETTINGS = "UI Settings";
static std::string WIDGET = "Widget";
static std::string CLOCK = "Clock";
static std::string BATTERY = "Battery";
static std::string SOC_TEMPERATURE = "SOC Temperature";
static std::string PCB_TEMPERATURE = "PCB Temperature";
static std::string MISCELLANEOUS = "Miscellaneous";
static std::string MENU_ITEMS = "Menu Items";
static std::string USER_GUIDE = "User Guide";
static std::string VERSION_LABELS = "Version Labels";
static std::string KEY_COMBO = "Key Combo";
static std::string LANGUAGE = "Language";
static std::string OVERLAY_INFO = "Overlay Info";
static std::string SOFTWARE_UPDATE = "Software Update";
static std::string UPDATE_ULTRAHAND = "Update Ultrahand";
static std::string UPDATE_LANGUAGES = "Update Languages";
static std::string THEME = "Theme";
static std::string DEFAULT = "default";
static std::string ROOT_PACKAGE = "Root Package";
static std::string SORT_PRIORITY = "Sort Priority";
static std::string FAILED_TO_OPEN = "Failed to open file";
static std::string CLEAN_LABELS = "Clean Versions";
static std::string OVERLAY_LABELS = "Overlay Versions";
static std::string PACKAGE_LABELS = "Package Versions";
static std::string ON = "On";
static std::string OFF = "Off";
static std::string PACKAGE_INFO = "Package Info";
static std::string TITLE = "Title";
static std::string VERSION = "Version";
static std::string CREATOR = "Creator(s)";
static std::string ABOUT = "About";
static std::string CREDITS = "Credits";
static std::string OK = "OK";
static std::string BACK = "Back";
static std::string REBOOT = "Reboot";
static std::string SHUTDOWN = "Shutdown";
static std::string GAP_1 = "     ";
static std::string GAP_2 = "  ";
static std::string USERGUIDE_OFFSET = "162";
static std::string SETTINGS_MENU = "Settings Menu";
static std::string SCRIPT_OVERLAY = "Script Overlay";
static std::string STAR_FAVORITE = "Star/Favorite";
static std::string APP_SETTINGS = "App Settings";
static std::string ON_MAIN_MENU = "on Main Menu";
static std::string ON_A_COMMAND = "on a command";
static std::string ON_OVERLAY_PACKAGE = "on overlay/package";

static std::string SUNDAY = "Sunday ";
static std::string MONDAY = "Monday ";
static std::string TUESDAY = "Tuesday ";
static std::string WEDNESDAY = "Wednesday ";
static std::string THURSDAY = "Thursday ";
static std::string FRIDAY = "Friday ";
static std::string SATURDAY = "Saturday ";

static std::string JANUARY = "January ";
static std::string FEBRUARY = "February ";
static std::string MARCH = "March ";
static std::string APRIL = "April ";
static std::string MAY = "May ";
static std::string JUNE = "June ";
static std::string JULY = "July ";
static std::string AUGUST = "August ";
static std::string SEPTEMBER = "September ";
static std::string OCTOBER = "October ";
static std::string NOVEMBER = "November ";
static std::string DECEMBER = "December ";

static std::string SUN = "Sun ";
static std::string MON = "Mon ";
static std::string TUE = "Tue ";
static std::string WED = "Wed ";
static std::string THU = "Thu ";
static std::string FRI = "Fri ";
static std::string SAT = "Sat ";

static std::string JAN = "Jan ";
static std::string FEB = "Feb ";
static std::string MAR = "Mar ";
static std::string APR = "Apr ";
static std::string MAY_ABBR = "May ";
static std::string JUN = "Jun ";
static std::string JUL = "Jul ";
static std::string AUG = "Aug ";
static std::string SEP = "Sep ";
static std::string OCT = "Oct ";
static std::string NOV = "Nov ";
static std::string DEC = "Dec ";

// Constant string definitions (English)
void reinitializeLangVars() {
    DEFAULT_CHAR_WIDTH = "0.33";
    UNAVAILABLE_SELECTION = "Not available";
    OVERLAYS = "Overlays"; //defined in libTesla now
    OVERLAY = "Overlay";
    HIDDEN_OVERLAYS = "Hidden Overlays";
    PACKAGES = "Packages"; //defined in libTesla now
    PACKAGE = "Package";
    HIDDEN_PACKAGES = "Hidden Packages";
    HIDDEN = "Hidden";
    HIDE_OVERLAY = "Hide Overlay";
    HIDE_PACKAGE = "Hide Package";
    LAUNCH_ARGUMENTS = "Launch Arguments";
    COMMANDS = "Commands";
    SETTINGS = "Settings";
    MAIN_SETTINGS = "Main Settings";
    UI_SETTINGS = "UI Settings";
    WIDGET = "Widget";
    CLOCK = "Clock";
    BATTERY = "Battery";
    SOC_TEMPERATURE = "SOC Temperature";
    PCB_TEMPERATURE = "PCB Temperature";
    MISCELLANEOUS = "Miscellaneous";
    MENU_ITEMS = "Menu Items";
    USER_GUIDE = "User Guide";
    VERSION_LABELS = "Version Labels";
    KEY_COMBO = "Key Combo";
    LANGUAGE = "Language";
    OVERLAY_INFO = "Overlay Info";
    SOFTWARE_UPDATE = "Software Update";
    UPDATE_ULTRAHAND = "Update Ultrahand";
    UPDATE_LANGUAGES = "Update Languages";
    THEME = "Theme";
    DEFAULT = "default";
    ROOT_PACKAGE = "Root Package";
    SORT_PRIORITY = "Sort Priority";
    FAILED_TO_OPEN = "Failed to open file";
    CLEAN_LABELS = "Clean Versions";
    OVERLAY_LABELS = "Overlay Versions";
    PACKAGE_LABELS = "Package Versions";
    ON = "On";
    OFF = "Off";
    PACKAGE_INFO = "Package Info";
    TITLE = "Title";
    VERSION = "Version";
    CREATOR = "Creator(s)";
    ABOUT = "About";
    CREDITS = "Credits";
    OK = "OK";
    BACK = "Back";
    REBOOT = "Reboot";
    SHUTDOWN = "Shutdown";
    GAP_1 = "     ";
    GAP_2 = "  ";
    USERGUIDE_OFFSET = "162";
    SETTINGS_MENU = "Settings Menu";
    SCRIPT_OVERLAY = "Script Overlay";
    STAR_FAVORITE = "Star/Favorite";
    APP_SETTINGS = "App Settings";
    ON_MAIN_MENU = "on Main Menu";
    ON_A_COMMAND = "on a command";
    ON_OVERLAY_PACKAGE = "on overlay/package";
    
    SUNDAY = "Sunday ";
    MONDAY = "Monday ";
    TUESDAY = "Tuesday ";
    WEDNESDAY = "Wednesday ";
    THURSDAY = "Thursday ";
    FRIDAY = "Friday ";
    SATURDAY = "Saturday ";
    
    JANUARY = "January ";
    FEBRUARY = "February ";
    MARCH = "March ";
    APRIL = "April ";
    MAY = "May ";
    JUNE = "June ";
    JULY = "July ";
    AUGUST = "August ";
    SEPTEMBER = "September ";
    OCTOBER = "October ";
    NOVEMBER = "November ";
    DECEMBER = "December ";
    
    SUN = "Sun ";
    MON = "Mon ";
    TUE = "Tue ";
    WED = "Wed ";
    THU = "Thu ";
    FRI = "Fri ";
    SAT = "Sat ";
    
    JAN = "Jan ";
    FEB = "Feb ";
    MAR = "Mar ";
    APR = "Apr ";
    MAY_ABBR = "May ";
    JUN = "Jun ";
    JUL = "Jul ";
    AUG = "Aug ";
    SEP = "Sep ";
    OCT = "Oct ";
    NOV = "Nov ";
    DEC = "Dec ";
}



// Define the updateIfNotEmpty function
void updateIfNotEmpty(std::string& constant, const char* jsonKey, json_t* jsonData) {
    std::string newValue = getStringFromJson(jsonData, jsonKey);
    if (!newValue.empty()) {
        constant = newValue;
    }
}

void parseLanguage(std::string langFile) {
    json_t* langData = readJsonFromFile(langFile);
    
    // Use the updateIfNotEmpty function to update global variables
    updateIfNotEmpty(DEFAULT_CHAR_WIDTH, "DEFAULT_CHAR_WIDTH", langData);
    updateIfNotEmpty(UNAVAILABLE_SELECTION, "UNAVAILABLE_SELECTION", langData);
    updateIfNotEmpty(OVERLAYS, "OVERLAYS", langData);
    updateIfNotEmpty(OVERLAY, "OVERLAY", langData);
    updateIfNotEmpty(HIDDEN_OVERLAYS, "HIDDEN_OVERLAYS", langData);
    updateIfNotEmpty(PACKAGES, "PACKAGES", langData);
    updateIfNotEmpty(PACKAGE, "PACKAGE", langData);
    updateIfNotEmpty(HIDDEN_PACKAGES, "HIDDEN_PACKAGES", langData);
    updateIfNotEmpty(HIDDEN, "HIDDEN", langData);
    updateIfNotEmpty(HIDE_PACKAGE, "HIDE_PACKAGE", langData);
    updateIfNotEmpty(HIDE_OVERLAY, "HIDE_OVERLAY", langData);
    updateIfNotEmpty(LAUNCH_ARGUMENTS, "LAUNCH_ARGUMENTS", langData);
    updateIfNotEmpty(COMMANDS, "COMMANDS", langData);
    updateIfNotEmpty(SETTINGS, "SETTINGS", langData);
    updateIfNotEmpty(MAIN_SETTINGS, "MAIN_SETTINGS", langData);
    updateIfNotEmpty(UI_SETTINGS, "UI_SETTINGS", langData);
    updateIfNotEmpty(WIDGET, "WIDGET", langData);
    updateIfNotEmpty(CLOCK, "CLOCK", langData);
    updateIfNotEmpty(BATTERY, "BATTERY", langData);
    updateIfNotEmpty(SOC_TEMPERATURE, "SOC_TEMPERATURE", langData);
    updateIfNotEmpty(PCB_TEMPERATURE, "PCB_TEMPERATURE", langData);
    updateIfNotEmpty(MISCELLANEOUS, "MISCELLANEOUS", langData);
    updateIfNotEmpty(MENU_ITEMS, "MENU_ITEMS", langData);
    updateIfNotEmpty(USER_GUIDE, "USER_GUIDE", langData);
    updateIfNotEmpty(VERSION_LABELS, "VERSION_LABELS", langData);
    updateIfNotEmpty(KEY_COMBO, "KEY_COMBO", langData);
    updateIfNotEmpty(LANGUAGE, "LANGUAGE", langData);
    updateIfNotEmpty(OVERLAY_INFO, "OVERLAY_INFO", langData);
    updateIfNotEmpty(SOFTWARE_UPDATE, "SOFTWARE_UPDATE", langData);
    updateIfNotEmpty(UPDATE_ULTRAHAND, "UPDATE_ULTRAHAND", langData);
    updateIfNotEmpty(UPDATE_LANGUAGES, "UPDATE_LANGUAGES", langData);
    updateIfNotEmpty(THEME, "THEME", langData);
    updateIfNotEmpty(DEFAULT, "DEFAULT", langData);
    updateIfNotEmpty(ROOT_PACKAGE, "ROOT_PACKAGE", langData);
    updateIfNotEmpty(SORT_PRIORITY, "SORT_PRIORITY", langData);
    updateIfNotEmpty(FAILED_TO_OPEN, "FAILED_TO_OPEN", langData);
    updateIfNotEmpty(CLEAN_LABELS, "CLEAN_LABELS", langData);
    updateIfNotEmpty(OVERLAY_LABELS, "OVERLAY_LABELS", langData);
    updateIfNotEmpty(PACKAGE_LABELS, "PACKAGE_LABELS", langData);
    updateIfNotEmpty(ON, "ON", langData);
    updateIfNotEmpty(OFF, "OFF", langData);
    updateIfNotEmpty(PACKAGE_INFO, "PACKAGE_INFO", langData);
    updateIfNotEmpty(TITLE, "TITLE", langData);
    updateIfNotEmpty(VERSION, "VERSION", langData);
    updateIfNotEmpty(CREATOR, "CREATOR", langData);
    updateIfNotEmpty(ABOUT, "ABOUT", langData);
    updateIfNotEmpty(CREDITS, "CREDITS", langData);
    updateIfNotEmpty(OK, "OK", langData);
    updateIfNotEmpty(BACK, "BACK", langData);
    updateIfNotEmpty(REBOOT, "REBOOT", langData);
    updateIfNotEmpty(SHUTDOWN, "SHUTDOWN", langData);
    updateIfNotEmpty(GAP_1, "GAP_1", langData);
    updateIfNotEmpty(GAP_2, "GAP_2", langData);
    updateIfNotEmpty(USERGUIDE_OFFSET, "USERGUIDE_OFFSET", langData);
    updateIfNotEmpty(SETTINGS_MENU, "SETTINGS_MENU", langData);
    updateIfNotEmpty(SCRIPT_OVERLAY, "SCRIPT_OVERLAY", langData);
    updateIfNotEmpty(STAR_FAVORITE, "STAR_FAVORITE", langData);
    updateIfNotEmpty(APP_SETTINGS, "APP_SETTINGS", langData);
    updateIfNotEmpty(ON_MAIN_MENU, "ON_MAIN_MENU", langData);
    updateIfNotEmpty(ON_A_COMMAND, "ON_A_COMMAND", langData);
    updateIfNotEmpty(ON_OVERLAY_PACKAGE, "ON_OVERLAY_PACKAGE", langData);
    
    // Day and Month names
    updateIfNotEmpty(SUNDAY, "SUNDAY", langData);
    updateIfNotEmpty(MONDAY, "MONDAY", langData);
    updateIfNotEmpty(TUESDAY, "TUESDAY", langData);
    updateIfNotEmpty(WEDNESDAY, "WEDNESDAY", langData);
    updateIfNotEmpty(THURSDAY, "THURSDAY", langData);
    updateIfNotEmpty(FRIDAY, "FRIDAY", langData);
    updateIfNotEmpty(SATURDAY, "SATURDAY", langData);
    
    updateIfNotEmpty(JANUARY, "JANUARY", langData);
    updateIfNotEmpty(FEBRUARY, "FEBRUARY", langData);
    updateIfNotEmpty(MARCH, "MARCH", langData);
    updateIfNotEmpty(APRIL, "APRIL", langData);
    updateIfNotEmpty(MAY, "MAY", langData);
    updateIfNotEmpty(JUNE, "JUNE", langData);
    updateIfNotEmpty(JULY, "JULY", langData);
    updateIfNotEmpty(AUGUST, "AUGUST", langData);
    updateIfNotEmpty(SEPTEMBER, "SEPTEMBER", langData);
    updateIfNotEmpty(OCTOBER, "OCTOBER", langData);
    updateIfNotEmpty(NOVEMBER, "NOVEMBER", langData);
    updateIfNotEmpty(DECEMBER, "DECEMBER", langData);
    
    updateIfNotEmpty(SUN, "SUN", langData);
    updateIfNotEmpty(MON, "MON", langData);
    updateIfNotEmpty(TUE, "TUE", langData);
    updateIfNotEmpty(WED, "WED", langData);
    updateIfNotEmpty(THU, "THU", langData);
    updateIfNotEmpty(FRI, "FRI", langData);
    updateIfNotEmpty(SAT, "SAT", langData);
    
    updateIfNotEmpty(JAN, "JAN", langData);
    updateIfNotEmpty(FEB, "FEB", langData);
    updateIfNotEmpty(MAR, "MAR", langData);
    updateIfNotEmpty(APR, "APR", langData);
    updateIfNotEmpty(MAY_ABBR, "MAY_ABBR", langData);
    updateIfNotEmpty(JUN, "JUN", langData);
    updateIfNotEmpty(JUL, "JUL", langData);
    updateIfNotEmpty(AUG, "AUG", langData);
    updateIfNotEmpty(SEP, "SEP", langData);
    updateIfNotEmpty(OCT, "OCT", langData);
    updateIfNotEmpty(NOV, "NOV", langData);
    updateIfNotEmpty(DEC, "DEC", langData);
    
    // Free langData
    if (langData != nullptr) {
        json_decref(langData);
        langData = nullptr;
    }
}


void localizeTimeStr(char* timeStr) {
    // Define mappings for day and month names
    std::vector<std::pair<std::string, std::string>> dayMappings = {
        {"Sun", SUN},
        {"Mon", MON},
        {"Tue", TUE},
        {"Wed", WED},
        {"Thu", THU},
        {"Fri", FRI},
        {"Sat", SAT},
        {"Sunday", SUNDAY},
        {"Monday", MONDAY},
        {"Tuesday", TUESDAY},
        {"Wednesday", WEDNESDAY},
        {"Thursday", THURSDAY},
        {"Friday", FRIDAY},
        {"Saturday", SATURDAY}
    };
    
    std::vector<std::pair<std::string, std::string>> monthMappings = {
        {"Jan", JAN},
        {"Feb", FEB},
        {"Mar", MAR},
        {"Apr", APR},
        {"May", MAY_ABBR},
        {"Jun", JUN},
        {"Jul", JUL},
        {"Aug", AUG},
        {"Sep", SEP},
        {"Oct", OCT},
        {"Nov", NOV},
        {"Dec", DEC},
        {"January", JANUARY},
        {"February", FEBRUARY},
        {"March", MARCH},
        {"April", APRIL},
        {"May", MAY},
        {"June", JUNE},
        {"July", JULY},
        {"August", AUGUST},
        {"September", SEPTEMBER},
        {"October", OCTOBER},
        {"November", NOVEMBER},
        {"December", DECEMBER}
    };
    
    std::string timeStrCopy = timeStr; // Convert the char array to a string for processing
    
    // Replace abbreviated day names with their all-capital versions
    size_t pos;
    for (const auto &dayMapping : dayMappings) {
        pos = timeStrCopy.find(dayMapping.first);
        while (pos != std::string::npos) {
            timeStrCopy.replace(pos, dayMapping.first.length(), dayMapping.second);
            pos = timeStrCopy.find(dayMapping.first, pos + dayMapping.second.length());
        }
    }
    
    // Replace abbreviated month names with their all-capital versions
    for (const auto &monthMapping : monthMappings) {
        pos = timeStrCopy.find(monthMapping.first);
        while (pos != std::string::npos) {
            timeStrCopy.replace(pos, monthMapping.first.length(), monthMapping.second);
            pos = timeStrCopy.find(monthMapping.first, pos + monthMapping.second.length());
        }
    }
    
    // Copy the modified string back to the character array
    strcpy(timeStr, timeStrCopy.c_str());
}




// Map of character widths
static std::unordered_map<char, float> characterWidths = {
    {'°', 0.25},
    {'%', 0.98}, // not calibrated
    {':', 0.25}, // not calibrated
    {' ', 0.3},
    {'+', 0.75},
    {'-', 0.36},
    {'_', 0.47},
    {'&', 0.74},
    {'(', 0.36},
    {')', 0.36},
    {'[', 0.3635},
    {']', 0.3635},
    {'A', 0.78},
    {'B', 0.644},
    {'C', 0.76},
    {'D', 0.8},
    {'E', 0.6},
    {'F', 0.6},
    {'G', 0.8},
    {'H', 0.72},
    {'I', 0.26},
    {'J', 0.48},
    {'K', 0.68},
    {'L', 0.46},
    {'M', 0.98},
    {'N', 0.82},
    {'O', 0.92},
    {'P', 0.6},
    {'Q', 0.9},
    {'R', 0.6},
    {'S', 0.56},
    {'T', 0.64},
    {'U', 0.80},
    {'V', 0.76},
    {'W', 1.14},
    {'X', 0.66},
    {'Y', 0.66},
    {'Z', 0.74},
    {'a', 0.6},
    {'b', 0.66},
    {'c', 0.56},
    {'d', 0.66},
    {'e', 0.6},
    {'f', 0.28},
    {'g', 0.6},
    {'h', 0.6},
    {'i', 0.25},
    {'j', 0.36},
    {'k', 0.56},
    {'l', 0.28},
    {'m', 0.94},
    {'n', 0.582},
    {'o', 0.656},
    {'p', 0.66},
    {'q', 0.68},
    {'r', 0.36},
    {'s', 0.5},
    {'t', 0.37},
    {'u', 0.6},
    {'v', 0.50},
    {'w', 0.87},
    {'x', 0.54},
    {'y', 0.53},
    {'z', 0.5},
    {'0', 0.66},
    {'1', 0.66},
    {'2', 0.66},
    {'3', 0.66},
    {'4', 0.66},
    {'5', 0.66},
    {'6', 0.66},
    {'7', 0.66},
    {'8', 0.66},
    {'9', 0.66}
};

bool isValidHexColor(const std::string& hexColor) {
    // Check if the string is a valid hexadecimal color of the format "#RRGGBB"
    if (hexColor.size() != 6) {
        return false; // Must be exactly 6 characters long
    }
    
    for (char c : hexColor) {
        if (!isxdigit(c)) {
            return false; // Must contain only hexadecimal digits (0-9, A-F, a-f)
        }
    }
    
    return true;
}

// Variables for touch commands
static bool simulatedBack = false;
static bool simulatedBackComplete = true;
static bool simulatedSelect = false;
static bool simulatedSelectComplete = true;
static bool simulatedNextPage = false;
static bool simulatedNextPageComplete = true;
static bool simulatedMenu = false;
static bool simulatedMenuComplete = true;
static bool stillTouching = false;
static bool interruptedTouch = false;
static bool touchInBounds = false;


// Battery implementation
static bool powerInitialized = false;
static bool powerCacheInitialized;
static uint32_t powerCacheCharge;
//static float powerConsumption;
static bool powerCacheIsCharging;
static PsmSession powerSession;

// Define variables to store previous battery charge and time
static uint32_t prevBatteryCharge = 0;
static uint64_t timeOut = 0;
static char chargeString[6];  // Need space for the null terminator and the percentage sign

static uint32_t batteryCharge;
static bool isCharging;
//static bool validPower;

bool powerGetDetails(uint32_t *batteryCharge, bool *isCharging) {
    PsmChargerType charger = PsmChargerType_Unconnected;
    bool hwReadsSucceeded = false;
    bool use_cache = false;
    Result rc = 0;
    
    *isCharging = false;
    *batteryCharge = 0;
    
    if (powerInitialized) {
        if (powerCacheInitialized) {
            rc = psmWaitStateChangeEvent(&powerSession, 0);
            
            if (R_FAILED(rc)) use_cache = true;
        }
        
        rc = psmGetBatteryChargePercentage(batteryCharge);
        hwReadsSucceeded = R_SUCCEEDED(rc);
        if (use_cache) {
            *isCharging = powerCacheIsCharging;
        }
        else {
            rc = psmGetChargerType(&charger);
            hwReadsSucceeded &= R_SUCCEEDED(rc);
            *isCharging = (charger != PsmChargerType_Unconnected);
        }
        
        powerCacheCharge = *batteryCharge;
        powerCacheIsCharging = *isCharging;
        powerCacheInitialized = true;
    }
    
    return hwReadsSucceeded;
}

void powerInit(void) {
    uint32_t charge = 0;
    isCharging = 0;
    
    powerCacheInitialized = false;
    powerCacheCharge = 0;
    powerCacheIsCharging = false;
    
    if (!powerInitialized) {
        Result rc = psmInitialize();
        if (R_SUCCEEDED(rc)) {
            rc = psmBindStateChangeEvent(&powerSession, 1, 1, 1);
            
            if (R_FAILED(rc)) psmExit();
            if (R_SUCCEEDED(rc)) {
                powerInitialized = true;
                powerGetDetails(&charge, &isCharging);
                
                // Initialize prevBatteryCharge here with a non-zero value if needed.
                prevBatteryCharge = charge;
            }
        }
    }
}

void powerExit(void) {
    if (powerInitialized) {
        psmUnbindStateChangeEvent(&powerSession);
        psmExit();
        powerInitialized = false;
        powerCacheInitialized = false;
    }
}


// Temperature Implementation
static s32 PCB_temperature, SOC_temperature;
static Service* g_tsSrv;
Result tsCheck = 1;
Result tcCheck = 1;

Result tsOpenTsSession(Service* &serviceSession, TsSession* out, TsDeviceCode device_code) {
    return serviceDispatchIn(serviceSession, 4, device_code,
        .out_num_objects = 1,
        .out_objects = &out->s,
    );
}

void tsCloseTsSession(TsSession* in) {
    serviceClose(&in->s);
}

Result tsGetTemperatureWithTsSession(TsSession* ITs, float* temperature) {
    return serviceDispatchOut(&ITs->s, 4, *temperature);
}


bool thermalstatusInit(void) {
    
    tcCheck = tcInitialize();
    tsCheck = tsInitialize();
    if (R_SUCCEEDED(tsCheck)) {
        g_tsSrv = tsGetServiceSession();
    } else
        return false;
    
    return true;
}

void thermalstatusExit(void) {
    tsExit();
    tcExit();
}

bool thermalstatusGetDetailsPCB(s32* temperature) {
    TsSession ts_session;
    Result rc = tsOpenTsSession(g_tsSrv, &ts_session, TsDeviceCode_LocationInternal);
    if (R_SUCCEEDED(rc)) {
        float temp_float;
        if (R_SUCCEEDED(tsGetTemperatureWithTsSession(&ts_session, &temp_float))) {
            *temperature = static_cast<s32>(temp_float);
        }
        tsSessionClose(&ts_session);
        return true;
    }
    return false;
}

bool thermalstatusGetDetailsSOC(s32* temperature) {
    TsSession ts_session;
    Result rc = tsOpenTsSession(g_tsSrv, &ts_session, TsDeviceCode_LocationExternal);
    if (R_SUCCEEDED(rc)) {
        float temp_float;
        if (R_SUCCEEDED(tsGetTemperatureWithTsSession(&ts_session, &temp_float))) {
            *temperature = static_cast<s32>(temp_float);
        }
        tsSessionClose(&ts_session);
        return true;
    }
    return false;
}







//s32 SOC_temperature, PCB_temperature;
//static TsSession g_tsInternalSession, g_tsExternalSession;
//
//
//bool thermalstatusInit(void) {
//    if (R_FAILED(tsInitialize()))
//        return false;
//
//    if (hosversionAtLeast(17,0,0) && R_FAILED(tsOpenSession(&g_tsInternalSession, TsDeviceCode_LocationInternal)) && R_FAILED(tsOpenSession(&g_tsExternalSession, TsDeviceCode_LocationExternal)))
//        return false;
//
//    return true;
//}
//
//void thermalstatusExit(void) {
//    if (hosversionAtLeast(17,0,0)) {
//        tsSessionClose(&g_tsInternalSession);
//        tsSessionClose(&g_tsExternalSession);
//    }
//    tsExit();
//}
//
//bool thermalstatusGetDetails(s32 *temperature, std::string location = "internal") {
//    if (hosversionAtLeast(17,0,0)) {
//        float temp_float;
//        if ((location == "internal") && R_SUCCEEDED(tsSessionGetTemperature(&g_tsInternalSession, &temp_float))) {
//            *temperature = (int)temp_float;
//            return true;
//        } else if ((location == "external") && R_SUCCEEDED(tsSessionGetTemperature(&g_tsExternalSession, &temp_float))) {
//            *temperature = (int)temp_float;
//            return true;
//        } else {
//            return false;
//        }
//    } else {
//        if (location == "internal") {
//            return R_SUCCEEDED(tsGetTemperature(TsLocation_Internal, temperature));
//        } else {
//            return R_SUCCEEDED(tsGetTemperature(TsLocation_External, temperature));
//        }
//    }
//}




// Time implementation
struct timespec currentTime;
static const std::string DEFAULT_DT_FORMAT = "'%a %T'";
static std::string datetimeFormat = removeQuotes(DEFAULT_DT_FORMAT);


// Widget settings
static std::string hideClock, hideBattery, hidePCBTemp, hideSOCTemp;

void reinitializeWidgetVars() {
    hideClock = parseValueFromIniSection("/config/ultrahand/config.ini", "ultrahand", "hide_clock");
    hideBattery = parseValueFromIniSection("/config/ultrahand/config.ini", "ultrahand", "hide_battery");
    hideSOCTemp = parseValueFromIniSection("/config/ultrahand/config.ini", "ultrahand", "hide_soc_temp");
    hidePCBTemp = parseValueFromIniSection("/config/ultrahand/config.ini", "ultrahand", "hide_pcb_temp");
}

static std::string cleanVersionLabels, hideOverlayVersions, hidePackageVersions;

static std::string loaderInfo = envGetLoaderInfo();
static std::string versionLabel;

void reinitializeVersionLabels() {
    cleanVersionLabels = parseValueFromIniSection("/config/ultrahand/config.ini", "ultrahand", "clean_version_labels");
    hideOverlayVersions = parseValueFromIniSection("/config/ultrahand/config.ini", "ultrahand", "hide_overlay_versions");
    hidePackageVersions = parseValueFromIniSection("/config/ultrahand/config.ini", "ultrahand", "hide_package_versions");
    if (cleanVersionLabels == "true")
        versionLabel = APP_VERSION+std::string("   (")+ extractTitle(loaderInfo)+" "+cleanVersionLabel(loaderInfo)+std::string(")"); // Still needs to parse nx-ovlloader instead of hard coding it
    else
        versionLabel = APP_VERSION+std::string("   (")+ extractTitle(loaderInfo)+" v"+cleanVersionLabel(loaderInfo)+std::string(")");
}



// CUSTOM SECTION END

// Define this makro before including tesla.hpp in your main file. If you intend
// to use the tesla.hpp header in more than one source file, only define it once!
// #define TESLA_INIT_IMPL

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

#ifdef TESLA_INIT_IMPL
    #define STB_TRUETYPE_IMPLEMENTATION
#endif
#include "stb_truetype.h"

#pragma GCC diagnostic pop

#define ELEMENT_BOUNDS(elem) elem->getX()+4, elem->getY(), elem->getWidth()+4, elem->getHeight()

#define ASSERT_EXIT(x) if (R_FAILED(x)) std::exit(1)
#define ASSERT_FATAL(x) if (Result res = x; R_FAILED(res)) fatalThrow(res)

#define PACKED __attribute__((packed))
#define ALWAYS_INLINE inline __attribute__((always_inline))

/// Evaluates an expression that returns a result, and returns the result if it would fail.
#define TSL_R_TRY(resultExpr)           \
    ({                                  \
        const auto result = resultExpr; \
        if (R_FAILED(result)) {         \
            return result;              \
        }                               \
    })

using namespace std::literals::string_literals;
using namespace std::literals::chrono_literals;




namespace tsl {
    
    // Constants
    
    namespace cfg {
        
        constexpr u32 ScreenWidth = 1920;       ///< Width of the Screen
        constexpr u32 ScreenHeight = 1080;      ///< Height of the Screen
        
        extern u16 LayerWidth;                  ///< Width of the Tesla layer
        extern u16 LayerHeight;                 ///< Height of the Tesla layer
        extern u16 LayerPosX;                   ///< X position of the Tesla layer
        extern u16 LayerPosY;                   ///< Y position of the Tesla layer
        extern u16 FramebufferWidth;            ///< Width of the framebuffer
        extern u16 FramebufferHeight;           ///< Height of the framebuffer
        extern u64 launchCombo;                 ///< Overlay activation key combo
        extern u64 launchCombo2;                 ///< Overlay activation key combo
        
    }
    
    /**
     * @brief RGBA4444 Color structure
     */
    struct Color {
        
        union {
            struct {
                u16 r: 4, g: 4, b: 4, a: 4;
            } PACKED;
            u16 rgba;
        };
        
        constexpr inline Color(u16 raw): rgba(raw) {}
        constexpr inline Color(u8 r, u8 g, u8 b, u8 a): r(r), g(g), b(b), a(a) {}
        
    };
    
    Color GradientColor(float temperature) {
        // Ensure temperature is within the range [0, 100]
        temperature = std::max(0.0f, std::min(100.0f, temperature)); // Celsius
        
        // this is where colors are at their full
        float blueStart = 35.0f;
        float greenStart = 45.0f;
        float yellowStart = 55.0f;
        float redStart = 65.0f;
        
        // Initialize RGB values
        uint8_t r, g, b, a = 0xFF;
        
        if (temperature < blueStart) { // rgb 7, 7, 15 at blueStart
            r = 7;
            g = 7;
            b = 15;
        } else if (temperature >= blueStart && temperature < greenStart) {
            // Smooth color blending from (7 7 15) to (0 15 0)
            float t = (temperature - blueStart) / (greenStart - blueStart);
            r = static_cast<uint8_t>(7 - 7 * t);
            g = static_cast<uint8_t>(7 + 8 * t);
            b = static_cast<uint8_t>(15 - 15 * t);
        } else if (temperature >= greenStart && temperature < yellowStart) {
            // Smooth color blending from (0 15 0) to (15 15 0)
            float t = (temperature - greenStart) / (yellowStart - greenStart);
            r = static_cast<uint8_t>(15 * t);
            g = static_cast<uint8_t>(15);
            b = static_cast<uint8_t>(0);
        } else if (temperature >= yellowStart && temperature < redStart) {
            // Smooth color blending from (15 15 0) to (15 0 0)
            float t = (temperature - yellowStart) / (redStart - yellowStart);
            r = static_cast<uint8_t>(15);
            g = static_cast<uint8_t>(15 - 15 * t);
            b = static_cast<uint8_t>(0);
        } else {
            // Full red
            r = 15;
            g = 0;
            b = 0;
        }
        
        return Color(r, g, b, a);
    }
    
    Color RGB888(std::string hexColor, std::string defaultHexColor = "#FFFFFF", size_t alpha = 15) {
        // Remove the '#' character if it's present
        if (!hexColor.empty() && hexColor[0] == '#') {
            hexColor = hexColor.substr(1);
        }
        
        if (isValidHexColor(hexColor)) {
            //std::string r = hexColor.substr(0, 2); // Extract the first two characters (red component)
            //std::string g = hexColor.substr(2, 2); // Extract the next two characters (green component)
            //std::string b = hexColor.substr(4, 2); // Extract the last two characters (blue component)
            
            // Convert the RGBA8888 strings to RGBA4444
            uint8_t redValue = std::stoi(hexColor.substr(0, 2), nullptr, 16) >> 4;   // Right-shift by 4 bits
            uint8_t greenValue = std::stoi(hexColor.substr(2, 2), nullptr, 16) >> 4; // Right-shift by 4 bits
            uint8_t blueValue = std::stoi(hexColor.substr(4, 2), nullptr, 16) >> 4;  // Right-shift by 4 bits
            
            // Create a Color with the extracted RGB values
            
            return Color(redValue, greenValue, blueValue, alpha);
        }
        return RGB888(defaultHexColor);
    }
    std::tuple<float, float, float> hexToRGB444Floats(std::string hexColor, std::string defaultHexColor = "#FFFFFF") {
        // Remove the '#' character if it's present
        if (!hexColor.empty() && hexColor[0] == '#') {
            hexColor = hexColor.substr(1);
        }
        
        if (isValidHexColor(hexColor)) {
            unsigned int hexValue = std::stoul(hexColor, nullptr, 16);
            
            // Extract red, green, blue components from RGB888 to RGB444
            float red = static_cast<float>((hexValue >> 16) & 0xFF) / 255.0f * 15.0f;
            float green = static_cast<float>((hexValue >> 8) & 0xFF) / 255.0f * 15.0f;
            float blue = static_cast<float>((hexValue) & 0xFF) / 255.0f * 15.0f;
            
            return std::make_tuple(red, green, blue);
        }
        return hexToRGB444Floats(defaultHexColor);
    }
    
    
    
    namespace style {
        constexpr u32 ListItemDefaultHeight         = 70;       ///< Standard list item height
        constexpr u32 TrackBarDefaultHeight         = 90;       ///< Standard track bar height
        constexpr u8  ListItemHighlightSaturation   = 6;        ///< Maximum saturation of Listitem highlights
        constexpr u8  ListItemHighlightLength       = 22;       ///< Maximum length of Listitem highlights
        
        namespace color {
            constexpr Color ColorFrameBackground  = { 0x0, 0x0, 0x0, 0xD };   ///< Overlay frame background color
            constexpr Color ColorTransparent      = { 0x0, 0x0, 0x0, 0x0 };   ///< Transparent color
            constexpr Color ColorHighlight        = { 0x0, 0xF, 0xD, 0xF };   ///< Greenish highlight color
            constexpr Color ColorFrame            = { 0x7, 0x7, 0x7, 0x7 };   ///< Outer boarder color // CUSTOM MODIFICATION
            constexpr Color ColorHandle           = { 0x5, 0x5, 0x5, 0xF };   ///< Track bar handle color
            constexpr Color ColorText             = { 0xF, 0xF, 0xF, 0xF };   ///< Standard text color
            constexpr Color ColorDescription      = { 0xA, 0xA, 0xA, 0xF };   ///< Description text color
            constexpr Color ColorHeaderBar        = { 0xC, 0xC, 0xC, 0xF };   ///< Category header rectangle color
            constexpr Color ColorClickAnimation   = { 0x0, 0x2, 0x2, 0xF };   ///< Element click animation color
        }
    }
    
    //std::string highlightColor1Str = parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "highlight_color_1"); // format "X,X,X"
    //std::string highlightColor2Str = parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "highlight_color_2"); // format "X,X,X"
    
    // Declarations
    
    /**
     * @brief Direction in which focus moved before landing on
     *        the currently focused element
     */
    enum class FocusDirection {
        None,                       ///< Focus was placed on the element programatically without user input
        Up,                         ///< Focus moved upwards
        Down,                       ///< Focus moved downwards
        Left,                       ///< Focus moved from left to rigth
        Right                       ///< Focus moved from right to left
    };
    
    /**
     * @brief Current input controll mode
     *
     */
    enum class InputMode {
        Controller,                 ///< Input from controller
        Touch,                      ///< Touch input
        TouchScroll                 ///< Moving/scrolling touch input
    };
    
    class Overlay;
    namespace elm { class Element; }
    
    namespace impl {
        
        /**
         * @brief Overlay launch parameters
         */
        enum class LaunchFlags : u8 {
            None = 0,                       ///< Do nothing special at launch
            CloseOnExit        = BIT(0)     ///< Close the overlay the last Gui gets poped from the stack
        };
        
        [[maybe_unused]] static constexpr LaunchFlags operator|(LaunchFlags lhs, LaunchFlags rhs) {
            return static_cast<LaunchFlags>(u8(lhs) | u8(rhs));
        }
        
        /**
         * @brief Combo key mapping
         */
        struct KeyInfo {
            u64 key;
            const char* name;
            const char* glyph;
        };
        
        /**
         * @brief Combo key mappings
         *
         * Ordered as they should be displayed
         */
        constexpr std::array<KeyInfo, 18> KEYS_INFO = {{
            { HidNpadButton_L, "L", "\uE0A4" }, { HidNpadButton_R, "R", "\uE0A5" },
            { HidNpadButton_ZL, "ZL", "\uE0A6" }, { HidNpadButton_ZR, "ZR", "\uE0A7" },
            { HidNpadButton_AnySL, "SL", "\uE0A8" }, { HidNpadButton_AnySR, "SR", "\uE0A9" },
            { HidNpadButton_Left, "DLEFT", "\uE07B" }, { HidNpadButton_Up, "DUP", "\uE079" }, { HidNpadButton_Right, "DRIGHT", "\uE07C" }, { HidNpadButton_Down, "DDOWN", "\uE07A" },
            { HidNpadButton_A, "A", "\uE0A0" }, { HidNpadButton_B, "B", "\uE0A1" }, { HidNpadButton_X, "X", "\uE0A2" }, { HidNpadButton_Y, "Y", "\uE0A3" },
            { HidNpadButton_StickL, "LS", "\uE08A" }, { HidNpadButton_StickR, "RS", "\uE08B" },
            { HidNpadButton_Minus, "MINUS", "\uE0B6" }, { HidNpadButton_Plus, "PLUS", "\uE0B5" }
        }};
        
    }
    
    [[maybe_unused]] static void goBack();
    
    [[maybe_unused]] static void setNextOverlay(const std::string& ovlPath, std::string args = "");
    
    template<typename TOverlay, impl::LaunchFlags launchFlags = impl::LaunchFlags::CloseOnExit>
    int loop(int argc, char** argv);
    
    // Helpers
    
    namespace hlp {
        
        /**
         * @brief Wrapper for service initialization
         *
         * @param f wrapped function
         */
        template<typename F>
        static inline void doWithSmSession(F f) {
            smInitialize();
            f();
            smExit();
        }
        
        /**
         * @brief Wrapper for sd card access using stdio
         * @note Consider using raw fs calls instead as they are faster and need less space
         *
         * @param f wrapped function
         */
        template<typename F>
        static inline void doWithSDCardHandle(F f) {
            fsdevMountSdmc();
            f();
            fsdevUnmountDevice("sdmc");
        }
        
        /**
         * @brief Guard that will execute a passed function at the end of the current scope
         *
         * @param f wrapped function
         */
        template<typename F>
        class ScopeGuard {
            ScopeGuard(const ScopeGuard&) = delete;
            ScopeGuard& operator=(const ScopeGuard&) = delete;
            private:
                F f;
                bool canceled = false;
            public:
                ALWAYS_INLINE ScopeGuard(F f) : f(std::move(f)) { }
                ALWAYS_INLINE ~ScopeGuard() { if (!canceled) { f(); } }
                void dismiss() { canceled = true; }
        };
        
        /**
         * @brief libnx hid:sys shim that gives or takes away frocus to or from the process with the given aruid
         *
         * @param enable Give focus or take focus
         * @param aruid Aruid of the process to focus/unfocus
         * @return Result Result
         */
        static Result hidsysEnableAppletToGetInput(bool enable, u64 aruid) {
            const struct {
                u8 permitInput;
                u64 appletResourceUserId;
            } in = { enable != 0, aruid };
            
            return serviceDispatchIn(hidsysGetServiceSession(), 503, in);
        }
        
        static Result viAddToLayerStack(ViLayer *layer, ViLayerStack stack) {
            const struct {
                u32 stack;
                u64 layerId;
            } in = { stack, layer->layer_id };
            
            return serviceDispatchIn(viGetSession_IManagerDisplayService(), 6000, in);
        }
        
        /**
         * @brief Toggles focus between the Tesla overlay and the rest of the system
         *
         * @param enabled Focus Tesla?
         */
        static void requestForeground(bool enabled) {
            u64 applicationAruid = 0, appletAruid = 0;
            
            for (u64 programId = 0x0100000000001000UL; programId < 0x0100000000001020UL; programId++) {
                pmdmntGetProcessId(&appletAruid, programId);
                
                if (appletAruid != 0)
                    hidsysEnableAppletToGetInput(!enabled, appletAruid);
            }
            
            pmdmntGetApplicationProcessId(&applicationAruid);
            hidsysEnableAppletToGetInput(!enabled, applicationAruid);
            
            hidsysEnableAppletToGetInput(true, 0);
        }
        
        /**
         * @brief Splits a string at the given delimeters
         *
         * @param str String to split
         * @param delim Delimeter
         * @return Vector containing the split tokens
         */
        static std::vector<std::string> split(const std::string& str, char delim = ' ') {
            std::vector<std::string> out;
            
            size_t current, previous = 0;
            current = str.find(delim);
            while (current != std::string::npos) {
                out.push_back(str.substr(previous, current - previous));
                previous = current + 1;
                current = str.find(delim, previous);
            }
            out.push_back(str.substr(previous, current - previous));
            
            return out;
        }
        
        namespace ini {
            
            /**
             * @brief Ini file type
             */
            using IniData = std::map<std::string, std::map<std::string, std::string>>;
            
            /**
             * @brief Tesla config file
             */
            //static const char* TESLA_CONFIG_FILE = "/config/tesla/config.ini"; // CUSTOM MODIFICATION
            //static const char* ULTRAHAND_CONFIG_FILE = "/config/ultrahand/config.ini"; // CUSTOM MODIFICATION
            
            /**
             * @brief Parses an INI string
             *
             * @param str String to parse
             * @return Parsed data
             */
            //static IniData parseIni(const std::string &str) {
            //    IniData iniData;
            //   
            //    auto lines = split(str, '\n');
            //   
            //    std::string lastHeader = "";
            //    for (auto& line : lines) {
            //        if (line.empty())
            //            continue;
            //   
            //        if (line[0] == '[' && line[line.size() - 1] == ']') {
            //            lastHeader = line.substr(1, line.size() - 2);
            //            iniData.emplace(lastHeader, std::map<std::string, std::string>{});
            //        }
            //        else {
            //            auto keyValuePair = split(line, '=');
            //            if (keyValuePair.size() == 2) {
            //                std::string key = trim(keyValuePair[0]);
            //                std::string value = trim(keyValuePair[1]);
            //   
            //                // Remove leading spaces before the equal sign, trailing spaces at the end of the line
            //                key.erase(key.begin(), std::find_if(key.begin(), key.end(), [](unsigned char ch) {
            //                    return !std::isspace(ch);
            //                }));
            //                key.erase(std::find_if(key.rbegin(), key.rend(), [](unsigned char ch) {
            //                    return !std::isspace(ch);
            //                }).base(), key.end());
            //   
            //                // No need to remove spaces within the value, so just store it as is
            //                iniData[lastHeader].emplace(key, value);
            //            }
            //        }
            //    }
            //   
            //    return iniData;
            //} // CUSTOM MODIFICATION END
            
            
            /**
             * @brief Unparses ini data into a string
             *
             * @param iniData Ini data
             * @return Ini string
             */
            static std::string unparseIni(IniData const &iniData) {
                std::string string;
                bool addSectionGap = false;
                for (auto &section : iniData) {
                    if (addSectionGap)
                        string += "\n";
                    string += "["s + section.first + "]\n"s;
                    for (auto &keyValue : section.second) {
                        string += keyValue.first + "="s + keyValue.second + "\n"s;
                    }
                }
                return string;
            }
            
            /**
             * @brief Read Tesla settings file
             *
             * @return Settings data
             */
            static IniData readOverlaySettings(auto& CONFIG_FILE) {
                /* Open Sd card filesystem. */
                FsFileSystem fsSdmc;
                if (R_FAILED(fsOpenSdCardFileSystem(&fsSdmc)))
                    return {};
                hlp::ScopeGuard fsGuard([&] { fsFsClose(&fsSdmc); });
                
                /* Open config file. */
                FsFile fileConfig;
                if (R_FAILED(fsFsOpenFile(&fsSdmc, CONFIG_FILE, FsOpenMode_Read, &fileConfig)))
                    return {};
                hlp::ScopeGuard fileGuard([&] { fsFileClose(&fileConfig); });
                
                /* Get config file size. */
                s64 configFileSize;
                if (R_FAILED(fsFileGetSize(&fileConfig, &configFileSize)))
                    return {};
                
                /* Read and parse config file. */
                std::string configFileData(configFileSize, '\0');
                u64 readSize;
                Result rc = fsFileRead(&fileConfig, 0, configFileData.data(), configFileSize, FsReadOption_None, &readSize);
                if (R_FAILED(rc) || readSize != static_cast<u64>(configFileSize))
                    return {};
                
                return parseIni(configFileData);
            }
            
            /**
             * @brief Replace Tesla settings file with new data
             *
             * @param iniData new data
             */
            static void writeOverlaySettings(IniData const &iniData, auto& CONFIG_FILE) {
                /* Open Sd card filesystem. */
                FsFileSystem fsSdmc;
                if (R_FAILED(fsOpenSdCardFileSystem(&fsSdmc)))
                    return;
                hlp::ScopeGuard fsGuard([&] { fsFsClose(&fsSdmc); });
                
                /* Open config file. */
                FsFile fileConfig;
                if (R_FAILED(fsFsOpenFile(&fsSdmc, CONFIG_FILE, FsOpenMode_Write, &fileConfig)))
                    return;
                hlp::ScopeGuard fileGuard([&] { fsFileClose(&fileConfig); });
                
                std::string iniString = unparseIni(iniData);
                
                fsFileWrite(&fileConfig, 0, iniString.c_str(), iniString.length(), FsWriteOption_Flush);
            }
            
            /**
             * @brief Merge and save changes into Tesla settings file
             *
             * @param changes setting values to add or update
             */
            static void updateOverlaySettings(IniData const &changes, auto& CONFIG_FILE) {
                hlp::ini::IniData iniData = hlp::ini::readOverlaySettings(CONFIG_FILE);
                for (auto &section : changes) {
                    for (auto &keyValue : section.second) {
                        iniData[section.first][keyValue.first] = keyValue.second;
                    }
                }
                writeOverlaySettings(iniData, CONFIG_FILE);
            }
            
        }
        
        /**
         * @brief Decodes a key string into it's key code
         *
         * @param value Key string
         * @return Key code
         */
        static u64 stringToKeyCode(const std::string &value) {
            for (auto &keyInfo : impl::KEYS_INFO) {
                if (strcasecmp(value.c_str(), keyInfo.name) == 0)
                    return keyInfo.key;
            }
            return 0;
        }
        
        /**
         * @brief Decodes a combo string into key codes
         *
         * @param value Combo string
         * @return Key codes
         */
        static u64 comboStringToKeys(const std::string &value) {
            u64 keyCombo = 0x00;
            for (std::string key : hlp::split(removeWhiteSpaces(value), '+')) { // CUSTOM MODIFICATION (bug fix)
                keyCombo |= hlp::stringToKeyCode(key);
            }
            return keyCombo;
        }
        
        /**
         * @brief Encodes key codes into a combo string
         *
         * @param keys Key codes
         * @return Combo string
         */
        static std::string keysToComboString(u64 keys) {
            std::string str;
            for (auto &keyInfo : impl::KEYS_INFO) {
                if (keys & keyInfo.key) {
                    if (!str.empty())
                        str.append("+");
                    str.append(keyInfo.name);
                }
            }
            return str;
        }
        
    }
    
    // Renderer
    
    namespace gfx {
        
        extern "C" u64 __nx_vi_layer_id;
        
        struct ScissoringConfig {
            s32 x, y, w, h;
        };
        
        /**
         * @brief Manages the Tesla layer and draws raw data to the screen
         */
        class Renderer final {
        public:
            Renderer& operator=(Renderer&) = delete;
            
            friend class tsl::Overlay;
            
            /**
             * @brief Handles opacity of drawn colors for fadeout. Pass all colors through this function in order to apply opacity properly
             *
             * @param c Original color
             * @return Color with applied opacity
             */
            static Color a(const Color &c) {
                return (c.rgba & 0x0FFF) | (static_cast<u8>(c.a * Renderer::s_opacity) << 12);
            }
            
            /**
             * @brief Enables scissoring, discarding of any draw outside the given boundaries
             *
             * @param x x pos
             * @param y y pos
             * @param w Width
             * @param h Height
             */
            inline void enableScissoring(s32 x, s32 y, s32 w, s32 h) {
                this->m_scissoringStack.emplace(x, y, w, h);
            }
            
            /**
             * @brief Disables scissoring
             */
            inline void disableScissoring() {
                this->m_scissoringStack.pop();
            }
            
            
            // Drawing functions
            
            /**
             * @brief Draw a single pixel onto the screen
             *
             * @param x X pos
             * @param y Y pos
             * @param color Color
             */
            inline void setPixel(s32 x, s32 y, Color color) {
                if (x < 0 || y < 0 || x >= cfg::FramebufferWidth || y >= cfg::FramebufferHeight)
                    return;
                
                u32 offset = this->getPixelOffset(x, y);
                
                if (offset != UINT32_MAX)
                    static_cast<Color*>(this->getCurrentFramebuffer())[offset] = color;
            }
            
            /**
             * @brief Blends two colors
             *
             * @param src Source color
             * @param dst Destination color
             * @param alpha Opacity
             * @return Blended color
             */
            inline u8 blendColor(u8 src, u8 dst, u8 alpha) {
                u8 oneMinusAlpha = 0x0F - alpha;
                
                return (dst * alpha + src * oneMinusAlpha) / float(0xF);
            }
            
            /**
             * @brief Draws a single source blended pixel onto the screen
             *
             * @param x X pos
             * @param y Y pos
             * @param color Color
             */
            inline void setPixelBlendSrc(s32 x, s32 y, Color color) {
                if (x < 0 || y < 0 || x >= cfg::FramebufferWidth || y >= cfg::FramebufferHeight)
                    return;
                
                u32 offset = this->getPixelOffset(x, y);
                
                if (offset == UINT32_MAX)
                    return;
                
                Color src((static_cast<u16*>(this->getCurrentFramebuffer()))[offset]);
                Color dst(color);
                Color end(0);
                
                end.r = this->blendColor(src.r, dst.r, dst.a);
                end.g = this->blendColor(src.g, dst.g, dst.a);
                end.b = this->blendColor(src.b, dst.b, dst.a);
                end.a = src.a;
                
                this->setPixel(x, y, end);
            }
            
            /**
             * @brief Draws a single destination blended pixel onto the screen
             *
             * @param x X pos
             * @param y Y pos
             * @param color Color
             */
            inline void setPixelBlendDst(s32 x, s32 y, Color color) {
                if (x < 0 || y < 0 || x >= cfg::FramebufferWidth || y >= cfg::FramebufferHeight)
                    return;
                
                u32 offset = this->getPixelOffset(x, y);
                
                if (offset == UINT32_MAX)
                    return;
                
                Color src((static_cast<u16*>(this->getCurrentFramebuffer()))[offset]);
                Color dst(color);
                Color end(0);
                
                end.r = this->blendColor(src.r, dst.r, dst.a);
                end.g = this->blendColor(src.g, dst.g, dst.a);
                end.b = this->blendColor(src.b, dst.b, dst.a);
                end.a = std::min(dst.a + src.a, 0xF);
                
                this->setPixel(x, y, end);
            }
            
            /**
             * @brief Draws a rectangle of given sizes
             *
             * @param x X pos
             * @param y Y pos
             * @param w Width
             * @param h Height
             * @param color Color
             */
            inline void drawRect(float x, float y, float w, float h, Color color) {
                for (s32 x1 = x; x1 < (x + w); x1++)
                    for (s32 y1 = y; y1 < (y + h); y1++)
                        this->setPixelBlendDst(x1, y1, color);
            }
            
            void drawCircle(s32 centerX, s32 centerY, u16 radius, bool filled, Color color) {
                s32 x = radius;
                s32 y = 0;
                s32 radiusError = 0;
                s32 xChange = 1 - (radius << 1);
                s32 yChange = 0;
                
                s32 y0;
                s32 y1;
                s32 x0;
                
                while (x >= y) {
                    if(filled) {
                        for (s32 i = centerX - x; i <= centerX + x; i++) {
                            y0 = centerY + y;
                            y1 = centerY - y;
                            x0 = i;
                            
                            this->setPixelBlendDst(x0, y0, color);
                            this->setPixelBlendDst(x0, y1, color);
                        }
                        
                        for (s32 i = centerX - y; i <= centerX + y; i++) {
                            y0 = centerY + x;
                            y1 = centerY - x;
                            x0 = i;
                            
                            this->setPixelBlendDst(x0, y0, color);
                            this->setPixelBlendDst(x0, y1, color);
                        }
                        
                        y++;
                        radiusError += yChange;
                        yChange += 2;
                        if (((radiusError << 1) + xChange) > 0) {
                            x--;
                            radiusError += xChange;
                            xChange += 2;
                        }
                    } else {
                        this->setPixelBlendDst(centerX + x, centerY + y, color);
                        this->setPixelBlendDst(centerX + y, centerY + x, color);
                        this->setPixelBlendDst(centerX - y, centerY + x, color);
                        this->setPixelBlendDst(centerX - x, centerY + y, color);
                        this->setPixelBlendDst(centerX - x, centerY - y, color);
                        this->setPixelBlendDst(centerX - y, centerY - x, color);
                        this->setPixelBlendDst(centerX + y, centerY - x, color);
                        this->setPixelBlendDst(centerX + x, centerY - y, color);
                        
                        if(radiusError <= 0) {
                            y++;
                            radiusError += 2 * y + 1;
                        } else {
                            x--;
                            radiusError -= 2 * x + 1;
                        }
                    }
                }
            }
            
            /**
             * @brief Draws a RGBA8888 bitmap from memory
             *
             * @param x X start position
             * @param y Y start position
             * @param w Bitmap width
             * @param h Bitmap height
             * @param bmp Pointer to bitmap data
             */
            void drawBitmap(s32 x, s32 y, s32 w, s32 h, const u8 *bmp) {
                for (s32 y1 = 0; y1 < h; y1++) {
                    for (s32 x1 = 0; x1 < w; x1++) {
                        setPixelBlendSrc(x + x1, y + y1, a({ static_cast<u8>(bmp[0] >> 4), static_cast<u8>(bmp[1] >> 4), static_cast<u8>(bmp[2] >> 4), static_cast<u8>(bmp[3] >> 4) }));
                        bmp += 4;
                    }
                }
            }
            
            /**
             * @brief Fills the entire layer with a given color
             *
             * @param color Color
             */
            inline void fillScreen(Color color) {
                std::fill_n(static_cast<Color*>(this->getCurrentFramebuffer()), this->getFramebufferSize() / sizeof(Color), color);
            }
            
            /**
             * @brief Clears the layer (With transparency)
             *
             */
            inline void clearScreen() {
                this->fillScreen({ 0x00, 0x00, 0x00, 0x00 });
            }
            
            struct Glyph {
                stbtt_fontinfo *currFont;
                float currFontSize;
                int bounds[4];
                int xAdvance;
                u8 *glyphBmp;
                int width, height;
            };
            
            /**
             * @brief Draws a string
             *
             * @param string String to draw
             * @param monospace Draw string in monospace font
             * @param x X pos
             * @param y Y pos
             * @param fontSize Height of the text drawn in pixels
             * @param color Text color. Use transparent color to skip drawing and only get the string's dimensions
             * @return Dimensions of drawn string
             */
            std::pair<u32, u32> drawString(const char* string, bool monospace, float x, float y, float fontSize, Color color, ssize_t maxWidth = 0) {
                float maxX = x;
                float currX = x;
                float currY = y;
                
                
                static std::unordered_map<u64, Glyph> s_glyphCache;
                
                do {
                    if (maxWidth > 0 && maxWidth < (currX - x))
                        break;
                    
                    u32 currCharacter;
                    ssize_t codepointWidth = decode_utf8(&currCharacter, reinterpret_cast<const u8*>(string));
                    
                    if (codepointWidth <= 0)
                        break;
                    
                    string += codepointWidth;
                    
                    if (currCharacter == '\n') {
                        maxX = std::max(currX, maxX);
                        
                        currX = x;
                        currY += fontSize;
                        
                        continue;
                    }
                    
                    u64 key = (static_cast<u64>(currCharacter) << 32) | static_cast<u64>(monospace) << 31 | static_cast<u64>(std::bit_cast<u32>(fontSize));
                    
                    Glyph *glyph = nullptr;
                    
                    auto it = s_glyphCache.find(key);
                    if (it == s_glyphCache.end()) {
                        /* Cache glyph */
                        glyph = &s_glyphCache.emplace(key, Glyph()).first->second;
                        
                        if (stbtt_FindGlyphIndex(&this->m_extFont, currCharacter))
                            glyph->currFont = &this->m_extFont;
                        else if(this->m_hasLocalFont && stbtt_FindGlyphIndex(&this->m_stdFont, currCharacter)==0)
                            glyph->currFont = &this->m_localFont;
                        else
                            glyph->currFont = &this->m_stdFont;
                        
                        glyph->currFontSize = stbtt_ScaleForPixelHeight(glyph->currFont, fontSize);
                        
                        stbtt_GetCodepointBitmapBoxSubpixel(glyph->currFont, currCharacter, glyph->currFontSize, glyph->currFontSize,
                                                            0, 0, &glyph->bounds[0], &glyph->bounds[1], &glyph->bounds[2], &glyph->bounds[3]);
                                                            
                        int yAdvance = 0;
                        stbtt_GetCodepointHMetrics(glyph->currFont, monospace ? 'W' : currCharacter, &glyph->xAdvance, &yAdvance);
                        
                        glyph->glyphBmp = stbtt_GetCodepointBitmap(glyph->currFont, glyph->currFontSize, glyph->currFontSize, currCharacter, &glyph->width, &glyph->height, nullptr, nullptr);
                    } else {
                        /* Use cached glyph */
                        glyph = &it->second;
                    }
                    
                    if (glyph->glyphBmp != nullptr && !std::iswspace(currCharacter) && fontSize > 0 && color.a != 0x0) {
                        Color tmpColor = {0xF,0xF,0xF,0xF};
                        uint8_t bmpColor;
                        
                        auto x = currX + glyph->bounds[0];
                        auto y = currY + glyph->bounds[1];
                        
                        for (s32 bmpY = 0; bmpY < glyph->height; bmpY++) {
                            for (s32 bmpX = 0; bmpX < glyph->width; bmpX++) {
                                bmpColor = glyph->glyphBmp[glyph->width * bmpY + bmpX] >> 4;
                                if (bmpColor == 0xF) {
                                    this->setPixel(x + bmpX, y + bmpY, color);
                                } else if (bmpColor != 0x0) {
                                    tmpColor = color;
                                    tmpColor.a = bmpColor * (float(tmpColor.a) / 0xF);
                                    this->setPixelBlendDst(x + bmpX, y + bmpY, tmpColor);
                                }
                            }
                        }
                        
                    }
                    
                    currX += static_cast<s32>(glyph->xAdvance * glyph->currFontSize);
                    
                } while (*string != '\0');
                
                maxX = std::max(currX, maxX);
                
                return { maxX - x, currY - y };
            }
            
            /**
             * @brief Limit a strings length and end it with "…"
             *
             * @param string String to truncate
             * @param maxLength Maximum length of string
             */
            std::string limitStringLength(std::string string, bool monospace, float fontSize, s32 maxLength) {
                if (string.size() < 2)
                    return string;
                
                s32 currX = 0;
                ssize_t strPos = 0;
                ssize_t codepointWidth;
                
                do {
                    u32 currCharacter;
                    codepointWidth = decode_utf8(&currCharacter, reinterpret_cast<const u8*>(&string[strPos]));
                    
                    if (codepointWidth <= 0)
                        break;
                    
                    strPos += codepointWidth;
                    
                    stbtt_fontinfo *currFont = nullptr;
                    
                    if (stbtt_FindGlyphIndex(&this->m_extFont, currCharacter))
                        currFont = &this->m_extFont;
                    else if(this->m_hasLocalFont && stbtt_FindGlyphIndex(&this->m_stdFont, currCharacter)==0)
                        currFont = &this->m_localFont;
                    else
                        currFont = &this->m_stdFont;
                    
                    float currFontSize = stbtt_ScaleForPixelHeight(currFont, fontSize);
                    
                    int xAdvance = 0, yAdvance = 0;
                    stbtt_GetCodepointHMetrics(currFont, monospace ? 'W' : currCharacter, &xAdvance, &yAdvance);
                    
                    currX += static_cast<s32>(xAdvance * currFontSize);
                    
                } while (string[strPos] != '\0' && string[strPos] != '\n' && currX < maxLength);
                
                string = string.substr(0, strPos - codepointWidth) + "…";
                string.shrink_to_fit();
                
                return string;
            }
            
        private:
            Renderer() {}
            
            /**
             * @brief Gets the renderer instance
             *
             * @return Renderer
             */
            static Renderer& get() {
                static Renderer renderer;
                
                return renderer;
            }
            
            /**
             * @brief Sets the opacity of the layer
             *
             * @param opacity Opacity
             */
            static void setOpacity(float opacity) {
                opacity = std::clamp(opacity, 0.0F, 1.0F);
                
                Renderer::s_opacity = opacity;
            }
            
            bool m_initialized = false;
            ViDisplay m_display;
            ViLayer m_layer;
            Event m_vsyncEvent;
            
            NWindow m_window;
            Framebuffer m_framebuffer;
            void *m_currentFramebuffer = nullptr;
            
            std::stack<ScissoringConfig> m_scissoringStack;
            
            stbtt_fontinfo m_stdFont, m_localFont, m_extFont;
            bool m_hasLocalFont = false;
            
            static inline float s_opacity = 1.0F;
            
            u32 tmpPos;
            
            /**
             * @brief Get the current framebuffer address
             *
             * @return Framebuffer address
             */
            inline void* getCurrentFramebuffer() {
                return this->m_currentFramebuffer;
            }
            
            /**
             * @brief Get the next framebuffer address
             *
             * @return Next framebuffer address
             */
            inline void* getNextFramebuffer() {
                return static_cast<u8*>(this->m_framebuffer.buf) + this->getNextFramebufferSlot() * this->getFramebufferSize();
            }
            
            /**
             * @brief Get the framebuffer size
             *
             * @return Framebuffer size
             */
            inline size_t getFramebufferSize() {
                return this->m_framebuffer.fb_size;
            }
            
            /**
             * @brief Get the number of framebuffers in use
             *
             * @return Number of framebuffers
             */
            inline size_t getFramebufferCount() {
                return this->m_framebuffer.num_fbs;
            }
            
            /**
             * @brief Get the currently used framebuffer's slot
             *
             * @return Slot
             */
            inline u8 getCurrentFramebufferSlot() {
                return this->m_window.cur_slot;
            }
            
            /**
             * @brief Get the next framebuffer's slot
             *
             * @return Next slot
             */
            inline u8 getNextFramebufferSlot() {
                return (this->getCurrentFramebufferSlot() + 1) % this->getFramebufferCount();
            }
            
            /**
             * @brief Waits for the vsync event
             *
             */
            inline void waitForVSync() {
                eventWait(&this->m_vsyncEvent, UINT64_MAX);
            }
            
            /**
             * @brief Decodes a x and y coordinate into a offset into the swizzled framebuffer
             *
             * @param x X pos
             * @param y Y Pos
             * @return Offset
             */
            u32 getPixelOffset(s32 x, s32 y) {
                if (!this->m_scissoringStack.empty()) {
                    auto& currScissorConfig = this->m_scissoringStack.top();
                    if (x < currScissorConfig.x ||
                        y < currScissorConfig.y ||
                        x > currScissorConfig.x + currScissorConfig.w ||
                        y > currScissorConfig.y + currScissorConfig.h)
                            return UINT32_MAX;
                }
                
                tmpPos = ((y & 127) / 16) + (x / 32 * 8) + ((y / 16 / 8) * (((cfg::FramebufferWidth / 2) / 16 * 8)));
                tmpPos *= 16 * 16 * 4;
                
                tmpPos += ((y % 16) / 8) * 512 + ((x % 32) / 16) * 256 + ((y % 8) / 2) * 64 + ((x % 16) / 8) * 32 + (y % 2) * 16 + (x % 8) * 2;
                
                return tmpPos / 2;
            }
            
            /**
             * @brief Initializes the renderer and layers
             *
             */
            void init() {
                
                cfg::LayerPosX = 0;
                cfg::LayerPosY = 0;
                cfg::FramebufferWidth  = 448;
                cfg::FramebufferHeight = 720;
                cfg::LayerWidth  = cfg::ScreenHeight * (float(cfg::FramebufferWidth) / float(cfg::FramebufferHeight));
                cfg::LayerHeight = cfg::ScreenHeight;
                
                if (this->m_initialized)
                    return;
                
                tsl::hlp::doWithSmSession([this]{
                    ASSERT_FATAL(viInitialize(ViServiceType_Manager));
                    ASSERT_FATAL(viOpenDefaultDisplay(&this->m_display));
                    ASSERT_FATAL(viGetDisplayVsyncEvent(&this->m_display, &this->m_vsyncEvent));
                    ASSERT_FATAL(viCreateManagedLayer(&this->m_display, static_cast<ViLayerFlags>(0), 0, &__nx_vi_layer_id));
                    ASSERT_FATAL(viCreateLayer(&this->m_display, &this->m_layer));
                    ASSERT_FATAL(viSetLayerScalingMode(&this->m_layer, ViScalingMode_FitToLayer));
                    
                    if (s32 layerZ = 0; R_SUCCEEDED(viGetZOrderCountMax(&this->m_display, &layerZ)) && layerZ > 0)
                        ASSERT_FATAL(viSetLayerZ(&this->m_layer, layerZ));
                    
                    ASSERT_FATAL(tsl::hlp::viAddToLayerStack(&this->m_layer, ViLayerStack_Default));
                    ASSERT_FATAL(tsl::hlp::viAddToLayerStack(&this->m_layer, ViLayerStack_Screenshot));
                    ASSERT_FATAL(tsl::hlp::viAddToLayerStack(&this->m_layer, ViLayerStack_Recording));
                    ASSERT_FATAL(tsl::hlp::viAddToLayerStack(&this->m_layer, ViLayerStack_Arbitrary));
                    ASSERT_FATAL(tsl::hlp::viAddToLayerStack(&this->m_layer, ViLayerStack_LastFrame));
                    ASSERT_FATAL(tsl::hlp::viAddToLayerStack(&this->m_layer, ViLayerStack_Null));
                    ASSERT_FATAL(tsl::hlp::viAddToLayerStack(&this->m_layer, ViLayerStack_ApplicationForDebug));
                    ASSERT_FATAL(tsl::hlp::viAddToLayerStack(&this->m_layer, ViLayerStack_Lcd));
                    //ASSERT_FATAL(tsl::hlp::viAddToLayerStack(&this->m_layer, 8));
                    
                    ASSERT_FATAL(viSetLayerSize(&this->m_layer, cfg::LayerWidth, cfg::LayerHeight));
                    ASSERT_FATAL(viSetLayerPosition(&this->m_layer, cfg::LayerPosX, cfg::LayerPosY));
                    ASSERT_FATAL(nwindowCreateFromLayer(&this->m_window, &this->m_layer));
                    ASSERT_FATAL(framebufferCreate(&this->m_framebuffer, &this->m_window, cfg::FramebufferWidth, cfg::FramebufferHeight, PIXEL_FORMAT_RGBA_4444, 2));
                    ASSERT_FATAL(setInitialize());
                    ASSERT_FATAL(this->initFonts());
                    setExit();
                });
                
                this->m_initialized = true;
            }
            
            /**
             * @brief Exits the renderer and layer
             *
             */
            void exit() {
                if (!this->m_initialized)
                    return;
                
                framebufferClose(&this->m_framebuffer);
                nwindowClose(&this->m_window);
                viDestroyManagedLayer(&this->m_layer);
                viCloseDisplay(&this->m_display);
                eventClose(&this->m_vsyncEvent);
                viExit();
            }
            
            /**
             * @brief Initializes Nintendo's shared fonts. Default and Extended
             *
             * @return Result
             */
            Result initFonts() {
                static PlFontData stdFontData, localFontData, extFontData;
                
                // Nintendo's default font
                TSL_R_TRY(plGetSharedFontByType(&stdFontData, PlSharedFontType_Standard));
                
                u8 *fontBuffer = reinterpret_cast<u8*>(stdFontData.address);
                stbtt_InitFont(&this->m_stdFont, fontBuffer, stbtt_GetFontOffsetForIndex(fontBuffer, 0));
                
                u64 languageCode;
                if (R_SUCCEEDED(setGetSystemLanguage(&languageCode))) {
                    // Check if need localization font
                    SetLanguage setLanguage;
                    TSL_R_TRY(setMakeLanguage(languageCode, &setLanguage));
                    this->m_hasLocalFont = true;
                    switch (setLanguage) {
                    case SetLanguage_ZHCN:
                    case SetLanguage_ZHHANS:
                        TSL_R_TRY(plGetSharedFontByType(&localFontData, PlSharedFontType_ChineseSimplified));
                        break;
                    case SetLanguage_KO:
                        TSL_R_TRY(plGetSharedFontByType(&localFontData, PlSharedFontType_KO));
                        break;
                    case SetLanguage_ZHTW:
                    case SetLanguage_ZHHANT:
                        TSL_R_TRY(plGetSharedFontByType(&localFontData, PlSharedFontType_ChineseTraditional));
                        break;
                    default:
                        this->m_hasLocalFont = false;
                        break;
                    }
                    
                    if (this->m_hasLocalFont) {
                        fontBuffer = reinterpret_cast<u8*>(localFontData.address);
                        stbtt_InitFont(&this->m_localFont, fontBuffer, stbtt_GetFontOffsetForIndex(fontBuffer, 0));
                    }
                }
                
                // Nintendo's extended font containing a bunch of icons
                TSL_R_TRY(plGetSharedFontByType(&extFontData, PlSharedFontType_NintendoExt));
                
                fontBuffer = reinterpret_cast<u8*>(extFontData.address);
                stbtt_InitFont(&this->m_extFont, fontBuffer, stbtt_GetFontOffsetForIndex(fontBuffer, 0));
                
                return 0;
            }
            
            /**
             * @brief Start a new frame
             * @warning Don't call this more than once before calling \ref endFrame
             */
            inline void startFrame() {
                this->m_currentFramebuffer = framebufferBegin(&this->m_framebuffer, nullptr);
            }
            
            /**
             * @brief End the current frame
             * @warning Don't call this before calling \ref startFrame once
             */
            inline void endFrame() {
                this->waitForVSync();
                framebufferEnd(&this->m_framebuffer);
                
                this->m_currentFramebuffer = nullptr;
            }
        };
        
    }
    
    // Elements
    
    namespace elm {
        
        enum class TouchEvent {
            Touch,
            Hold,
            Scroll,
            Release,
            None
        };
        
        /**
         * @brief The top level Element of the libtesla UI library
         * @note When creating your own elements, extend from this or one of it's sub classes
         */
        class Element {
        public:
            
            Element() {}
            virtual ~Element() { }
            
            std::string disableSelectionBGStr = parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "disable_selection_bg");
            bool disableSelectionBG = (!disableSelectionBGStr.empty() && disableSelectionBGStr != "false");
            
            bool invertBGClickColor = (parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "invert_bg_click_color") == "true");
            Color selectionBGColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "selection_bg_color"), "#000000");
            
            Color highlightColor1 = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "highlight_color_1"), "#2288CC");
            Color highlightColor2 = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "highlight_color_2"), "#88FFFF");
            Color highlightColor = {0xf,0xf,0xf,0xf};
            
            Color clickColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "click_color"), "#F7253E");
            
            std::chrono::duration<long int, std::ratio<1, 1000000000>> t;
            //double timeCounter;
            u8 saturation;
            Color animColor = tsl::style::color::ColorClickAnimation;
            float progress;
            Color clickColor1 = {0xf,0xf,0xf,0xf};
            Color clickColor2 = {0xf,0xf,0xf,0xf};
            
            s32 x, y;
            s32 amplitude;
            
            
            /**
             * @brief Handles focus requesting
             * @note This function should return the element to focus.
             *       When this element should be focused, return `this`.
             *       When one of it's child should be focused, return `this->child->requestFocus(oldFocus, direction)`
             *       When this element is not focusable, return `nullptr`
             *
             * @param oldFocus Previously focused element
             * @param direction Direction in which focus moved. \ref FocusDirection::None is passed for the initial load
             * @return Element to focus
             */
            virtual Element* requestFocus(Element *oldFocus, FocusDirection direction) {
                return nullptr;
            }
            
            /**
             * @brief Function called when a joycon button got pressed
             *
             * @param keys Keys pressed in the last frame
             * @return true when button press has been consumed
             * @return false when button press should be passed on to the parent
             */
            virtual bool onClick(u64 keys) {
                return m_clickListener(keys);
            }
            
            /**
             * @brief Called once per frame with the latest HID inputs
             *
             * @param keysDown Buttons pressed in the last frame
             * @param keysHeld Buttons held down longer than one frame
             * @param touchInput Last touch position
             * @param leftJoyStick Left joystick position
             * @param rightJoyStick Right joystick position
             * @return Weather or not the input has been consumed
             */
            virtual bool handleInput(u64 keysDown, u64 keysHeld, const HidTouchState &touchPos, HidAnalogStickState joyStickPosLeft, HidAnalogStickState joyStickPosRight) {
                return false;
            }
            
            /**
             * @brief Function called when the element got touched
             * @todo Not yet implemented
             *
             * @param x X pos
             * @param y Y pos
             * @return true when touch input has been consumed
             * @return false when touch input should be passed on to the parent
             */
            virtual bool onTouch(TouchEvent event, s32 currX, s32 currY, s32 prevX, s32 prevY, s32 initialX, s32 initialY) {
                return false;
            }
            
            /**
             * @brief Called once per frame to draw the element
             * @warning Do not call this yourself. Use \ref Element::frame(gfx::Renderer *renderer)
             *
             * @param renderer Renderer
             */
            virtual void draw(gfx::Renderer *renderer) = 0;
            
            /**
             * @brief Called when the underlying Gui gets created and after calling \ref Gui::invalidate() to calculate positions and boundaries of the element
             * @warning Do not call this yourself. Use \ref Element::invalidate()
             *
             * @param parentX Parent X pos
             * @param parentY Parent Y pos
             * @param parentWidth Parent Width
             * @param parentHeight Parent Height
             */
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) = 0;
            
            /**
             * @brief Draws highlighting and the element itself
             * @note When drawing children of a element in \ref Element::draw(gfx::Renderer *renderer), use `this->child->frame(renderer)` instead of calling draw directly
             *
             * @param renderer
             */
            void frame(gfx::Renderer *renderer) {
                
                if (this->m_focused) {
                    renderer->enableScissoring(0, 97, tsl::cfg::FramebufferWidth, tsl::cfg::FramebufferHeight-73-97);
                    this->drawFocusBackground(renderer);
                    this->drawHighlight(renderer);
                    renderer->disableScissoring();
                }
                
                this->draw(renderer);
            }
            
            /**
             * @brief Forces a layout recreation of a element
             *
             */
            void invalidate() {
                const auto& parent = this->getParent();
                
                if (parent == nullptr)
                    this->layout(0, 0, cfg::FramebufferWidth, cfg::FramebufferHeight);
                else
                    this->layout(ELEMENT_BOUNDS(parent));
            }
            
            /**
             * @brief Shake the highlight in the given direction to signal that the focus cannot move there
             *
             * @param direction Direction to shake highlight in
             */
            void shakeHighlight(FocusDirection direction) {
                this->m_highlightShaking = true;
                this->m_highlightShakingDirection = direction;
                this->m_highlightShakingStartTime = std::chrono::system_clock::now();
            }
            
            /**
             * @brief Triggers the blue click animation to signal a element has been clicked on
             *
             */
            void triggerClickAnimation() {
                this->m_clickAnimationProgress = tsl::style::ListItemHighlightLength;
            }
            
            /**
             * @brief Resets the click animation progress, canceling the animation
             */
            void resetClickAnimation() {
                this->m_clickAnimationProgress = 0;
            }
            
            /**
             * @brief Draws the blue highlight animation when clicking on a button
             * @note Override this if you have a element that e.g requires a non-rectangular animation or a different color
             *
             * @param renderer Renderer
             */
            virtual void drawClickAnimation(gfx::Renderer *renderer) {
                
                if (!disableSelectionBG) {
                    saturation = tsl::style::ListItemHighlightSaturation * (float(this->m_clickAnimationProgress) / float(tsl::style::ListItemHighlightLength));
                    if (invertBGClickColor) {
                        animColor.r = 15-saturation;
                        animColor.g = 15-saturation;
                        animColor.b = 15;
                    } else {
                        animColor.r = 0;
                        animColor.g = saturation;
                        animColor.b = saturation;
                    }
                    renderer->drawRect(ELEMENT_BOUNDS(this), (animColor));
                } else {
                    clickColor1 = highlightColor1;
                    clickColor2 = clickColor;
                    
                    //half progress = half((std::sin(2.0 * M_PI * fmod(std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count(), 1.0)) + 1.0) / 2.0);
                    progress = (std::sin(2.0 * M_PI * fmod(std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count(), 1.0)) + 1.0) / 2.0;
                    
                    if (progress >= 0.5) {
                        clickColor1 = clickColor;
                        clickColor2 = highlightColor2;
                    }
                    
                    highlightColor = {
                        static_cast<u8>((clickColor1.r - clickColor2.r) * progress + clickColor2.r),
                        static_cast<u8>((clickColor1.g - clickColor2.g) * progress + clickColor2.g),
                        static_cast<u8>((clickColor1.b - clickColor2.b) * progress + clickColor2.b),
                        0xF
                    };
                    
                    x = 0;
                    y = 0;
                    if (this->m_highlightShaking) {
                        t = (std::chrono::system_clock::now() - this->m_highlightShakingStartTime);
                        if (t >= 100ms)
                            this->m_highlightShaking = false;
                        else {
                            amplitude = std::rand() % 5 + 5;
                            
                            switch (this->m_highlightShakingDirection) {
                                case FocusDirection::Up:
                                    y -= shakeAnimation(t, amplitude);
                                    break;
                                case FocusDirection::Down:
                                    y += shakeAnimation(t, amplitude);
                                    break;
                                case FocusDirection::Left:
                                    x -= shakeAnimation(t, amplitude);
                                    break;
                                case FocusDirection::Right:
                                    x += shakeAnimation(t, amplitude);
                                    break;
                                default:
                                    break;
                            }
                            
                            x = std::clamp(x, -amplitude, amplitude);
                            y = std::clamp(y, -amplitude, amplitude);
                        }
                    }
                    
                    
                    //renderer->drawRect(this->getX() + x - 4, this->getY() + y - 4, this->getWidth() + 8, 4, highlightColor);
                    //renderer->drawRect(this->getX() + x - 4, this->getY() + y + this->getHeight(), this->getWidth() + 8, 4, highlightColor);
                    //renderer->drawRect(this->getX() + x - 4, this->getY() + y, 4, this->getHeight(), highlightColor);
                    //renderer->drawRect(this->getX() + x + this->getWidth(), this->getY() + y, 4, this->getHeight(), highlightColor);
                    
                    
                    renderer->drawRect(this->getX() + x + 5 -1, this->getY() + y - 4, this->getWidth() - 5 +2 +4, 5, highlightColor);
                    renderer->drawRect(this->getX() + x + 5 -1, this->getY() + y + this->getHeight(), this->getWidth() - 5 +2 +4, 5, highlightColor);
                    renderer->drawRect(this->getX() + x, this->getY() + y + 2 - 2, 5, this->getHeight()-3 +4, highlightColor);
                    renderer->drawRect(this->getX() + x + this->getWidth()+4, this->getY() + y + 2 -2, 5, this->getHeight()-3 +4, highlightColor);
                    
                    renderer->drawCircle(this->getX() + x + 2, this->getY() + y + this->getHeight() + 2, 2.5, true, highlightColor);
                    renderer->drawCircle(this->getX() + x + 2, this->getY() + y - 2, 2.5, true, highlightColor);
                    renderer->drawCircle(this->getX() + x + this->getWidth() + 2+4, this->getY() + y + this->getHeight() + 2, 2.5, true, highlightColor);
                    renderer->drawCircle(this->getX() + x + this->getWidth() + 2+4, this->getY() + y - 2, 2.5, true, highlightColor);
                    
                }
            }
            
            /**
             * @brief Draws the back background when a element is highlighted
             * @note Override this if you have a element that e.g requires a non-rectangular focus
             *
             * @param renderer Renderer
             */
            virtual void drawFocusBackground(gfx::Renderer *renderer) {
                if (!disableSelectionBG)
                    renderer->drawRect(ELEMENT_BOUNDS(this), selectionBGColor); // CUSTOM MODIFICATION 
                
                if (this->m_clickAnimationProgress > 0) {
                    this->drawClickAnimation(renderer);
                    this->m_clickAnimationProgress--;
                }
            }
            
            /**
             * @brief Draws the blue boarder when a element is highlighted
             * @note Override this if you have a element that e.g requires a non-rectangular focus
             *
             * @param renderer Renderer
             */
            virtual void drawHighlight(gfx::Renderer *renderer) { // CUSTOM MODIFICATION start
                
                //Color highlightColor1 = {0x2, 0x8, 0xC, 0xF};
                //Color highlightColor2 = {0x8, 0xF, 0xF, 0xF};
                //highlightColor1Str = "#2288CC";
                //highlightColor2Str = "#88FFFF";
                
                
                // Get the current time
                
                // Calculate the progress for one full sine wave per second
                //const double cycleDuration = 1.0;  // 1 second for one full sine wave
                //double timeCounter = 
                //half progress = half((std::sin(2.0 * M_PI * fmod(std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count(), 1.0)) + 1.0) / 2.0);
                progress = ((std::sin(2.0 * M_PI * fmod(std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count(), 1.0)) + 1.0) / 2.0);
                
                highlightColor = {
                    static_cast<u8>((highlightColor1.r - highlightColor2.r) * progress + highlightColor2.r),
                    static_cast<u8>((highlightColor1.g - highlightColor2.g) * progress + highlightColor2.g),
                    static_cast<u8>((highlightColor1.b - highlightColor2.b) * progress + highlightColor2.b),
                    0xF
                };
                x = 0;
                y = 0;
                
                if (this->m_highlightShaking) {
                    t = (std::chrono::system_clock::now() - this->m_highlightShakingStartTime);
                    if (t >= 100ms)
                        this->m_highlightShaking = false;
                    else {
                        amplitude = std::rand() % 5 + 5;
                        
                        switch (this->m_highlightShakingDirection) {
                            case FocusDirection::Up:
                                y -= shakeAnimation(t, amplitude);
                                break;
                            case FocusDirection::Down:
                                y += shakeAnimation(t, amplitude);
                                break;
                            case FocusDirection::Left:
                                x -= shakeAnimation(t, amplitude);
                                break;
                            case FocusDirection::Right:
                                x += shakeAnimation(t, amplitude);
                                break;
                            default:
                                break;
                        }
                        
                        x = std::clamp(x, -amplitude, amplitude);
                        y = std::clamp(y, -amplitude, amplitude);
                    }
                }
                if ((disableSelectionBG && this->m_clickAnimationProgress == 0) || !disableSelectionBG) {
                    
                    renderer->drawRect(this->getX() + x + 5 -1, this->getY() + y - 4, this->getWidth() - 5 +2 +4, 5, highlightColor);
                    renderer->drawRect(this->getX() + x + 5 -1, this->getY() + y + this->getHeight(), this->getWidth() - 5 +2 +4, 5, highlightColor);
                    renderer->drawRect(this->getX() + x, this->getY() + y + 2 - 2, 5, this->getHeight()-3 +4, highlightColor);
                    renderer->drawRect(this->getX() + x + this->getWidth()+4, this->getY() + y + 2 -2, 5, this->getHeight()-3 +4, highlightColor);
                    
                    renderer->drawCircle(this->getX() + x + 2, this->getY() + y + this->getHeight() + 2, 2.5, true, highlightColor);
                    renderer->drawCircle(this->getX() + x + 2, this->getY() + y - 2, 2.5, true, highlightColor);
                    renderer->drawCircle(this->getX() + x + this->getWidth() + 2+4, this->getY() + y + this->getHeight() + 2, 2.5, true, highlightColor);
                    renderer->drawCircle(this->getX() + x + this->getWidth() + 2+4, this->getY() + y - 2, 2.5, true, highlightColor);
                }
                //renderer->drawRect(ELEMENT_BOUNDS(this), a(0xF000)); // This has been moved here (needs to be toggleable)
            }
            
            
            
            
            /**
             * @brief Sets the boundaries of this view
             *
             * @param x Start X pos
             * @param y Start Y pos
             * @param width Width
             * @param height Height
             */
            void setBoundaries(s32 x, s32 y, s32 width, s32 height) {
                this->m_x = x;
                this->m_y = y;
                this->m_width = width;
                this->m_height = height;
            }
            
            /**
             * @brief Adds a click listener to the element
             *
             * @param clickListener Click listener called with keys that were pressed last frame. Callback should return true if keys got consumed
             */
            virtual void setClickListener(std::function<bool(u64 keys)> clickListener) {
                this->m_clickListener = clickListener;
            }
            
            /**
             * @brief Gets the element's X position
             *
             * @return X position
             */
            inline s32 getX() { return this->m_x; }
            /**
             * @brief Gets the element's Y position
             *
             * @return Y position
             */
            inline s32 getY() { return this->m_y; }
            /**
             * @brief Gets the element's Width
             *
             * @return Width
             */
            inline s32 getWidth() { return this->m_width;  }
            /**
             * @brief Gets the element's Height
             *
             * @return Height
             */
            inline s32 getHeight() { return this->m_height; }
            
            inline s32 getTopBound() { return this->getY(); }
            inline s32 getLeftBound() { return this->getX(); }
            inline s32 getRightBound() { return this->getX() + this->getWidth(); }
            inline s32 getBottomBound() { return this->getY() + this->getHeight(); }
            
            /**
             * @brief Check if the coordinates are in the elements bounds
             *
             * @return true if coordinates are in bounds, false otherwise
             */
            bool inBounds(s32 touchX, s32 touchY) {
                return touchX >= this->getLeftBound() && touchX <= this->getRightBound() && touchY >= this->getTopBound() && touchY <= this->getBottomBound();
            }
            
            /**
             * @brief Sets the element's parent
             * @note This is required to handle focus and button downpassing properly
             *
             * @param parent Parent
             */
            inline void setParent(Element *parent) { this->m_parent = parent; }
            
            /**
             * @brief Get the element's parent
             *
             * @return Parent
             */
            inline Element* getParent() { return this->m_parent; }
            

            virtual std::vector<Element*> getChildren() const {
                return {}; // Return empty vector for simplicity
            }

            ///**
            // * @brief Adds a child element to this element
            // *
            // * @param child Child element to add
            // */
            //void addChild(Element* child) {
            //    // Set the parent of the child to this element
            //    child->setParent(this);
            //    // Add the child to the list of children
            //    m_children.push_back(child);
            //}
            //
            ///**
            // * @brief Get the list of child elements
            // *
            // * @return Vector of child elements
            // */
            //const std::vector<Element*>& getChildren() const { return this->m_children; }


            /**
             * @brief Marks this element as focused or unfocused to draw the highlight
             *
             * @param focused Focused
             */
            virtual inline void setFocused(bool focused) {
                this->m_focused = focused;
                this->m_clickAnimationProgress = 0;
            }
            
            
            static InputMode getInputMode() { return Element::s_inputMode; }
            
            static void setInputMode(InputMode mode) { Element::s_inputMode = mode; }
            
        protected:
            constexpr static inline auto a = &gfx::Renderer::a;
            bool m_focused = false;
            u8 m_clickAnimationProgress = 0;
            
            // Highlight shake animation
            bool m_highlightShaking = false;
            std::chrono::system_clock::time_point m_highlightShakingStartTime;
            FocusDirection m_highlightShakingDirection;
            
            static inline InputMode s_inputMode;
            
            /**
             * @brief Shake animation callculation based on a damped sine wave
             *
             * @param t Passed time
             * @param a Amplitude
             * @return Damped sine wave output
             */
            int shakeAnimation(std::chrono::system_clock::duration t, float a) {
                float w = 0.2F;
                float tau = 0.05F;
                
                int t_ = t.count() / 1'000'000;
                
                return roundf(a * exp(-(tau * t_) * sin(w * t_)));
            }
            
        private:
            friend class Gui;
            
            s32 m_x = 0, m_y = 0, m_width = 0, m_height = 0;
            Element *m_parent = nullptr;
            std::vector<Element*> m_children;
            std::function<bool(u64 keys)> m_clickListener = [](u64) { return false; };
            
        };
        
        /**
         * @brief A Element that exposes the renderer directly to draw custom views easily
         */
        class CustomDrawer : public Element {
        public:
            /**
             * @brief Constructor
             * @note This element should only be used to draw static things the user cannot interact with e.g info text, images, etc.
             *
             * @param renderFunc Callback that will be called once every frame to draw this view
             */
            CustomDrawer(std::function<void(gfx::Renderer* r, s32 x, s32 y, s32 w, s32 h)> renderFunc) : Element(), m_renderFunc(renderFunc) {}
            virtual ~CustomDrawer() {}
            
            virtual void draw(gfx::Renderer* renderer) override {
                //renderer->enableScissoring(ELEMENT_BOUNDS(this));
                //this->m_renderFunc(renderer, ELEMENT_BOUNDS(this));
                //renderer->disableScissoring();
                
                renderer->enableScissoring(0, 97, tsl::cfg::FramebufferWidth, tsl::cfg::FramebufferHeight-73-97); // CUSTOM MODIFICATION (bug fix with renderer)
                this->m_renderFunc(renderer, ELEMENT_BOUNDS(this));
                renderer->disableScissoring();
            }
            
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                
            }
            
        private:
            std::function<void(gfx::Renderer*, s32 x, s32 y, s32 w, s32 h)> m_renderFunc;
        };
        
        // CUSTOM SECTION START
        
        
        float calculateStringWidth(const std::string& str, int fontSize) {
            
            float totalWidth = 0;
            float letterWidth;
            
            for (char letter : str) {
                // Lookup the width of the current character
                letterWidth = characterWidths[letter];
                if (letterWidth == 0) {
                    //letterWidth = 0.33; // default width
                    letterWidth = std::stof(DEFAULT_CHAR_WIDTH);
                }
                
                // Accumulate the width
                totalWidth += letterWidth;
            }
            
            // Adjust the total width based on the font size
            return (totalWidth * fontSize);
        }
        
        float calculateAmplitude2(float x, float peakDurationFactor = 0.25) {
            const float phasePeriod = 360*peakDurationFactor;  // One full phase period
            
            // Calculate the phase within the full period
            int phase = static_cast<int>((x) * (180.0 / 3.1415927)) % static_cast<int>(phasePeriod);
            
            // Check if the phase is odd
            if (phase % 2 == 1) {
                return 1.0f;  // Flat amplitude (maximum positive)
            } else {
                // Calculate the sinusoidal amplitude for the remaining period
                return (std::cos((-x) * (180.0 / 3.1415927)) + 1) / 2;
            }
        }
        
        // CUSTOM SECTION END
        
        /**
         * @brief The base frame which can contain another view
         *
         */
        class OverlayFrame : public Element {
        public:
            /**
             * @brief Constructor
             *
             * @param title Name of the Overlay drawn bolt at the top
             * @param subtitle Subtitle drawn bellow the title e.g version number
             */
            std::string m_menuMode; // CUSTOM MODIFICATION
            std::string m_colorSelection; // CUSTOM MODIFICATION
            std::string m_pageLeftName; // CUSTOM MODIFICATION
            std::string m_pageRightName; // CUSTOM MODIFICATION
            
            std::string disableColorfulLogoStr = parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "disable_colorful_logo");
            bool disableColorfulLogo = (!disableColorfulLogoStr.empty() && disableColorfulLogoStr == "true");
            tsl::Color logoColor1 = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "logo_color_1"), "#FFFFFF");
            tsl::Color logoColor2 = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "logo_color_2"), "#F7253E");
            
            
            std::string backgroundAlphaStr = parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "bg_alpha");
            size_t defaultBackgroundAlpha = (!backgroundAlphaStr.empty()) ? std::stoi(backgroundAlphaStr) : 13;
            
            tsl::Color defaultBackgroundColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "bg_color"), "#000000", defaultBackgroundAlpha);
            
            tsl::Color defaultTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "text_color"));
            tsl::Color clockColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "clock_color"));
            tsl::Color batteryColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "battery_color"));
            tsl::Color highlightColor = {0xF, 0xF, 0xF, 0xF};
            
            tsl::Color versionTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "version_text_color"), "#AAAAAA");
            tsl::Color onTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "on_text_color"), "#00FFDD");
            tsl::Color offTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "off_text_color"), "#AAAAAA");
            
            std::tuple<float,float,float> dynamicLogoRGB1 = hexToRGB444Floats(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "dynamic_logo_color_1"), "#00E669");
            std::tuple<float,float,float> dynamicLogoRGB2 = hexToRGB444Floats(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "dynamic_logo_color_2"), "#8080EA");
            
            std::string firstHalf, secondHalf;
            //tsl::Color handColor = RGB888("#F7253E");
            tsl::Color titleColor = {0xF, 0xF, 0xF, 0xF};
            const double cycleDuration = 1.5;
            float counter = 0;
            float countOffset;
            double timeInSeconds;
            float progress;
            float letterWidth;
            float x, y;
            int offset, y_offset;
            int fontSize;
            char timeStr[20]; // Allocate a buffer to store the time string
            char PCB_temperatureStr[10];
            char SOC_temperatureStr[10];
            // Convert the C-style string to an std::string
            std::string chargeStringSTD;
            std::string PCB_temperatureStringSTD;
            std::string SOC_temperatureStringSTD;
            std::string menuBottomLine;
            
            
            OverlayFrame(const std::string& title, const std::string& subtitle, const std::string& menuMode = "", const std::string& colorSelection = "", const std::string& pageLeftName = "", const std::string& pageRightName = "")
                : Element(), m_menuMode(menuMode), m_title(title), m_subtitle(subtitle), m_colorSelection(colorSelection), m_pageLeftName(pageLeftName), m_pageRightName(pageRightName) {} // CUSTOM MODIFICATION
            
            virtual ~OverlayFrame() {
                if (this->m_contentElement != nullptr)
                    delete this->m_contentElement;
            }
            
            // CUSTOM SECTION START
            virtual void draw(gfx::Renderer *renderer) override {
                renderer->fillScreen(defaultBackgroundColor);
                //renderer->fillScreen(tsl::style::color::ColorFrameBackground);
                //renderer->drawRect(tsl::cfg::FramebufferWidth - 1, 0, 1, tsl::cfg::FramebufferHeight, a(0xF222)); // CUSTOM MODIFICATION, not sure why this call was even necessary after comparisons.
                
                y = 50;
                offset = 0;
                // Check if m_title is "Ultrahand"
                if (this->m_title == "Ultrahand" && this->m_subtitle != "Ultrahand Package" && this->m_subtitle != "Ultrahand Script") {
                    chargeStringSTD = "";
                    PCB_temperatureStringSTD = "";
                    SOC_temperatureStringSTD = "";
                    
                    firstHalf = "Ultra";
                    secondHalf = "hand";
                    
                    x = 20;
                    fontSize = 42;
                    offset = 6;
                    
                    countOffset = 0;
                    
                    if (!disableColorfulLogo) {
                        for (char letter : firstHalf) {
                            
                            // Calculate the progress for each letter based on the counter
                            //progress = calculateAmplitude(counter - x * 0.001F);
                            counter = (2 * M_PI * (fmod(std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count(), cycleDuration) + countOffset) / 1.5);
                            //progress = calculateAmplitude(counter);
                            
                            // Calculate the corresponding highlight color for each letter
                            //progress = (std::sin(counter) + 1) / 2;
                            //highlightColor = {
                            //    static_cast<u8>((0xA - 0xF) * (3 - 1.5*progress) + 0xF),
                            //    static_cast<u8>((0xA - 0xF) * 1.5*progress + 0xF),
                            //    static_cast<u8>((0xA - 0xF) * (1.25 - progress) + 0xF),
                            //    0xF
                            //};
                            
                            //float red1 = 0;
                            //float green1 = 15;
                            //float blue1 = 6.25;
                            
                            //float red2 = 7.5;
                            //float green2 = 7.5;
                            //float blue2 = 13.75;
                            
                            progress = std::sin(counter); // -1 to 1
                            
                            highlightColor = {
                                static_cast<u8>((std::get<0>(dynamicLogoRGB2) - std::get<0>(dynamicLogoRGB1)) * (progress + 1.) / 2. + std::get<0>(dynamicLogoRGB1)),
                                static_cast<u8>((std::get<1>(dynamicLogoRGB2) - std::get<1>(dynamicLogoRGB1)) * (progress + 1.) / 2. + std::get<1>(dynamicLogoRGB1)),
                                static_cast<u8>((std::get<2>(dynamicLogoRGB2) - std::get<2>(dynamicLogoRGB1)) * (progress + 1.) / 2. + std::get<2>(dynamicLogoRGB1)),
                                15
                            };
                            
                            
                            // we want to rewrite this function using the color variables above
                            //highlightColor = {
                            //    static_cast<u8>(3.75  +  (3.75 * progress)), // ranges from 0 to 7.5
                            //    static_cast<u8>(11.25 + (-3.75 * progress)), // ranges from 15 to 7.5
                            //    static_cast<u8>(10.0  +  (3.75 * progress)), // ranges from 6.25 to 13.75
                            //    15
                            //};
                            
                            
                            // Draw each character with its corresponding highlight color
                            //renderer->drawString(std::string(1, letter).c_str(), false, x, y + offset, fontSize, highlightColor);
                            
                            // Call the renderer->drawString function
                            renderer->drawString(std::string(1, letter).c_str(), false, x, y + offset, fontSize, highlightColor);
                            
                            // Manually calculate the width of the current letter
                            letterWidth = calculateStringWidth(std::string(1, letter), fontSize);
                            
                            // Adjust the x-coordinate for the next character's position
                            x += letterWidth;
                            
                            // Update the counter for the next character
                            countOffset -= 0.2F;
                        }
                    } else {
                        for (char letter : firstHalf) {
                            renderer->drawString(std::string(1, letter).c_str(), false, x, y + offset, fontSize, logoColor1);
                            
                            // Manually calculate the width of the current letter
                            letterWidth = calculateStringWidth(std::string(1, letter), fontSize);
                            
                            // Adjust the x-coordinate for the next character's position
                            x += letterWidth;
                            
                            // Update the counter for the next character
                            countOffset -= 0.2F;
                        }
                    }
                    
                    
                    // Draw the second half of the string in red color
                    renderer->drawString(secondHalf.c_str(), false, x, y+offset, fontSize, logoColor2);
                    
                    
                    // Time drawing implementation
                    //struct timespec currentTime;
                    clock_gettime(CLOCK_REALTIME, &currentTime);
                    
                    y_offset = 45;
                    if ((hideBattery == "true" && hidePCBTemp == "true" && hideSOCTemp == "true") || (hideClock == "true"))
                        y_offset += 10;
                    
                    if (hideClock != "true") {// Use the 'timeStr' to display the time
                        
                        // Convert the current time to a human-readable string
                        
                        //strftime(timeStr, sizeof(timeStr), "%r", localtime(&currentTime.tv_sec));
                        strftime(timeStr, sizeof(timeStr), datetimeFormat.c_str(), localtime(&currentTime.tv_sec));
                        
                        localizeTimeStr(timeStr); // for language localizations
                        
                        renderer->drawString(timeStr, false, tsl::cfg::FramebufferWidth - calculateStringWidth(timeStr, 20) - 20, y_offset, 20, clockColor);
                        y_offset += 22;
                    }
                    
                    // check in 1s intervals
                    if ((currentTime.tv_sec - timeOut) >= 1) {
                        if (hidePCBTemp != "true")
                            thermalstatusGetDetailsPCB(&PCB_temperature);
                        if (hideSOCTemp != "true")
                            thermalstatusGetDetailsSOC(&SOC_temperature);
                        if (hideBattery != "true")
                            powerGetDetails(&batteryCharge, &isCharging);
                        //thermalstatusGetDetails(&SOC_temperature, "internal");
                        //thermalstatusGetDetails(&PCB_temperature, "external");
                        
                        timeOut = int(currentTime.tv_sec);
                    }
                    
                    
                    
                    snprintf(PCB_temperatureStr, sizeof(PCB_temperatureStr)-1, "%d°C", PCB_temperature);
                    
                    //char SOC_temperatureStr[10];
                    snprintf(SOC_temperatureStr, sizeof(SOC_temperatureStr)-1, "%d°C", SOC_temperature);
                    
                    batteryCharge = (batteryCharge > 100) ? 100 : batteryCharge;
                    sprintf(chargeString, "%d%%", batteryCharge);
                    
                    
                    // Convert the float to std::string
                    //std::string powerConsumptionStr = std::to_string(powerConsumption);
                    
                    // Use the '+' operator to concatenate the strings
                    
                    if (hideBattery != "true" && batteryCharge > 0) {
                        chargeStringSTD = chargeString;
                        //PCB_temperatureStringSTD += " ";
                        // Use the 'timeStr' to display the time
                        if (powerCacheIsCharging)
                            renderer->drawString(chargeStringSTD.c_str(), false, tsl::cfg::FramebufferWidth - calculateStringWidth(chargeStringSTD, 20) - 19, y_offset, 20, tsl::Color(0x0, 0xF, 0x0, 0xF));
                        else {
                            if (batteryCharge <= 20) {
                                renderer->drawString(chargeStringSTD.c_str(), false, tsl::cfg::FramebufferWidth - calculateStringWidth(chargeStringSTD, 20) - 19, y_offset, 20, tsl::Color(0xF, 0x0, 0x0, 0xF));
                            } else {
                                renderer->drawString(chargeStringSTD.c_str(), false, tsl::cfg::FramebufferWidth - calculateStringWidth(chargeStringSTD, 20) - 19, y_offset, 20, batteryColor);
                            }
                        }
                    }
                    //if (hidePCBTemp != "true" && hideBattery != "true")
                    //     SOC_temperatureStringSTD += " ";
                    
                    offset = 0;
                    if (hidePCBTemp != "true") {
                        PCB_temperatureStringSTD = PCB_temperatureStr;
                        if (PCB_temperature > 0) {
                            offset += 2;
                            renderer->drawString(PCB_temperatureStringSTD.c_str(), false, tsl::cfg::FramebufferWidth + offset - calculateStringWidth(PCB_temperatureStringSTD, 20) - calculateStringWidth(chargeStringSTD, 20) - 20, y_offset, 20, tsl::GradientColor(PCB_temperature));
                        }
                    }
                    if (hideSOCTemp != "true") {
                        SOC_temperatureStringSTD = SOC_temperatureStr;
                        if (SOC_temperature > 0) {
                            offset += 2;
                            renderer->drawString(SOC_temperatureStringSTD.c_str(), false, tsl::cfg::FramebufferWidth + offset -  calculateStringWidth(SOC_temperatureStringSTD, 20) - calculateStringWidth(PCB_temperatureStringSTD, 20) - calculateStringWidth(chargeStringSTD, 20) - 20, y_offset, 20, tsl::GradientColor(SOC_temperature));
                        }
                    }
                } else {
                    //static float counter = 0;
                    //progress;
                    //letterWidth;
                    x = 20;
                    y = 50;
                    fontSize = 32;
                    if (this->m_subtitle == "Ultrahand Package") {
                        std::string& title = this->m_title;
                        titleColor = Color(0x0, 0xF, 0x0, 0xF);
                        if (this->m_colorSelection == "" || this->m_colorSelection == "green") {
                            titleColor = Color(0x0, 0xF, 0x0, 0xF);
                            renderer->drawString(title.c_str(), false, x, y, fontSize, titleColor);
                        } else if (this->m_colorSelection == "red") {
                            //titleColor = a(Color(0xF, 0x0, 0x0, 0xF));
                            titleColor = RGB888("#F7253E");
                            renderer->drawString(title.c_str(), false, x, y, fontSize, titleColor);
                        } else if (this->m_colorSelection == "blue") {
                            titleColor = Color(0x7, 0x7, 0xF, 0xF);
                            renderer->drawString(title.c_str(), false, x, y, fontSize, titleColor);
                        } else if (this->m_colorSelection == "yellow") {
                            titleColor = Color(0xF, 0xF, 0x0, 0xF);
                            renderer->drawString(title.c_str(), false, x, y, fontSize, titleColor);
                        } else if (this->m_colorSelection == "orange") {
                            titleColor = Color(0xFF, 0xA5, 0x00, 0xFF);
                            renderer->drawString(title.c_str(), false, x, y, fontSize, titleColor);
                        } else if (this->m_colorSelection == "pink") {
                            titleColor = Color(0xFF, 0x69, 0xB4, 0xFF);
                            renderer->drawString(title.c_str(), false, x, y, fontSize, titleColor);
                        } else if (this->m_colorSelection == "purple") {
                            titleColor = Color(0x80, 0x00, 0x80, 0xFF);
                            renderer->drawString(title.c_str(), false, x, y, fontSize, titleColor);
                        } else if (this->m_colorSelection == "white") {
                            titleColor = Color(0xF, 0xF, 0xF, 0xF);
                            renderer->drawString(title.c_str(), false, x, y, fontSize, titleColor);
                        } else if (this->m_colorSelection == "ultra") {
                            for (char letter : title) {
                                // Calculate the progress for each letter based on the counter
                                progress = calculateAmplitude2(counter - x * 0.0001F);
                                
                                // Calculate the corresponding highlight color for each letter
                                highlightColor = {
                                    static_cast<u8>((0xA - 0xF) * (3 - 1.5*progress) + 0xF),
                                    static_cast<u8>((0xA - 0xF) * 1.5*progress + 0xF),
                                    static_cast<u8>((0xA - 0xF) * (1.25 - progress) + 0xF),
                                    0xF
                                };
                                
                                // Draw each character with its corresponding highlight color
                                renderer->drawString(std::string(1, letter).c_str(), false, x, y, fontSize, highlightColor);
                                
                                // Manually calculate the width of the current letter
                                letterWidth = calculateStringWidth(std::string(1, letter), fontSize);
                                
                                // Adjust the x-coordinate for the next character's position
                                x += letterWidth;
                                
                                // Update the counter for the next character
                                counter -= 0.00004F;
                            }
                        } else if (this->m_colorSelection.size() == 7 && this->m_colorSelection[0] == '#') {
                            // Check if m_colorSelection is a valid hexadecimal color
                            //std::string hexColor = this->m_colorSelection.substr(1);
                            if (isValidHexColor(this->m_colorSelection.substr(1))) {
                                titleColor = RGB888(this->m_colorSelection.substr(1));
                                renderer->drawString(title.c_str(), false, x, y, fontSize, titleColor);
                            } else {
                                // Invalid hexadecimal color, handle the error accordingly
                                // You can log an error message or use a default color
                                renderer->drawString(title.c_str(), false, x, y, fontSize, titleColor);
                            }
                        } else { // for unknown colors
                            renderer->drawString(title.c_str(), false, x, y, fontSize, titleColor);
                        }
                    } else if (this->m_subtitle == "Ultrahand Script") {
                        renderer->drawString(this->m_title.c_str(), false, 20, 50, 32, Color(0xFF, 0x33, 0x3F, 0xFF));
                    } else {
                        renderer->drawString(this->m_title.c_str(), false, 20, 50, 30, defaultTextColor);
                    }
                }
                
                
                if (this->m_title == "Ultrahand") {
                    renderer->drawString(versionLabel.c_str(), false, 20, y+25, 15, versionTextColor);
                } else
                    renderer->drawString(this->m_subtitle.c_str(), false, 20, y+20, 15, versionTextColor);
                
                renderer->drawRect(15, tsl::cfg::FramebufferHeight - 73, tsl::cfg::FramebufferWidth - 30, 1, defaultTextColor);
                
                menuBottomLine = "\uE0E1"+GAP_2+BACK+GAP_1+"\uE0E0"+GAP_2+OK+GAP_1;
                if (this->m_menuMode == "packages") {
                    //menuBottomLine = "\uE0E1"+GAP_2+"Close"+GAP_1+"\uE0E0"+GAP_2+OK+GAP_1+"\uE0ED"+GAP_2+OVERLAYS;
                    menuBottomLine += "\uE0ED"+GAP_2+OVERLAYS;
                } else if (this->m_menuMode == "overlays") {
                    //menuBottomLine = "\uE0E1"+GAP_2+"Close"+GAP_1+"\uE0E0"+GAP_2+OK+GAP_1+"\uE0ED"+GAP_2+PACKAGES;
                    menuBottomLine += "\uE0EE"+GAP_2+PACKAGES;
                }
                
                if (!(this->m_pageLeftName).empty()) {
                    menuBottomLine += "\uE0ED"+GAP_2 + this->m_pageLeftName;
                } else if (!(this->m_pageRightName).empty()) {
                    menuBottomLine += "\uE0EE"+GAP_2 + this->m_pageRightName;
                }
                
                renderer->drawString(menuBottomLine.c_str(), false, 30, 693, 23, defaultTextColor);
                
                if (this->m_contentElement != nullptr)
                    this->m_contentElement->frame(renderer);
            }
            // CUSTOM SECTION END
            
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                this->setBoundaries(parentX, parentY, parentWidth, parentHeight);
                
                if (this->m_contentElement != nullptr) {
                    this->m_contentElement->setBoundaries(parentX + 35, parentY + 102, parentWidth - 85, parentHeight - 73 - 105); // CUSTOM MODIFICATION (125->105->102)
                    this->m_contentElement->invalidate();
                }
            }
            
            virtual Element* requestFocus(Element *oldFocus, FocusDirection direction) override {
                if (this->m_contentElement != nullptr)
                    return this->m_contentElement->requestFocus(oldFocus, direction);
                else
                    return nullptr;
            }
            
            virtual bool onTouch(TouchEvent event, s32 currX, s32 currY, s32 prevX, s32 prevY, s32 initialX, s32 initialY) {
                // Discard touches outside bounds
                if (!this->m_contentElement->inBounds(currX, currY))
                    return false;
                
                if (this->m_contentElement != nullptr)
                    return this->m_contentElement->onTouch(event, currX, currY, prevX, prevY, initialX, initialY);
                else return false;
            }
            
            /**
             * @brief Sets the content of the frame
             *
             * @param content Element
             */
            void setContent(Element *content) {
                if (this->m_contentElement != nullptr)
                    delete this->m_contentElement;
                
                this->m_contentElement = content;
                
                if (content != nullptr) {
                    this->m_contentElement->setParent(this);
                    this->invalidate();
                }
            }
            
            /**
             * @brief Changes the title of the menu
             *
             * @param title Title to change to
             */
            void setTitle(const std::string &title) {
                this->m_title = title;
            }
            
            /**
             * @brief Changes the subtitle of the menu
             *
             * @param title Subtitle to change to
             */
            void setSubtitle(const std::string &subtitle) {
                this->m_subtitle = subtitle;
            }
            
        protected:
            Element *m_contentElement = nullptr;
            
            std::string m_title, m_subtitle;
        };
        
        /**
         * @brief The base frame which can contain another view with a customizable header
         *
         */
        class HeaderOverlayFrame : public Element {
        public:
            std::string backgroundAlphaStr = parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "bg_alpha");
            size_t defaultBackgroundAlpha = (!backgroundAlphaStr.empty()) ? std::stoi(backgroundAlphaStr) : 13;
            tsl::Color defaultBackgroundColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "bg_color"), "#000000", defaultBackgroundAlpha);
            
            tsl::Color defaultTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "text_color"));
            
            HeaderOverlayFrame(u16 headerHeight = 175) : Element(), m_headerHeight(headerHeight) {}
            virtual ~HeaderOverlayFrame() {
                if (this->m_contentElement != nullptr)
                    delete this->m_contentElement;
                
                if (this->m_header != nullptr)
                    delete this->m_header;
            }
            
            virtual void draw(gfx::Renderer *renderer) override {
                renderer->fillScreen(defaultBackgroundColor);
                //renderer->fillScreen(tsl::style::color::ColorFrameBackground);
                renderer->drawRect(tsl::cfg::FramebufferWidth - 1, 0, 1, tsl::cfg::FramebufferHeight, a(0xF222));
                
                renderer->drawRect(15, tsl::cfg::FramebufferHeight - 73, tsl::cfg::FramebufferWidth - 30, 1, defaultTextColor);
                
                renderer->drawString(("\uE0E1  "+BACK+"     \uE0E0  "+OK).c_str(), false, 30, 693, 23, defaultTextColor); // CUSTOM MODIFICATION
                
                if (this->m_header != nullptr)
                    this->m_header->frame(renderer);
                
                if (this->m_contentElement != nullptr)
                    this->m_contentElement->frame(renderer);
            }
            
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                this->setBoundaries(parentX, parentY, parentWidth, parentHeight);
                
                if (this->m_contentElement != nullptr) {
                    this->m_contentElement->setBoundaries(parentX + 35, parentY + this->m_headerHeight, parentWidth - 85, parentHeight - 73 - this->m_headerHeight);
                    this->m_contentElement->invalidate();
                }
                
                if (this->m_header != nullptr) {
                    this->m_header->setBoundaries(parentX, parentY, parentWidth, this->m_headerHeight);
                    this->m_header->invalidate();
                }
            }
            
            virtual bool onTouch(TouchEvent event, s32 currX, s32 currY, s32 prevX, s32 prevY, s32 initialX, s32 initialY) {
                // Discard touches outside bounds
                if (!this->m_contentElement->inBounds(currX, currY))
                    return false;
                
                if (this->m_contentElement != nullptr)
                    return this->m_contentElement->onTouch(event, currX, currY, prevX, prevY, initialX, initialY);
                else return false;
            }
            
            virtual Element* requestFocus(Element *oldFocus, FocusDirection direction) override {
                if (this->m_contentElement != nullptr)
                    return this->m_contentElement->requestFocus(oldFocus, direction);
                else
                    return nullptr;
            }
            
            /**
             * @brief Sets the content of the frame
             *
             * @param content Element
             */
            void setContent(Element *content) {
                if (this->m_contentElement != nullptr)
                    delete this->m_contentElement;
                
                this->m_contentElement = content;
                
                if (content != nullptr) {
                    this->m_contentElement->setParent(this);
                    this->invalidate();
                }
            }
            
            /**
             * @brief Sets the header of the frame
             *
             * @param header Header custom drawer
             */
            void setHeader(CustomDrawer *header) {
                if (this->m_header != nullptr)
                    delete this->m_header;
                
                this->m_header = header;
                
                if (header != nullptr) {
                    this->m_header->setParent(this);
                    this->invalidate();
                }
            }
            
        protected:
            Element *m_contentElement = nullptr;
            CustomDrawer *m_header = nullptr;
            
            u16 m_headerHeight;
        };
        
        /**
         * @brief Single color rectangle element mainly used for debugging to visualize boundaries
         *
         */
        class DebugRectangle : public Element {
        public:
            /**
             * @brief Constructor
             *
             * @param color Color of the rectangle
             */
            DebugRectangle(Color color) : Element(), m_color(color) {}
            virtual ~DebugRectangle() {}
            
            virtual void draw(gfx::Renderer *renderer) override {
                renderer->drawRect(ELEMENT_BOUNDS(this), this->m_color);
            }
            
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {}
            
        private:
            Color m_color;
        };
        
        
        /**
         * @brief A List containing list items
         *
         */
        class List : public Element {
        public:
            /**
             * @brief Constructor
             *
             */
            List() : Element() {}
            virtual ~List() {
                for (auto& item : this->m_items)
                    delete item;
            }
            
            Color trackBarColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "trackbar_color"), "#555555");
            float scrollbarHeight;
            float scrollbarOffset;
            int offset;
            float prevOffset;
            s32 y;
            bool handled;
            u16 i;
            
            virtual void draw(gfx::Renderer *renderer) override {
                
                
                if (this->m_clearList) {
                    for (auto& item : this->m_items)
                        delete item;
                    
                    this->m_items.clear();
                    this->m_offset = 0;
                    this->m_focusedIndex = 0;
                    this->invalidate();
                    this->m_clearList = false;
                }
                
                for (auto [index, element] : this->m_itemsToAdd) {
                    element->invalidate();
                    if (index >= 0 && (this->m_items.size() > static_cast<size_t>(index))) {
                        const auto& it = this->m_items.cbegin() + static_cast<size_t>(index);
                        this->m_items.insert(it, element);
                    } else {
                        this->m_items.push_back(element);
                    }
                    this->invalidate();
                    this->updateScrollOffset();
                }
                this->m_itemsToAdd.clear();
                
                for (auto element : this->m_itemsToRemove) {
                    for (auto it = m_items.cbegin(); it != m_items.cend(); ++it) {
                        if (*it == element) {
                            this->m_items.erase(it);
                            if (this->m_focusedIndex >= (it - this->m_items.cbegin())) {
                                this->m_focusedIndex--;
                            }
                            this->invalidate();
                            this->updateScrollOffset();
                            delete element;
                            break;
                        }
                    }
                }
                this->m_itemsToRemove.clear();
                
                renderer->enableScissoring(this->getLeftBound(), this->getTopBound() - 5, this->getWidth(), this->getHeight() + 4);
                
                for (auto &entry : this->m_items) {
                    if (entry->getBottomBound() > this->getTopBound() && entry->getTopBound() < this->getBottomBound()) {
                        entry->frame(renderer);
                    }
                }
                
                renderer->disableScissoring();
                
                if (this->m_listHeight > this->getHeight()) {
                    scrollbarHeight = static_cast<float>(this->getHeight() * this->getHeight() / this->m_listHeight - 50);
                    if (scrollbarHeight < 0)
                        scrollbarHeight = 0;
                    scrollbarOffset = (static_cast<float>(this->m_offset)) / static_cast<float>(this->m_listHeight - this->getHeight()) * static_cast<float>(this->getHeight() - std::ceil(scrollbarHeight + 50));
                    
                    offset = 11;
                    renderer->drawRect(this->getRightBound() + 10+offset, this->getY() + scrollbarOffset, 5, scrollbarHeight, trackBarColor);
                    renderer->drawCircle(this->getRightBound() + 12+offset, this->getY() + scrollbarOffset, 2, true, trackBarColor);
                    renderer->drawCircle(this->getRightBound() + 12+offset, ( this->getY() + scrollbarOffset + (this->getY() + scrollbarOffset + this->getY() + scrollbarOffset + scrollbarHeight)/2)/2, 2, true, trackBarColor);
                    renderer->drawCircle(this->getRightBound() + 12+offset, (this->getY() + scrollbarOffset + this->getY() + scrollbarOffset + scrollbarHeight)/2, 2, true, trackBarColor);
                    renderer->drawCircle(this->getRightBound() + 12+offset, (this->getY() + scrollbarOffset + scrollbarHeight + (this->getY() + scrollbarOffset + this->getY() + scrollbarOffset + scrollbarHeight)/2)/2, 2, true, trackBarColor);
                    renderer->drawCircle(this->getRightBound() + 12+offset, this->getY() + scrollbarOffset + scrollbarHeight, 2, true, trackBarColor);
                    
                    prevOffset = this->m_offset;
                    
                    if (Element::getInputMode() == InputMode::Controller)
                        this->m_offset += ((this->m_nextOffset) - this->m_offset) * 0.1F;
                    else if (Element::getInputMode() == InputMode::TouchScroll)
                        this->m_offset += ((this->m_nextOffset) - this->m_offset);
                    
                    if (static_cast<u32>(prevOffset) != static_cast<u32>(this->m_offset))
                        this->invalidate();
                }
                
            }
            
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                y = this->getY() - this->m_offset;
                
                this->m_listHeight = 0;
                for (auto &entry : this->m_items)
                    this->m_listHeight += entry->getHeight();
                
                for (auto &entry : this->m_items) {
                    entry->setBoundaries(this->getX(), y, this->getWidth(), entry->getHeight());
                    entry->invalidate();
                    y += entry->getHeight();
                }
            }
            
            virtual bool onTouch(TouchEvent event, s32 currX, s32 currY, s32 prevX, s32 prevY, s32 initialX, s32 initialY) {
                handled = false;
                
                // Discard touches out of bounds
                if (!this->inBounds(currX, currY))
                    return false;
                
                // Direct touches to all children
                for (auto &item : this->m_items)
                    handled |= item->onTouch(event, currX, currY, prevX, prevY, initialX, initialY);
                
                if (handled)
                    return true;
                
                // Handle scrolling
                if (event != TouchEvent::Release && Element::getInputMode() == InputMode::TouchScroll) {
                    if (prevX != 0 && prevY != 0)
                        this->m_nextOffset += (prevY - currY);
                    
                    if (this->m_nextOffset < 0)
                        this->m_nextOffset = 0;
                    
                    if (this->m_nextOffset > (this->m_listHeight - this->getHeight()) + 50)
                        this->m_nextOffset = (this->m_listHeight - this->getHeight() + 50);
                    
                    return true;
                }
                
                return false;
            }
            
            /**
             * @brief Adds a new item to the list before the next frame starts
             *
             * @param element Element to add
             * @param index Index in the list where the item should be inserted. -1 or greater list size will insert it at the end
             * @param height Height of the element. Don't set this parameter for libtesla to try and figure out the size based on the type
             */
            void addItem(Element *element, u16 height = 0, ssize_t index = -1) {
                if (element != nullptr) {
                    if (height != 0)
                        element->setBoundaries(this->getX(), this->getY(), this->getWidth(), height);
                    
                    element->setParent(this);
                    element->invalidate();
                    
                    this->m_itemsToAdd.emplace_back(index, element);
                }
            }
            
            /**
             * @brief Removes an item form the list and deletes it
             * @note Item will only be deleted if it was found in the list
             *
             * @param element Element to remove from list. Call \ref Gui::removeFocus before.
             */
            virtual void removeItem(Element *element) {
                if (element != nullptr)
                    this->m_itemsToRemove.emplace_back(element);
            }
            
            /**
             * @brief Try to remove an item from the list
             *
             * @param index Index of element in list. Call \ref Gui::removeFocus before.
             */
            virtual void removeIndex(size_t index) {
                if (index < this->m_items.size())
                    removeItem(this->m_items[index]);
            }
            
            /**
             * @brief Removes all children from the list later on
             * @warning When clearing a list, make sure none of the its children are focused. Call \ref Gui::removeFocus before.
             */
            void clear() {
                this->m_clearList = true;
            }
            
            virtual Element* requestFocus(Element *oldFocus, FocusDirection direction) override {
                Element *newFocus = nullptr;
                
                if (this->m_clearList || this->m_itemsToAdd.size() > 0)
                    return nullptr;
                
                if (direction == FocusDirection::None) {
                    i = 0;
                    
                    if (oldFocus == nullptr) {
                        s32 elementHeight = 0;
                        while (elementHeight < this->m_offset && i < this->m_items.size() - 1) {
                            i++;
                            elementHeight += this->m_items[i]->getHeight();
                        }
                    }
                    
                    for (; i < this->m_items.size(); i++) {
                        newFocus = this->m_items[i]->requestFocus(oldFocus, direction);
                        
                        if (newFocus != nullptr) {
                            this->m_focusedIndex = i;
                            
                            this->updateScrollOffset();
                            return newFocus;
                        }
                    }
                } else {
                    if (direction == FocusDirection::Down) {
                        
                        for (u16 i = this->m_focusedIndex + 1; i < this->m_items.size(); i++) {
                            newFocus = this->m_items[i]->requestFocus(oldFocus, direction);
                            
                            if (newFocus != nullptr && newFocus != oldFocus) {
                                this->m_focusedIndex = i;
                                
                                this->updateScrollOffset();
                                return newFocus;
                            }
                        }
                        
                        return oldFocus;
                    } else if (direction == FocusDirection::Up) {
                        if (this->m_focusedIndex > 0) {
                            
                            for (u16 i = this->m_focusedIndex - 1; i >= 0; i--) {
                                if (i > this->m_items.size() || this->m_items[i] == nullptr)
                                    return oldFocus;
                                else
                                    newFocus = this->m_items[i]->requestFocus(oldFocus, direction);
                                
                                if (newFocus != nullptr && newFocus != oldFocus) {
                                    this->m_focusedIndex = i;
                                    
                                    this->updateScrollOffset();
                                    return newFocus;
                                }
                            }
                        }
                        
                        return oldFocus;
                    }
                }
                
                return oldFocus;
            }
            
            /**
             * @brief Gets the item at the index in the list
             *
             * @param index Index position in list
             * @return Element from list. nullptr for if the index is out of bounds
             */
            virtual Element* getItemAtIndex(u32 index) {
                if (this->m_items.size() <= index)
                    return nullptr;
                
                return this->m_items[index];
            }
            
            /**
             * @brief Gets the index in the list of the element passed in
             *
             * @param element Element to check
             * @return Index in list. -1 for if the element isn't a member of the list
             */
            virtual s32 getIndexInList(Element *element) {
                auto it = std::find(this->m_items.begin(), this->m_items.end(), element);
                
                if (it == this->m_items.end())
                    return -1;
                
                return it - this->m_items.begin();
            }
            
            virtual void setFocusedIndex(u32 index) {
                if (this->m_items.size() > index) {
                    m_focusedIndex = index;
                    this->updateScrollOffset();
                }
            }
            
        protected:
            std::vector<Element*> m_items;
            u16 m_focusedIndex = 0;
            
            float m_offset = 0, m_nextOffset = 0;
            s32 m_listHeight = 0;
            
            bool m_clearList = false;
            std::vector<Element *> m_itemsToRemove;
            std::vector<std::pair<ssize_t, Element *>> m_itemsToAdd;
            
        private:
            
            virtual void updateScrollOffset() {
                if (this->getInputMode() != InputMode::Controller)
                    return;
                
                if (this->m_listHeight <= this->getHeight()) {
                    this->m_nextOffset = 0;
                    this->m_offset = 0;
                    
                    return;
                }
                
                this->m_nextOffset = 0;
                for (u16 i = 0; i < this->m_focusedIndex; i++)
                    this->m_nextOffset += this->m_items[i]->getHeight();
                
                this->m_nextOffset -= this->getHeight() / 3;
                
                if (this->m_nextOffset < 0)
                    this->m_nextOffset = 0;
                
                if (this->m_nextOffset > (this->m_listHeight - this->getHeight()) + 50)
                    this->m_nextOffset = (this->m_listHeight - this->getHeight() + 50);
            }
        };
        
        /**
         * @brief A item that goes into a list
         *
         */
        class ListItem : public Element {
        public:
            std::string seperatorAlphaStr = parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "seperator_alpha");
            size_t seperatorAlpha = (!seperatorAlphaStr.empty()) ? std::stoi(seperatorAlphaStr) : 7;
            
            tsl::Color seperatorColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "seperator_color"), "#777777", seperatorAlpha);
            
            tsl::Color defaultTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "text_color")); ; // CUSTOM MODIFICATION
            tsl::Color selectedTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "selection_text_color"));
            
            tsl::Color invalidTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "invalid_text_color"), "#FF0000");
            tsl::Color onTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "on_text_color"), "#00FFDD");
            tsl::Color offTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "off_text_color"), "#AAAAAA");
            
            tsl::Color clickTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "click_text_color"));
            tsl::Color clickColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "click_color"));

            std::chrono::system_clock::time_point timeIn;// = std::chrono::system_clock::now();
            std::chrono::duration<long int, std::ratio<1, 1000000000>> t;
            u32 width, height;
            
            /**
             * @brief Constructor
             *
             * @param text Initial description text
             */
            ListItem(const std::string& text, const std::string& value = "")
                : Element(), m_text(text), m_value(value) {
            }
            virtual ~ListItem() {}
            
            virtual void draw(gfx::Renderer *renderer) override {
                bool useClickTextColor = false;
                if (this->m_touched && Element::getInputMode() == InputMode::Touch) {
                    if (touchInBounds) {
                        renderer->drawRect(ELEMENT_BOUNDS(this), clickColor);
                        useClickTextColor = true;
                    }
                    //renderer->drawRect(ELEMENT_BOUNDS(this), tsl::style::color::ColorClickAnimation);
                }
                
                if (this->m_maxWidth == 0) {
                    if (this->m_value.length() > 0) {
                        std::tie(width, height) = renderer->drawString(this->m_value.c_str(), false, 0, 0, 20, tsl::style::color::ColorTransparent);
                        this->m_maxWidth = this->getWidth() - width - 70;
                    } else {
                        this->m_maxWidth = this->getWidth() - 40;
                    }
                    
                    std::tie(width, height) = renderer->drawString(this->m_text.c_str(), false, 0, 0, 23, tsl::style::color::ColorTransparent);
                    this->m_trunctuated = width > this->m_maxWidth;
                    
                    if (this->m_trunctuated) {
                        this->m_scrollText = this->m_text + "        ";
                        std::tie(width, height) = renderer->drawString(this->m_scrollText.c_str(), false, 0, 0, 23, tsl::style::color::ColorTransparent);
                        this->m_scrollText += this->m_text;
                        this->m_textWidth = width;
                        if (this->m_value.length() > 0) {
                            this->m_ellipsisText = renderer->limitStringLength(this->m_text, false, 23, this->m_maxWidth);
                        } else {
                            this->m_ellipsisText = renderer->limitStringLength(this->m_text, false, 24, this->m_maxWidth);
                        }
                    } else {
                        this->m_textWidth = width;
                    }
                }
                
                //renderer->drawRect(this->getX(), this->getY(), this->getWidth(), 1, tsl::style::color::ColorFrame);
                //renderer->drawRect(this->getX()+4, this->getTopBound(), this->getWidth()-4, 1, a(0x0000));
                
                //renderer->drawRect(this->getX()+5, this->getTopBound(), this->getWidth()-5+10, 1, tsl::style::color::ColorFrame);
                renderer->drawRect(this->getX()+5, this->getTopBound(), this->getWidth()-5+10, 1, seperatorColor);
                
                if (this->m_trunctuated) {
                    if (this->m_focused) {
                        renderer->enableScissoring(this->getX()+7, 97, this->m_maxWidth + 40 - 10+2+4, tsl::cfg::FramebufferHeight-73-97);
                        //renderer->enableScissoring(this->getX(), this->getY(), this->m_maxWidth + 40, this->getHeight());
                        //renderer->drawString(this->m_scrollText.c_str(), false, this->getX() + 20.0 - std::round(this->m_scrollOffset*10000.0)/10000.0, this->getY() + 45, 23, defaultTextColor);
                        renderer->drawString(this->m_scrollText.c_str(), false, this->getX() + 20.0 - this->m_scrollOffset, this->getY() + 45, 23, selectedTextColor);
                        renderer->disableScissoring();
                        t = std::chrono::system_clock::now() - this->timeIn;
                        if (t >= 2000ms) {
                            if (this->m_scrollOffset >= this->m_textWidth) {
                                this->m_scrollOffset = 0;
                                this->timeIn = std::chrono::system_clock::now();
                            } else {
                                // Calculate the increment based on the desired scroll rate
                                //this->m_scrollOffset = (1.0-0.9) * this->m_scrollOffset + 0.9 * (0.1 * std::chrono::duration_cast<std::chrono::milliseconds>(t - 2000ms).count());
                                //this->m_scrollOffset = (half(0.1) * std::chrono::duration_cast<std::chrono::milliseconds>(t - 2000ms).count());
                                this->m_scrollOffset = ((0.1) * std::chrono::duration_cast<std::chrono::milliseconds>(t - 2000ms).count());
                                //this->m_scrollOffset = (customRound(0.10 * std::chrono::duration_cast<std::chrono::milliseconds>((t) - 2000ms).count() * 10000.0) / 10000.0);
                            }
                        } // CUSTOM MODIFICATION END
                    } else {
                        renderer->drawString(this->m_ellipsisText.c_str(), false, this->getX() + 20, this->getY() + 45, 23, !useClickTextColor ? defaultTextColor : clickTextColor);
                    }
                } else {
                    if (this->m_focused) {
                        renderer->drawString(this->m_text.c_str(), false, this->getX() + 20, this->getY() + 45, 23, !useClickTextColor ? selectedTextColor : clickTextColor);
                    } else {
                        renderer->drawString(this->m_text.c_str(), false, this->getX() + 20, this->getY() + 45, 23, !useClickTextColor ? defaultTextColor : clickTextColor);
                    }
                }
                
                
                // CUSTOM SECTION START (modification for submenu footer color)
                if (this->m_value == DROPDOWN_SYMBOL || this->m_value == OPTION_SYMBOL) {
                    if (this->m_focused)
                        renderer->drawString(this->m_value.c_str(), false, this->getX() + this->m_maxWidth + 45 + 10 +4, this->getY() + 45, 20, !useClickTextColor ? (this->m_faint ? offTextColor : selectedTextColor) : clickTextColor);
                    else
                        renderer->drawString(this->m_value.c_str(), false, this->getX() + this->m_maxWidth + 45 + 10 +4, this->getY() + 45, 20, !useClickTextColor ? (this->m_faint ? offTextColor : defaultTextColor) : clickTextColor);
                } else if (this->m_value == CROSSMARK_SYMBOL) {
                    renderer->drawString(this->m_value.c_str(), false, this->getX() + this->m_maxWidth + 45 + 10 +4, this->getY() + 45, 20, !useClickTextColor ? (this->m_faint ? offTextColor : invalidTextColor) : clickTextColor);
                } else {
                    renderer->drawString(this->m_value.c_str(), false, this->getX() + this->m_maxWidth + 45 + 10 +4, this->getY() + 45, 20, !useClickTextColor ? (this->m_faint ? offTextColor : onTextColor) : clickTextColor);
                }
                // CUSTOM SECTION END 
            }
            
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                this->setBoundaries(this->getX(), this->getY(), this->getWidth()-2, tsl::style::ListItemDefaultHeight);
            }
            
            virtual bool onClick(u64 keys) override {
                if (keys & HidNpadButton_A)
                    this->triggerClickAnimation();
                else if (keys & (HidNpadButton_AnyUp | HidNpadButton_AnyDown | HidNpadButton_AnyLeft | HidNpadButton_AnyRight))
                    this->m_clickAnimationProgress = 0;
                
                return Element::onClick(keys);
            }
            
            
            virtual bool onTouch(TouchEvent event, s32 currX, s32 currY, s32 prevX, s32 prevY, s32 initialX, s32 initialY) override {
                if (event == TouchEvent::Touch)
                    this->m_touched = this->inBounds(currX, currY);
                
                if (event == TouchEvent::Release && this->m_touched) {
                    this->m_touched = false;
                    
                    if (Element::getInputMode() == InputMode::Touch) {
                        bool handled = this->onClick(HidNpadButton_A);
                        
                        this->m_clickAnimationProgress = 0;
                        return handled;
                    }
                }
                
                
                return false;
            }
            
            
            virtual void setFocused(bool state) override {
                this->m_scroll = false;
                this->m_scrollOffset = 0;
                this->timeIn = std::chrono::system_clock::now(); // CUSTOM MODIFICATION
                Element::setFocused(state);
            }
            
            virtual Element* requestFocus(Element *oldFocus, FocusDirection direction) override {
                return this;
            }
            
            /**
             * @brief Sets the left hand description text of the list item
             *
             * @param text Text
             */
            inline void setText(const std::string& text) {
                this->m_text = text;
                this->m_scrollText = "";
                this->m_ellipsisText = "";
                this->m_maxWidth = 0;
            }
            
            /**
             * @brief Sets the right hand value text of the list item
             *
             * @param value Text
             * @param faint Should the text be drawn in a glowing green or a faint gray
             */
            inline void setValue(const std::string& value, bool faint = false) {
                this->m_value = value;
                this->m_faint = faint;
                this->m_maxWidth = 0;
            }
            
            /**
             * @brief Gets the left hand description text of the list item
             *
             * @return Text
             */
            inline const std::string& getText() const {
                return this->m_text;
            }
            
            /**
             * @brief Gets the right hand value text of the list item
             *
             * @return Value
             */
            inline const std::string& getValue() {
                return this->m_value;
            }
            
        protected:
            std::string m_text;
            std::string m_value = "";
            std::string m_scrollText = "";
            std::string m_ellipsisText = "";
            
            bool m_scroll = false;
            bool m_trunctuated = false;
            bool m_faint = false;
            
            bool m_touched = false;
            
            u16 m_maxScroll = 0;
            //half m_scrollOffset = half(0);
            float m_scrollOffset = 0.0;
            u32 m_maxWidth = 0;
            u32 m_textWidth = 0;
        };
        
        /**
         * @brief A toggleable list item that changes the state from On to Off when the A button gets pressed
         *
         */
        class ToggleListItem : public ListItem {
        public:
            /**
             * @brief Constructor
             *
             * @param text Initial description text
             * @param initialState Is the toggle set to On or Off initially
             * @param onValue Value drawn if the toggle is on
             * @param offValue Value drawn if the toggle is off
             */
            ToggleListItem(const std::string& text, bool initialState, const std::string& onValue = ON, const std::string& offValue = OFF)
                : ListItem(text), m_state(initialState), m_onValue(onValue), m_offValue(offValue) {
                    
                this->setState(this->m_state);
            }
            
            virtual ~ToggleListItem() {}
            
            virtual bool onClick(u64 keys) override {
                if (keys & HidNpadButton_A) {
                    this->m_state = !this->m_state;
                    
                    this->setState(this->m_state);
                    this->m_stateChangedListener(this->m_state);
                    
                    return ListItem::onClick(keys);
                }
                
                return false;
            }
            
            /**
             * @brief Gets the current state of the toggle
             *
             * @return State
             */
            virtual inline bool getState() {
                return this->m_state;
            }
            
            /**
             * @brief Sets the current state of the toggle. Updates the Value
             *
             * @param state State
             */
            virtual void setState(bool state) {
                this->m_state = state;
                
                if (state)
                    this->setValue(this->m_onValue, false);
                else
                    this->setValue(this->m_offValue, true);
            }
            
            /**
             * @brief Adds a listener that gets called whenever the state of the toggle changes
             *
             * @param stateChangedListener Listener with the current state passed in as parameter
             */
            void setStateChangedListener(std::function<void(bool)> stateChangedListener) {
                this->m_stateChangedListener = stateChangedListener;
            }
            
        protected:
            bool m_state = true;
            std::string m_onValue, m_offValue;
            
            std::function<void(bool)> m_stateChangedListener = [](bool){};
        };
        
        class CategoryHeader : public Element {
        public:
            tsl::Color defaultTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "text_color"));
            
            CategoryHeader(const std::string &title, bool hasSeparator = false) : m_text(title), m_hasSeparator(hasSeparator) {}
            virtual ~CategoryHeader() {}
            
            virtual void draw(gfx::Renderer *renderer) override {
                renderer->drawRect(this->getX() - 2, this->getBottomBound() - 30, 5, 23, defaultTextColor);
                renderer->drawString(this->m_text.c_str(), false, this->getX() + 13, this->getBottomBound() - 12, 15, defaultTextColor);
                
                //if (this->m_hasSeparator)
                //    renderer->drawRect(this->getX(), this->getBottomBound(), this->getWidth(), 1, tsl::style::color::ColorFrame); // CUSTOM MODIFICATION
            }
            
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                // Check if the CategoryHeader is part of a list and if it's the first entry in it, half it's height
                if (List *list = dynamic_cast<List*>(this->getParent()); list != nullptr) {
                    if (list->getIndexInList(this) == 0) {
                        this->setBoundaries(this->getX(), this->getY(), this->getWidth(), tsl::style::ListItemDefaultHeight / 2);
                        return;
                    }
                }
                if (!m_hasSeparator) { // CUSTOM MODIFICATION
                    this->setBoundaries(this->getX(), this->getY(), this->getWidth(), tsl::style::ListItemDefaultHeight *3/4); // CUSTOM MODIFICATION
                } else {
                    this->setBoundaries(this->getX(), this->getY(), this->getWidth(), tsl::style::ListItemDefaultHeight / 2); // CUSTOM MODIFICATION
                }
            }
            
            virtual bool onClick(u64 keys) {
                return false;
            }
            
            virtual Element* requestFocus(Element *oldFocus, FocusDirection direction) override {
                return nullptr;
            }
            
            inline void setText(const std::string &text) {
                this->m_text = text;
            }
            
            inline const std::string& getText() const {
                return this->m_text;
            }
            
        private:
            std::string m_text;
            bool m_hasSeparator;
        };
        
        /**
         * @brief A customizable analog trackbar going from 0% to 100% (like the brightness slider)
         *
         */
        class TrackBar : public Element {
        public:
            Color defaultTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "text_color"));
            Color trackBarColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "trackbar_color"), "#555555");
            std::chrono::duration<long int, std::ratio<1, 1000000000>> t;
            Color highlightColor = {0xf,0xf,0xf,0xf};
            //alf progress;
            float progress;
            float counter = 0.0;
            s32 x, y;
            s32 amplitude;
            
            /**
             * @brief Constructor
             *
             * @param icon Icon shown next to the track bar
             */
            TrackBar(const char icon[3]) : m_icon(icon) { }
            
            virtual ~TrackBar() {}
            
            virtual Element* requestFocus(Element *oldFocus, FocusDirection direction) {
                return this;
            }
            
            virtual bool handleInput(u64 keysDown, u64 keysHeld, const HidTouchState &touchPos, HidAnalogStickState leftJoyStick, HidAnalogStickState rightJoyStick) override {
                if (keysHeld & HidNpadButton_AnyLeft && keysHeld & HidNpadButton_AnyRight)
                    return true;
                
                if (keysHeld & HidNpadButton_AnyLeft) {
                    if (this->m_value > 0) {
                        this->m_value--;
                        this->m_valueChangedListener(this->m_value);
                        return true;
                    }
                }
                
                if (keysHeld & HidNpadButton_AnyRight) {
                    if (this->m_value < 100) {
                        this->m_value++;
                        this->m_valueChangedListener(this->m_value);
                        return true;
                    }
                }
                
                return false;
            }
            
            virtual bool onTouch(TouchEvent event, s32 currX, s32 currY, s32 prevX, s32 prevY, s32 initialX, s32 initialY) override {
                if (event == TouchEvent::Release) {
                    this->m_interactionLocked = false;
                    return false;
                }
                
                
                if (!this->m_interactionLocked && this->inBounds(initialX, initialY)) {
                    if (currX > this->getLeftBound() + 50 && currX < this->getRightBound() && currY > this->getTopBound() && currY < this->getBottomBound()) {
                        s16 newValue = (static_cast<float>(currX - (this->getX() + 60)) / static_cast<float>(this->getWidth() - 95)) * 100;
                        
                        if (newValue < 0) {
                            newValue = 0;
                        } else if (newValue > 100) {
                            newValue = 100;
                        }
                        
                        if (newValue != this->m_value) {
                            this->m_value = newValue;
                            this->m_valueChangedListener(this->getProgress());
                        }
                        
                        return true;
                    }
                }
                else
                    this->m_interactionLocked = true;
                
                return false;
            }
            
            virtual void draw(gfx::Renderer *renderer) override {
                //renderer->drawRect(this->getX(), this->getY(), this->getWidth(), 1, tsl::style::color::ColorFrame);
                //renderer->drawRect(this->getX(), this->getBottomBound(), this->getWidth(), 1, tsl::style::color::ColorFrame);
                
                renderer->drawString(this->m_icon, false, this->getX() + 15, this->getY() + 50, 23, defaultTextColor);
                
                //u16 handlePos = (this->getWidth() - 95) * static_cast<half>(this->m_value) / 100;
                u16 handlePos = (this->getWidth() - 95) * (this->m_value) / 100;
                renderer->drawCircle(this->getX() + 60, this->getY() + 42, 2, true, tsl::style::color::ColorHighlight);
                renderer->drawCircle(this->getX() + 60 + this->getWidth() - 95, this->getY() + 42, 2, true, tsl::style::color::ColorFrame);
                //renderer->drawRect(this->getX() + 60 + handlePos, this->getY() + 40, this->getWidth() - 95 - handlePos, 5, tsl::style::color::ColorFrame);
                renderer->drawRect(this->getX() + 60, this->getY() + 40, handlePos, 5, tsl::style::color::ColorHighlight);
                
                renderer->drawCircle(this->getX() + 62 + handlePos, this->getY() + 42, 18, true, trackBarColor);
                renderer->drawCircle(this->getX() + 62 + handlePos, this->getY() + 42, 18, false, tsl::style::color::ColorFrame);
            }
            
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                this->setBoundaries(this->getX(), this->getY(), this->getWidth(), tsl::style::TrackBarDefaultHeight);
            }
            
            virtual void drawFocusBackground(gfx::Renderer *renderer) {
                // No background drawn here in HOS
            }
            
            virtual void drawHighlight(gfx::Renderer *renderer) override {
                //static half counter = half(0);
                //progress = half((std::sin(counter) + 1.0) / 2.0);
                //static float counter = 0.0;
                progress = ((std::sin(counter) + 1.0) / 2.0);
                highlightColor = {   static_cast<u8>((0x2 - 0x8) * progress + 0x8),
                                     static_cast<u8>((0x8 - 0xF) * progress + 0xF),
                                     static_cast<u8>((0xC - 0xF) * progress + 0xF),
                                     static_cast<u8>((0x6 - 0xD) * progress + 0xD) };
                                     
                //counter += half(0.1F);
                counter += 0.1F;
                
                //u16 handlePos = (this->getWidth() - 95) * static_cast<half>(this->m_value) / 100;
                u16 handlePos = (this->getWidth() - 95) * (this->m_value) / 100;
                
                x = 0;
                y = 0;
                
                if (Element::m_highlightShaking) {
                    t = (std::chrono::system_clock::now() - Element::m_highlightShakingStartTime);
                    if (t >= 100ms)
                        Element::m_highlightShaking = false;
                    else {
                        amplitude = std::rand() % 5 + 5;
                        
                        switch (Element::m_highlightShakingDirection) {
                            case FocusDirection::Up:
                                y -= shakeAnimation(t, amplitude);
                                break;
                            case FocusDirection::Down:
                                y += shakeAnimation(t, amplitude);
                                break;
                            case FocusDirection::Left:
                                x -= shakeAnimation(t, amplitude);
                                break;
                            case FocusDirection::Right:
                                x += shakeAnimation(t, amplitude);
                                break;
                            default:
                                break;
                        }
                        
                        x = std::clamp(x, -amplitude, amplitude);
                        y = std::clamp(y, -amplitude, amplitude);
                    }
                }
                
                for (u8 i = 16; i <= 19; i++) {
                    renderer->drawCircle(this->getX() + 62 + x + handlePos, this->getY() + 42 + y, i, false, highlightColor);
                }
            }
            
            /**
             * @brief Gets the current value of the trackbar
             *
             * @return State
             */
            virtual inline u8 getProgress() {
                return this->m_value;
            }
            
            /**
             * @brief Sets the current state of the toggle. Updates the Value
             *
             * @param state State
             */
            virtual void setProgress(u8 value) {
                this->m_value = value;
            }
            
            /**
             * @brief Adds a listener that gets called whenever the state of the toggle changes
             *
             * @param stateChangedListener Listener with the current state passed in as parameter
             */
            void setValueChangedListener(std::function<void(u8)> valueChangedListener) {
                this->m_valueChangedListener = valueChangedListener;
            }
            
        protected:
            const char *m_icon = nullptr;
            s16 m_value = 0;
            bool m_interactionLocked = false;
            
            std::function<void(u8)> m_valueChangedListener = [](u8){};
        };
        
        
        /**
         * @brief A customizable analog trackbar going from 0% to 100% but using discrete steps (Like the volume slider)
         *
         */
        class StepTrackBar : public TrackBar {
        public:
            /**
             * @brief Constructor
             *
             * @param icon Icon shown next to the track bar
             * @param numSteps Number of steps the track bar has
             */
            StepTrackBar(const char icon[3], size_t numSteps)
                : TrackBar(icon), m_numSteps(numSteps) { }
            
            virtual ~StepTrackBar() {}
            
            virtual bool handleInput(u64 keysDown, u64 keysHeld, const HidTouchState &touchPos, HidAnalogStickState leftJoyStick, HidAnalogStickState rightJoyStick) override {
                static u32 tick = 0;
                
                if (keysHeld & HidNpadButton_AnyLeft && keysHeld & HidNpadButton_AnyRight) {
                    tick = 0;
                    return true;
                }
                
                if (keysHeld & (HidNpadButton_AnyLeft | HidNpadButton_AnyRight)) {
                    if ((tick == 0 || tick > 20) && (tick % 3) == 0) {
                        if (keysHeld & HidNpadButton_AnyLeft && this->m_value > 0) {
                            this->m_value = std::max(this->m_value - (100 / (this->m_numSteps - 1)), 0);
                        } else if (keysHeld & HidNpadButton_AnyRight && this->m_value < 100) {
                            this->m_value = std::min(this->m_value + (100 / (this->m_numSteps - 1)), 100);
                        } else {
                            return false;
                        }
                        this->m_valueChangedListener(this->getProgress());
                    }
                    tick++;
                    return true;
                } else {
                    tick = 0;
                }
                
                return false;
            }
            
            virtual bool onTouch(TouchEvent event, s32 currX, s32 currY, s32 prevX, s32 prevY, s32 initialX, s32 initialY) override {
                if (this->inBounds(initialX, initialY)) {
                    if (currY > this->getTopBound() && currY < this->getBottomBound()) {
                        s16 newValue = (static_cast<float>(currX - (this->getX() + 60)) / static_cast<float>(this->getWidth() - 95)) * 100;
                        
                        if (newValue < 0) {
                            newValue = 0;
                        } else if (newValue > 100) {
                            newValue = 100;
                        } else {
                            newValue = std::round(newValue / (100.0F / (this->m_numSteps - 1))) * (100.0F / (this->m_numSteps - 1));
                        }
                        
                        if (newValue != this->m_value) {
                            this->m_value = newValue;
                            this->m_valueChangedListener(this->getProgress());
                        }
                        
                        return true;
                    }
                }
                
                return false;
            }
            
            /**
             * @brief Gets the current value of the trackbar
             *
             * @return State
             */
            virtual inline u8 getProgress() override {
                return this->m_value / (100 / (this->m_numSteps - 1));
            }
            
            /**
             * @brief Sets the current state of the toggle. Updates the Value
             *
             * @param state State
             */
            virtual void setProgress(u8 value) override {
                value = std::min(value, u8(this->m_numSteps - 1));
                this->m_value = value * (100 / (this->m_numSteps - 1));
            }
            
        protected:
            u8 m_numSteps = 1;
        };
        
        
        /**
         * @brief A customizable trackbar with multiple discrete steps with specific names. Name gets displayed above the bar
         *
         */
        class NamedStepTrackBar : public StepTrackBar {
        public:
            u16 trackBarWidth, stepWidth, currentDescIndex;
            u32 descWidth, descHeight;
            
            tsl::Color offTextColor = RGB888(parseValueFromIniSection("/config/ultrahand/theme.ini", "theme", "off_text_color"), "#AAAAAA");
            
            /**
             * @brief Constructor
             *
             * @param icon Icon shown next to the track bar
             * @param stepDescriptions Step names displayed above the track bar
             */
            NamedStepTrackBar(const char icon[3], std::initializer_list<std::string> stepDescriptions)
                : StepTrackBar(icon, stepDescriptions.size()), m_stepDescriptions(stepDescriptions.begin(), stepDescriptions.end()) { }
            
            virtual ~NamedStepTrackBar() {}
            
            virtual void draw(gfx::Renderer *renderer) override {
                
                trackBarWidth = this->getWidth() - 95;
                stepWidth = trackBarWidth / (this->m_numSteps - 1);
                
                for (u8 i = 0; i < this->m_numSteps; i++) {
                    renderer->drawRect(this->getX() + 60 + stepWidth * i, this->getY() + 50, 1, 10, tsl::style::color::ColorFrame);
                }
                
                currentDescIndex = std::clamp(this->m_value / (100 / (this->m_numSteps - 1)), 0, this->m_numSteps - 1);
                
                std::tie(descWidth, descHeight) = renderer->drawString(this->m_stepDescriptions[currentDescIndex].c_str(), false, 0, 0, 15, tsl::style::color::ColorTransparent);
                renderer->drawString(this->m_stepDescriptions[currentDescIndex].c_str(), false, ((this->getX() + 60) + (this->getWidth() - 95) / 2) - (descWidth / 2), this->getY() + 20, 15, offTextColor);
                
                StepTrackBar::draw(renderer);
            }
            
        protected:
            std::vector<std::string> m_stepDescriptions;
        };
        
    }
    
    // GUI
    
    /**
     * @brief The top level Gui class
     * @note The main menu and every sub menu are a separate Gui. Create your own Gui class that extends from this one to create your own menus
     *
     */
    class Gui {
    public:
        Gui() { }
        
        virtual ~Gui() {
            if (this->m_topElement != nullptr)
                delete this->m_topElement;

            if (this->m_bottomElement != nullptr)
                delete this->m_bottomElement;
        }
        
        /**
         * @brief Creates all elements present in this Gui
         * @note Implement this function and let it return a heap allocated element used as the top level element. This is usually some kind of frame e.g \ref OverlayFrame
         *
         * @return Top level element
         */
        virtual elm::Element* createUI() = 0;
        
        /**
         * @brief Called once per frame to update values
         *
         */
        virtual void update() {}
        
        /**
         * @brief Called once per frame with the latest HID inputs
         *
         * @param keysDown Buttons pressed in the last frame
         * @param keysHeld Buttons held down longer than one frame
         * @param touchInput Last touch position
         * @param leftJoyStick Left joystick position
         * @param rightJoyStick Right joystick position
         * @return Weather or not the input has been consumed
         */
        virtual bool handleInput(u64 keysDown, u64 keysHeld, const HidTouchState &touchPos, HidAnalogStickState leftJoyStick, HidAnalogStickState rightJoyStick) {
            return false;
        }
        
        /**
         * @brief Gets the top level element
         *
         * @return Top level element
         */
        elm::Element* getTopElement() {
            return this->m_topElement;
        }
        
        /**
         * @brief Gets the bottom level element
         *
         * @return Bottom level element
         */
        elm::Element* getBottomElement() {
            return this->m_bottomElement;
        }

        /**
         * @brief Get the currently focused element
         *
         * @return Focused element
         */
        elm::Element* getFocusedElement() {
            return this->m_focusedElement;
        }
        
        /**
         * @brief Requests focus to a element
         * @note Use this function when focusing a element outside of a element's requestFocus function
         *
         * @param element Element to focus
         * @param direction Focus direction
         */
        void requestFocus(elm::Element *element, FocusDirection direction, bool shake = true) {
            elm::Element *oldFocus = this->m_focusedElement;
            
            if (element != nullptr) {
                this->m_focusedElement = element->requestFocus(oldFocus, direction);
                
                if (oldFocus != nullptr)
                    oldFocus->setFocused(false);
                
                if (this->m_focusedElement != nullptr) {
                    this->m_focusedElement->setFocused(true);
                }
            }
            
            if (shake && oldFocus == this->m_focusedElement && this->m_focusedElement != nullptr)
                this->m_focusedElement->shakeHighlight(direction);
        }
        
        /**
         * @brief Removes focus from a element
         *
         * @param element Element to remove focus from. Pass nullptr to remove the focus unconditionally
         */
        void removeFocus(elm::Element* element = nullptr) {
            if (element == nullptr || element == this->m_focusedElement) {
                if (this->m_focusedElement != nullptr) {
                    this->m_focusedElement->setFocused(false);
                    this->m_focusedElement = nullptr;
                }
            }
        }
        
        void restoreFocus() {
            this->m_initialFocusSet = false;
        }
        
    protected:
        constexpr static inline auto a = &gfx::Renderer::a;
        
    private:
        elm::Element *m_focusedElement = nullptr;
        elm::Element *m_topElement = nullptr;
        elm::Element *m_bottomElement = nullptr;
        
        bool m_initialFocusSet = false;
        
        friend class Overlay;
        friend class gfx::Renderer;
        
        //// Function to recursively find the bottom element
        //void findBottomElement(elm::Element* currentElement) {
        //    // Base case: if the current element has no children, it is the bottom element
        //    if (currentElement->getChildren().empty()) {
        //        m_bottomElement = currentElement;
        //        return;
        //    }
        //
        //    // Recursive case: traverse through all children elements
        //    for (elm::Element* child : currentElement->getChildren()) {
        //        findBottomElement(child);
        //    }
        //}

        /**
         * @brief Draws the Gui
         *
         * @param renderer
         */
        void draw(gfx::Renderer *renderer) {
            if (this->m_topElement != nullptr)
                this->m_topElement->draw(renderer);
        }
        
        bool initialFocusSet() {
            return this->m_initialFocusSet;
        }
        
        void markInitialFocusSet() {
            this->m_initialFocusSet = true;
        }
        
    };
    
    
    // Overlay
    
    /**
     * @brief The top level Overlay class
     * @note Every Tesla overlay should have exactly one Overlay class initializing services and loading the default Gui
     */
    class Overlay {
    protected:
        /**
         * @brief Constructor
         * @note Called once when the Overlay gets loaded
         */
        Overlay() {}
    public:
        /**
         * @brief Deconstructor
         * @note Called once when the Overlay exits
         *
         */
        virtual ~Overlay() {}
        
        /**
         * @brief Initializes services
         * @note Called once at the start to initializes services. You have a sm session available during this call, no need to initialize sm yourself
         */
        virtual void initServices() {}
        
        /**
         * @brief Exits services
         * @note Make sure to exit all services you initialized in \ref Overlay::initServices() here to prevent leaking handles
         */
        virtual void exitServices() {}
        
        /**
         * @brief Called before overlay changes from invisible to visible state
         *
         */
        virtual void onShow() {}
        
        /**
         * @brief Called before overlay changes from visible to invisible state
         *
         */
        virtual void onHide() {}
        
        /**
         * @brief Loads the default Gui
         * @note This function should return the initial Gui to load using the \ref Gui::initially<T>(Args.. args) function
         *       e.g `return initially<GuiMain>();`
         *
         * @return Default Gui
         */
        virtual std::unique_ptr<tsl::Gui> loadInitialGui() = 0;
        
        /**
         * @brief Gets a reference to the current Gui on top of the Gui stack
         *
         * @return Current Gui reference
         */
        std::unique_ptr<tsl::Gui>& getCurrentGui() {
            return this->m_guiStack.top();
        }
        
        /**
         * @brief Shows the Gui
         *
         */
        void show() {
            if (this->m_disableNextAnimation) {
                this->m_animationCounter = 5;
                this->m_disableNextAnimation = false;
            }
            else {
                this->m_fadeInAnimationPlaying = true;
                this->m_animationCounter = 0;
            }
            
            this->onShow();
            
            if (auto& currGui = this->getCurrentGui(); currGui != nullptr)
                currGui->restoreFocus();
        }
        
        /**
         * @brief Hides the Gui
         *
         */
        void hide() {
            if (this->m_disableNextAnimation) {
                this->m_animationCounter = 0;
                this->m_disableNextAnimation = false;
            }
            else {
                this->m_fadeOutAnimationPlaying = true;
                this->m_animationCounter = 5;
            }
            
            this->onHide();
        }
        
        /**
         * @brief Returns whether fade animation is playing
         *
         * @return whether fade animation is playing
         */
        bool fadeAnimationPlaying() {
            return this->m_fadeInAnimationPlaying || this->m_fadeOutAnimationPlaying;
        }
        
        /**
         * @brief Closes the Gui
         * @note This makes the Tesla overlay exit and return back to the Tesla-Menu
         *
         */
        void close() {
            this->m_shouldClose = true;
        }
        
        /**
         * @brief Gets the Overlay instance
         *
         * @return Overlay instance
         */
        static inline Overlay* const get() {
            return Overlay::s_overlayInstance;
        }
        
        /**
         * @brief Creates the initial Gui of an Overlay and moves the object to the Gui stack
         *
         * @tparam T
         * @tparam Args
         * @param args
         * @return constexpr std::unique_ptr<T>
         */
        template<typename T, typename ... Args>
        constexpr inline std::unique_ptr<T> initially(Args&&... args) {
            return std::make_unique<T>(args...);
        }
        
    private:
        using GuiPtr = std::unique_ptr<tsl::Gui>;
        std::stack<GuiPtr, std::list<GuiPtr>> m_guiStack;
        static inline Overlay *s_overlayInstance = nullptr;
        
        bool m_fadeInAnimationPlaying = true, m_fadeOutAnimationPlaying = false;
        u8 m_animationCounter = 0;
        
        bool m_shouldHide = false;
        bool m_shouldClose = false;
        
        bool m_disableNextAnimation = false;
        
        bool m_closeOnExit;
        
        /**
         * @brief Initializes the Renderer
         *
         */
        void initScreen() {
            gfx::Renderer::get().init();
        }
        
        /**
         * @brief Exits the Renderer
         *
         */
        void exitScreen() {
            gfx::Renderer::get().exit();
        }
        
        /**
         * @brief Weather or not the Gui should get hidden
         *
         * @return should hide
         */
        bool shouldHide() {
            return this->m_shouldHide;
        }
        
        /**
         * @brief Weather or not hte Gui should get closed
         *
         * @return should close
         */
        bool shouldClose() {
            return this->m_shouldClose;
        }
        
        /**
         * @brief Handles fade in and fade out animations of the Overlay
         *
         */
        void animationLoop() {
            if (this->m_fadeInAnimationPlaying) {
                this->m_animationCounter++;
                
                if (this->m_animationCounter >= 5)
                    this->m_fadeInAnimationPlaying = false;
            }
            
            if (this->m_fadeOutAnimationPlaying) {
                this->m_animationCounter--;
                
                if (this->m_animationCounter == 0) {
                    this->m_fadeOutAnimationPlaying = false;
                    this->m_shouldHide = true;
                }
            }
            
            gfx::Renderer::setOpacity(0.2 * this->m_animationCounter);
        }
        
        /**
         * @brief Main loop
         *
         */
        void loop() {
            auto& renderer = gfx::Renderer::get();
            
            renderer.startFrame();
            
            this->animationLoop();
            this->getCurrentGui()->update();
            this->getCurrentGui()->draw(&renderer);
            
            renderer.endFrame();
        }
        


        /**
         * @brief Called once per frame with the latest HID inputs
         *
         * @param keysDown Buttons pressed in the last frame
         * @param keysHeld Buttons held down longer than one frame
         * @param touchInput Last touch position
         * @param leftJoyStick Left joystick position
         * @param rightJoyStick Right joystick position
         * @return Whether or not the input has been consumed
         */
        void handleInput(u64 keysDown, u64 keysHeld, bool touchDetected, const HidTouchState &touchPos, HidAnalogStickState joyStickPosLeft, HidAnalogStickState joyStickPosRight) {
            static HidTouchState initialTouchPos = { 0 };
            static HidTouchState oldTouchPos = { 0 };
            static bool oldTouchDetected = false;
            static elm::TouchEvent touchEvent;
            static elm::TouchEvent oldTouchEvent;
            static u32 repeatTick = 0;
            
            auto& currentGui = this->getCurrentGui();
            
            if (currentGui == nullptr)
                return;
            
            auto currentFocus = currentGui->getFocusedElement();
            static auto lastFocus = currentFocus;
            auto topElement = currentGui->getTopElement();
            auto bottomElement = currentGui->getBottomElement(); // backend is still not implemented/working yet
            

            if (currentFocus == nullptr  && !simulatedBack && simulatedBackComplete && !stillTouching) {
                if (keysDown & HidNpadButton_B) {
                    if (!currentGui->handleInput(HidNpadButton_B, 0,{},{},{}))
                        this->goBack();
                    return;
                }
                
                if (topElement == nullptr)
                    return;
                else if (currentGui != nullptr) {
                    if (!currentGui->initialFocusSet() || keysDown & (HidNpadButton_AnyUp | HidNpadButton_AnyDown | HidNpadButton_AnyLeft | HidNpadButton_AnyRight)) {
                        currentGui->requestFocus(topElement, FocusDirection::None);
                        currentGui->markInitialFocusSet();
                        repeatTick = 1;
                    }
                }
            }

            // If nothing is highlighted AND the menu is fully loaded / drawn, set focus to topElement ( IMPLEMENBT THIS)
            if (!touchDetected && (!oldTouchDetected || (oldTouchEvent == elm::TouchEvent::Scroll)) && currentFocus == nullptr) {
                if (!simulatedBack && simulatedBackComplete ) {
                    if (topElement != nullptr) {
                        currentGui->removeFocus();
                        currentGui->requestFocus(topElement, FocusDirection::None);
                    }
                }
            }

            
            bool handled = false;
            elm::Element *parentElement = currentFocus;
            
            while (!handled && parentElement != nullptr) {
                handled = parentElement->onClick(keysDown);
                parentElement = parentElement->getParent();
            }
            
            parentElement = currentFocus;
            while (!handled && parentElement != nullptr) {
                handled = parentElement->handleInput(keysDown, keysHeld, touchPos, joyStickPosLeft, joyStickPosRight);
                parentElement = parentElement->getParent();
            }
            
            if (currentGui != this->getCurrentGui())
                return;
            
            handled = handled | currentGui->handleInput(keysDown, keysHeld, touchPos, joyStickPosLeft, joyStickPosRight);
            
            if (!touchDetected && !oldTouchDetected && !handled && currentFocus != nullptr && !stillTouching) {
                static bool shouldShake = true;
                
                if ((((keysHeld & HidNpadButton_AnyUp) != 0) + ((keysHeld & HidNpadButton_AnyDown) != 0) + ((keysHeld & HidNpadButton_AnyLeft) != 0) + ((keysHeld & HidNpadButton_AnyRight) != 0)) == 1) {
                    if ((repeatTick == 0 || repeatTick > 20) && (repeatTick % 4) == 0) {
                        if (keysHeld & HidNpadButton_AnyUp)
                            currentGui->requestFocus(currentGui->getTopElement(), FocusDirection::Up, shouldShake); // Request focus on the top element when double-clicking up
                        else if (keysHeld & HidNpadButton_AnyDown)
                            currentGui->requestFocus(currentFocus->getParent(), FocusDirection::Down, shouldShake);
                        else if (keysHeld & HidNpadButton_AnyLeft)
                            currentGui->requestFocus(currentFocus->getParent(), FocusDirection::Left, shouldShake);
                        else if (keysHeld & HidNpadButton_AnyRight)
                            currentGui->requestFocus(currentFocus->getParent(), FocusDirection::Right, shouldShake);
                        
                        shouldShake = currentGui->getFocusedElement() != currentFocus;
                    }
                    repeatTick++;
                } else {
                    if (keysDown & HidNpadButton_B)
                        this->goBack();
                    repeatTick = 0;
                    shouldShake = true;
                }
            }
        
            static u64 lastUpPressTimestamp = 0; // Store the timestamp of the last up button press
            
            // Define a threshold for double-click timing (in milliseconds)
            constexpr u64 DOUBLE_CLICK_THRESHOLD_MS = 100;
        
            // If the up button is pressed
            if (!touchDetected && keysDown & HidNpadButton_AnyUp) {
                // Get the current time using high_resolution_clock
                auto currentTime = std::chrono::high_resolution_clock::now();
                
                // Convert the time point to milliseconds
                auto currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();
        
                // Calculate the time since the last up button press
                u64 timeSinceLastUpPress = currentTimestamp - lastUpPressTimestamp;
        
                // If the time since the last up press is within the threshold for a double-click
                if (timeSinceLastUpPress <= DOUBLE_CLICK_THRESHOLD_MS) {
                    // Perform action for double-clicking up (shift focus to top element)
                    topElement = currentGui->getTopElement();
                    if (topElement != nullptr) {
                        currentGui->requestFocus(topElement, FocusDirection::None);
                    }
                    // Reset the last up press timestamp after successful double-click action
                    lastUpPressTimestamp = 0;
                } else {
                    // Update the last up press timestamp if not within the double-click threshold
                    lastUpPressTimestamp = currentTimestamp;
                }
            }

            static u64 lastDownPressTimestamp = 0;

            // If the down button is pressed
            if (keysDown & HidNpadButton_AnyDown) {
                // Get the current time using high_resolution_clock
                auto currentTime = std::chrono::high_resolution_clock::now();
                
                // Convert the time point to milliseconds
                auto currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();
        
                // Calculate the time since the last up button press
                u64 timeSinceLastDownPress = currentTimestamp - lastDownPressTimestamp;
        
                // If the time since the last up press is within the threshold for a double-click
                if (timeSinceLastDownPress <= DOUBLE_CLICK_THRESHOLD_MS) {
                    // Perform action for double-clicking up (shift focus to top element)
                    bottomElement = currentGui->getBottomElement();
                    if (bottomElement != nullptr) {
                        currentGui->requestFocus(bottomElement, FocusDirection::None);
                    }
                    // Reset the last up press timestamp after successful double-click action
                    lastDownPressTimestamp = 0;
                } else {
                    // Update the last up press timestamp if not within the double-click threshold
                    lastDownPressTimestamp = currentTimestamp;
                }
            }
            

            if (!touchDetected && oldTouchDetected) {
                if (currentGui != nullptr && topElement != nullptr)
                    topElement->onTouch(elm::TouchEvent::Release, oldTouchPos.x, oldTouchPos.y, oldTouchPos.x, oldTouchPos.y, initialTouchPos.x, initialTouchPos.y);
            }
            
            if (touchDetected) {
                if (!interruptedTouch)
                    interruptedTouch = ((keysHeld & ALL_KEYS_MASK) != 0);

                u32 xDistance = std::abs(static_cast<s32>(initialTouchPos.x) - static_cast<s32>(touchPos.x));
                u32 yDistance = std::abs(static_cast<s32>(initialTouchPos.y) - static_cast<s32>(touchPos.y));
                
                xDistance *= xDistance;
                yDistance *= yDistance;
                
                if ((xDistance + yDistance) > 1000) {
                    elm::Element::setInputMode(InputMode::TouchScroll);
                    touchEvent = elm::TouchEvent::Scroll;
                } else {
                    if (touchEvent != elm::TouchEvent::Scroll)
                        touchEvent = elm::TouchEvent::Hold;
                }

                // CUSTOM MODIFICATION START
                if (!oldTouchDetected) {
                    initialTouchPos = touchPos;
                    elm::Element::setInputMode(InputMode::Touch);
                    if (currentFocus != nullptr)
                        lastFocus = currentFocus;
                    if (initialTouchPos.y <= cfg::FramebufferHeight - 73U && initialTouchPos.y > 73U && initialTouchPos.x <= cfg::FramebufferWidth && initialTouchPos.x > 0U) {
                        touchInBounds = true;
                        currentGui->removeFocus();
                    } else {
                        touchInBounds = false;
                    }
                    touchEvent = elm::TouchEvent::Touch;
                }
                
                // CUSTOM MODIFICATION END
                
                if (currentGui != nullptr && topElement != nullptr) {
                    topElement->onTouch(touchEvent, touchPos.x, touchPos.y, oldTouchPos.x, oldTouchPos.y, initialTouchPos.x, initialTouchPos.y);
                }

                
                oldTouchPos = touchPos;
                
                // Hide overlay when touching out of bounds
                if (touchPos.x >= cfg::FramebufferWidth) {
                    if (tsl::elm::Element::getInputMode() == tsl::InputMode::Touch) {
                        oldTouchPos = { 0 };
                        initialTouchPos = { 0 };
                        
                        this->hide();
                    }
                }
                stillTouching = true;
            } else {
                if (!interruptedTouch) {
                    // Location of back touch button
                    if (oldTouchPos.x < 150U && oldTouchPos.y > cfg::FramebufferHeight - 73U) {
                        if (initialTouchPos.x < 150U && initialTouchPos.y > cfg::FramebufferHeight - 73U) {
                            simulatedBackComplete = false;
                            simulatedBack = true;
                        }
                    }
                    // Location of select touch button
                    if (oldTouchPos.x >= 150U && oldTouchPos.x < 260U && oldTouchPos.y > cfg::FramebufferHeight - 73U) {
                        if (initialTouchPos.x >= 150U && initialTouchPos.x < 260U && initialTouchPos.y > cfg::FramebufferHeight - 73U) {
                            simulatedSelectComplete = false;
                            simulatedSelect = true;
                        }
                    }
                    // Location of next page touch button
                    if (oldTouchPos.x >= 260U && oldTouchPos.x <= cfg::FramebufferWidth && oldTouchPos.y > cfg::FramebufferHeight - 73U) {
                        if (initialTouchPos.x >= 260U && initialTouchPos.x <= cfg::FramebufferWidth && initialTouchPos.y > cfg::FramebufferHeight - 73U) {
                            simulatedNextPageComplete = false;
                            simulatedNextPage = true;
                        }
                    }
                    // Location of menu touch button
                    if (oldTouchPos.x > 0U && oldTouchPos.x <= cfg::FramebufferWidth && oldTouchPos.y > 0U && oldTouchPos.y <= 73U) {
                        if (initialTouchPos.x > 0U && initialTouchPos.x <= cfg::FramebufferWidth && initialTouchPos.y > 0U && initialTouchPos.y <= 73U) {
                            simulatedMenuComplete = false;
                            simulatedMenu = true;
                        }
                    }
                }
                
                elm::Element::setInputMode(InputMode::Controller);
                
                oldTouchPos = { 0 };
                initialTouchPos = { 0 };
                touchEvent = elm::TouchEvent::None;
                stillTouching = false;
                interruptedTouch = false;
            }
            

            oldTouchDetected = touchDetected;
            oldTouchEvent = touchEvent;
        }


        /**
         * @brief Clears the screen
         *
         */
        void clearScreen() {
            auto& renderer = gfx::Renderer::get();
            
            renderer.startFrame();
            renderer.clearScreen();
            renderer.endFrame();
        }
        
        /**
         * @brief Reset hide and close flags that were previously set by \ref Overlay::close() or \ref Overlay::hide()
         *
         */
        void resetFlags() {
            this->m_shouldHide = false;
            this->m_shouldClose = false;
        }
        
        /**
         * @brief Disables the next animation that would play
         *
         */
        void disableNextAnimation() {
            this->m_disableNextAnimation = true;
        }
        

        /**
         * @brief Changes to a different Gui
         *
         * @param gui Gui to change to
         * @return Reference to the Gui
         */
        std::unique_ptr<tsl::Gui>& changeTo(std::unique_ptr<tsl::Gui>&& gui) {
            if (this->m_guiStack.top() != nullptr && this->m_guiStack.top()->m_focusedElement != nullptr)
                this->m_guiStack.top()->m_focusedElement->resetClickAnimation();
            
            
            // Create the top element of the new Gui
            gui->m_topElement = gui->createUI();

            
            // Push the new Gui onto the stack
            this->m_guiStack.push(std::move(gui));
            
            return this->m_guiStack.top();
        }

        
        /**
         * @brief Creates a new Gui and changes to it
         *
         * @tparam G Gui to create
         * @tparam Args Arguments to pass to the Gui
         * @param args Arguments to pass to the Gui
         * @return Reference to the newly created Gui
         */
        template<typename G, typename ...Args>
        std::unique_ptr<tsl::Gui>& changeTo(Args&&... args) {
            return this->changeTo(std::make_unique<G>(std::forward<Args>(args)...));
        }
        
        /**
         * @brief Pops the top Gui from the stack and goes back to the last one
         * @note The Overlay gets closes once there are no more Guis on the stack
         */
        void goBack() {
            if (!this->m_closeOnExit && this->m_guiStack.size() == 1) {
                this->hide();
                return;
            }
            
            if (!this->m_guiStack.empty())
                this->m_guiStack.pop();
            
            if (this->m_guiStack.empty())
                this->close();
        }
        
        template<typename G, typename ...Args>
        friend std::unique_ptr<tsl::Gui>& changeTo(Args&&... args);
        
        friend void goBack();
        
        template<typename, tsl::impl::LaunchFlags>
        friend int loop(int argc, char** argv);
        
        friend class tsl::Gui;
    };
    
    
    namespace impl {
        static const char* TESLA_CONFIG_FILE = "/config/tesla/config.ini"; // CUSTOM MODIFICATION
        static const char* ULTRAHAND_CONFIG_FILE = "/config/ultrahand/config.ini"; // CUSTOM MODIFICATION
        
        /**
         * @brief Data shared between the different threads
         *
         */
        struct SharedThreadData {
            bool running = false;
            
            Event comboEvent = { 0 };
            
            bool overlayOpen = false;
            
            std::mutex dataMutex;
            u64 keysDown = 0;
            u64 keysDownPending = 0;
            u64 keysHeld = 0;
            HidTouchScreenState touchState = { 0 };
            HidAnalogStickState joyStickPosLeft = { 0 }, joyStickPosRight = { 0 };
        };
        
        
        /**
         * @brief Extract values from Tesla settings file
         *
         */
        static void parseOverlaySettings() {
            hlp::ini::IniData parsedConfig = hlp::ini::readOverlaySettings(ULTRAHAND_CONFIG_FILE);
            
            try {
                u64 decodedKeys = hlp::comboStringToKeys(parsedConfig["ultrahand"]["key_combo"]); // CUSTOM MODIFICATION
                if (decodedKeys)
                    tsl::cfg::launchCombo = decodedKeys;
            } catch (const std::exception& e) {}
            
            try {
                datetimeFormat = removeQuotes(parsedConfig["ultrahand"]["datetime_format"]); // read datetime_format
            } catch (const std::exception& e) {}
            if (datetimeFormat.empty()) {
                datetimeFormat = removeQuotes(DEFAULT_DT_FORMAT);
            }
            
            try {
                hideClock = removeQuotes(parsedConfig["ultrahand"]["hide_clock"]);
            } catch (const std::exception& e) {}
            if (hideClock.empty())
                hideClock = "false";
            
            try {
                hideBattery = removeQuotes(parsedConfig["ultrahand"]["hide_battery"]);
            } catch (const std::exception& e) {}
            if (hideBattery.empty())
                hideBattery = "false";
            
            try {
                hidePCBTemp = removeQuotes(parsedConfig["ultrahand"]["hide_pcb_temp"]);
            } catch (const std::exception& e) {}
            if (hidePCBTemp.empty())
                hidePCBTemp = "false";
            
            try {
                hideSOCTemp = removeQuotes(parsedConfig["ultrahand"]["hide_soc_temp"]);
            } catch (const std::exception& e) {}
            if (hideSOCTemp.empty())
                hideSOCTemp = "false";
            
        }

        /**
         * @brief Update and save launch combo keys
         *
         * @param keys the new combo keys
         */
        [[maybe_unused]] static void updateCombo(u64 keys) {
            tsl::cfg::launchCombo = keys;
            hlp::ini::updateOverlaySettings({
                { "tesla", { // CUSTOM MODIFICATION
                    { "key_combo", tsl::hlp::keysToComboString(keys) }
                }}
            }, TESLA_CONFIG_FILE);
            hlp::ini::updateOverlaySettings({
                { "ultrahand", { // CUSTOM MODIFICATION
                    { "key_combo", tsl::hlp::keysToComboString(keys) }
                }}
            }, ULTRAHAND_CONFIG_FILE);
        }
        
        /**
         * @brief Background event polling loop thread
         *
         * @param args Used to pass in a pointer to a \ref SharedThreadData struct
         */
        static void backgroundEventPoller(void *args) {
            SharedThreadData *shData = static_cast<SharedThreadData*>(args);
            
            // To prevent focus glitchout, close the overlay immediately when the home button gets pressed
            Event homeButtonPressEvent = {};
            hidsysAcquireHomeButtonEventHandle(&homeButtonPressEvent, false);
            eventClear(&homeButtonPressEvent);
            hlp::ScopeGuard homeButtonEventGuard([&] { eventClose(&homeButtonPressEvent); });
            
            // To prevent focus glitchout, close the overlay immediately when the power button gets pressed
            Event powerButtonPressEvent = {};
            hidsysAcquireSleepButtonEventHandle(&powerButtonPressEvent, false);
            eventClear(&powerButtonPressEvent);
            hlp::ScopeGuard powerButtonEventGuard([&] { eventClose(&powerButtonPressEvent); });
            
            // Parse Tesla settings
            impl::parseOverlaySettings();
            
            // Configure input to take all controllers and up to 8
            padConfigureInput(8, HidNpadStyleSet_NpadStandard | HidNpadStyleTag_NpadSystemExt);
            
            // Initialize pad
            PadState pad;
            padInitializeAny(&pad);
            
            // Initialize touch screen
            hidInitializeTouchScreen();
            
            // Drop all inputs from the previous overlay
            padUpdate(&pad);
            
            enum WaiterObject {
                WaiterObject_HomeButton,
                WaiterObject_PowerButton,
                
                WaiterObject_Count
            };
            
            // Construct waiter
            Waiter objects[2] = {
                [WaiterObject_HomeButton] = waiterForEvent(&homeButtonPressEvent),
                [WaiterObject_PowerButton] = waiterForEvent(&powerButtonPressEvent),
            };
            
            while (shData->running) {
                // Scan for input changes
                padUpdate(&pad);
                
                // Read in HID values
                {
                    std::scoped_lock lock(shData->dataMutex);
                    
                    shData->keysDown = padGetButtonsDown(&pad);
                    shData->keysHeld = padGetButtons(&pad);
                    shData->joyStickPosLeft  = padGetStickPos(&pad, 0);
                    shData->joyStickPosRight = padGetStickPos(&pad, 1);
                    
                    // Read in touch positions
                    if (hidGetTouchScreenStates(&shData->touchState, 1) == 0)
                        shData->touchState = { 0 };
                    
                    if (((shData->keysHeld & tsl::cfg::launchCombo) == tsl::cfg::launchCombo) && shData->keysDown & tsl::cfg::launchCombo) {
                        //useCombo2 = "ZL+ZR+DDOWN";
                        if (shData->overlayOpen) {
                            tsl::Overlay::get()->hide();
                            shData->overlayOpen = false;
                        }
                        else
                            eventFire(&shData->comboEvent);
                    } else if (((shData->keysHeld & tsl::cfg::launchCombo2) == tsl::cfg::launchCombo2) && shData->keysDown & tsl::cfg::launchCombo2 && useCombo2) {  // CUSTOM MODIFICATION
                        tsl::cfg::launchCombo = hlp::comboStringToKeys("L+DDOWN+RS");
                        //updateCombo(tsl::cfg::launchCombo);
                        updateMenuCombos = true;
                        useCombo2 = false;
                        if (shData->overlayOpen) {
                            tsl::Overlay::get()->hide();
                            shData->overlayOpen = false;
                        }
                        else
                            eventFire(&shData->comboEvent);
                    }
                    
                    shData->keysDownPending |= shData->keysDown;
                }
                
                //20 ms
                s32 idx = 0;
                Result rc = waitObjects(&idx, objects, WaiterObject_Count, 20'000'000ul);
                if (R_SUCCEEDED(rc)) {
                    if (shData->overlayOpen) {
                        tsl::Overlay::get()->hide();
                        shData->overlayOpen = false;
                    }
                    
                    switch (idx) {
                        case WaiterObject_HomeButton:
                            eventClear(&homeButtonPressEvent);
                            break;
                        case WaiterObject_PowerButton:
                            eventClear(&powerButtonPressEvent);
                            break;
                    }
                } else if (rc != KERNELRESULT(TimedOut)) {
                    ASSERT_FATAL(rc);
                }
            }
        }
        
    }
    
    /**
     * @brief Creates a new Gui and changes to it
     *
     * @tparam G Gui to create
     * @tparam Args Arguments to pass to the Gui
     * @param args Arguments to pass to the Gui
     * @return Reference to the newly created Gui
     */
    template<typename G, typename ...Args>
    std::unique_ptr<tsl::Gui>& changeTo(Args&&... args) {
        return Overlay::get()->changeTo<G, Args...>(std::forward<Args>(args)...);
    }
    
    /**
     * @brief Pops the top Gui from the stack and goes back to the last one
     * @note The Overlay gets closed once there are no more Guis on the stack
     */
    static void goBack() {
        Overlay::get()->goBack();
    }
    
    static void setNextOverlay(const std::string& ovlPath, std::string origArgs) {
        
        //std::string args = std::filesystem::path(ovlPath).filename();
        std::string args = getNameFromPath(ovlPath); // CUSTOM MODIFICATION
        args += " " + origArgs + " --skipCombo";
        
        envSetNextLoad(ovlPath.c_str(), args.c_str());
    }
    
    
    
    /**
     * @brief libtesla's main function
     * @note Call it directly from main passing in argc and argv and returning it e.g `return tsl::loop<OverlayTest>(argc, argv);`
     *
     * @tparam TOverlay Your overlay class
     * @tparam launchFlags \ref LaunchFlags
     * @param argc argc
     * @param argv argv
     * @return int result
     */
    template<typename TOverlay, impl::LaunchFlags launchFlags>
    static inline int loop(int argc, char** argv) {
        static_assert(std::is_base_of_v<tsl::Overlay, TOverlay>, "tsl::loop expects a type derived from tsl::Overlay");
        
        impl::SharedThreadData shData;
        
        shData.running = true;
        
        Thread backgroundThread;
        threadCreate(&backgroundThread, impl::backgroundEventPoller, &shData, nullptr, 0x1000, 0x2c, -2);
        threadStart(&backgroundThread);
        
        eventCreate(&shData.comboEvent, false);
        
        auto& overlay = tsl::Overlay::s_overlayInstance;
        overlay = new TOverlay();
        overlay->m_closeOnExit = (u8(launchFlags) & u8(impl::LaunchFlags::CloseOnExit)) == u8(impl::LaunchFlags::CloseOnExit);
        
        tsl::hlp::doWithSmSession([&overlay]{ overlay->initServices(); });
        overlay->initScreen();
        overlay->changeTo(overlay->loadInitialGui());
        
        // Argument parsing
        //for (u8 arg = 0; arg < argc; arg++) {
        //    if (strcasecmp(argv[arg], "--skipCombo") == 0) {
        //        eventFire(&shData.comboEvent);
        //        overlay->disableNextAnimation();
        //    }
        //}
        
        // CUSTOM SECTION START
        // Argument parsing
        bool skipCombo = false;
        for (u8 arg = 0; arg < argc; arg++) {
            if (strcasecmp(argv[arg], "--skipCombo") == 0) {
                //eventFire(&shData.comboEvent);
                //overlay->disableNextAnimation();
                skipCombo = true;
            }
        }
        
        std::string settingsConfigPath = "sdmc:/config/ultrahand/config.ini";
        std::string teslaSettingsConfigIniPath = "sdmc:/config/tesla/config.ini";
        std::map<std::string, std::map<std::string, std::string>> settingsData = getParsedDataFromIniFile(settingsConfigPath);
        std::string inOverlayString;
        
        if (settingsData.count("ultrahand") > 0 && settingsData["ultrahand"].count("in_overlay") > 0) {
            inOverlayString = settingsData["ultrahand"]["in_overlay"];
        } else {
            inOverlayString = "false"; // Assign default value if the keys are not present
        }
        
        bool inOverlay = false;
        if (inOverlayString == "true") {
            inOverlay = true;
            setIniFileValue(settingsConfigPath, "ultrahand", "in_overlay", "false");
        }
        
        if (inOverlay && skipCombo) {
            eventFire(&shData.comboEvent);
            overlay->disableNextAnimation();
        }
        // CUSTOM SECTION END
        
        
        while (shData.running) {
            
            eventWait(&shData.comboEvent, UINT64_MAX);
            eventClear(&shData.comboEvent);
            shData.overlayOpen = true;
            
            
            hlp::requestForeground(true);
            
            overlay->show();
            overlay->clearScreen();
            
            
            while (shData.running) {
                overlay->loop();
                
                {
                    std::scoped_lock lock(shData.dataMutex);
                    if (!overlay->fadeAnimationPlaying()) {
                        overlay->handleInput(shData.keysDownPending, shData.keysHeld, shData.touchState.count, shData.touchState.touches[0], shData.joyStickPosLeft, shData.joyStickPosRight);
                    }
                    shData.keysDownPending = 0;
                }
                
                if (overlay->shouldHide())
                    break;
                
                if (overlay->shouldClose())
                    shData.running = false;
                
                if (updateMenuCombos) { // CUSTOM MODIFICATION
                    setIniFileValue(settingsConfigPath, "ultrahand", "key_combo", "L+DDOWN+RS");
                    setIniFileValue(teslaSettingsConfigIniPath, "tesla", "key_combo", "L+DDOWN+RS");
                    updateMenuCombos = false;
                }
            }
            
            overlay->clearScreen();
            overlay->resetFlags();
            
            hlp::requestForeground(false);
            
            shData.overlayOpen = false;
            eventClear(&shData.comboEvent);
        }
        
        eventClose(&shData.comboEvent);
        
        threadWaitForExit(&backgroundThread);
        threadClose(&backgroundThread);
        
        overlay->exitScreen();
        overlay->exitServices();
        
        delete overlay;
        
        return 0;
    }

}


#ifdef TESLA_INIT_IMPL

namespace tsl::cfg {
    
    u16 LayerWidth  = 0;
    u16 LayerHeight = 0;
    u16 LayerPosX   = 0;
    u16 LayerPosY   = 0;
    u16 FramebufferWidth  = 0;
    u16 FramebufferHeight = 0;
    u64 launchCombo = KEY_ZL | KEY_ZR | KEY_DDOWN;
    u64 launchCombo2 = KEY_L | KEY_DDOWN | KEY_RSTICK;
}
extern "C" void __libnx_init_time(void);

extern "C" {
    
    u32 __nx_applet_type = AppletType_None;
    u32 __nx_fs_num_sessions = 1;
    u32  __nx_nv_transfermem_size = 0x40000;
    ViLayerFlags __nx_vi_stray_layer_flags = (ViLayerFlags)0;
    
    /**
     * @brief libtesla service initializing function to override libnx's
     *
     */
    void __appInit(void) {
        tsl::hlp::doWithSmSession([]{
            
            ASSERT_FATAL(fsInitialize());
            ASSERT_FATAL(hidInitialize());                          // Controller inputs and Touch
            if (hosversionAtLeast(16,0,0)) {
                ASSERT_FATAL(plInitialize(PlServiceType_User));     // Font data. Use pl:u for 16.0.0+
            } else {
                ASSERT_FATAL(plInitialize(PlServiceType_System));   // Use pl:s for 15.0.1 and below to prevent qlaunch/overlaydisp session exhaustion
            }
            ASSERT_FATAL(pmdmntInitialize());                       // PID querying
            ASSERT_FATAL(hidsysInitialize());                       // Focus control
            ASSERT_FATAL(setsysInitialize());                       // Settings querying
            
            ASSERT_FATAL(timeInitialize()); // CUSTOM MODIFICATION
            __libnx_init_time();            // CUSTOM MODIFICATION
            timeExit(); // CUSTOM MODIFICATION
            powerInit();
            thermalstatusInit();
        });
    }
    
    /**
     * @brief libtesla service exiting function to override libnx's
     *
     */
    void __appExit(void) {
        thermalstatusExit();
        powerExit(); // CUSTOM MODIFICATION
        fsExit();
        hidExit();
        plExit();
        pmdmntExit();
        hidsysExit();
        setsysExit();
    }

}

#endif
