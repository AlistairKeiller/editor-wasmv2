#include "clang/Frontend/CompilerInstance.h"
#include "clang/CodeGen/CodeGenAction.h"
#include "llvm/Support/TargetSelect.h"

using namespace clang;

// std::unique_ptr<CompilerInstance> Clang;
std::unique_ptr<EmitObjAction> Obj;

extern "C" void init()
{
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmPrinters();
    llvm::InitializeAllAsmParsers();

    Obj = std::unique_ptr<EmitObjAction>(new EmitObjAction());

    // Clang = std::unique_ptr<CompilerInstance>(new CompilerInstance());
    // Clang->createDiagnostics();
    // Clang->getHeaderSearchOpts().AddPath("include/clang", frontend::System, false, true);
    // Clang->getFrontendOpts().Inputs.push_back(FrontendInputFile("main.cpp", Language::CXX));
    // Clang->getFrontendOpts().OutputFile = "main.obj";
    // Clang->getTargetOpts().Triple = "wasm32-wasi";
}

extern "C" int compile()
{
    // I dont understand why we need to create a new CompilerInstance every call
    std::unique_ptr<CompilerInstance> Clang(new CompilerInstance());
    Clang->createDiagnostics();
    Clang->getHeaderSearchOpts().AddPath("sysroot/include", frontend::System, false, true);
    Clang->getHeaderSearchOpts().AddPath("sysroot/include/c++/v1", frontend::System, false, true);
    Clang->getHeaderSearchOpts().AddPath("llvm-project/llvm/lib/clang/16.0.0/include", frontend::System, false, true);
    Clang->getFrontendOpts().Inputs.push_back(FrontendInputFile("main.cpp", Language::CXX));
    Clang->getFrontendOpts().OutputFile = "main.obj";
    Clang->getTargetOpts().Triple = "wasm32-wasi";
    return Clang->ExecuteAction(*Obj);
}
