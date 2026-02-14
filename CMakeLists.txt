cmake_minimum_required(VERSION 3.21.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(ConfigureRcFile)

project("Quake++" VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

string(TIMESTAMP CURRENT_YEAR "%Y")
set(PACKAGE_NAME ${PROJECT_NAME})
set(PACKAGE_TARNAME "quake++")
set(PACKAGE_VERSION ${PROJECT_VERSION})
set(PACKAGE_STRING "${PROJECT_NAME} ${PROJECT_VERSION}")
set(PACKAGE_COPYRIGHT "Copyright (C) ${CURRENT_YEAR}")
set(PACKAGE_LICENSE "GNU General Public License, version 3")

find_library(MATH m)
if(MATH)
    link_libraries(${MATH})
endif()
find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_compile_definitions($<$<CONFIG:Debug>:PARANOID>)
configure_file(cmake/config.h.in config.h)

# Add internal libs first.
set(LIBS common core filesystem input video)
foreach(LIB ${LIBS})
    add_subdirectory(src/${LIB})
endforeach()
# Then append external libs.
list(APPEND LIBS ${SDL2_LIBRARIES} glad::glad)

set(SOURCE_FILES src/main.cpp)
if(WIN32)
    set(RC_NAME "${PACKAGE_TARNAME}.rc")
    set(WIN_DIR "${CMAKE_SOURCE_DIR}/dist/win")
    add_executable(${PACKAGE_TARNAME} WIN32 ${SOURCE_FILES})
    configure_rc_file(${RC_NAME} ${WIN_DIR})
else()
    add_executable(${PACKAGE_TARNAME} ${SOURCE_FILES})
endif()
target_include_directories(${PACKAGE_TARNAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${PACKAGE_TARNAME} ${LIBS} stdc++exp)

if(MSVC)
    set_target_properties(${PACKAGE_TARNAME} PROPERTIES LINK_FLAGS "/MANIFEST:NO")
endif()
