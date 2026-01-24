set(LIB core)

add_library(${LIB} STATIC
    engine.cpp
    event.cpp
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PUBLIC common video ${SDL2_LIBRARIES})
