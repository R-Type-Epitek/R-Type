cmake_minimum_required(VERSION 3.5.1)


project(rtype-parent-cmake CXX)

option(BUILD_TESTS "Build tests" ON)

set(CMAKE_CXX_STANDARD 20)
set(Boost_NO_WARN_NEW_VERSIONS 1)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(RTYPE_GAME_ENGINE_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/gameEngine/include CACHE PATH "Path to game engine include directory")

#[===[ DEPENDENCIES ]===]
find_package(SFML
        REQUIRED COMPONENTS
        system
        window
        graphics
        network
        audio
)

add_definitions("-DBOOST_ALLOW_DEPRECATED_HEADERS")
add_definitions("-DBOOST_BIND_GLOBAL_PLACEHOLDERS")
find_package(Boost
        REQUIRED COMPONENTS
        system
        thread
        regex
)
find_package(Threads REQUIRED)
find_package(spdlog CONFIG REQUIRED)
if(BUILD_TESTS)
    find_package(GTest REQUIRED)
endif ()
#[===[ END DEPENDENCIES ]===]

#[===[ GAME ENGINE ]===]
add_subdirectory(gameEngine)

#[===[ SERVER ]===]
add_subdirectory(server)

#[===[ CLIENT ]===]
add_subdirectory(client)

#[===[ EXTERN ]===]
#add_subdirectory(lib/etc)
