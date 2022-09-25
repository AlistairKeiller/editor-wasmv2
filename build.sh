#!/bin/sh
set -e

# install emscripten
cd emsdk
./emsdk install latest
./emsdk activate latest
. ./emsdk_env.sh
cd ..

# download sysroot
wget -qO- https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-16/wasi-sysroot-16.0.tar.gz | tar -xz
wget -qO- https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-16/libclang_rt.builtins-wasm32-wasi-16.0.tar.gz | tar -xz
mkdir -p build/sysroot/include
mkdir -p build/sysroot/lib
cp -r wasi-sysroot/include/* build/sysroot/include/
cp -r wasi-sysroot/lib/wasm32-wasi/* build/sysroot/lib/
cp -r lib/wasi/libclang_rt.builtins-wasm32.a build/sysroot/lib/

# build
CXXFLAGS="-Dwait4=__syscall_wait4" \
emcmake cmake -G Ninja -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_ENABLE_PROJECTS="clang;lld" \
    -DLLVM_TARGETS_TO_BUILD=WebAssembly \
    -DLLVM_DEFAULT_TARGET_TRIPLE=wasm32-wasi \
    -DLLVM_TARGET_ARCH=wasm32-emscripten \
    -DLLVM_INCLUDE_BENCHMARKS=OFF \
    -DLLVM_INCLUDE_EXAMPLES=OFF \
    -DLLVM_INCLUDE_TESTS=OFF \
    -DLLVM_ENABLE_THREADS=OFF \
    -DLLVM_PARALLEL_LINK_JOBS=2 \
    -DLLVM_CCACHE_BUILD=ON \
    -DLLVM_CCACHE_DIR=/tmp/ccache \
    # -DLLVM_ENABLE_LTO=Full
ninja -C build -- compile