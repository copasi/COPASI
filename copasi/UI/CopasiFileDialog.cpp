// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiFileDialog.cpp,v $
//   $Revision: 1.25 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/06/22 15:41:53 $
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
  /*QString newFile = QFileDialog::getOpenFileName(startWith.isNull() ? LastDir.path() : startWith,
                    filter,
                    parent,
                    name,
                    caption,
                    pSelectedFilter,
                    true);*/

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
  /*
    QString newFile = QFileDialog::getSaveFileName(startWith.isNull() ? LastDir.path() : startWith,
                      filter,
                      parent,
                      name,
                      caption,
                      pSelectedFilter,
                      true);
  */

  QString newFile = QFileDialog::getSaveFileName(parent,
                    caption,
                    startWith.isNull() ? LastDir.path() : startWith,
                    filter,
                    pSelectedFilter);

  if (newFile != "")
    LastDir = FROM_UTF8(CDirEntry::dirName(TO_UTF8(newFile)));

  return newFile;
}

// static

/*
Apply this static function if you need to ensure that the file is being saved
with the correct extension regarding to the chosen filter.
 */

QString CopasiFileDialog::getSaveFileNameAndFilter(QString & selFilter,
    QWidget * parent,
    const char * name,
    const QString & startWith,
    const QString & filter,
    const QString & caption)
{
  // Alternative 1: by means of the native static function

  QString selectedFilter;

  QString fileName = QFileDialog::getSaveFileName(parent,
                     caption,
                     startWith.isNull() ? LastDir.path() : startWith,
                     filter,
                     &selectedFilter,
                     QFileDialog::DontConfirmOverwrite);

// correlated to 'save formula' on differential equations window
  if (selectedFilter == "TeX (*.tex)") selFilter = ".tex";
  else if (selectedFilter == "MathML (*.mml)") selFilter = ".mml";

// correlated to 'save image' on plot window
  if (selectedFilter == "PNG Files (*.png)") selFilter = ".png";
  else if (selectedFilter == "SVG Files (*.svg)") selFilter = ".svg";

// correlated to 'save data' on plot window
//    if (selectedFilter.contains("txt")) fd.setDefaultSuffix("txt");

// correlated to 'export ODE' on main window
  if (selectedFilter == "C Files (*.c)") selFilter = ".c";
  else if (selectedFilter == "Berkeley Madonna Files (*.mmd)") selFilter = ".mmd";
  else if (selectedFilter == "XPPAUT (*.ode)") selFilter = ".ode";

// correlated to 'save as' on main window
//      if (selectedFilter.contains("cps")) fd.setDefaultSuffix("cps");

  QString suffix = FROM_UTF8(CDirEntry::suffix(TO_UTF8(fileName)));

#ifdef DEBUG_UI
  qDebug() << "fileName = " << fileName;
  qDebug() << "suffix = " << suffix;
  qDebug() << "default suffix = " << selFilter;
  qDebug() << "selected Filter = " << selectedFilter;
#endif

  if (suffix.isEmpty())
    fileName.append(selFilter);
  else
    fileName.replace(suffix, selFilter);

  // Alternative 2 : use own QFileDialog

  /*
    NOTE(19.06.2009):
    We should apply our own QFileDialog without using the static functions.
    The main reason is that for having more control on it.
    Alternative: this class should inherit QFileDialog.
  */
  /*
    QFileDialog fd(parent);
    fd.setAcceptMode(QFileDialog::AcceptSave);
    fd.setWindowTitle(caption);
    fd.setDirectory(startWith.isNull() ? LastDir.path() : startWith);
    fd.setFileMode(QFileDialog::AnyFile);
    fd.setOption(QFileDialog::DontConfirmOverwrite);

    fd.setNameFilter(filter);

    if (filter.count("*.") == 1)
      fd.setDefaultSuffix(filter);

    QString fileName;

    if (fd.exec() == QDialog::Accepted)
      {
        QString selectedFilter(fd.selectedNameFilter());

#ifdef DEBUG_UI
        qDebug() << selectedFilter;
#endif

  // correlated to 'save formula' on differential equations window
        if (selectedFilter == "TeX (*.tex)") fd.setDefaultSuffix("tex");
        else if (selectedFilter == "MathML (*.mml)") fd.setDefaultSuffix("mml");

  // correlated to 'save image' on plot window
        if (selectedFilter == "PNG Files (*.png)") fd.setDefaultSuffix("png");
        else if (selectedFilter == "SVG Files (*.svg)") fd.setDefaultSuffix("svg");

  // correlated to 'save data' on plot window
  //    if (selectedFilter.contains("txt")) fd.setDefaultSuffix("txt");

  // correlated to 'export ODE' on main window
        if (selectedFilter == "C Files (*.c)") fd.setDefaultSuffix("c");
        else if (selectedFilter == "Berkeley Madonna Files (*.mmd)") fd.setDefaultSuffix("mmd");
        else if (selectedFilter == "XPPAUT (*.ode)") fd.setDefaultSuffix("ode");

  // correlated to 'save as' on main window
  //      if (selectedFilter.contains("cps")) fd.setDefaultSuffix("cps");

        QString defaultSuffix = fd.defaultSuffix();

        defaultSuffix.prepend(".");
        selFilter = defaultSuffix;

  //      selFilter = fd.defaultSuffix();

  //  fileName = fd.selectedFiles()[0];
        fileName = fd.selectedFiles().value(0);
        QString suffix = FROM_UTF8(CDirEntry::suffix(TO_UTF8(fileName)));

#ifdef DEBUG_UI
        qDebug() << "fileName = " << fileName;
        qDebug() << "suffix = " << suffix;
        qDebug() << "default suffix = " << selFilter;
#endif

        fileName.replace(suffix, selFilter);
      }
  */
#ifdef DEBUG_UI
  qDebug() << fileName;
#endif

  return fileName;
}
