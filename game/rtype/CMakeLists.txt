#[===[ GameEngine ]===]

set(LIBRARY "RtypeGame")

add_library(${LIBRARY} STATIC
        src/scene/ClientGame.cpp
        src/scene/Lobby.cpp
        src/scene/Welcome.cpp
        src/scene/HostGame.cpp
        src/sceneController/GraphicController.cpp
        src/sceneController/HostGameController.cpp
        src/sceneController/SceneController.cpp
        src/sceneController/NetworkController.cpp
        src/sceneController/RendererController.cpp
        src/sceneController/BindingController.cpp
        src/sceneController/BindingController.cpp
        src/scripts/DataHolder.cpp
        src/scripts/EnemyLinear.cpp
        src/scripts/EnemySinusoidal.cpp
        src/scene/SoloHostGame.cpp
)

target_include_directories(${LIBRARY}
        PUBLIC
        ${RTYPE_GAME_ENGINE_INCLUDE}
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_options(${LIBRARY}
        PRIVATE
        -Wall
        -Wextra
        -ggdb3
)

target_link_libraries(${LIBRARY}
        PRIVATE
        GameEngine
        Boost::serialization
        Boost::system
        spdlog::spdlog
)

set_target_properties(${LIBRARY}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
)
