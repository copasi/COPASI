// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiFileDialog.cpp,v $
//   $Revision: 1.17 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/30 13:50:03 $
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
                              QMessageBox::Ok, 0);
}

// static
QString CopasiFileDialog::getOpenFileName(QWidget * parent,
    const char * name,
    const QString & startWith,
    const QString & filter,
    const QString & caption,
    QString * pSelectedFilter)
{
  QString newFile = QFileDialog::getOpenFileName(startWith.isNull() ? LastDir.path() : startWith,
                    filter,
                    parent,
                    name,
                    caption,
                    pSelectedFilter,
                    true);
  if (newFile != "")
    LastDir = FROM_UTF8(CDirEntry::dirName((const char *)newFile.utf8()));

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
  QString newFile = QFileDialog::getSaveFileName(startWith.isNull() ? LastDir.path() : startWith,
                    filter,
                    parent,
                    name,
                    caption,
                    pSelectedFilter,
                    true);
  if (newFile != "")
    LastDir = FROM_UTF8(CDirEntry::dirName((const char *)newFile.utf8()));

  return newFile;
}

// static
QString CopasiFileDialog::getSaveFileNameAndFilter(QString & selectedFilter,
    QWidget * parent,
    const char * name,
    const QString & startWith,
    const QString & filter,
    const QString & caption)
{
  QString File =
    CopasiFileDialog::getSaveFileName(parent, name, startWith,
                                      filter, caption, & selectedFilter);

  if (!File) return "";

  // check the extension and replace the uncorrect extension with the correct one according to the filter
  QString Filter;

  if (selectedFilter.contains("png"))
    Filter = "png";
  else if (selectedFilter.contains("svg"))
    Filter = "svg";
  else if (selectedFilter.contains("tex"))
    Filter = "tex";
  else if (selectedFilter.contains("mml"))
    Filter = "mml";
  else if (selectedFilter.contains("xml"))
    Filter = "xml";

  if (!File.endsWith("." + Filter))
    {
      if (File.contains("."))
        {
          int pos = File.find(".");
          File.truncate(pos);
        }

      File += "." + Filter;
    }

  return File;
}
