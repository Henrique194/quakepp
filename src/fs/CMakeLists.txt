set(LIB fs)

add_library(${LIB} STATIC
    src/dir.cpp
    src/init.cpp
    src/load.cpp
    src/pak.cpp
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PUBLIC common)
