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
  CReadConfig * pFunctionDB = new CReadConfig("FunctionDB.gps");
  Copasi->pFunctionDB->load(*pFunctionDB);
  delete pFunctionDB;

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
