/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingItemWidget.ui.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/20 18:50:45 $
   End CVS Header */

#include <qapplication.h>

#include "CCopasiSelectionDialog.h"
#include "CQValidator.h"
#include "CQExperimentSelection.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "parameterFitting/CFitItem.h"
#include "parameterFitting/CFitProblem.h"
#include "parameterFitting/CExperiment.h"
#include "parameterFitting/CExperimentSet.h"
#include "utilities/utility.h"

void CQFittingItemWidget::init()
{
  mpItem = NULL;
  mppSet = NULL;
  mpItemsCopy = new std::vector<COptItem *>;

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

      if (!mpItem) slotNew();

      mpItem->setLowerBound(Selection[0]->getCN());

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

      if (!mpItem) slotNew();

      mpItem->setUpperBound(Selection[0]->getCN());

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
  pBrowseDialog->setSingleSelection(false);
  pBrowseDialog->setOutputVector(&Selection);

  if (pBrowseDialog->exec () == QDialog::Accepted && Selection.size() != 0)
    {
      // We need to loop through the selection.
      disconnect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));

      if (!mpItem)
        {
          switch (mItemType)
            {
            case OPT_ITEM:
              mpItem = new COptItem();
              break;
            case FIT_ITEM:
              mpItem = new CFitItem();
              break;
            case FIT_CONSTRAINT:
              mpItem = new CFitConstraint();
              break;
            }

          mpItemsCopy->push_back(mpItem);
          mpTable->insertRows(0);
          setTableText(0, mpItem);
        }

      mpItem->setObjectCN(Selection[0]->getCN());
      saveItem();

      unsigned C_INT32 current = mpTable->currentRow();
      unsigned C_INT32 i, imax = Selection.size();

      for (i = 1; i != imax; i++)
        {
          COptItem * pItem;

          switch (mItemType)
            {
            case OPT_ITEM:
              pItem = new COptItem(*mpItem);
              break;
            case FIT_ITEM:
              pItem = new CFitItem(*mpItem);
              break;
            case FIT_CONSTRAINT:
              pItem = new CFitConstraint(*mpItem);
              break;
            }

          pItem->setObjectCN(Selection[i]->getCN());

          // Add the new item to the list.
          mpItemsCopy->insert(mpItemsCopy->begin() + current + i, pItem);

          // Update the table
          mpTable->insertRows(current + i);
          setTableText(current + i, pItem);
        }

      // Update the table
      mpTable->adjustColumn(0);
      mpTable->selectRow(current);
      connect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));

      loadItem(mpItem);
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
          if (!mpItem) slotNew();

          mpItem->getGroup("Affected Experiments")->clear();
          unsigned C_INT32 i, imax = mpBoxExperiments->count();

          for (i = 0; i < imax && imax < (*mppSet)->size(); i++)
            static_cast<CFitItem *>(mpItem)->addExperiment((*mppSet)->getExperiment((const char *) mpBoxExperiments->text(i).utf8())->CCopasiParameter::getKey());
        }

      mpCheckAll->setChecked(!static_cast<CFitItem *>(mpItem)->getExperimentCount());
      mpBoxExperiments->setEnabled(static_cast<CFitItem *>(mpItem)->getExperimentCount());

      delete pDialog;
    }
}

bool CQFittingItemWidget::load(CCopasiParameterGroup * pItems,
                               const std::map<std::string, std::string> * pKeyMap)
{
  mpItems = pItems;
  mpItem = NULL;

  std::vector< COptItem * >::iterator it = mpItemsCopy->begin();
  std::vector< COptItem * >::iterator end = mpItemsCopy->end();

  for (; it != end; ++it)
    pdelete(*it);

  disconnect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));
  mpTable->setNumRows(0); // This is a hack to assure proper selection on reload :(
  mpTable->setNumRows(mpItems->size());
  mpTable->clearSelection();
  connect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));

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
    mpTable->selectRow(0);
  else
    loadItem(NULL);

  mpTable->adjustColumn(0);

  emit numberChanged(mpItemsCopy->size());

  return true;
}

bool CQFittingItemWidget::loadItem(COptItem * pItem)
{
  mpItem = pItem;

  if (!pItem)
    {
      mpEditObject->setText("");

      mpEditLower->setText("");
      mpCheckLowerInf->setChecked(true);

      mpEditUpper->setText("");
      mpCheckUpperInf->setChecked(true);

      mpCheckAll->setChecked(true);
      mpBoxExperiments->setEnabled(false);

      QString Empty("");
      int Pos = 0;
      mpObjectValidator->validate(Empty, Pos);
    }
  else
    {
      QString Value;

      const CCopasiObject *pObject = RootContainer.getObject(mpItem->getObjectCN());
      if (pObject)
        {
          Value = FROM_UTF8(pObject->getObjectDisplayName());
          mpEditObject->setText(Value);
          mpObjectValidator->saved();
        }
      else
        {
          if (mpItem->getObjectCN() != "")
            Value = "Not found: " + FROM_UTF8(mpItem->getObjectCN());
          else
            Value = "";

          mpEditObject->setText(Value);

          int Pos = 0;
          mpObjectValidator->validate(Value, Pos);
        }

      if (mpItem->getLowerBound() == "-inf" ||
          isNumber(mpItem->getLowerBound()))
        Value = FROM_UTF8(mpItem->getLowerBound());
      else if ((pObject = RootContainer.getObject(mpItem->getLowerBound())))
        Value = FROM_UTF8(pObject->getObjectDisplayName());
      else
        Value = "Not found: " + FROM_UTF8(mpItem->getLowerBound());

      mpEditLower->setText(Value);
      mpCheckLowerInf->setChecked(Value == "-inf");

      if (mpItem->getUpperBound() == "inf" ||
          isNumber(mpItem->getUpperBound()))
        Value = FROM_UTF8(mpItem->getUpperBound());
      else if ((pObject = RootContainer.getObject(mpItem->getUpperBound())))
        Value = FROM_UTF8(pObject->getObjectDisplayName());
      else
        Value = "Not found: " + FROM_UTF8(mpItem->getUpperBound());

      mpEditUpper->setText(Value);
      mpCheckUpperInf->setChecked(Value == "inf");

      if (mItemType)
        {
          mpBoxExperiments->clear();

          unsigned C_INT32 i, imax = static_cast<CFitItem *>(mpItem)->getExperimentCount();
          for (i = 0; i < imax; i++)
            {
              const CCopasiObject * pObject =
                GlobalKeys.get(static_cast<CFitItem *>(mpItem)->getExperiment(i));

              if (pObject)
                mpBoxExperiments->insertItem(FROM_UTF8(pObject->getObjectName()));
            }

          mpCheckAll->setChecked(!static_cast<CFitItem *>(mpItem)->getExperimentCount());
          mpBoxExperiments->setEnabled(static_cast<CFitItem *>(mpItem)->getExperimentCount());
        }
    }

  mpLowerValidator->saved();
  mpUpperValidator->saved();
  mpCheckLowerInf->setPaletteBackgroundColor(mSavedColor);
  mLowerInfChanged = false;
  mpCheckUpperInf->setPaletteBackgroundColor(mSavedColor);
  mUpperInfChanged = false;

  return true;
}

bool CQFittingItemWidget::save(const std::map<std::string, std::string> * pKeyMap)
{
  // Make sure that the current items is saved.
  saveItem();

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

void CQFittingItemWidget::saveItem()
{
  if (!mpItem) return;

  if (mpCheckLowerInf->isChecked())
    mpItem->setLowerBound(CCopasiObjectName("-inf"));
  else if (isNumber((const char *) mpEditLower->text().utf8()))
    mpItem->setLowerBound(CCopasiObjectName((const char *) mpEditLower->text().utf8()));

  if (mpCheckUpperInf->isChecked())
    mpItem->setUpperBound(CCopasiObjectName("inf"));
  else if (isNumber((const char *) mpEditUpper->text().utf8()))
    mpItem->setUpperBound(CCopasiObjectName((const char *) mpEditUpper->text().utf8()));

  mpCheckLowerInf->setPaletteBackgroundColor(mSavedColor);
  mLowerInfChanged = false;
  mpCheckUpperInf->setPaletteBackgroundColor(mSavedColor);
  mUpperInfChanged = false;
  mpObjectValidator->saved();
  mpLowerValidator->saved();
  mpUpperValidator->saved();

  unsigned C_INT32 row;

  std::vector< COptItem * >::const_iterator it = mpItemsCopy->begin();
  std::vector< COptItem * >::const_iterator end = mpItemsCopy->end();

  for (row = 0; it != end; ++it, ++row)
    if (*it == mpItem) break;

  setTableText(row, mpItem);
  mpTable->adjustColumn(0);

  return;
}

void CQFittingItemWidget::setItemType(const ItemType & type)
{
  mItemType = type;
  pdelete(mpItem);

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
  if (!mItemType) return;

  // Remove all references to deleted experiments.
  std::vector< COptItem * >::iterator it = mpItemsCopy->begin();
  std::vector< COptItem * >::iterator end = mpItemsCopy->end();
  unsigned C_INT32 i, imax;

  // :TODO: If an experiment is deleted and another created they may have the same keys.
  for (; it != end; ++it)
    for (i = 0, imax = static_cast<CFitItem *>(*it)->getExperimentCount(); i < imax; ++i)
      if (!GlobalKeys.get(static_cast<CFitItem *>(*it)->getExperiment(i)))
        static_cast<CFitItem *>(*it)->removeExperiment(i);

  // Reload the current item.
  loadItem(mpItem);

  return;
}

void CQFittingItemWidget::setExperimentSet(const CExperimentSet * & pExperimentSet)
{mppSet = &pExperimentSet;}

void CQFittingItemWidget::slotCheckAll(bool checked)
{
  if (!checked && mpBoxExperiments->count() == 0)
    slotExperiments();

  mpBoxExperiments->setEnabled(!checked);
}

void CQFittingItemWidget::slotDelete()
{
  unsigned C_INT32 row = mpTable->currentRow();

  if (row >= mpItemsCopy->size()) return;

  COptItem * pItem = mpItem;

  // Erase the item from the vector.
  mpItemsCopy->erase(mpItemsCopy->begin() + row);

  // Update the table
  mpTable->removeRow(row);

  // Change the selection
  if (row == mpItemsCopy->size()) row--;

  if (row != C_INVALID_INDEX)
    mpTable->selectRow(row);
  else
    loadItem(NULL);

  pdelete(pItem);

  emit numberChanged(mpItemsCopy->size());
}

void CQFittingItemWidget::slotCopy()
{
  if (!mpItem)
    {
      // We have nothing to copy, therefore we create a new item.
      slotNew();
      return;
    }

  disconnect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));

  // Save the changes to  the current items
  saveItem();

  // Create the new item.
  COptItem * pItem;

  switch (mItemType)
    {
    case OPT_ITEM:
      pItem = new COptItem(*mpItem);
      break;
    case FIT_ITEM:
      pItem = new CFitItem(*mpItem);
      break;
    case FIT_CONSTRAINT:
      pItem = new CFitConstraint(*mpItem);
      break;
    }

  unsigned C_INT32 row = mpTable->currentRow() + 1;
  mpItemsCopy->insert(mpItemsCopy->begin() + row, pItem);

  // Load the item
  loadItem(pItem);

  // Update the table
  mpTable->insertRows(row);
  setTableText(row, mpItem);
  mpTable->adjustColumn(0);

  // Update the selection
  mpTable->selectRow(row);

  connect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));
  emit numberChanged(mpItemsCopy->size());
}

void CQFittingItemWidget::slotUp()
{
  unsigned C_INT32 row = mpTable->currentRow();

  if (row == C_INVALID_INDEX || row == 0) return;

  (*mpItemsCopy)[row] = (*mpItemsCopy)[row - 1];
  (*mpItemsCopy)[row - 1] = mpItem;

  QString tmp = mpTable->text(row, 0);
  mpTable->setText(row, 0, mpTable->text(row - 1, 0));
  mpTable->setText(row - 1, 0, tmp);

  disconnect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));
  mpTable->selectRow(row - 1);
  connect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));
}

void CQFittingItemWidget::slotDown()
{
  unsigned C_INT32 row = mpTable->currentRow();

  if (row >= mpItemsCopy->size() - 1) return;

  (*mpItemsCopy)[row] = (*mpItemsCopy)[row + 1];
  (*mpItemsCopy)[row + 1] = mpItem;

  QString tmp = mpTable->text(row, 0);
  mpTable->setText(row, 0, mpTable->text(row + 1, 0));
  mpTable->setText(row + 1, 0, tmp);

  disconnect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));
  mpTable->selectRow(row + 1);
  connect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));
}

void CQFittingItemWidget::slotDuplicatePerExperiment()
{
  if (!mpItem || !mItemType) return;

  disconnect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));

  // Save the changes to  the current items
  saveItem();

  unsigned C_INT32 row = mpTable->currentRow() + 1;
  unsigned C_INT32 i, imax =
    static_cast<CFitItem *>(mpItem)->getExperimentCount();

  CFitItem * pItem, * pTemplate;
  if (imax)
    {
      // We have a list of experiments
      switch (mItemType)
        {
        case FIT_ITEM:
          pTemplate = new CFitItem(*mpItem);
          break;
        case FIT_CONSTRAINT:
          pTemplate = new CFitConstraint(*mpItem);
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

          pItem->addExperiment(static_cast<CFitItem *>(mpItem)->getExperiment(i));

          static_cast<CFitItem *>(mpItem)->removeExperiment(i);

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
          pItem = new CFitItem(*mpItem);
          pItem->addExperiment((*mppSet)->getExperiment(i)->CCopasiParameter::getKey());

          mpItemsCopy->insert(mpItemsCopy->begin() + row, pItem);

          // Update the table
          mpTable->insertRows(row);
          setTableText(row, pItem);
        }

      // Update the current item only when we have more than one experiment.
      if (imax > 1)
        static_cast<CFitItem *>(mpItem)->addExperiment((*mppSet)->getExperiment(0)->CCopasiParameter::getKey());
    }

  // Update the current item
  loadItem(mpItem);
  setTableText(row - 1, mpItem);

  // Update the selection
  mpTable->selectRow(row - 1);

  mpTable->adjustColumn(0);

  connect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));
  emit numberChanged(mpItemsCopy->size());
}

void CQFittingItemWidget::slotNew()
{
  disconnect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));

  // Save the changes to  the current items
  saveItem();

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

  // Load the item
  loadItem(NULL);
  mpItem = pItem;

  // Update the table
  unsigned C_INT32 row = mpTable->numRows();
  mpTable->insertRows(row);
  setTableText(row, mpItem);
  mpTable->adjustColumn(0);

  // Update the selection
  mpTable->selectRow(row);

  connect(mpTable, SIGNAL(currentChanged(int, int)), this, SLOT(slotItemChanged(int, int)));
  emit numberChanged(mpItemsCopy->size());
}

void CQFittingItemWidget::slotItemChanged(int row, int /* col */)
{
  saveItem();

  mpTable->selectRow(row);

  loadItem((*mpItemsCopy)[row]);
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

  mpTable->setText(row, 0, Item);
}
