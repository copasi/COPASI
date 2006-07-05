/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/main.cpp,v $
   $Revision: 1.27 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/07/05 15:26:02 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <stdexcept>

#include <qapplication.h>
#include <qmessagebox.h>

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
  QApplication a(argc, argv);

  // Parse the commandline options
  try
    {
      COptions::init(argc, argv);
    }
  catch (copasi::option_error & msg)
    {
      QMessageBox::critical(NULL, "Initialization Error",
                            msg.what(),
                            QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);

      return 1;
    }

  // Create the root container.
  CCopasiContainer::init();

  // Create the global data model.
  CCopasiDataModel::Global = new CCopasiDataModel(true);

  CopasiUI3Window window;
  a.setMainWidget(&window);

  window.getDataModel()->setQApp(&a);

  //  window.resize(800, 600);
  //  window.show();

  //  ObjectDebug objwindow;
  //  objwindow.show();

  a.exec();

  pdelete(CCopasiDataModel::Global);
  pdelete(CCopasiContainer::Root);

  return 0;
}
