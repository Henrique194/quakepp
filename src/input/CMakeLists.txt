set(LIB input)

add_library(${LIB} STATIC
    src/input.cpp
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PRIVATE ${SDL2_LIBRARIES})
