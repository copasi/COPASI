/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/Attic/CGlobals.h,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:35:33 $
   End CVS Header */

#ifndef COPASI_CGlobals
#define COPASI_CGlobals

#include <string>
#include <vector>

#include "copasi.h"
#include "CVersion.h"

template < class CType > class CCopasiVectorS;
class CMetabOld;
class CFunctionDB;
class CUDFunctionDB;
class CModel;
class COutputList;

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
    CFunctionDB * pFunctionDB;

    /**
     *
     */
    CUDFunctionDB * pUDFunctionDB;
    // CCompartment Compartmentfile;

    /**
     *  This is a hack at the moment to be able to read old configuration files
     */
    CCopasiVectorS < CMetabOld > * pOldMetabolites;

    /**
     *
     */
    COutputList * pOutputList;

    /**
     *
     */
    std::vector <char *> Arguments;

    /**
     *  This a hack to be able to read old configaration files output information
     */
    CModel * pModel;

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
