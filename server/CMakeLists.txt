#[===[ SERVER ]===]

set(EXEC_SERVER "r-type_server")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)
add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

find_package(Boost REQUIRED COMPONENTS system thread regex)

add_executable(${EXEC_SERVER}
        src/Commands/Hello.cpp
        src/Commands/Input.cpp
        src/Commands/JoinRoom.cpp
        src/Commands/StartGame.cpp
        src/Commands/UpdateName.cpp
        src/game/rtype/RtypeScene.cpp
        src/game/rtype/RtypeGame.cpp
        src/Client.cpp
        src/Room.cpp
        src/ThreadSafeQueue.cpp
        src/UDPServer.cpp
        src/main.cpp
)

target_include_directories(${EXEC_SERVER}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${Boost_INCLUDE_DIRS}
        ${RTYPE_GAME_ENGINE_INCLUDE}
)

target_compile_options(${EXEC_SERVER}
        PRIVATE
        -Wall
        -Wextra
        -ggdb3
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fno-gnu-unique)
endif ()

target_link_libraries(${EXEC_SERVER}
        PRIVATE
        GameEngine
        Boost::boost
        Boost::system
        spdlog::spdlog
)
