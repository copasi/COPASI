// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

#include "CQCompartment.h"

#include "CQExpressionWidget.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CCompartment.h"
#include "model/CChemEqInterface.h"
#include "function/CExpression.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiRootContainer.h"

/*
 *  Constructs a CQCompartment which is a child of 'parent', with the
 *  name 'name'.'
 */
CQCompartment::CQCompartment(QWidget* parent, const char* name):
  CopasiWidget(parent, name),
  mItemToType(),
  mpCompartment(NULL),
  mChanged(false),
  mExpressionValid(true),
  mInitialExpressionValid(true),
  mKeyToCopy("")
{
  setupUi(this);

  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);

  mpMetaboliteTable->horizontalHeader()->hide();

  mExpressionValid = false;
  mpExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);

  mInitialExpressionValid = false;
  mpInitialExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::InitialExpression);

#ifdef COPASI_EXTUNIT
  mpLblDim->show();
  mpComboBoxDim->show();
#else
  mpLblDim->hide();
  mpComboBoxDim->hide();
#endif
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQCompartment::~CQCompartment()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQCompartment::slotBtnNew()
{
  leave();

  std::string name = "compartment_1";
  int i = 1;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  while (!(mpCompartment = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createCompartment(name)))
    {
      i++;
      name = "compartment_";
      name += TO_UTF8(QString::number(i));
    }

  std::string key = mpCompartment->getKey();
//  enter(key);
  protectedNotify(ListViews::COMPARTMENT, ListViews::ADD, key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQCompartment::slotBtnCopy()
{
  mKeyToCopy = mKey;
}

void CQCompartment::slotBtnDelete()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL) return;

  if (mpCompartment == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "compartment",
                                FROM_UTF8(mpCompartment->getObjectName()),
                                mpCompartment->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        pDataModel->getModel()->removeCompartment(mKey);

        protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, mKey);
        protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, ""); //Refresh all as there may be dependencies.
        break;
      }

      default:
        break;
    }
}

/*!
    If the simulation type is changed then COPASI will automatically adjust its appearance,
    especially correlating to the Expression Widget and its buttons.
 */
void CQCompartment::slotTypeChanged(int type)
{
  QString Units;

  const CModel * pModel = NULL;

  if (mpCompartment != NULL)
    pModel = dynamic_cast<const CModel *>(mpCompartment->getObjectAncestor("Model"));

  switch ((CModelEntity::Status) mItemToType[type])
    {
      case CModelEntity::FIXED:
        mpLblExpression->hide();
        mpExpressionEMW->hide();

        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());
        break;

      case CModelEntity::ASSIGNMENT:

        if (pModel)
          Units = FROM_UTF8(pModel->getVolumeUnitsDisplayString());

        if (!Units.isEmpty())
          Units = " (" + Units + ")";

        mpLblExpression->setText("Expression" + Units);

        mpLblExpression->show();
        mpExpressionEMW->show();

        mpBoxUseInitialExpression->setEnabled(false);
        slotInitialTypeChanged(false);

        mpExpressionEMW->updateWidget();
        break;

      case CModelEntity::ODE:

        if (pModel)
          Units = FROM_UTF8(pModel->getVolumeRateUnitsDisplayString());

        if (!Units.isEmpty())
          Units = " (" + Units + ")";

        mpLblExpression->setText("Expression" + Units);

        mpLblExpression->show();
        mpExpressionEMW->show();

        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

        mpExpressionEMW->updateWidget();

        break;

      default:
        break;
    }
}

/*!
    This function is used in case of not FIXED type
 */
void CQCompartment::slotInitialTypeChanged(bool useInitialAssignment)
{
  if (useInitialAssignment)
    {
      mpLblInitialExpression->show();
      mpInitialExpressionEMW->show();

      mpEditInitialVolume->setEnabled(false);
      mpInitialExpressionEMW->updateWidget();
    }
  else
    {
      mpLblInitialExpression->hide();
      mpInitialExpressionEMW->hide();

      mpEditInitialVolume->setEnabled((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::ASSIGNMENT);
    }
}

/*!
 */

void CQCompartment::slotExpressionValid(bool valid)
{
  mExpressionValid = valid;
}

void CQCompartment::slotInitialExpressionValid(bool valid)
{
  mInitialExpressionValid = valid;
}

bool CQCompartment::enterProtected()
{
  if (mKeyToCopy != "")
    {
      mpCompartment = dynamic_cast<CCompartment*>(CCopasiRootContainer::getKeyFactory()->get(mKeyToCopy));
      mKeyToCopy = "";
    }
  else
    {
      mpCompartment = dynamic_cast< CCompartment * >(mpObject);
    }

  if (!mpCompartment)
    {
      mpListView->switchToOtherWidget(111, "");
      return false;
    }

  load();

  mpCompartment = dynamic_cast<CCompartment*>(mpObject);

  return true;
}

bool CQCompartment::leave()
{
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::FIXED)
    {
      // -- Expression --
      mpExpressionEMW->updateWidget();
    }

  if (mpBoxUseInitialExpression->isChecked())
    {
      // -- Initial Expression --
      mpInitialExpressionEMW->updateWidget();
    }

  save();

  return true;
}

bool CQCompartment::update(ListViews::ObjectType objectType,
                           ListViews::Action /* action */,
                           const std::string & /* key */)
{
  if (!isVisible() || mIgnoreUpdates) return true;

  switch (objectType)
    {
      case ListViews::STATE:
      case ListViews::MODEL:
      case ListViews::METABOLITE:
      case ListViews::COMPARTMENT:
        load();
        break;

      default:
        break;
    }

  return true;
}

void CQCompartment::load()
{
  if (mpCompartment == NULL) return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  const CModel * pModel = NULL;

  if (mpCompartment != NULL)
    pModel = dynamic_cast<const CModel *>(mpCompartment->getObjectAncestor("Model"));

  // Update the labels to reflect the model units
  QString ValueUnits;

  if (pModel)
    ValueUnits = FROM_UTF8(pModel->getVolumeUnitsDisplayString());

  if (!ValueUnits.isEmpty())
    ValueUnits = " (" + ValueUnits + ")";

  QString RateUnits;

  if (pModel)
    RateUnits = FROM_UTF8(pModel->getVolumeRateUnitsDisplayString());

  if (!RateUnits.isEmpty())
    RateUnits = " (" + RateUnits + ")";

  mpLblInitialValue->setText("Initial Volume" + ValueUnits);
  mpLblInitialExpression->setText("Initial Expression" + ValueUnits);
  mpLblVolume->setText("Volume" + ValueUnits);
  mpLblRate->setText("Rate" + RateUnits);

  //Dimensionality
  mpComboBoxDim->setCurrentIndex(mpCompartment->getDimensionality());
  //this assumes the indices of the entries in the combobox correspond 1to1 to the values of dimensionality

  // Simulation Type
  mpComboBoxType->setCurrentIndex(mpComboBoxType->findText(FROM_UTF8(CModelEntity::StatusName[mpCompartment->getStatus()])));

  // Initial Volume
  mpEditInitialVolume->setText(QString::number(mpCompartment->getInitialValue(), 'g', 10));

  // Transient Volume
  mpEditCurrentVolume->setText(QString::number(mpCompartment->getValue(), 'g', 10));

  // Concentration Rate
  mpEditRate->setText(QString::number(mpCompartment->getRate(), 'g', 10));

  // Expression
  mpExpressionEMW->mpExpressionWidget->setExpression(mpCompartment->getExpression());
  mpExpressionEMW->updateWidget();

  // Initial Expression
  mpInitialExpressionEMW->mpExpressionWidget->setExpression(mpCompartment->getInitialExpression());
  mpInitialExpressionEMW->updateWidget();

  // Type dependent display of values
  slotTypeChanged(mpComboBoxType->currentIndex());

  // Use Initial Expression
  if (mpCompartment->getStatus() == CModelEntity::ASSIGNMENT ||
      mpCompartment->getInitialExpression() == "")
    {
      mpBoxUseInitialExpression->setChecked(false);
    }
  else
    {
      mpBoxUseInitialExpression->setChecked(true);
    }

  loadMetaboliteTable();

  mChanged = false;
  return;
}

void CQCompartment::save()
{

  if (mpCompartment == NULL) return;

#ifdef COPASI_EXTUNIT

  //Dimensionality
  if ((C_INT32)mpCompartment->getDimensionality() != mpComboBoxDim->currentIndex()) //this makes assumptions about the order of entries in the combo box!
    {
      mpCompartment->setDimensionality(mpComboBoxDim->currentIndex());
      mChanged = true;
    }

#endif

  // Type
  if (mpCompartment->getStatus() != (CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()])
    {
      mpCompartment->setStatus((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()]);
      mChanged = true;
    }

  // Initial Volume
  if (QString::number(mpCompartment->getInitialValue(), 'g', 10) != mpEditInitialVolume->text())
    {
      mpCompartment->setInitialValue(mpEditInitialVolume->text().toDouble());
      mChanged = true;
    }

  // Expression
  if (mpCompartment->getExpression() != mpExpressionEMW->mpExpressionWidget->getExpression())
    {
      mpCompartment->setExpression(mpExpressionEMW->mpExpressionWidget->getExpression());
      mChanged = true;
    }

  // Initial Expression
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentIndex()] != CModelEntity::ASSIGNMENT)
    {
      if (mpBoxUseInitialExpression->isChecked() &&
          mpCompartment->getInitialExpression() != mpInitialExpressionEMW->mpExpressionWidget->getExpression())
        {
          mpCompartment->setInitialExpression(mpInitialExpressionEMW->mpExpressionWidget->getExpression());
          mChanged = true;
        }
      else if (!mpBoxUseInitialExpression->isChecked() &&
               mpCompartment->getInitialExpression() != "")
        {
          mpCompartment->setInitialExpression("");
          mChanged = true;
        }
    }

  if (mChanged)
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      (*CCopasiRootContainer::getDatamodelList())[0]->changed();
      protectedNotify(ListViews::COMPARTMENT, ListViews::CHANGE, mKey);
    }

  mChanged = false;
}

void CQCompartment::destroy()
{}

void CQCompartment::slotMetaboliteTableCurrentChanged(int row, int col)
{
  if (mpCompartment == NULL) return;

  QTableWidgetItem * pItem = mpMetaboliteTable->item(row, col);

  std::string s1, s2;
  s1 = TO_UTF8(pItem->text());

  std::multimap< const std::string, CCopasiObject * >::const_iterator it =
    mpCompartment->getMetabolites().getObjects().begin();
  std::multimap< const std::string, CCopasiObject * >::const_iterator end =
    mpCompartment->getMetabolites().getObjects().end();

  for (; it != end; ++it)
    if (dynamic_cast< CMetab * >(it->second) != NULL)
      {
        s2 = it->second->getObjectName();

        if (s1 == s2)
          mpListView->switchToOtherWidget(C_INVALID_INDEX, it->second->getKey());
      }
}

void CQCompartment::loadMetaboliteTable()
{
  if (mpCompartment == NULL) return;

  mpMetaboliteTable->setRowCount(mpCompartment->getMetabolites().size());

  std::multimap< const std::string, CCopasiObject * >::const_iterator it =
    mpCompartment->getMetabolites().getObjects().begin();
  std::multimap< const std::string, CCopasiObject * >::const_iterator end =
    mpCompartment->getMetabolites().getObjects().end();

  for (int i = 0; it != end; ++it)
    {
      if (dynamic_cast< CMetab * >(it->second) != NULL)
        {
          mpMetaboliteTable->setItem(i++, 0, new QTableWidgetItem(FROM_UTF8(it->second->getObjectName())));
        }
    }

  mpMetaboliteTable->resizeRowsToContents();

  return;
}
