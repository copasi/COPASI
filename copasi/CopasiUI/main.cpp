/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/main.cpp,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:44 $
   End CVS Header */

#include <qapplication.h>
#define COPASI_MAIN
#include "copasiui3window.h" 
//#include "objectdebug.h"

#include "utilities/CGlobals.h"
#include "function/CFunctionDB.h"
#include "function/CFunction.h"

int main(int argc, char **argv)
{
  CCopasiContainer::init();

  Copasi = new CGlobals;
  Copasi->pFunctionDB->load();

  QApplication a(argc, argv);

  CopasiUI3Window window;
  a.setMainWidget(&window);

  window.resize(640, 480);
  window.show();

  //ObjectDebug objwindow;
  //objwindow.show();

  a.exec();

  pdelete(Copasi);
  pdelete(CCopasiContainer::Root);

  return 0;
}
