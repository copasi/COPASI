// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExperimentSelection.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:37:46 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QComboBox>
#include <QCheckBox>

#include "copasi.h"

#include "UI/qtUtilities.h"

#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CExperiment.h"
#include "CQExperimentSelection.h"

/*
 *  Constructs a CQExperimentSelection as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CQExperimentSelection::CQExperimentSelection(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, name, modal, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQExperimentSelection::~CQExperimentSelection()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQExperimentSelection::languageChange()
{
  retranslateUi(this);
}


void CQExperimentSelection::slotBtnOK()
{
  mpBox->clear();

  QCheckBox * pCheckBox;
  bool AllChecked = true;
  bool NoneChecked = true;
  size_t i, imax = mpTable->numRows();

  for (i = 0; i < imax; i++)
    {
      pCheckBox = static_cast<QCheckBox *>(mpTable->cellWidget((int) i, 0));

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
  size_t i, imax = mpTable->numRows();

  for (i = 0; i < imax; i++)
    static_cast<QCheckBox *>(mpTable->cellWidget((int) i, 0))->setChecked(true);
}

void CQExperimentSelection::slotBtnNone()
{
  size_t i, imax = mpTable->numRows();

  for (i = 0; i < imax; i++)
    static_cast<QCheckBox *>(mpTable->cellWidget((int) i, 0))->setChecked(false);
}

void CQExperimentSelection::load(QComboBox * pBox, const CExperimentSet * pExperimentSet)
{
  mpBox = pBox;

  QCheckBox * pCheckBox;
  QString Name;

  size_t i, imax = pExperimentSet->getExperimentCount();
  size_t j, jmax = mpBox->count();
  mpTable->setNumRows((int) imax);
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
          if (mpBox->text((int) j) == Name)
            {
              pCheckBox->setChecked(true);
              break;
            }

      mpTable->setCellWidget((int) i, 0, pCheckBox);
    }
}

void CQExperimentSelection::init()
{
  mpBox = NULL;

  mpTable->horizontalHeader()->hide();
  mpTable->verticalHeader()->hide();
  mpTable->setTopMargin(0);
  mpTable->setLeftMargin(0);
  mpTable->setFocusStyle(Q3Table::FollowStyle);
  mpTable->setColumnStretchable(0, true);
}
