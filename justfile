set-vcpckg:
    ./vcpkg/bootstrap-vcpkg.sh
    set VCPKG_ROOT="${PWD}/vcpkg/"

build-dependencies:
    ./vcpkg/vcpkg install

cmake:
    cmake -DCMAKE_TOOLCHAIN_FILE:STRING="./vcpkg/scripts/buildsystems/vcpkg.cmake" -S . -B ./build
    cmake --build build
