
#include <qapplication.h>

#define COPASI_MAIN
#include "copasiui3window.h"
#include "utilities/CGlobals.h"
#include "function/CFunctionDB.h"

int main(int argc, char **argv)
{
  Copasi = new CGlobals;

  CReadConfig * pFunctionDB = new CReadConfig("FunctionDB.gps");
  Copasi->pFunctionDB->load(*pFunctionDB);
  delete pFunctionDB;

  QApplication a(argc, argv);

  CopasiUI3Window window;
  a.setMainWidget(&window);

  window.resize(800, 600);
  window.show();

  return a.exec();
}
