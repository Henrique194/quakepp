set(LIB core)

add_library(${LIB} STATIC
    src/cli.cpp
    src/engine.cpp
    src/event.cpp
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PRIVATE filesystem input video)
target_link_libraries(${LIB} PUBLIC common ${SDL2_LIBRARIES})
