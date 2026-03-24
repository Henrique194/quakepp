set(LIB render)

set(GL1_RENDERER
    src/gl1/init.cpp
    src/gl1/render.cpp
    src/gl1/texture.cpp
)

add_library(${LIB} STATIC ${GL1_RENDERER})

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB}
    PRIVATE common window ${SDL2_LIBRARIES}
    PUBLIC filesystem
)
