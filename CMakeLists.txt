add_link_options(-sERROR_ON_UNDEFINED_SYMBOLS=0 -sINITIAL_MEMORY=64MB)

add_subdirectory(llvm-project/llvm)

add_executable(compile main.cpp)
# target_include_directories(compile PRIVATE llvm-project/clang/include)
# target_link_libraries(compile PRIVATE clangFrontend)