// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEventsWidget.cpp,v $
//   $Revision: 1.16 $
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

#include "listviews.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "CQEventsWidget.h"

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "report/CKeyFactory.h"

#define COL_MARK    0
#define COL_NAME    1
#define COL_TRIGGER    2
#define COL_DELAY    3
#define COL_ASSIGNTARGET  4
#define COL_ASSIGNEXPRESSION 5

std::vector<const CCopasiObject*> CQEventsWidget::getObjects() const
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiVectorN<CEvent>& tmp = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getEvents();
  std::vector<const CCopasiObject*> ret;

  C_INT32 i, imax = tmp.size();

  for (i = 0; i < imax; ++i)
    ret.push_back(tmp[i]);

  return ret;
}

void CQEventsWidget::init()
{
  mOT = ListViews::EVENT;
  numCols = 6; // + 1;
  table->setNumCols(numCols);
  std::vector<const CCopasiObject*> objectstemp;
  //table->QTable::setNumRows(1);

  //Setting table headers
  Q3Header *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Condition Trigger");
  tableHeader->setLabel(3, "Delay");
  tableHeader->setLabel(4, "Assignment Target");
  tableHeader->setLabel(5, "Assignment Expression");
}

void CQEventsWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;

  const CEvent* pEv = dynamic_cast<const CEvent*>(obj);
  assert(pEv);

  //table->horizontalHeader()->setLabel(4, "Flux\n("
  //                                    + FROM_UTF8((*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getQuantityRateUnitName()) + ")");
  table->setText(row, 1, FROM_UTF8(pEv->getObjectName()));

  table->setText(row, 2, FROM_UTF8(pEv->getTriggerExpression()));
  table->setText(row, 3, FROM_UTF8(pEv->getDelayExpression()));

  QString assignmentTarget = "";
  QString assignmentExpression = "";

  CCopasiVectorN< CEventAssignment >::const_iterator it = pEv->getAssignments().begin();
  CCopasiVectorN< CEventAssignment >::const_iterator begin = pEv->getAssignments().begin();
  CCopasiVectorN< CEventAssignment >::const_iterator end = pEv->getAssignments().end();

  for (; it != end; ++it)
    {
      const CModelEntity * pEntity =
        dynamic_cast< CModelEntity * >(CCopasiRootContainer::getKeyFactory()->get((*it)->getTargetKey()));

      if (pEntity != NULL)
        {
          if (it != begin)
            {
              assignmentTarget += "\n";
              assignmentExpression += "\n";
            }

          assignmentTarget += FROM_UTF8(pEntity->getObjectDisplayName());
          assignmentExpression += FROM_UTF8((*it)->getExpression());
        }
    }

  table->setText(row, 4, assignmentTarget);
  table->setText(row, 5, assignmentExpression);

  table->adjustRow(row);
}

void CQEventsWidget::tableLineToObject(unsigned C_INT32 C_UNUSED(row), CCopasiObject* obj)
{
  if (!obj) return;
}

void CQEventsWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 /* exc */)
{
  //  std::cout << "exc = " << exc << std::endl;

  //  if (exc != 2)
  //    table->clearCell(row, 2);

  table->clearCell(row, 2);
  table->clearCell(row, 3);
  table->clearCell(row, 4);
  table->clearCell(row, 5);

  //  {int y; std::cout << "L: " << __LINE__ << std::endl; std::cin >> y;}

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
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  while (!(pEv = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createEvent(nname)))
    {
      i++;
      nname = name + "_";
      nname += TO_UTF8(QString::number(i));
    }

  //std::cout << " *** created Reaction: " << nname << " : " << pRea->getKey() << std::endl;
  return pEv;
}

void CQEventsWidget::deleteObjects(const std::vector<std::string> & keys)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  if (pModel == NULL)
    return;

  if (keys.size() == 0)
    return;

  unsigned C_INT32 i, imax = keys.size();

  for (i = 0; i < imax; i++)
    {
      (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->removeEvent(keys[i]);
    }

  for (i = 0; i < imax; i++)
    protectedNotify(ListViews::EVENT, ListViews::DELETE, keys[i]);

  return;
}
