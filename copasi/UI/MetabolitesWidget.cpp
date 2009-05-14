// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MetabolitesWidget.cpp,v $
//   $Revision: 1.158 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/05/14 18:48:40 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "MetabolitesWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>

//#include "MyTable.h"
#include "listviews.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "report/CKeyFactory.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "function/CExpression.h"

#define COL_MARK               0
#define COL_NAME               1
#define COL_COMPARTMENT        2
#define COL_TYPE               3
#define COL_ICONCENTRATION     4
#define COL_INUMBER            5
#define COL_CONCENTRATION      6
#define COL_NUMBER             7
#define COL_CRATE              8
#define COL_NRATE              9
#define COL_IEXPRESSION       10
#define COL_EXPRESSION        11
#define COL_CURRENTCOMPARTMENT    12

std::vector<const CCopasiObject*> MetabolitesWidget::getObjects() const
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiVector<CMetab>& tmp = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getMetabolites();
  std::vector<const CCopasiObject*> ret;

  C_INT32 i, imax = tmp.size();

  for (i = 0; i < imax; ++i)
    ret.push_back(tmp[i]);

  return ret;
}

void MetabolitesWidget::init()
{
  mOT = ListViews::METABOLITE;
  numCols = 13; //+ 1; //+1 for SBML id
  table->setNumCols(numCols);

  //Setting table headers
  Q3Header *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_NAME, "Name");
  tableHeader->setLabel(COL_COMPARTMENT, "Compartment");
  tableHeader->setLabel(COL_TYPE, "Type");
  // tableHeader->setLabel(COL_ICONCENTRATION, "Initial Concentration");
  tableHeader->setLabel(COL_INUMBER, "Initial Number");
  // tableHeader->setLabel(COL_CONCENTRATION, "Concentration");
  tableHeader->setLabel(COL_NUMBER, "Number");
  // tableHeader->setLabel(COL_CRATE, "Rate");
  // tableHeader->setLabel(COL_NRATE, "Number Rate");
  // tableHeader->setLabel(COL_IEXPRESSION, "Initial Expression");
  // tableHeader->setLabel(COL_EXPRESSION, "Expression");

  // Hide columns
  table->hideColumn(COL_CURRENTCOMPARTMENT);

  // Set read only
  table->setColumnReadOnly(COL_CONCENTRATION, true);
  table->setColumnReadOnly(COL_NUMBER, true);
  table->setColumnReadOnly(COL_CRATE, true);
  table->setColumnReadOnly(COL_NRATE, true);
  table->setColumnReadOnly(COL_IEXPRESSION, true);
  table->setColumnReadOnly(COL_EXPRESSION, true);

  // We start with the concentration showing.
  setFramework(mFramework);

  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::REACTIONS]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::REACTIONS);
  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);
}

void MetabolitesWidget::updateHeaderUnits()
{
  Q3Header *tableHeader = table->horizontalHeader();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  const CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  if (pModel == NULL) return;

  QString ValueUnits;

  if (pModel)
    ValueUnits = FROM_UTF8(pModel->getConcentrationUnitsDisplayString());

  if (!ValueUnits.isEmpty())
    ValueUnits = "\n(" + ValueUnits + ")";

  QString RateUnits;

  if (pModel)
    RateUnits = FROM_UTF8(pModel->getConcentrationRateUnitsDisplayString());

  if (!RateUnits.isEmpty())
    RateUnits = "\n(" + RateUnits + ")";

  QString FrequencyUnits;

  if (pModel)
    FrequencyUnits = FROM_UTF8(pModel->getFrequencyUnitsDisplayString());

  if (!FrequencyUnits.isEmpty())
    FrequencyUnits = "\n(" + FrequencyUnits + ")";

  tableHeader->setLabel(COL_ICONCENTRATION, "Initial Concentration" + ValueUnits);
  tableHeader->setLabel(COL_CONCENTRATION, "Concentration" + ValueUnits);

  tableHeader->setLabel(COL_CRATE, "Rate" + RateUnits);
  tableHeader->setLabel(COL_NRATE, "Number Rate" + FrequencyUnits);
  tableHeader->setLabel(COL_IEXPRESSION, "Initial Expression" + ValueUnits);

  QString ExpressionUnits;

  if (!ValueUnits.isEmpty() && !RateUnits.isEmpty())
    {
      if (ValueUnits == RateUnits)
        ExpressionUnits = ValueUnits;
      else
        ExpressionUnits = "\n(" + FROM_UTF8(pModel->getConcentrationUnitsDisplayString())
                          + " or " + FROM_UTF8(pModel->getConcentrationRateUnitsDisplayString()) + ")";
    }
  else if (!ValueUnits.isEmpty())
    ExpressionUnits = "\n(" + FROM_UTF8(pModel->getConcentrationUnitsDisplayString()) + " or 1)";
  else if (!RateUnits.isEmpty())
    ExpressionUnits = "\n(1 or " + FROM_UTF8(pModel->getConcentrationRateUnitsDisplayString()) + ")";

  tableHeader->setLabel(COL_EXPRESSION, "Expression" + ExpressionUnits);
}

void MetabolitesWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;

  const CMetab* pMetab = static_cast<const CMetab *>(obj);

  // Name
  table->setText(row, COL_NAME, FROM_UTF8(pMetab->getObjectName()));

  // Compartment
  QStringList compartmentType;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  const CCopasiVector < CCompartment > & compartments = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments();

  for (unsigned C_INT32 jj = 0; jj < compartments.size(); jj++)
    compartmentType.push_back(FROM_UTF8(compartments[jj]->getObjectName()));

  Q3ComboTableItem * item = new Q3ComboTableItem(table, compartmentType, false);
  table->setItem(row, COL_COMPARTMENT, item);
  item->setCurrentItem(FROM_UTF8(pMetab->getCompartment()->getObjectName()));

  // Type
  Q3ComboTableItem * pComboBox = new Q3ComboTableItem(table, mTypes);
  pComboBox->setCurrentItem(FROM_UTF8(CModelEntity::StatusName[pMetab->getStatus()]));
  table->setItem(row, COL_TYPE, pComboBox);

  // Initial Concentration
  table->setText(row, COL_ICONCENTRATION, QString::number(pMetab->getInitialConcentration()));

  // Initial Number
  table->setText(row, COL_INUMBER, QString::number(pMetab->getInitialValue()));

  if (pMetab->getStatus() == CModelEntity::ASSIGNMENT ||
      pMetab->getInitialExpression() != "")
    {
      table->item(row, COL_ICONCENTRATION)->setEnabled(false);
      table->item(row, COL_INUMBER)->setEnabled(false);
    }
  else
    {
      table->item(row, COL_ICONCENTRATION)->setEnabled(const_cast< CMetab * >(pMetab)->isInitialConcentrationChangeAllowed());
      table->item(row, COL_INUMBER)->setEnabled(true);
    }

  // Transient Concentration
  table->setText(row, COL_CONCENTRATION, QString::number(pMetab->getConcentration()));

  // Transient Number
  table->setText(row, COL_NUMBER, QString::number(pMetab->getValue()));

  // Concentration Rate
  table->setText(row, COL_CRATE, QString::number(pMetab->getConcentrationRate()));

  // Number Rate
  table->setText(row, COL_NRATE, QString::number(pMetab->getRate()));

  const CExpression * pExpression = NULL;

  // Initial Expression
  if (pMetab->getInitialExpression() != "")
    {
      pExpression = pMetab->getInitialExpressionPtr();

      if (pExpression != NULL)
        table->setText(row, COL_IEXPRESSION, FROM_UTF8(pExpression->getDisplayString()));
      else
        table->clearCell(row, COL_IEXPRESSION);
    }

  // Expression
  pExpression = pMetab->getExpressionPtr();

  if (pExpression != NULL)
    table->setText(row, COL_EXPRESSION, FROM_UTF8(pExpression->getDisplayString()));
  else
    table->clearCell(row, COL_EXPRESSION);

  // Current Compartment
  table->setText(row, COL_CURRENTCOMPARTMENT,
                 FROM_UTF8(pMetab->getCompartment()->getObjectName()));
}

void MetabolitesWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;

  CMetab* pMetab = static_cast<CMetab *>(obj);

  // Compartment
  // This must be set first for setInitialConcentration and
  // setInitialNumber to work correctly.
  QString Compartment(table->text(row, COL_COMPARTMENT));

  if ((TO_UTF8(Compartment) != pMetab->getCompartment()->getObjectName()) //has changed
      && (Compartment != ""))
    {
      std::string CompartmentToRemove = pMetab->getCompartment()->getObjectName();
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

      if (!(*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[TO_UTF8(Compartment)]->addMetabolite(pMetab))
        {
          QString msg;
          msg = "Unable to move species '" + FROM_UTF8(pMetab->getObjectName()) + "'\n"
                + "from compartment '" + FROM_UTF8(CompartmentToRemove) + "' to compartment '" + Compartment + "'\n"
                + "since a species with that name already exist in the target compartment.";

          CQMessageBox::information(this,
                                    "Unable to move Species",
                                    msg,
                                    QMessageBox::Ok, QMessageBox::Ok);
        }
      else
        {
          (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[CompartmentToRemove]->getMetabolites().remove(pMetab->getObjectName());
          (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->setCompileFlag();
          (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->initializeMetabolites();
          protectedNotify(ListViews::METABOLITE, ListViews::CHANGE, "");
          protectedNotify(ListViews::COMPARTMENT, ListViews::CHANGE, "");
        }
    }

  // Type
  if (dynamic_cast<Q3ComboTableItem *>(table->item(row, COL_TYPE)))
    pMetab->setStatus((CModelEntity::Status) mItemToType[static_cast<Q3ComboTableItem *>(table->item(row, COL_TYPE))->currentItem()]);

  // Initial Concentration or Initial Number
  if (mFlagConc)
    pMetab->setInitialConcentration(table->text(row, COL_ICONCENTRATION).toDouble());
  else
    pMetab->setInitialValue(table->text(row, COL_INUMBER).toDouble());
}

void MetabolitesWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  // Compartment
  if (exc != COL_COMPARTMENT)
    {
      QStringList compartmentType;
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      const CCopasiVector < CCompartment > & compartments =
        (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments();

      for (unsigned C_INT32 jj = 0; jj < compartments.size(); jj++)
        compartmentType.push_back(FROM_UTF8(compartments[jj]->getObjectName()));

      Q3ComboTableItem * item = new Q3ComboTableItem(table, compartmentType, false);
      table->setItem(row, COL_COMPARTMENT, item);

      if (compartments.size())
        item->setCurrentItem(FROM_UTF8(compartments[0]->getObjectName()));
    }

  // Current Compartment
  if (exc != COL_CURRENTCOMPARTMENT)
    table->setText(row, COL_CURRENTCOMPARTMENT,
                   table->text(row, COL_COMPARTMENT));

  // Type
  if (exc != COL_TYPE)
    {
      Q3ComboTableItem * pComboBox = new Q3ComboTableItem(table, mTypes);
      pComboBox->setCurrentItem(0);
      table->setItem(row, COL_TYPE, pComboBox);
    }

  if (mFlagConc)
    {
      // Initial Concentration
      if (exc != COL_ICONCENTRATION)
        table->setText(row, COL_ICONCENTRATION, QString::number(1.0));

      table->setText(row, COL_INUMBER, "");
      initialConcentrationChanged(row);
    }
  else
    {
      // Initial Number
      if (exc != COL_INUMBER)
        table->setText(row, COL_INUMBER, QString::number(100.0));

      table->clearCell(row, COL_ICONCENTRATION);
      initialNumberChanged(row);
    }

  // Concentration
  if (exc != COL_CONCENTRATION)
    table->clearCell(row, COL_CONCENTRATION);

  // Number
  if (exc != COL_NUMBER)
    table->clearCell(row, COL_NUMBER);

  // Concentration Rate
  if (exc != COL_CRATE)
    table->clearCell(row, COL_CRATE);

  // Number Rate
  if (exc != COL_NRATE)
    table->clearCell(row, COL_NRATE);

  // Initial Expression
  if (exc != COL_IEXPRESSION)
    table->clearCell(row, COL_IEXPRESSION);

  // Expression
  if (exc != COL_EXPRESSION)
    table->clearCell(row, COL_EXPRESSION);
}

QString MetabolitesWidget::defaultObjectName() const
{
  return "species";
}

CCopasiObject* MetabolitesWidget::createNewObject(const std::string & name)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  if (pDataModel->getModel()->getCompartments().size() == 0)
    pDataModel->getModel()->createCompartment("compartment");

  std::string nname = name;
  int i = 0;
  CMetab* pMetab;

  while (!(pMetab = pDataModel->getModel()->createMetabolite(nname, "", 1.0, CModelEntity::REACTIONS)))
    {
      i++;
      nname = name + "_";
      nname += TO_UTF8(QString::number(i));
    }

  return pMetab;
}

void MetabolitesWidget::deleteObjects(const std::vector<std::string> & keys)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  if (keys.size() == 0)
    return;

  QString ObjectType = "species";
  QString Objects;
  std::set< const CCopasiObject * > DeletedObjects;

  unsigned C_INT32 i, imax = keys.size();

  for (i = 0; i < imax; i++)
    {
      CMetab* pMetab =
        dynamic_cast< CMetab *>(CCopasiRootContainer::getKeyFactory()->get(keys[i]));

      if (pMetab == NULL)
        continue;

      Objects.append(FROM_UTF8(pMetab->getObjectName()) + ", ");

      std::set< const CCopasiObject * > AdditionalObjects =
        pMetab->getDeletedObjects();

      std::set< const CCopasiObject * >::const_iterator itDeleted = AdditionalObjects.begin();
      std::set< const CCopasiObject * >::const_iterator endDeleted = AdditionalObjects.end();

      for (; itDeleted != endDeleted; ++itDeleted)
        DeletedObjects.insert(*itDeleted);
    }

  Objects.remove(Objects.length() - 2, 2);

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(NULL, pModel, ObjectType,
                                Objects, DeletedObjects);

  switch (choice)
    {
      case QMessageBox::Ok:                                           // Yes or Enter
      {
        for (i = 0; i < imax; i++)
          {
            pDataModel->getModel()->removeMetabolite(keys[i]);
          }

        for (i = 0; i < imax; i++)
          protectedNotify(ListViews::METABOLITE, ListViews::DELETE, keys[i]);

        //TODO notify about reactions

        mChanged = true;
        break;
      }
      default:                                           // No or Escape
        break;
    }
}

void MetabolitesWidget::valueChanged(unsigned C_INT32 row, unsigned C_INT32 col)
{
  switch (col)
    {
      case COL_TYPE:

        if (CModelEntity::ASSIGNMENT == (CModelEntity::Status) mItemToType[static_cast<Q3ComboTableItem *>(table->item(row, COL_TYPE))->currentItem()])
          {
            table->item(row, COL_ICONCENTRATION)->setEnabled(false);
            table->item(row, COL_INUMBER)->setEnabled(false);
          }
        else
          {
            table->item(row, COL_ICONCENTRATION)->setEnabled(true);
            table->item(row, COL_INUMBER)->setEnabled(true);
          }

        break;

      case COL_ICONCENTRATION:
        initialConcentrationChanged(row);
        break;

      case COL_INUMBER:
        initialNumberChanged(row);
        break;

      case COL_COMPARTMENT:
        compartmentChanged(row);
        break;

      default:
        break;
    }

  return;
}

void MetabolitesWidget::initialConcentrationChanged(unsigned C_INT32 row)
{
  const CMetab * pMetab
  = static_cast< CMetab * >(CCopasiRootContainer::getKeyFactory()->get(mKeys[row]));

  const CCompartment * pCompartment = NULL;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  unsigned C_INT32 Index =
    (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments().getIndex(TO_UTF8(table->text(row, COL_CURRENTCOMPARTMENT)));

  if (Index != C_INVALID_INDEX)
    {
      pCompartment = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[Index];
    }

  if (!pMetab || !pCompartment) return;

  table->setText(row, COL_INUMBER,
                 QString::number(CMetab::convertToNumber(table->text(row, COL_ICONCENTRATION).toDouble(),
                                                         *pCompartment,
                                                         *(*CCopasiRootContainer::getDatamodelList())[0]->getModel())));
  return;
}

void MetabolitesWidget::initialNumberChanged(unsigned C_INT32 row)
{
  const CMetab * pMetab
  = static_cast< CMetab * >(CCopasiRootContainer::getKeyFactory()->get(mKeys[row]));

  const CCompartment * pCompartment = NULL;

  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      pCompartment = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[TO_UTF8(table->text(row, COL_CURRENTCOMPARTMENT))];
    }
  catch (...) {}

  if (!pMetab || !pCompartment) return;

  table->setText(row, COL_ICONCENTRATION,
                 QString::number(CMetab::convertToConcentration(table->text(row, COL_INUMBER).toDouble(),
                                 *pCompartment,
                                 *(*CCopasiRootContainer::getDatamodelList())[0]->getModel())));
  return;
}

void MetabolitesWidget::compartmentChanged(unsigned C_INT32 row)
{
  const CMetab * pMetab
  = static_cast< CMetab * >(CCopasiRootContainer::getKeyFactory()->get(mKeys[row]));

  QString Compartment = table->text(row, COL_CURRENTCOMPARTMENT);

  const CCompartment * pCompartment = NULL;

  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      pCompartment = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[TO_UTF8(table->text(row, COL_CURRENTCOMPARTMENT))];
    }
  catch (...) {}

  if (!pMetab || !pCompartment) return;

  C_FLOAT64 Factor = 1.0 / pCompartment->getInitialValue();

  Compartment = table->text(row, COL_COMPARTMENT);
  table->setText(row, COL_CURRENTCOMPARTMENT, Compartment);

  pCompartment
  = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[TO_UTF8(Compartment)];
  Factor *= pCompartment->getInitialValue();

  table->setText(row, COL_INUMBER,
                 QString::number(Factor * table->text(row, COL_INUMBER).toDouble()));
  table->setText(row, COL_NUMBER,
                 QString::number(Factor * table->text(row, COL_NUMBER).toDouble()));

  return;
}

void MetabolitesWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);

  switch (mFramework)
    {
      case 0:
        table->showColumn(COL_ICONCENTRATION);
        table->showColumn(COL_CONCENTRATION);
        table->showColumn(COL_CRATE);

        table->hideColumn(COL_INUMBER);
        table->hideColumn(COL_NUMBER);
        table->hideColumn(COL_NRATE);

        mFlagConc = true;
        break;

      case 1:
        table->hideColumn(COL_ICONCENTRATION);
        table->hideColumn(COL_CONCENTRATION);
        table->hideColumn(COL_CRATE);

        table->showColumn(COL_INUMBER);
        table->showColumn(COL_NUMBER);
        table->showColumn(COL_NRATE);

        mFlagConc = false;
        break;
    }
}
