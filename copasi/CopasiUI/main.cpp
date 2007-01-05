/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/main.cpp,v $
   $Revision: 1.26.2.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2007/01/05 18:32:15 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <stdexcept>

#include <qapplication.h>

#define COPASI_MAIN

#include "copasi.h"
#include "copasilicense.h"
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

  // Create the root container.
  CCopasiContainer::init();

  // Create the global data model.
  CCopasiDataModel::Global = new CCopasiDataModel(true);

  QApplication a(argc, argv);

  // Create the main application window.
  CopasiUI3Window *pWindow = CopasiUI3Window::create();

  if (pWindow != NULL)
    {
      a.setMainWidget(pWindow);

      pWindow->getDataModel()->setQApp(&a);

      //  ObjectDebug objwindow;
      //  objwindow.show();

      a.exec();
    }

  pdelete(CCopasiDataModel::Global);
  pdelete(CCopasiContainer::Root);

  return 0;
}
