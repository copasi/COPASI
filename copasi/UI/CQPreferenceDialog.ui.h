// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQPreferenceDialog.ui.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/04/21 20:33:00 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qmessagebox.h>

#include "copasiui3window.h"
#include "qtUtilities.h"

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
  CCopasiParameter * par;

  if (CCopasiDataModel::Global)
    {
      CConfigurationFile * configFile = CCopasiDataModel::Global->getConfiguration();

      QString parName = "Max Last Visited Files";
      QListViewItem *item = mpListView->findItem(parName, 0);
      newMaxFiles = item->text(COL_VALUE).toUInt();
      CRecentFiles & recentFiles = configFile->getRecentFiles();
      par = recentFiles.getParameter("MaxFiles");
      unsigned C_INT32 maxFiles = *par->getValue().pUINT;
      if (newMaxFiles > 0 && newMaxFiles <= 20)
      {par->setValue(newMaxFiles);}
      else
        {
          QMessageBox::critical(this, "Incorrect Setting", "Max Last Visited Files should be a number between 1 and 20.");
          if (item)
          {item->setText(COL_VALUE, QString::number(maxFiles));}
          return;
        }

      /*
      parName = "Max Last Visited SBML Files";
      item = mpListView->findItem(parName, 0);
      newMaxFiles = item->text(COL_VALUE).toUInt();
      CRecentFiles & recentFilesSBML = configFile->getRecentSBMLFiles();
      par = recentFilesSBML.getParameter("MaxFiles");
      maxFiles = *par->getValue().pUINT;
      if (newMaxFiles > 0 && newMaxFiles <= 20)
           {par->setValue(newMaxFiles);}
         else
           {
             QMessageBox::critical(this, "Incorrect Setting", "Max Last Visited SBML Files should be a number between 1 and 20.");
             if (item)
             {item->setText(COL_VALUE, QString::number(maxFiles));}
             return;
           }
      */
    }
  done(1);
}

void CQPreferenceDialog::slotBtnCancel()
{
  if (CCopasiDataModel::Global)
    {
      unsigned C_INT32 maxFiles = 0;
      CConfigurationFile * configFile = CCopasiDataModel::Global->getConfiguration();

      QListViewItem *item = mpListView->findItem("Max Last Visited Files", 0);
      CRecentFiles & recentFiles = configFile->getRecentFiles();
      CCopasiParameter * par = recentFiles.getParameter("MaxFiles");
      maxFiles = *par->getValue().pUINT;
      if (item && maxFiles > 0)
      {item->setText(COL_VALUE, QString::number(maxFiles));}

      /*
      item = mpListView->findItem("Max Last Visited SBML Files", 0);
      recentFiles = configFile->getRecentSBMLFiles();
         par = recentFiles.getParameter("MaxFiles");
         maxFiles = *par->getValue().pUINT;
      if (item && maxFiles > 0)
      {item->setText(COL_VALUE, QString::number(maxFiles));}
      */
    }
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
      if (maxFiles > 0)
      {new CPreferenceListViewItem(mpListView, "Max Last Visited Files", QString::number(maxFiles));}

      /*
      recentFiles = configFile->getRecentSBMLFiles();
         par = recentFiles.getParameter("MaxFiles");
      maxFiles = *par->getValue().pUINT;
      if (maxFiles > 0)
      {new CPreferenceListViewItem(mpListView, "Max Last Visited SBML Files", QString::number(maxFiles));}
      */

      //QMessageBox::information(this, "maxFiles", QString::number(maxFiles));
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
