#pragma once

#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>
#include <experimental/filesystem>

/**
 * Function that converts the string into uppercase
 * @param string
 * @return string in upper case
 */
std::string StringToUpper(const std::string &string);

/**
 * Finds the substring in the string
 * @param string
 * @param substring
 * @return position where the substring starts - 0 if not found
 */
std::string::size_type FindSubstring(const std::string &string, const std::string &substring);

/**
 * Converts the string input into int output
 * @param str_input
 * @param output
 * @return true if successful / false if not
 */
bool Parse(const std::string &str_input, int &output);

/**
 * Converts the string input into double output
 * @param str_input
 * @param output
 * @return true if successful / flase if not
 */
bool ParseDouble(const std::string &str_input, double &output);


/**
* Function that correctly reads the user int input
* https://stackoverflow.com/questions/22818496/read-integer-from-
* https://www.codespeedy.com/taking-only-integer-input-in-cpp/
* @return int
*/
int IntegerEnter();

/**
 * Function that correctly reads the user double input
 * @return
 */
int DoubleEnter();

/**
 * Function that compares 2 string returns true if they are equal case insensitively
 * https://stackoverflow.com/questions/11635/case-insensitive-string-comparison-in-c
 * @param str1
 * @param str2
 * @return true if equal / flase if not
 */
bool CaseInsensitiveEquals(const std::string &str1, const std::string &str2);

/**
 * Function that returns true if the string starts with another string
 * @param string
 * @param starts
 * @return true if the string starts with the starts string / false otherwise
 */
bool startsWith(const std::string &string, const std::string &starts);

/**
 * Stops the program for a certain amount of milliseconds
 * @param millisecond
 */
void Wait(const int &millisecond);

/**
 * Waits for any user input
 */
void continueByEnter();

/**
 * Appends a timestamp to a string
 * @param string
 */
void AppendTime(std::string &string);

/**
 * Function that clears the screen
 */
void clearScreen();

/**
 * Prints a border
 */
void printBorder();

/**
 * Prints a little error message.
 */
void printWrong();

/**
 * Prints the options text
 */
void printOptions();

/**
 * Prints a divider between text
 */
void printDivider();
