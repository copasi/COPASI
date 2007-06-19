// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQPreferenceDialog.ui.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/06/19 16:35:28 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasiui3window.h"
#include <qmessagebox.h>
#include "commandline/CConfigurationFile.h"
#include "CopasiDataModel/CCopasiDataModel.h"

void CQPreferenceDialog::slotBtnOk()
{
  done(1);
}

void CQPreferenceDialog::slotBtnCancel()
{
  done(0);
}

void CQPreferenceDialog::init()
{
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
      QListViewItem *item = mpListView->findItem("Max Last Visited Files", 0);
      item->setText(1, QString::number(maxFiles));
    }
}

void CQPreferenceDialog::destroy()
{
}
