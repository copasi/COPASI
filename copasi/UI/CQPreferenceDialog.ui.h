// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQPreferenceDialog.ui.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/09/26 21:11:41 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasiui3window.h"
#include <qmessagebox.h>
#include "commandline/CConfigurationFile.h"
#include "CopasiDataModel/CCopasiDataModel.h"

#define COL_NAME 0
#define COL_VALUE 1

class CPreferenceListViewItem : public QListViewItem
  {
  public:
    CPreferenceListViewItem(QListView *parent, const QString & label1, QString label2 = QString::null)
        : QListViewItem(parent, label1, label2)
    {
      setRenameEnabled(COL_VALUE, true);
    }

    CPreferenceListViewItem(QListViewItem *parent, const QString & label1, QString label2 = QString::null)
        : QListViewItem(parent, label1, label2)
    {
      setRenameEnabled(COL_VALUE, true);
    }
  };

void CQPreferenceDialog::slotBtnOk()
{
  unsigned C_INT32 newMaxFiles = 0;
  QListViewItem *item = mpListView->findItem("Max Last Visited Files", 0);
  newMaxFiles = item->text(COL_VALUE).toUInt();

  if (CCopasiDataModel::Global)
    {
      CConfigurationFile * configFile = CCopasiDataModel::Global->getConfiguration();
      CRecentFiles & recentFiles = configFile->getRecentFiles();
      CCopasiParameter * par = recentFiles.getParameter("MaxFiles");

      unsigned C_INT32 maxFiles = *par->getValue().pUINT;
      if (newMaxFiles > 0 && newMaxFiles <= 20)
        {
          par->setValue(newMaxFiles);
        }
      else
        {
          QMessageBox::critical(this, "Incorrect Setting", "Max Last Visited Files should be a number between 1 and 20.");
          if (item)
          {item->setText(COL_VALUE, QString::number(maxFiles));}
          return;
        }
    }
  done(1);
}

void CQPreferenceDialog::slotBtnCancel()
{
  unsigned C_INT32 maxFiles = 0;
  QListViewItem *item = mpListView->findItem("Max Last Visited Files", 0);
  if (CCopasiDataModel::Global)
    {
      CConfigurationFile * configFile = CCopasiDataModel::Global->getConfiguration();
      CRecentFiles & recentFiles = configFile->getRecentFiles();
      CCopasiParameter * par = recentFiles.getParameter("MaxFiles");
      maxFiles = *par->getValue().pUINT;
    }
  if (item && maxFiles > 0)
  {item->setText(COL_VALUE, QString::number(maxFiles));}
  done(0);
}

void CQPreferenceDialog::init()
{
  mpListView->setColumnWidth (COL_NAME, 150);
  mpListView->setColumnWidth (COL_VALUE, 100);
  unsigned C_INT32 maxFiles = 0;

  if (CCopasiDataModel::Global)
    {
      CConfigurationFile * configFile = CCopasiDataModel::Global->getConfiguration();
      CRecentFiles & recentFiles = configFile->getRecentFiles();
      CCopasiParameter * par = recentFiles.getParameter("MaxFiles");
      maxFiles = *par->getValue().pUINT;
      //QMessageBox::information(this, "maxFiles", QString::number(maxFiles));
    }
  if (maxFiles > 0)
    {
      CPreferenceListViewItem *item = new CPreferenceListViewItem(mpListView, "Max Last Visited Files", QString::number(maxFiles));
    }
}

//slot
void CQPreferenceDialog::editItem(QListViewItem * item, const QPoint & C_UNUSED(pnt), int c)
{
  if (!item) return;
  if (c == COL_VALUE) //column 1
    item->startRename(COL_VALUE);
}

//slot
void CQPreferenceDialog::editItem(QListViewItem * item)
{
  if (!item) return;
  item->startRename(COL_VALUE);
}
