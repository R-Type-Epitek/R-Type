#[===[ Client ]===]

set(EXEC_CLIENT "r-type_client")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)


add_executable(${EXEC_CLIENT}
        src/main.cpp
        src/Client.cpp
        src/network/commands/ConnectToServer.cpp
        src/network/commands/GodMode.cpp
        src/network/commands/Input.cpp
        src/network/commands/JoinRoom.cpp
        src/network/commands/JoinRoomAuto.cpp
        src/network/commands/JoinGame.cpp
        src/network/commands/KickPlayer.cpp
        src/network/commands/Spectate.cpp
        src/network/commands/Tracker.cpp
        src/network/commands/UpdateName.cpp
        src/network/tools/Logs.cpp
        src/network/Network.cpp
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
        RtypeGame
        Boost::serialization
        Boost::system
        spdlog::spdlog
)
