/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/main.cpp,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/28 22:25:05 $
   End CVS Header */

#include <qapplication.h>

#define COPASI_MAIN
#include "copasiversion.h"

#include "copasiui3window.h" 
//#include "objectdebug.h"

#include "utilities/CGlobals.h"
#include "function/CFunctionDB.h"
#include "function/CFunction.h"
#include "commandline/COptionParser.h"
#include "commandline/COptions.h"

int main(int argc, char **argv)
{
  CCopasiContainer::init();

  Copasi = new CGlobals;
  Copasi->pFunctionDB->load();
  Copasi->ProgramVersion.setVersion(COPASI_VERSION_MAJOR,
                                    COPASI_VERSION_MINOR,
                                    COPASI_VERSION_BUILD);

  // Parse the commandline options
  COptions::init(argc, argv);

  QApplication a(argc, argv);

  CopasiUI3Window window;
  a.setMainWidget(&window);
  window.getDataModel()->setQApp(&a);

  window.resize(640, 480);
  window.show();

  //ObjectDebug objwindow;
  //objwindow.show();

  a.exec();

  pdelete(Copasi);
  pdelete(CCopasiContainer::Root);

  return 0;
}
