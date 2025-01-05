#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include "config.hpp"
#include "help.hpp"
#include "mainview.hpp" 

// Color macros for terminal output
#define RESET      "\033[0m"     // Back to regular style
#define GREEN      "\033[32m"    // Green for success or valid messages
#define RED        "\033[31m"    // Red for errors
#define INFO       "\033[34m"    // Blue for informational messages
#define HIGHLIGHT  "\033[33m"    // Yellow for highlighted options or active items
#define CYAN       "\033[36m"    // Cyan for user input or prompts
#define BOLD       "\033[1m"     // Bold for headers or important sections



bool createConfigFileIfNotExist(const std::string& filepath);
std::string getConfigFilePath();
void welcomeMessage(void);

#endif // FILEMANAGER_HPP
