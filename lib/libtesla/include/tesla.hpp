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

#include <ultra.hpp>

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


//static std::unordered_map<std::string, std::string> hexSumCache;

// Define an atomic bool for interpreter completion
static std::atomic<bool> threadFailure(false);
static std::atomic<bool> runningInterpreter(false);
static std::atomic<bool> shakingProgress(true);

static std::atomic<bool> isHidden(true);

bool progressAnimation = false;

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



bool updateMenuCombos = false;

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
static const std::string UNZIP_SYMBOL = "\u2191"; 
static const std::string COPY_SYMBOL = "\u2192";
static const std::string INPROGRESS_SYMBOL = "\u25CF";
static const std::string STAR_SYMBOL = "\u2605";


//float customRound(float num) {
//    if (num >= 0) {
//        return floor(num + 0.5);
//    } else {
//        return ceil(num - 0.5);
//    }
//}

// English string definitions

const std::string whiteColor = "#FFFFFF";
const std::string blackColor = "#000000";


constexpr float M_PI = 3.14159265358979323846;
constexpr float RAD_TO_DEG = 180.0f / M_PI;

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
static std::string USERGUIDE_OFFSET = "166";
static std::string SETTINGS_MENU = "Settings Menu";
static std::string SCRIPT_OVERLAY = "Script Overlay";
static std::string STAR_FAVORITE = "Star/Favorite";
static std::string APP_SETTINGS = "App Settings";
static std::string ON_MAIN_MENU = "on Main Menu";
static std::string ON_A_COMMAND = "on a command";
static std::string ON_OVERLAY_PACKAGE = "on overlay/package";
static std::string EFFECTS = "Effects";
static std::string PROGRESS_ANIMATION = "Progress Animation";
static std::string EMPTY = "Empty";

static std::string SUNDAY = "Sunday";
static std::string MONDAY = "Monday";
static std::string TUESDAY = "Tuesday";
static std::string WEDNESDAY = "Wednesday";
static std::string THURSDAY = "Thursday";
static std::string FRIDAY = "Friday";
static std::string SATURDAY = "Saturday";

static std::string JANUARY = "January";
static std::string FEBRUARY = "February";
static std::string MARCH = "March";
static std::string APRIL = "April";
static std::string MAY = "May";
static std::string JUNE = "June";
static std::string JULY = "July";
static std::string AUGUST = "August";
static std::string SEPTEMBER = "September";
static std::string OCTOBER = "October";
static std::string NOVEMBER = "November";
static std::string DECEMBER = "December";

static std::string SUN = "Sun";
static std::string MON = "Mon";
static std::string TUE = "Tue";
static std::string WED = "Wed";
static std::string THU = "Thu";
static std::string FRI = "Fri";
static std::string SAT = "Sat";

static std::string JAN = "Jan";
static std::string FEB = "Feb";
static std::string MAR = "Mar";
static std::string APR = "Apr";
static std::string MAY_ABBR = "May";
static std::string JUN = "Jun";
static std::string JUL = "Jul";
static std::string AUG = "Aug";
static std::string SEP = "Sep";
static std::string OCT = "Oct";
static std::string NOV = "Nov";
static std::string DEC = "Dec";

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
    USERGUIDE_OFFSET = "166";
    SETTINGS_MENU = "Settings Menu";
    SCRIPT_OVERLAY = "Script Overlay";
    STAR_FAVORITE = "Star/Favorite";
    APP_SETTINGS = "App Settings";
    ON_MAIN_MENU = "on Main Menu";
    ON_A_COMMAND = "on a command";
    ON_OVERLAY_PACKAGE = "on overlay/package";
    EFFECTS = "Effects";
    PROGRESS_ANIMATION = "Progress Animation";
    EMPTY = "Empty";

    SUNDAY = "Sunday";
    MONDAY = "Monday";
    TUESDAY = "Tuesday";
    WEDNESDAY = "Wednesday";
    THURSDAY = "Thursday";
    FRIDAY = "Friday";
    SATURDAY = "Saturday";
    
    JANUARY = "January";
    FEBRUARY = "February";
    MARCH = "March";
    APRIL = "April";
    MAY = "May";
    JUNE = "June";
    JULY = "July";
    AUGUST = "August";
    SEPTEMBER = "September";
    OCTOBER = "October";
    NOVEMBER = "November";
    DECEMBER = "December";
    
    SUN = "Sun";
    MON = "Mon";
    TUE = "Tue";
    WED = "Wed";
    THU = "Thu";
    FRI = "Fri";
    SAT = "Sat";
    
    JAN = "Jan";
    FEB = "Feb";
    MAR = "Mar";
    APR = "Apr";
    MAY_ABBR = "May";
    JUN = "Jun";
    JUL = "Jul";
    AUG = "Aug";
    SEP = "Sep";
    OCT = "Oct";
    NOV = "Nov";
    DEC = "Dec";
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
    if (!langData)
        return;
    
    std::map<std::string, std::string*> configMap = {
        {"DEFAULT_CHAR_WIDTH", &DEFAULT_CHAR_WIDTH},
        {"UNAVAILABLE_SELECTION", &UNAVAILABLE_SELECTION},
        {"OVERLAYS", &OVERLAYS},
        {"OVERLAY", &OVERLAY},
        {"HIDDEN_OVERLAYS", &HIDDEN_OVERLAYS},
        {"PACKAGES", &PACKAGES},
        {"PACKAGE", &PACKAGE},
        {"HIDDEN_PACKAGES", &HIDDEN_PACKAGES},
        {"HIDDEN", &HIDDEN},
        {"HIDE_PACKAGE", &HIDE_PACKAGE},
        {"HIDE_OVERLAY", &HIDE_OVERLAY},
        {"LAUNCH_ARGUMENTS", &LAUNCH_ARGUMENTS},
        {"COMMANDS", &COMMANDS},
        {"SETTINGS", &SETTINGS},
        {"MAIN_SETTINGS", &MAIN_SETTINGS},
        {"UI_SETTINGS", &UI_SETTINGS},
        {"WIDGET", &WIDGET},
        {"CLOCK", &CLOCK},
        {"BATTERY", &BATTERY},
        {"SOC_TEMPERATURE", &SOC_TEMPERATURE},
        {"PCB_TEMPERATURE", &PCB_TEMPERATURE},
        {"MISCELLANEOUS", &MISCELLANEOUS},
        {"MENU_ITEMS", &MENU_ITEMS},
        {"USER_GUIDE", &USER_GUIDE},
        {"VERSION_LABELS", &VERSION_LABELS},
        {"KEY_COMBO", &KEY_COMBO},
        {"LANGUAGE", &LANGUAGE},
        {"OVERLAY_INFO", &OVERLAY_INFO},
        {"SOFTWARE_UPDATE", &SOFTWARE_UPDATE},
        {"UPDATE_ULTRAHAND", &UPDATE_ULTRAHAND},
        {"UPDATE_LANGUAGES", &UPDATE_LANGUAGES},
        {"THEME", &THEME},
        {"DEFAULT", &DEFAULT},
        {"ROOT_PACKAGE", &ROOT_PACKAGE},
        {"SORT_PRIORITY", &SORT_PRIORITY},
        {"FAILED_TO_OPEN", &FAILED_TO_OPEN},
        {"CLEAN_LABELS", &CLEAN_LABELS},
        {"OVERLAY_LABELS", &OVERLAY_LABELS},
        {"PACKAGE_LABELS", &PACKAGE_LABELS},
        {"ON", &ON},
        {"OFF", &OFF},
        {"PACKAGE_INFO", &PACKAGE_INFO},
        {"TITLE", &TITLE},
        {"VERSION", &VERSION},
        {"CREATOR", &CREATOR},
        {"ABOUT", &ABOUT},
        {"CREDITS", &CREDITS},
        {"OK", &OK},
        {"BACK", &BACK},
        {"REBOOT", &REBOOT},
        {"SHUTDOWN", &SHUTDOWN},
        {"GAP_1", &GAP_1},
        {"GAP_2", &GAP_2},
        {"USERGUIDE_OFFSET", &USERGUIDE_OFFSET},
        {"SETTINGS_MENU", &SETTINGS_MENU},
        {"SCRIPT_OVERLAY", &SCRIPT_OVERLAY},
        {"STAR_FAVORITE", &STAR_FAVORITE},
        {"APP_SETTINGS", &APP_SETTINGS},
        {"ON_MAIN_MENU", &ON_MAIN_MENU},
        {"ON_A_COMMAND", &ON_A_COMMAND},
        {"ON_OVERLAY_PACKAGE", &ON_OVERLAY_PACKAGE},
        {"EFFECTS", &EFFECTS},
        {"PROGRESS_ANIMATION", &PROGRESS_ANIMATION},
        {"EMPTY", &EMPTY},
        {"SUNDAY", &SUNDAY},
        {"MONDAY", &MONDAY},
        {"TUESDAY", &TUESDAY},
        {"WEDNESDAY", &WEDNESDAY},
        {"THURSDAY", &THURSDAY},
        {"FRIDAY", &FRIDAY},
        {"SATURDAY", &SATURDAY},
        {"JANUARY", &JANUARY},
        {"FEBRUARY", &FEBRUARY},
        {"MARCH", &MARCH},
        {"APRIL", &APRIL},
        {"MAY", &MAY},
        {"JUNE", &JUNE},
        {"JULY", &JULY},
        {"AUGUST", &AUGUST},
        {"SEPTEMBER", &SEPTEMBER},
        {"OCTOBER", &OCTOBER},
        {"NOVEMBER", &NOVEMBER},
        {"DECEMBER", &DECEMBER},
        {"SUN", &SUN},
        {"MON", &MON},
        {"TUE", &TUE},
        {"WED", &WED},
        {"THU", &THU},
        {"FRI", &FRI},
        {"SAT", &SAT},
        {"JAN", &JAN},
        {"FEB", &FEB},
        {"MAR", &MAR},
        {"APR", &APR},
        {"MAY_ABBR", &MAY_ABBR},
        {"JUN", &JUN},
        {"JUL", &JUL},
        {"AUG", &AUG},
        {"SEP", &SEP},
        {"OCT", &OCT},
        {"NOV", &NOV},
        {"DEC", &DEC}
    };

    // Iterate over the map to update global variables
    for (auto& kv : configMap) {
        updateIfNotEmpty(*kv.second, kv.first.c_str(), langData);
    }

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
static std::unordered_map<wchar_t, float> characterWidths = {
    {L'°', 0.25},
    {L'%', 0.98}, // not calibrated
    {L':', 0.25}, // not calibrated
    {L' ', 0.3},
    {L'+', 0.75},
    {L'-', 0.36},
    {L'_', 0.47},
    {L'&', 0.74},
    {L'(', 0.36},
    {L')', 0.36},
    {L'[', 0.3635},
    {L']', 0.3635},
    {L'A', 0.78},
    {L'B', 0.644},
    {L'C', 0.76},
    {L'D', 0.8},
    {L'E', 0.6},
    {L'F', 0.6},
    {L'G', 0.8},
    {L'H', 0.72},
    {L'I', 0.26},
    {L'J', 0.48},
    {L'K', 0.68},
    {L'L', 0.46},
    {L'M', 0.98},
    {L'N', 0.82},
    {L'O', 0.92},
    {L'P', 0.6},
    {L'Q', 0.9},
    {L'R', 0.6},
    {L'S', 0.56},
    {L'T', 0.64},
    {L'U', 0.80},
    {L'V', 0.76},
    {L'W', 1.14},
    {L'X', 0.66},
    {L'Y', 0.66},
    {L'Z', 0.74},
    {L'a', 0.6},
    {L'b', 0.66},
    {L'c', 0.56},
    {L'd', 0.66},
    {L'e', 0.6},
    {L'f', 0.28},
    {L'g', 0.6},
    {L'h', 0.6},
    {L'i', 0.25},
    {L'j', 0.36},
    {L'k', 0.56},
    {L'l', 0.28},
    {L'm', 0.94},
    {L'n', 0.582},
    {L'o', 0.656},
    {L'p', 0.66},
    {L'q', 0.68},
    {L'r', 0.36},
    {L's', 0.5},
    {L't', 0.37},
    {L'u', 0.6},
    {L'v', 0.50},
    {L'w', 0.87},
    {L'x', 0.54},
    {L'y', 0.53},
    {L'z', 0.5},
    {L'0', 0.66},
    {L'1', 0.66},
    {L'2', 0.66},
    {L'3', 0.66},
    {L'4', 0.66},
    {L'5', 0.66},
    {L'6', 0.66},
    {L'7', 0.66},
    {L'8', 0.66},
    {L'9', 0.66}
};

static std::unordered_map<wchar_t, float> numericCharacterWidths = {
    {L'0', 0.66},
    {L'1', 0.57},
    {L'2', 0.66},
    {L'3', 0.66},
    {L'4', 0.66},
    {L'5', 0.66},
    {L'6', 0.66},
    {L'7', 0.66},
    {L'8', 0.66},
    {L'9', 0.66}
};

// Predefined hexMap
const std::array<int, 256> hexMap = [] {
    std::array<int, 256> map = {0};
    map['0'] = 0; map['1'] = 1; map['2'] = 2; map['3'] = 3; map['4'] = 4;
    map['5'] = 5; map['6'] = 6; map['7'] = 7; map['8'] = 8; map['9'] = 9;
    map['A'] = 10; map['B'] = 11; map['C'] = 12; map['D'] = 13; map['E'] = 14; map['F'] = 15;
    map['a'] = 10; map['b'] = 11; map['c'] = 12; map['d'] = 13; map['e'] = 14; map['f'] = 15;
    return map;
}();


// Prepare a map of default settings
std::map<std::string, std::string> defaultThemeSettingsMap = {
    {"clock_color", whiteColor},
    {"bg_alpha", "13"},
    {"bg_color", blackColor},
    {"seperator_alpha", "7"},
    {"seperator_color", "#777777"},
    {"battery_color", "#ffff45"},
    {"text_color", whiteColor},
    {"table_bg_color", "#303030"},
    {"table_section_text_color", "#e9ff40"},
    {"table_info_text_color", whiteColor},
    {"version_text_color", "#AAAAAA"},
    {"on_text_color", "#00FFDD"},
    {"off_text_color", "#AAAAAA"},
    {"invalid_text_color", "#FF0000"},
    {"inprogress_text_color", "#FFFF45"},
    {"selection_text_color", whiteColor},
    {"selection_bg_color", blackColor},
    {"trackbar_color", "#555555"},
    {"highlight_color_1", "#2288CC"},
    {"highlight_color_2", "#88FFFF"},
    {"highlight_color_3", "#FFFF45"},
    {"highlight_color_4", "#F7253E"},
    {"click_text_color", whiteColor},
    {"click_alpha", "7"},
    {"click_color", "#F7253E"},
    {"invert_bg_click_color", FALSE_STR},
    {"disable_selection_bg", FALSE_STR},
    {"disable_colorful_logo", FALSE_STR},
    {"logo_color_1", whiteColor},
    {"logo_color_2", "#FF0000"},
    {"dynamic_logo_color_1", "#00E669"},
    {"dynamic_logo_color_2", "#8080EA"}
};

inline bool isNumericCharacter(char c) {
    return std::isdigit(c);
}

inline bool isValidHexColor(const std::string& hexColor) {
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


inline float calculateStringWidth(const std::string& str, int fontSize, bool fixedWidthNumbers = true) {
    
    float totalWidth = 0;
    float letterWidth;
    
    for (char letter : str) {
        // Lookup the width of the current character
        if (!fixedWidthNumbers && isNumericCharacter(letter))
            letterWidth = numericCharacterWidths[letter];
        else
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

inline float calculateCharacterWidth(char character, bool fixedWidthNumbers) {
    if (!fixedWidthNumbers && isNumericCharacter(character)) {
        return numericCharacterWidths[character];
    } else {
        return characterWidths[character];
    }
}


inline float calculateAmplitude(float x, float peakDurationFactor = 0.25f) {
    const float phasePeriod = 360.0f * peakDurationFactor;  // One full phase period

    // Convert x from radians to degrees and calculate phase within the period
    int phase = static_cast<int>(x * RAD_TO_DEG) % static_cast<int>(phasePeriod);

    // Check if the phase is odd using bitwise operation
    if (phase & 1) {
        return 1.0f;  // Flat amplitude (maximum positive)
    } else {
        // Calculate the sinusoidal amplitude for the remaining period
        return (std::cos(x) + 1.0f) / 2.0f;  // Cosine function expects radians
    }
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

constexpr auto min_delay = std::chrono::seconds(3); // Minimum delay between checks

bool powerGetDetails(uint32_t *batteryCharge, bool *isCharging) {
    static auto last_call = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
   

    PsmChargerType charger = PsmChargerType_Unconnected;
    bool hwReadsSucceeded = false;

    *isCharging = false;
    *batteryCharge = 0;

    if (powerInitialized) {
        // Only proceed with new hardware read if sufficient time has elapsed
        if (now - last_call > min_delay || !powerCacheInitialized) {
            Result rc = psmGetBatteryChargePercentage(batteryCharge);
            hwReadsSucceeded = R_SUCCEEDED(rc);

            if (hwReadsSucceeded) {
                rc = psmGetChargerType(&charger);
                hwReadsSucceeded &= R_SUCCEEDED(rc);
                *isCharging = (charger != PsmChargerType_Unconnected);
            }

            if (hwReadsSucceeded) {
                // Update cache
                powerCacheCharge = *batteryCharge;
                powerCacheIsCharging = *isCharging;
                powerCacheInitialized = true;
                last_call = now;  // Update last call time after successful hardware read
            } else if (powerCacheInitialized) {
                // Use cached values if current read fails
                *batteryCharge = powerCacheCharge;
                *isCharging = powerCacheIsCharging;
                hwReadsSucceeded = true; // Report success when falling back to cache
            }
        } else {
            // Use cached values if not enough time has passed
            *batteryCharge = powerCacheCharge;
            *isCharging = powerCacheIsCharging;
            hwReadsSucceeded = true; // Report success when using cache
        }
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
    static std::chrono::steady_clock::time_point last_call;
    auto now = std::chrono::steady_clock::now();

    // Throttle the function to not execute more often than every 3 seconds
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_call) < min_delay) {
        return false;
    }

    last_call = now;

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
    static std::chrono::steady_clock::time_point last_call;
    auto now = std::chrono::steady_clock::now();

    // Throttle the function to not execute more often than every 3 seconds
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_call) < min_delay) {
        return false;
    }

    last_call = now;

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
//static std::string hideClock, hideBattery, hidePCBTemp, hideSOCTemp;
static bool hideClock, hideBattery, hidePCBTemp, hideSOCTemp;

void reinitializeWidgetVars() {
    hideClock = (parseValueFromIniSection(SETTINGS_CONFIG_INI_PATH, ULTRAHAND_PROJECT_NAME, "hide_clock") != FALSE_STR);
    hideBattery = (parseValueFromIniSection(SETTINGS_CONFIG_INI_PATH, ULTRAHAND_PROJECT_NAME, "hide_battery") != FALSE_STR);
    hideSOCTemp = (parseValueFromIniSection(SETTINGS_CONFIG_INI_PATH, ULTRAHAND_PROJECT_NAME, "hide_soc_temp") != FALSE_STR);
    hidePCBTemp = (parseValueFromIniSection(SETTINGS_CONFIG_INI_PATH, ULTRAHAND_PROJECT_NAME, "hide_pcb_temp") != FALSE_STR);
}

static bool cleanVersionLabels, hideOverlayVersions, hidePackageVersions;

static std::string loaderInfo = envGetLoaderInfo();
static std::string versionLabel;

void reinitializeVersionLabels() {
    cleanVersionLabels = (parseValueFromIniSection(SETTINGS_CONFIG_INI_PATH, ULTRAHAND_PROJECT_NAME, "clean_version_labels") != FALSE_STR);
    hideOverlayVersions = (parseValueFromIniSection(SETTINGS_CONFIG_INI_PATH, ULTRAHAND_PROJECT_NAME, "hide_overlay_versions") != FALSE_STR);
    hidePackageVersions = (parseValueFromIniSection(SETTINGS_CONFIG_INI_PATH, ULTRAHAND_PROJECT_NAME, "hide_package_versions") != FALSE_STR);
    versionLabel = std::string(APP_VERSION) + "   (" + extractTitle(loaderInfo) + " " + (cleanVersionLabels ? "" : "v") + cleanVersionLabel(loaderInfo) + ")";
    //versionLabel = (cleanVersionLabels) ? std::string(APP_VERSION) : (std::string(APP_VERSION) + "   (" + extractTitle(loaderInfo) + " v" + cleanVersionLabel(loaderInfo) + ")");
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
#define ELEMENT_BOUNDS_2(elem) elem->getX()+4, elem->getY()+4, elem->getWidth(), elem->getHeight()+10

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


    Color RGB888(const std::string& hexColor, const std::string& defaultHexColor = whiteColor, size_t alpha = 15) {
        std::string validHex = hexColor.empty() || hexColor[0] != '#' ? hexColor : hexColor.substr(1);
        
        if (!isValidHexColor(validHex)) {
            validHex = defaultHexColor;
        }
        
        // Convert hex to RGB values
        uint8_t redValue = (hexMap[static_cast<unsigned char>(validHex[0])] << 4) | hexMap[static_cast<unsigned char>(validHex[1])];
        uint8_t greenValue = (hexMap[static_cast<unsigned char>(validHex[2])] << 4) | hexMap[static_cast<unsigned char>(validHex[3])];
        uint8_t blueValue = (hexMap[static_cast<unsigned char>(validHex[4])] << 4) | hexMap[static_cast<unsigned char>(validHex[5])];
        
        return Color(redValue >> 4, greenValue >> 4, blueValue >> 4, alpha);
    }


    std::tuple<float, float, float> hexToRGB444Floats(const std::string& hexColor, const std::string& defaultHexColor = "#FFFFFF") {
        const char* validHex = hexColor.c_str();
        if (validHex[0] == '#') validHex++;
    
        if (!isValidHexColor(validHex)) {
            validHex = defaultHexColor.c_str();
            if (validHex[0] == '#') validHex++;
        }
    
        // Manually parse the hex string to an integer value
        unsigned int hexValue = (hexMap[static_cast<unsigned char>(validHex[0])] << 20) |
                                (hexMap[static_cast<unsigned char>(validHex[1])] << 16) |
                                (hexMap[static_cast<unsigned char>(validHex[2])] << 12) |
                                (hexMap[static_cast<unsigned char>(validHex[3])] << 8)  |
                                (hexMap[static_cast<unsigned char>(validHex[4])] << 4)  |
                                hexMap[static_cast<unsigned char>(validHex[5])];
    
        // Extract and scale the RGB components from 8-bit (0-255) to 4-bit float scale (0-15)
        float red = ((hexValue >> 16) & 0xFF) / 255.0f * 15.0f;
        float green = ((hexValue >> 8) & 0xFF) / 255.0f * 15.0f;
        float blue = (hexValue & 0xFF) / 255.0f * 15.0f;
    
        return std::make_tuple(red, green, blue);
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


    // Theme color variable definitions
    static bool disableColorfulLogo = false;
    static Color logoColor1 = RGB888(whiteColor);
    static Color logoColor2 = RGB888("#F7253E");
    static size_t defaultBackgroundAlpha = 13;
    
    static Color defaultBackgroundColor = RGB888(blackColor, blackColor, defaultBackgroundAlpha);
    static Color defaultTextColor = RGB888(whiteColor);
    static Color clockColor = RGB888(whiteColor);
    static Color batteryColor = RGB888("#ffff45");
    static Color versionTextColor = RGB888("#AAAAAA");
    static Color onTextColor = RGB888("#00FFDD");
    static Color offTextColor = RGB888("#AAAAAA");
    
    static std::tuple<float,float,float> dynamicLogoRGB1 = hexToRGB444Floats("#00E669");
    static std::tuple<float,float,float> dynamicLogoRGB2 = hexToRGB444Floats("#8080EA");

    static bool disableSelectionBG = false;
    static bool invertBGClickColor = false;
    static Color selectionBGColor = RGB888(blackColor);
    static Color highlightColor1 = RGB888("#2288CC");
    static Color highlightColor2 = RGB888("#88FFFF");
    static Color highlightColor3 = RGB888("#FFFF45");
    static Color highlightColor4 = RGB888("#F7253E");

    static Color highlightColor = tsl::style::color::ColorHighlight;
    
    static size_t clickAlpha = 7;

    static Color clickColor = RGB888("#F7253E", "#F7253E", clickAlpha);
    static Color trackBarColor = RGB888("#555555");

    static size_t seperatorAlpha = 7;
    
    static Color seperatorColor = RGB888("#777777", "#777777", seperatorAlpha);
    static Color selectedTextColor = RGB888(whiteColor);
    static Color inprogressTextColor = RGB888(whiteColor);
    static Color invalidTextColor = RGB888("#FF0000");
    static Color clickTextColor = RGB888(whiteColor);

    static Color tableBGColor = RGB888("#303030");
    static Color sectionTextColor = RGB888("#e9ff40");
    static Color infoTextColor = RGB888(whiteColor);
    
    void initializeThemeVars() { // NOTE: This needs to be called once in your application.
        // Fetch all theme settings at once from the INI file
        auto themeData = getParsedDataFromIniFile(THEME_CONFIG_INI_PATH);
        if (themeData.count(THEME_STR) > 0) {
            auto& themeSection = themeData[THEME_STR];
    
            // Fetch and process each theme setting using a helper to simplify fetching and fallback
            auto getValue = [&](const std::string& key) {
                return themeSection.count(key) ? themeSection[key] : defaultThemeSettingsMap[key];
            };
    
            // Convert hex color to Color and manage default values and conversion
            auto getColor = [&](const std::string& key, size_t alpha = 15) {
                std::string hexColor = getValue(key);
                return RGB888(hexColor, hexColor, alpha);
            };
    
            auto getAlpha = [&](const std::string& key) {
                std::string alphaStr = getValue(key);
                return !alphaStr.empty() ? std::stoi(alphaStr) : std::stoi(defaultThemeSettingsMap[key]);
            };
    
            disableColorfulLogo = (getValue("disable_colorful_logo") == TRUE_STR);
    
            logoColor1 = getColor("logo_color_1");
            logoColor2 = getColor("logo_color_2");
    
            defaultBackgroundAlpha = getAlpha("bg_alpha");
            defaultBackgroundColor = getColor("bg_color", defaultBackgroundAlpha);
            defaultTextColor = getColor("text_color");
            clockColor = getColor("clock_color");
            batteryColor = getColor("battery_color");
    
            versionTextColor = getColor("version_text_color");
            onTextColor = getColor("on_text_color");
            offTextColor = getColor("off_text_color");
    
            dynamicLogoRGB1 = hexToRGB444Floats(getValue("dynamic_logo_color_1"));
            dynamicLogoRGB2 = hexToRGB444Floats(getValue("dynamic_logo_color_2"));
    
            disableSelectionBG = (getValue("disable_selection_bg") == TRUE_STR);
            invertBGClickColor = (getValue("invert_bg_click_color") == TRUE_STR);
            selectionBGColor = getColor("selection_bg_color");
    
            highlightColor1 = getColor("highlight_color_1");
            highlightColor2 = getColor("highlight_color_2");
            highlightColor3 = getColor("highlight_color_3");
            highlightColor4 = getColor("highlight_color_4");
    
            clickAlpha = getAlpha("click_alpha");
            clickColor = getColor("click_color", clickAlpha);
            trackBarColor = getColor("trackbar_color");
    
            seperatorAlpha = getAlpha("seperator_alpha");
            seperatorColor = getColor("seperator_color", seperatorAlpha);
    
            selectedTextColor = getColor("selection_text_color");
            inprogressTextColor = getColor("inprogress_text_color");
            invalidTextColor = getColor("invalid_text_color");
            clickTextColor = getColor("click_text_color");
    
            tableBGColor = getColor("table_bg_color");
            sectionTextColor = getColor("table_section_text_color");
            infoTextColor = getColor("table_info_text_color");
        }
    }
    


    
    
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
            { HidNpadButton_Left, "DLEFT", "\uE07B" }, { HidNpadButton_Up, "DUP", "\uE079" },
            { HidNpadButton_Right, "DRIGHT", "\uE07C" }, { HidNpadButton_Down, "DDOWN", "\uE07A" },
            { HidNpadButton_A, "A", "\uE0A0" }, { HidNpadButton_B, "B", "\uE0A1" },
            { HidNpadButton_X, "X", "\uE0A2" }, { HidNpadButton_Y, "Y", "\uE0A3" },
            { HidNpadButton_StickL, "LS", "\uE08A" }, { HidNpadButton_StickR, "RS", "\uE08B" },
            { HidNpadButton_Minus, "MINUS", "\uE0B6" }, { HidNpadButton_Plus, "PLUS", "\uE0B5" }
        }};
        
    }
    
    [[maybe_unused]] static void goBack();

    [[maybe_unused]] static void pop();
    
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
            //static const char* ULTRAHAND_CONFIG_FILE = SETTINGS_CONFIG_INI_PATH; // CUSTOM MODIFICATION
            
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
                if ((unsigned)x < cfg::FramebufferWidth && (unsigned)y < cfg::FramebufferHeight) {
                    u32 offset = this->getPixelOffset(x, y);
                    if (offset != UINT32_MAX) {
                        Color* framebuffer = static_cast<Color*>(this->getCurrentFramebuffer());
                        framebuffer[offset] = color;
                    }
                }
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
                // Use fixed-point arithmetic to avoid float division
                return (dst * alpha + src * (0x0F - alpha)) >> 4;
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
            
                u16* framebuffer = static_cast<u16*>(this->getCurrentFramebuffer());
                Color src(framebuffer[offset]);
            
                Color end(0);
                end.r = blendColor(src.r, color.r, color.a);
                end.g = blendColor(src.g, color.g, color.a);
                end.b = blendColor(src.b, color.b, color.a);
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
            
                u16* framebuffer = static_cast<u16*>(this->getCurrentFramebuffer());
                Color src(framebuffer[offset]);
            
                Color end(0);
                end.r = blendColor(src.r, color.r, color.a);
                end.g = blendColor(src.g, color.g, color.a);
                end.b = blendColor(src.b, color.b, color.a);
                end.a = std::min(color.a + src.a, 0xF);
            
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
                s32 x_end = static_cast<s32>(x + w);
                s32 y_end = static_cast<s32>(y + h);
                for (s32 x1 = static_cast<s32>(x); x1 < x_end; ++x1) {
                    for (s32 y1 = static_cast<s32>(y); y1 < y_end; ++y1) {
                        this->setPixelBlendDst(x1, y1, color);
                    }
                }
            }
            
            void drawCircle(s32 centerX, s32 centerY, u16 radius, bool filled, Color color) {
                s32 x = radius;
                s32 y = 0;
                s32 radiusError = 0;
                s32 xChange = 1 - (radius << 1);
                s32 yChange = 0;
            
                while (x >= y) {
                    if (filled) {
                        for (s32 i = centerX - x; i <= centerX + x; i++) {
                            this->setPixelBlendDst(i, centerY + y, color);
                            this->setPixelBlendDst(i, centerY - y, color);
                        }
            
                        for (s32 i = centerX - y; i <= centerX + y; i++) {
                            this->setPixelBlendDst(i, centerY + x, color);
                            this->setPixelBlendDst(i, centerY - x, color);
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
                    }
            
                    y++;
                    radiusError += yChange;
                    yChange += 2;
            
                    if (((radiusError << 1) + xChange) > 0) {
                        x--;
                        radiusError += xChange;
                        xChange += 2;
                    }
                }
            }

            /**
             * @brief Draws a rounded rectangle of given sizes and corner radius
             *
             * @param x X pos
             * @param y Y pos
             * @param w Width
             * @param h Height
             * @param radius Corner radius
             * @param color Color
             */
            inline void drawRoundedRect(float x, float y, float w, float h, float radius, Color color) {
                s32 x_start = static_cast<s32>(x + radius);
                s32 x_end = static_cast<s32>(x + w - radius);
                s32 y_start = static_cast<s32>(y + radius);
                s32 y_end = static_cast<s32>(y + h - radius);
                
                // Draw the central rectangle excluding the corners
                for (s32 y1 = y_start; y1 < y_end; ++y1) {
                    for (s32 x1 = x_start; x1 < x_end; ++x1) {
                        this->setPixelBlendDst(x1, y1, color);
                    }
                }
            
                // Draw the top and bottom rectangles excluding the corners
                for (s32 y1 = static_cast<s32>(y); y1 < y_start; ++y1) {
                    for (s32 x1 = x_start; x1 < x_end; ++x1) {
                        this->setPixelBlendDst(x1, y1, color);
                    }
                }
                for (s32 y1 = y_end; y1 < static_cast<s32>(y + h); ++y1) {
                    for (s32 x1 = x_start; x1 < x_end; ++x1) {
                        this->setPixelBlendDst(x1, y1, color);
                    }
                }
            
                // Draw the left and right rectangles excluding the corners
                for (s32 y1 = y_start; y1 < y_end; ++y1) {
                    for (s32 x1 = static_cast<s32>(x); x1 < x_start; ++x1) {
                        this->setPixelBlendDst(x1, y1, color);
                    }
                    for (s32 x1 = x_end; x1 < static_cast<s32>(x + w); ++x1) {
                        this->setPixelBlendDst(x1, y1, color);
                    }
                }
                
                // Draw the rounded corners
                s32 cornerX, cornerY ;
                s32 radiusSquared = radius * radius;
                for (s32 x1 = 0; x1 < radius; ++x1) {
                    for (s32 y1 = 0; y1 < radius; ++y1) {
                        if ((x1 * x1 + y1 * y1) <= radiusSquared) {
                            cornerX = static_cast<s32>(x + radius - x1);
                            cornerY = static_cast<s32>(y + radius - y1);
                            this->setPixelBlendDst(cornerX, cornerY, color);  // Top-left corner
                            this->setPixelBlendDst(static_cast<s32>(x + w - radius + x1), cornerY, color);  // Top-right corner
                            this->setPixelBlendDst(cornerX, static_cast<s32>(y + h - radius + y1), color);  // Bottom-left corner
                            this->setPixelBlendDst(static_cast<s32>(x + w - radius + x1), static_cast<s32>(y + h - radius + y1), color);  // Bottom-right corner
                        }
                    }
                }
            }

            
            //inline void drawRoundedRectBorder(float x, float y, float w, float h, float radius, float thickness, Color color) {
            //    // Draw the top horizontal border
            //    for (s32 t = 0; t < thickness; ++t) {
            //        for (s32 i = radius; i < w - radius; ++i) {
            //            this->setPixelBlendDst(x + i, y + t, color);                // Top border
            //            this->setPixelBlendDst(x + i, y + h - 1 - t, color); // Bottom border
            //        }
            //    }
            //
            //    // Draw the bottom horizontal border
            //    for (s32 t = 0; t < thickness; ++t) {
            //        for (s32 i = radius; i < w - radius; ++i) {
            //            this->setPixelBlendDst(x + i, y + h - thickness + t, color); // Corrected Bottom border
            //        }
            //    }
            //
            //    // Draw the left vertical border
            //    for (s32 t = 0; t < thickness; ++t) {
            //        for (s32 i = radius; i < h - radius; ++i) {
            //            this->setPixelBlendDst(x + t, y + i, color);                // Left border
            //            this->setPixelBlendDst(x + w - 1 - t, y + i, color); // Right border
            //        }
            //    }
            //
            //    // Draw the right vertical border
            //    for (s32 t = 0; t < thickness; ++t) {
            //        for (s32 i = radius; i < h - radius; ++i) {
            //            this->setPixelBlendDst(x + w - 1 - t, y + i, color); // Right border
            //        }
            //    }
            //
            //    // Draw the rounded corners
            //    for (s32 t = 0; t < thickness; ++t) {
            //        for (s32 i = 0; i < radius; ++i) {
            //            for (s32 j = 0; j < radius; ++j) {
            //                if ((i * i + j * j) <= (radius * radius)) {
            //                    // Top-left corner
            //                    this->setPixelBlendDst(x + radius - i, y + radius - j - t, color);
            //                    this->setPixelBlendDst(x + radius - i - t, y + radius - j, color);
            //                    
            //                    // Top-right corner
            //                    this->setPixelBlendDst(x + w - radius + i, y + radius - j - t, color);
            //                    this->setPixelBlendDst(x + w - radius + i + t, y + radius - j, color);
            //
            //                    // Bottom-left corner
            //                    this->setPixelBlendDst(x + radius - i, y + h - radius + j + t, color);
            //                    this->setPixelBlendDst(x + radius - i - t, y + h - radius + j, color);
            //
            //                    // Bottom-right corner
            //                    this->setPixelBlendDst(x + w - radius + i, y + h - radius + j + t, color);
            //                    this->setPixelBlendDst(x + w - radius + i + t, y + h - radius + j, color);
            //                }
            //            }
            //        }
            //    }
            //}

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
                u32 currCharacter;
                ssize_t codepointWidth;
                u64 key;
                Glyph* glyph = nullptr;
                auto it = s_glyphCache.end();
                Color tmpColor = { 0xF, 0xF, 0xF, 0xF };
                uint8_t bmpColor;
            
                float xPos, yPos;
                int yAdvance = 0;
                float scaledFontSize;
            
                while (*string != '\0') {
                    if (maxWidth > 0 && maxWidth < (currX - x))
                        break;
            
                    codepointWidth = decode_utf8(&currCharacter, reinterpret_cast<const u8*>(string));
                    if (codepointWidth <= 0)
                        break;
            
                    string += codepointWidth;
            
                    if (currCharacter == '\n') {
                        maxX = std::max(currX, maxX);
                        currX = x;
                        currY += fontSize;
                        continue;
                    }
            
                    key = (static_cast<u64>(currCharacter) << 32) | (static_cast<u64>(monospace) << 31) | (static_cast<u64>(std::bit_cast<u32>(fontSize)));
                    it = s_glyphCache.find(key);
                    if (it == s_glyphCache.end()) {
                        /* Cache glyph */
                        glyph = &s_glyphCache.emplace(key, Glyph()).first->second;
            
                        if (stbtt_FindGlyphIndex(&this->m_extFont, currCharacter))
                            glyph->currFont = &this->m_extFont;
                        else if (this->m_hasLocalFont && stbtt_FindGlyphIndex(&this->m_stdFont, currCharacter) == 0)
                            glyph->currFont = &this->m_localFont;
                        else
                            glyph->currFont = &this->m_stdFont;
            
                        scaledFontSize = stbtt_ScaleForPixelHeight(glyph->currFont, fontSize);
                        glyph->currFontSize = scaledFontSize;
            
                        stbtt_GetCodepointBitmapBoxSubpixel(glyph->currFont, currCharacter, scaledFontSize, scaledFontSize,
                            0, 0, &glyph->bounds[0], &glyph->bounds[1], &glyph->bounds[2], &glyph->bounds[3]);
            
                        yAdvance = 0;
                        stbtt_GetCodepointHMetrics(glyph->currFont, monospace ? 'W' : currCharacter, &glyph->xAdvance, &yAdvance);
            
                        glyph->glyphBmp = stbtt_GetCodepointBitmap(glyph->currFont, scaledFontSize, scaledFontSize, currCharacter, &glyph->width, &glyph->height, nullptr, nullptr);
                    } else {
                        /* Use cached glyph */
                        glyph = &it->second;
                    }
            
                    if (glyph->glyphBmp != nullptr && !std::iswspace(currCharacter) && fontSize > 0 && color.a != 0x0) {
                        xPos = currX + glyph->bounds[0];
                        yPos = currY + glyph->bounds[1];
            
                        for (s32 bmpY = 0; bmpY < glyph->height; ++bmpY) {
                            for (s32 bmpX = 0; bmpX < glyph->width; ++bmpX) {
                                bmpColor = glyph->glyphBmp[glyph->width * bmpY + bmpX] >> 4;
                                if (bmpColor == 0xF) {
                                    this->setPixel(xPos + bmpX, yPos + bmpY, color);
                                } else if (bmpColor != 0x0) {
                                    tmpColor = color;
                                    tmpColor.a = static_cast<uint8_t>(bmpColor * (tmpColor.a / 0xF));
                                    this->setPixelBlendDst(xPos + bmpX, yPos + bmpY, tmpColor);
                                }
                            }
                        }
                    }
            
                    currX += static_cast<s32>(glyph->xAdvance * glyph->currFontSize);
                }
            
                maxX = std::max(currX, maxX);
                return { static_cast<u32>(maxX - x), static_cast<u32>(currY - y) };
            }
            
            
            
            /**
             * @brief Limit a strings length and end it with "…"
             *
             * @param string String to truncate
             * @param maxLength Maximum length of string
             */
            std::string limitStringLength(const std::string& string, bool monospace, float fontSize, s32 maxLength) {
                if (string.size() < 2) {
                    return string;
                }
            
                float currX = 0.0f;
                size_t strPos = 0;
                ssize_t codepointWidth = 0;
                u32 currCharacter = 0;
                float charWidth;

                // Iterate through the string and calculate the width incrementally
                while (strPos < string.size() && currX < maxLength) {
                    codepointWidth = decode_utf8(&currCharacter, reinterpret_cast<const u8*>(&string[strPos]));
                    if (codepointWidth <= 0) {
                        break;
                    }
            
                    // Calculate the width of the current character
                    charWidth = calculateCharacterWidth(static_cast<char>(currCharacter), monospace) * fontSize;
                    currX += charWidth;
            
                    if (currX >= maxLength) {
                        // If the length exceeds maxLength, truncate the string and add ellipsis
                        return string.substr(0, strPos) + "…";
                    }
            
                    strPos += codepointWidth;
                }
            
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
                // Check for scissoring boundaries
                if (!this->m_scissoringStack.empty()) {
                    const auto& currScissorConfig = this->m_scissoringStack.top();
                    if (x < currScissorConfig.x || y < currScissorConfig.y || 
                        x >= currScissorConfig.x + currScissorConfig.w || 
                        y >= currScissorConfig.y + currScissorConfig.h) {
                        return UINT32_MAX;
                    }
                }
            
                // Calculate the base offset
                tmpPos = ((y & 127) / 16) + (x / 32 * 8) + 
                         ((y / 128) * ((cfg::FramebufferWidth / 2) / 16 * 8));
                tmpPos *= 1024; // 16 * 16 * 4 = 1024
            
                // Calculate the fine offset and add it to the base offset
                tmpPos += ((y % 16) / 8) * 512 + 
                          ((x % 32) / 16) * 256 + 
                          ((y % 8) / 2) * 64 + 
                          ((x % 16) / 8) * 32 + 
                          (y % 2) * 16 + 
                          (x % 8) * 2;
            
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
            
            
            std::chrono::duration<long int, std::ratio<1, 1000000000>> t;
            //double timeCounter;
            u8 saturation;
            //Color animColor = tsl::style::color::ColorClickAnimation;
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
                
                //if (!disableSelectionBG) {
                //    saturation = tsl::style::ListItemHighlightSaturation * (float(this->m_clickAnimationProgress) / float(tsl::style::ListItemHighlightLength));
                //    if (invertBGClickColor) {
                //        animColor.r = 15-saturation;
                //        animColor.g = 15-saturation;
                //        animColor.b = 15;
                //    } else {
                //        animColor.r = 0;
                //        animColor.g = saturation;
                //        animColor.b = saturation;
                //    }
                //    renderer->drawRect(ELEMENT_BOUNDS(this), a(animColor));
                //} else {
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
                
                
                renderer->drawRect(this->getX() + x + 2, this->getY() + y - 4, this->getWidth() - 5 +2 +4, 5, a(highlightColor));
                renderer->drawRect(this->getX() + x + 2, this->getY() + y + this->getHeight(), this->getWidth() - 5 +2 +4, 5, a(highlightColor));
                renderer->drawRect(this->getX() + x -2, this->getY() + y + 2 - 2, 5, this->getHeight()-3 +4, a(highlightColor));
                renderer->drawRect(this->getX() + x + this->getWidth()+2, this->getY() + y + 2 -2, 5, this->getHeight()-3 +4, a(highlightColor));
                
                renderer->drawCircle(this->getX() + x, this->getY() + y + this->getHeight() + 2, 2.5, true, a(highlightColor));
                renderer->drawCircle(this->getX() + x, this->getY() + y - 2, 2.5, true, a(highlightColor));
                renderer->drawCircle(this->getX() + x + this->getWidth() +4, this->getY() + y + this->getHeight() + 2, 2.5, true, a(highlightColor));
                renderer->drawCircle(this->getX() + x + this->getWidth() +4, this->getY() + y - 2, 2.5, true, a(highlightColor));
                    
                //}
            }
            
            /**
             * @brief Draws the back background when a element is highlighted
             * @note Override this if you have a element that e.g requires a non-rectangular focus
             *
             * @param renderer Renderer
             */
            virtual void drawFocusBackground(gfx::Renderer *renderer) {
                if (!disableSelectionBG)
                    renderer->drawRect(ELEMENT_BOUNDS(this), a(selectionBGColor)); // CUSTOM MODIFICATION 
                
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
                if (runningInterpreter.load(std::memory_order_acquire)) {
                    highlightColor = {
                        static_cast<u8>((highlightColor3.r - highlightColor4.r) * progress + highlightColor4.r),
                        static_cast<u8>((highlightColor3.g - highlightColor4.g) * progress + highlightColor4.g),
                        static_cast<u8>((highlightColor3.b - highlightColor4.b) * progress + highlightColor4.b),
                        0xF
                    };
                } else {
                    highlightColor = {
                        static_cast<u8>((highlightColor1.r - highlightColor2.r) * progress + highlightColor2.r),
                        static_cast<u8>((highlightColor1.g - highlightColor2.g) * progress + highlightColor2.g),
                        static_cast<u8>((highlightColor1.b - highlightColor2.b) * progress + highlightColor2.b),
                        0xF
                    };
                }
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
                //if ((disableSelectionBG && this->m_clickAnimationProgress == 0) || !disableSelectionBG) {
                if (this->m_clickAnimationProgress == 0) {
                    //renderer->drawRoundedRectBorder(ELEMENT_BOUNDS(this), 4, 4, a(highlightColor));
                    //renderer->drawRoundedRectBorder(this->getX() + x + 2, this->getY() + y - 4, this->getWidth() - 5 + 2 + 4, this->getHeight() + 5, 0, 4, a(highlightColor));

                    renderer->drawRect(this->getX() + x + 2, this->getY() + y - 4, this->getWidth() - 5 +2 +4, 5, a(highlightColor));
                    renderer->drawRect(this->getX() + x + 2, this->getY() + y + this->getHeight(), this->getWidth() - 5 +2 +4, 5, a(highlightColor));
                    renderer->drawRect(this->getX() + x -2, this->getY() + y + 2 - 2, 5, this->getHeight()-3 +4, a(highlightColor));
                    renderer->drawRect(this->getX() + x + this->getWidth()+2, this->getY() + y + 2 -2, 5, this->getHeight()-3 +4, a(highlightColor));
                    
                    renderer->drawCircle(this->getX() + x, this->getY() + y + this->getHeight() + 2, 2.5, true, a(highlightColor));
                    renderer->drawCircle(this->getX() + x, this->getY() + y - 2, 2.5, true, a(highlightColor));
                    renderer->drawCircle(this->getX() + x + this->getWidth() + 4, this->getY() + y + this->getHeight() + 2, 2.5, true, a(highlightColor));
                    renderer->drawCircle(this->getX() + x + this->getWidth() + 4, this->getY() + y - 2, 2.5, true, a(highlightColor));
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
                renderer->enableScissoring(ELEMENT_BOUNDS(this));
                this->m_renderFunc(renderer, ELEMENT_BOUNDS(this));
                renderer->disableScissoring();
            }
            
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                
            }
            
        private:
            std::function<void(gfx::Renderer*, s32 x, s32 y, s32 w, s32 h)> m_renderFunc;
        };


        /**
         * @brief A Element that exposes the renderer directly to draw custom views easily
         */
        class TableDrawer : public Element {
        public:
            TableDrawer(std::function<void(gfx::Renderer* r, s32 x, s32 y, s32 w, s32 h)> renderFunc, bool _hideTableBackground, size_t _endGap)
                : Element(), m_renderFunc(renderFunc), hideTableBackground(_hideTableBackground), endGap(_endGap) {}
        
            virtual ~TableDrawer() {}

            virtual void draw(gfx::Renderer* renderer) override {

                renderer->enableScissoring(0, 97, tsl::cfg::FramebufferWidth, tsl::cfg::FramebufferHeight - 73 - 97 - 4);
        
                if (!hideTableBackground)
                    renderer->drawRoundedRect(this->getX() + 4, this->getY() + 2,this->getWidth() - 2, this->getHeight() + 18 - endGap, 10.0, a(tableBGColor));
        
                m_renderFunc(renderer, this->getX() + 4, this->getY(), this->getWidth() + 4, this->getHeight());
        
                renderer->disableScissoring();
            }
        
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {}


            virtual bool onClick(u64 keys) {
                return false;
            }
            
            virtual Element* requestFocus(Element *oldFocus, FocusDirection direction) override {
                return nullptr;
            }
        
        private:
            std::function<void(gfx::Renderer*, s32 x, s32 y, s32 w, s32 h)> m_renderFunc;
            bool hideTableBackground = false;
            size_t endGap = 3;
        };


        
        // CUSTOM SECTION START
        
        
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
            std::string m_title;
            std::string m_subtitle;
            std::string m_menuMode; // CUSTOM MODIFICATION
            std::string m_colorSelection; // CUSTOM MODIFICATION
            std::string m_pageLeftName; // CUSTOM MODIFICATION
            std::string m_pageRightName; // CUSTOM MODIFICATION
            
            
            //std::string firstHalf, secondHalf;
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

            // Convert the C-style string to an std::string
            std::string chargeStringSTD;
            std::string PCB_temperatureStringSTD;
            std::string SOC_temperatureStringSTD;
            std::string menuBottomLine;
            char timeStr[20]; // Allocate a buffer to store the time string
            char PCB_temperatureStr[10];
            char SOC_temperatureStr[10];
            
            
    OverlayFrame(const std::string& title, const std::string& subtitle, const std::string& menuMode = "", const std::string& colorSelection = "", const std::string& pageLeftName = "", const std::string& pageRightName = "")
        : Element(), m_title(title), m_subtitle(subtitle), m_menuMode(menuMode), m_colorSelection(colorSelection), m_pageLeftName(pageLeftName), m_pageRightName(pageRightName) {}

            virtual ~OverlayFrame() {
                if (this->m_contentElement != nullptr)
                    delete this->m_contentElement;
            }
            
            // CUSTOM SECTION START
            virtual void draw(gfx::Renderer *renderer) override {
                renderer->fillScreen(a(defaultBackgroundColor));
            
                y = 50;
                offset = 0;
            
                bool isUltrahand = (this->m_title == CAPITAL_ULTRAHAND_PROJECT_NAME && 
                                    this->m_subtitle.find("Ultrahand Package") == std::string::npos && 
                                    this->m_subtitle.find("Ultrahand Script") == std::string::npos);
                if (isUltrahand) {
                    chargeStringSTD.clear();
                    PCB_temperatureStringSTD.clear();
                    SOC_temperatureStringSTD.clear();
            
                    std::string firstHalf = "Ultra";
                    std::string secondHalf = "hand";
                    
                    x = 20;
                    fontSize = 42;
                    offset = 6;
                    
                    countOffset = 0;
                    auto currentTime = std::chrono::system_clock::now();
                    auto currentTimeCount = std::chrono::duration<double>(currentTime.time_since_epoch()).count();
                    
                    if (!disableColorfulLogo) {
                        float progress;
                        for (char letter : firstHalf) {
                            counter = (2 * M_PI * (fmod(currentTimeCount, cycleDuration) + countOffset) / 1.5);
                            progress = std::sin(counter); // -1 to 1
                            
                            highlightColor = {
                                static_cast<u8>((std::get<0>(dynamicLogoRGB2) - std::get<0>(dynamicLogoRGB1)) * (progress + 1.0) / 2.0 + std::get<0>(dynamicLogoRGB1)),
                                static_cast<u8>((std::get<1>(dynamicLogoRGB2) - std::get<1>(dynamicLogoRGB1)) * (progress + 1.0) / 2.0 + std::get<1>(dynamicLogoRGB1)),
                                static_cast<u8>((std::get<2>(dynamicLogoRGB2) - std::get<2>(dynamicLogoRGB1)) * (progress + 1.0) / 2.0 + std::get<2>(dynamicLogoRGB1)),
                                15
                            };
                            
                            renderer->drawString(std::string(1, letter).c_str(), false, x, y + offset, fontSize, a(highlightColor));
                            x += calculateStringWidth(std::string(1, letter), fontSize);
                            countOffset -= 0.2F;
                        }
                    } else {
                        for (char letter : firstHalf) {
                            renderer->drawString(std::string(1, letter).c_str(), false, x, y + offset, fontSize, a(logoColor1));
                            x += calculateStringWidth(std::string(1, letter), fontSize);
                            countOffset -= 0.2F;
                        }
                    }
                    
                    renderer->drawString(secondHalf.c_str(), false, x, y + offset, fontSize, a(logoColor2));
            
                    if (!(hideBattery && hidePCBTemp && hideSOCTemp && hideClock)) {
                        renderer->drawRect(252, 23, 1, 49, a(seperatorColor));
                    }
            
                    struct timespec currentTimeSpec;
                    clock_gettime(CLOCK_REALTIME, &currentTimeSpec);
            
                    y_offset = 45;
                    if ((hideBattery && hidePCBTemp && hideSOCTemp) || hideClock) {
                        y_offset += 10;
                    }
            
                    if (!hideClock) {
                        strftime(timeStr, sizeof(timeStr), datetimeFormat.c_str(), localtime(&currentTimeSpec.tv_sec));
                        localizeTimeStr(timeStr);
                        renderer->drawString(timeStr, false, tsl::cfg::FramebufferWidth - calculateStringWidth(timeStr, 20) - 20, y_offset, 20, a(clockColor));
                        y_offset += 22;
                    }
            
                    if ((currentTimeSpec.tv_sec - timeOut) >= 1) {
                        if (!isHidden.load()) {
                            if (!hidePCBTemp) thermalstatusGetDetailsPCB(&PCB_temperature);
                            if (!hideSOCTemp) thermalstatusGetDetailsSOC(&SOC_temperature);
                            if (!hideBattery) powerGetDetails(&batteryCharge, &isCharging);
                        }
                        timeOut = int(currentTimeSpec.tv_sec);
                    }
            
                    snprintf(PCB_temperatureStr, sizeof(PCB_temperatureStr) - 1, "%d°C", PCB_temperature);
                    snprintf(SOC_temperatureStr, sizeof(SOC_temperatureStr) - 1, "%d°C", SOC_temperature);
                    batteryCharge = std::min(batteryCharge, 100U);
                    sprintf(chargeString, "%d%%", batteryCharge);
            
                    if (!hideBattery && batteryCharge > 0) {
                        chargeStringSTD = chargeString;
                        Color batteryColorToUse = isCharging ? tsl::Color(0x0, 0xF, 0x0, 0xF) : 
                                                (batteryCharge < 20 ? tsl::Color(0xF, 0x0, 0x0, 0xF) : batteryColor);
                        renderer->drawString(chargeStringSTD.c_str(), false, tsl::cfg::FramebufferWidth - calculateStringWidth(chargeStringSTD, 20) - 19, y_offset, 20, a(batteryColorToUse));
                    }
            
                    offset = 0;
                    if (!hidePCBTemp && PCB_temperature > 0) {
                        PCB_temperatureStringSTD = PCB_temperatureStr;
                        offset += 2;
                        renderer->drawString(PCB_temperatureStringSTD.c_str(), false, tsl::cfg::FramebufferWidth + offset - calculateStringWidth(PCB_temperatureStringSTD, 20) - calculateStringWidth(chargeStringSTD, 20) - 20, y_offset, 20, a(tsl::GradientColor(PCB_temperature)));
                    }
                    if (!hideSOCTemp && SOC_temperature > 0) {
                        SOC_temperatureStringSTD = SOC_temperatureStr;
                        offset += 2;
                        renderer->drawString(SOC_temperatureStringSTD.c_str(), false, tsl::cfg::FramebufferWidth + offset - calculateStringWidth(SOC_temperatureStringSTD, 20) - calculateStringWidth(PCB_temperatureStringSTD, 20) - calculateStringWidth(chargeStringSTD, 20) - 20, y_offset, 20, a(tsl::GradientColor(SOC_temperature)));
                    }
                } else {

                    x = 20;
                    y = 50;
                    fontSize = 32;
                    if (this->m_subtitle.find("Ultrahand Package") != std::string::npos) {
                        const std::string& title = this->m_title;
                        titleColor = Color(0x0, 0xF, 0x0, 0xF); // Default to green
                    
                        // Function to draw the title
                        auto drawTitle = [&](const Color& color) {
                            renderer->drawString(title.c_str(), false, x, y, fontSize, a(color));
                        };
                    
                        if (this->m_colorSelection == "" || this->m_colorSelection == "green") {
                            titleColor = Color(0x0, 0xF, 0x0, 0xF);
                            drawTitle(titleColor);
                        } else if (this->m_colorSelection == "red") {
                            titleColor = RGB888("#F7253E");
                            drawTitle(titleColor);
                        } else if (this->m_colorSelection == "blue") {
                            titleColor = Color(0x7, 0x7, 0xF, 0xF);
                            drawTitle(titleColor);
                        } else if (this->m_colorSelection == "yellow") {
                            titleColor = Color(0xF, 0xF, 0x0, 0xF);
                            drawTitle(titleColor);
                        } else if (this->m_colorSelection == "orange") {
                            titleColor = Color(0xFF, 0xA5, 0x00, 0xFF);
                            drawTitle(titleColor);
                        } else if (this->m_colorSelection == "pink") {
                            titleColor = Color(0xFF, 0x69, 0xB4, 0xFF);
                            drawTitle(titleColor);
                        } else if (this->m_colorSelection == "purple") {
                            titleColor = Color(0x80, 0x00, 0x80, 0xFF);
                            drawTitle(titleColor);
                        } else if (this->m_colorSelection == "white") {
                            titleColor = Color(0xF, 0xF, 0xF, 0xF);
                            drawTitle(titleColor);
                        } else if (this->m_colorSelection == "ultra") {
                            for (char letter : title) {
                                // Calculate the progress for each letter based on the counter
                                progress = calculateAmplitude(counter - x * 0.0001F);
                    
                                // Calculate the corresponding highlight color for each letter
                                highlightColor = {
                                    static_cast<u8>((0xA - 0xF) * (3 - 1.5 * progress) + 0xF),
                                    static_cast<u8>((0xA - 0xF) * 1.5 * progress + 0xF),
                                    static_cast<u8>((0xA - 0xF) * (1.25 - progress) + 0xF),
                                    0xF
                                };
                    
                                // Draw each character with its corresponding highlight color
                                renderer->drawString(std::string(1, letter).c_str(), false, x, y, fontSize, a(highlightColor));
                    
                                // Manually calculate the width of the current letter
                                letterWidth = calculateStringWidth(std::string(1, letter), fontSize);
                    
                                // Adjust the x-coordinate for the next character's position
                                x += letterWidth;
                    
                                // Update the counter for the next character
                                counter -= 0.00004F;
                            }
                        } else if (this->m_colorSelection.size() == 7 && this->m_colorSelection[0] == '#') {
                            // Check if m_colorSelection is a valid hexadecimal color
                            if (isValidHexColor(this->m_colorSelection.substr(1))) {
                                titleColor = RGB888(this->m_colorSelection.substr(1));
                                drawTitle(titleColor);
                            } else {
                                // Invalid hexadecimal color, handle the error accordingly
                                drawTitle(titleColor); // Using the default titleColor
                            }
                        } else { // for unknown colors
                            drawTitle(titleColor); // Using the default titleColor
                        }
                    } else if (this->m_subtitle.find("Ultrahand Script") != std::string::npos) {
                        renderer->drawString(this->m_title.c_str(), false, 20, 50, 32, a(Color(0xFF, 0x33, 0x3F, 0xFF)));
                    } else {
                        renderer->drawString(this->m_title.c_str(), false, 20, 50, 30, a(defaultTextColor));
                    }

                }
                
                
                if (this->m_title == CAPITAL_ULTRAHAND_PROJECT_NAME) {
                    renderer->drawString(versionLabel.c_str(), false, 20, y+25, 15, a(versionTextColor));
                } else
                    renderer->drawString(this->m_subtitle.c_str(), false, 20, y+20, 15, a(versionTextColor));
                
                renderer->drawRect(15, tsl::cfg::FramebufferHeight - 73, tsl::cfg::FramebufferWidth - 30, 1, a(defaultTextColor));
                
                menuBottomLine = "\uE0E1"+GAP_2+BACK+GAP_1+"\uE0E0"+GAP_2+OK+GAP_1;
                if (this->m_menuMode == "packages") {
                    menuBottomLine += "\uE0ED"+GAP_2+OVERLAYS;
                } else if (this->m_menuMode == "overlays") {
                    menuBottomLine += "\uE0EE"+GAP_2+PACKAGES;
                }
                
                if (!(this->m_pageLeftName).empty()) {
                    menuBottomLine += "\uE0ED"+GAP_2 + this->m_pageLeftName;
                } else if (!(this->m_pageRightName).empty()) {
                    menuBottomLine += "\uE0EE"+GAP_2 + this->m_pageRightName;
                }
                
                renderer->drawString(menuBottomLine.c_str(), false, 30, 693, 23, a(defaultTextColor));
                
                if (this->m_contentElement != nullptr)
                    this->m_contentElement->frame(renderer);
            }
            // CUSTOM SECTION END
            
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                this->setBoundaries(parentX, parentY, parentWidth, parentHeight);
                
                if (this->m_contentElement != nullptr) {
                    this->m_contentElement->setBoundaries(parentX + 35, parentY + 97, parentWidth - 85, parentHeight - 73 - 105); // CUSTOM MODIFICATION (125->105->102)
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
            
            //std::string m_title, m_subtitle;
        };
        
        /**
         * @brief The base frame which can contain another view with a customizable header
         *
         */
        class HeaderOverlayFrame : public Element {
        public:
            
            HeaderOverlayFrame(u16 headerHeight = 175) : Element(), m_headerHeight(headerHeight) {}
            virtual ~HeaderOverlayFrame() {
                if (this->m_contentElement != nullptr)
                    delete this->m_contentElement;
                
                if (this->m_header != nullptr)
                    delete this->m_header;
            }
            
            virtual void draw(gfx::Renderer *renderer) override {
                renderer->fillScreen(a(defaultBackgroundColor));
                //renderer->fillScreen(tsl::style::color::ColorFrameBackground);
                renderer->drawRect(tsl::cfg::FramebufferWidth - 1, 0, 1, tsl::cfg::FramebufferHeight, a(0xF222));
                
                renderer->drawRect(15, tsl::cfg::FramebufferHeight - 73, tsl::cfg::FramebufferWidth - 30, 1, a(defaultTextColor));
                
                renderer->drawString(("\uE0E1  "+BACK+"     \uE0E0  "+OK).c_str(), false, 30, 693, 23, a(defaultTextColor)); // CUSTOM MODIFICATION
                
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
                renderer->drawRect(ELEMENT_BOUNDS(this), a(this->m_color));
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
            
            float scrollbarHeight;
            float scrollbarOffset;
            int offset;
            float prevOffset;
            s32 y;
            bool handled;
            u16 i;
            
            virtual void draw(gfx::Renderer *renderer) override {
                if (this->m_clearList) {
                    for (auto& item : this->m_items) {
                        delete item;
                    }
                    this->m_items.clear();
                    this->m_offset = 0;
                    this->m_focusedIndex = 0;
                    this->invalidate();
                    this->m_clearList = false;
                }

                if (!this->m_itemsToAdd.empty()) {
                    for (auto [index, element] : this->m_itemsToAdd) {
                        element->invalidate();
                        if (index >= 0 && (this->m_items.size() > static_cast<size_t>(index))) {
                            this->m_items.insert(this->m_items.cbegin() + static_cast<size_t>(index), element);
                        } else {
                            this->m_items.push_back(element);
                        }
                    }
                    this->m_itemsToAdd.clear();
                    this->invalidate();
                    this->updateScrollOffset();
                }

                if (!this->m_itemsToRemove.empty()) {
                    for (auto element : this->m_itemsToRemove) {
                        auto it = std::find(this->m_items.cbegin(), this->m_items.cend(), element);
                        if (it != this->m_items.cend()) {
                            this->m_items.erase(it);
                            if (this->m_focusedIndex >= static_cast<size_t>(it - this->m_items.cbegin())) {
                                this->m_focusedIndex--;
                            }
                            delete element;
                        }
                    }
                    this->m_itemsToRemove.clear();
                    this->invalidate();
                    this->updateScrollOffset();
                }

                renderer->enableScissoring(this->getLeftBound(), this->getTopBound(), this->getWidth(), this->getHeight() + 4);

                for (auto &entry : this->m_items) {
                    if (entry->getBottomBound() > this->getTopBound() && entry->getTopBound() < this->getBottomBound()) {
                        entry->frame(renderer);
                    }
                }

                renderer->disableScissoring();

                if (this->m_listHeight > this->getHeight()) {
                    float viewHeight = static_cast<float>(this->getHeight() - 16);
                    float totalHeight = static_cast<float>(this->m_listHeight + 16);

                    scrollbarHeight = (viewHeight * viewHeight) / totalHeight;
                    if (scrollbarHeight > viewHeight) {
                        scrollbarHeight = viewHeight;
                    }

                    int maxScrollableHeight = totalHeight - viewHeight;
                    if (maxScrollableHeight < 1) maxScrollableHeight = 1;

                    scrollbarOffset = (static_cast<double>(this->m_offset) / maxScrollableHeight) * (viewHeight - scrollbarHeight);
                    if (scrollbarOffset + scrollbarHeight > viewHeight) {
                        scrollbarOffset = viewHeight - scrollbarHeight;
                    }
                    scrollbarOffset += 8;

                    int offset = 11;
                    renderer->drawRect(this->getRightBound() + 10 + offset, this->getY() + scrollbarOffset, 5, scrollbarHeight, a(trackBarColor));
                    renderer->drawCircle(this->getRightBound() + 12 + offset, this->getY() + scrollbarOffset, 2, true, a(trackBarColor));
                    renderer->drawCircle(this->getRightBound() + 12 + offset, this->getY() + scrollbarOffset + scrollbarHeight, 2, true, a(trackBarColor));

                    float prevOffset = this->m_offset;

                    if (Element::getInputMode() == InputMode::Controller) {
                        this->m_offset += ((this->m_nextOffset) - this->m_offset) * 0.1F;
                    } else if (Element::getInputMode() == InputMode::TouchScroll) {
                        this->m_offset += ((this->m_nextOffset) - this->m_offset);
                    }

                    if (static_cast<u32>(prevOffset) != static_cast<u32>(this->m_offset)) {
                        this->invalidate();
                    }
                }
            }
            
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                y = this->getY() - this->m_offset;
                
                this->m_listHeight = 0;
                for (auto &entry : this->m_items)
                    this->m_listHeight += entry->getHeight();
                
                this->m_listHeight -= 32;
                for (auto &entry : this->m_items) {
                    entry->setBoundaries(this->getX(), y, this->getWidth(), entry->getHeight());
                    entry->invalidate();
                    y += entry->getHeight();
                }
                y -= 32;
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
            void clearItems() {
                for (auto& item : this->m_items) {
                    delete item;
                }
                this->m_items.clear();
                this->m_offset = 0;
                this->m_focusedIndex = 0;
                this->invalidate();
                this->m_clearList = false;
            }
            
            void addPendingItems() {
                for (auto [index, element] : this->m_itemsToAdd) {
                    element->invalidate();
                    if (index >= 0 && (this->m_items.size() > static_cast<size_t>(index))) {
                        this->m_items.insert(this->m_items.cbegin() + static_cast<size_t>(index), element);
                    } else {
                        this->m_items.push_back(element);
                    }
                }
                this->m_itemsToAdd.clear();
                this->invalidate();
                this->updateScrollOffset();
            }
            
            void removePendingItems() {
                for (auto element : this->m_itemsToRemove) {
                    auto it = std::find(this->m_items.cbegin(), this->m_items.cend(), element);
                    if (it != this->m_items.cend()) {
                        this->m_items.erase(it);
                        if (this->m_focusedIndex >= static_cast<size_t>(it - this->m_items.cbegin())) {
                            this->m_focusedIndex--;
                        }
                        delete element;
                    }
                }
                this->m_itemsToRemove.clear();
                this->invalidate();
                this->updateScrollOffset();
            }
            
            void drawScrollbar(gfx::Renderer *renderer) {
                float viewHeight = static_cast<float>(this->getHeight() - 16);
                float totalHeight = static_cast<float>(this->m_listHeight + 16);
            
                scrollbarHeight = (viewHeight * viewHeight) / totalHeight;
                if (scrollbarHeight > viewHeight) {
                    scrollbarHeight = viewHeight;
                }
            
                int maxScrollableHeight = totalHeight - viewHeight;
                if (maxScrollableHeight < 1) maxScrollableHeight = 1;
            
                scrollbarOffset = (static_cast<double>(this->m_offset) / maxScrollableHeight) * (viewHeight - scrollbarHeight);
                if (scrollbarOffset + scrollbarHeight > viewHeight) {
                    scrollbarOffset = viewHeight - scrollbarHeight;
                }
                scrollbarOffset += 8;
            
                int offset = 11;
                renderer->drawRect(this->getRightBound() + 10 + offset, this->getY() + scrollbarOffset, 5, scrollbarHeight, a(trackBarColor));
                renderer->drawCircle(this->getRightBound() + 12 + offset, this->getY() + scrollbarOffset, 2, true, a(trackBarColor));
                //renderer->drawCircle(this->getRightBound() + 12 + offset, (this->getY() + scrollbarOffset + scrollbarHeight) / 2, 2, true, a(trackBarColor));
                renderer->drawCircle(this->getRightBound() + 12 + offset, this->getY() + scrollbarOffset + scrollbarHeight, 2, true, a(trackBarColor));
            
                float prevOffset = this->m_offset;
            
                if (Element::getInputMode() == InputMode::Controller) {
                    this->m_offset += ((this->m_nextOffset) - this->m_offset) * 0.1F;
                } else if (Element::getInputMode() == InputMode::TouchScroll) {
                    this->m_offset += ((this->m_nextOffset) - this->m_offset);
                }
            
                if (static_cast<u32>(prevOffset) != static_cast<u32>(this->m_offset)) {
                    this->invalidate();
                }
            }

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
            //std::chrono::duration<long int, std::ratio<1, 1000000000>> t;
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
                static float lastBottomBound;
                bool useClickTextColor = false;
                if (this->m_touched && Element::getInputMode() == InputMode::Touch) {
                    if (touchInBounds) {
                        renderer->drawRect(ELEMENT_BOUNDS(this), a(clickColor));
                        useClickTextColor = true;
                    }
                    //renderer->drawRect(ELEMENT_BOUNDS(this), tsl::style::color::ColorClickAnimation);
                }
                
                if (this->m_maxWidth == 0) {
                    if (this->m_value.length() > 0) {
                        std::tie(width, height) = renderer->drawString(this->m_value.c_str(), false, 0, 0, 20, a(tsl::style::color::ColorTransparent));
                        this->m_maxWidth = this->getWidth() - width - 70;
                    } else {
                        this->m_maxWidth = this->getWidth() - 40;
                    }
                    
                    std::tie(width, height) = renderer->drawString(this->m_text.c_str(), false, 0, 0, 23, a(tsl::style::color::ColorTransparent));
                    this->m_trunctuated = width > this->m_maxWidth+10;
                    
                    if (this->m_trunctuated) {
                        this->m_scrollText = this->m_text + "        ";
                        std::tie(width, height) = renderer->drawString(this->m_scrollText.c_str(), false, 0, 0, 23, a(tsl::style::color::ColorTransparent));
                        this->m_scrollText += this->m_text;
                        this->m_textWidth = width;
                        if (this->m_value.length() > 0) {
                            this->m_ellipsisText = renderer->limitStringLength(this->m_text, false, 23, this->m_maxWidth+10);
                        } else {
                            this->m_ellipsisText = renderer->limitStringLength(this->m_text, false, 23, this->m_maxWidth+10);
                        }
                    } else {
                        this->m_textWidth = width;
                    }
                }
                
                if (lastBottomBound !=  this->getTopBound())
                    renderer->drawRect(this->getX()+5-2, this->getTopBound(), this->getWidth()-5+10, 1, a(seperatorColor));
                renderer->drawRect(this->getX()+5-2, this->getBottomBound(), this->getWidth()-5+10, 1, a(seperatorColor));
                lastBottomBound = this->getBottomBound();
                
                if (this->m_trunctuated) {
                    if (this->m_focused) {
                        renderer->enableScissoring(this->getX()+7, 97, this->m_maxWidth + 40 - 10+4, tsl::cfg::FramebufferHeight-73-97);
                        renderer->drawString(this->m_scrollText.c_str(), false, this->getX() + 20.0-2 - this->m_scrollOffset, this->getY() + 44.9, 23, a(selectedTextColor));
                        renderer->disableScissoring();
                        //t = std::chrono::system_clock::now() - this->timeIn;
                        if (std::chrono::system_clock::now() - this->timeIn >= 2000ms) {
                            if (this->m_scrollOffset >= this->m_textWidth) {
                                this->m_scrollOffset = 0;
                                this->timeIn = std::chrono::system_clock::now();
                            } else {
                                // Calculate the increment based on the desired scroll rate
                                this->m_scrollOffset = ((0.1) * std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - this->timeIn - 2000ms).count());
                            }
                        } // CUSTOM MODIFICATION END
                    } else {
                        renderer->drawString(this->m_ellipsisText.c_str(), false, this->getX() + 20-2, this->getY() + 45, 23, !useClickTextColor ? defaultTextColor : a(clickTextColor));
                    }
                } else {
                    if (this->m_focused) {
                        renderer->drawString(this->m_text.c_str(), false, this->getX() + 20-2, this->getY() + 45, 23, !useClickTextColor ? selectedTextColor : a(clickTextColor));
                    } else {
                        renderer->drawString(this->m_text.c_str(), false, this->getX() + 20-2, this->getY() + 45, 23, !useClickTextColor ? defaultTextColor : a(clickTextColor));
                    }
                }
                
                
                // CUSTOM SECTION START (modification for submenu footer color)
                if (this->m_value == DROPDOWN_SYMBOL || this->m_value == OPTION_SYMBOL) {
                    if (this->m_focused)
                        renderer->drawString(this->m_value.c_str(), false, this->getX() + this->m_maxWidth + 45 + 10 +2, this->getY() + 45, 20, !useClickTextColor ? (this->m_faint ? offTextColor : selectedTextColor) : a(clickTextColor));
                    else
                        renderer->drawString(this->m_value.c_str(), false, this->getX() + this->m_maxWidth + 45 + 10 +2, this->getY() + 45, 20, !useClickTextColor ? (this->m_faint ? offTextColor : defaultTextColor) : a(clickTextColor));
                } else if (runningInterpreter.load(std::memory_order_acquire) &&
                    ((((this->m_value).find(DOWNLOAD_SYMBOL) != std::string::npos) || ((this->m_value).find(UNZIP_SYMBOL) != std::string::npos) || ((this->m_value).find(COPY_SYMBOL) != std::string::npos)) || this->m_value == INPROGRESS_SYMBOL)) {
                    
                    renderer->drawString(this->m_value.c_str(), false, this->getX() + this->m_maxWidth + 45 + 10 +2, this->getY() + 45, 20, (this->m_faint ? offTextColor : a(inprogressTextColor)));
                } else if (this->m_value == CROSSMARK_SYMBOL) {
                    renderer->drawString(this->m_value.c_str(), false, this->getX() + this->m_maxWidth + 45 + 10 +2, this->getY() + 45, 20, (this->m_faint ? offTextColor : a(invalidTextColor)));
                } else {
                    renderer->drawString(this->m_value.c_str(), false, this->getX() + this->m_maxWidth + 45 + 10 +2, this->getY() + 45, 20, (this->m_faint ? offTextColor : a(onTextColor)));
                }
                // CUSTOM SECTION END 
            }
            
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                this->setBoundaries(this->getX()+2, this->getY(), this->getWidth()-2, tsl::style::ListItemDefaultHeight);
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
            std::chrono::system_clock::time_point timeIn;// = std::chrono::system_clock::now();
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
                if (simulatedSelect && !simulatedSelectComplete) {
                    keys |= KEY_A;
                    simulatedSelect = false;
                }

                if (keys & HidNpadButton_A) {
                    this->m_state = !this->m_state;
                    
                    this->setState(this->m_state);
                    this->m_stateChangedListener(this->m_state);
                    
                    simulatedSelectComplete = true;
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
                
                this->setValue(state ? this->m_onValue : this->m_offValue, !state);
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
            
            
            CategoryHeader(const std::string &title, bool hasSeparator = false) : m_text(title), m_hasSeparator(hasSeparator) {}
            virtual ~CategoryHeader() {}
            
            virtual void draw(gfx::Renderer *renderer) override {
                renderer->drawRect(this->getX() - 2, this->getBottomBound() - 30, 5, 23, a(defaultTextColor));
                renderer->drawString(this->m_text.c_str(), false, this->getX() + 13, this->getBottomBound() - 12, 15, a(defaultTextColor));
                
                //if (this->m_hasSeparator)
                //    renderer->drawRect(this->getX(), this->getBottomBound(), this->getWidth(), 1, tsl::style::color::ColorFrame); // CUSTOM MODIFICATION
            }
            
            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                // Check if the CategoryHeader is part of a list and if it's the first entry in it, half it's height
                if (List *list = static_cast<List*>(this->getParent()); list != nullptr) {
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
                
                renderer->drawString(this->m_icon, false, this->getX() + 15, this->getY() + 50, 23, a(defaultTextColor));
                
                //u16 handlePos = (this->getWidth() - 95) * static_cast<half>(this->m_value) / 100;
                u16 handlePos = (this->getWidth() - 95) * (this->m_value) / 100;
                renderer->drawCircle(this->getX() + 60, this->getY() + 42, 2, true, a(tsl::style::color::ColorHighlight));
                renderer->drawCircle(this->getX() + 60 + this->getWidth() - 95, this->getY() + 42, 2, true, a(tsl::style::color::ColorFrame));
                //renderer->drawRect(this->getX() + 60 + handlePos, this->getY() + 40, this->getWidth() - 95 - handlePos, 5, tsl::style::color::ColorFrame);
                renderer->drawRect(this->getX() + 60, this->getY() + 40, handlePos, 5, a(tsl::style::color::ColorHighlight));
                
                renderer->drawCircle(this->getX() + 62 + handlePos, this->getY() + 42, 18, true, a(trackBarColor));
                renderer->drawCircle(this->getX() + 62 + handlePos, this->getY() + 42, 18, false, a(tsl::style::color::ColorFrame));
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
                    renderer->drawCircle(this->getX() + 62 + x + handlePos, this->getY() + 42 + y, i, false, a(highlightColor));
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
                    renderer->drawRect(this->getX() + 60 + stepWidth * i, this->getY() + 50, 1, 10, a(tsl::style::color::ColorFrame));
                }
                
                currentDescIndex = std::clamp(this->m_value / (100 / (this->m_numSteps - 1)), 0, this->m_numSteps - 1);
                
                std::tie(descWidth, descHeight) = renderer->drawString(this->m_stepDescriptions[currentDescIndex].c_str(), false, 0, 0, 15, a(tsl::style::color::ColorTransparent));
                renderer->drawString(this->m_stepDescriptions[currentDescIndex].c_str(), false, ((this->getX() + 60) + (this->getWidth() - 95) / 2) - (descWidth / 2), this->getY() + 20, 15, a(offTextColor));
                
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

            isHidden.store(false);
            this->onShow();
            
            if (auto& currGui = this->getCurrentGui(); currGui != nullptr) // TESTING DISABLED (EFFECTS NEED TO BE VERIFIED)
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
            isHidden.store(true);
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
        
        bool m_fadeInAnimationPlaying = false, m_fadeOutAnimationPlaying = false;
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
                
                if (this->m_animationCounter >= 5) {
                    this->m_fadeInAnimationPlaying = false;
                }
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
            // Static variables to maintain state between function calls
            static HidTouchState initialTouchPos = { 0 };
            static HidTouchState oldTouchPos = { 0 };
            static bool oldTouchDetected = false;
            static elm::TouchEvent touchEvent;
            static elm::TouchEvent oldTouchEvent;
            static u32 repeatTick = 0;
            static ssize_t counter = 0;
        
            auto& currentGui = this->getCurrentGui();
        
            // Return early if current GUI is not available
            if (!currentGui)
                return;
        
            // Retrieve current focus and top/bottom elements of the GUI
            auto currentFocus = currentGui->getFocusedElement();
            auto topElement = currentGui->getTopElement();
            auto bottomElement = currentGui->getBottomElement();
        
            if (runningInterpreter.load()) {
                if (keysHeld & HidNpadButton_AnyUp && keysDown & HidNpadButton_AnyUp && !(keysHeld & (KEY_DLEFT | KEY_DRIGHT | KEY_DDOWN | KEY_B | KEY_A | KEY_X | KEY_Y | KEY_L | KEY_R | KEY_ZL | KEY_ZR)))
                    currentFocus->shakeHighlight(FocusDirection::Up);
                else if (keysHeld & HidNpadButton_AnyDown && keysDown & HidNpadButton_AnyDown && !(keysHeld & (KEY_DLEFT | KEY_DRIGHT | KEY_DUP | KEY_B | KEY_A | KEY_X | KEY_Y | KEY_L | KEY_R | KEY_ZL | KEY_ZR)))
                    currentFocus->shakeHighlight(FocusDirection::Down);
                else if (keysHeld & HidNpadButton_AnyLeft && keysDown & HidNpadButton_AnyLeft && !(keysHeld & (KEY_DRIGHT | KEY_DUP | KEY_DDOWN | KEY_B | KEY_A | KEY_X | KEY_Y | KEY_L | KEY_R | KEY_ZL | KEY_ZR)))
                    currentFocus->shakeHighlight(FocusDirection::Left);
                else if (keysHeld & HidNpadButton_AnyRight && keysDown & HidNpadButton_AnyRight && !(keysHeld & (KEY_DLEFT | KEY_DUP | KEY_DDOWN | KEY_B | KEY_A | KEY_X | KEY_Y | KEY_L | KEY_R | KEY_ZL | KEY_ZR)))
                    currentFocus->shakeHighlight(FocusDirection::Right);
                else if (progressAnimation) {
                    if (counter % 4 == 0) currentFocus->shakeHighlight(FocusDirection::Up);
                    else if (counter % 4 == 1) currentFocus->shakeHighlight(FocusDirection::Right);
                    else if (counter % 4 == 2) currentFocus->shakeHighlight(FocusDirection::Down);
                    else if (counter % 4 == 3) currentFocus->shakeHighlight(FocusDirection::Left);
                    counter = (counter + 1) % 4; // Reset the counter after a full cycle to prevent overflow
                }
            }
        
            // Handle input when no element is focused
            if (!currentFocus && !simulatedBack && simulatedBackComplete && !stillTouching && !runningInterpreter.load(std::memory_order_acquire)) {
                if (!topElement)
                    return;
        
                if (!currentGui->initialFocusSet() || keysDown & (HidNpadButton_AnyUp | HidNpadButton_AnyDown | HidNpadButton_AnyLeft | HidNpadButton_AnyRight)) {
                    currentGui->requestFocus(topElement, FocusDirection::None);
                    currentGui->markInitialFocusSet();
                    repeatTick = 1;
                }
            }
        
            // If nothing is highlighted AND the menu is fully loaded/drawn, set focus to topElement
            if (!currentFocus && !touchDetected && (!oldTouchDetected || oldTouchEvent == elm::TouchEvent::Scroll)) {
                if (!simulatedBack && simulatedBackComplete) {
                    if (topElement) {
                        currentGui->removeFocus();
                        currentGui->requestFocus(topElement, FocusDirection::None);
                    }
                }
            }
        
            bool handled = false;
            elm::Element* parentElement = currentFocus;
        
            // Propagate click events upwards through the hierarchy
            while (!handled && parentElement) {
                handled = parentElement->onClick(keysDown);
                parentElement = parentElement->getParent();
            }
        
            parentElement = currentFocus;
            // Propagate input events upwards through the hierarchy
            while (!handled && parentElement) {
                handled = parentElement->handleInput(keysDown, keysHeld, touchPos, joyStickPosLeft, joyStickPosRight);
                parentElement = parentElement->getParent();
            }
        
            // Return early if the GUI has changed
            if (currentGui != this->getCurrentGui())
                return;
        
            // Handle input events for the current GUI
            handled |= currentGui->handleInput(keysDown, keysHeld, touchPos, joyStickPosLeft, joyStickPosRight);
        
            // Handle arrow key navigation when no touch input is detected
            if (!touchDetected && !oldTouchDetected && !handled && currentFocus && !stillTouching && !runningInterpreter.load(std::memory_order_acquire)) {
                static bool shouldShake = true;
        
                // Check for single arrow key press
                if ((((keysHeld & HidNpadButton_AnyUp) != 0) + ((keysHeld & HidNpadButton_AnyDown) != 0) + ((keysHeld & HidNpadButton_AnyLeft) != 0) + ((keysHeld & HidNpadButton_AnyRight) != 0)) == 1) {
                    if ((repeatTick == 0 || repeatTick > 20) && (repeatTick % 4) == 0) {
                        // Request focus based on arrow key direction
                        if (keysHeld & HidNpadButton_AnyUp && !(keysHeld & (KEY_DLEFT | KEY_DRIGHT | KEY_DDOWN | KEY_B | KEY_A | KEY_X | KEY_Y | KEY_L | KEY_R | KEY_ZL | KEY_ZR)))
                            currentGui->requestFocus(currentGui->getTopElement(), FocusDirection::Up, shouldShake); // Request focus on the top element when double-clicking up
                        else if (keysHeld & HidNpadButton_AnyDown && !(keysHeld & (KEY_DLEFT | KEY_DRIGHT | KEY_DUP | KEY_B | KEY_A | KEY_X | KEY_Y | KEY_L | KEY_R | KEY_ZL | KEY_ZR)))
                            currentGui->requestFocus(currentFocus->getParent(), FocusDirection::Down, shouldShake);
                        else if (keysHeld & HidNpadButton_AnyLeft && !(keysHeld & (KEY_DRIGHT | KEY_DUP | KEY_DDOWN | KEY_B | KEY_A | KEY_X | KEY_Y | KEY_L | KEY_R | KEY_ZL | KEY_ZR)))
                            currentGui->requestFocus(currentFocus->getParent(), FocusDirection::Left, shouldShake);
                        else if (keysHeld & HidNpadButton_AnyRight && !(keysHeld & (KEY_DLEFT | KEY_DUP | KEY_DDOWN | KEY_B | KEY_A | KEY_X | KEY_Y | KEY_L | KEY_R | KEY_ZL | KEY_ZR)))
                            currentGui->requestFocus(currentFocus->getParent(), FocusDirection::Right, shouldShake);
        
                        shouldShake = currentGui->getFocusedElement() != currentFocus;
                    }
                    repeatTick++;
                } else {
                    repeatTick = 0;
                    shouldShake = true;
                }
            }
        
            // If the up button is pressed, shift focus to the top element
            if (!touchDetected && (keysDown & HidNpadButton_L) && !(keysHeld & (KEY_DLEFT | KEY_DRIGHT | KEY_DUP | KEY_DDOWN | KEY_B | KEY_A | KEY_X | KEY_Y | KEY_R | KEY_ZL | KEY_ZR)) && !runningInterpreter.load(std::memory_order_acquire)) {
                topElement = currentGui->getTopElement();
                if (topElement) {
                    currentGui->requestFocus(topElement, FocusDirection::None);
                }
            }
        
            // If the down button is pressed, shift focus to the bottom element
            if (!touchDetected && (keysDown & HidNpadButton_R) && !(keysHeld & (KEY_DLEFT | KEY_DRIGHT | KEY_DUP | KEY_DDOWN | KEY_B | KEY_A | KEY_X | KEY_Y | KEY_L | KEY_ZL | KEY_ZR)) && !runningInterpreter.load(std::memory_order_acquire)) {
                bottomElement = currentGui->getBottomElement();
                if (bottomElement) {
                    currentGui->requestFocus(bottomElement, FocusDirection::None);
                }
            }
        
            // Handle touch release event
            if (!touchDetected && oldTouchDetected) {
                if (currentGui && topElement) {
                    topElement->onTouch(elm::TouchEvent::Release, oldTouchPos.x, oldTouchPos.y, oldTouchPos.x, oldTouchPos.y, initialTouchPos.x, initialTouchPos.y);
                }
            }
        
            // Handle touch input
            if (touchDetected) {
                if (!interruptedTouch)
                    interruptedTouch = (keysHeld & ALL_KEYS_MASK) != 0;
        
                // Calculate touch distance
                u32 xDistance = std::abs(static_cast<s32>(initialTouchPos.x) - static_cast<s32>(touchPos.x));
                u32 yDistance = std::abs(static_cast<s32>(initialTouchPos.y) - static_cast<s32>(touchPos.y));
        
                xDistance *= xDistance;
                yDistance *= yDistance;
        
                // Determine touch event type (scroll or hold)
                if ((xDistance + yDistance) > 1000) {
                    elm::Element::setInputMode(InputMode::TouchScroll);
                    touchEvent = elm::TouchEvent::Scroll;
                } else {
                    if (touchEvent != elm::TouchEvent::Scroll)
                        touchEvent = elm::TouchEvent::Hold;
                }
        
                // Handle touch input initiation
                if (!oldTouchDetected) {
                    initialTouchPos = touchPos;
                    elm::Element::setInputMode(InputMode::Touch);
                    if (!runningInterpreter.load(std::memory_order_acquire)) {
                        if (initialTouchPos.y <= cfg::FramebufferHeight - 73U && initialTouchPos.y > 73U && initialTouchPos.x <= cfg::FramebufferWidth && initialTouchPos.x > 0U) {
                            touchInBounds = true;
                            currentGui->removeFocus();
                        } else {
                            touchInBounds = false;
                        }
                    }
                    touchEvent = elm::TouchEvent::Touch;
                }
        
                // Call onTouch method for the top element to handle touch event
                if (currentGui && topElement && !runningInterpreter.load(std::memory_order_acquire)) {
                    topElement->onTouch(touchEvent, touchPos.x, touchPos.y, oldTouchPos.x, oldTouchPos.y, initialTouchPos.x, initialTouchPos.y);
        
                    if (touchPos.x > 0U && touchPos.x <= cfg::FramebufferWidth && touchPos.y > 73U && touchPos.y <= cfg::FramebufferHeight - 73U)
                        currentGui->removeFocus();
                }
        
                // Update old touch position
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
                if (!interruptedTouch && !runningInterpreter.load(std::memory_order_acquire)) {
                    // Check touch button locations for specific actions
                    if (oldTouchPos.x < 150U && oldTouchPos.y > cfg::FramebufferHeight - 73U && initialTouchPos.x < 150U && initialTouchPos.y > cfg::FramebufferHeight - 73U) {
                        simulatedBackComplete = false;
                        simulatedBack = true;
                    }
                    if (oldTouchPos.x >= 150U && oldTouchPos.x < 260U && oldTouchPos.y > cfg::FramebufferHeight - 73U && initialTouchPos.x >= 150U && initialTouchPos.x < 260U && initialTouchPos.y > cfg::FramebufferHeight - 73U) {
                        simulatedSelectComplete = false;
                        simulatedSelect = true;
                    }
                    if (oldTouchPos.x >= 260U && oldTouchPos.x <= cfg::FramebufferWidth && oldTouchPos.y > cfg::FramebufferHeight - 73U && initialTouchPos.x >= 260U && initialTouchPos.x <= cfg::FramebufferWidth && initialTouchPos.y > cfg::FramebufferHeight - 73U) {
                        simulatedNextPageComplete = false;
                        simulatedNextPage = true;
                    }
                    if (oldTouchPos.x > 0U && oldTouchPos.x <= 252 && oldTouchPos.y > 0U && oldTouchPos.y <= 73U && initialTouchPos.x > 0U && initialTouchPos.x <= 252 && initialTouchPos.y > 0U && initialTouchPos.y <= 73U) {
                        simulatedMenuComplete = false;
                        simulatedMenu = true;
                    }
                }
        
                // Set input mode to controller when touch input ends
                elm::Element::setInputMode(InputMode::Controller);
        
                // Reset touch-related variables
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

        void pop() {
            if (!this->m_guiStack.empty())
                this->m_guiStack.pop();
        }
        
        template<typename G, typename ...Args>
        friend std::unique_ptr<tsl::Gui>& changeTo(Args&&... args);
        
        friend void goBack();
        friend void pop();
        
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
            
            u64 decodedKeys = hlp::comboStringToKeys(parsedConfig[ULTRAHAND_PROJECT_NAME][KEY_COMBO_STR]); // CUSTOM MODIFICATION
            if (decodedKeys)
                tsl::cfg::launchCombo = decodedKeys;
            
            datetimeFormat = removeQuotes(parsedConfig[ULTRAHAND_PROJECT_NAME]["datetime_format"]); // read datetime_format
            if (datetimeFormat.empty()) {
                datetimeFormat = removeQuotes(DEFAULT_DT_FORMAT);
            }
            
            hideClock = (removeQuotes(parsedConfig[ULTRAHAND_PROJECT_NAME]["hide_clock"]) != FALSE_STR);
            hideBattery = (removeQuotes(parsedConfig[ULTRAHAND_PROJECT_NAME]["hide_battery"]) != FALSE_STR);
            hidePCBTemp = (removeQuotes(parsedConfig[ULTRAHAND_PROJECT_NAME]["hide_pcb_temp"]) != FALSE_STR);
            hideSOCTemp = (removeQuotes(parsedConfig[ULTRAHAND_PROJECT_NAME]["hide_soc_temp"]) != FALSE_STR);
            
        }

        /**
         * @brief Update and save launch combo keys
         *
         * @param keys the new combo keys
         */
        [[maybe_unused]] static void updateCombo(u64 keys) {
            tsl::cfg::launchCombo = keys;
            hlp::ini::updateOverlaySettings({
                { TESLA_STR, { // CUSTOM MODIFICATION
                    { KEY_COMBO_STR, tsl::hlp::keysToComboString(keys) }
                }}
            }, TESLA_CONFIG_FILE);
            hlp::ini::updateOverlaySettings({
                { ULTRAHAND_PROJECT_NAME, { // CUSTOM MODIFICATION
                    { KEY_COMBO_STR, tsl::hlp::keysToComboString(keys) }
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
                    
                    if (updateMenuCombos) {  // CUSTOM MODIFICATION
                        if ((shData->keysHeld & tsl::cfg::launchCombo2) == tsl::cfg::launchCombo2) {
                            tsl::cfg::launchCombo = tsl::cfg::launchCombo2;
                            setIniFileValue(SETTINGS_CONFIG_INI_PATH, ULTRAHAND_PROJECT_NAME, KEY_COMBO_STR, TESLA_COMBO_STR);
                            setIniFileValue(TESLA_CONFIG_INI_PATH, TESLA_STR, KEY_COMBO_STR, TESLA_COMBO_STR);
                            eventFire(&shData->comboEvent);
                            updateMenuCombos = false;
                        }
                        
                    }

                    if ((((shData->keysHeld & tsl::cfg::launchCombo) == tsl::cfg::launchCombo) && shData->keysDown & tsl::cfg::launchCombo)) {
                        if (updateMenuCombos) {
                            setIniFileValue(SETTINGS_CONFIG_INI_PATH, ULTRAHAND_PROJECT_NAME, KEY_COMBO_STR, ULTRAHAND_COMBO_STR);
                            setIniFileValue(TESLA_CONFIG_INI_PATH, TESLA_STR, KEY_COMBO_STR, ULTRAHAND_COMBO_STR);
                            updateMenuCombos = false;
                        }
                        
                        //updateMenuCombos = "ZL+ZR+DDOWN";
                        if (shData->overlayOpen) {
                            tsl::Overlay::get()->hide();
                            shData->overlayOpen = false;
                        }
                        else {
                            eventFire(&shData->comboEvent);
                        }
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
    
    static void pop() {
        Overlay::get()->pop();
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
            //logMessage("argv[arg]: "+std::string(argv[arg]));
            if ((strcasecmp(argv[arg], "--skipCombo") == 0)) {
                //logMessage("argv[0]: " +std::string(argv[0]));
                //logMessage("argv[1]: " +std::string(argv[1]));
                //eventFire(&shData.comboEvent);
                //overlay->disableNextAnimation();
                skipCombo = true;
                break;
                //etIniFileValue(SETTINGS_CONFIG_INI_PATH, ULTRAHAND_PROJECT_NAME, IN_OVERLAY_STR, FALSE_STR);
            }
            //std::memset(argv[arg], 0, std::strlen(argv[arg]));
        }
        
        //std::string SETTINGS_CONFIG_INI_PATH = "sdmc:/config/ultrahand/config.ini"; // global vars in ultra.hpp
        //std::string TESLA_CONFIG_INI_PATH = "sdmc:/config/tesla/config.ini";
        //std::map<std::string, std::map<std::string, std::string>> settingsData = getParsedDataFromIniFile(SETTINGS_CONFIG_INI_PATH);
        //std::string inOverlayStrVal = ;
        
        bool inOverlay = (parseValueFromIniSection(SETTINGS_CONFIG_INI_PATH, ULTRAHAND_PROJECT_NAME, IN_OVERLAY_STR) != FALSE_STR);
        //if (settingsData.count(ULTRAHAND_PROJECT_NAME) > 0 && settingsData[ULTRAHAND_PROJECT_NAME].count(IN_OVERLAY_STR) > 0) {
        //    inOverlayStrVal = settingsData[ULTRAHAND_PROJECT_NAME][IN_OVERLAY_STR];
        //} else {
        //    inOverlayStrVal = TRUE_STR; // Assign default value if the keys are not present
        //    inOverlay = true;
        //}
        //settingsData.clear();
        
        
        
        if (inOverlay && skipCombo) {
            setIniFileValue(SETTINGS_CONFIG_INI_PATH, ULTRAHAND_PROJECT_NAME, IN_OVERLAY_STR, FALSE_STR);
            eventFire(&shData.comboEvent);
            //overlay->disableNextAnimation();
        }

        overlay->disableNextAnimation();
        
        
        //if ((skipCombo)) {
        //    overlay->disableNextAnimation();
        //}


        //if (inOverlay) {
        //    logMessage("In Overlay/");
        //    overlay->disableNextAnimation();
        //} else
        //    logMessage("Not in overlay");

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
                
                if (overlay->shouldHide()) {
                    break;
                }
                
                if (overlay->shouldClose())
                    shData.running = false;
                
                //if (updateMenuCombos) { // CUSTOM MODIFICATION
                //    setIniFileValue(SETTINGS_CONFIG_INI_PATH, ULTRAHAND_PROJECT_NAME, KEY_COMBO_STR, "L+DDOWN+RS");
                //    setIniFileValue(TESLA_CONFIG_INI_PATH, "tesla", KEY_COMBO_STR, "L+DDOWN+RS");
                //    updateMenuCombos = false;
                //}
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
    u32  __nx_nv_transfermem_size = 0x16000;
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
