/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/Attic/CGlobals.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:04 $
   End CVS Header */

#ifndef COPASI_CGlobals
#define COPASI_CGlobals

#include <string>
#include <vector>

#include "CVersion.h"

template < class CType > class CCopasiVectorS;
class CMetabOld;
class CFunctionDB;
//class CUDFunctionDB;
class CModel;
//class COutputList;
class CReportDefinitionVector;
//class CPlotSpecVector;

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
    //CUDFunctionDB * pUDFunctionDB;
    // CCompartment Compartmentfile;

    /**
     *  This is a hack at the moment to be able to read old configuration files
     */
    CCopasiVectorS < CMetabOld > * pOldMetabolites;

    /**
     *
     */ 
    //COutputList * pOutputList;

    /**
     *
     */
    std::vector <char *> Arguments;

    /**
     *  This a hack to be able to read old configaration files output information
     */
    CModel * pModel;

    CReportDefinitionVector * pReportDefinitions;
    //    CPlotSpecVector *;

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
