// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/main.cpp,v $
//   $Revision: 1.35.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/10/31 21:24:42 $
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

  if (pWindow != NULL)
    {
#ifdef COPASI_SBW_INTEGRATION
      // Let us define how COPASI will look to the rest of SBW
      std::string sName("COPASI");
      std::string sServiceName("COPASI");
      std::string sDisplayName = "COPASI " + CCopasiDataModel::Global->getVersion()->getVersion();

      // By belonging to the Analysis category, we tell all other modules that
      // COPASI can take SBML files and do *something* with them
      std::string sCategory("Analysis");
      std::string sDescription("COPASI Analyzer - Loads an SBML model into COPASI");

      SystemsBiologyWorkbench::ModuleImpl modImpl(sName, sDisplayName, SystemsBiologyWorkbench::UniqueModule, sDescription);
      modImpl.addServiceObject(sServiceName, sDisplayName, sCategory, pWindow, sDescription);

      try
        {
          if (COptions::compareValue("SBWRegister", true))
            {
              // in registration mode, we want to register COPASI with SBW but then shut it down again
              modImpl.run(argc, argv);
              goto finish;
            }
          if (COptions::compareValue("SBWModule", true))
            {
              SBW::addListener(pWindow);  // this lets SBW ask COPASI to shut down
              modImpl.enableModuleServices(); // here we start the SBW services and give over to QT's main loop
            }
        }
      catch (...)
      {}
#endif // COPASI_SBW_INTEGRATION

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
