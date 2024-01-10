#[===[ GameEngine ]===]

set(LIBRARY "GameEngine")

add_library(${LIBRARY} STATIC
        src/asset/AssetManager.cpp
        src/asset/ConfigLoader.cpp
        src/core/Core.cpp
        src/ecs/entity/EntityManager.cpp
        src/ecs/RegistryBuilder.cpp
        src/entity/EntityFactory.cpp
        src/entity/EntityBuilder.cpp
        src/scene/SceneContainer.cpp
        src/scene/SceneManager.cpp
        src/scene/SimpleScene.cpp
        src/UI/Window.cpp
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
        Boost::serialization
        Boost::system
        spdlog::spdlog
)


set_target_properties(${LIBRARY}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
)
