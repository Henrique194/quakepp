set(LIB common)

add_library(${LIB} INTERFACE)

target_include_directories(${LIB} INTERFACE ${CMAKE_BINARY_DIR})
target_include_directories(${LIB} INTERFACE "./include")
target_link_libraries(${LIB} INTERFACE ${SDL2_LIBRARIES})
