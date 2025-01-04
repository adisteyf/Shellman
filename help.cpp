#include <iostream>
#include <string>
#include <ncurses.h>
#include <cstring>

void helpCommand() {
    // Ask the user if they want interactive help or not
    setlocale(LC_ALL, "");
    std::string input;
    std::cout << "Do you want to see the help text interactively? (y/n): ";
    std::cin >> input;

    if (input == "y" || input == "Y") {
        // Initialize ncurses for interactive display
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);

        // Enable bold text in ncurses
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_WHITE); // Optional: Customize text colors
        attron(A_BOLD);  // Enable bold mode

        // Define sections of the help text
        const char* sections[] = {
            "Commands Center\nThis program allows you to execute commands using arguments or parameters.\n\n",
            "Usage Format: <arg1> <arg2> <arg3>\n\n",
            "Arguments Explained:\n"
            "  <arg1> = shellman (This is the program's name; always use it first.)\n"
            "  <arg2> = the command you want to run (e.g., 'help', 'open', etc.)\n"
            "  <arg3> = additional data for the command (e.g., a filename). Not required for all commands.\n\n",
            "Examples:\n"
            "  Simple command: shellman help shellman (Displays help for the program.)\n"
            "  Complex command: shellman open file.txt (Opens a file named 'file.txt'.)\n\n",
            "Additional Information:\n"
            "  Common Use Cases:\n"
            "    - Use 'help' to get a list of available commands.\n"
            "    - Use 'open <filename>' to work with files in the program.\n"
            "    - Use 'exit' to close the program.\n\n",
            "Tips for Beginners:\n"
            "    - Always type 'shellman' first, followed by your command.\n"
            "    - Use meaningful filenames and paths or info when passing data.\n"
            "    - Double-check spelling to avoid errors.\n\n",
            "Troubleshooting:\n"
            "    - If a command doesn’t work, make sure you’re using the correct format.\n"
            "    - Check if the file you’re trying to open exists in the specified location.\n"
            "    - For unknown commands, use 'help' to see the full list of supported commands.\n"
            "    - Ensure your arguments do not contain spaces unless wrapped in quotes.\n\n",
            "ALL COMMANDS:\n"
            "  help : displays this text and general help\n"
            "  version : displays the metadata of the shellman\n\n",
            "MODES:\n"
            "  GUI like : the main mode that can be entered using certain commands\n"
            "  Regular terminal : this mode includes just some of the commands and can be used for setup\n\n",
            "Need more help? Visit the documentation or contact support.\n"
            "We suggest visiting the official documentation:\n"
            "https://github.com/IvanKoskov/Shellman\n"
        };

        int sectionCount = sizeof(sections) / sizeof(sections[0]);
        int currentSection = 0;

        // Get terminal dimensions
        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        // Calculate the center of the screen
        int startY = rows / 4; // Start from one-fourth down the screen for better aesthetics
        int startX = cols / 2; // Center horizontally

        // Display each section when a key is pressed
        while (currentSection < sectionCount) {
            clear();
            
            // Split text into lines and center them
            const char* text = sections[currentSection];
            int lineCount = 0;
            char* textCopy = strdup(text);  // Make a copy of the text to avoid modifying the literal

            char* line = strtok(textCopy, "\n");
            while (line != NULL) {
                // Calculate the starting position for each line to center it
                int x = (cols - strlen(line)) / 2;
                mvprintw(startY + lineCount, x, "%s", line);
                line = strtok(NULL, "\n");
                lineCount++;
            }

            free(textCopy);  // Free the copied string

            refresh();
            int ch = getch(); // Wait for user input
            if (ch == 'q' || ch == 'Q') { // Exit on 'q'
                break;
            }
            currentSection++;
        }

        // Disable bold text
        attroff(A_BOLD);

        // End ncurses mode
        endwin();
    } else {
        // Display the help text in plain text format
        std::cout << "Commands Center\nThis program allows you to execute commands using arguments or parameters.\n\n";
        std::cout << "Usage Format: <arg1> <arg2> <arg3>\n\n";
        std::cout << "Arguments Explained:\n";
        std::cout << "  <arg1> = shellman (This is the program's name; always use it first.)\n";
        std::cout << "  <arg2> = the command you want to run (e.g., 'help', 'open', etc.)\n";
        std::cout << "  <arg3> = additional data for the command (e.g., a filename). Not required for all commands.\n\n";
        std::cout << "Examples:\n";
        std::cout << "  Simple command: shellman help shellman (Displays help for the program.)\n";
        std::cout << "  Complex command: shellman open file.txt (Opens a file named 'file.txt'.)\n\n";
        std::cout << "Additional Information:\n";
        std::cout << "  Common Use Cases:\n";
        std::cout << "    - Use 'help' to get a list of available commands.\n";
        std::cout << "    - Use 'open <filename>' to work with files in the program.\n";
        std::cout << "    - Use 'exit' to close the program.\n\n";
        std::cout << "Tips for Beginners:\n";
        std::cout << "    - Always type 'shellman' first, followed by your command.\n";
        std::cout << "    - Use meaningful filenames and paths or info when passing data.\n";
        std::cout << "    - Double-check spelling to avoid errors.\n\n";
        std::cout << "Troubleshooting:\n";
        std::cout << "    - If a command doesn’t work, make sure you’re using the correct format.\n";
        std::cout << "    - Check if the file you’re trying to open exists in the specified location.\n";
        std::cout << "    - For unknown commands, use 'help' to see the full list of supported commands.\n";
        std::cout << "    - Ensure your arguments do not contain spaces unless wrapped in quotes.\n\n";
        std::cout << "ALL COMMANDS:\n";
        std::cout << "  help : displays this text and general help\n";
        std::cout << "  version : displays the metadata of the shellman\n\n";
        std::cout << "MODES:\n";
        std::cout << "  GUI like : the main mode that can be entered using certain commands\n";
        std::cout << "  Regular terminal : this mode includes just some of the commands and can be used for setup\n\n";
        std::cout << "Need more help? Visit the documentation or contact support.\n";
        std::cout << "We suggest visiting the official documentation:\n";
        std::cout << "https://github.com/IvanKoskov/Shellman\n";
    }
}
