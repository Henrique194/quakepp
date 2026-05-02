set(LIB renderer)

set(GL1_RENDERER
    src/gl1/gl1.h
    src/gl1/image.cpp
    src/gl1/init.cpp
    src/gl1/pic.cpp
    src/gl1/upload.cpp
    src/gl1/window.cpp
)

set(SRC
    src/gl_ctx.cpp
    src/gl_ctx.h
    src/init.cpp
    ${GL1_RENDERER}
)

add_library(${LIB} STATIC ${SRC})

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR} "src/")
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PRIVATE fs glad::glad video)
target_link_libraries(${LIB} PUBLIC common ${SDL2_LIBRARIES})
