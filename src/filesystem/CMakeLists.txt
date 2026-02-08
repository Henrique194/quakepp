set(LIB filesystem)

add_library(${LIB} STATIC
    src/filesystem.cpp
    src/pak.cpp
    src/search_dir.cpp
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PRIVATE common)
