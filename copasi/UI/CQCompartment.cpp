// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartment.cpp,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/07/13 15:36:17 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQExpressionWidget.h"
#include "CQExpressionMmlWidget.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CCompartment.h"
#include "model/CChemEqInterface.h"
#include "function/CExpression.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiRootContainer.h"

#include "UI/CQMessageBox.h"
#include "UI/qtUtilities.h"

#include "CQCompartment.h"

/*
 *  Constructs a CQCompartment which is a child of 'parent', with the
 *  name 'name'.'
 */
CQCompartment::CQCompartment(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  connect(mpExpressionEMW->mpExpressionWidget, SIGNAL(valid(bool)), this, SLOT(slotExpressionValid(bool)));
  connect(mpInitialExpressionEMW->mpExpressionWidget, SIGNAL(valid(bool)), this, SLOT(slotInitialExpressionValid(bool)));

  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);

  mpMetaboliteTable->header()->hide();

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

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQCompartment::languageChange()
{
  retranslateUi(this);
}

/*!
    After clicking the Commit button, COPASI will internally, automatically save any inputs and load them.
 */
void CQCompartment::slotBtnCommit()
{
  save();
  load();
}

void CQCompartment::slotBtnRevert()
{
  load();
}

void CQCompartment::slotBtnNew()
{
  save();

  std::string name = "compartment";
  int i = 0;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  while (!(mpCompartment = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createCompartment(name)))
    {
      i++;
      name = "compartment_";
      name += TO_UTF8(QString::number(i));
    }

  enter(mpCompartment->getKey());
  protectedNotify(ListViews::METABOLITE, ListViews::ADD);
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
    CQMessageBox::confirmDelete(this, pModel, "compartment",
                                FROM_UTF8(mpCompartment->getObjectName()),
                                mpCompartment->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        unsigned C_INT32 Index =
          pDataModel->getModel()->getCompartments().getIndex(mpCompartment->getObjectName());
        pDataModel->getModel()->removeCompartment(mKey);

        unsigned C_INT32 Size =
          pDataModel->getModel()->getCompartments().size();

        if (Size > 0)
          enter(pDataModel->getModel()->getCompartments()[std::min(Index, Size - 1)]->getKey());
        else
          enter("");

        protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, mKey);
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
      gridLayout->addWidget(mpLblInitialExpression, 5, 0);

      mpLblInitialExpression->show();
      mpInitialExpressionEMW->show();

      mpEditInitialVolume->setEnabled(false);
      mpInitialExpressionEMW->updateWidget();
    }
  else
    {
      gridLayout->remove(mpLblInitialExpression);

      mpLblInitialExpression->hide();
      mpInitialExpressionEMW->hide();

      mpEditInitialVolume->setEnabled((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] != CModelEntity::ASSIGNMENT);
    }
}

/*!
 */
void CQCompartment::slotNameLostFocus()
{
  if (mpEditName->text() != FROM_UTF8(mpCompartment->getObjectName()))
    {}}

void CQCompartment::slotExpressionValid(bool valid)
{
  mExpressionValid = valid;
  mpBtnCommit->setEnabled(mExpressionValid && mInitialExpressionValid);
}

void CQCompartment::slotInitialExpressionValid(bool valid)
{
  mInitialExpressionValid = valid;
  mpBtnCommit->setEnabled(mExpressionValid && mInitialExpressionValid);
}

bool CQCompartment::enter(const std::string & key)
{
  mKey = key;
  mpCompartment = dynamic_cast< CCompartment * >(CCopasiRootContainer::getKeyFactory()->get(key));

  if (!mpCompartment)
    {
      mpListView->switchToOtherWidget(111, "");
      return false;
    }

  load();
  return true;
}

bool CQCompartment::leave()
{
  if (mpBtnCommit->isEnabled())
    {
      if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] != CModelEntity::FIXED)
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
    }

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
  //CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];

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

  // Name
  mpEditName->setText(FROM_UTF8(mpCompartment->getObjectName()));

  //Dimensionality
  mpComboBoxDim->setCurrentIndex(mpCompartment->getDimensionality());
  //this assumes the indices of the entries in the combobox correspond 1to1 to the values of dimensionality

  // Simulation Type
  mpComboBoxType->setCurrentText(FROM_UTF8(CModelEntity::StatusName[mpCompartment->getStatus()]));

  // Initial Volume
  mpEditInitialVolume->setText(QString::number(mpCompartment->getInitialValue(), 'g', 10));

  // Transient Volume
  mpEditCurrentVolume->setText(QString::number(mpCompartment->getValue()));

  // Concentration Rate
  mpEditRate->setText(QString::number(mpCompartment->getRate()));

  // Expression
  mpExpressionEMW->mpExpressionWidget->setExpression(mpCompartment->getExpression());
  mpExpressionEMW->updateWidget();

  // Initial Expression
  mpInitialExpressionEMW->mpExpressionWidget->setExpression(mpCompartment->getInitialExpression());
  mpInitialExpressionEMW->updateWidget();

  // Type dependent display of values
  slotTypeChanged(mpComboBoxType->currentItem());

  // Use Initial Expression
  if (mpCompartment->getStatus() == CModelEntity::ASSIGNMENT ||
      mpCompartment->getInitialExpression() == "")
    {
      mpBoxUseInitialExpression->setChecked(false);
      // slotInitialTypeChanged(false);
    }
  else
    {
      mpBoxUseInitialExpression->setChecked(true);
      // slotInitialTypeChanged(true);
    }

  loadMetaboliteTable();

  mChanged = false;
  return;
}

void CQCompartment::save()
{
  if (mpCompartment == NULL) return;

  // Name
  if (mpCompartment->getObjectName() != TO_UTF8(mpEditName->text()))
    {
      if (!mpCompartment->setObjectName(TO_UTF8(mpEditName->text())))
        {
          QString msg;
          msg = "Unable to rename compartment '" + FROM_UTF8(mpCompartment->getObjectName()) + "'\n"
                + "to '" + mpEditName->text() + "' since a compartment with that name already exists.\n";

          CQMessageBox::information(this,
                                    "Unable to rename Compartment",
                                    msg,
                                    QMessageBox::Ok, QMessageBox::Ok);

          mpEditName->setText(FROM_UTF8(mpCompartment->getObjectName()));
        }
      else
        {
          protectedNotify(ListViews::COMPARTMENT, ListViews::RENAME, mKey);
          mChanged = true;
        }
    }

#ifdef COPASI_EXTUNIT

  //Dimensionality
  if ((C_INT32)mpCompartment->getDimensionality() != mpComboBoxDim->currentIndex()) //this makes assumptions about the order of entries in the combo box!
    {
      mpCompartment->setDimensionality(mpComboBoxDim->currentIndex());
      mChanged = true;
    }

#endif

  // Type
  if (mpCompartment->getStatus() != (CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()])
    {
      mpCompartment->setStatus((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()]);
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
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] != CModelEntity::ASSIGNMENT)
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

void CQCompartment::slotMetaboliteTableCurrentChanged(Q3ListViewItem * pItem)
{
  if (mpCompartment == NULL) return;

  std::string s1, s2;
  s1 = TO_UTF8(pItem->text(0));

  std::multimap< const std::string, CCopasiObject * >::const_iterator it =
    mpCompartment->getMetabolites().getObjects().begin();
  std::multimap< const std::string, CCopasiObject * >::const_iterator end =
    mpCompartment->getMetabolites().getObjects().end();

  for (; it != end; ++it)
    if (dynamic_cast< CMetab * >(it->second) != NULL)
      {
        s2 = it->second->getObjectName();

        if (s1 == s2)
          mpListView->switchToOtherWidget(0, it->second->getKey());
      }
}

void CQCompartment::loadMetaboliteTable()
{
  if (mpCompartment == NULL) return;

  mpMetaboliteTable->clear();
  mpMetaboliteTable->setColumnWidth(0, 10);

  std::multimap< const std::string, CCopasiObject * >::const_iterator it =
    mpCompartment->getMetabolites().getObjects().begin();
  std::multimap< const std::string, CCopasiObject * >::const_iterator end =
    mpCompartment->getMetabolites().getObjects().end();

  for (; it != end; ++it)
    if (dynamic_cast< CMetab * >(it->second) != NULL)
      new Q3ListViewItem(mpMetaboliteTable, FROM_UTF8(it->second->getObjectName()));

  return;
}
