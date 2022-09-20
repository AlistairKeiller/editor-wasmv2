cmake_minimum_required(VERSION 3.24.2)

add_subdirectory(llvm-project/llvm)

add_executable(compile main.cpp)
target_link_options(compile PRIVATE
    -sINVOKE_RUN=0
    -sEXPORT_ES6
    -sMODULARIZE
    -sWASM_BIGINT
    -sALLOW_MEMORY_GROWTH
    # -sINITIAL_MEMORY=64MB
    # -sWASMFS=1
    -sMALLOC=emmalloc
    -sENVIRONMENT=worker
    # --embed-file=lib/clang/16.0.0/include
    # --closure 1
)
target_include_directories(compile PRIVATE
    llvm-project/llvm/include
    llvm-project/clang/include
    build/llvm-project/llvm/include
    build/llvm-project/llvm/tools/clang/include
)
target_link_directories(compile PRIVATE build/llvm-project/llvm/lib)
target_link_libraries(compile PRIVATE clangFrontend)