// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QFileDialog>

#include "copasi/copasi.h"

#include "copasi/UI/CopasiFileDialog.h"
#include "copasi/UI/qtUtilities.h"
#include "copasi/UI/CQMessageBox.h"
#include "copasi/UI/copasiui3window.h"
#include "copasi/UI/listviews.h"

#include "copasi/commandline/COptions.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasi/core/CRootContainer.h"

#include <QRegExp>

#ifdef DEBUG_UI
#include <QtCore/QtDebug>
#endif

// static
QString CopasiFileDialog::StartWith(const QString & startWith)
{
  QString WorkingDirectory = FROM_UTF8(CRootContainer::getConfiguration()->getWorkingDirectory());

  if (startWith.isNull())
    {
      return WorkingDirectory;
    }
  else if (CDirEntry::dirName(TO_UTF8(startWith)) == "")
    {
      return WorkingDirectory + "/" + startWith;
    }

  return startWith;
}

// static
void CopasiFileDialog::openExampleDir(QWidget * parent)
{
  std::string ExampleDir;
  COptions::getValue("ExampleDir", ExampleDir);

  if (CDirEntry::isDir(ExampleDir))
    CRootContainer::getConfiguration()->setWorkingDirectory(ExampleDir);
  else
    CQMessageBox::information(parent, "Directory Not Found", FROM_UTF8(ExampleDir),
                              QMessageBox::Ok, QMessageBox::Ok);
}

// static
QString CopasiFileDialog::getOpenFileName(QWidget * parent,
    const char * /* name */,
    const QString & startWith,
    const QString & filter,
    const QString & caption,
    QString * pSelectedFilter,
    QFileDialog::Options options)
{
  QString newFilter = filter;

  if (filter.indexOf("(*)") < 0)
    newFilter += ";;Any File (*)";

  QString newFile = QFileDialog::getOpenFileName(parent,
                    caption,
                    StartWith(startWith),
                    newFilter,
                    pSelectedFilter,
                    options);

  if (newFile != "")
    CRootContainer::getConfiguration()->setWorkingDirectory(CDirEntry::dirName(TO_UTF8(newFile)));

  return newFile;
}

// static
QString CopasiFileDialog::getSaveFileName(QWidget * parent,
    const char * /* name */,
    const QString & startWith,
    const QString & filter,
    const QString & caption,
    QString * pSelectedFilter,
    QFileDialog::Options options)
{
  QString newFile, newFilter = filter;
  bool fileValid;

  if (!pSelectedFilter)
    pSelectedFilter = new QString("");

  if (filter.indexOf("(*)") < 0)
    newFilter += ";;Any File (*)";

  do
    {
      fileValid = true;
      newFile = QFileDialog::getSaveFileName(parent,
                                             caption,
                                             StartWith(startWith),
                                             newFilter, pSelectedFilter,
                                             QFileDialog::DontConfirmOverwrite | options);

      if (newFile != "")
        CRootContainer::getConfiguration()->setWorkingDirectory(CDirEntry::dirName(TO_UTF8(newFile)));
      else
        return QString();

      if (pSelectedFilter->indexOf("(*)") >= 0)
        {
          QString fileName = FROM_UTF8(CDirEntry::fileName(TO_UTF8(newFile)));
          QString suffix = FROM_UTF8(CDirEntry::suffix(TO_UTF8(newFile)));

          if (!suffix.length())
            {
              fileValid = true;
            }
          else
            {
              QRegExp rx("\\.\\S{1,4}$");

              if (rx.indexIn(fileName) < 0)
                {
                  CQMessageBox::information(parent, "Save File Error",
                                            "Filename can have an extension 1 to 4 characters long.",
                                            QMessageBox::Ok, QMessageBox::Ok);
                  fileValid = false;
                  continue;
                }

              QRegExp rxDigits("\\.\\d{1,4}$");

              if (rxDigits.indexIn(fileName) > 0)
                {
                  CQMessageBox::information(parent, "Save File Error",
                                            "All characters in the file extension cannot be digits.",
                                            QMessageBox::Ok, QMessageBox::Ok);
                  fileValid = false;
                  continue;
                }
            }
        }
    }
  while (fileValid == false);

#ifdef DEBUG_UI
//  qDebug() << "user selected Filter = " << usersFilter;
  qDebug() << "user's Filter = " << *pSelectedFilter;
//  qDebug() << "correct extension = " << correctExt;
//  qDebug() << "filename = " << newFile;
#endif

  return newFile;
}

// static
QString CopasiFileDialog::getDefaultFileName(const QString & suffix)
{
  QString Default = "untitled" + suffix;

  CopasiUI3Window * pMainWindow = CopasiUI3Window::getMainWindow();

  if (pMainWindow == NULL)
    return Default;

  ListViews * pMainWidget =  pMainWindow->getMainWidget();

  if (pMainWidget == NULL)
    return Default;

  CDataModel * pDataModel = pMainWidget->getDataModel();

  if (pDataModel == NULL)
    return Default;

  return FROM_UTF8(pDataModel->getDefaultFileName(TO_UTF8(suffix)));
}
