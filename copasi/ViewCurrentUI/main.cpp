// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <stdexcept>

#include <QtGui/QApplication>
#include <QtCore/QString>

#define COPASI_MAIN

#include "copasi/copasi.h"

#include "copasi/UI/CQCopasiApplication.h"
#include "copasi/UI/copasiui3window.h"
#include "copasi/UI/DataModelGUI.h"
#include "copasi/UI/CQMessageBox.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CFunction.h"
#include "copasi/commandline/COptionParser.h"
#include "copasi/commandline/COptions.h"

#ifdef COPASI_SBW_INTEGRATION
// SBW includes
#include "SBW/SBW.h"
#include <sstream>
#endif // COPASI_SBW_INTEGRATION

#ifdef Darwin
# include <QtCore/QDir>
# include "UI/qtUtilities.h"
#endif // Darwin

#include <worker.h>
#include <arguments.h>

int main(int argc, char *argv[])
{
  CQCopasiApplication a(argc, argv);

  // parse args
  Arguments args(argc, argv);

  if (args.handleCommandLine())
    {
      return 0;
    }

  a.setAttribute(Qt::AA_DontShowIconsInMenus, false);

  Q_INIT_RESOURCE(copasi);

  // Parse the commandline options
  try
    {
      // Create the root container but don't pass in any args past the executable name
      CRootContainer::init(1, argv, true);
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
  CRootContainer::addDatamodel();

  // instantiate model and apply all changes
  args.prepareModel();

  // Create the main application window.
  CopasiUI3Window *pWindow = CopasiUI3Window::create();
  Worker* pWorker = NULL;
#ifdef COPASI_SBW_INTEGRATION

  if (COptions::compareValue("SBWRegister", true))
    goto finish;

#endif // COPASI_SBW_INTEGRATION

  if (pWindow != NULL)
    {
      a.setMainWindow(pWindow);

      // pass control to the worker
      if (args.isValid())
        pWorker = new Worker(pWindow, &args);

      a.exec();
    }

finish:

  try // To suppress any access violations during destruction works only under Windows
    {
      if (pWorker != NULL)
        {
          delete pWorker;
          pWorker = NULL;
        }

      CRootContainer::destroy();
    }
  catch (...)
    {}

  return 0;
}
