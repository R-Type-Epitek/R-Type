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

default: start
