include(ConfigureRcFile)

add_compile_definitions($<$<CONFIG:Debug>:PARANOID>)

set(LIBS common core video)
foreach(LIB ${LIBS})
    add_subdirectory(${LIB})
endforeach()

set(SOURCE_FILES main.cpp)
list(APPEND LIBS ${SDL2_LIBRARIES})

if(WIN32)
    add_executable(${PACKAGE_TARNAME} WIN32 ${SOURCE_FILES})
    configure_rc_file()
else()
    add_executable(${PACKAGE_TARNAME} ${SOURCE_FILES})
endif()
target_include_directories(${PACKAGE_TARNAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${PACKAGE_TARNAME} ${LIBS} stdc++exp)

if(MSVC)
    set_target_properties(${PACKAGE_TARNAME} PROPERTIES
        LINK_FLAGS
        "/MANIFEST:NO"
    )
endif()
