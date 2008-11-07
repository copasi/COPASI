// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/main.cpp,v $
//   $Revision: 1.35.2.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/07 17:26:58 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <stdexcept>

#include <qapplication.h>

#define COPASI_MAIN

#include "copasi.h"
#include "copasilicense.h"
#include "copasiversion.h"

#include "UI/copasiui3window.h"
#include "UI/objectdebug.h"
#include "UI/DataModelGUI.h"
#include "UI/CQMessageBox.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "function/CFunctionDB.h"
#include "function/CFunction.h"
#include "commandline/COptionParser.h"
#include "commandline/COptions.h"
#include "utilities/CVersion.h"

#ifdef COPASI_SBW_INTEGRATION
// SBW includes
#include "SBW/SBW.h"
#include <sstream>
#endif // COPASI_SBW_INTEGRATION

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
      CQMessageBox::critical(NULL, "Initialization Error",
                             msg.what(),
                             QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);

      return 1;
    }

  // Create the root container.
  CCopasiContainer::init();

  // Create the global data model.
  CCopasiDataModel::Global = new CCopasiDataModel(true);

  // Create the main application window.
  CopasiUI3Window *pWindow = CopasiUI3Window::create();

#ifdef COPASI_SBW_INTEGRATION
  if (COptions::compareValue("SBWRegister", true))
    goto finish;
#endif // COPASI_SBW_INTEGRATION

  if (pWindow != NULL)
    {
      a.setMainWidget(pWindow);
      pWindow->getDataModel()->setQApp(&a);
      a.exec();
    }

finish:
  try // To suppress any access violations during destruction
    {
      pdelete(CCopasiDataModel::Global);
      COptions::cleanup();
      pdelete(CCopasiContainer::Root);
    }
  catch (...)
  {}

  return 0;
}
