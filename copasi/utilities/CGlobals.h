#ifndef COPASI_CGlobals
#define COPASI_CGlobals

#include <string>

#include "output/COutputList.h"
#include "model/CMetab.h"
#include "function/CFunctionDB.h"
#include "CVersion.h"
#include "output/output.h"
#include "model/CCompartment.h"
#include "model/CMoiety.h"

class CGlobals
  {
    // Attributes

  public:
    /**
     *
     */
    CVersion ProgramVersion;

    /**
     *
     */
    CFunctionDB FunctionDB;
    CCompartment Compartmentfile;
    /**
     *
     */
    CUDFunctionDB UDFunctionDB;

    /**
     *  This is a hack at the moment to be able to read old configuration files
     */
    CCopasiVectorS < CMetabOld > OldMetabolites;

    /**
     *
     */
    C_FLOAT64 DefaultConc;

    /**
     *
     */
    COutputList OutputList;

    /**
     *
     */
    vector <char *> Arguments;

    /**
     *  This a hack to be able to read old configaration files output information
     */
    CModel * Model;

  public:

    // Operations

  public:
    /**
     *
     */
    CGlobals();

    /**
     *
     */
    ~CGlobals();

    /**
     *
     */
    void setArguments(C_INT argc, char *argv[]);
  };

#ifdef COPASI_MAIN
CGlobals *Copasi = NULL;
#else
extern CGlobals *Copasi;
#endif // __MAIN

#endif // COPASI_CGlobals
