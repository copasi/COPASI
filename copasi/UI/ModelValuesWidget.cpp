/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ModelValuesWidget.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/07/19 18:51:19 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "ModelValuesWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>
#include <qstringlist.h>

//#include "MyTable.h"
#include "model/CModel.h"
#include "model/CModelValue.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"
#include "CopasiDataModel/CCopasiDataModel.h"

#define COL_NAME 1
#define COL_TYPE 2
#define COL_INITIAL 3
#define COL_TRANSIENT 4
#define COL_EXPRESSION 5

std::vector<const CCopasiObject*> ModelValuesWidget::getObjects() const
  {
    CCopasiVectorN<CModelValue>& tmp = CCopasiDataModel::Global->getModel()->getModelValues();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void ModelValuesWidget::init()
{
  mOT = ListViews::MODELVALUE;
  numCols = 6 + 1;
  table->setNumCols(numCols);
  table->setColumnReadOnly (COL_TRANSIENT, true);
  table->setColumnReadOnly (COL_EXPRESSION, true);

  //table->QTable::setNumRows(1);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();

  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(COL_NAME, "Name");
  tableHeader->setLabel(COL_TYPE, "Type");
  tableHeader->setLabel(COL_INITIAL, "Initial Value");
  tableHeader->setLabel(COL_TRANSIENT, "Transient Value");
  tableHeader->setLabel(COL_EXPRESSION, "Expression");

  //for sbml ids
  tableHeader->setLabel(numCols - 1, "SBML ID");
  table->setColumnReadOnly(numCols - 1, true);
}

void ModelValuesWidget::showHeaders()
{
  /*  QHeader *tableHeader = table->horizontalHeader();
    tableHeader->setLabel(0, "Status");
    tableHeader->setLabel(COL_NAME "Name");
    if (CCopasiDataModel::Global->getModel())
      {
        std::string str = CCopasiDataModel::Global->getModel()->getVolumeUnit();
        tableHeader->setLabel(COL_INITIAL "Volume\n(" + FROM_UTF8(str) + ")");
      }*/
}

void ModelValuesWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CModelValue* pMV = dynamic_cast<const CModelValue*>(obj);
  if (!pMV) return;
  table->setText(row, COL_NAME, FROM_UTF8(pMV->getObjectName()));

  QStringList Types;
  Types.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  Types.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  Types.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));
  QComboTableItem * pComboBox = new QComboTableItem(table, Types);
  pComboBox->setCurrentItem(pMV->getStatus());
  table->setItem(row, COL_TYPE, pComboBox);

  table->setText(row, COL_INITIAL, QString::number(pMV->getInitialValue()));
  table->setText(row, COL_TRANSIENT, QString::number(pMV->getValue()));

  std::string Expression = pMV->getExpression();

  unsigned C_INT32 i = 0;

  std::string out_str = "";
  while (i < Expression.length())
    {
      if (Expression[i] == '<')
        {
          i++;
          std::string objectName = "";

          while (Expression[i] != '>' && i < Expression.length())
            {
              if (Expression[i] == '\\')
                objectName += Expression[i++];

              objectName += Expression[i];
              i++;
            }

          CCopasiObjectName temp_CN(objectName);
          CCopasiObject * temp_object = const_cast<CCopasiObject *>(RootContainer.getObject(temp_CN));
          out_str += "<" + temp_object->getObjectDisplayName() + ">";
          continue;
        }

      else if (Expression[i] == '>')
        {
          //do nothing
        }

      else
        {
          out_str += Expression[i];
        }

      i++;
    }

  table->setText(row, COL_EXPRESSION, FROM_UTF8(out_str));

  showHeaders();
}

void ModelValuesWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CModelValue* pMV = dynamic_cast<CModelValue*>(obj);
  if (!pMV) return;
  pMV->setStatus((CModelEntity::Status) static_cast<QComboTableItem *>(table->item(row, COL_TYPE))->currentItem());
  pMV->setInitialValue(table->text(row, COL_INITIAL).toDouble());
}

void ModelValuesWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != COL_INITIAL)
    table->setText(row, COL_INITIAL, QString::number(0.0));
  if (exc != COL_TYPE)
    {
      QStringList Types;
      Types.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
      Types.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
      Types.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));
      QComboTableItem * pComboBox = new QComboTableItem(table, Types);
      pComboBox->setCurrentItem(0);
      table->setItem(row, COL_TYPE, pComboBox);
    }
}

QString ModelValuesWidget::defaultObjectName() const
  {
    return "quantity";
  }

CCopasiObject* ModelValuesWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CModelValue* pMV;
  while (!(pMV = CCopasiDataModel::Global->getModel()->createModelValue(nname)))
    {
      i++;
      nname = name + "_";
      nname += (const char *)QString::number(i).utf8();
    }
  //std::cout << " *** created non concentration value: " << nname << " : " << pMV->getKey() << std::endl;
  return pMV;
}

void ModelValuesWidget::deleteObjects(const std::vector<std::string> & keys)
{
  if (!CCopasiDataModel::Global->getModel())
    return;

  if (keys.size() == 0)
    return;

  QString valuesList = "Are you sure you want to delete listed parameter(s) ?\n";
  QString effectedReacList = "Following reation(s) reference above parameter(s) and will be deleted -\n";
  int reacFound = 0;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all modelValues
    {
      valuesList.append(FROM_UTF8(GlobalKeys.get(keys[i])->getObjectName()));
      valuesList.append(", ");

      CModelValue* mv =
        dynamic_cast< CModelValue *>(GlobalKeys.get(keys[i]));

      std::set<std::string> effectedReacKeys = CCopasiDataModel::Global->getModel()->listReactionsDependentOnModelValue(keys[i]);
      if (effectedReacKeys.size() > 0)
        {
          reacFound = 1;
          std::set<std::string>::const_iterator it, itEnd = effectedReacKeys.end();
          for (it = effectedReacKeys.begin(); it != itEnd; ++it)
            {
              effectedReacList.append(FROM_UTF8(GlobalKeys.get(*it)->getObjectName()));
              effectedReacList.append(", ");
            }

          effectedReacList.remove(effectedReacList.length() - 2, 2);
          effectedReacList.append("  ---> ");
          effectedReacList.append(FROM_UTF8(mv->getObjectName()));
          effectedReacList.append("\n");
        }
    }

  valuesList.remove(valuesList.length() - 2, 2);

  QString msg = valuesList;
  if (reacFound == 1)
    {
      msg.append("\n \n");
      msg.append(effectedReacList);
    }

  C_INT32 choice;
  if (reacFound == 1)
    choice = QMessageBox::warning(this,
                                  "CONFIRM DELETE",
                                  msg,
                                  "Continue", "Cancel", 0, 0, 1);
  else
    choice = 0;

  switch (choice)
    {
    case 0:                     // Yes or Enter
      {
        for (i = 0; i < imax; i++)
          {
            CCopasiDataModel::Global->getModel()->removeModelValue(keys[i]);
          }

        for (i = 0; i < imax; i++)
          ListViews::notify(ListViews::MODELVALUE, ListViews::DELETE, keys[i]);
        //TODO notify about metabs and reactions
        break;
      }
    case 1:                     // No or Escape
      break;
    }
}
