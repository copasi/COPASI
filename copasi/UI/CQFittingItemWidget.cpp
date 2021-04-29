// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#include "CQFittingItemWidget.h"

#include <QApplication>
#include <QPalette>
#include <QHeaderView>

#include "CCopasiSelectionDialog.h"
#include "CQValidator.h"
#include "CQExperimentSelection.h"
#include "CQStartValueReset.h"
#include "qtUtilities.h"

#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/parameterFitting/CFitItem.h"
#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/parameterFitting/CExperiment.h"
#include "copasi/parameterFitting/CExperimentSet.h"
#include "copasi/utilities/utility.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/math/CMathContainer.h"

#include <copasi/commandline/CConfigurationFile.h>

#include <QtCore/QtDebug>

/*
 *  Constructs a CQFittingItemWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQFittingItemWidget::CQFittingItemWidget(QWidget *parent, Qt::WindowFlags fl)
  : QWidget(parent, fl)
{
  setupUi(this);
  mpBtnDel->setIcon(CQIconResource::icon(CQIconResource::editDelete));
  mpBtnUp->setIcon(CQIconResource::icon(CQIconResource::moveUp));
  mpBtnUpperEdit->setIcon(CQIconResource::icon(CQIconResource::copasi));
  mpBtnLowerEdit->setIcon(CQIconResource::icon(CQIconResource::copasi));
  mpBtnObject->setIcon(CQIconResource::icon(CQIconResource::copasi));
  mpBtnNew->setIcon(CQIconResource::icon(CQIconResource::editAdd));
  mpBtnDown->setIcon(CQIconResource::icon(CQIconResource::moveDown));
  mpBtnCopy->setIcon(CQIconResource::icon(CQIconResource::editCopy));
  // mpBtnReset->setIcon(CQIconResource::icon(CQIconResource::tool));
  // mpBtnExperiments->setIcon(CQIconResource::icon(CQIconResource::tool));
  // mpBtnCrossValidations->setIcon(CQIconResource::icon(CQIconResource::tool));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFittingItemWidget::~CQFittingItemWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

void CQFittingItemWidget::init()
{
  mppExperimentSet = NULL;
  mppCrossValidationSet = NULL;
  mpItemsCopy = new std::vector<COptItem *>;
  mCurrentRow = C_INVALID_INDEX;
  setItemType(OPT_ITEM);
  mLowerInfChanged = false;
  mUpperInfChanged = false;
  mpTable->horizontalHeader()->hide();
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  mpTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
  mpTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif
  mpTable->setAlternatingRowColors(true);
  mpTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
  mpTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  int h, s, v;
  mSavedColor = palette().color(backgroundRole());
  mSavedColor.getHsv(&h, &s, &v);

  if (s < 20) s = 20;

  mChangedColor.setHsv(240, s, v);
  mpObjectValidator = new CQValidatorNotEmpty(mpEditObject);
  mpEditObject->setValidator(mpObjectValidator);
  mpObjectValidator->revalidate();
  mpLowerValidator = new CQValidatorBound(mpEditLower, "-");
  mpEditLower->setValidator(mpLowerValidator);
  mpLowerValidator->revalidate();
  mpUpperValidator = new CQValidatorBound(mpEditUpper, "+");
  mpEditUpper->setValidator(mpUpperValidator);
  mpUpperValidator->revalidate();
  mpBtnCrossValidations->hide();
  mpCheckCrossValidationsAll->hide();
  mpBoxCrossValidations->hide();
  mpLblCrossValidations->hide();
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
      mpCheckLowerInf->setStyleSheet(QString(mpCheckLowerInf->metaObject()->className()) + " {background-color:" + mChangedColor.name() + ";}");

      if (mpEditLower->isEnabled()) mpLowerValidator->revalidate();
    }
  else
    {
      mpCheckLowerInf->setStyleSheet(QString(mpCheckLowerInf->metaObject()->className()) + " {background-color:" + mSavedColor.name() + ";}");
    }

  std::string Number;

  if (checked)
    Number = "-inf";
  else if (isNumber(TO_UTF8(mpEditLower->text())))
    Number = TO_UTF8(mpEditLower->text());
  else if (mpLowerObject)
    Number = mpLowerObject->getCN();
  else return;

  std::set< size_t >::const_iterator it = mSelection.begin();
  std::set< size_t >::const_iterator end = mSelection.end();

  for (; it != end; ++it)
    {
      (*mpItemsCopy)[*it]->setLowerBound(Number);
      setTableText((int) *it, (*mpItemsCopy)[*it]);
    }
}

void CQFittingItemWidget::slotCheckUpperInf(bool checked)
{
  mpEditUpper->setEnabled(!checked);
  mUpperInfChanged = !mUpperInfChanged;

  if (mUpperInfChanged)
    {
      mpCheckUpperInf->setStyleSheet(QString(mpCheckUpperInf->metaObject()->className()) + " {background-color:" + mChangedColor.name() + ";}");

      if (mpEditUpper->isEnabled()) mpUpperValidator->revalidate();
    }
  else
    {
      mpCheckUpperInf->setStyleSheet(QString(mpCheckUpperInf->metaObject()->className()) + " {background-color:" + mSavedColor.name() + ";}");
    }

  std::string Number;

  if (checked)
    Number = "inf";
  else if (isNumber(TO_UTF8(mpEditUpper->text())))
    Number = TO_UTF8(mpEditUpper->text());
  else if (mpUpperObject)
    Number = mpUpperObject->getCN();
  else return;

  std::set< size_t >::const_iterator it = mSelection.begin();
  std::set< size_t >::const_iterator end = mSelection.end();

  for (; it != end; ++it)
    {
      (*mpItemsCopy)[*it]->setUpperBound(Number);
      setTableText((int) *it, (*mpItemsCopy)[*it]);
    }
}

void CQFittingItemWidget::slotLowerEdit()
{
  CQSimpleSelectionTree::ObjectClasses Classes;

  switch (mItemType)
    {
      case OPT_ITEM:
      case FIT_ITEM:
        Classes =
          CQSimpleSelectionTree::InitialTime |
          CQSimpleSelectionTree::Parameters |
          CQSimpleSelectionTree::ObservedConstants;
        break;

      case OPT_CONSTRAINT:
      case FIT_CONSTRAINT:
        Classes =
          CQSimpleSelectionTree::InitialTime |
          CQSimpleSelectionTree::Parameters |
          CQSimpleSelectionTree::ObservedConstants |
          CQSimpleSelectionTree::Time |
          CQSimpleSelectionTree::Variables |
          CQSimpleSelectionTree::ObservedValues;
        break;
    }

  const CDataObject *pObject =
    CCopasiSelectionDialog::getObjectSingle(this, Classes);

  if (pObject)
    {
      mpCheckLowerInf->setChecked(false);
      mpEditLower->setEnabled(true);

      if (!mSelection.size())
        slotNew();

      std::set< size_t >::const_iterator it = mSelection.begin();
      std::set< size_t >::const_iterator end = mSelection.end();
      mpLowerObject = pObject;
      CCommonName CN = mpLowerObject->getCN();

      for (; it != end; ++it)
        {
          (*mpItemsCopy)[*it]->setLowerBound(CN);
          setTableText((int) *it, (*mpItemsCopy)[*it]);
        }

      QString Value = FROM_UTF8(pObject->getObjectDisplayName());
      mpLowerValidator->force(Value);
      mpEditLower->setText(Value);
    }
}

void CQFittingItemWidget::slotUpperEdit()
{
  CQSimpleSelectionTree::ObjectClasses Classes;

  switch (mItemType)
    {
      case OPT_ITEM:
      case FIT_ITEM:
        Classes =
          CQSimpleSelectionTree::InitialTime |
          CQSimpleSelectionTree::Parameters |
          CQSimpleSelectionTree::ObservedConstants;
        break;

      case OPT_CONSTRAINT:
      case FIT_CONSTRAINT:
        Classes =
          CQSimpleSelectionTree::InitialTime |
          CQSimpleSelectionTree::Parameters |
          CQSimpleSelectionTree::ObservedConstants |
          CQSimpleSelectionTree::Time |
          CQSimpleSelectionTree::Variables |
          CQSimpleSelectionTree::ObservedValues;
        break;
    }

  const CDataObject *pObject =
    CCopasiSelectionDialog::getObjectSingle(this, Classes);

  if (pObject)
    {
      mpCheckUpperInf->setChecked(false);
      mpEditUpper->setEnabled(true);

      if (!mSelection.size())
        slotNew();

      std::set< size_t >::const_iterator it = mSelection.begin();
      std::set< size_t >::const_iterator end = mSelection.end();
      mpUpperObject = pObject;
      CCommonName CN = mpUpperObject->getCN();

      for (; it != end; ++it)
        {
          (*mpItemsCopy)[*it]->setUpperBound(CN);
          setTableText((int) *it, (*mpItemsCopy)[*it]);
        }

      QString Value = FROM_UTF8(pObject->getObjectDisplayName());
      mpUpperValidator->force(Value);
      mpEditUpper->setText(Value);
    }
}

void CQFittingItemWidget::slotParamEdit()
{
  std::vector< const CDataObject * > Selection;
  CQSimpleSelectionTree::ObjectClasses Classes;

  switch (mItemType)
    {
      case OPT_ITEM:
      case FIT_ITEM:
        Classes =
          CQSimpleSelectionTree::InitialTime |
          CQSimpleSelectionTree::Parameters;
        break;

      case OPT_CONSTRAINT:
      case FIT_CONSTRAINT:
        Classes =
          CQSimpleSelectionTree::Time |
          CQSimpleSelectionTree::Variables |
          CQSimpleSelectionTree::ObservedValues |
          CQSimpleSelectionTree::ObservedConstants |
          CQSimpleSelectionTree::Results;
        break;
    }

  int numSelected = mSelection.size();
  std::vector< const CDataObject * > currentSelection;
  currentSelection.reserve(numSelected);
  std::set< size_t >::const_iterator it = mSelection.begin();
  std::set< size_t >::const_iterator end = mSelection.end();

  if (mpDataModel)
    for (; it != end; ++it)
      {
        const COptItem * pCurrent = (*mpItemsCopy)[*it];

        if (!pCurrent || pCurrent->getObjectCN().empty())
          continue;

        const CDataObject * pObject =
          dynamic_cast<const CDataObject*>
          (mpDataModel->getObjectFromCN(pCurrent->getObjectCN()));

        if (!pObject)
          continue;

        currentSelection.push_back(pObject);
      }

  if (numSelected > 1)
    {
      const CDataObject * pObject =
        CCopasiSelectionDialog::getObjectSingle(this, Classes,
            currentSelection.empty() ? NULL :  currentSelection.front());

      if (pObject)
        Selection.push_back(pObject);
    }
  else
    {
      Selection =
        CCopasiSelectionDialog::getObjectVector(this, Classes,
            currentSelection.empty() ? NULL : &currentSelection);
    }

  if (Selection.size() != 0)
    {
      // We need to loop through the selection.
      size_t current = currentRow();
      // We must not trigger slotSelectionChanged!
      disconnect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));

      // If no item is selected create one.
      if (!mSelection.size())
        {
          COptItem *pItem;

          switch (mItemType)
            {
              case OPT_ITEM:
              case OPT_CONSTRAINT:
                pItem = new COptItem(mpDataModel);
                break;

              case FIT_ITEM:
                pItem = new CFitItem(mpDataModel);
                break;

              case FIT_CONSTRAINT:
                pItem = new CFitConstraint(mpDataModel);
                break;
            }

          mpItemsCopy->push_back(pItem);
          current = mpTable->rowCount();
          mSelection.insert(current);
          mpTable->insertRow((int) current);
          setTableText((int) current, pItem);
        }

      // Update the selected items
      std::set< size_t >::const_iterator it = mSelection.begin();
      std::set< size_t >::const_iterator end = mSelection.end();

      for (; it != end; ++it)
        {
          (*mpItemsCopy)[*it]->setObjectCN(Selection[0]->getCN());
          setTableText((int) *it, (*mpItemsCopy)[*it]);
        }

      saveSelection();
      // If one item is selected we may have no several objects
      // and must create the appropriate items
      size_t i, imax = Selection.size();
      COptItem *pSrc = (*mpItemsCopy)[*mSelection.begin()];

      for (i = 1; i != imax; i++)
        {
          COptItem *pItem;

          switch (mItemType)
            {
              case OPT_ITEM:
              case OPT_CONSTRAINT:
                pItem = new COptItem(*pSrc, NO_PARENT);
                break;

              case FIT_ITEM:
                pItem = new CFitItem(*pSrc, NO_PARENT);
                break;

              case FIT_CONSTRAINT:
                pItem = new CFitConstraint(*pSrc, NO_PARENT);
                break;
            }

          pItem->setObjectCN(Selection[i]->getCN());
          // Add the new item to the list.
          mpItemsCopy->insert(mpItemsCopy->begin() + current + i, pItem);
          // Update the table
          mpTable->insertRow((int)(current + i));
          setTableText((int)(current + i), pItem);
        }

      connect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));

      // Update the selection;
      if (current != C_INVALID_INDEX)
        selectRow(current);
      else
        loadSelection();

      emit numberChanged((int) mpItemsCopy->size());
    }
}

void CQFittingItemWidget::slotExperiments()
{
  if (mItemType == FIT_ITEM || mItemType == FIT_CONSTRAINT)
    {
      CQExperimentSelection *pDialog = new CQExperimentSelection(this);
      pDialog->load(mpBoxExperiments, * mppExperimentSet);

      if (pDialog->exec() == QDialog::Accepted)
        {
          if (!mSelection.size())
            slotNew();

          std::set< size_t >::const_iterator it = mSelection.begin();
          std::set< size_t >::const_iterator end = mSelection.end();

          for (; it != end; ++it)
            {
              (*mpItemsCopy)[*it]->getGroup("Affected Experiments")->clear();
              size_t i, imax = mpBoxExperiments->count();

              for (i = 0; i < imax && imax < (*mppExperimentSet)->getExperimentCount(); i++)
                static_cast<CFitItem *>((*mpItemsCopy)[*it])->addExperiment((*mppExperimentSet)->getExperiment(TO_UTF8(mpBoxExperiments->itemText((int) i)))->CCopasiParameter::getKey());

              setTableText((int) *it, (*mpItemsCopy)[*it]);
            }
        }

      loadSelection();
      delete pDialog;
    }
}

bool CQFittingItemWidget::load(CDataModel *pDataModel,
                               CCopasiParameterGroup *pItems,
                               const std::map<std::string, std::string> *pExperimentMap,
                               const std::map<std::string, std::string> *pCrossValidationMap)
{
  mpDataModel = pDataModel;
  mpItems = pItems;
  mSelection.clear();
  std::vector< COptItem * >::iterator it = mpItemsCopy->begin();
  std::vector< COptItem * >::iterator end = mpItemsCopy->end();

  for (; it != end; ++it)
    pdelete(*it);

  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));
  mpTable->setRowCount((int) mpItems->size());
  connect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));
  mCurrentRow = C_INVALID_INDEX;
  mpItemsCopy->resize(mpItems->size());
  it = mpItemsCopy->begin();
  end = mpItemsCopy->end();
  std::vector< COptItem * >::const_iterator src =
    mpItems->CCopasiParameter::getValue< std::vector< COptItem * > >().begin();
  size_t i;

  for (i = 0; it != end; ++it, ++src, ++i)
    {
      switch (mItemType)
        {
          case OPT_ITEM:
          case OPT_CONSTRAINT:
            *it = new COptItem(**src, NO_PARENT);
            break;

          case FIT_ITEM:
            *it = new CFitItem(**src, NO_PARENT);
            break;

          case FIT_CONSTRAINT:
            *it = new CFitConstraint(**src, NO_PARENT);
            break;
        }

      if (mItemType == FIT_ITEM || mItemType == FIT_CONSTRAINT)
        {
          if (!pExperimentMap) return false;

          CFitItem *fitItem = static_cast<CFitItem *>(*it);
          // Change the key to reflect the local copy *mppExperimentSet
          size_t j, jmax = fitItem->getExperimentCount();

          for (j = 0; j < jmax; j++)
            {
              std::string &Key =
                *const_cast<std::string *>(&fitItem->getExperiment(j));

              if (Key.empty())
                {
                  CCopasiMessage(CCopasiMessage::ERROR, "Could not find experiment for fit item '%s'.", fitItem->getObjectCN().c_str());
                  continue;
                }

              Key = pExperimentMap->find(Key)->second;
            }

          if (!pCrossValidationMap) return false;

          // Change the key to reflect the local copy *mppCrossValidationSet
          jmax = fitItem->getCrossValidationCount();

          for (j = 0; j < jmax; j++)
            {
              std::string &Key =
                *const_cast<std::string *>(&fitItem->getCrossValidation(j));

              if (Key.empty())
                {
                  CCopasiMessage(CCopasiMessage::ERROR, "Could not find cross validation set for fit item '%s'.", fitItem->getObjectCN().c_str());
                  continue;
                }

              Key = pCrossValidationMap->find(Key)->second;
            }
        }

      setTableText((int) i, *it);
    }

  if (mpItemsCopy->size())
    selectRow(0);
  else
    selectRow(C_INVALID_INDEX);

  emit numberChanged((int) mpItemsCopy->size());

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTable->resizeRowsToContents();
    }

  return true;
}

bool CQFittingItemWidget::save(const std::map<std::string, std::string> *pExperimentMap,
                               const std::map<std::string, std::string> *pCrossValidationMap)
{
  // Make sure that the current items is saved.
  saveSelection();
  bool changed = false;
  std::vector< COptItem * >::const_iterator it = mpItemsCopy->begin();
  std::vector< COptItem * >::const_iterator end = mpItemsCopy->end();
  std::vector< COptItem * >::iterator target =
    mpItems->CCopasiParameter::getValue< std::vector< COptItem * > >().begin();
  std::vector< COptItem * >::iterator targetEnd =
    mpItems->CCopasiParameter::getValue< std::vector< COptItem * > >().end();
  size_t i;
  size_t imax = std::max<size_t>(mpItemsCopy->size(), mpItems->size());

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

      if (mItemType == FIT_ITEM || mItemType == FIT_CONSTRAINT)
        {
          if (pExperimentMap == NULL) return false;

          size_t j, jmax =
            std::min(static_cast<CFitItem *>(*it)->getExperimentCount(),
                     static_cast<CFitItem *>(*target)->getExperimentCount());

          // Compare and assign common experiments
          for (j = 0; j < jmax; j++)
            {
              std::string &Target =
                *const_cast<std::string *>(&static_cast<CFitItem *>(*target)->getExperiment(j));
              const std::string &Key = static_cast<CFitItem *>(*it)->getExperiment(j);

              if (Key.empty())
                {
                  continue;
                }

              std::map<std::string, std::string>::const_iterator found = pExperimentMap->find(Key);

              if (found == pExperimentMap->end())
                {
                  continue;
                }

              if (Target != found->second)
                {
                  changed = true;
                  Target = found->second;
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
              const std::string &Source =
                pExperimentMap->find(static_cast<CFitItem *>(*it)->getExperiment(j))->second;
              static_cast<CFitItem *>(*target)->addExperiment(Source);
            }

          if (pCrossValidationMap == NULL) return false;

          jmax =
            std::min(static_cast<CFitItem *>(*it)->getCrossValidationCount(),
                     static_cast<CFitItem *>(*target)->getCrossValidationCount());

          // Compare and assign common cross validations
          for (j = 0; j < jmax; j++)
            {
              std::string &Target =
                *const_cast<std::string *>(&static_cast<CFitItem *>(*target)->getCrossValidation(j));
              const std::string &Key = static_cast<CFitItem *>(*it)->getCrossValidation(j);

              if (Key.empty())
                {
                  continue;
                }

              std::map<std::string, std::string>::const_iterator found = pCrossValidationMap->find(Key);

              if (found == pCrossValidationMap->end())
                {
                  continue;
                }

              if (Target != found->second)
                {
                  changed = true;
                  Target = found->second;
                }
            }

          // Remove exceeding cross validations starting from the last
          for (jmax = static_cast<CFitItem *>(*target)->getCrossValidationCount() - 1;
               j <= jmax && jmax != C_INVALID_INDEX; jmax--)
            {
              changed = true;
              static_cast<CFitItem *>(*target)->removeCrossValidation(jmax);
            }

          // Add missing cross validations
          for (jmax = static_cast<CFitItem *>(*it)->getCrossValidationCount(); j < jmax; j++)
            {
              changed = true;
              const std::string &Source =
                pCrossValidationMap->find(static_cast<CFitItem *>(*it)->getCrossValidation(j))->second;
              static_cast<CFitItem *>(*target)->addCrossValidation(Source);
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
      COptItem *pItem = NULL;

      switch (mItemType)
        {
          case OPT_ITEM:
          case OPT_CONSTRAINT:
            pItem = new COptItem(**it, NO_PARENT);
            break;

          case FIT_ITEM:
            pItem = new CFitItem(**it, NO_PARENT);
            break;

          case FIT_CONSTRAINT:
            pItem = new CFitConstraint(**it, NO_PARENT);
            break;
        }

      if (mItemType == FIT_ITEM || mItemType == FIT_CONSTRAINT)
        {
          if (pExperimentMap == NULL) return false;

          size_t j, jmax =
            static_cast<CFitItem *>(pItem)->getExperimentCount();

          // Remap the experiment keys
          for (j = 0; j < jmax; j++)
            {
              std::string &Target =
                *const_cast<std::string *>(&static_cast<CFitItem *>(pItem)->getExperiment(j));
              const std::string &Source =
                pExperimentMap->find(static_cast<CFitItem *>(*it)->getExperiment(j))->second;
              Target = Source;
            }
        }

      mpItems->addParameter(pItem);
    }

  return changed;
}

void CQFittingItemWidget::setItemType(const ItemType &type)
{
  mItemType = type;

  if (mItemType == FIT_ITEM || mItemType == FIT_CONSTRAINT)
    {
      mpLblExperiments->show();
      mpCheckAll->show();
      mpBoxExperiments->show();
      mpBtnExperiments->show();
      mpBtnPerExperiment->show();
      mpLblCrossValidations->show();
      mpCheckCrossValidationsAll->show();
      mpBoxCrossValidations->show();
      mpBtnCrossValidations->show();
    }
  else
    {
      mpLblExperiments->hide();
      mpCheckAll->hide();
      mpBoxExperiments->hide();
      mpBtnExperiments->hide();
      mpBtnPerExperiment->hide();
      mpLblCrossValidations->hide();
      mpCheckCrossValidationsAll->hide();
      mpBoxCrossValidations->hide();
      mpBtnCrossValidations->hide();
    }

  if (mItemType == OPT_CONSTRAINT || mItemType == FIT_CONSTRAINT)
    {
      mpLblStart->hide();
      mpEditStart->hide();
      mpBtnReset->hide();
    }
  else
    {
      mpLblStart->show();
      mpEditStart->show();
      mpBtnReset->show();
    }

  qApp->processEvents();
}

void CQFittingItemWidget::slotExperimentChanged()
{
  // This slot is triggered when an experiment is deleted or changed,
  // but before new experiments are created.
  if (mItemType == OPT_ITEM || mItemType == OPT_CONSTRAINT) return;

  // Remove all references to deleted experiments.
  std::vector< COptItem * >::iterator it = mpItemsCopy->begin();
  std::vector< COptItem * >::iterator end = mpItemsCopy->end();
  size_t i, imax;
  size_t Row;

  for (Row = 0; it != end; ++it, ++Row)
    {
      for (i = 0, imax = static_cast<CFitItem *>(*it)->getExperimentCount(); i < imax; ++i)
        if (!CRootContainer::getKeyFactory()->get(static_cast<CFitItem *>(*it)->getExperiment(i)))
          static_cast<CFitItem *>(*it)->removeExperiment(i);

      setTableText((int) Row, *it);
    }

  // Reload the current item.
  loadSelection();
  return;
}

void CQFittingItemWidget::setExperimentSet(const CExperimentSet *&pExperimentSet)
{mppExperimentSet = &pExperimentSet;}

void CQFittingItemWidget::slotDelete()
{
  size_t row = mCurrentRow;
  COptItem *pItem;
  std::set< size_t >::const_iterator it = mSelection.begin();
  std::set< size_t >::const_iterator end = mSelection.end();
  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));
  size_t Deleted = 0;

  for (; it != end; ++it, ++Deleted)
    {
      row = *it - Deleted;
      pItem = (*mpItemsCopy)[row];
      // Erase the item from the vector.
      mpItemsCopy->erase(mpItemsCopy->begin() + row);
      // Update the table
      mpTable->removeRow((int) row);
      pdelete(pItem);
    }

  mpTable->clearSelection();
  mSelection.clear();
  connect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));

  // Change the selection
  if (row >= mpItemsCopy->size())
    row = mpItemsCopy->size() - 1;

  selectRow(row);
  emit numberChanged((int) mpItemsCopy->size());
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
  COptItem *pItem;
  COptItem *pSrc = (*mpItemsCopy)[*mSelection.begin()];

  switch (mItemType)
    {
      case OPT_ITEM:
      case OPT_CONSTRAINT:
        pItem = new COptItem(*pSrc, NO_PARENT);
        break;

      case FIT_ITEM:
        pItem = new CFitItem(*pSrc, NO_PARENT);
        break;

      case FIT_CONSTRAINT:
        pItem = new CFitConstraint(*pSrc, NO_PARENT);
        break;
    }

  size_t row = mCurrentRow + 1;
  mpItemsCopy->insert(mpItemsCopy->begin() + row, pItem);
  // Update the table
  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));
  //  mpTable->insertRows(row);
  mpTable->insertRow((int) row);
  connect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));
  setTableText((int) row, pItem);
  // Update the selection
  selectRow(row);
  emit numberChanged((int) mpItemsCopy->size());
}

void CQFittingItemWidget::slotUp()
{
  if (!mSelection.size()) return; // Nothing to move.

  saveSelection();
  std::set< size_t > NewSelection;
  std::set< size_t >::const_iterator it = mSelection.begin();
  std::set< size_t >::const_iterator end = mSelection.end();
  COptItem *pItem;

  if (*it == 0) ++it; // The first row can not be moved up.

  for (; it != end; ++it)
    {
      NewSelection.insert(*it - 1);
      // Swap the items
      pItem = (*mpItemsCopy)[*it];
      (*mpItemsCopy)[*it] = (*mpItemsCopy)[*it - 1];
      (*mpItemsCopy)[*it - 1] = pItem;
      // Swap the table rows
      QTableWidgetItem *item1 = mpTable->takeItem((int)(*it - 1), 0);
      QTableWidgetItem *item2 = mpTable->takeItem((int) * it, 0);
      mpTable->setItem((int) *it, 0, item1);
      mpTable->setItem((int)(*it - 1), 0, item2);
    }

  setItemSelection(NewSelection);
  loadSelection();
}

void CQFittingItemWidget::slotDown()
{
  if (!mSelection.size()) return; // Nothing to move.

  saveSelection();
  std::set< size_t > NewSelection;
  std::set< size_t >::reverse_iterator it = mSelection.rbegin();
  std::set< size_t >::reverse_iterator end = mSelection.rend();
  COptItem *pItem;

  if ((int) *it == (mpTable->rowCount() - 1))
    ++it; // The last row can not be moved down.

  for (; it != end; ++it)
    {
      NewSelection.insert(*it + 1);
      // Swap the items
      pItem = (*mpItemsCopy)[*it];
      (*mpItemsCopy)[*it] = (*mpItemsCopy)[*it + 1];
      (*mpItemsCopy)[*it + 1] = pItem;
      // Swap the table rows
      QTableWidgetItem *item1 = mpTable->takeItem((int)(*it + 1), 0);
      QTableWidgetItem *item2 = mpTable->takeItem((int) * it, 0);
      mpTable->setItem((int) *it, 0, item1);
      mpTable->setItem((int)(*it + 1), 0, item2);
    }

  setItemSelection(NewSelection);
  loadSelection();
}

void CQFittingItemWidget::slotDuplicatePerExperiment()
{
  if (mItemType == OPT_ITEM || mItemType == OPT_CONSTRAINT) return;

  // Save the changes to  the current items
  saveSelection();

  if (!mSelection.size())
    slotNew();

  size_t row = mCurrentRow + 1;
  size_t i, imax =
    static_cast<CFitItem *>((*mpItemsCopy)[*mSelection.begin()])->getExperimentCount();
  CFitItem *pItem = NULL, * pTemplate = NULL;
  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));

  if (imax)
    {
      // We have a list of experiments
      switch (mItemType)
        {
          case FIT_ITEM:
            pTemplate = new CFitItem(*(*mpItemsCopy)[*mSelection.begin()], NO_PARENT);
            break;

          case FIT_CONSTRAINT:
            pTemplate = new CFitConstraint(*(*mpItemsCopy)[*mSelection.begin()], NO_PARENT);
            break;

          default:
            break;
        }

      // Remove all experiments from the template
      for (i = imax - 1; i != C_INVALID_INDEX; i--)
        pTemplate->removeExperiment(i);

      // Create imax - 1 copies
      for (i = imax - 1; i != 0; i--)
        {
          switch (mItemType)
            {
              case FIT_ITEM:
                pItem = new CFitItem(*pTemplate, NO_PARENT);
                break;

              case FIT_CONSTRAINT:
                pItem = new CFitConstraint(*pTemplate, NO_PARENT);
                break;

              default:
                break;
            }

          pItem->addExperiment(static_cast<CFitItem *>((*mpItemsCopy)[*mSelection.begin()])->getExperiment(i));
          static_cast<CFitItem *>((*mpItemsCopy)[*mSelection.begin()])->removeExperiment(i);
          mpItemsCopy->insert(mpItemsCopy->begin() + row, pItem);
          // Update the table
          mpTable->insertRow((int) row);
          setTableText((int) row, pItem);
        }
    }
  else
    {
      // We have ALL
      imax = (*mppExperimentSet)->getExperimentCount();

      if (imax > 0)
        {
          // Create imax - 1 copies
          for (i = imax - 1; i != 0; i--)
            {
              pItem = new CFitItem(*(*mpItemsCopy)[*mSelection.begin()], NO_PARENT);
              pItem->addExperiment((*mppExperimentSet)->getExperiment(i)->CCopasiParameter::getKey());
              mpItemsCopy->insert(mpItemsCopy->begin() + row, pItem);
              // Update the table
              mpTable->insertRow((int) row);
              setTableText((int) row, pItem);
            }
        }

      // Update the current item only when we have more than one experiment.
      if (imax > 1)
        static_cast<CFitItem *>((*mpItemsCopy)[*mSelection.begin()])->addExperiment((*mppExperimentSet)->getExperiment(0)->CCopasiParameter::getKey());
    }

  connect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));
  // Update the current item
  setTableText((int)(row - 1), (*mpItemsCopy)[*mSelection.begin()]);
  // Update the selection
  selectRow(row - 1);
  emit numberChanged((int) mpItemsCopy->size());
}

void CQFittingItemWidget::slotNew()
{
  // Save the changes to  the current items
  saveSelection();
  // Create the new item.
  COptItem *pItem;

  switch (mItemType)
    {
      case OPT_ITEM:
      case OPT_CONSTRAINT:
        pItem = new COptItem(mpDataModel);
        break;

      case FIT_ITEM:
        pItem = new CFitItem(mpDataModel);
        break;

      case FIT_CONSTRAINT:
        pItem = new CFitConstraint(mpDataModel);
        break;
    }

  mpItemsCopy->push_back(pItem);
  size_t row = mpTable->rowCount();
  // Update the table
  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));
  // mpTable->insertRows(row);
  mpTable->insertRow((int) row);
  connect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));
  setTableText((int) row, pItem);
  // Update the selection
  selectRow(row);
  emit numberChanged((int) mpItemsCopy->size());
}

void CQFittingItemWidget::setTableText(const int &row, const COptItem *pItem)
{
  QString Item = "   ";
  const CObjectInterface *pObject;

  if (pItem->getLowerBound() == "-inf" ||
      isNumber(pItem->getLowerBound()))
    Item += FROM_UTF8(pItem->getLowerBound());
  else if ((pObject = mpDataModel->getObjectFromCN(pItem->getLowerBound())))
    Item += FROM_UTF8(pObject->getObjectDisplayName());
  else
    Item += "Not found: " + FROM_UTF8(pItem->getLowerBound());

  // Insert less than character
  Item += FROM_UTF8(std::string(" \xe2\x89\xa4 "));
  pObject = mpDataModel->getObjectFromCN(pItem->getObjectCN());

  if (pObject)
    Item += FROM_UTF8(pObject->getObjectDisplayName());
  else
    Item += "Not found: " + FROM_UTF8(pItem->getObjectCN());

  if (mItemType == FIT_ITEM || mItemType == FIT_CONSTRAINT)
    {
      QString Experiments =
        FROM_UTF8(static_cast<const CFitItem *>(pItem)->getExperiments());

      if (Experiments != "")
        Item += "; {" + Experiments + "}";
    }

  // Insert less than character
  Item += FROM_UTF8(std::string(" \xe2\x89\xa4 "));

  if (pItem->getUpperBound() == "inf" ||
      isNumber(pItem->getUpperBound()))
    Item += FROM_UTF8(pItem->getUpperBound());
  else if ((pObject = mpDataModel->getObjectFromCN(pItem->getUpperBound())))
    Item += FROM_UTF8(pObject->getObjectDisplayName());
  else
    Item += "Not found: " + FROM_UTF8(pItem->getUpperBound());

  if (mItemType == OPT_ITEM || mItemType == FIT_ITEM)
    {
      Item += "; Start Value = " + convertToQString(pItem->getStartValue());
    }

  QTableWidgetItem *itemValue = new QTableWidgetItem(Item);
  itemValue->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
  itemValue->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  mpTable->setItem(row, 0, itemValue);
  mpTable->resizeRowToContents(row);
}

size_t CQFittingItemWidget::currentRow()
{
  if (mSelection.size() != 1)
    return C_INVALID_INDEX;

  return *mSelection.begin();
}

void CQFittingItemWidget::slotSelectionChanged()
{
  saveSelection();
  size_t i, imax = mpTable->rowCount();

  // Update mSelection;
  for (i = 0; i != imax; i++)
    if (mpTable->item((int) i, 0)->isSelected())
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
  std::set< size_t >::const_iterator it = mSelection.begin();
  std::set< size_t >::const_iterator end = mSelection.end();

  if (it == end)
    {
      mpEditObject->setText("");
      mpEditLower->setText(convertToQString(1e-06));
      mpCheckLowerInf->setChecked(false);
      mpLowerObject = NULL;
      mpEditUpper->setText(convertToQString(1e+06));
      mpCheckUpperInf->setChecked(false);
      mpUpperObject = NULL;
      mpEditStart->setText("");
      mpCheckAll->setChecked(true);
      mpBoxExperiments->setEnabled(false);
      mpCheckCrossValidationsAll->setChecked(true);
      mpBoxCrossValidations->setEnabled(false);
      QString Empty("");
      int Pos = 0;
      mpObjectValidator->validate(Empty, Pos);
    }
  else
    {
      disconnect(mpCheckAll, SIGNAL(toggled(bool)), this, SLOT(slotCheckAllExperiments(bool)));
      disconnect(mpCheckCrossValidationsAll, SIGNAL(toggled(bool)), this, SLOT(slotCheckAllCrossValidations(bool)));
      QString Value;
      COptItem *pItem = (*mpItemsCopy)[*it];
      const CObjectInterface *pObject = mpDataModel->getObjectFromCN(pItem->getObjectCN());

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
      else if ((mpLowerObject = mpDataModel->getObjectFromCN(pItem->getLowerBound())))
        Value = FROM_UTF8(mpLowerObject->getObjectDisplayName());
      else
        Value = "Not found: " + FROM_UTF8(pItem->getLowerBound());

      mpEditLower->setText(Value);
      mpCheckLowerInf->setChecked(Value == "-inf");
      mpUpperObject = NULL;

      if (pItem->getUpperBound() == "inf" ||
          isNumber(pItem->getUpperBound()))
        Value = FROM_UTF8(pItem->getUpperBound());
      else if ((mpUpperObject = mpDataModel->getObjectFromCN(pItem->getUpperBound())))
        Value = FROM_UTF8(mpUpperObject->getObjectDisplayName());
      else
        Value = "Not found: " + FROM_UTF8(pItem->getUpperBound());

      mpEditUpper->setText(Value);
      mpCheckUpperInf->setChecked(Value == "inf");
      mpEditStart->setText(convertToQString(pItem->getStartValue()));
      std::string Experiments;
      std::string CrossValidations;

      if (mItemType == FIT_ITEM || mItemType == FIT_CONSTRAINT)
        {
          Experiments = static_cast<CFitItem *>(pItem)->getExperiments();
          mpBoxExperiments->clear();
          size_t i, imax = static_cast<CFitItem *>(pItem)->getExperimentCount();

          for (i = 0; i < imax; i++)
            {
              const CDataObject *pObject =
                CRootContainer::getKeyFactory()->get(static_cast<CFitItem *>(pItem)->getExperiment(i));

              if (pObject)
                mpBoxExperiments->insertItem(mpBoxExperiments->count(), FROM_UTF8(pObject->getObjectName()));
            }

          mpCheckAll->setChecked(imax == 0);
          mpBoxExperiments->setEnabled(imax != 0);
          CrossValidations = static_cast<CFitItem *>(pItem)->getCrossValidations();
          mpBoxCrossValidations->clear();
          imax = static_cast<CFitItem *>(pItem)->getCrossValidationCount();

          for (i = 0; i < imax; i++)
            {
              const CDataObject *pObject =
                CRootContainer::getKeyFactory()->get(static_cast<CFitItem *>(pItem)->getCrossValidation(i));

              if (pObject)
                mpBoxCrossValidations->insertItem(0, FROM_UTF8(pObject->getObjectName()));
            }

          mpCheckCrossValidationsAll->setChecked(imax == 0);
          mpBoxCrossValidations->setEnabled(imax != 0);
        }

      for (++it; it != end; ++it)
        {
          pItem = (*mpItemsCopy)[*it];
          const CObjectInterface *pObject = mpDataModel->getObjectFromCN(pItem->getObjectCN());

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
          else if ((pObject = mpDataModel->getObjectFromCN(pItem->getLowerBound())))
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
          else if ((pObject = mpDataModel->getObjectFromCN(pItem->getUpperBound())))
            Value = FROM_UTF8(pObject->getObjectDisplayName());
          else
            Value = "Not found: " + FROM_UTF8(pItem->getUpperBound());

          if (Value != mpEditUpper->text())
            {
              mpEditUpper->setText("");
              mpCheckUpperInf->setChecked(false);
            }

          if (convertToQString(pItem->getStartValue()) != mpEditStart->text())
            mpEditStart->setText("");

          if ((mItemType == FIT_ITEM || mItemType == FIT_CONSTRAINT) &&
              Experiments != static_cast<CFitItem *>(pItem)->getExperiments())
            {
              mpCheckAll->setChecked(false);
              mpBoxExperiments->setEnabled(false);
            }

          if ((mItemType == FIT_ITEM || mItemType == FIT_CONSTRAINT) &&
              CrossValidations != static_cast<CFitItem *>(pItem)->getCrossValidations())
            {
              mpCheckCrossValidationsAll->setChecked(false);
              mpBoxCrossValidations->setEnabled(false);
            }
        }

      connect(mpCheckAll, SIGNAL(toggled(bool)), this, SLOT(slotCheckAllExperiments(bool)));
      connect(mpCheckCrossValidationsAll, SIGNAL(toggled(bool)), this, SLOT(slotCheckAllCrossValidations(bool)));
    }

  mpLowerValidator->saved();
  mpUpperValidator->saved();
  mpCheckLowerInf->setStyleSheet(QString(mpCheckLowerInf->metaObject()->className()) + " {background-color:" + mSavedColor.name() + ";}");
  mLowerInfChanged = false;
  mpCheckUpperInf->setStyleSheet(QString(mpCheckUpperInf->metaObject()->className()) + " {background-color:" + mSavedColor.name() + ";}");
  mUpperInfChanged = false;
}

void CQFittingItemWidget::saveSelection()
{
  std::set< size_t >::const_iterator it = mSelection.begin();
  std::set< size_t >::const_iterator end = mSelection.end();
  COptItem *pItem;

  for (; it != end; ++it)
    {
      pItem = (*mpItemsCopy)[*it];

      if (mpCheckLowerInf->isChecked())
        pItem->setLowerBound(CCommonName("-inf"));
      else if (isNumber(TO_UTF8(mpEditLower->text())))
        pItem->setLowerBound(CCommonName(TO_UTF8(mpEditLower->text())));

      if (mpCheckUpperInf->isChecked())
        pItem->setUpperBound(CCommonName("inf"));
      else if (isNumber(TO_UTF8(mpEditUpper->text())))
        pItem->setUpperBound(CCommonName(TO_UTF8(mpEditUpper->text())));

      if (isNumber(TO_UTF8(mpEditStart->text())))
        pItem->setStartValue(mpEditStart->text().toDouble());

      mpCheckLowerInf->setStyleSheet(QString(mpCheckLowerInf->metaObject()->className()) + " {background-color:" + mSavedColor.name() + ";}");
      mLowerInfChanged = false;
      mpCheckUpperInf->setStyleSheet(QString(mpCheckUpperInf->metaObject()->className()) + " {background-color:" + mSavedColor.name() + ";}");
      mUpperInfChanged = false;
      mpObjectValidator->saved();
      mpLowerValidator->saved();
      mpUpperValidator->saved();
      setTableText((int) *it, pItem);
    }
}

void CQFittingItemWidget::selectRow(const size_t &row)
{
  if (row == C_INVALID_INDEX)
    {
      mSelection.clear();
      return loadSelection();
    }

  // This sets the focus and creates a selection
  mpTable->setCurrentCell((int) row, 0);
  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));
  mpTable->clearSelection();
  connect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));
  mpTable->selectRow((int) row);
}

void CQFittingItemWidget::setItemSelection(const std::set< size_t > &selection)
{
  mSelection = selection;
  std::set< size_t >::const_iterator it = selection.begin();
  std::set< size_t >::const_iterator end = selection.end();
  // We must not trigger slotSelectionChanged!
  disconnect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));

  // This sets the focus and creates a selection
  if (it != end)
    mpTable->setCurrentCell((int) *it, 0);
  else
    mpTable->setCurrentCell(-1, 0);

  // Update selection
  for (; it != end; ++it)
    mpTable->item((int) *it, 0)->setSelected(true);

  connect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectionChanged()));
}

void CQFittingItemWidget::slotLowerLostFocus()
{
  std::string Number = TO_UTF8(mpEditLower->text());

  if (!isNumber(Number) &&
      !(Number[0] == '-' &&
        Number[Number.length() - 1] == '%' &&
        isNumber(Number.substr(1, Number.length() - 2)))) return;

  mpLowerObject = NULL;
  bool first = true;
  std::string NewValue = "";
  std::set< size_t >::const_iterator it = mSelection.begin();
  std::set< size_t >::const_iterator end = mSelection.end();

  for (; it != end; ++it)
    {
      (*mpItemsCopy)[*it]->setLowerBound(Number);

      if (first)
        {
          NewValue = (*mpItemsCopy)[*it]->getLowerBound();
          first = false;
        }
      else if (NewValue != (*mpItemsCopy)[*it]->getLowerBound())
        NewValue = "";

      setTableText((int) *it, (*mpItemsCopy)[*it]);
    }

  mpEditLower->setText(FROM_UTF8(NewValue));
}

void CQFittingItemWidget::slotUpperLostFocus()
{
  std::string Number = TO_UTF8(mpEditUpper->text());

  if (!isNumber(Number) &&
      !(Number[0] == '+' &&
        Number[Number.length() - 1] == '%' &&
        isNumber(Number.substr(1, Number.length() - 2)))) return;

  mpUpperObject = NULL;
  std::set< size_t >::const_iterator it = mSelection.begin();
  std::set< size_t >::const_iterator end = mSelection.end();
  bool first = true;
  std::string NewValue = "";

  for (; it != end; ++it)
    {
      (*mpItemsCopy)[*it]->setUpperBound(Number);

      if (first)
        {
          NewValue = (*mpItemsCopy)[*it]->getUpperBound();
          first = false;
        }
      else if (NewValue != (*mpItemsCopy)[*it]->getUpperBound())
        NewValue = "";

      setTableText((int) *it, (*mpItemsCopy)[*it]);
    }

  mpEditUpper->setText(FROM_UTF8(NewValue));
}

void CQFittingItemWidget::slotReset()
{
  CQStartValueReset *pDialog = new CQStartValueReset(this);
  pDialog->exec();
  std::set< size_t >::const_iterator it = mSelection.begin();
  std::set< size_t >::const_iterator end = mSelection.end();

  switch (pDialog->result())
    {
      case QDialog::Rejected:
        break;

      case CQStartValueReset::MODEL:
        for (; it != end; ++it)
          {
            (*mpItemsCopy)[*it]->setStartValue(std::numeric_limits<C_FLOAT64>::quiet_NaN());
            mpEditStart->setText(convertToQString((*mpItemsCopy)[*it]->getStartValue()));
            setTableText((int) *it, (*mpItemsCopy)[*it]);
          }

        break;

      case CQStartValueReset::RANDOM:
      {
        CRandom &Random = mpDataModel->getModel()->getMathContainer().getRandomGenerator();

        for (; it != end; ++it)
          {
            (*mpItemsCopy)[*it]->setStartValue((*mpItemsCopy)[*it]->getRandomValue(Random));
            mpEditStart->setText(convertToQString((*mpItemsCopy)[*it]->getStartValue()));
            setTableText((int) *it, (*mpItemsCopy)[*it]);
          }
      }
      break;

      case CQStartValueReset::SOLUTION:
      {
        COptProblem *pProblem = dynamic_cast< COptProblem * >(mpItems->getObjectParent());
        const CVector< C_FLOAT64 > &Solution = pProblem->getSolutionVariables();

        if (Solution.size() > 0 && Solution.size() == mpItems->size())
          for (; it != end; ++it)
            {
              (*mpItemsCopy)[*it]->setStartValue(Solution[*it]);
              mpEditStart->setText(convertToQString((*mpItemsCopy)[*it]->getStartValue()));
              setTableText((int) *it, (*mpItemsCopy)[*it]);
            }
      }
      break;
    }

  pdelete(pDialog);
  loadSelection();
}

void CQFittingItemWidget::slotStartLostFocus()
{
  if (!isNumber(TO_UTF8(mpEditStart->text()))) return;

  C_FLOAT64 Number = mpEditStart->text().toDouble();
  std::set< size_t >::const_iterator it = mSelection.begin();
  std::set< size_t >::const_iterator end = mSelection.end();

  for (; it != end; ++it)
    {
      (*mpItemsCopy)[*it]->setStartValue(Number);
      setTableText((int) *it, (*mpItemsCopy)[*it]);
    }
}

void CQFittingItemWidget::slotCrossValidations()
{
  if (mItemType == FIT_ITEM || mItemType == FIT_CONSTRAINT)
    {
      CQExperimentSelection *pDialog = new CQExperimentSelection(this);
      pDialog->load(mpBoxCrossValidations, * mppCrossValidationSet);

      if (pDialog->exec() == QDialog::Accepted)
        {
          if (!mSelection.size())
            slotNew();

          std::set< size_t >::const_iterator it = mSelection.begin();
          std::set< size_t >::const_iterator end = mSelection.end();

          for (; it != end; ++it)
            {
              (*mpItemsCopy)[*it]->getGroup("Affected Cross Validation Experiments")->clear();
              size_t i, imax = mpBoxCrossValidations->count();

              for (i = 0; i < imax && imax < (*mppCrossValidationSet)->getExperimentCount(); i++)
                static_cast<CFitItem *>((*mpItemsCopy)[*it])->addCrossValidation((*mppCrossValidationSet)->getExperiment(TO_UTF8(mpBoxCrossValidations->itemText(i)))->CCopasiParameter::getKey());

              setTableText(*it, (*mpItemsCopy)[*it]);
            }
        }

      loadSelection();
      delete pDialog;
    }
}

void CQFittingItemWidget::slotCrossValidationChanged()
{
  // This slot is triggered when an experiment is deleted or changed,
  // but before new experiments are created.
  if (mItemType == OPT_ITEM || mItemType == OPT_CONSTRAINT) return;

  // Remove all references to deleted experiments.
  std::vector< COptItem * >::iterator it = mpItemsCopy->begin();
  std::vector< COptItem * >::iterator end = mpItemsCopy->end();
  size_t i, imax;
  size_t Row;

  for (Row = 0; it != end; ++it, ++Row)
    {
      for (i = 0, imax = static_cast<CFitItem *>(*it)->getCrossValidationCount(); i < imax; ++i)
        if (!CRootContainer::getKeyFactory()->get(static_cast<CFitItem *>(*it)->getCrossValidation(i)))
          static_cast<CFitItem *>(*it)->removeCrossValidation(i);

      setTableText(Row, *it);
    }

  // Reload the current item.
  loadSelection();
  // Enable/disable the interface to affected cross validations.
  setCrossValidationSet(*mppCrossValidationSet);
  return;
}

void CQFittingItemWidget::setCrossValidationSet(const CCrossValidationSet *&pCrossValidationSet)
{
  mppCrossValidationSet = &pCrossValidationSet;
  bool Enabled = (*mppCrossValidationSet)->getExperimentCount() != 0;
  mpBtnCrossValidations->setEnabled(Enabled);
  mpCheckCrossValidationsAll->setEnabled(Enabled);
  mpBoxCrossValidations->setEnabled(Enabled && !mpCheckCrossValidationsAll->isChecked());
  mpLblCrossValidations->setEnabled(Enabled);
}

void CQFittingItemWidget::slotCheckAllCrossValidations(bool checked)
{
  if (mItemType == OPT_ITEM || mItemType == OPT_CONSTRAINT) return;

  if (!checked && mpBoxCrossValidations->count() == 0)
    slotCrossValidations();
  else if (checked)
    {
      std::set< size_t >::const_iterator it = mSelection.begin();
      std::set< size_t >::const_iterator end = mSelection.end();

      for (; it != end; ++it)
        {
          (*mpItemsCopy)[*it]->getGroup("Affected Cross Validation Experiments")->clear();
          setTableText((int) *it, (*mpItemsCopy)[*it]);
        }
    }

  loadSelection();
}

void CQFittingItemWidget::slotCheckAllExperiments(bool checked)
{
  if (mItemType == OPT_ITEM || mItemType == OPT_CONSTRAINT) return;

  if (!checked && mpBoxExperiments->count() == 0)
    slotExperiments();
  else if (checked)
    {
      std::set< size_t >::const_iterator it = mSelection.begin();
      std::set< size_t >::const_iterator end = mSelection.end();

      for (; it != end; ++it)
        {
          (*mpItemsCopy)[*it]->getGroup("Affected Experiments")->clear();
          setTableText((int) *it, (*mpItemsCopy)[*it]);
        }
    }

  loadSelection();
}
