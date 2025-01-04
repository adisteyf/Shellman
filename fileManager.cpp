#include "fileManager.hpp"

void welcomeMessage(void) {
    // Initialize ncurses
    initscr();              // Initialize screen
    noecho();               // Disable automatic echoing of typed characters
    cbreak();               // Disable line buffering
    curs_set(0);            // Hide the cursor

    // Start color functionality
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);  // Blue text on black background
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);  // Yellow text for the box

    // Get the window size to center the message
    int height, width;
    getmaxyx(stdscr, height, width);

    // Define the welcome message
    std::string message = "Welcome to Shellman File Manager!";

    // Calculate the starting position to center the text
    int startX = (width - message.length()) / 2;
    int startY = height / 4;

    // Bold and Blue for the first line
    attron(A_BOLD);  // Bold text
    attron(COLOR_PAIR(1));  // Blue text
    mvprintw(startY, startX, message.c_str());  // Print centered message
    attroff(A_BOLD);  // Turn off bold
    attroff(COLOR_PAIR(1));  // Turn off blue color

    std::string info = "Browse and find files with ease in terminal.";
    startY += 2;  // Move down
    mvprintw(startY, startX, info.c_str());

    std::string infomore = "Use Shellman with vim and other terminal utilities for productivity!";
    startY += 2;  // Move down
    mvprintw(startY, startX, infomore.c_str());

    // Add a message for first-time users
    std::string firstTimeMessage = "This is your first time using Shellman!";
    startY += 2;  // Move down
    mvprintw(startY, startX, firstTimeMessage.c_str());

    // Display additional info or instructions
    std::string instructions = "Press any key to continue...";
    startY += 2;  // Move down
    mvprintw(startY, startX, instructions.c_str());

    // Create a small box for the creator's name and credits
    std::string creatorMessage = "Created by Ivan Koskov";
    std::string creditsMessage = "Credits: ncurses, adisteyf, cherry";
    int boxWidth = std::max(creatorMessage.length(), creditsMessage.length()) + 4;  // Add space for the box border
    int boxHeight = 4;  // Height of the box (2 rows for messages, 1 row for top/bottom border)
    int boxStartX = (width - boxWidth) / 2;
    int boxStartY = height - 8;  // Place the box a bit above the bottom of the screen

    // Draw the box (top and bottom borders)
    attron(COLOR_PAIR(2));  // Yellow text for the box
    mvhline(boxStartY, boxStartX, '-', boxWidth);  // Top border
    mvhline(boxStartY + boxHeight - 1, boxStartX, '-', boxWidth);  // Bottom border

    // Left and right borders of the box
    for (int i = boxStartY + 1; i < boxStartY + boxHeight - 1; ++i) {
        mvaddch(i, boxStartX, '|');
        mvaddch(i, boxStartX + boxWidth - 1, '|');
    }

    // Print the creator's name inside the box
    mvprintw(boxStartY + 1, boxStartX + 2, creatorMessage.c_str());
    mvprintw(boxStartY + 2, boxStartX + 2, creditsMessage.c_str());

    // Turn off color
    attroff(COLOR_PAIR(2));

    // Refresh the screen
    refresh();

    // Wait for user input
    getch();

    // Clean up and end ncurses mode
    endwin();
}







bool createConfigFileIfNotExist(const std::string& filepath) {
    std::ifstream configFile(filepath);
    
    if (!configFile) {
        // File does not exist, create it
        std::ofstream newConfigFile(filepath);
        if (newConfigFile) {
            std::cout << "Configuration file created: " << filepath << std::endl;
            newConfigFile << "{\n\t\"setting1\": \"value1\",\n\t\"setting2\": \"value2\"\n}\n";  // Sample content
            return true; // File was created
        } else {
            std::cerr << "Failed to create configuration file: " << filepath << std::endl;
            return false;
        }
    } else {
        return false; // File already exists
    }
}

std::string getConfigFilePath() {
    std::string homeDir = getenv("HOME");
    return homeDir + "/Documents/.shellman_config"; // Hidden file with no extension
}