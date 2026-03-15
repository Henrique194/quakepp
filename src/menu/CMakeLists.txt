set(LIB menu)

add_library(${LIB} STATIC
    src/menu.cpp
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PRIVATE common filesystem render video ${SDL2_LIBRARIES})
