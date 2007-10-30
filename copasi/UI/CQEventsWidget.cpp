// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEventsWidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/10/30 16:08:52 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "listviews.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "CQEventsWidget.h"

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"

std::vector<const CCopasiObject*> CQEventsWidget::getObjects() const
  {
    CCopasiVectorN<CEvent>& tmp = CCopasiDataModel::Global->getModel()->getEvents();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void CQEventsWidget::init()
{
  mOT = ListViews::EVENT;
  numCols = 3; // + 1;
  table->setNumCols(numCols);
  std::vector<const CCopasiObject*> objectstemp;
  //table->QTable::setNumRows(1);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Bla");

  //for sbml ids
  //tableHeader->setLabel(numCols - 1, "SBML ID");
  //table->setColumnReadOnly(numCols - 1, true);

  //this restricts users from editing function names
  //table->setColumnReadOnly (3, true);
}

void CQEventsWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;

  const CEvent* pEv = dynamic_cast<const CEvent*>(obj);
  assert(pEv);

  //table->horizontalHeader()->setLabel(4, "Flux\n("
  //                                    + FROM_UTF8(CCopasiDataModel::Global->getModel()->getQuantityRateUnitName()) + ")");

  table->setText(row, 1, FROM_UTF8(pEv->getObjectName()));

  //table->setText(row, 2, FROM_UTF8(CChemEqInterface::getChemEqString(CCopasiDataModel::Global->getModel(), *pRea, false)));
  table->setText(row, 2, "abc");
}

void CQEventsWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
}

void CQEventsWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != 2)
    table->clearCell(row, 2);

  //if (exc != 3)
  // table->clearCell(row, 3);
}

QString CQEventsWidget::defaultObjectName() const
  {
    return "event";
  }

CCopasiObject* CQEventsWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CEvent* pEv;
  while (!(pEv = CCopasiDataModel::Global->getModel()->createEvent(nname)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }
  //std::cout << " *** created Reaction: " << nname << " : " << pRea->getKey() << std::endl;
  return pEv;
}

void CQEventsWidget::deleteObjects(const std::vector<std::string> & keys)
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL)
    return;

  if (keys.size() == 0)
    return;

  QString eventList = "Are you sure you want to delete listed Event(s) ?\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above REACTION(S) and will be deleted -\n";
  QString effectedMetabList = "Following METABOLITE(S) reference above REACTION(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above REACTION(S) and will be deleted -\n";
  QString effectedValueList = "Following MODEL VALUE(S) reference above REACTION(S) and will be deleted -\n";

  bool compartmentFound = false;
  bool metabFound = false;
  bool reacFound = false;
  bool valueFound = false;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all compartments
    {
      CEvent * pEvent =
        dynamic_cast< CEvent *>(GlobalKeys.get(keys[i]));
      if (!pEvent) continue;

      eventList.append(FROM_UTF8(pEvent->getObjectName()));
      eventList.append(", ");

      std::set< const CCopasiObject * > Reactions;
      std::set< const CCopasiObject * > Metabolites;
      std::set< const CCopasiObject * > Values;
      std::set< const CCopasiObject * > Compartments;

      pModel->appendDependentModelObjects(pEvent->getDeletedObjects(),
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
          //effectedReacList.append("  ---> ");
          //effectedReacList.append(FROM_UTF8(pEvent->getObjectName()));
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
          //effectedMetabList.append("  ---> ");
          //effectedMetabList.append(FROM_UTF8(pEvent->getObjectName()));
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
          //effectedValueList.append("  ---> ");
          //effectedValueList.append(FROM_UTF8(pEvent->getObjectName()));
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
          //effectedCompartmentList.append("  ---> ");
          //effectedCompartmentList.append(FROM_UTF8(pEvent->getObjectName()));
          effectedCompartmentList.append("\n");
        }
    }

  eventList.remove(eventList.length() - 2, 2);

  QString msg = eventList;

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
            CCopasiDataModel::Global->getModel()->removeEvent(keys[i]);
          }

        for (i = 0; i < imax; i++)
          protectedNotify(ListViews::EVENT, ListViews::DELETE, keys[i]);

        mChanged = true;
        break;
      }
    default:                                           // No or Escape
      break;
    }
}
