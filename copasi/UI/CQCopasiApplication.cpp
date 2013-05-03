// Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include <QFileOpenEvent>
#include <QString>

#include "CQCopasiApplication.h"
#include "copasiui3window.h"
#include "listviews.h"
#include "utilities/CCopasiException.h"

#ifdef WIN32

#include <QWindowsVistaStyle>

bool IsWindows8()
{

  OSVERSIONINFOEX osvi = {0};
  DWORDLONG mask = 0;

  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
  osvi.dwMajorVersion = 6;
  osvi.dwMinorVersion = 2;

  VER_SET_CONDITION(mask, VER_MAJORVERSION, VER_GREATER_EQUAL);
  VER_SET_CONDITION(mask, VER_MINORVERSION, VER_GREATER_EQUAL);

  return VerifyVersionInfo(&osvi,
                           VER_MAJORVERSION | VER_MINORVERSION,
                           mask
                          );
}

#endif

CQCopasiApplication::CQCopasiApplication(int & argc, char ** argv):
  QApplication(argc, argv),
  mpMainWindow(NULL),
  mFile(),
  mStarting(true)
{
#if WIN32

  if (IsWindows8())
    setStyle(new QWindowsVistaStyle);

#endif

// Alter styles using Qt's CSS-like mechanism
QString globalStyleSheet =
"QLineEdit[readOnly=\"true\"] {\n"  // When readOnly
"  color: gray;\n"                  // make text gray and
"  border: false;\n"                // remove box border.
"}\n";   //can add future items after this (move semicolon down)     

qApp->setStyleSheet(globalStyleSheet);


}

CQCopasiApplication::~CQCopasiApplication()
{
}

// virtual
bool CQCopasiApplication::event(QEvent * pEvent)
{
  switch (pEvent->type())
    {
      case QEvent::FileOpen:

        if (mStarting)
          {
            mFile = static_cast<QFileOpenEvent *>(pEvent)->file();
          }
        else
          {
            // need to take the new file, otherwise whenever the application
            // is open we will re-open the first file that was supposed to be
            // opened.
            mFile = static_cast<QFileOpenEvent *>(pEvent)->file();
            mpMainWindow->slotFileOpen(mFile);
          }

        pEvent->accept();
        return true;

        break;

      default:
        break;
    }

  return QApplication::event(pEvent);
}

void CQCopasiApplication::setMainWindow(CopasiUI3Window * pMainWindow)
{
  mpMainWindow = pMainWindow;

  processEvents();

  mpMainWindow->openInitialDocument(mFile);
  mStarting = false;
}

#ifdef COPASI_DEBUG
bool CQCopasiApplication::notify(QObject * pObject, QEvent * pEvent)
{
  bool success = false;

  try
    {
      success = QApplication::notify(pObject, pEvent);
    }

  catch (CCopasiException & e)
    {
      std::cout << "Unhandled Exception: " << e.getMessage().getText() << std::endl;
    }

  catch (...)
    {
      std::cout << "Unhandled Exception: Unknown Source" << std::endl;
    }

  return success;
}
#endif
