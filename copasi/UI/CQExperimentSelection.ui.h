/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQExperimentSelection.ui.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/10/28 00:21:45 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qcombobox.h>
#include <qcheckbox.h>

#include "copasi.h"

#include "UI/qtUtilities.h"

#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CExperiment.h"

void CQExperimentSelection::slotBtnOK()
{
  mpBox->clear();

  QCheckBox * pCheckBox;
  bool AllChecked = true;
  bool NoneChecked = true;
  unsigned C_INT32 i, imax = mpTable->numRows();

  for (i = 0; i < imax; i++)
    {
      pCheckBox = static_cast<QCheckBox *>(mpTable->cellWidget(i, 0));
      if (pCheckBox->isChecked())
        {
          mpBox->insertItem(pCheckBox->text());
          NoneChecked = false;
        }
      else
        AllChecked = false;
    }

  if (AllChecked || NoneChecked)
    mpBox->clear();

  accept();
}

void CQExperimentSelection::slotBtnCancel()
{
  reject();
}

void CQExperimentSelection::slotBtnAll()
{
  unsigned C_INT32 i, imax = mpTable->numRows();

  for (i = 0; i < imax; i++)
    static_cast<QCheckBox *>(mpTable->cellWidget(i, 0))->setChecked(true);
}

void CQExperimentSelection::slotBtnNone()
{
  unsigned C_INT32 i, imax = mpTable->numRows();

  for (i = 0; i < imax; i++)
    static_cast<QCheckBox *>(mpTable->cellWidget(i, 0))->setChecked(false);
}

void CQExperimentSelection::load(QComboBox * pBox, const CExperimentSet * pExperimentSet)
{
  mpBox = pBox;

  QCheckBox * pCheckBox;
  QString Name;

  unsigned C_INT32 i, imax = pExperimentSet->size();
  unsigned C_INT32 j, jmax = mpBox->count();
  mpTable->setNumRows(imax);
  bool All = (jmax == 0);

  for (i = 0; i < imax; i++)
    {
      Name = FROM_UTF8(pExperimentSet->getExperiment(i)->getObjectName());
      pCheckBox = new QCheckBox(Name, this);
      pCheckBox->setChecked(false);

      if (All)
        pCheckBox->setChecked(true);
      else
        for (j = 0; j < jmax; j++)
          if (mpBox->text(j) == Name)
            {
              pCheckBox->setChecked(true);
              break;
            }

      mpTable->setCellWidget(i, 0, pCheckBox);
    }
}

void CQExperimentSelection::init()
{
  mpBox = NULL;

  mpTable->horizontalHeader()->hide();
  mpTable->verticalHeader()->hide();
  mpTable->setTopMargin(0);
  mpTable->setLeftMargin(0);
  mpTable->setFocusStyle(QTable::FollowStyle);
  mpTable->setColumnStretchable(0, true);
}
