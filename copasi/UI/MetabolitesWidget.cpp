// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MetabolitesWidget.cpp,v $
//   $Revision: 1.149 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 00:32:59 $
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
    CCopasiVector<CMetab>& tmp = CCopasiDataModel::Global->getModel()->getMetabolites();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void MetabolitesWidget::init()
{
  mOT = ListViews::METABOLITE;
  numCols = 13; //+ 1; //+1 for sbml id
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_NAME, "Name");
  tableHeader->setLabel(COL_COMPARTMENT, "Compartment");
  tableHeader->setLabel(COL_TYPE, "Type");
  // tableHeader->setLabel(COL_ICONCENTRATION, "Initial Concentration");
  tableHeader->setLabel(COL_INUMBER, "Initial Number");
  // tableHeader->setLabel(COL_CONCENTRATION, "Concentration");
  tableHeader->setLabel(COL_NUMBER, "Number");
  // tableHeader->setLabel(COL_CRATE, "Rate");
  tableHeader->setLabel(COL_NRATE, "Number Rate");
  tableHeader->setLabel(COL_IEXPRESSION, "Initial Expression");
  tableHeader->setLabel(COL_EXPRESSION, "Expression");

  // Hide columns
  table->hideColumn(COL_CURRENTCOMPARTMENT);

  // Set readonly
  table->setColumnReadOnly (COL_CONCENTRATION, true);
  table->setColumnReadOnly (COL_NUMBER, true);
  table->setColumnReadOnly (COL_CRATE, true);
  table->setColumnReadOnly (COL_NRATE, true);
  table->setColumnReadOnly (COL_IEXPRESSION, true);
  table->setColumnReadOnly (COL_EXPRESSION, true);

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
  QHeader *tableHeader = table->horizontalHeader();

  if (CCopasiDataModel::Global->getModel())
    {
      tableHeader->setLabel(COL_ICONCENTRATION, "Initial Concentration\n(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getConcentrationUnitName()) + ")");
      tableHeader->setLabel(COL_CONCENTRATION, "Concentration\n(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getConcentrationUnitName()) + ")");
      tableHeader->setLabel(COL_CRATE, "Rate\n("
                            + FROM_UTF8(CCopasiDataModel::Global->getModel()->getConcentrationRateUnitName()) + ")");
    }
}

void MetabolitesWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CMetab* pMetab = static_cast<const CMetab *>(obj);

  // Name
  table->setText(row, COL_NAME, FROM_UTF8(pMetab->getObjectName()));

  // Compartment
  QStringList compartmentType;
  const CCopasiVector < CCompartment > & compartments = CCopasiDataModel::Global->getModel()->getCompartments();
  for (unsigned C_INT32 jj = 0; jj < compartments.size(); jj++)
    compartmentType.push_back(FROM_UTF8(compartments[jj]->getObjectName()));
  QComboTableItem * item = new QComboTableItem(table, compartmentType, false);
  table->setItem(row, COL_COMPARTMENT, item);
  item->setCurrentItem(FROM_UTF8(pMetab->getCompartment()->getObjectName()));

  // Type
  QComboTableItem * pComboBox = new QComboTableItem(table, mTypes);
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
  if (((const char *)Compartment.utf8() != pMetab->getCompartment()->getObjectName()) //has changed
      && (Compartment != ""))
    {
      std::string CompartmentToRemove = pMetab->getCompartment()->getObjectName();
      if (!CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)Compartment.utf8()]->addMetabolite(pMetab))
        {
          QString msg;
          msg = "Unable to move species '" + FROM_UTF8(pMetab->getObjectName()) + "'\n"
                + "from compartment '" + FROM_UTF8(CompartmentToRemove) + "' to compartment '" + Compartment + "'\n"
                + "since a species with that name already exist in the target compartment.";

          CQMessageBox::information(this,
                                    "Unable to move Species",
                                    msg,
                                    QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
        }
      else
        {
          CCopasiDataModel::Global->getModel()->getCompartments()[CompartmentToRemove]->getMetabolites().remove(pMetab->getObjectName());
          CCopasiDataModel::Global->getModel()->setCompileFlag();
          CCopasiDataModel::Global->getModel()->initializeMetabolites();
          protectedNotify(ListViews::METABOLITE, ListViews::CHANGE, "");
          protectedNotify(ListViews::COMPARTMENT, ListViews::CHANGE, "");
        }
    }

  // Type
  if (dynamic_cast<QComboTableItem *>(table->item(row, COL_TYPE)))
    pMetab->setStatus((CModelEntity::Status) mItemToType[static_cast<QComboTableItem *>(table->item(row, COL_TYPE))->currentItem()]);

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
      const CCopasiVector < CCompartment > & compartments =
        CCopasiDataModel::Global->getModel()->getCompartments();
      for (unsigned C_INT32 jj = 0; jj < compartments.size(); jj++)
        compartmentType.push_back(FROM_UTF8(compartments[jj]->getObjectName()));

      QComboTableItem * item = new QComboTableItem(table, compartmentType, false);
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
      QComboTableItem * pComboBox = new QComboTableItem(table, mTypes);
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
  if (CCopasiDataModel::Global->getModel()->getCompartments().size() == 0)
    CCopasiDataModel::Global->getModel()->createCompartment("compartment");

  std::string nname = name;
  int i = 0;
  CMetab* pMetab;
  while (!(pMetab = CCopasiDataModel::Global->getModel()->createMetabolite(nname, "", 1.0, CModelEntity::REACTIONS)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }
  //std::cout << " *** created Species: " << nname << " : " << pMetab->getKey() << std::endl;
  return pMetab;
}

void MetabolitesWidget::deleteObjects(const std::vector<std::string> & keys)
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL)
    return;

  if (keys.size() == 0)
    return;

  QString metaboliteList = "Are you sure you want to delete listed SPECIES ?\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above SPECIES and will be deleted -\n";
  QString effectedMetabList = "Following METABOLITE(S) reference above SPECIES and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above SPECIES and will be deleted -\n";
  QString effectedValueList = "Following MODEL VALUE(S) reference above SPECIES and will be deleted -\n";

  bool compartmentFound = false;
  bool metabFound = false;
  bool reacFound = false;
  bool valueFound = false;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all compartments
    {
      CMetab* pMetab =
        dynamic_cast< CMetab *>(GlobalKeys.get(keys[i]));

      metaboliteList.append(FROM_UTF8(pMetab->getObjectName()));
      metaboliteList.append(", ");

      std::set< const CCopasiObject * > Reactions;
      std::set< const CCopasiObject * > Metabolites;
      std::set< const CCopasiObject * > Values;
      std::set< const CCopasiObject * > Compartments;

      pModel->appendDependentModelObjects(pMetab->getDeletedObjects(),
                                          Reactions, Metabolites, Compartments, Values);

      if (Reactions.size() > 0)
        {
          reacFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Reactions.end();
          for (it = Reactions.begin(); it != itEnd; ++it)
            {
              effectedReacList.append(FROM_UTF8((*it)->getObjectName()));
              effectedReacList.append(", ");
            }

          effectedReacList.remove(effectedReacList.length() - 2, 2);
          effectedReacList.append("  ---> ");
          effectedReacList.append(FROM_UTF8(pMetab->getObjectName()));
          effectedReacList.append("\n");
        }

      if (Metabolites.size() > 0)
        {
          metabFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Metabolites.end();
          for (it = Metabolites.begin(); it != itEnd; ++it)
            {
              effectedMetabList.append(FROM_UTF8((*it)->getObjectName()));
              effectedMetabList.append(", ");
            }

          effectedMetabList.remove(effectedMetabList.length() - 2, 2);
          effectedMetabList.append("  ---> ");
          effectedMetabList.append(FROM_UTF8(pMetab->getObjectName()));
          effectedMetabList.append("\n");
        }

      if (Values.size() > 0)
        {
          valueFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Values.end();
          for (it = Values.begin(); it != itEnd; ++it)
            {
              effectedValueList.append(FROM_UTF8((*it)->getObjectName()));
              effectedValueList.append(", ");
            }

          effectedValueList.remove(effectedValueList.length() - 2, 2);
          effectedValueList.append("  ---> ");
          effectedValueList.append(FROM_UTF8(pMetab->getObjectName()));
          effectedValueList.append("\n");
        }

      if (Compartments.size() > 0)
        {
          compartmentFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Compartments.end();
          for (it = Compartments.begin(); it != itEnd; ++it)
            {
              effectedCompartmentList.append(FROM_UTF8((*it)->getObjectName()));
              effectedCompartmentList.append(", ");
            }

          effectedCompartmentList.remove(effectedCompartmentList.length() - 2, 2);
          effectedCompartmentList.append("  ---> ");
          effectedCompartmentList.append(FROM_UTF8(pMetab->getObjectName()));
          effectedCompartmentList.append("\n");
        }
    }

  metaboliteList.remove(metaboliteList.length() - 2, 2);

  QString msg = metaboliteList;

  if (compartmentFound)
    {
      msg.append("\n \n");
      msg.append(effectedCompartmentList);
    }

  if (metabFound)
    {
      msg.append("\n \n");
      msg.append(effectedMetabList);
    }

  if (reacFound)
    {
      msg.append("\n \n");
      msg.append(effectedReacList);
    }

  if (valueFound)
    {
      msg.append("\n \n");
      msg.append(effectedValueList);
    }

  C_INT32 choice = 0;
  if (metabFound || reacFound || valueFound || valueFound)
    choice = CQMessageBox::question(this,
                                    "CONFIRM DELETE",
                                    msg,
                                    "Continue", "Cancel", 0, 1, 1);

  switch (choice)
    {
    case 0:                                           // Yes or Enter
      {
        for (i = 0; i < imax; i++)
          {
            CCopasiDataModel::Global->getModel()->removeMetabolite(keys[i]);
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
      if (CModelEntity::ASSIGNMENT == (CModelEntity::Status) mItemToType[static_cast<QComboTableItem *>(table->item(row, COL_TYPE))->currentItem()])
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
  = static_cast< CMetab * >(GlobalKeys.get(mKeys[row]));

  const CCompartment * pCompartment = NULL;

  unsigned C_INT32 Index =
    CCopasiDataModel::Global->getModel()->getCompartments().getIndex((const char *)table->text(row, COL_CURRENTCOMPARTMENT).utf8());
  if (Index != C_INVALID_INDEX)
    {
      pCompartment = CCopasiDataModel::Global->getModel()->getCompartments()[Index];
    }

  if (!pMetab || !pCompartment) return;

  table->setText(row, COL_INUMBER,
                 QString::number(CMetab::convertToNumber(table->text(row, COL_ICONCENTRATION).toDouble(),
                                                         *pCompartment,
                                                         *CCopasiDataModel::Global->getModel())));
  return;
}

void MetabolitesWidget::initialNumberChanged(unsigned C_INT32 row)
{
  const CMetab * pMetab
  = static_cast< CMetab * >(GlobalKeys.get(mKeys[row]));

  const CCompartment * pCompartment = NULL;
  try
    {
      pCompartment = CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)table->text(row, COL_CURRENTCOMPARTMENT).utf8()];
    }
  catch (...) {}

  if (!pMetab || !pCompartment) return;

  table->setText(row, COL_ICONCENTRATION,
                 QString::number(CMetab::convertToConcentration(table->text(row, COL_INUMBER).toDouble(),
                                 *pCompartment,
                                 *CCopasiDataModel::Global->getModel())));
  return;
}

void MetabolitesWidget::compartmentChanged(unsigned C_INT32 row)
{
  const CMetab * pMetab
  = static_cast< CMetab * >(GlobalKeys.get(mKeys[row]));

  QString Compartment = table->text(row, COL_CURRENTCOMPARTMENT);

  const CCompartment * pCompartment = NULL;
  try
    {
      pCompartment = CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)table->text(row, COL_CURRENTCOMPARTMENT).utf8()];
    }
  catch (...) {}

  if (!pMetab || !pCompartment) return;

  C_FLOAT64 Factor = 1.0 / pCompartment->getInitialValue();

  Compartment = table->text(row, COL_COMPARTMENT);
  table->setText(row, COL_CURRENTCOMPARTMENT, Compartment);

  pCompartment
  = CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)Compartment.utf8()];
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
