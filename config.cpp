#include <ncurses.h>
#include <vector>
#include <string>
#include "config.hpp"

void displayConfig(void) {
    // Initialize ncurses
    initscr();        // Start ncurses mode
    cbreak();         // Disable line buffering
    noecho();         // Prevent input from being displayed
    curs_set(0);      // Hide the cursor

    // Check if color is supported
    if (has_colors()) {
        start_color();  // Start color functionality
        // Define color pairs
        init_pair(1, COLOR_CYAN, COLOR_BLACK);  // Cyan text on black background
        init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Yellow text on black background
        init_pair(3, COLOR_GREEN, COLOR_BLACK);  // Green text on black background
    }

    int height, width;
    getmaxyx(stdscr, height, width);  // Get the terminal size

    std::vector<std::string> lines;
    lines.push_back("Project: " + std::string(PROJECT_NAME));
    lines.push_back("Version: " + std::string(VERSION));
    lines.push_back("Author: " + std::string(AUTHOR));
    lines.push_back("Maintainer: " + std::string(MAINTAINER));
    lines.push_back("License: " + std::string(LICENSE));
    lines.push_back("Platform: " + std::string(PLATFORM));
    lines.push_back("About: " + std::string(ABOUT));
    lines.push_back("Version: " + std::to_string(VERSION_MAJOR) + "." + 
                     std::to_string(VERSION_MINOR) + "." + 
                     std::to_string(VERSION_PATCH));
    lines.push_back("Compiled with: " + std::string(COMPILER));
    lines.push_back("Compiled on: " + std::string(COMPILED_ON));

    // Calculate where to start printing to center text vertically and horizontally
    int startY = height / 2 - lines.size() / 2;
    int startX = (width - lines[0].length()) / 2 - 5;  // Move text left by 5 characters

    // Display each line with coloring
    for (int i = 0; i < lines.size(); i++) {
        if (i == 0) {
            attron(COLOR_PAIR(1));  // Cyan color for the project name
        } else if (i == 1) {
            attron(COLOR_PAIR(2));  // Yellow color for the version
        } else if (i == 8) {
            attron(COLOR_PAIR(3));  // Green color for compiled with
        } else {
            attroff(COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3));  // Reset colors
        }

        mvprintw(startY + i, startX, "%s", lines[i].c_str());  // Display each line
        attroff(COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3));  // Reset colors after each line
    }

    refresh();       // Refresh the screen to show the changes
    getch();         // Wait for user input
    endwin();        // End ncurses mode
}
