set-vcpckg:
    git submodule update --init --recursive
    ./vcpkg/bootstrap-vcpkg.sh
    set VCPKG_ROOT="${PWD}/vcpkg/"

cmake:
    cmake -DCMAKE_TOOLCHAIN_FILE:STRING="./vcpkg/scripts/buildsystems/vcpkg.cmake" -S . -B ./build
    cmake --build build
