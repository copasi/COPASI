// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQSpeciesDetail.h"
#include "CQMessageBox.h"
#include "CQNameSelectionDialog.h"  // for Copy button compartment options
#include "qtUtilities.h"
#include "copasiui3window.h"
#include "CQDependencyWidget.h"
#include "copasi/UI/CQScrolledDependenciesWidget.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CChemEqInterface.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModelExpansion.h"    //for Copy button and options
#include "copasi/CopasiDataModel/CDataModel.h"

//UNDO framework classes
#include "copasi/undo/CUndoStack.h"
#include "copasi/undo/CUndoData.h"

/*
 *  Constructs a CQSpeciesDetail which is a child of 'parent', with the
 *  name 'name'.'
 */
CQSpeciesDetail::CQSpeciesDetail(QWidget *parent, const char *name) :
  CopasiWidget(parent, name),
  mChanged(false),
  mpMetab(NULL),
  mpCurrentCompartment(NULL),
  mInitialNumber(0.0),
  mInitialConcentration(0.0),
  mpDependencies(NULL)
{
  setupUi(this);
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::REACTIONS]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::FIXED]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ASSIGNMENT]));
  mpComboBoxType->insertItem(mpComboBoxType->count(), FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ODE]));

  mpExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);
  mpInitialExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::InitialExpression);
  mpNoiseExpressionWidget->mpExpressionWidget->setExpressionType(CQExpressionWidget::TransientExpression);
  mpReactionTable->verticalHeader()->hide();
  mpReactionTable->horizontalHeader()->hide();
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  mpReactionTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  mpReactionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
  mpReactionTable->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpReactionTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif

  // temporarily hide the reaction label / table
  mpLblReactions->setVisible(false);
  mpReactionTable->setVisible(false);
  // display dependency widget instead

  mpDependencies = new CQScrolledDependenciesWidget(this);
  mpDependencies->setVisibleDependencies(REACTION | EVENT | SPECIES | PARAMETERS | COMPARTMENT);
  mpDependencies->setLabelWidth(mpLblValue->width() - 6);
  gridLayout->addWidget(mpDependencies, gridLayout->rowCount(), 0, 1, -1);
}

CQSpeciesDetail::~CQSpeciesDetail()
{
}

bool CQSpeciesDetail::leaveProtected()
{
  if (CModelEntity::StatusName.toEnum(TO_UTF8(mpComboBoxType->currentText())) != CModelEntity::Status::FIXED &&
      CModelEntity::StatusName.toEnum(TO_UTF8(mpComboBoxType->currentText())) != CModelEntity::Status::REACTIONS)
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

bool CQSpeciesDetail::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  mpMetab = dynamic_cast< CMetab * >(mpObject);

  switch (objectType)
    {
      case ListViews::ObjectType::MODEL:

        // For a new model we need to remove references to no longer existing metabolites
        if (action != ListViews::CHANGE)
          {
            mObjectCN.clear();
            mpObject = NULL;
            mpMetab = NULL;

            // we also have to clear the widgets that might store old data
            mpExpressionEMW->reset();
            mpInitialExpressionEMW->reset();
          }

        break;

      case ListViews::ObjectType::METABOLITE:

        // If the currently displayed metabolite is deleted we need to remove its references.
        if (action == ListViews::DELETE && mObjectCN == cn)
          {
            mObjectCN.clear();
            mpObject = NULL;
            mpMetab = NULL;

            // we also have to clear the widgets that might store old data
            mpExpressionEMW->reset();
            mpInitialExpressionEMW->reset();
          }

        break;

      case ListViews::ObjectType::STATE:
      case ListViews::ObjectType::COMPARTMENT:
        break;

      default:
        return true;
        break;
    }

  mpMetab = dynamic_cast< CMetab * >(mpObject);

  if (isVisible() && !mIgnoreUpdates)
    load();

  return true;
}

void CQSpeciesDetail::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);

  if (mpMetab == NULL) return;

  const CModel *pModel = mpMetab->getModel();
  QString ParticleNumberUnits = "[" + FROM_UTF8(CUnit::prettyPrint(mpMetab->getValueReference()->getUnits())) + "]";
  QString ParticleNumberRateUnits = "[" + FROM_UTF8(CUnit::prettyPrint(mpMetab->getRateReference()->getUnits())) + "]";
  // These depend on the current selected compartment's unit (which depends on it's dimensionality)
  std::string concUnitStdStr = "(" + pModel->getQuantityUnit() + ")/(" + mpCurrentCompartment->getUnits() + ")";
  QString ConcentrationUnits = "[" + FROM_UTF8(CUnit::prettyPrint(concUnitStdStr)) + "]";
  QString ConcentrationRateUnits = "[" + FROM_UTF8(CUnit::prettyPrint("(" + concUnitStdStr + ")/(" + pModel->getTimeUnit() + ")")) + "]";

  switch (static_cast <CCore::Framework >(mFramework))
    {
      case CCore::Framework::Concentration:
        mpLblInitialValue->setText("Initial Concentration\n" + ConcentrationUnits);
        mpLblInitialExpression->setText("Initial Expression\n" + ConcentrationUnits);

        if (mpMetab != NULL &&
            CModelEntity::StatusName.toEnum(TO_UTF8(mpComboBoxType->currentText())) == CModelEntity::Status::ASSIGNMENT)
          mpLblExpression->setText("Expression " + ConcentrationUnits);
        else
          mpLblExpression->setText("Expression " + ConcentrationRateUnits);

        mpLblValue->setText("Concentration " + ConcentrationUnits);
        mpLblRate->setText("Rate " + ConcentrationRateUnits);
        mpEditInitialValue->setText(convertToQString(mInitialConcentration));
        mpEditInitialValue->setReadOnly(!mpMetab->isInitialValueChangeAllowed((CCore::Framework) mFramework));
        mpEditCurrentValue->setText(convertToQString(mpMetab->getConcentration()));
        mpEditRate->setText(convertToQString(mpMetab->getConcentrationRate()));
        break;

      case CCore::Framework::ParticleNumbers:
        mpLblInitialValue->setText("Initial Number " + ParticleNumberUnits);
        mpLblInitialExpression->setText("Initial Expression " + ConcentrationUnits);

        if (mpMetab->getStatus() == CModelEntity::Status::ASSIGNMENT)
          mpLblExpression->setText("Expression" + ConcentrationUnits);
        else
          mpLblExpression->setText("Expression" + ConcentrationRateUnits);

        mpLblValue->setText("Number " + ParticleNumberUnits);
        mpLblRate->setText("Number Rate " + ParticleNumberRateUnits);
        mpEditInitialValue->setText(convertToQString(mInitialNumber));
        mpEditInitialValue->setReadOnly(!mpMetab->isInitialValueChangeAllowed((CCore::Framework) mFramework));
        mpEditCurrentValue->setText(convertToQString(mpMetab->getValue()));
        mpEditRate->setText(convertToQString(mpMetab->getRate()));
        break;

      case CCore::Framework::__SIZE:
        break;
    }
}

bool CQSpeciesDetail::enterProtected()
{
  mpMetab = dynamic_cast< CMetab * >(mpObject);

  if (!mpMetab)
    {
      mpListView->switchToOtherWidget(ListViews::WidgetType::Species, std::string());
      return false;
    }

  load();
  return true;
}

void CQSpeciesDetail::load()
{
  if (mpMetab == NULL) return;

  const CModel *pModel = NULL;

  if (mpMetab)
    pModel = mpMetab->getModel();

  std::string TimeUnit = (pModel != NULL) ? CUnit::prettyPrint(pModel->getTimeUnit()) : "?";
  QString TimeUnits = " [" + FROM_UTF8(TimeUnit) + "]";
  // Update the labels to reflect the model units
  mpLblTransitionTime->setText("Transition Time " + TimeUnits);
  // Compartment
  const CDataVectorNS< CCompartment > &Compartments = pModel->getCompartments();
  const CCompartment *pCompartment;
  mpComboBoxCompartment->clear();
  mpComboBoxCompartment->setDuplicatesEnabled(false);
  size_t m;

  for (m = 0; m < Compartments.size(); m++)
    {
      pCompartment = &Compartments[m];
      mpComboBoxCompartment->insertItem(mpComboBoxCompartment->count(), FROM_UTF8(pCompartment->getObjectName()));
    }

  mpCurrentCompartment = mpMetab->getCompartment();
  mpComboBoxCompartment->setCurrentIndex(mpComboBoxCompartment->findText(FROM_UTF8(mpCurrentCompartment->getObjectName())));
  // Simulation Type
  mpComboBoxType->setCurrentIndex(mpComboBoxType->findText(FROM_UTF8(CModelEntity::StatusName[mpMetab->getStatus()])));
  // Initial Concentration handled in slotTypeChanged
  mInitialConcentration = mpMetab->getInitialConcentration();
  // Initial Number handled in slotTypeChanged
  mInitialNumber = mpMetab->getInitialValue();
  // Transition Time
  mpEditTransitionTime->setText(convertToQString(mpMetab->getTransitionTime()));
  // Expression
  mpExpressionEMW->mpExpressionWidget->setExpression(mpMetab->getExpression());
  mpExpressionEMW->updateWidget();
  // Initial Expression
  mpInitialExpressionEMW->mpExpressionWidget->setExpression(mpMetab->getInitialExpression());
  mpInitialExpressionEMW->updateWidget();
  // Noise Expression
  mpNoiseExpressionWidget->mpExpressionWidget->setExpression(mpMetab->getNoiseExpression());
  mpNoiseExpressionWidget->updateWidget();
  mpBoxAddNoise->setChecked(mpMetab->hasNoise());
  // Type dependent display of values
  slotTypeChanged(mpComboBoxType->currentText());

  // Use Initial Expression
  if (mpMetab->getStatus() == CModelEntity::Status::ASSIGNMENT ||
      mpMetab->getInitialExpression() == "")
    {
      mpBoxUseInitialExpression->setChecked(false);
      // slotInitialTypeChanged(false);
    }
  else
    {
      mpBoxUseInitialExpression->setChecked(true);
      // slotInitialTypeChanged(true);
    }

  loadReactionTable();
  mpDependencies->loadFrom(mpObject);
  // Update the units and values accordingly
  setFramework(mFramework);
  mChanged = false;
  return;
}

void CQSpeciesDetail::save()
{
  if (mpMetab == NULL) return;

  CModel *pModel = const_cast< CModel * >(mpMetab->getModel());

  if (pModel == NULL) return;

  CData OldData(mpMetab->toData());
  mChanged = false;

  // Compartment
  if (mpCurrentCompartment != mpMetab->getCompartment())
    {
      if (mpCurrentCompartment->getMetabolites().getIndex(mpMetab->getObjectName()) == C_INVALID_INDEX)
        {
          const_cast< CCompartment * >(mpCurrentCompartment)->getMetabolites().add(mpMetab, true);
          mChanged = true;
        }
      else
        {
          QString msg;
          msg = "Unable to move species '" + FROM_UTF8(mpObject->getObjectName()) + "'\n"
                + "from '" + FROM_UTF8(mpMetab->getCompartment()->getObjectName())
                + "to '" + FROM_UTF8(mpCurrentCompartment->getObjectName()) + "' since a species with that name already exists.\n";

          CQMessageBox::information(this,
                                    "Unable to rename " + FROM_UTF8(ListViews::ObjectTypeName[mObjectType]),
                                    msg,
                                    QMessageBox::Ok, QMessageBox::Ok);
        }
    }

  // Type
  if (mpMetab->getStatus() != CModelEntity::StatusName.toEnum(TO_UTF8(mpComboBoxType->currentText())))
    {
      mpMetab->setStatus(CModelEntity::StatusName.toEnum(TO_UTF8(mpComboBoxType->currentText())));
      mChanged = true;
    }

  if (mpMetab->getInitialConcentration() != mInitialConcentration &&
      mpMetab->getStatus() != CModelEntity::Status::ASSIGNMENT)
    {
      mpMetab->setInitialConcentration(mInitialConcentration);
      mChanged = true;
    }

  if (mpMetab->getInitialValue() != mInitialNumber &&
      mpMetab->getStatus() != CModelEntity::Status::ASSIGNMENT)
    {
      mpMetab->setInitialValue(mInitialNumber);
      mChanged = true;
    }

  // Expression
  if (mpMetab->getExpression() != mpExpressionEMW->mpExpressionWidget->getExpression())
    {
      mpMetab->setExpression(mpExpressionEMW->mpExpressionWidget->getExpression());
      mChanged = true;
    }

  // Initial Expression
  if (CModelEntity::StatusName.toEnum(TO_UTF8(mpComboBoxType->currentText())) != CModelEntity::Status::ASSIGNMENT)
    {
      if (mpBoxUseInitialExpression->isChecked() &&
          mpMetab->getInitialExpression() != (mpInitialExpressionEMW->mpExpressionWidget->getExpression()))
        {
          mpMetab->setInitialExpression(mpInitialExpressionEMW->mpExpressionWidget->getExpression());
          mChanged = true;
        }
      else if (!mpBoxUseInitialExpression->isChecked() &&
               mpMetab->getInitialExpression() != "")
        {
          mpMetab->setInitialExpression("");
          mChanged = true;
        }
    }

  // Add Noise
  if (mpMetab->hasNoise() != mpBoxAddNoise->isChecked())
    {
      mpMetab->setHasNoise(mpBoxAddNoise->isChecked() && mpMetab->getStatus() == CModelEntity::Status::ODE);
      mChanged = true;
    }

  // Noise Expression
  if (mpMetab->getNoiseExpression() != mpNoiseExpressionWidget->mpExpressionWidget->getExpression())
    {
      mpMetab->setNoiseExpression(mpNoiseExpressionWidget->mpExpressionWidget->getExpression());
      mChanged = true;
    }

  if (mChanged)
    {
      CUndoData UndoData;
      mpMetab->createUndoData(UndoData, CUndoData::Type::CHANGE, OldData, static_cast< CCore::Framework >(mFramework));
      ListViews::addUndoMetaData(this, UndoData);

      slotNotifyChanges(mpDataModel->recordData(UndoData));
      load();
    }
}

void CQSpeciesDetail::loadReactionTable()
{
  if (mpMetab == NULL) return;

  CModel *pModel = const_cast< CModel * >(mpMetab->getModel());

  if (pModel == NULL) return;

  CDataObject::DataObjectSet dependentReactions;
  CDataObject::DataObjectSet dependentMetabolites;
  CDataObject::DataObjectSet dependentCompartments;
  CDataObject::DataObjectSet dependentModelValues;
  CDataObject::DataObjectSet dependentEvents;
  CDataObject::DataObjectSet dependentEventAssignments;

  pModel->appendAllDependents(*mpMetab, dependentReactions, dependentMetabolites, dependentCompartments,  dependentModelValues,  dependentEvents,  dependentEventAssignments);

  mpReactionTable->setRowCount((int) dependentReactions.size());
  mpReactionTable->setSortingEnabled(false);
  std::set< const CDataObject * >::const_iterator it = dependentReactions.begin();
  std::set< const CDataObject * >::const_iterator end = dependentReactions.end();
  int i = 0;
  const CReaction *pReaction;

  for (; it != end; ++it, ++i)
    {
      pReaction = static_cast< const CReaction * >(*it);
      mpReactionTable->setItem(i, 0, new QTableWidgetItem(FROM_UTF8(pReaction->getObjectName()) + ":"));
      mpReactionTable->setItem(i, 1, new QTableWidgetItem(FROM_UTF8(CChemEqInterface::getChemEqString(*pReaction, false))));
    }

  if (i == 0)
    mpReactionTable->setItem(i, 0, new QTableWidgetItem("none"));

  mpReactionTable->setSortingEnabled(true);
  // Provide count of reactions, in label.
  mpLblReactions->setText("Involved in \n" + QString::number(mpReactionTable->rowCount()) + " Reactions");
  return;
}

void CQSpeciesDetail::slotBtnDelete()
{
  deleteSpecies();
}

void CQSpeciesDetail::copy()
{
  if (mpMetab == NULL) return;

  CModel *pModel = NULL;

  if (mpMetab) pModel = mpDataModel->getModel();

  if (pModel == NULL) return; // for getting compartments and initializing cModelExpObj

  // Create and customize compartment choices dialog
  CQNameSelectionDialog *pDialog = new CQNameSelectionDialog(this);
  pDialog->setWindowTitle("Choose a compartment");
  pDialog->mpLblName->setText("compartment");
  pDialog->mpSelectionBox->clear();
  pDialog->mpSelectionBox->setDuplicatesEnabled(false);
  pDialog->mpSelectionBox->setEditable(false); // at least for now, unless we want to add new compartment creation here.
  // Use CModelExpansion for duplication
  CModelExpansion cModelExpObj = CModelExpansion(pModel);
  CModelExpansion::SetOfModelElements sourceObjects;
  CModelExpansion::ElementsMap origToCopyMapping;
  // for comboBox compartment list and setting compartment
  CDataVectorNS< CCompartment > &Compartments = pModel->getCompartments();
  CDataVectorN< CCompartment >::const_iterator it = Compartments.begin();
  CDataVectorN< CCompartment >::const_iterator end = Compartments.end();
  QStringList SelectionList;

  // Collect and load list of compartment names in comboBox
  for (; it != end; ++it)
    {
      SelectionList.append(FROM_UTF8(it->getObjectName()));
    }

  pDialog->setSelectionList(SelectionList);
  //Set the current compartment as the default
  mpCurrentCompartment = mpMetab->getCompartment();
  // to use here, and for testing if compartment changed after executing the dialog
  int origCompartmentIndex = pDialog->mpSelectionBox->findText(FROM_UTF8(mpCurrentCompartment->getObjectName()));
  pDialog->mpSelectionBox->setCurrentIndex(origCompartmentIndex);
  it = Compartments.begin(); // Reuse Compartments iterator to set compartment choice

  if (pDialog->exec() != QDialog::Rejected)
    {
      // Put species in different compartment (without name modification) by making
      // duplicateMetab think the other compartment was duplicated from the original
      if (origCompartmentIndex != pDialog->mpSelectionBox->currentIndex())
        {
          sourceObjects.addCompartment(mpMetab->getCompartment());
          origToCopyMapping.add(mpMetab->getCompartment(), (it + pDialog->mpSelectionBox->currentIndex()).constCast());
        }

      sourceObjects.addMetab(mpMetab);

      CUndoData UndoData;
      cModelExpObj.duplicateMetab(mpMetab, "_copy", sourceObjects, origToCopyMapping, UndoData);
      const CDataObject * pObject = origToCopyMapping.getDuplicateFromObject(mpObject);

      ListViews::addUndoMetaData(this, UndoData);
      UndoData.addMetaDataProperty("Widget Object CN (after)", pObject->getCN());
      UndoData.addMetaDataProperty("Widget Object Name (after)", pObject->getObjectName() + "{" + CCommonName::compartmentNameFromCN(pObject->getCN()) + "}");

      slotNotifyChanges(mpDataModel->recordData(UndoData));

      if (pObject != NULL)
        {
          mpListView->switchToOtherWidget(ListViews::WidgetType::SpeciesDetail, pObject->getCN());
        }
    }

  pdelete(pDialog);
}

CMetab * CQSpeciesDetail::getCurrentMetab()
{
  return mpMetab;
}

void CQSpeciesDetail::slotBtnNew()
{
  createNewSpecies();
}

void CQSpeciesDetail::slotBtnCopy() {}

void CQSpeciesDetail::slotCompartmentChanged(int compartment)
{
  if (!mpMetab || !mpCurrentCompartment) return;

  const CModel *pModel = mpMetab->getModel();

  if (pModel == NULL)
    return;

  QString Compartment = mpComboBoxCompartment->itemText(compartment);
  const CCompartment *pNewCompartment =
    &pModel->getCompartments()[TO_UTF8(Compartment)];

  if (pNewCompartment == mpCurrentCompartment ||
      pNewCompartment == NULL) return;

  switch (static_cast< CCore::Framework >(mFramework))
    {
      case CCore::Framework::Concentration:
        mInitialNumber = CMetab::convertToNumber(mInitialConcentration, *pNewCompartment);
        break;

      case CCore::Framework::ParticleNumbers:
        mInitialConcentration = CMetab::convertToConcentration(mInitialNumber, *pNewCompartment);
        break;

      case CCore::Framework::__SIZE:
        break;
    }

  mpCurrentCompartment = pNewCompartment;

  // Update the units and values accordingly
  setFramework(mFramework);
}

void CQSpeciesDetail::slotInitialTypeChanged(bool useInitialExpression)
{
  if (useInitialExpression)
    {
      mpLblInitialExpression->show();
      mpInitialExpressionEMW->show();
      mpEditInitialValue->setEnabled(false);
      mpInitialExpressionEMW->updateWidget();
    }
  else
    {
      mpLblInitialExpression->hide();
      mpInitialExpressionEMW->hide();
      mpEditInitialValue->setEnabled(CModelEntity::StatusName.toEnum(TO_UTF8(mpComboBoxType->currentText())) != CModelEntity::Status::ASSIGNMENT);
    }
}

void CQSpeciesDetail::slotAddNoiseChanged(bool hasNoise)
{
  if (hasNoise)
    {
      if (mpMetab != NULL &&
          mpMetab->getNoiseExpression().empty())
        {
          mpNoiseExpressionWidget->mpExpressionWidget->setExpression(mpMetab->getDefaultNoiseExpression());
        }

      mpLblNoiseExpression->show();
      mpNoiseExpressionWidget->show();
      mpNoiseExpressionWidget->updateWidget();
    }
  else
    {
      mpLblNoiseExpression->hide();
      mpNoiseExpressionWidget->hide();
    }
}

void CQSpeciesDetail::slotInitialValueLostFocus()
{
  if (!mpMetab || !mpCurrentCompartment) return;

  const CModel *pModel = mpMetab->getModel();

  if (pModel == NULL)
    return;

  switch (static_cast< CCore::Framework >(mFramework))
    {
      case CCore::Framework::Concentration:
        if (QString::number(mInitialConcentration, 'g', 10) == mpEditInitialValue->text())
          return;

        mInitialConcentration = mpEditInitialValue->text().toDouble();
        mInitialNumber = CMetab::convertToNumber(mInitialConcentration, *mpCurrentCompartment);
        break;

      case CCore::Framework::ParticleNumbers:
        if (QString::number(mInitialNumber, 'g', 10) == mpEditInitialValue->text())
          return;

        mInitialNumber = mpEditInitialValue->text().toDouble();
        mInitialConcentration = CMetab::convertToConcentration(mInitialNumber, *mpCurrentCompartment);
        break;

      case CCore::Framework::__SIZE:
        break;
    }
}

void CQSpeciesDetail::slotSwitchToReaction(int row, int /* column */)
{
  if (mpMetab == NULL) return;

  const CModel *pModel = mpMetab->getModel();

  if (pModel == NULL) return;

  CDataObject::DataObjectSet dependentReactions;
  CDataObject::DataObjectSet dependentMetabolites;
  CDataObject::DataObjectSet dependentCompartments;
  CDataObject::DataObjectSet dependentModelValues;
  CDataObject::DataObjectSet dependentEvents;
  CDataObject::DataObjectSet dependentEventAssignments;

  pModel->appendAllDependents(*mpMetab, dependentReactions, dependentMetabolites, dependentCompartments,  dependentModelValues,  dependentEvents,  dependentEventAssignments);

  std::string s1, s2;
  s1 = TO_UTF8(mpReactionTable->item(row, 0)->text());
  s1 = s1.substr(0, s1.length() - 1);
  C_INT32 i = 0;
  std::set< const CDataObject * >::const_iterator it = dependentReactions.begin();
  std::set< const CDataObject * >::const_iterator end = dependentReactions.end();
  const CReaction *pReaction;

  for (; it != end; ++it, ++i)
    {
      pReaction = static_cast< const CReaction * >(*it);
      s2 = pReaction->getObjectName();

      if (s1 == s2)
        mpListView->switchToOtherWidget(ListViews::WidgetType::ReactionDetail, pReaction->getCN());
    }
}

void CQSpeciesDetail::slotTypeChanged(const QString & type)
{
  speciesTypeChanged(type);
}

//Undo methods
void CQSpeciesDetail::createNewSpecies()
{
  leaveProtected();

  CModel *pModel = mpDataModel->getModel();
  CCompartment * pComp  = NULL;

  if (pModel->getCompartments().size() == 0)
    {
      // We need to create a compartment
      pComp = pModel->createCompartment("compartment");
    }

  std::string name = "species";
  int i = 1;

  while (!(mpMetab = pModel->createMetabolite(name, "", 1.0, CModelEntity::Status::REACTIONS)))
    {
      i++;
      name = "species_";
      name += TO_UTF8(QString::number(i));
    }

  switch (mFramework)
    {
      case 0:
        mpMetab->setInitialConcentration(1.0);
        break;

      case 1:
        mpMetab->setInitialValue(100.0);
        break;
    }

  std::string cn = mpMetab->getCN();

  CUndoData UndoData(CUndoData::Type::INSERT, mpMetab);

  if (pComp != NULL)
    {
      UndoData.addPreProcessData(CUndoData(CUndoData::Type::INSERT, pComp));
    }

  ListViews::addUndoMetaData(this, UndoData);
  UndoData.addMetaDataProperty("Widget Object CN (after)", mpMetab->getCN());
  UndoData.addMetaDataProperty("Widget Object Name (after)", mpMetab->getObjectName() + "{" + CCommonName::compartmentNameFromCN(mpMetab->getCN()) + "}");

  slotNotifyChanges(mpDataModel->recordData(UndoData));

  mpListView->switchToOtherWidget(ListViews::WidgetType::SpeciesDetail, cn);
}

void CQSpeciesDetail::deleteSpecies()
{
  if (mpMetab == NULL) return;

  CModel *pModel = const_cast< CModel *>(mpMetab->getModel());

  if (pModel == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "species",
                                FROM_UTF8(mpMetab->getObjectName()),
                                mpMetab);

  if (choice == QMessageBox::Ok)
    {
      CUndoData UndoData;
      mpMetab->createUndoData(UndoData, CUndoData::Type::REMOVE);
      ListViews::addUndoMetaData(this, UndoData);

      slotNotifyChanges(mpDataModel->applyData(UndoData));
    }
}
void CQSpeciesDetail::speciesTypeChanged(const QString & type)
{
  switch (CModelEntity::StatusName.toEnum(TO_UTF8(type)))
    {
      case CModelEntity::Status::FIXED:
        mpLblExpression->hide();
        mpExpressionEMW->hide();
        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());
        mpBoxAddNoise->hide();
        mpBoxAddNoise->setChecked(false);
        slotAddNoiseChanged(false);
        break;

      case CModelEntity::Status::ASSIGNMENT:
        mpLblExpression->show();
        mpExpressionEMW->show();
        mpBoxUseInitialExpression->setEnabled(false);
        slotInitialTypeChanged(false);
        mpExpressionEMW->updateWidget();
        mpBoxAddNoise->hide();
        mpBoxAddNoise->setChecked(false);
        slotAddNoiseChanged(false);
        break;

      case CModelEntity::Status::ODE:
        mpLblExpression->show();
        mpExpressionEMW->show();
        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());
        mpExpressionEMW->updateWidget();

        mpBoxAddNoise->show();
        slotAddNoiseChanged(mpBoxAddNoise->isChecked());
        break;

      case CModelEntity::Status::REACTIONS:
        mpLblExpression->hide();
        mpExpressionEMW->hide();
        mpBoxUseInitialExpression->setEnabled(true);
        slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());
        mpBoxAddNoise->hide();
        mpBoxAddNoise->setChecked(false);
        slotAddNoiseChanged(false);
        break;

      default:
        break;
    }

  // This will update the unit display.
  setFramework(mFramework);
}

// virtual
bool CQSpeciesDetail::event(QEvent * pEvent)
{
  if (pEvent->type() == QEvent::LayoutRequest &&
      mpLblValue->width() - 6 != mpDependencies->getLabelWidth())
    {
      mpDependencies->setLabelWidth(mpLblValue->width() - 6);
    }

  return CopasiWidget::event(pEvent);
}
