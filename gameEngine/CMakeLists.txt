#[===[ GameEngine ]===]

set(LIBRARY "GameEngine")

add_library(${LIBRARY} STATIC
        src/testlib.cpp
        src/ecs/entity/EntityManager.cpp
)

target_include_directories(${LIBRARY}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_options(${LIBRARY}
        PRIVATE
        -Wall
        -Wextra
        -ggdb3
)

target_link_libraries(${LIBRARY}
        PUBLIC
        sfml-system
        sfml-network
        sfml-graphics
        sfml-window
)


set_target_properties(${LIBRARY}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
)