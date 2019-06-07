cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)
project(gamepad)

include_directories(..)

# Add macos homebrew paths
if(APPLE)
	include_directories(/usr/local/include)
	link_directories(/usr/local/lib)
endif()

link_libraries(SDL pthread ncurses)
add_executable(gamepad
                ../gamepad.cpp
                main.cpp
)
