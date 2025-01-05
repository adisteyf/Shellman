cmake_minimum_required(VERSION 3.10)


project(Shellman)
find_package(Curses REQUIRED)

set(SOURCES
    src/main.cpp
    src/config.cpp
    src/fileManager.cpp
    src/help.cpp
    src/mainview.cpp

    src/config.hpp
    src/fileManager.hpp
    src/help.hpp
    src/mainview.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CURSES_INCLUDE_DIRS})

