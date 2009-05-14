// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/FunctionWidget.cpp,v $
//   $Revision: 1.81 $
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

#include "FunctionWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>

//#include "MyTable.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "report/CKeyFactory.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "function/CFunctionDB.h"
#include "model/CModel.h"

std::vector<const CCopasiObject*> FunctionWidget::getObjects() const
{
  CCopasiVectorN<CEvaluationTree>& tmp = CCopasiRootContainer::getFunctionList()->loadedFunctions();
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
  Q3Header *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Type");
  tableHeader->setLabel(3, "mathematical description");

  //for sbml ids
  tableHeader->setLabel(numCols - 1, "SBML ID");
  table->setColumnReadOnly(numCols - 1, true);

  //this restricts users from editing function types or descriptions on the table
  table->setColumnReadOnly(2, true);
  table->setColumnReadOnly(3, true);
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
      case CEvaluationTree::Boolean:
        mFlagRO[row] = false;
        break;
    }
}

void FunctionWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;

  CFunction* pFunc = (CFunction*) obj;

  if (CEvaluationTree::TypeName[pFunc->getType()] !=
      TO_UTF8(table->text(row, 2)))
    {
      QString msg;
      msg = "Type must not be changed for '" + FROM_UTF8(pFunc->getObjectName()) + "'.\n";

      CQMessageBox::information(this,
                                "Unable to change Function Type",
                                msg,
                                QMessageBox::Ok, QMessageBox::Ok);
    }

  if (pFunc->getInfix() != TO_UTF8(table->text(row, 3)))
    {
      if (!pFunc->setInfix(TO_UTF8(table->text(row, 3))))
        {
          QString msg;
          msg = "Incorrect  mathematical description'" + FROM_UTF8(pFunc->getObjectName()) + "'.\n";

          CQMessageBox::information(this,
                                    "Unable to change mathematical description",
                                    msg,
                                    QMessageBox::Ok, QMessageBox::Ok);
        }
    }
}

void FunctionWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != 2)
    table->setText(row, 2, FROM_UTF8(CEvaluationTree::TypeName[4]));

  if (exc != 3)
    table->clearCell(row, 3);
}

QString FunctionWidget::defaultObjectName() const
{
  return "function";
}

CCopasiObject* FunctionWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CCopasiVectorN<CEvaluationTree>& FunctionList = CCopasiRootContainer::getFunctionList()->loadedFunctions();
  CFunction* pFunc;

  while (FunctionList.getIndex(nname) != C_INVALID_INDEX)
    {
      i++;
      nname = name + "_";
      nname += TO_UTF8(QString::number(i));
    }

  CCopasiRootContainer::getFunctionList()->add(pFunc = new CKinFunction(nname), true);

  return pFunc;
}

void FunctionWidget::deleteObjects(const std::vector<std::string> & keys)
{
  if (keys.size() == 0)
    return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  if (pModel == NULL)
    return;

  CFunctionDB * pFunctionDB = CCopasiRootContainer::getFunctionList();

  if (pFunctionDB == NULL)
    return;

  CEvaluationTree * pFunction;

  QString ObjectType = "function(s)";
  QString Objects;
  std::set< const CCopasiObject * > DeletedObjects;

  unsigned C_INT32 i, imax = keys.size();

  for (i = 0; i < imax; i++)
    {
      pFunction = dynamic_cast<CEvaluationTree *>(CCopasiRootContainer::getKeyFactory()->get(keys[i]));

      if (pFunction == NULL)
        continue;

      Objects.append(FROM_UTF8(pFunction->getObjectName()) + ", ");

      std::set< const CCopasiObject * > AdditionalObjects =
        pFunction->getDeletedObjects();

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
      case QMessageBox::Ok:
      {
        //now delete functions
        for (i = 0; i < imax; i++)
          {
            CCopasiRootContainer::getFunctionList()->removeFunction(keys[i]);
            protectedNotify(ListViews::FUNCTION, ListViews::DELETE, keys[i]);
          }

        mChanged = true;
        break;
      }
      default:
        break;
    }
}
