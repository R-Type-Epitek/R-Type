#[===[ Client ]===]

set(EXEC_CLIENT "r-type_client")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)


add_executable(${EXEC_CLIENT}
        src/main.cpp
        src/Client.cpp
        src/scene/SceneManager.cpp
        src/scene/GameScene.cpp
        src/network/Network.cpp
        src/graphics/GUI.cpp
)

target_include_directories(${EXEC_CLIENT}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${RTYPE_GAME_ENGINE_INCLUDE}
)

target_compile_options(${EXEC_CLIENT}
        PRIVATE
        -Wall
        -Wextra
        -ggdb3
)

target_link_libraries(${EXEC_CLIENT}
        PRIVATE
        GameEngine
        sfml-system
        sfml-network
        sfml-graphics
        sfml-window
        spdlog::spdlog
)
