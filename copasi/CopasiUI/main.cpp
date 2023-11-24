// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

#include <stdexcept>
#include <locale.h>

#include <QApplication>
#include <QLocale>
#include <QDesktopServices>

#define COPASI_MAIN

#include "copasi/copasi.h"

#include "copasi/UI/CQCopasiApplication.h"
#include "copasi/UI/copasiui3window.h"
#include "copasi/UI/DataModelGUI.h"
#include "copasi/UI/CQMessageBox.h"
#include  <copasi/UI/CQUndoTester.h>

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
# include "copasi/UI/qtUtilities.h"
#endif // Darwin

int main(int argc, char *argv[])
{
  // Fix for Issue 1377, if locale is not set to the default one, some
  // numbers will be displayed in the systems default locale:
  setlocale(LC_ALL, "C");
  QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

  // Fix of Issue with Text centering on OSX Mavericks
#ifdef Q_OS_MACX

  // fix Mac OS X 10.9 (mavericks) font issue
  // https://bugreports.qt-project.org/browse/QTBUG-32789
  QFont::insertSubstitution(".Lucida Grande UI", "Lucida Grande");

#endif



#if defined(Q_OS_WIN) && defined(QT_DEBUG)

  qInstallMessageHandler([](QtMsgType type, const QMessageLogContext & ctx, const QString & message) {
    const QString msg = qFormatLogMessage(type, ctx, message);
    // write logs to Output window of Visual Studio
    {
      QString prefix;
      switch (type)
        {
        case QtWarningMsg:
          prefix = "[WARNING] ";
          break;
        case QtCriticalMsg:
          prefix = "[CRITICAL ERROR] ";
          break;
        case QtFatalMsg:
          prefix = "[FATAL ERROR] ";
          break;
        }
      auto msgW = QString(prefix + message + QString("\n")).toStdWString();
      OutputDebugStringW(msgW.c_str());
    }
  });
#endif


  CQCopasiApplication a(argc, argv);

  a.setAttribute(Qt::AA_DontShowIconsInMenus, false);

  Q_INIT_RESOURCE(copasi);

  // Parse the commandline options
  try
    {
      // Create the root container.
      CRootContainer::init(argc, argv, true);
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

  // Create the main application window.
  CopasiUI3Window *pWindow = CopasiUI3Window::create();

#ifdef COPASI_SBW_INTEGRATION

  if (COptions::compareValue("SBWRegister", true))
    goto finish;

#endif // COPASI_SBW_INTEGRATION

  if (pWindow != NULL)
    {
      a.setMainWindow(pWindow);

      if (!COptions::getEnvironmentVariable("COPASI_TEST_UNDO").empty())
        {
          // test undo if environment variable is present
          CQUndoTester*  tester = new CQUndoTester(&a, NULL);
          tester->startTestIn(1000);
        }

      QDesktopServices::setUrlHandler("copasi", pWindow, "slotHandleCopasiScheme");

      a.exec();
                
    }

finish:

  try // To suppress any access violations during destruction works only under Windows
    {
        QDesktopServices::unsetUrlHandler("copasi");
        pdelete(pWindow);
        CRootContainer::destroy();
    }
  catch (...)
    {}

  return 0;
}
