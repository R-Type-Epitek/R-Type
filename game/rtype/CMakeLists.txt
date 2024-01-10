#[===[ GameEngine ]===]

set(LIBRARY "rtype")

add_library(${LIBRARY} STATIC
        src/scene/ClientGame.cpp
        src/scene/Lobby.cpp
        src/scene/Welcome.cpp
        src/sceneController/HostGameController.cpp
        src/sceneController/ClientGameController.cpp
        src/sceneController/LobbySceneController.cpp
        src/sceneController/WelcomeController.cpp
        include/scene/Welcome.hpp
        include/scene/ClientGame.hpp
        src/scene/HostGame.cpp
)

target_include_directories(${LIBRARY}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${RTYPE_GAME_ENGINE_INCLUDE}
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
