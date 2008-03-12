// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CompartmentsWidget.cpp,v $
//   $Revision: 1.116 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 00:32:58 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*******************************************************************
 **  $ CopasiUI/CompartmentsWidget.cpp
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the
 ** information obtained from the data model about the
 ** Compartments----It is Basically the First level of Compartments
 ********************************************************************/
#include "CompartmentsWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>
#include <qregexp.h>
#include <qvalidator.h>

#include "CQMessageBox.h"
#include "listviews.h"
#include "qtUtilities.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "report/CKeyFactory.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "function/CExpression.h"

#define COL_MARK         0
#define COL_NAME         1
#define COL_TYPE         2
#define COL_IVOLUME      3
#define COL_VOLUME       4
#define COL_RATE         5
#define COL_IEXPRESSION  6
#define COL_EXPRESSION   7

std::vector<const CCopasiObject*> CompartmentsWidget::getObjects() const
  {
    CCopasiVectorN<CCompartment>& tmp = CCopasiDataModel::Global->getModel()->getCompartments();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void CompartmentsWidget::init()
{
  mOT = ListViews::COMPARTMENT;
  numCols = 8;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");
  tableHeader->setLabel(COL_NAME, "Name");
  tableHeader->setLabel(COL_TYPE, "Type");
  // tableHeader->setLabel(COL_IVOLUME, "Initial Volume");
  // tableHeader->setLabel(COL_VOLUME, "Volume");
  // tableHeader->setLabel(COL_RATE, "Rate");
  tableHeader->setLabel(COL_IEXPRESSION, "Initial Expression");
  tableHeader->setLabel(COL_EXPRESSION, "Expression");

  // Set readonly
  table->setColumnReadOnly (COL_VOLUME, true);
  table->setColumnReadOnly (COL_RATE, true);
  table->setColumnReadOnly (COL_IEXPRESSION, true);
  table->setColumnReadOnly (COL_EXPRESSION, true);

  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);
}

void CompartmentsWidget::updateHeaderUnits()
{
  QHeader *tableHeader = table->horizontalHeader();

  if (CCopasiDataModel::Global->getModel())
    {
      std::string str = CCopasiDataModel::Global->getModel()->getVolumeUnitName();
      tableHeader->setLabel(COL_IVOLUME, "Initial Volume\n(" + FROM_UTF8(str) + ")");
      tableHeader->setLabel(COL_VOLUME, "Volume\n(" + FROM_UTF8(str) + ")");
      tableHeader->setLabel(COL_RATE,
                            "Rate\n(" + FROM_UTF8(str) + "/" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnitName()) + ")");
    }
}

void CompartmentsWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CCompartment * pComp = static_cast< const CCompartment * >(obj);

  // Name
  table->setText(row, COL_NAME, FROM_UTF8(pComp->getObjectName()));

  // Type
  QComboTableItem * pComboBox = new QComboTableItem(table, mTypes);
  pComboBox->setCurrentItem(FROM_UTF8(CModelEntity::StatusName[pComp->getStatus()]));
  table->setItem(row, COL_TYPE, pComboBox);

  // Initial Volume
  table->setText(row, COL_IVOLUME, QString::number(pComp->getInitialValue()));
  if (pComp->getStatus() == CModelEntity::ASSIGNMENT ||
      pComp->getInitialExpression() != "")
    table->item(row, COL_IVOLUME)->setEnabled(false);
  else
    table->item(row, COL_IVOLUME)->setEnabled(true);

  // Volume
  table->setText(row, COL_VOLUME, QString::number(pComp->getValue()));

  // Rate
  table->setText(row, COL_RATE, QString::number(pComp->getRate()));

  const CExpression * pExpression = NULL;
  // Initial Expression
  if (pComp->getInitialExpression() != "")
    {
      pExpression = pComp->getInitialExpressionPtr();
      if (pExpression != NULL)
        table->setText(row, COL_IEXPRESSION, FROM_UTF8(pExpression->getDisplayString()));
      else
        table->clearCell(row, COL_IEXPRESSION);
    }

  // Expression
  pExpression = pComp->getExpressionPtr();
  if (pExpression != NULL)
    table->setText(row, COL_EXPRESSION, FROM_UTF8(pExpression->getDisplayString()));
  else
    table->clearCell(row, COL_EXPRESSION);
}

void CompartmentsWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CCompartment * pComp = static_cast< CCompartment * >(obj);

  // Type
  if (dynamic_cast<QComboTableItem *>(table->item(row, COL_TYPE)))
    pComp->setStatus((CModelEntity::Status) mItemToType[static_cast<QComboTableItem *>(table->item(row, COL_TYPE))->currentItem()]);

  // Initial Volume
  pComp->setInitialValue(table->text(row, COL_IVOLUME).toDouble());
}

void CompartmentsWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  // Type
  if (exc != COL_TYPE)
    {
      QComboTableItem * pComboBox = new QComboTableItem(table, mTypes);
      pComboBox->setCurrentItem(0);
      table->setItem(row, COL_TYPE, pComboBox);
    }

  // Initial Volume
  if (exc != COL_IVOLUME)
    table->setText(row, COL_IVOLUME, QString::number(1.0));

  // Volume
  if (exc != COL_VOLUME)
    table->clearCell(row, COL_VOLUME);

  // Rate
  if (exc != COL_RATE)
    table->clearCell(row, COL_RATE);

  // Initial Expression
  if (exc != COL_IEXPRESSION)
    table->clearCell(row, COL_IEXPRESSION);

  // Expression
  if (exc != COL_EXPRESSION)
    table->clearCell(row, COL_EXPRESSION);
}

QString CompartmentsWidget::defaultObjectName() const
  {
    return "compartment";
  }

CCopasiObject* CompartmentsWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CCompartment* pCom;
  while (!(pCom = CCopasiDataModel::Global->getModel()->createCompartment(nname)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }
  //std::cout << " *** created Compartment: " << nname << " : " << pCom->getKey() << std::endl;
  return pCom;
}

void CompartmentsWidget::deleteObjects(const std::vector<std::string> & keys)
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL)
    return;

  if (keys.size() == 0)
    return;

  QString compartmentList = "Are you sure you want to delete listed COMPARTMENT(S) ?\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedMetabList = "Following SPECIES reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedValueList = "Following MODEL VALUE(S) reference above COMPARTMENT(S) and will be deleted -\n";

  bool compartmentFound = false;
  bool metabFound = false;
  bool reacFound = false;
  bool valueFound = false;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all compartments
    {
      CCompartment* comp =
        dynamic_cast< CCompartment *>(GlobalKeys.get(keys[i]));

      compartmentList.append(FROM_UTF8(comp->getObjectName()));
      compartmentList.append(", ");

      std::set< const CCopasiObject * > Reactions;
      std::set< const CCopasiObject * > Metabolites;
      std::set< const CCopasiObject * > Values;
      std::set< const CCopasiObject * > Compartments;

      pModel->appendDependentModelObjects(comp->getDeletedObjects(),
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
          effectedReacList.append(FROM_UTF8(comp->getObjectName()));
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
          effectedMetabList.append(FROM_UTF8(comp->getObjectName()));
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
          effectedValueList.append(FROM_UTF8(comp->getObjectName()));
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
          effectedCompartmentList.append(FROM_UTF8(comp->getObjectName()));
          effectedCompartmentList.append("\n");
        }
    }

  compartmentList.remove(compartmentList.length() - 2, 2);

  QString msg = compartmentList;

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
    case 0:                    // Yes or Enter
      {
        for (i = 0; i < imax; i++)
          {
            CCopasiDataModel::Global->getModel()->removeCompartment(keys[i]);
          }

        for (i = 0; i < imax; i++)
          protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, keys[i]);
        //TODO notify about metabs and reactions

        mChanged = true;
        break;
      }

    default:                    // No or Escape
      break;
    }
}

void CompartmentsWidget::valueChanged(unsigned C_INT32 row, unsigned C_INT32 col)
{
  switch (col)
    {
    case COL_TYPE:
      if (CModelEntity::ASSIGNMENT == (CModelEntity::Status) mItemToType[static_cast<QComboTableItem *>(table->item(row, COL_TYPE))->currentItem()])
        table->item(row, COL_IVOLUME)->setEnabled(false);
      else
        table->item(row, COL_IVOLUME)->setEnabled(true);
      break;

    default:
      break;
    }
  return;
}
