#include "mainview.hpp" 

//view to display  the main window
void displayMainScreen(int height, int width, int leftWidth) {
    // Draw a border around the entire screen
    box(stdscr, 0, 0);

    // Add a vertical border to separate left and right panes
    for (int i = 1; i < height - 1; ++i) {
        mvaddch(i, leftWidth, '|'); // Draw a vertical line separating panes
    }

    // Display text in each pane
    mvprintw(1, 1, "Hello, Shellman!"); // Display a message in the top-left corner
    mvprintw(1, leftWidth + 2, "Right Pane"); // Display message in the right pane

    // Display help/info in the bottom
    mvprintw(height - 2, 1, "Press 'q' to quit | Press 'h' for help");

    refresh();
}

void initializeWindows(void) {
    initscr();               // Start ncurses mode
    noecho();                // Disable echo
    cbreak();                // Disable line buffering
    curs_set(0);             // Hide cursor

    // Get terminal dimensions
    int height, width;
    getmaxyx(stdscr, height, width); // Get terminal dimensions

    int leftWidth = width / 3; // Set the width of the left pane

    // Display the main screen
    displayMainScreen(height, width, leftWidth);

    // Wait for user input and handle it
    while (true) {
        int ch = getch(); // Get user input
        if (ch == 'q') {   // Check if it's 'q'
            break;         // Exit the loop if 'q' is pressed
        } else if (ch == 'h') {  // Check if it's 'h'
            clear();  // Clear the screen to show the help message
            mvprintw(1, 1, "Help Message:");  // Display the help message header
            mvprintw(2, 1, "Shellman File Manager");
            mvprintw(3, 1, "Press 'q' to quit the program.");
            mvprintw(4, 1, "Use the left pane for directory navigation.");
            mvprintw(5, 1, "Use the right pane for file management.");
            mvprintw(6, 1, "Press 'h' again to return to the main screen.");
            mvprintw(height - 2, 1, "Press 'q' to quit | Press 'h' for help");
            refresh();
            
            // Wait for user to press a key again (either 'q' to quit or 'h' to return)
            while (true) {
                int helpKey = getch();
                if (helpKey == 'h') {
                    // Clear help message and return to the main screen
                    clear();
                    displayMainScreen(height, width, leftWidth);
                    break;
                } else if (helpKey == 'q') {
                    // Quit if 'q' is pressed in the help screen
                    break;
                }
            }
        }
    }

    endwin(); // End ncurses mode
}