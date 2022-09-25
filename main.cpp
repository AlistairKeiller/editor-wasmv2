#include "clang/Frontend/CompilerInstance.h"
#include "llvm/Support/TargetSelect.h"

std::unique_ptr<CompilerInstance> Clang;
std::unique_ptr obj<EmitObjAction> Obj;

void init()
{
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmPrinters();
    llvm::InitializeAllAsmParsers();

    Clang = std::unique_ptr<CompilerInstance>(new CompilerInstance());
    Obj = std::unique_ptr obj<EmitObjAction>(new EmitObjAction());

    Clang->createDiagnostics();

    CompilerInvocation::setLangDefaults(
        Clang->getLangOpts(), InputKind{InputKind::CXX, InputKind::Source},
        Triple{"wasm32-wasi"}, compiler->getPreprocessorOpts(),
        LangStandard::lang_cxx2a);
    
    Clang->getFrontendOpts().Inputs.push_back(FrontendInputFile{"main.cpp", InputKind{InputKind::CXX, InputKind::Source}});
    Clang->getFrontendOpts().OutputFile = "main.obj";
    
    Clang->getHeaderSearchOpts().UseBuiltinIncludes = false;
    Clang->getHeaderSearchOpts().UseStandardSystemIncludes = false;
    Clang->getHeaderSearchOpts().UseStandardCXXIncludes = false;
    Clang->getHeaderSearchOpts().AddPath("include/clang", false, true);
    
    Clang->getCodeGenOpts().CodeModel = "default";
    Clang->getCodeGenOpts().RelocationModel = "static";
    Clang->getCodeGenOpts().ThreadModel = "single";
    Clang->getCodeGenOpts().OptimizationLevel = 2; // -Os
    Clang->getCodeGenOpts().OptimizeSize = 1;      // -Os
    Clang->getLangOpts().Optimize = 1;
    Clang->getLangOpts().OptimizeSize = 1;
    Clang->getLangOpts().DollarIdents = false;
    Clang->getLangOpts().CoroutinesTS = true;
    Clang->getLangOpts().DoubleSquareBracketAttributes = true;
    Clang->getLangOpts().WCharIsSigned = true;
    Clang->getLangOpts().ConceptsTS = true;
    Clang->getLangOpts().MathErrno = false;
    Clang->getLangOpts().Deprecated = true;
    Clang->getLangOpts().setValueVisibilityMode(HiddenVisibility);
    Clang->getLangOpts().setTypeVisibilityMode(HiddenVisibility);
    Clang->getLangOpts().RTTI = true;
    Clang->getLangOpts().RTTIData = true;
    Clang->getLangOpts().Exceptions = true;
    Clang->getLangOpts().CXXExceptions = true;
    
    compiler->getTargetOpts().Triple = "wasm32-wasi";
    compiler->getTargetOpts().HostTriple = "wasm32-wasi";
}

int compile()
{
    return Clang->ExecuteAction(*Obj);
}
