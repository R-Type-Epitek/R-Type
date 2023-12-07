#[===[ Client ]===]

set(EXEC_CLIENT "r-type_client")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)


add_executable(${EXEC_CLIENT}
        src/main.cpp
)

target_include_directories(${EXEC_CLIENT}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_options(${EXEC_CLIENT}
        PRIVATE
        -Wall
        -Wextra
        -ggdb3
)

target_link_libraries(${EXEC_CLIENT}
        PRIVATE
        sfml-system
        sfml-network
        sfml-graphics
        sfml-window
)
