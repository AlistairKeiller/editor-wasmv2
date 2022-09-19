add_executable(compile main.cpp)
# target_include_directories(compile PRIVATE llvm-project/clang/include)
# target_link_libraries(compile PRIVATE clangFrontend)

add_subdirectory(llvm-project/llvm)