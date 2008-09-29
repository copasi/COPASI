// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiFileDialog.cpp,v $
//   $Revision: 1.16 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/29 21:36:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qapplication.h>
#include <qlayout.h>
#include <qtoolbutton.h>
#include <qfileinfo.h>

#include "copasi.h"

#include "CopasiFileDialog.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"

#include "commandline/COptions.h"
#include "utilities/CDirEntry.h"

QDir CopasiFileDialog::mLastDir; // = QDir::current();

CopasiFileDialog::CopasiFileDialog(QWidget * parent ,
                                   const char * name ,
                                   bool modal)
    : QFileDialog(parent , name , modal)
{
  setDir(mLastDir);

  mpGrp = new CQFileDialogBtnGrp(this);
  addLeftWidget(mpGrp);

  connect(mpGrp->mpBtnExamples, SIGNAL(pressed()),
          this, SLOT(slotExampleDir()));
  connect(mpGrp->mpBtnHome, SIGNAL(pressed()),
          this, SLOT(slotHomeDir()));
}

CopasiFileDialog::~CopasiFileDialog()
{
  const QDir * pTmp = dir();
  mLastDir = * pTmp;
  delete pTmp;
}

QString CopasiFileDialog::getOpenFileName(const QString & startWith,
    const QString & filter,
    const QString & caption,
    QString selectedFilter)

{
  if (!startWith.isNull()) this->setSelection(startWith);
  if (!filter.isNull()) this->setFilters(filter);
  if (!caption.isNull()) this->setCaption(caption);
  if (selectedFilter) this->setSelectedFilter(selectedFilter);

  this->setMode(QFileDialog::ExistingFile);

  QString newFile = "";
  if (this->exec() == QDialog::Accepted)
    {
      newFile = this->selectedFile();
      return newFile;
    }
  return NULL;
}

QString CopasiFileDialog::getSaveFileName(const QString & startWith,
    const QString & filter,
    const QString & caption,
    QString selectedFilter)
{
  if (!startWith.isNull()) this->setSelection(startWith);
  if (!filter.isNull()) this->setFilters(filter);
  if (!caption.isNull()) this->setCaption(caption);
  if (selectedFilter) this->setSelectedFilter(selectedFilter);

  this->setMode(QFileDialog::AnyFile);

  QString newFile = "";
  if (this->exec() == QDialog::Accepted)
    {
      newFile = this->selectedFile();
      return newFile;
    }
  return NULL;
}

void CopasiFileDialog::slotExampleDir()
{
  std::string ExampleDir;
  COptions::getValue("ExampleDir", ExampleDir);

  if (CDirEntry::isDir(ExampleDir))
    {
      setDir(FROM_UTF8(ExampleDir));
    }
  else
    {
      CQMessageBox::information(this, "Directory Not Found", FROM_UTF8(ExampleDir),
                                QMessageBox::Ok, 0);
      mpGrp->mpBtnExamples->setDown(false);
    }
}

void CopasiFileDialog::slotHomeDir()
{
  std::string homeDir;
  COptions::getValue("Home", homeDir);

  if (CDirEntry::isDir(homeDir))
    {
      setDir(FROM_UTF8(homeDir));
    }
  else
    {
      CQMessageBox::information(this, "Directory Not Found", FROM_UTF8(homeDir),
                                QMessageBox::Ok, 0);
      mpGrp->mpBtnHome->setDown(false);
    }
}

// static
void CopasiFileDialog::openExampleDir()
{
  std::string ExampleDir;
  COptions::getValue("ExampleDir", ExampleDir);

  if (CDirEntry::isDir(ExampleDir))
    mLastDir = FROM_UTF8(ExampleDir);
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
  QString newFile = QFileDialog::getOpenFileName(mLastDir.path(),
                    filter,
                    parent,
                    name,
                    caption,
                    pSelectedFilter,
                    true);
  if (newFile != "")
    mLastDir = FROM_UTF8(CDirEntry::dirName((const char *)newFile.utf8()));

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
  QString newFile = QFileDialog::getSaveFileName(mLastDir.path(),
                    filter,
                    parent,
                    name,
                    caption,
                    pSelectedFilter,
                    true);
  if (newFile != "")
    mLastDir = FROM_UTF8(CDirEntry::dirName((const char *)newFile.utf8()));

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
