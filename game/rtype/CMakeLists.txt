#[===[ GameEngine ]===]

set(LIBRARY "RtypeGame")

add_library(${LIBRARY} STATIC
        src/scene/ClientGame.cpp
        src/scene/Lobby.cpp
        src/scene/Welcome.cpp
        src/scene/HostGame.cpp
        src/sceneController/HostGameController.cpp
        src/sceneController/ClientGameController.cpp
        src/sceneController/LobbyController.cpp
        src/sceneController/WelcomeController.cpp
        src/sceneController/NetworkController.cpp
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
