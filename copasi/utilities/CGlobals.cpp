/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/Attic/CGlobals.cpp,v $
   $Revision: 1.25 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:35:31 $
   End CVS Header */

#define  COPASI_TRACE_CONSTRUCTION

#include "CGlobals.h"
#include "CCopasiException.h"
#include "CMethodParameter.h"
#include "function/CFunctionDB.h"
#include "function/CFunction.h"
#include "output/CUDFunctionDB.h"
#include "output/CUDFunction.h"
#include "output/COutputList.h"
#include "output/COutput.h"

CGlobals::CGlobals():
    pFunctionDB(new CFunctionDB("Kinetic Functions")),
    pUDFunctionDB(new CUDFunctionDB),
    pOldMetabolites(new CCopasiVectorS < CMetabOld >),
    pOutputList(new COutputList)
{
  try
    {
      ProgramVersion.setVersion(4, 0, 101);
      pFunctionDB->setFilename("FunctionDB.xml");
      pModel = NULL;
    }

  catch (CCopasiException Exception)
    {
      std::cout << Exception.getMessage().getText() << std::endl;
    }
}

CGlobals::~CGlobals()
{
  pdelete(pFunctionDB);
  //  already be called inside CFunctionDB deconstructor
  //  pFunctionDB->cleanup();
  pOldMetabolites->cleanup();
  pdelete(pUDFunctionDB);
  pdelete(pOldMetabolites);
  pdelete(pOutputList);
}

void CGlobals::setArguments(C_INT argc, char *argv[])
{
  C_INT i, imax = argc;
  Arguments.resize(imax);

  for (i = 0; i < imax; i++)
    Arguments[i] = argv[i];
}

// CGlobals Copasi;
