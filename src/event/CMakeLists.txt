set(LIB event)

add_library(${LIB} STATIC
    src/init.cpp
    src/keyboard.cpp
    src/mouse.cpp
    src/queue.cpp
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PRIVATE input)
target_link_libraries(${LIB} PUBLIC common ${SDL2_LIBRARIES})
