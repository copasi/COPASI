// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CompartmentsWidget.cpp,v $
//   $Revision: 1.105.4.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/01/30 00:13:01 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>
#include <qregexp.h>
#include <qvalidator.h>

//#include "MyTable.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"
#include "CopasiDataModel/CCopasiDataModel.h"

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
  numCols = 3; //+ 1;
  table->setNumCols(numCols);
  //table->QTable::setNumRows(1);

  //Setting table headers

  QHeader *tableHeader = table->horizontalHeader();

  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Volume");

  //for sbml ids
  //tableHeader->setLabel(numCols - 1, "SBML ID");
  //table->setColumnReadOnly(numCols - 1, true);
}

void CompartmentsWidget::showHeaders()
{
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  if (CCopasiDataModel::Global->getModel())
    {
      std::string str = CCopasiDataModel::Global->getModel()->getVolumeUnitName();
      tableHeader->setLabel(2, "Volume\n(" + FROM_UTF8(str) + ")");
    }
}

void CompartmentsWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CCompartment* pComp = (const CCompartment*)obj;
  table->setText(row, 1, FROM_UTF8(pComp->getObjectName()));
  table->setText(row, 2, QString::number(pComp->getValue()));
  showHeaders();
}

void CompartmentsWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  int pos = 0;
  QDoubleValidator v(this, "");
  QString tmpstring = table->text(row, 2);
  if ((v.validate(tmpstring, pos) == QValidator::Intermediate) ||
      (v.validate(tmpstring, pos) == QValidator::Invalid))
    {
      QMessageBox::warning(this, "Parent Compartment Widget::Invalid Input!!!",
                           "The volume must be given",
                           QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
      return;
    }
  CCompartment* pComp = (CCompartment*)obj;
  pComp->setInitialValue(table->text(row, 2).toDouble());
}

void CompartmentsWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != 2)
    table->setText(row, 2, QString::number(1.0));
}

QString CompartmentsWidget::defaultObjectName() const
  {
    return "compartment";
  }

//specific
/*void CompartmentsWidget::createNewObject()
{
  std::string name = "compartment_0";
  int i = 0;
  while (!CCopasiDataModel::Global->getModel()->createCompartment(name))
    {
      i++;
      name = "compartment_";
      name += (const char *)QString::number(i).utf8();
    }
  table->setText(table->numRows() - 1, 1, FROM_UTF8(name));
  table->setNumRows(table->numRows());
  ListViews::notify(ListViews::COMPARTMENT, ListViews::ADD);
}*/

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
  QString effectedMetabList = "Following METABOLITE(S) reference above COMPARTMENT(S) and will be deleted -\n";
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
      pModel->appendDependentReactions(comp->getDeletedObjects(), Reactions);

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

      std::set< const CCopasiObject * > Metabolites;
      pModel->appendDependentMetabolites(comp->getDeletedObjects(), Metabolites);

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

      std::set< const CCopasiObject * > Values;
      pModel->appendDependentModelValues(comp->getDeletedObjects(), Values);

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

      std::set< const CCopasiObject * > Compartments;
      pModel->appendDependentCompartments(comp->getDeletedObjects(), Compartments);

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

  C_INT32 choice;
  if (metabFound || reacFound || valueFound || valueFound)
    choice = QMessageBox::warning(this,
                                  "CONFIRM DELETE",
                                  msg,
                                  "Continue", "Cancel", 0, 0, 1);
  else
    choice = 0;

  switch (choice)
    {
    case 0:                    // Yes or Enter
      {
        for (i = 0; i < imax; i++)
          {
            CCopasiDataModel::Global->getModel()->removeCompartment(keys[i]);
          }

        for (i = 0; i < imax; i++)
          ListViews::notify(ListViews::COMPARTMENT, ListViews::DELETE, keys[i]);
        //TODO notify about metabs and reactions
        break;
      }
    case 1:                    // No or Escape
      break;
    }
}
