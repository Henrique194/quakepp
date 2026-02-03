set(LIB filesystem)

add_library(${LIB} STATIC
    filesystem.cpp
    pak.cpp
    search_dir.cpp
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PRIVATE common)
