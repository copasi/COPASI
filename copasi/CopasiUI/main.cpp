/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/main.cpp,v $
   $Revision: 1.19 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/24 15:56:39 $
   End CVS Header */

#include <stdexcept>

#include <qapplication.h>

#define COPASI_MAIN
#include "copasiversion.h"

#include "copasiui3window.h"
#include "objectdebug.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "function/CFunctionDB.h"
#include "function/CFunction.h"
#include "commandline/COptionParser.h"
#include "commandline/COptions.h"
#include "DataModelGUI.h"

int main(int argc, char **argv)
{
  // Create the root container.
  CCopasiContainer::init();

  // Create the global data model.
  CCopasiDataModel::Global = new CCopasiDataModel(true);

  // Parse the commandline options
  try
    {
      COptions::init(argc, argv);
    }
  catch (copasi::option_error & msg)
    {
      std::cout << msg.what() << std::endl;
      return 1;
    }

  QApplication a(argc, argv);

  CopasiUI3Window window;
  a.setMainWidget(&window);
  window.getDataModel()->setQApp(&a);

  window.resize(800, 600);
  window.show();

  //ObjectDebug objwindow;
  //objwindow.show();

  a.exec();

  pdelete(CCopasiDataModel::Global);
  pdelete(CCopasiContainer::Root);

  return 0;
}
