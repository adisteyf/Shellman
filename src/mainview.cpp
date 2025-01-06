#include "mainview.hpp" 
#include <ctime>
#include <unistd.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <string>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>



namespace fs = std::filesystem;

// Function to get a list of directories in a given path
std::vector<std::string> getDirectories(const std::string& path) {
    std::vector<std::string> directories;
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_directory()) {
                directories.push_back(entry.path().filename().string());
            }
        }
    } catch (...) {
        directories.push_back("Error reading directory");
    }
    std::sort(directories.begin(), directories.end());
    return directories;
}

// Function to draw the left pane with the directory tree
void drawDirectoryTree(int height, int leftWidth, const std::string& currentPath, 
                       const std::vector<std::string>& directories, int selectedIndex) {
    // Clear the left pane
    for (int i = 1; i < height - 2; ++i) {
        mvhline(i, 1, ' ', leftWidth - 2);
    }

    // Display the current path at the top
    mvprintw(1, 1, "Current: %s", currentPath.c_str());

    // Display the directories
    int maxItems = height - 4; // Leave space for top/bottom borders
    for (int i = 0; i < std::min(maxItems, (int)directories.size()); ++i) {
        if (i == selectedIndex) {
            attron(A_REVERSE); // Highlight the selected directory
        }
        mvprintw(3 + i, 2, "%s", directories[i].c_str());
        if (i == selectedIndex) {
            attroff(A_REVERSE);
        }
    }
  
  
    refresh();
}

std::string getCurrentTime() {
    time_t now = time(nullptr);
    char buffer[9];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", localtime(&now));
    return std::string(buffer);
}

// Function to get the OS information
std::string getOSInfo() {
#ifdef __linux__
    return "Linux";
#elif __APPLE__
    return "macOS";
#else
    return "Unknown OS";
#endif
}

// Function to draw the bottom pane with dynamic info
void drawBottomPane(int height, int width, const std::string& osInfo, const std::string& username) {
    mvhline(height - 2, 1, '-', width - 2); // Horizontal line
    mvprintw(height - 1, 2, "Press 'q' to quit | Press 'h' for help | %s | %s | %s",
             osInfo.c_str(), username.c_str(), getCurrentTime().c_str()); // Call getCurrentTime() dynamically
    refresh();
}


// Function to draw the main screen
void drawMainScreen(int height, int width, const std::string& osInfo, const std::string& username) {
    clear(); // Clear the screen

    // Draw a border around the entire screen
    box(stdscr, 0, 0);

    // Add a vertical line separating panes
    int leftWidth = width / 3; // Width of the left pane
    for (int i = 1; i < height - 2; ++i) {
        mvaddch(i, leftWidth, '|');
    }

    std::string currentPath = "/";
    std::vector<std::string> directories = getDirectories(currentPath);
    int selectedIndex = 0;

    // Draw the main screen with the initial tree
    drawDirectoryTree(height, leftWidth, currentPath, directories, selectedIndex);
      



    // Draw the bottom pane with dynamic info
    drawBottomPane(height, width, osInfo, username);

    refresh(); // Refresh the screen to apply changes
}

// Function to show the help screen
void showHelpScreen(int height, int width, const std::string& osInfo, const std::string& username) {
    clear(); // Clear the current screen

    // Draw a border around the help screen
    box(stdscr, 0, 0);

    // Display the help message
    mvprintw(1, 1, "Help Message:");
    mvprintw(2, 1, "Shellman File Manager");
    mvprintw(3, 1, "Press 'q' to quit the program.");
    mvprintw(4, 1, "Use the left pane for directory navigation.");
    mvprintw(5, 1, "Use the right pane for file management.");
    mvprintw(6, 1, "Press 'h' again to return to the main screen.");

    // Redraw the bottom pane with system info
    drawBottomPane(height, width, osInfo, username);

    refresh();
}

void initializeWindows() {
    initscr();               // Start ncurses mode
    noecho();                // Disable echo
    cbreak();                // Disable line buffering
    curs_set(0);             // Hide cursor
    keypad(stdscr, TRUE);    // Enable special keys like arrows
    nodelay(stdscr, TRUE);   // Make getch() non-blocking

    // Get terminal dimensions
    int height, width;
    getmaxyx(stdscr, height, width);

    // Get system information
    std::string osInfo = getOSInfo();
    std::string username = getlogin();

    // Directory navigation variables
    std::string currentPath = "/";
    std::vector<std::string> directories = getDirectories(currentPath);
    int selectedIndex = 0;

    // Initial draw
    drawMainScreen(height, width, osInfo, username);
    drawDirectoryTree(height, width / 3, currentPath, directories, selectedIndex);

    long lastTimeUpdate = 0;  // Track last time update for clock

    // Main loop
    int ch;
    while ((ch = getch()) != 'q') {
        // Update the time every second
        long currentTime = time(nullptr);
        if (currentTime - lastTimeUpdate >= 1) { // 1 second interval to update time
            lastTimeUpdate = currentTime;
            drawBottomPane(height, width, osInfo, username);
        }

        if (ch == 'h') {
            showHelpScreen(height, width, osInfo, username);
            while ((ch = getch()) != 'h' && ch != 'q') {
                // Wait for user to press 'h' or 'q'
            }
            if (ch == 'h') {
                drawMainScreen(height, width, osInfo, username);
                drawDirectoryTree(height, width / 3, currentPath, directories, selectedIndex);
            }
        } else if (ch == KEY_UP) {
            // Move selection up
            if (selectedIndex > 0) {
                --selectedIndex;
                drawDirectoryTree(height, width / 3, currentPath, directories, selectedIndex);
            }
        } else if (ch == KEY_DOWN) {
            // Move selection down
            if (selectedIndex < (int)directories.size() - 1) {
                ++selectedIndex;
                drawDirectoryTree(height, width / 3, currentPath, directories, selectedIndex);
            }
        } else if (ch == 'd') {
            // Drill into a directory
            if (!directories.empty()) {
                currentPath = fs::path(currentPath) / directories[selectedIndex];
                directories = getDirectories(currentPath);
                selectedIndex = 0;
                drawDirectoryTree(height, width / 3, currentPath, directories, selectedIndex);
            }
        } else if (ch == 'b') {
            // Go back to the parent directory
            if (currentPath != "/") {
                currentPath = fs::path(currentPath).parent_path().string();
                directories = getDirectories(currentPath);
                selectedIndex = 0;
                drawDirectoryTree(height, width / 3, currentPath, directories, selectedIndex);
            }
        }

        usleep(50000); // Small delay for smoother input handling
    }

    endwin(); // End ncurses mode
}

