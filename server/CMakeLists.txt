#[===[ SERVER ]===]

set(EXEC_SERVER "r-type_server")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)
add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

find_package(Boost REQUIRED COMPONENTS system thread regex)


add_executable(${EXEC_SERVER}
        src/network/Client.cpp
        src/network/UDPServer.cpp
        src/main.cpp
)

target_include_directories(${EXEC_SERVER}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

target_compile_options(${EXEC_SERVER}
        PRIVATE
        -Wall
        -Wextra
        -fno-gnu-unique
        -ggdb3
)

target_link_libraries(${EXEC_SERVER}
        PRIVATE
        Boost::boost
        Boost::system
)
