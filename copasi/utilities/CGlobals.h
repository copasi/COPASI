#ifndef COPASI_CGlobals
#define COPASI_CGlobals

#include <string>

#include "output/COutputList.h"
#include "model/CMetab.h"
#include "function/CFunctionDB.h"
#include "CVersion.h"
#include "output/output.h"

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

#ifdef __MAIN
CGlobals *Copasi = NULL;
#else
extern CGlobals *Copasi;
#endif // __MAIN

#endif // COPASI_CGlobals

