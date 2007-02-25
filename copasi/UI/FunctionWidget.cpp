// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/FunctionWidget.cpp,v $
//   $Revision: 1.68 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/25 22:12:36 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "FunctionWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>

//#include "MyTable.h"
#include "function/CFunctionDB.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"

std::vector<const CCopasiObject*> FunctionWidget::getObjects() const
  {
    CCopasiVectorN<CEvaluationTree>& tmp = CCopasiDataModel::Global->getFunctionList()->loadedFunctions();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      if (dynamic_cast<CFunction *>(tmp[i]))
        ret.push_back(tmp[i]);

    return ret;
  }

void FunctionWidget::init()
{
  mOT = ListViews::FUNCTION;
  numCols = 4 + 1;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Type");
  tableHeader->setLabel(3, "mathematical description");

  //for sbml ids
  tableHeader->setLabel(numCols - 1, "SBML ID");
  table->setColumnReadOnly(numCols - 1, true);

  //this restricts users from editing function types or descriptions on the table
  table->setColumnReadOnly (2, true);
  table->setColumnReadOnly (3, true);
}

void FunctionWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CFunction* pFunc = (const CFunction*)obj;
  table->setText(row, 1, FROM_UTF8(pFunc->getObjectName()));
  table->setText(row, 2, FROM_UTF8(CEvaluationTree::TypeName[pFunc->getType()]));
  table->setText(row, 3, FROM_UTF8(pFunc->getInfix()));

  switch (pFunc->getType())
    {
    case CEvaluationTree::PreDefined:
    case CEvaluationTree::MassAction:
      mFlagRO[row] = true;
      break;
    case CEvaluationTree::UserDefined:
    case CEvaluationTree::Function:
    case CEvaluationTree::Expression:
      mFlagRO[row] = false;
      break;
    }
}

void FunctionWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CFunction* pFunc = (CFunction*) obj;

  if (CEvaluationTree::TypeName[pFunc->getType()] !=
      (const char *) table->text(row, 2).utf8())
    {
      QString msg;
      msg = "Type must not be changed for '" + FROM_UTF8(pFunc->getObjectName()) + "'.\n";

      QMessageBox::warning(this,
                           "Unable to change Function Type",
                           msg,
                           QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
    }
  if (pFunc->getInfix() != (const char *) table->text(row, 3).utf8())
    {
      if (!pFunc->setInfix((const char *) table->text(row, 3).utf8()))
        {
          QString msg;
          msg = "Incorrect  mathematical description'" + FROM_UTF8(pFunc->getObjectName()) + "'.\n";

          QMessageBox::warning(this,
                               "Unable to change mathematical description",
                               msg,
                               QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
        }
    }
}

void FunctionWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != 2)
    table->setText(row, 2, FROM_UTF8(CEvaluationTree::TypeName[4]));
  if (exc != 3)
    table->setText(row, 3, "");
}

QString FunctionWidget::defaultObjectName() const
  {
    return "function";
  }

CCopasiObject* FunctionWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CCopasiVectorN<CEvaluationTree>& FunctionList = CCopasiDataModel::Global->getFunctionList()->loadedFunctions();
  CFunction* pFunc;

  while (FunctionList.getIndex(nname) != C_INVALID_INDEX)
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }

  CCopasiDataModel::Global->getFunctionList()->add(pFunc = new CKinFunction(nname), true);

  //std::cout << " *** created Function: " << nname << " : " << pFunc->getKey() << std::endl;
  return pFunc;
}

void FunctionWidget::deleteObjects(const std::vector<std::string> & keys)
{
  if (keys.size() == 0)
    return;

  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL)
    return;

  CFunctionDB * pFunctionDB = CCopasiDataModel::Global->getFunctionList();
  if (pFunctionDB == NULL)
    return;

  CEvaluationTree * pFunction;

  QString functionList;
  QString effectedFunctionList = "Following FUNCTION(S) reference above FUNCTION(S) -\n";
  QString effectedReactionList = "Following REACTION(S) reference above FUNCTION(S) -\n";
  QString effectedMetaboliteList = "Following METABOLITE(S) reference above FUNCTION(S) -\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above FUNCTION(S) -\n";
  QString effectedValueList = "Following MODEL QUANTIT(S) reference above FUNCTION(S) -\n";

  bool functionFound = false;
  bool reactionFound = false;
  bool metaboliteFound = false;
  bool compartmentFound = false;
  bool valueFound = false;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++)
    {
      pFunction = dynamic_cast<CEvaluationTree *>(GlobalKeys.get(keys[i]));
      if (pFunction == NULL)
        continue;

      std::set< const CCopasiObject * > ToBeDeleted;
      ToBeDeleted.insert(pFunction);
      ToBeDeleted.insert(pFunction->getObject(CCopasiObjectName("Reference=Value")));

      functionList.append(FROM_UTF8(pFunction->getObjectName()));
      functionList.append(", ");

      std::set< const CCopasiObject * > Functions;
      pFunctionDB->appendDependentFunctions(ToBeDeleted, Functions);

      if (Functions.size() > 0)
        {
          functionFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Functions.end();
          for (it = Functions.begin(); it != itEnd; ++it)
            {
              effectedFunctionList.append(FROM_UTF8((*it)->getObjectName()));
              effectedFunctionList.append(", ");
            }

          effectedFunctionList.remove(effectedFunctionList.length() - 2, 2);
          effectedFunctionList.append("  ---> ");
          effectedFunctionList.append(FROM_UTF8(pFunction->getObjectName()));
          effectedFunctionList.append("\n");
        }

      std::set< const CCopasiObject * > Reactions;
      pModel->appendDependentReactions(ToBeDeleted, Reactions);

      if (Reactions.size() > 0)
        {
          reactionFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Reactions.end();
          for (it = Reactions.begin(); it != itEnd; ++it)
            {
              effectedReactionList.append(FROM_UTF8((*it)->getObjectName()));
              effectedReactionList.append(", ");
            }

          effectedReactionList.remove(effectedReactionList.length() - 2, 2);
          effectedReactionList.append("  ---> ");
          effectedReactionList.append(FROM_UTF8(pFunction->getObjectName()));
          effectedReactionList.append("\n");
        }

      std::set< const CCopasiObject * > Metabolites;
      pModel->appendDependentMetabolites(ToBeDeleted, Metabolites);

      if (Metabolites.size() > 0)
        {
          metaboliteFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Metabolites.end();
          for (it = Metabolites.begin(); it != itEnd; ++it)
            {
              effectedMetaboliteList.append(FROM_UTF8((*it)->getObjectName()));
              effectedMetaboliteList.append(", ");
            }

          effectedMetaboliteList.remove(effectedMetaboliteList.length() - 2, 2);
          effectedMetaboliteList.append("  ---> ");
          effectedMetaboliteList.append(FROM_UTF8(pFunction->getObjectName()));
          effectedMetaboliteList.append("\n");
        }

      std::set< const CCopasiObject * > Compartments;
      pModel->appendDependentCompartments(ToBeDeleted, Compartments);

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
          effectedCompartmentList.append(FROM_UTF8(pFunction->getObjectName()));
          effectedCompartmentList.append("\n");
        }

      std::set< const CCopasiObject * > Values;
      pModel->appendDependentModelValues(ToBeDeleted, Values);

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
          effectedValueList.append(FROM_UTF8(pFunction->getObjectName()));
          effectedValueList.append("\n");
        }
    }

  functionList.remove(functionList.length() - 2, 2);

  QString msg;

  if (functionFound || reactionFound || metaboliteFound || compartmentFound || valueFound)
    {
      msg = "Cannot delete FUNCTION(S).\n" + functionList;

      if (functionFound)
        {
          msg.append("\n \n");
          msg.append(effectedFunctionList);
        }

      if (reactionFound)
        {
          msg.append("\n \n");
          msg.append(effectedReactionList);
        }

      if (metaboliteFound)
        {
          msg.append("\n \n");
          msg.append(effectedMetaboliteList);
        }

      if (compartmentFound)
        {
          msg.append("\n \n");
          msg.append(effectedCompartmentList);
        }

      if (valueFound)
        {
          msg.append("\n \n");
          msg.append(effectedValueList);
        }

      QMessageBox::warning(this, "Sorry, Cannot Delete",
                           msg, "OK", 0, 0, 0, 1);

      return;
    }

  msg = "Are you sure to delete listed Function(s)?\n" + functionList;

  int choice = QMessageBox::warning(this,
                                    "CONFIRM DELETE",
                                    msg,
                                    "Continue", "Cancel", 0, 0, 1);

  switch (choice)
    {
    case 0:                          // Yes or Enter
      {
        //now delete functions
        for (i = 0; i < imax; i++)
          {
            CCopasiDataModel::Global->getFunctionList()->removeFunction(keys[i]);
            protectedNotify(ListViews::FUNCTION, ListViews::DELETE, keys[i]);
          }

        break;
      }
    case 1:                          // No or Escape
      break;
    }
}
