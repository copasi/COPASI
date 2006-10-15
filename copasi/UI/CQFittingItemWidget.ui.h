/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQFittingItemWidget.ui.h,v $
   $Revision: 1.19 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 06:57:33 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qapplication.h>

#include "CopasiUI/CCopasiSelectionDialog.h"
#include "CopasiUI/CQValidator.h"
#include "CopasiUI/CQExperimentSelection.h"
#include "CopasiUI/CQStartValueReset.h"
#include "CopasiUI/qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "parameterFitting/CFitItem.h"
#include "parameterFitting/CFitProblem.h"
#include "parameterFitting/CExperiment.h"
#include "parameterFitting/CExperimentSet.h"
#include "utilities/utility.h"

void CQFittingItemWidget::init()
{
  mppSet = NULL;
  mpItemsCopy = new std::vector<COptItem *>;
  mCurrentRow = C_INVALID_INDEX;

  setItemType(OPT_ITEM);

  mLowerInfChanged = false;
  mUpperInfChanged = false;

  mpTable->horizontalHeader()->hide();
  mpTable->setTopMargin(0);

  int h, s, v;

  mSavedColor = paletteBackgroundColor();
  mSavedColor.getHsv(&h, &s, &v);

  if (s < 20) s = 20;
  mChangedColor.setHsv(240, s, v);

  mpObjectValidator = new CQValidatorNotEmpty(mpEditObject);
  mpEditObject->setValidator(mpObjectValidator);
  mpObjectValidator->revalidate();

  mpLowerValidator = new CQValidatorBound(mpEditLower);
  mpEditLower->setValidator(mpLowerValidator);
  mpLowerValidator->revalidate();

  mpUpperValidator = new CQValidatorBound(mpEditUpper);
  mpEditUpper->setValidator(mpUpperValidator);
  mpUpperValidator->revalidate();
}

void CQFittingItemWidget::destroy()
{
  std::vector< COptItem * >::iterator it = mpItemsCopy->begin();
  std::vector< COptItem * >::iterator end = mpItemsCopy->end();

  for (; it != end; ++it)
    pdelete(*it);

  pdelete(mpItemsCopy);
}

void CQFittingItemWidget::slotCheckLowerInf(bool checked)
{
  mpEditLower->setEnabled(!checked);

  mLowerInfChanged = !mLowerInfChanged;

  if (mLowerInfChanged)
    {
      mpCheckLowerInf->setPaletteBackgroundColor(mChangedColor);
      if (mpEditLower->isEnabled()) mpLowerValidator->revalidate();
    }
  else
    mpCheckLowerInf->setPaletteBackgroundColor(mSavedColor);

  std::string Number;

  if (checked)
    Number = "-inf";
  else if (isNumber((const char *) mpEditLower->text().utf8()))
    Number = (const char *) mpEditLower->text().utf8();
  else if (mpLowerObject)
    Number = mpLowerObject->getCN();
  else return;

  std::set< unsigned int >::const_iterator it = mSelection.begin();
  std::set< unsigned int >::const_iterator end = mSelection.end();

  for (; it != end; ++it)
    {
      (*mpItemsCopy)[*it]->setLowerBound(Number);
      setTableText(*it, (*mpItemsCopy)[*it]);
    }
}

void CQFittingItemWidget::slotCheckUpperInf(bool checked)
{
  mpEditUpper->setEnabled(!checked);

  mUpperInfChanged = !mUpperInfChanged;

  if (mUpperInfChanged)
    {
      mpCheckUpperInf->setPaletteBackgroundColor(mChangedColor);
      if (mpEditUpper->isEnabled()) mpUpperValidator->revalidate();
    }
  else
    mpCheckUpperInf->setPaletteBackgroundColor(mSavedColor);

  std::string Number;

  if (checked)
    Number = "inf";
  else if (isNumber((const char *) mpEditUpper->text().utf8()))
    Number = (const char *) mpEditUpper->text().utf8();
  else if (mpUpperObject)
    Number = mpUpperObject->getCN();
  else return;

  std::set< unsigned int >::const_iterator it = mSelection.begin();
  std::set< unsigned int >::const_iterator end = mSelection.end();

  for (; it != end; ++it)
    {
      (*mpItemsCopy)[*it]->setUpperBound(Number);
      setTableText(*it, (*mpItemsCopy)[*it]);
    }
}

void CQFittingItemWidget::slotLowerEdit()
{
  std::vector<CCopasiObject*> Selection;

  CCopasiSelectionDialog * pBrowseDialog = new CCopasiSelectionDialog(this);
  pBrowseDialog->setModel(CCopasiDataModel::Global->getModel());
  pBrowseDialog->setSingleSelection(true);
  pBrowseDialog->setOutputVector(&Selection);

  if (pBrowseDialog->exec () == QDialog::Accepted && Selection.size() != 0)
    {
      mpCheckLowerInf->setChecked(false);
      mpEditLower->setEnabled(true);

      if (!mSelection.size())
        slotNew();

      std::set< unsigned int >::const_iterator it = mSelection.begin();
      std::set< unsigned int >::const_iterator end = mSelection.end();

      mpLowerObject = Selection[0];
      CCopasiObjectName CN = mpLowerObject->getCN();

      for (; it != end; ++it)
        {
          (*mpItemsCopy)[*it]->setLowerBound(CN);
          setTableText(*it, (*mpItemsCopy)[*it]);
        }

      mpTable->adjustColumn(0);

      QString Value = FROM_UTF8(Selection[0]->getObjectDisplayName());
      mpLowerValidator->force(Value);
      mpEditLower->setText(Value);
    }
}

void CQFittingItemWidget::slotUpperEdit()
{
  std::vector<CCopasiObject*> Selection;

  CCopasiSelectionDialog * pBrowseDialog = new CCopasiSelectionDialog(this);
  pBrowseDialog->setModel(CCopasiDataModel::Global->getModel());
  pBrowseDialog->setSingleSelection(true);
  pBrowseDialog->setOutputVector(&Selection);

  if (pBrowseDialog->exec () == QDialog::Accepted && Selection.size() != 0)
    {
      mpCheckUpperInf->setChecked(false);
      mpEditUpper->setEnabled(true);

      if (!mSelection.size())
        slotNew();

      std::set< unsigned int >::const_iterator it = mSelection.begin();
      std::set< unsigned int >::const_iterator end = mSelection.end();

      mpUpperObject = Selection[0];
      CCopasiObjectName CN = mpUpperObject->getCN();

      for (; it != end; ++it)
        {
          (*mpItemsCopy)[*it]->setUpperBound(CN);
          setTableText(*it, (*mpItemsCopy)[*it]);
        }

      mpTable->adjustColumn(0);

      QString Value = FROM_UTF8(Selection[0]->getObjectDisplayName());
      mpUpperValidator->force(Value);
      mpEditUpper->setText(Value);
    }
}

void CQFittingItemWidget::slotParamEdit()
{
  std::vector<CCopasiObject*> Selection;

  CCopasiSelectionDialog * pBrowseDialog = new CCopasiSelectionDialog(this);
  pBrowseDialog->setModel(CCopasiDataModel::Global->getModel());
  pBrowseDialog->setSingleSelection(mSelection.size() > 1);
  pBrowseDialog->setOutputVector(&Selection);

  if (pBrowseDialog->exec () == QDialog::Accepted && Selection.size() != 0)
    {
      // We need to loop through the selection.
      unsigned C_INT32 current = currentRow();

      // We must not trigger slotSelectionChanged!
      disconnect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));

      // If no item is selected create one.
      if (!mSelection.size())
        {
          COptItem * pItem;

          switch (mItemType)
            {
            case OPT_ITEM:
              pItem = new COptItem();
              break;
            case FIT_ITEM:
              pItem = new CFitItem();
              break;
            case FIT_CONSTRAINT:
              pItem = new CFitConstraint();
              break;
            }

          mpItemsCopy->push_back(pItem);
          current = mpTable->numRows();
          mSelection.insert(current);
          mpTable->insertRows(current);
          setTableText(current, pItem);
        }

      // Update the selected items
      std::set< unsigned int >::const_iterator it = mSelection.begin();
      std::set< unsigned int >::const_iterator end = mSelection.end();

      for (; it != end; ++it)
        {
          (*mpItemsCopy)[*it]->setObjectCN(Selection[0]->getCN());
          setTableText(*it, (*mpItemsCopy)[*it]);
        }

      saveSelection();

      // If one item is selected we may have no several objects
      // and must create the appropriate items
      unsigned C_INT32 i, imax = Selection.size();

      COptItem * pSrc = (*mpItemsCopy)[*mSelection.begin()];

      for (i = 1; i != imax; i++)
        {
          COptItem * pItem;

          switch (mItemType)
            {
            case OPT_ITEM:
              pItem = new COptItem(*pSrc);
              break;
            case FIT_ITEM:
              pItem = new CFitItem(*pSrc);
              break;
            case FIT_CONSTRAINT:
              pItem = new CFitConstraint(*pSrc);
              break;
            }

          pItem->setObjectCN(Selection[i]->getCN());

          // Add the new item to the list.
          mpItemsCopy->insert(mpItemsCopy->begin() + current + i, pItem);

          // Update the table
          mpTable->insertRows(current + i);
          setTableText(current + i, pItem);
        }

      connect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));
      // Update the table
      mpTable->adjustColumn(0);

      // Update the selection;
      if (current != C_INVALID_INDEX)
        selectRow(current);
      else
        loadSelection();

      emit numberChanged(mpItemsCopy->size());
    }
}

void CQFittingItemWidget::slotExperiments()
{
  if (mItemType)
    {
      CQExperimentSelection * pDialog = new CQExperimentSelection(this);
      pDialog->load(mpBoxExperiments, * mppSet);

      if (pDialog->exec() == QDialog::Accepted)
        {
          if (!mSelection.size())
            slotNew();

          std::set< unsigned int >::const_iterator it = mSelection.begin();
          std::set< unsigned int >::const_iterator end = mSelection.end();

          for (; it != end; ++it)
            {
              (*mpItemsCopy)[*it]->getGroup("Affected Experiments")->clear();
              unsigned C_INT32 i, imax = mpBoxExperiments->count();

              for (i = 0; i < imax && imax < (*mppSet)->size(); i++)
                static_cast<CFitItem *>((*mpItemsCopy)[*it])->addExperiment((*mppSet)->getExperiment((const char *) mpBoxExperiments->text(i).utf8())->CCopasiParameter::getKey());

              setTableText(*it, (*mpItemsCopy)[*it]);
            }

          mpTable->adjustColumn(0);
        }

      loadSelection();

      delete pDialog;
    }
}

bool CQFittingItemWidget::load(CCopasiParameterGroup * pItems,
                               const std::map<std::string, std::string> * pKeyMap)
{
  mpItems = pItems;
  mSelection.clear();

  std::vector< COptItem * >::iterator it = mpItemsCopy->begin();
  std::vector< COptItem * >::iterator end = mpItemsCopy->end();

  for (; it != end; ++it)
    pdelete(*it);

  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));
  mpTable->setNumRows(mpItems->size());
  connect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));
  mCurrentRow = C_INVALID_INDEX;

  mpItemsCopy->resize(mpItems->size());

  it = mpItemsCopy->begin();
  end = mpItemsCopy->end();

  std::vector< COptItem * >::const_iterator src =
    static_cast<std::vector< COptItem * > *>(mpItems->CCopasiParameter::getValue().pVOID)->begin();

  unsigned C_INT32 i;
  for (i = 0; it != end; ++it, ++src, ++i)
    {
      switch (mItemType)
        {
        case OPT_ITEM:
          *it = new COptItem(**src);
          break;
        case FIT_ITEM:
          *it = new CFitItem(**src);
          break;
        case FIT_CONSTRAINT:
          *it = new CFitConstraint(**src);
          break;
        }

      if (mItemType)
        {
          if (!pKeyMap) return false;

          // Change the key to reflect the local copy *mppSet
          unsigned C_INT32 j, jmax = static_cast<CFitItem *>(*it)->getExperimentCount();

          for (j = 0; j < jmax; j++)
            {
              std::string & Key =
                *const_cast<std::string *>(&static_cast<CFitItem *>(*it)->getExperiment(j));
              Key = pKeyMap->find(Key)->second;
            }
        }

      setTableText(i, *it);
    }

  if (mpItemsCopy->size())
    selectRow(0);
  else
    selectRow(C_INVALID_INDEX);

  mpTable->adjustColumn(0);

  emit numberChanged(mpItemsCopy->size());

  return true;
}

bool CQFittingItemWidget::save(const std::map<std::string, std::string> * pKeyMap)
{
  // Make sure that the current items is saved.
  saveSelection();

  bool changed = false;

  std::vector< COptItem * >::const_iterator it = mpItemsCopy->begin();
  std::vector< COptItem * >::const_iterator end = mpItemsCopy->end();

  std::vector< COptItem * >::iterator target =
    static_cast<std::vector< COptItem * > *>(mpItems->CCopasiParameter::getValue().pVOID)->begin();
  std::vector< COptItem * >::iterator targetEnd =
    static_cast<std::vector< COptItem * > *>(mpItems->CCopasiParameter::getValue().pVOID)->end();

  unsigned C_INT32 i;
  unsigned C_INT32 imax = std::max<unsigned C_INT32>(mpItemsCopy->size(), mpItems->size());

  for (i = 0; it != end && target != targetEnd; ++it, ++target, ++i)
    {
      if ((*target)->getObjectCN() != (*it)->getObjectCN())
        {
          changed = true;
          if (!(*target)->setObjectCN((*it)->getObjectCN()))
            (*target)->setValue("ObjectCN", (*it)->getObjectCN());
        }

      if ((*target)->getLowerBound() != (*it)->getLowerBound())
        {
          changed = true;
          (*target)->setLowerBound((*it)->getLowerBound());
        }

      if ((*target)->getUpperBound() != (*it)->getUpperBound())
        {
          changed = true;
          (*target)->setUpperBound((*it)->getUpperBound());
        }

      if ((*target)->getStartValue() != (*it)->getStartValue())
        {
          changed = true;
          (*target)->setStartValue((*it)->getStartValue());
        }

      if (mItemType)
        {
          if (!pKeyMap) return false;

          unsigned C_INT32 j, jmax =
            std::min(static_cast<CFitItem *>(*it)->getExperimentCount(),
                     static_cast<CFitItem *>(*target)->getExperimentCount());

          // Compare and assign common experiments
          for (j = 0; j < jmax; j++)
            {
              std::string & Target =
                *const_cast<std::string *>(&static_cast<CFitItem *>(*target)->getExperiment(j));
              const std::string & Source =
                pKeyMap->find(static_cast<CFitItem *>(*it)->getExperiment(j))->second;

              if (Target != Source)
                {
                  changed = true;
                  Target = Source;
                }
            }

          // Remove exceeding experiments starting from the last
          for (jmax = static_cast<CFitItem *>(*target)->getExperimentCount() - 1;
               j <= jmax && jmax != C_INVALID_INDEX; jmax--)
            {
              changed = true;
              static_cast<CFitItem *>(*target)->removeExperiment(jmax);
            }

          // Add missing experiments
          for (jmax = static_cast<CFitItem *>(*it)->getExperimentCount(); j < jmax; j++)
            {
              changed = true;

              const std::string & Source =
                pKeyMap->find(static_cast<CFitItem *>(*it)->getExperiment(j))->second;

              static_cast<CFitItem *>(*target)->addExperiment(Source);
            }
        }
    }

  // Remove exceeding items starting from the last.
  for (imax--; i <= imax && imax != C_INVALID_INDEX; imax--)
    {
      changed = true;
      mpItems->removeParameter(imax);
    }

  // Add missing items
  for (; it != end; ++it)
    {
      changed = true;

      COptItem * pItem;

      switch (mItemType)
        {
        case OPT_ITEM:
          pItem = new COptItem(**it);
          break;
        case FIT_ITEM:
          pItem = new CFitItem(**it);
          break;
        case FIT_CONSTRAINT:
          pItem = new CFitConstraint(**it);
          break;
        }

      if (mItemType)
        {
          if (!pKeyMap) return false;

          unsigned C_INT32 j, jmax =
            static_cast<CFitItem *>(pItem)->getExperimentCount();

          // Remap the experiment keys
          for (j = 0; j < jmax; j++)
            {
              std::string & Target =
                *const_cast<std::string *>(&static_cast<CFitItem *>(pItem)->getExperiment(j));
              const std::string & Source =
                pKeyMap->find(static_cast<CFitItem *>(*it)->getExperiment(j))->second;

              Target = Source;
            }
        }

      mpItems->addParameter(pItem);
    }

  return changed;
}

void CQFittingItemWidget::setItemType(const ItemType & type)
{
  mItemType = type;

  if (mItemType)
    {
      mpLblExperiments->show();
      mpCheckAll->show();
      mpBoxExperiments->show();
      mpBtnExperiments->show();
      mpBtnPerExperiment->show();
    }
  else
    {
      mpLblExperiments->hide();
      mpCheckAll->hide();
      mpBoxExperiments->hide();
      mpBtnExperiments->hide();
      mpBtnPerExperiment->hide();
    }

  qApp->processEvents();
}

void CQFittingItemWidget::slotExperimentChanged()
{
  // This slot is trigered when an experiment is deleted or changed,
  // but before new experiments are created.

  if (!mItemType) return;

  // Remove all references to deleted experiments.
  std::vector< COptItem * >::iterator it = mpItemsCopy->begin();
  std::vector< COptItem * >::iterator end = mpItemsCopy->end();

  unsigned C_INT32 i, imax;
  unsigned C_INT32 Row;

  for (Row = 0; it != end; ++it, ++Row)
    {
      for (i = 0, imax = static_cast<CFitItem *>(*it)->getExperimentCount(); i < imax; ++i)
        if (!GlobalKeys.get(static_cast<CFitItem *>(*it)->getExperiment(i)))
          static_cast<CFitItem *>(*it)->removeExperiment(i);

      setTableText(Row, *it);
    }

  mpTable->adjustColumn(0);

  // Reload the current item.
  loadSelection();

  return;
}

void CQFittingItemWidget::setExperimentSet(const CExperimentSet * & pExperimentSet)
{mppSet = &pExperimentSet;}

void CQFittingItemWidget::slotCheckAll(bool checked)
{
  if (!mItemType) return;

  if (!checked && mpBoxExperiments->count() == 0)
    slotExperiments();
  else if (checked)
    {
      std::set< unsigned int >::const_iterator it = mSelection.begin();
      std::set< unsigned int >::const_iterator end = mSelection.end();

      for (; it != end; ++it)
        {
          (*mpItemsCopy)[*it]->getGroup("Affected Experiments")->clear();
          setTableText(*it, (*mpItemsCopy)[*it]);
        }
    }

  mpTable->adjustColumn(0);

  loadSelection();
}

void CQFittingItemWidget::slotDelete()
{
  unsigned C_INT32 row = mCurrentRow;

  COptItem * pItem;

  std::set< unsigned int >::const_iterator it = mSelection.begin();
  std::set< unsigned int >::const_iterator end = mSelection.end();

  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));

  unsigned int Deleted = 0;
  for (; it != end; ++it, ++Deleted)
    {
      row = *it - Deleted;

      pItem = (*mpItemsCopy)[row];

      // Erase the item from the vector.
      mpItemsCopy->erase(mpItemsCopy->begin() + row);
      // Update the table
      mpTable->removeRow(row);
      pdelete(pItem);
    }

  mpTable->clearSelection();
  mSelection.clear();

  connect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));

  // Change the selection
  if (row >= mpItemsCopy->size())
    row = mpItemsCopy->size() - 1;

  selectRow(row);

  emit numberChanged(mpItemsCopy->size());
}

void CQFittingItemWidget::slotCopy()
{
  if (!mSelection.size())
    {
      // We have nothing to copy, therefore we create a new item.
      slotNew();
      return;
    }

  // Save the changes to  the current items
  saveSelection();

  // Create the new item.
  COptItem * pItem;
  COptItem * pSrc = (*mpItemsCopy)[*mSelection.begin()];

  switch (mItemType)
    {
    case OPT_ITEM:
      pItem = new COptItem(*pSrc);
      break;
    case FIT_ITEM:
      pItem = new CFitItem(*pSrc);
      break;
    case FIT_CONSTRAINT:
      pItem = new CFitConstraint(*pSrc);
      break;
    }

  unsigned C_INT32 row = mCurrentRow + 1;
  mpItemsCopy->insert(mpItemsCopy->begin() + row, pItem);

  // Update the table
  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));
  mpTable->insertRows(row);
  connect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));

  setTableText(row, pItem);
  mpTable->adjustColumn(0);

  // Update the selection
  selectRow(row);

  emit numberChanged(mpItemsCopy->size());
}

void CQFittingItemWidget::slotUp()
{
  if (!mSelection.size()) return; // Nothing to move.

  saveSelection();

  std::set< unsigned int > NewSelection;
  std::set< unsigned int >::const_iterator it = mSelection.begin();
  std::set< unsigned int >::const_iterator end = mSelection.end();
  COptItem * pItem;

  if (*it == 0) ++it; // The first row can not be moved up.

  for (; it != end; ++it)
    {
      NewSelection.insert(*it - 1);

      // Swap the items
      pItem = (*mpItemsCopy)[*it];
      (*mpItemsCopy)[*it] = (*mpItemsCopy)[*it - 1];
      (*mpItemsCopy)[*it - 1] = pItem;

      // Swap the table rows
      mpTable->swapRows(*it, *it - 1);
    }

  mpTable->updateContents();

  setItemSelection(NewSelection);
  loadSelection();
}

void CQFittingItemWidget::slotDown()
{
  if (!mSelection.size()) return; // Nothing to move.

  saveSelection();

  std::set< unsigned int > NewSelection;
  std::set< unsigned int >::reverse_iterator it = mSelection.rbegin();
  std::set< unsigned int >::reverse_iterator end = mSelection.rend();
  COptItem * pItem;

  if (*it == mpTable->numRows() - 1)
    ++it; // The last row can not be moved down.

  for (; it != end; ++it)
    {
      NewSelection.insert(*it + 1);

      // Swap the items
      pItem = (*mpItemsCopy)[*it];
      (*mpItemsCopy)[*it] = (*mpItemsCopy)[*it + 1];
      (*mpItemsCopy)[*it + 1] = pItem;

      // Swap the table rows
      mpTable->swapRows(*it, *it + 1);
    }

  mpTable->updateContents();

  setItemSelection(NewSelection);
  loadSelection();
}

void CQFittingItemWidget::slotDuplicatePerExperiment()
{
  if (!mItemType) return;

  // Save the changes to  the current items
  saveSelection();

  if (!mSelection.size())
    slotNew();

  unsigned C_INT32 row = mCurrentRow + 1;
  unsigned C_INT32 i, imax =
    static_cast<CFitItem *>((*mpItemsCopy)[*mSelection.begin()])->getExperimentCount();

  CFitItem * pItem, * pTemplate;

  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));

  if (imax)
    {
      // We have a list of experiments
      switch (mItemType)
        {
        case FIT_ITEM:
          pTemplate = new CFitItem(*(*mpItemsCopy)[*mSelection.begin()]);
          break;
        case FIT_CONSTRAINT:
          pTemplate = new CFitConstraint(*(*mpItemsCopy)[*mSelection.begin()]);
          break;
        }

      // Remove all experiments from the template
      for (i = imax - 1; i != C_INVALID_INDEX; i--)
        pTemplate->removeExperiment(i);

      for (i = imax - 1; i != 0; i--)
        {
          switch (mItemType)
            {
            case FIT_ITEM:
              pItem = new CFitItem(*pTemplate);
              break;
            case FIT_CONSTRAINT:
              pItem = new CFitConstraint(*pTemplate);
              break;
            }

          pItem->addExperiment(static_cast<CFitItem *>((*mpItemsCopy)[*mSelection.begin()])->getExperiment(i));

          static_cast<CFitItem *>((*mpItemsCopy)[*mSelection.begin()])->removeExperiment(i);

          mpItemsCopy->insert(mpItemsCopy->begin() + row, pItem);

          // Update the table
          mpTable->insertRows(row);
          setTableText(row, pItem);
        }
    }
  else
    {
      // We have ALL
      imax = (*mppSet)->size();
      for (i = imax - 1; i != 0; i--)
        {
          pItem = new CFitItem(*(*mpItemsCopy)[*mSelection.begin()]);
          pItem->addExperiment((*mppSet)->getExperiment(i)->CCopasiParameter::getKey());

          mpItemsCopy->insert(mpItemsCopy->begin() + row, pItem);

          // Update the table
          mpTable->insertRows(row);
          setTableText(row, pItem);
        }

      // Update the current item only when we have more than one experiment.
      if (imax > 1)
        static_cast<CFitItem *>((*mpItemsCopy)[*mSelection.begin()])->addExperiment((*mppSet)->getExperiment(0)->CCopasiParameter::getKey());
    }

  connect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));

  // Update the current item
  setTableText(row - 1, (*mpItemsCopy)[*mSelection.begin()]);

  // Update the selection
  selectRow(row - 1);

  mpTable->adjustColumn(0);

  emit numberChanged(mpItemsCopy->size());
}

void CQFittingItemWidget::slotNew()
{
  // Save the changes to  the current items
  saveSelection();

  // Create the new item.
  COptItem * pItem;

  switch (mItemType)
    {
    case OPT_ITEM:
      pItem = new COptItem();
      break;
    case FIT_ITEM:
      pItem = new CFitItem();
      break;
    case FIT_CONSTRAINT:
      pItem = new CFitConstraint();
      break;
    }

  mpItemsCopy->push_back(pItem);

  unsigned C_INT32 row = mpTable->numRows();

  // Update the table
  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));
  mpTable->insertRows(row);
  connect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));

  setTableText(row, pItem);
  mpTable->adjustColumn(0);

  // Update the selection
  selectRow(row);

  emit numberChanged(mpItemsCopy->size());
}

void CQFittingItemWidget::setTableText(const int & row, const COptItem * pItem)
{
  QString Item = "   ";
  const CCopasiObject *pObject;

  if (pItem->getLowerBound() == "-inf" ||
      isNumber(pItem->getLowerBound()))
    Item += FROM_UTF8(pItem->getLowerBound());
  else if ((pObject = RootContainer.getObject(pItem->getLowerBound())))
    Item += FROM_UTF8(pObject->getObjectDisplayName());
  else
    Item += "Not found: " + FROM_UTF8(pItem->getLowerBound());

  Item += " < ";

  pObject = RootContainer.getObject(pItem->getObjectCN());
  if (pObject)
    Item += FROM_UTF8(pObject->getObjectDisplayName());
  else
    Item += "Not found: " + FROM_UTF8(pItem->getObjectCN());

  if (mItemType)
    {
      QString Experiments =
        FROM_UTF8(static_cast<const CFitItem *>(pItem)->getExperiments());
      if (Experiments != "")
        Item += "; {" + Experiments + "}";
    }

  Item += " < ";

  if (pItem->getUpperBound() == "inf" ||
      isNumber(pItem->getUpperBound()))
    Item += FROM_UTF8(pItem->getUpperBound());
  else if ((pObject = RootContainer.getObject(pItem->getUpperBound())))
    Item += FROM_UTF8(pObject->getObjectDisplayName());
  else
    Item += "Not found: " + FROM_UTF8(pItem->getUpperBound());

  Item += "; Start Value = " + QString::number(pItem->getStartValue());

  mpTable->setText(row, 0, Item);
}

unsigned int CQFittingItemWidget::currentRow()
{
  if (mSelection.size() != 1)
    return C_INVALID_INDEX;

  return *mSelection.begin();
}

void CQFittingItemWidget::slotSelectionChanged()
{
  saveSelection();

  unsigned int i, imax = mpTable->numRows();

  // Update mSelection;
  for (i = 0; i != imax; i++)
    if (mpTable->isRowSelected(i))
      mSelection.insert(i);
    else
      mSelection.erase(i);

  mCurrentRow = currentRow();

  loadSelection();
}

void CQFittingItemWidget::loadSelection()
{
  bool Enabled = (mSelection.size() <= 1);

  mpBtnCopy->setEnabled(Enabled);
  mpBtnPerExperiment->setEnabled(Enabled);

  std::set< unsigned int >::const_iterator it = mSelection.begin();
  std::set< unsigned int >::const_iterator end = mSelection.end();

  if (it == end)
    {
      mpEditObject->setText("");

      mpEditLower->setText("");
      mpCheckLowerInf->setChecked(true);
      mpLowerObject = NULL;

      mpEditUpper->setText("");
      mpCheckUpperInf->setChecked(true);
      mpUpperObject = NULL;

      mpEditStart->setText("");

      mpCheckAll->setChecked(true);
      mpBoxExperiments->setEnabled(false);

      QString Empty("");
      int Pos = 0;
      mpObjectValidator->validate(Empty, Pos);
    }
  else
    {
      disconnect(mpCheckAll, SIGNAL(toggled(bool)), this, SLOT(slotCheckAll(bool)));
      QString Value;

      COptItem * pItem = (*mpItemsCopy)[*it];

      const CCopasiObject *pObject = RootContainer.getObject(pItem->getObjectCN());
      if (pObject)
        {
          Value = FROM_UTF8(pObject->getObjectDisplayName());
          mpEditObject->setText(Value);
          mpObjectValidator->saved();
        }
      else
        {
          if (pItem->getObjectCN() != "")
            Value = "Not found: " + FROM_UTF8(pItem->getObjectCN());
          else
            Value = "";

          mpEditObject->setText(Value);

          int Pos = 0;
          mpObjectValidator->validate(Value, Pos);
        }

      mpLowerObject = NULL;
      if (pItem->getLowerBound() == "-inf" ||
          isNumber(pItem->getLowerBound()))
        Value = FROM_UTF8(pItem->getLowerBound());
      else if ((mpLowerObject = RootContainer.getObject(pItem->getLowerBound())))
        Value = FROM_UTF8(mpLowerObject->getObjectDisplayName());
      else
        Value = "Not found: " + FROM_UTF8(pItem->getLowerBound());

      mpEditLower->setText(Value);
      mpCheckLowerInf->setChecked(Value == "-inf");

      mpUpperObject = NULL;
      if (pItem->getUpperBound() == "inf" ||
          isNumber(pItem->getUpperBound()))
        Value = FROM_UTF8(pItem->getUpperBound());
      else if ((mpUpperObject = RootContainer.getObject(pItem->getUpperBound())))
        Value = FROM_UTF8(mpUpperObject->getObjectDisplayName());
      else
        Value = "Not found: " + FROM_UTF8(pItem->getUpperBound());

      mpEditUpper->setText(Value);
      mpCheckUpperInf->setChecked(Value == "inf");

      mpEditStart->setText(QString::number(pItem->getStartValue()));

      std::string Experiments;
      if (mItemType)
        {
          Experiments = static_cast<CFitItem *>(pItem)->getExperiments();

          mpBoxExperiments->clear();

          unsigned C_INT32 i, imax = static_cast<CFitItem *>(pItem)->getExperimentCount();
          for (i = 0; i < imax; i++)
            {
              const CCopasiObject * pObject =
                GlobalKeys.get(static_cast<CFitItem *>(pItem)->getExperiment(i));

              if (pObject)
                mpBoxExperiments->insertItem(FROM_UTF8(pObject->getObjectName()));
            }

          mpCheckAll->setChecked(!static_cast<CFitItem *>(pItem)->getExperimentCount());
          mpBoxExperiments->setEnabled(static_cast<CFitItem *>(pItem)->getExperimentCount());
        }

      for (++it; it != end; ++it)
        {
          pItem = (*mpItemsCopy)[*it];

          const CCopasiObject *pObject = RootContainer.getObject(pItem->getObjectCN());
          if (pObject)
            Value = FROM_UTF8(pObject->getObjectDisplayName());
          else
            {
              if (pItem->getObjectCN() != "")
                Value = "Not found: " + FROM_UTF8(pItem->getObjectCN());
              else
                Value = "";
            }

          if (Value != mpEditObject->text())
            {
              mpEditObject->setText("");
              mpObjectValidator->saved();
            }

          if (pItem->getLowerBound() == "-inf" ||
              isNumber(pItem->getLowerBound()))
            Value = FROM_UTF8(pItem->getLowerBound());
          else if ((pObject = RootContainer.getObject(pItem->getLowerBound())))
            Value = FROM_UTF8(pObject->getObjectDisplayName());
          else
            Value = "Not found: " + FROM_UTF8(pItem->getLowerBound());

          if (Value != mpEditLower->text())
            {
              mpEditLower->setText("");
              mpCheckLowerInf->setChecked(false);
            }

          if (pItem->getUpperBound() == "inf" ||
              isNumber(pItem->getUpperBound()))
            Value = FROM_UTF8(pItem->getUpperBound());
          else if ((pObject = RootContainer.getObject(pItem->getUpperBound())))
            Value = FROM_UTF8(pObject->getObjectDisplayName());
          else
            Value = "Not found: " + FROM_UTF8(pItem->getUpperBound());

          if (Value != mpEditUpper->text())
            {
              mpEditUpper->setText("");
              mpCheckUpperInf->setChecked(false);
            }

          if (QString::number(pItem->getStartValue()) != mpEditStart->text())
            mpEditStart->setText("");

          if (mItemType &&
              Experiments != static_cast<CFitItem *>(pItem)->getExperiments())
            {
              mpCheckAll->setChecked(false);
              mpBoxExperiments->setEnabled(false);
            }
        }

      connect(mpCheckAll, SIGNAL(toggled(bool)), this, SLOT(slotCheckAll(bool)));
    }

  mpLowerValidator->saved();
  mpUpperValidator->saved();
  mpCheckLowerInf->setPaletteBackgroundColor(mSavedColor);
  mLowerInfChanged = false;
  mpCheckUpperInf->setPaletteBackgroundColor(mSavedColor);
  mUpperInfChanged = false;
}

void CQFittingItemWidget::saveSelection()
{
  std::set< unsigned int >::const_iterator it = mSelection.begin();
  std::set< unsigned int >::const_iterator end = mSelection.end();

  COptItem * pItem;
  for (; it != end; ++it)
    {
      pItem = (*mpItemsCopy)[*it];

      if (mpCheckLowerInf->isChecked())
        pItem->setLowerBound(CCopasiObjectName("-inf"));
      else if (isNumber((const char *) mpEditLower->text().utf8()))
        pItem->setLowerBound(CCopasiObjectName((const char *) mpEditLower->text().utf8()));

      if (mpCheckUpperInf->isChecked())
        pItem->setUpperBound(CCopasiObjectName("inf"));
      else if (isNumber((const char *) mpEditUpper->text().utf8()))
        pItem->setUpperBound(CCopasiObjectName((const char *) mpEditUpper->text().utf8()));

      if (isNumber((const char *) mpEditStart->text().utf8()))
        pItem->setStartValue(mpEditStart->text().toDouble());

      mpCheckLowerInf->setPaletteBackgroundColor(mSavedColor);
      mLowerInfChanged = false;
      mpCheckUpperInf->setPaletteBackgroundColor(mSavedColor);
      mUpperInfChanged = false;
      mpObjectValidator->saved();
      mpLowerValidator->saved();
      mpUpperValidator->saved();

      setTableText(*it, pItem);
    }

  mpTable->adjustColumn(0);
}

void CQFittingItemWidget::selectRow(const unsigned int & row)
{
  // This sets the focus and creates a selection
  mpTable->setCurrentCell(row, 0);

  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));
  mpTable->clearSelection();
  connect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));

  mpTable->selectRow(row);
}

void CQFittingItemWidget::setItemSelection(const std::set< unsigned int > & selection)
{
  mSelection = selection;

  std::set< unsigned int >::const_iterator it = selection.begin();
  std::set< unsigned int >::const_iterator end = selection.end();

  // This sets the focus and creates a selection
  if (it != end)
    mpTable->setCurrentCell(*it, 0);
  else
    mpTable->setCurrentCell(C_INVALID_INDEX, 0);

  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));

  // Update selection
  mpTable->clearSelection();
  for (; it != end; ++it)
    mpTable->addSelection(QTableSelection(*it, 0, *it, 0));

  connect(mpTable, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));
}

void CQFittingItemWidget::slotLowerLostFocus()
{
  if (!isNumber((const char *) mpEditLower->text().utf8())) return;

  mpLowerObject = NULL;
  std::string Number = (const char *) mpEditLower->text().utf8();

  std::set< unsigned int >::const_iterator it = mSelection.begin();
  std::set< unsigned int >::const_iterator end = mSelection.end();

  for (; it != end; ++it)
    {
      (*mpItemsCopy)[*it]->setLowerBound(Number);
      setTableText(*it, (*mpItemsCopy)[*it]);
    }
}

void CQFittingItemWidget::slotUpperLostFocus()
{
  if (!isNumber((const char *) mpEditUpper->text().utf8())) return;

  mpUpperObject = NULL;
  std::string Number = (const char *) mpEditUpper->text().utf8();

  std::set< unsigned int >::const_iterator it = mSelection.begin();
  std::set< unsigned int >::const_iterator end = mSelection.end();

  for (; it != end; ++it)
    {
      (*mpItemsCopy)[*it]->setUpperBound(Number);
      setTableText(*it, (*mpItemsCopy)[*it]);
    }
}

void CQFittingItemWidget::slotReset()
{
  CQStartValueReset * pDialog = new CQStartValueReset(this);
  pDialog->exec();

  std::set< unsigned int >::const_iterator it = mSelection.begin();
  std::set< unsigned int >::const_iterator end = mSelection.end();

  switch (pDialog->result())
    {
    case QDialog::Rejected:
      break;

    case CQStartValueReset::MODEL:
      for (; it != end; ++it)
        {
          (*mpItemsCopy)[*it]->setStartValue(std::numeric_limits<C_FLOAT64>::quiet_NaN());
          mpEditStart->setText(QString::number((*mpItemsCopy)[*it]->getStartValue()));
          setTableText(*it, (*mpItemsCopy)[*it]);
        }
      break;

    case CQStartValueReset::RANDOM:
      for (; it != end; ++it)
        {
          (*mpItemsCopy)[*it]->randomizeStartValue();
          mpEditStart->setText(QString::number((*mpItemsCopy)[*it]->getStartValue()));
          setTableText(*it, (*mpItemsCopy)[*it]);
        }
      break;

    case CQStartValueReset::SOLUTION:
      {
        COptProblem * pProblem = dynamic_cast< COptProblem * >(mpItems->getObjectParent());
        const CVector< C_FLOAT64 > & Solution = pProblem->getSolutionVariables();
        if (Solution.size() == mpItems->size())
          for (; it != end; ++it)
            {
              (*mpItemsCopy)[*it]->setStartValue(Solution[*it]);
              mpEditStart->setText(QString::number((*mpItemsCopy)[*it]->getStartValue()));
              setTableText(*it, (*mpItemsCopy)[*it]);
            }
      }
      break;
    }

  pdelete(pDialog);

  loadSelection();
}

void CQFittingItemWidget::slotStartLostFocus()
{
  if (!isNumber((const char *) mpEditStart->text().utf8())) return;

  C_FLOAT64 Number = mpEditStart->text().toDouble();

  std::set< unsigned int >::const_iterator it = mSelection.begin();
  std::set< unsigned int >::const_iterator end = mSelection.end();

  for (; it != end; ++it)
    {
      (*mpItemsCopy)[*it]->setStartValue(Number);
      setTableText(*it, (*mpItemsCopy)[*it]);
    }
}
