#include "CGlobals.h"
#include "utilities.h"

CGlobals::CGlobals()
{
  try
    {
      ProgramVersion.setVersion(4,0,101);
      FunctionDB.setFilename("FunctionDB.gps");
      FunctionDB.initialize();
      
      DefaultConc = 0.0;
      return;
      CReadConfig inbuf("gps/DANNY.GPS");
      OutputList.load(inbuf);
    }
  catch (CCopasiException Exception)
    {
      cout << Exception.getMessage().getText() << endl;
    }
}

CGlobals::~CGlobals()
{
  FunctionDB.cleanup();
}

CGlobals Copasi;
