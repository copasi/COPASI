/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/FunctionWidget.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:47 $
   End CVS Header */

#include "FunctionWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>

#include "MyTable.h"
#include "function/CFunctionDB.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"
#include "utilities/CGlobals.h"
#include "model/CModel.h"

std::vector<const CCopasiObject*> FunctionWidget::getObjects() const
  {
    CCopasiVectorN<CFunction>& tmp = Copasi->pFunctionDB->loadedFunctions();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void FunctionWidget::init()
{
  mOT = ListViews::FUNCTION;
  numCols = 4;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Type");
  tableHeader->setLabel(3, "mathematical description");

  //this restricts users from editing function types or descriptions on the table
  table->setColumnReadOnly (2, true);
  table->setColumnReadOnly (3, true);
}

void FunctionWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CFunction* pFunc = (const CFunction*)obj;
  table->setText(row, 1, FROM_UTF8(pFunc->getObjectName()));

  QString ftype;
  switch (pFunc->getType())
    {
    case 1:
    case 2:
      ftype = QString("pre-defined");
      mFlagRO[row] = true;
      break;
    case 3:
      ftype = QString("user-defined");
      break;
    }
  table->setText(row, 2, ftype);
  table->setText(row, 3, FROM_UTF8(pFunc->getDescription()));
}

void FunctionWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CFunction* pFunc = (CFunction*)obj;
}

void FunctionWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != 2)
    table->setText(row, 2, "");
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
  CFunction* pFunc;
  while (!(pFunc = Copasi->pFunctionDB->createFunction(nname, CFunction::UserDefined)))
    {
      i++;
      nname = name;
      nname += (const char *)QString::number(i).utf8();
    }
  std::cout << " *** created Function: " << nname << " : " << pFunc->getKey() << std::endl;
  return pFunc;
}

void FunctionWidget::deleteObjects(const std::vector<std::string> & keys)
{
  if (!dataModel->getModel())
    return;

  if (keys.size() == 0)
    return;

  QString funcList = "Are you sure you want to delete listed function(s)?\n";
  QString effectedReacList = "The following reaction(s) reference above functions(s) and will be deleted -\n";
  int reacFound = 0;

  std::set<std::string> totalEffectedReacKeys;
  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++)
    {
      funcList.append(FROM_UTF8(GlobalKeys.get(keys[i])->getObjectName()));
      funcList.append(", ");

      //CMetab* metab =
      //  dynamic_cast< CMetab *>(GlobalKeys.get(keys[i]));

      std::set<std::string> effectedReacKeys = dataModel->getModel()->listReactionsDependentOnFunction(keys[i]);

      if (effectedReacKeys.size() > 0)
        {
          reacFound = 1;
          std::set<std::string>::const_iterator it, itEnd = effectedReacKeys.end();
          for (it = effectedReacKeys.begin(); it != itEnd; ++it)
            {
              effectedReacList.append(FROM_UTF8(GlobalKeys.get(*it)->getObjectName()));
              effectedReacList.append(", ");
              totalEffectedReacKeys.insert(*it);
            }
          effectedReacList.remove(effectedReacList.length() - 2, 2);
          effectedReacList.append("  ---> ");
          effectedReacList.append(FROM_UTF8(GlobalKeys.get(keys[i])->getObjectName()));
          effectedReacList.append("\n");
        }
    }
  funcList.remove(funcList.length() - 2, 2);

  QString msg = funcList;
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
    case 0:                   // Yes or Enter
      {
        //first delete reactions
        std::set<std::string>::const_iterator it, itEnd = totalEffectedReacKeys.end();
        for (it = totalEffectedReacKeys.begin(); it != itEnd; ++it)
          {
            dataModel->getModel()->removeReaction(*it);
            ListViews::notify(ListViews::REACTION, ListViews::DELETE, *it);
          }

        //now delete functions

        for (i = 0; i < imax; i++)
          {
            Copasi->pFunctionDB->removeFunction(keys[i]);
            ListViews::notify(ListViews::FUNCTION, ListViews::DELETE, keys[i]);
          }

        break;
      }
    case 1:                   // No or Escape
      break;
    }
}
