// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiFileDialog.cpp,v $
//   $Revision: 1.27 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/07/03 09:41:23 $
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
  QString usersFilter, correctExt;

  QString newFile = QFileDialog::getSaveFileName(parent,
                    caption,
                    startWith.isNull() ? LastDir.path() : startWith,
                    filter,
                    pSelectedFilter, QFileDialog::DontConfirmOverwrite);

  if (newFile != "")
    LastDir = FROM_UTF8(CDirEntry::dirName(TO_UTF8(newFile)));
  else
    return QString::null;

  // newFile must end with correct extension
  newFile = newFile.remove(QRegExp("\\.$"));

  if (pSelectedFilter == NULL)  // it just happens if only one filter is available
    usersFilter = filter;
  else
    usersFilter = *pSelectedFilter;

  correctExt = usersFilter.section("*.", 1);
  correctExt = correctExt.remove(")");
  correctExt.prepend(".");

  if (!newFile.endsWith(correctExt)) newFile += correctExt;

#ifdef DEBUG_UI
  qDebug() << "user selected Filter = " << usersFilter;
//  qDebug() << "user's Filter = " << *pSelectedFilter;
  qDebug() << "correct extension = " << correctExt;
  qDebug() << "filename = " << newFile;
#endif

  return newFile;
}
