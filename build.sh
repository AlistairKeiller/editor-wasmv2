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

# build
emcmake cmake -G Ninja -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_ENABLE_PROJECTS="clang;lld" \
    -DLLVM_PARALLEL_LINK_JOBS=2 \
    -DLLVM_CCACHE_BUILD=ON \
    -DLLVM_CCACHE_DIR=/tmp/ccache \
    # -DLLVM_ENABLE_LTO=Full
ninja -C build -- compile