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
};

extern CGlobals Copasi;

#endif // COPASI_CGlobals

