#define  COPASI_TRACE_CONSTRUCTION

#include "CGlobals.h"
#include "utilities/CCopasiException.h"
#include "function/CFunctionDB.h"
#include "function/CFunction.h"
#include "output/CUDFunctionDB.h"
#include "output/CUDFunction.h"
#include "output/COutputList.h"
#include "output/COutput.h"

CGlobals::CGlobals():
    pFunctionDB(new CFunctionDB),
    pUDFunctionDB(new CUDFunctionDB),
    pOldMetabolites(new CCopasiVectorS < CMetabOld >),
    pOutputList(new COutputList)
{
  try
    {
      ProgramVersion.setVersion(4, 0, 101);
      pFunctionDB->setFilename("FunctionDB.gps");
      pFunctionDB->initialize();
      pModel = NULL;
    }

  catch (CCopasiException Exception)
    {
      std::cout << Exception.getMessage().getText() << std::endl;
    }
}

CGlobals::~CGlobals()
{
  pFunctionDB->cleanup();
  pOldMetabolites->cleanup();
  pdelete(pFunctionDB);
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
