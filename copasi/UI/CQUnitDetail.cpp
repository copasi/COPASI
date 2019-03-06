// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQUnitDetail.h"

#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "copasi/model/CModel.h"

#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/utilities/CUnitDefinitionDB.h"
#include "copasi/CopasiDataModel/CDataModel.h"

/*
 *  Constructs a CQUnitDetail which is a child of 'parent', with the
 *  name 'name'.'
 */
CQUnitDetail::CQUnitDetail(QWidget* parent, const char* name)
  : CopasiWidget(parent, name),
    mpUnitDefinition(NULL)
{
  setupUi(this);

  init();

//  CopasiUI3Window *  pWindow = dynamic_cast<CopasiUI3Window * >(parent->parent());
//  setUndoStack(pWindow->getUndoStack());
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQUnitDetail::~CQUnitDetail()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/// Slot to create a new unit; activated whenever the New button is clicked
void CQUnitDetail::slotBtnNew()
{
  std::string name = "unit_1";
  int i = 1;
  CUnitDefinition* pUnitDef;
  CUnitDefinitionDB * unitList
    = CRootContainer::getUnitList();

  while (unitList->getIndex(name) != C_INVALID_INDEX)
    {
      i++;
      name = "unit_";
      name += TO_UTF8(QString::number(i));
    }

  unitList->add(pUnitDef = new CUnitDefinition(name, unitList), true);

  CCommonName CN = pUnitDef->getCN();
  protectedNotify(ListViews::ObjectType::UNIT, ListViews::ADD, CN);
// enter(key);
  mpListView->switchToOtherWidget(ListViews::WidgetType::UnitDetail, CN);
}

void CQUnitDetail::slotBtnCopy()
{
  CUnitDefinitionDB * unitList = CRootContainer::getUnitList();
  std::string base_name, name;
  base_name = mpUnitDefinition->getObjectName() + "_copy";
  name = base_name;
  int i = 0;

  while (unitList->getIndex(name) != C_INVALID_INDEX)
    {
      i++;
      name = base_name + "_";
      name += TO_UTF8(QString::number(i));
    }

  CData ToCopy = mpObject->toData();
  ToCopy.addProperty(CData::Property::OBJECT_NAME, name);
  ToCopy.removeProperty(CData::Property::OBJECT_INDEX);
  ToCopy.removeProperty(CData::OBJECT_UUID);
  ToCopy.removeProperty(CData::OBJECT_REFERENCES);

  CUnitDefinition * pUnitDef = new CUnitDefinition(name, unitList);
  unitList->add(pUnitDef, true);
  CUndoData::CChangeSet Changes;
  pUnitDef->applyData(ToCopy, Changes);

  CUndoData UndoData(CUndoData::Type::INSERT, pUnitDef);
  ListViews::addUndoMetaData(this, UndoData);
  UndoData.addMetaDataProperty("Widget Object CN (after)", pUnitDef->getCN());
  UndoData.addMetaDataProperty("Widget Object Name (after)", pUnitDef->getObjectName());

  slotNotifyChanges(mpDataModel->recordData(UndoData));
}

//! Slot for being activated whenever Delete button is clicked
void CQUnitDetail::slotBtnDelete()
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();

  if (pModel == NULL)
    return;

  CDataVectorN<CUnitDefinition>* pUnitDefs = CRootContainer::getUnitList();

  if (pUnitDefs == NULL)
    return;

  CUnitDefinition * pUnitDef = dynamic_cast<CUnitDefinition *>(mpObject);

  if (pUnitDef == NULL)
    return;

  CDataObject::DataObjectSet uses = pModel->getUnitSymbolUsage(pUnitDef->getSymbol());

  if (!uses.empty())
    {
      QString text = "It is required for . . .\n";

      CDataObject::DataObjectSet::const_iterator it = uses.begin();
      CDataObject::DataObjectSet::const_iterator end = uses.end();

      for (; it != end; ++it)
        {
          text += FROM_UTF8((*it)->getObjectName()) + "\n";
        }

      CQMessageBox::information(this,
                                "Unable to delete " + FROM_UTF8(pUnitDef->getObjectName()),
                                text,
                                QMessageBox::Ok, QMessageBox::Ok);
    }
  else
    {
      int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete " + FROM_UTF8(pUnitDef->getObjectName()) + "?",
                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if (ret == QMessageBox::Yes)
        {
          CUndoData UndoData;
          pUnitDef->createUndoData(UndoData, CUndoData::Type::REMOVE);
          ListViews::addUndoMetaData(this, UndoData);

          slotNotifyChanges(mpDataModel->applyData(UndoData));
        }
    }

  return;
}

void CQUnitDetail::init()
{
  mpExpressionValidator = new CQValidatorUnit(mpEditExpression);
  mpEditExpression->setValidator(mpExpressionValidator);
}

void CQUnitDetail::destroy()
{
  delete mpExpressionValidator;
}

bool CQUnitDetail::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  mpUnitDefinition = dynamic_cast< CUnitDefinition * >(mpObject);

  if (isVisible() && !mIgnoreUpdates)
    load();

  return true;
}

bool CQUnitDetail::leaveProtected()
{
  save();

  return true;
}

bool CQUnitDetail::enterProtected()
{
//  mpUnitDefinition = NULL;

  mpUnitDefinition = dynamic_cast<CUnitDefinition *>(mpObject);

  if (!mpUnitDefinition)
    {
      mpListView->switchToOtherWidget(ListViews::WidgetType::Units, std::string());
      return false;
    }

  load();

  return true;
}

/*!
    Load any saved values to the screen
 */
void CQUnitDetail::load()
{
  if (mpUnitDefinition == NULL) return;

  // Expression
  mpEditExpression->setText(FROM_UTF8(mpUnitDefinition->getExpression()));
  mpExpressionValidator->saved();

  // Symbol
  mpEditSymbol->setText(FROM_UTF8(mpUnitDefinition->getSymbol()));

  if (mpUnitDefinition->isReadOnly())
    {
      mpEditExpression->setEnabled(false);
      mpEditSymbol->setEnabled(false);
    }
  else
    {
      mpEditExpression->setEnabled(true);
      mpEditSymbol->setEnabled(true);
    }

  mChanged = false;
}

/*!
    Save any inputs and set them as initial setting values
 */
void CQUnitDetail::save()
{
  if (mpUnitDefinition == NULL) return;

  mChanged = false;
  CData OldData(mpUnitDefinition->toData());

  // set unit symbol
  if (mpUnitDefinition->getSymbol() != TO_UTF8(mpEditSymbol->text()))
    {
      if (!mpUnitDefinition->setSymbol(TO_UTF8(mpEditSymbol->text())))
        {
          QString msg;
          msg = "Unable set Symbol of Unit '" + FROM_UTF8(mpObject->getObjectName()) + "'\n"
                + "to '" + mpEditSymbol->text() + "' since a Unit with that symbol already exists.\n";

          CQMessageBox::information(this,
                                    "Unable set Symbol",
                                    msg,
                                    QMessageBox::Ok, QMessageBox::Ok);
        }
      else
        {
          mChanged = true;
        }
    }

  if (mpUnitDefinition->getExpression() != TO_UTF8(mpEditExpression->text()))
    {
      mpUnitDefinition->setExpression(TO_UTF8(mpEditExpression->text()));
      mChanged = true;
    }

  if (mChanged)
    {

      CUndoData UndoData;
      mpUnitDefinition->createUndoData(UndoData, CUndoData::Type::CHANGE, OldData, static_cast<CCore::Framework>(mFramework));
      ListViews::addUndoMetaData(this, UndoData);

      slotNotifyChanges(mpDataModel->recordData(UndoData));
      load();
    }

  mChanged = false;
}
