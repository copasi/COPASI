// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#include <QFileOpenEvent>
#include <QtCore/QString>

#include "CQCopasiApplication.h"
#include "copasiui3window.h"
#include "listviews.h"
#include "copasi/utilities/CCopasiException.h"

#ifdef COPASI_DEBUG
#include <iostream>
#endif

#if (defined(WIN32) && QT_VERSION < QT_VERSION_CHECK(5,0,0))

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

// static
CQCopasiApplication * CQCopasiApplication::instance()
{
  return dynamic_cast< CQCopasiApplication * >(QCoreApplication::instance());
}

CQCopasiApplication::CQCopasiApplication(int & argc, char ** argv):
  QApplication(argc, argv),
  mpMainWindow(NULL),
  mFile(),
  mStarting(true)
{
#if (defined(WIN32) && QT_VERSION < QT_VERSION_CHECK(5,0,0))

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

            if (mFile.isEmpty())
              mFile = static_cast<QFileOpenEvent *>(pEvent)->url().toString();
          }
        else
          {
            // need to take the new file, otherwise whenever the application
            // is open we will re-open the first file that was supposed to be
            // opened.
            mFile = static_cast<QFileOpenEvent *>(pEvent)->file();

            if (mFile.isEmpty())
              mFile = static_cast<QFileOpenEvent *>(pEvent)->url().toString();

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

CopasiUI3Window *
CQCopasiApplication::getMainWindow()
{
  return mpMainWindow;
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
