set(LIB video)

add_library(${LIB} STATIC
    src/video.cpp
    src/window.cpp
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PUBLIC common ${SDL2_LIBRARIES})
