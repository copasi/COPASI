/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ModelValuesWidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/05/25 09:51:14 $
   End CVS Header */

#include "ModelValuesWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>

//#include "MyTable.h"
#include "model/CModel.h"
#include "model/CModelValue.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"
#include "CopasiDataModel/CCopasiDataModel.h"

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
  numCols = 3;
  table->setNumCols(numCols);
  //table->QTable::setNumRows(1);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();

  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Value");
}

void ModelValuesWidget::showHeaders()
{
  /*  QHeader *tableHeader = table->horizontalHeader();
    tableHeader->setLabel(0, "Status");
    tableHeader->setLabel(1, "Name");
    if (CCopasiDataModel::Global->getModel())
      {
        std::string str = CCopasiDataModel::Global->getModel()->getVolumeUnit();
        tableHeader->setLabel(2, "Volume\n(" + FROM_UTF8(str) + ")");
      }*/
}

void ModelValuesWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CModelValue* pMV = dynamic_cast<const CModelValue*>(obj);
  if (!pMV) return;
  table->setText(row, 1, FROM_UTF8(pMV->getObjectName()));
  table->setText(row, 2, QString::number(pMV->getValue()));
  showHeaders();
}

void ModelValuesWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CModelValue* pMV = dynamic_cast<CModelValue*>(obj);
  if (!pMV) return;
  pMV->setInitialValue(table->text(row, 2).toDouble());
  pMV->setValue(table->text(row, 2).toDouble());
}

void ModelValuesWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != 2)
    table->setText(row, 2, QString::number(0.0));
}

QString ModelValuesWidget::defaultObjectName() const
  {
    return "parameter";
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
  std::cout << " *** created non concentration value: " << nname << " : " << pMV->getKey() << std::endl;
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
