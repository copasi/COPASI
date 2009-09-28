// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiFileDialog.cpp,v $
//   $Revision: 1.28 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/09/28 14:51:54 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qfiledialog.h>

#include "copasi.h"

#include "CopasiFileDialog.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"

#include "commandline/COptions.h"
#include "utilities/CDirEntry.h"

#ifdef DEBUG_UI
#include <QtDebug>
#endif

// static
QDir CopasiFileDialog::LastDir;

// static
void CopasiFileDialog::openExampleDir()
{
  std::string ExampleDir;
  COptions::getValue("ExampleDir", ExampleDir);

  if (CDirEntry::isDir(ExampleDir))
    LastDir = FROM_UTF8(ExampleDir);
  else
    CQMessageBox::information(NULL, "Directory Not Found", FROM_UTF8(ExampleDir),
                              QMessageBox::Ok, QMessageBox::Ok);
}

// static
QString CopasiFileDialog::getOpenFileName(QWidget * parent,
    const char * /* name */,
    const QString & startWith,
    const QString & filter,
    const QString & caption,
    QString * pSelectedFilter)
{
  QString newFile = QFileDialog::getOpenFileName(parent,
                    caption,
                    startWith.isNull() ? LastDir.path() : startWith,
                    filter,
                    pSelectedFilter);

  if (newFile != "")
    LastDir = FROM_UTF8(CDirEntry::dirName(TO_UTF8(newFile)));

  return newFile;
}

// static
QString CopasiFileDialog::getSaveFileName(QWidget * parent,
    const char * name,
    const QString & startWith,
    const QString & filter,
    const QString & caption,
    QString * pSelectedFilter)
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
                                             startWith.isNull() ? LastDir.path() : startWith,
                                             newFilter, pSelectedFilter,
                                             QFileDialog::DontConfirmOverwrite);

      if (newFile != "")
        LastDir = FROM_UTF8(CDirEntry::dirName(TO_UTF8(newFile)));
      else
        return QString::null;

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
                  CQMessageBox::information(NULL, "Save File Error",
                                            "Filename can have an extension 1 to 4 characters long.",
                                            QMessageBox::Ok, QMessageBox::Ok);
                  fileValid = false;
                  continue;
                }

              QRegExp rxDigits("\\.\\d{1,4}$");

              if (rxDigits.indexIn(fileName) > 0)
                {
                  CQMessageBox::information(NULL, "Save File Error",
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
  qDebug() << "user selected Filter = " << usersFilter;
//  qDebug() << "user's Filter = " << *pSelectedFilter;
  qDebug() << "correct extension = " << correctExt;
  qDebug() << "filename = " << newFile;
#endif

  return newFile;
}
