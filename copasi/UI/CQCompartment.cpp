// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartment.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/08/07 14:12:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// #include "CQExpressionWidget.h"
// #include "CQExpressionMmlWidget.h"
// #include "CopasiDataModel/CCopasiDataModel.h"
// #include "model/CMetab.h"
// #include "model/CChemEqInterface.h"
// #include "function/CExpression.h"
// #include "report/CKeyFactory.h"

#include "CQCompartment.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "model/CModel.h"
#include "report/CCopasiRootContainer.h"

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

  mpMetaboliteTable->verticalHeader()->hide();
  mpMetaboliteTable->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpMetaboliteTable->horizontalHeader()->hide();
  mpMetaboliteTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
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

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  std::string name = "compartment";
  int i = 0;

  while (!(mpCompartment = pModel->createCompartment(name)))
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
  if (mpCompartment == NULL)
    return;

  CModel * pModel = static_cast< CModel * >(mpCompartment->getObjectAncestor("Model"));

  if (pModel == NULL)
    return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, pModel, "compartment",
                                FROM_UTF8(mpCompartment->getObjectName()),
                                mpCompartment->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:
      {
        unsigned C_INT32 Index =
          pModel->getCompartments().getIndex(mpCompartment->getObjectName());
        pModel->removeCompartment(mKey);

        unsigned C_INT32 Size =
          pModel->getCompartments().size();

        if (Size > 0)
          enter(pModel->getCompartments()[std::min(Index, Size - 1)]->getKey());
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

bool CQCompartment::enterProtected()
{
  mpCompartment = dynamic_cast< CCompartment * >(mpObject);

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
  if (mpCompartment == NULL)
    return;

  CModel * pModel = static_cast< CModel * >(mpCompartment->getObjectAncestor("Model"));

  if (pModel == NULL)
    return;

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
      if (mpDataModel)
        mpDataModel->changed();

      protectedNotify(ListViews::COMPARTMENT, ListViews::CHANGE, mKey);
    }

  mChanged = false;
}

void CQCompartment::destroy()
{}

void CQCompartment::slotSwitchToSpecies(int row, int /* column */)
{
  if (mpCompartment == NULL) return;

  std::string s1;
  s1 = TO_UTF8(mpMetaboliteTable->item(row, 0)->text());

  CCopasiVector< CMetab >::const_iterator it = mpCompartment->getMetabolites().begin();
  CCopasiVector< CMetab >::const_iterator end = mpCompartment->getMetabolites().end();

  for (; it != end; ++it)
    {
      if (s1 == (*it)->getObjectName())
        {
          mpListView->switchToOtherWidget(0, (*it)->getKey());
        }
    }
}

void CQCompartment::loadMetaboliteTable()
{
  if (mpCompartment == NULL) return;

  const CCopasiVector< CMetab > & Species = mpCompartment->getMetabolites();
  mpMetaboliteTable->setRowCount(Species.size());

  CCopasiVector< CMetab >::const_iterator it = Species.begin();
  CCopasiVector< CMetab >::const_iterator end = Species.end();

  for (int row = 0; it != end; ++it, ++row)
    {
      mpMetaboliteTable->setItem(row, 0, new QTableWidgetItem(FROM_UTF8((*it)->getObjectName())));
    }

  return;
}
