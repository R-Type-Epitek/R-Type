#[===[ GameEngine ]===]

set(LIBRARY "GameEngine")

add_library(${LIBRARY} STATIC
        src/ecs/entity/EntityManager.cpp
        src/ecs/RegistryBuilder.cpp
        src/ecs/EntityBuilder.cpp
        src/gfx/sfml/SfmlEvent.cpp
        src/gfx/sfml/SfmlTexture.cpp
        src/gfx/sfml/SfmlDisplay.cpp
        src/gfx/sfml/SfmlGfx.cpp
        src/scene/SceneContainer.cpp
        src/scene/SceneManager.cpp
        src/UI/Window.cpp
        src/asset/AssetManager.cpp
        src/entity/EntityFactory.cpp
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