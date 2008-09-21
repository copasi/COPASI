// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/main.cpp,v $
//   $Revision: 1.35 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/21 14:12:02 $
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
#ifdef COPASI_SBW_INTEGRATION

// SBW includes
#include "SBW/SBW.h"
#include "copasiversion.h"
#include <sstream>

using namespace SystemsBiologyWorkbench;

#endif // COPASI_SBW_INTEGRATION

int main(int argc, char **argv)
{
#ifdef COPASI_SBW_INTEGRATION

  // first of all we really should clean up the command line
  // taking out any sbw commands as -sbwregister and -sbwmodule

  int nArgC = 0;
  char **oArgV = (char**)malloc(sizeof(char*) * argc); memset(oArgV, 0, sizeof(char*)*argc);

  // remember whether we should register or ...
  bool bSBWRegister = false;

  // run as module
  bool bSBWModule = false;

  for (int i = 0; i < argc; i++)
    {
      if (strcmp(argv[i], "-sbwregister") == 0)
        bSBWRegister = true;
      else if (strcmp(argv[i], "-sbwmodule") == 0)
        bSBWModule = true;
      else
        {
          oArgV[nArgC] = argv[i];
          nArgC++;
        }
    }

  // Next let us define how COPASI will look to the rest of SBW
  std::string sName("COPASI");
  std::string sServiceName("COPASI");
  std::ostringstream os;
  os << "COPASI " << COPASI_VERSION_MAJOR << "." << COPASI_VERSION_MINOR << "." << COPASI_VERSION_BUILD << " (" << COPASI_VERSION_COMMENT << ")";
  std::string sDisplayName = os.str();
  // By belonging to the Analysis category, we tell all other modules that
  // copasi can take SBML files and do *something* with them
  std::string sCategory("Analysis");
  std::string sDescription("COPASI SBW Analyzer - Loads an SBML model into COPASI");
  ModuleImpl modImpl(sName, sDisplayName, UniqueModule, sDescription);

#endif // COPASI_SBW_INTEGRATION

  QApplication a(argc, argv);

  // Parse the commandline options
  try
    {
#ifdef COPASI_SBW_INTEGRATION
      // lets trick the command line parser to believe theré'd be no SBW integration
      COptions::init(nArgC, oArgV);
#else
      COptions::init(argc, argv);
#endif // COPASI_SBW_INTEGRATION
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
      a.setMainWidget(pWindow);

      pWindow->getDataModel()->setQApp(&a);

      //ObjectDebug objwindow;
      //objwindow.show();

#ifdef COPASI_SBW_INTEGRATION

      try
        {

          modImpl.addServiceObject(sServiceName, sDisplayName, sCategory, pWindow, sDescription);

          if (bSBWRegister)
            {
              // in registration mode, we want to register Copasi with SBW but then shut it down again
              modImpl.run(argc, argv);
              return 0;
            }
          SBW::addListener(pWindow);  // this lets SBW ask COPASI to shut down
          modImpl.enableModuleServices(); // here we start the SBW services and give over to QT's main loop
        }
      catch (...)
      {}

#endif // COPASI_SBW_INTEGRATION

      a.exec();
    }

  try // To surpress any access violations during destruction
    {
      pdelete(CCopasiDataModel::Global);
      COptions::cleanup();
      pdelete(CCopasiContainer::Root);
#ifdef COPASI_SBW_INTEGRATION
      // lets delete the memory for the copied command line
      free(oArgV);
#endif // COPASI_SBW_INTEGRATION
    }
  catch (...)
  {}

  return 0;
}
