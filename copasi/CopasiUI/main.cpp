// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/main.cpp,v $
//   $Revision: 1.49 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2012/05/03 14:50:01 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <stdexcept>

#include <qapplication.h>

#define COPASI_MAIN

#include "copasi.h"

#include "UI/CQCopasiApplication.h"
//#include "UI/objectdebug.h"
#include "UI/copasiui3window.h"
#include "UI/DataModelGUI.h"
#include "UI/CQMessageBox.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "function/CFunctionDB.h"
#include "function/CFunction.h"
#include "commandline/COptionParser.h"
#include "commandline/COptions.h"

#ifdef COPASI_SBW_INTEGRATION
// SBW includes
#include "SBW/SBW.h"
#include <sstream>
#endif // COPASI_SBW_INTEGRATION

#ifdef Darwin
# include <QDir>
# include "UI/qtUtilities.h"
#endif // Darwin

int main(int argc, char *argv[])
{
  CQCopasiApplication a(argc, argv);

  a.setAttribute(Qt::AA_DontShowIconsInMenus, false);

  Q_INIT_RESOURCE(copasi);

  // Parse the commandline options
  try
    {
      // Create the root container.
      CCopasiRootContainer::init(argc, argv, true);
    }
  catch (copasi::option_error & msg)
    {
      CQMessageBox::critical(NULL, "Initialization Error",
                             msg.what(),
                             QMessageBox::Ok , QMessageBox::Ok);

      return 1;
    }

#ifdef Darwin
  std::string PluginDir;

  COptions::getValue("CopasiDir", PluginDir);
  PluginDir += "/Contents/plugins";

  QApplication::setLibraryPaths(QStringList(FROM_UTF8(PluginDir)));
#endif // Darwin

  // Create the global data model.
  CCopasiRootContainer::addDatamodel();

  // Create the main application window.
  CopasiUI3Window *pWindow = CopasiUI3Window::create();

#ifdef COPASI_SBW_INTEGRATION

  if (COptions::compareValue("SBWRegister", true))
    goto finish;

#endif // COPASI_SBW_INTEGRATION

  if (pWindow != NULL)
    {
      // ObjectDebug objwindow;
      // objwindow.show();


      a.setMainWindow(pWindow);
      a.exec();
    }

finish:

  try // To suppress any access violations during destruction works only under Windows
    {
      CCopasiRootContainer::destroy();
    }
  catch (...)
    {}

  return 0;
}
