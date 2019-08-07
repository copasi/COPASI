// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQExperimentSelection.h"

#include <QComboBox>

#include "copasi/copasi.h"

#include "qtUtilities.h"

#include "copasi/parameterFitting/CExperimentSet.h"
#include "copasi/parameterFitting/CExperiment.h"

#include <copasi/resourcesUI/CQIconResource.h>

/*
 *  Constructs a CQExperimentSelection as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CQExperimentSelection::CQExperimentSelection(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
  : QDialog(parent, fl)
{
#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
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

void CQExperimentSelection::slotBtnOK()
{
  mpBox->clear();

  if (mpList->selectedItems().count() != mpList->count())
    {
      QListWidgetItem * pItem;
      QStringList Items;
      int i, imax = mpList->count();

      for (i = 0; i != imax; ++i)
        {
          pItem = mpList->item(i);

          if (pItem->isSelected())
            {
              Items.append(pItem->text());
            }
        }

      mpBox->addItems(Items);
    }

  accept();
}

void CQExperimentSelection::slotBtnCancel()
{
  reject();
}

void CQExperimentSelection::slotBtnAll()
{
  mpList->selectAll();
}

void CQExperimentSelection::slotBtnNone()
{
  mpList->clearSelection();
}

void CQExperimentSelection::load(QComboBox * pBox, const CExperimentSet * pExperimentSet)
{
  mpBox = pBox;
  mpList->clear();

  QStringList Items;
  size_t i, imax = pExperimentSet->getExperimentCount();

  for (i = 0; i < imax; i++)
    {
      Items.append(FROM_UTF8(pExperimentSet->getExperiment(i)->getObjectName()));
    }

  mpList->addItems(Items);

  int j, jmax = mpBox->count();

  if (jmax == 0 && !mIsSingleSelection)
    {
      slotBtnAll();
      return;
    }

  for (j = 0; j < jmax; j++)
    {
      QList< QListWidgetItem * > Found = mpList->findItems(mpBox->itemText(j), Qt::MatchExactly);

      if (Found.size() > 0)
        {
          Found[0]->setSelected(true);
        }
    }
}

void CQExperimentSelection::setSingleSelection(bool isSingleSelection)
{
  mIsSingleSelection = isSingleSelection;

  if (mpList != NULL)
    mpList->setSelectionMode(isSingleSelection ? QListView::SingleSelection : QListView::MultiSelection);

  mpBtnNone->setVisible(!isSingleSelection);
  mpBtnAll->setVisible(!isSingleSelection);
}

void CQExperimentSelection::init()
{
  mpBox = NULL;
}
