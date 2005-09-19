/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiFileDialog.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: stupe $ 
   $Date: 2005/09/19 09:44:12 $
   End CVS Header */

#include <qapplication.h>
#include <qlayout.h>
#include <qtoolbutton.h>
#include "copasi.h"

#include "CopasiFileDialog.h"
#include "qtUtilities.h"

#include "commandline/COptions.h"
#include "utilities/CDirEntry.h"

CopasiFileDialog::CopasiFileDialog(QWidget * parent , const char * name , bool modal)
    : QFileDialog(parent , name , modal)
{
  mpGrp = new CQFileDialogBtnGrp(this);
  addLeftWidget(mpGrp);

  connect(mpGrp->mpBtnExamples, SIGNAL(pressed()), this, SLOT(slotExampleDir()));
  connect(mpGrp->mpBtnHome, SIGNAL(pressed()), this, SLOT(slotHomeDir()));
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
      QMessageBox::warning(this, "Directory Not Found", FROM_UTF8(ExampleDir), QMessageBox::Ok, 0);
      mpGrp->mpBtnExamples->setDown(false);
    }
}

QString CopasiFileDialog::GetOpenFileName(const QString & startWith, const QString & filter, QWidget * parent, const char * name, const QString & caption , QString * selectedFilter, bool resolveSymlinks)

{
  QString newFile = "";
  //this->setFilter(filter);
  this->setMode(QFileDialog::ExistingFile);
  if (this->exec() == QDialog::Accepted)
    {
      newFile = this->selectedFile();
      return newFile;
    }
  return NULL;
}

QString CopasiFileDialog::GetSaveFileName(const QString & startWith, const QString & filter, QWidget * parent, const char * name, const QString & caption, QString * selectedFilter, bool resolveSymlinks)
{
  QString newFile = "";
  //this->setFilter(filter);
  this->setMode(QFileDialog::AnyFile);
  if (this->exec() == QDialog::Accepted)
    {
      newFile = this->selectedFile();
      return newFile;
    }
  return NULL;
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
      QMessageBox::warning(this, "Directory Not Found", FROM_UTF8(homeDir), QMessageBox::Ok, 0);
      mpGrp->mpBtnHome->setDown(false);
    }
}
