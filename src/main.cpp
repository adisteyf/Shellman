#include "fileManager.hpp"

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided

    if (argc != 3) {
        //std::cout << INFO << "Usage: " << argv[0] << " <arg1> <arg2>" << RESET << std::endl;
        //std::cout << "Use arguments to pass commands" << std::endl;
        //std::cout << "arguments will be parsed\n" << std::endl;
        //std::cout << INFO << "We suggest to visit documentation first: \n" << RESET << std::endl;
        //std::cout << "https://github.com/IvanKoskov/Shellman" << std::endl;
        HELPMSG;
        return 1;
    } 

       std::string configFilePath = getConfigFilePath();
    
    // Check if the file was created or already exists
    bool fileCreated = createConfigFileIfNotExist(configFilePath);

    // Final message indicating whether the file was created or exists already
    if (fileCreated) {
        std::cout << INFO << "Config file was just created at: " << configFilePath << RESET << std::endl;
        welcomeMessage();
        return 0;
    }

    else std::cout << INFO << "Config file already exists at: " << configFilePath << RESET << std::endl;


     if (argc > 1 && strcmp(argv[1], "help") == 0)
        helpCommand();

    else if (argc > 1 && strcmp(argv[1], "version") == 0)
        displayConfig();

    else if (argc > 1 && strcmp(argv[1], "man") == 0)
        initializeWindows();

    return 0;
}
