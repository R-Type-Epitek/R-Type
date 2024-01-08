#[===[ SERVER ]===]

set(EXEC_SERVER "r-type_server")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)
add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

find_package(Boost REQUIRED COMPONENTS system thread regex)

if (BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)

    set(TEST_EXECUTABLE "${EXEC_SERVER}_tests")

    add_executable(${TEST_EXECUTABLE}
            tests/TestClient.cpp
            tests/TestMain.cpp
            src/Client.cpp
    )

    target_include_directories(${TEST_EXECUTABLE} PRIVATE
            PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/include
            ${Boost_INCLUDE_DIRS}
            ${RTYPE_GAME_ENGINE_INCLUDE}
            ${GTEST_INCLUDE_DIRS}
    )

    target_link_libraries(${TEST_EXECUTABLE} PRIVATE
            PRIVATE
            GameEngine
            Boost::boost
            Boost::system
            Boost::serialization
            spdlog::spdlog
            ${GTEST_BOTH_LIBRARIES}
    )

    gtest_discover_tests(${TEST_EXECUTABLE})
endif ()

add_executable(${EXEC_SERVER}
        src/commands/ConnectToServer.cpp
        src/commands/Input.cpp
        src/commands/JoinRoom.cpp
        src/commands/JoinGame.cpp
        src/commands/UpdateName.cpp
        src/game/rtype/RtypeScene.cpp
        src/game/rtype/RtypeGame.cpp
        src/tools/Logs.cpp
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
        Boost::serialization
        spdlog::spdlog
)
