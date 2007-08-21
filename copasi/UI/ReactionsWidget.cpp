// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ReactionsWidget.cpp,v $
//   $Revision: 1.98 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/08/21 17:31:46 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>
#include <qfontmetrics.h>

#include "listviews.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "ReactionsWidget.h"

#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CChemEqInterface.h"
#include "model/CReaction.h"
#include "model/CReactionInterface.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"

std::vector<const CCopasiObject*> ReactionsWidget::getObjects() const
  {
    CCopasiVectorN<CReaction>& tmp = CCopasiDataModel::Global->getModel()->getReactions();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void ReactionsWidget::init()
{
  mOT = ListViews::REACTION;
  numCols = 5; // + 1;
  table->setNumCols(numCols);
  std::vector<const CCopasiObject*> objectstemp;
  //table->QTable::setNumRows(1);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Equation");
  tableHeader->setLabel(3, "Rate Law");
  tableHeader->setLabel(4, "Flux");

  //for sbml ids
  //tableHeader->setLabel(numCols - 1, "SBML ID");
  //table->setColumnReadOnly(numCols - 1, true);

  //this restricts users from editing function names
  table->setColumnReadOnly (3, true);
  table->setColumnReadOnly (4, true);
}

void ReactionsWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;

  const CReaction* pRea = (const CReaction*)obj;

  table->horizontalHeader()->setLabel(4, "Flux\n("
                                      + FROM_UTF8(CCopasiDataModel::Global->getModel()->getQuantityRateUnitName()) + ")");

  table->setText(row, 1, FROM_UTF8(pRea->getObjectName()));

  table->setText(row, 2, FROM_UTF8(CChemEqInterface::getChemEqString(CCopasiDataModel::Global->getModel(), *pRea, false)));

  if (pRea->getFunction())
    {
      table->setText(row, 3, FROM_UTF8(pRea->getFunction()->getObjectName()));
    }

  table->setText(row, 4, QString::number(pRea->getFlux()));
}

void ReactionsWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;

  // this loads the reaction into a CReactionInterface object.
  // the gui works on this object and later writes back the changes to ri;
  CReactionInterface ri(CCopasiDataModel::Global->getModel());
  ri.initFromReaction(obj->getKey());

  QString equation(table->text(row, 2));
  if ((const char *)equation.utf8() != ri.getChemEqString())
    {
      //first check if the string is a valid equation
      if (!CChemEqInterface::isValidEq((const char *)equation.utf8()))
        {
          //std::cout << "Not a valid equation!\n\n";
          return;
        }
      else
        {
          //tell the reaction interface
          ri.setChemEqString((const char *)equation.utf8(), "");
        }
    }

  //first check if new metabolites need to be created
  bool createdMetabs = ri.createMetabolites();
  bool createdObjects = ri.createOtherObjects();
  //this writes all changes to the reaction
  ri.writeBackToReaction(NULL);
  //CCopasiDataModel::Global->getModel()->compile();
  //this tells the gui what it needs to know.
  if (createdObjects)
    protectedNotify(ListViews::MODEL, ListViews::CHANGE, "");
  else
    {
      if (createdMetabs) protectedNotify(ListViews::METABOLITE, ListViews::ADD, "");
      protectedNotify(ListViews::REACTION, ListViews::CHANGE, "");
    }
}

void ReactionsWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != 2)
    table->clearCell(row, 2);

  if (exc != 3)
    table->clearCell(row, 3);

  if (exc != 4)
    table->clearCell(row, 4);
}

QString ReactionsWidget::defaultObjectName() const
  {
    return "reaction";
  }

CCopasiObject* ReactionsWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CReaction* pRea;
  while (!(pRea = CCopasiDataModel::Global->getModel()->createReaction(nname)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }
  //std::cout << " *** created Reaction: " << nname << " : " << pRea->getKey() << std::endl;
  return pRea;
}

void ReactionsWidget::deleteObjects(const std::vector<std::string> & keys)
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL)
    return;

  if (keys.size() == 0)
    return;

  QString reactionList = "Are you sure you want to delete listed REACTION(S) ?\n";
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
      CReaction * pReaction =
        dynamic_cast< CReaction *>(GlobalKeys.get(keys[i]));

      reactionList.append(FROM_UTF8(pReaction->getObjectName()));
      reactionList.append(", ");

      std::set< const CCopasiObject * > Reactions;
      std::set< const CCopasiObject * > Metabolites;
      std::set< const CCopasiObject * > Values;
      std::set< const CCopasiObject * > Compartments;

      pModel->appendDependentModelObjects(pReaction->getDeletedObjects(),
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
          effectedReacList.append(FROM_UTF8(pReaction->getObjectName()));
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
          effectedMetabList.append(FROM_UTF8(pReaction->getObjectName()));
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
          effectedValueList.append(FROM_UTF8(pReaction->getObjectName()));
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
          effectedCompartmentList.append(FROM_UTF8(pReaction->getObjectName()));
          effectedCompartmentList.append("\n");
        }
    }

  reactionList.remove(reactionList.length() - 2, 2);

  QString msg = reactionList;

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
            CCopasiDataModel::Global->getModel()->removeReaction(keys[i]);
          }

        for (i = 0; i < imax; i++)
          protectedNotify(ListViews::REACTION, ListViews::DELETE, keys[i]);

        mChanged = true;
        break;
      }
    default:                                           // No or Escape
      break;
    }
}
