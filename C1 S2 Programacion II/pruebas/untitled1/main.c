#include "rinternals.h"
#include "Rembedded.h"

int main()
{
    int w =0;
    int r_argc;
    char** r_argv;
    r_argv[0] ="7";
    Rf_initEmbeddedR(r_argc,r_argv);
    lang1(install("scripts.R"));
    
    SEXP e;
    PROTECT(e = lang2(install("scripts.R"), mkString("test")));
    R_tryEval(e, R_GlobalEnv, NULL);
    UNPROTECT(1);
    
    Rf_endEmbeddedR(0);
    return 0;
}
