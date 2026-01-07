list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

cmake_minimum_required(VERSION 3.21.0)
project("Quake++" VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

string(TIMESTAMP CURRENT_YEAR "%Y")
set(PACKAGE_NAME ${PROJECT_NAME})
set(PACKAGE_TARNAME "quake++")
set(PACKAGE_VERSION ${PROJECT_VERSION})
set(PACKAGE_STRING "${PROJECT_NAME} ${PROJECT_VERSION}")
set(PACKAGE_COPYRIGHT "Copyright (C) ${CURRENT_YEAR}")
set(PACKAGE_LICENSE "GNU General Public License, version 3")
set(WIN_DIR "${CMAKE_SOURCE_DIR}/dist/win")

configure_file(cmake/config.h.in src/config.h)

# Find math library
find_library(MATH m)
if(MATH)
    link_libraries(${MATH})
endif()

find_package(SDL2 CONFIG REQUIRED)

add_subdirectory("src")
