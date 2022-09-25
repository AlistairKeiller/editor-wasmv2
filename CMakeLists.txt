cmake_minimum_required(VERSION 3.24.2)

add_link_options(-sINITIAL_MEMORY=64MB)

add_subdirectory(llvm-project/llvm)

add_executable(compile main.cpp)
target_link_options(compile PRIVATE
    -sEXPORT_ES6
    -sMODULARIZE
    -sWASM_BIGINT
    -sALLOW_MEMORY_GROWTH
    # -sWASMFS
    # -sINITIAL_MEMORY=64MB
    -sEXPORTED_FUNCTIONS=_init,_compile
    -sEXPORTED_RUNTIME_METHODS=FS
    -sMALLOC=emmalloc
    -sENVIRONMENT=worker
    --embed-file=sysroot
    --embed-file=llvm-project/llvm/lib/clang/16.0.0/include
)
target_include_directories(compile PRIVATE
    llvm-project/llvm/include
    llvm-project/clang/include
    build/llvm-project/llvm/include
    build/llvm-project/llvm/tools/clang/include
)
target_link_directories(compile PRIVATE build/llvm-project/llvm/lib)
target_link_libraries(compile PRIVATE
    clangCodeGen
    clangFrontend
    LLVMWebAssemblyCodeGen
    LLVMWebAssemblyAsmParser
    clang # to generate clang include files
)