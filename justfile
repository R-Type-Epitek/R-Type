# Fetch all remote git repo
#git clone --recurse-submodules
init-remote:
    git submodule update --init --recursive
    git fetch --all

# Init vcpckg remote
init-vcpckg:
    ./vcpkg/bootstrap-vcpkg.sh
    set VCPKG_ROOT="${PWD}/vcpkg/"

# Build project and depenedencies
build:
    cmake -DCMAKE_TOOLCHAIN_FILE:STRING="./vcpkg/scripts/buildsystems/vcpkg.cmake" -S . -B ./build
    cmake --build build

# Start all
start: init-remote init-vcpckg build
    @echo "Done"

test:
    cmake -DBUILD_TESTS=ON -DCMAKE_TOOLCHAIN_FILE:STRING="./vcpkg/scripts/buildsystems/vcpkg.cmake" -S . -B ./build
    cmake --build build
    cd build/server && ctest

generate-doc:
    doxygen docs/Doxyfile
    @echo -e "\nfile://$(realpath docs/technical/html/index.html)"

clang-format-run-dir path:
    find {{path}} -name "*.cpp" -o -name "*.hpp" | xargs clang-format -style=file -i

clang-format-run:
    just clang-format-run-dir ./client
    just clang-format-run-dir ./server
    just clang-format-run-dir ./gameEngine

default: start
