/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiFileDialog.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:43 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qapplication.h>
#include <qlayout.h>
#include <qtoolbutton.h>
#include "copasi.h"

#include "CopasiFileDialog.h"
#include "qtUtilities.h"

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
      QMessageBox::warning(this, "Directory Not Found", FROM_UTF8(ExampleDir),
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
      QMessageBox::warning(this, "Directory Not Found", FROM_UTF8(homeDir),
                           QMessageBox::Ok, 0);
      mpGrp->mpBtnHome->setDown(false);
    }
}

QString CopasiFileDialog::getOpenFileName(QWidget * parent,
    const char * name,
    const QString & startWith,
    const QString & filter,
    const QString & caption,
    QString selectedFilter)
{
  CopasiFileDialog * pDialog = new CopasiFileDialog(parent, name, true);

  QString File = pDialog->getOpenFileName(startWith, filter, caption, selectedFilter);
  delete pDialog;

  return File;
}

QString CopasiFileDialog::getSaveFileName(QWidget * parent,
    const char * name,
    const QString & startWith,
    const QString & filter,
    const QString & caption,
    QString selectedFilter)
{
  CopasiFileDialog * pDialog = new CopasiFileDialog(parent, name, true);

  QString File = pDialog->getSaveFileName(startWith, filter, caption, selectedFilter);
  delete pDialog;

  return File;
}

QString CopasiFileDialog::getSaveFileNameAndFilter(QString & newFilter,
    QWidget * parent,
    const char * name,
    const QString & startWith,
    const QString & filter,
    const QString & caption,
    QString selectedFilter)
{
  CopasiFileDialog * pDialog = new CopasiFileDialog(parent, name, true);

  QString File = pDialog->getSaveFileName(startWith, filter, caption, selectedFilter);
  newFilter = pDialog->selectedFilter();

  delete pDialog;

  return File;
}
