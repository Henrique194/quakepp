set(LIB render)

add_library(${LIB} STATIC
    src/render.cpp
    src/texture.cpp
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PRIVATE common filesystem window ${SDL2_LIBRARIES})
