/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MetabolitesWidget.cpp,v $
   $Revision: 1.94 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/21 08:57:52 $
   End CVS Header */

#include "MetabolitesWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>

#include "MyTable.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"

std::vector<const CCopasiObject*> MetabolitesWidget::getObjects() const
  {
    CCopasiVector<CMetab>& tmp = dataModel->getModel()->getMetabolites();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void MetabolitesWidget::init()
{
  mFlagConc = false;
  btnToggle = new QPushButton("&Show Concentrations", this);
  mHLayout->addWidget(btnToggle);
  connect(btnToggle, SIGNAL(clicked ()), this,
          SLOT(slotBtnToggleClicked()));

  numCols = 7;
  table->setNumCols(numCols);
  table->QTable::setNumRows(1);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Initial Concentration");
  tableHeader->setLabel(3, "Concentration");
  tableHeader->setLabel(4, "Fixed");
  tableHeader->setLabel(5, "Status");
  tableHeader->setLabel(6, "Compartment");

  //this restricts users from editing concentration values on the table
  table->setColumnReadOnly (3, true);
  //this restricts users from editing status values on the table
  table->setColumnReadOnly (5, true);
}

void MetabolitesWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CMetab* pMetab = (const CMetab*)obj;

  //1: name
  table->setText(row, 1, FROM_UTF8(pMetab->getObjectName()));

  //2,3: Concentrations, Numbers
  if (mFlagConc)
    {
      table->setText(row, 2, QString::number(pMetab->getInitialConcentration()));
      table->setText(row, 3, QString::number(pMetab->getConcentration()));
    }
  else
    {
      table->setText(row, 2, QString::number(pMetab->getInitialNumber()));
      table->setText(row, 3, QString::number(pMetab->getNumber()));
    }

  //4: Fixed
  QCheckTableItem * fixedCB;
  fixedCB = new QCheckTableItem(table, "");
  if (CMetab::StatusName[pMetab->getStatus()] == "fixed") // not working?
    fixedCB->setChecked(true);
  table->setItem(row, 4, fixedCB);

  //5: Status
  table->setText(row, 5, FROM_UTF8(CMetab::StatusName[pMetab->getStatus()]));

  //6: Compartment
  QStringList compartmentType;
  const CCopasiVector < CCompartment > & compartments = dataModel->getModel()->getCompartments();
  for (unsigned C_INT32 jj = 0; jj < compartments.size(); jj++)
    compartmentType.push_back(FROM_UTF8(compartments[jj]->getObjectName()));
  QComboTableItem * item = new QComboTableItem(table, compartmentType, false);
  table->setItem(row, 6, item);
  item->setCurrentItem(FROM_UTF8(pMetab->getCompartment()->getObjectName()));
}

void MetabolitesWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CMetab* pMetab = (CMetab*)obj;

  //2: for Initial Concentration and Initial Number
  if (mFlagConc)
    pMetab->setInitialConcentration(table->text(row, 2).toDouble());
  else
    pMetab->setInitialNumber(table->text(row, 2).toDouble());

  //fixed? //TODO
  /*QString status(table->text(row, 5));
  if ((const char *)status.utf8() != CMetab::StatusName[obj->getStatus()])
    {
      if (obj->getStatus() != CMetab::METAB_FIXED)
        obj->setStatus(CMetab::METAB_FIXED);
      else
        obj->setStatus(CMetab::METAB_VARIABLE);

      changed[j] = 1;
    }*/

  //6: compartment
  QString Compartment(table->text(row, 6));
  if ((const char *)Compartment.utf8() != pMetab->getCompartment()->getObjectName())
    {
      unsigned C_INT32 index = dataModel->getModel()->
                               getCompartments().getIndex((const char *)Compartment.utf8());
      if (index != C_INVALID_INDEX)
        {
          dataModel->getModel()->
          getCompartments()[(const char *)Compartment.utf8()]->addMetabolite(*pMetab);
          dataModel->getModel()->
          getCompartments()[pMetab->getCompartment()->getObjectName()]->
          getMetabolites().remove(pMetab->getObjectName());
          dataModel->getModel()->initializeMetabolites();
          ListViews::notify(ListViews::COMPARTMENT,
                            ListViews::CHANGE, "");
        }
    } //TODO check if changing the compartment of a metabolite really works
}

void MetabolitesWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  //2,3: Concentrations, Numbers
  if (exc != 2)
    {
      if (mFlagConc)
        {
          table->setText(row, 2, QString::number(1.0));
          table->setText(row, 3, "");
        }
      else
        {
          table->setText(row, 2, QString::number(1.0));
          table->setText(row, 3, "");
        }
    }
  //4: Fixed
  if (exc != 4)
    {
      QCheckTableItem * fixedCB;
      fixedCB = new QCheckTableItem(table, "");
      fixedCB->setChecked(false);
      table->setItem(row, 4, fixedCB);
    }
  //5: Status
  table->setText(row, 5, "");

  //6: Compartment
  if (exc != 6)
    {
      QStringList compartmentType;
      const CCopasiVector < CCompartment > & compartments = dataModel->getModel()->getCompartments();
      if (compartments.size())
        {
          for (unsigned C_INT32 jj = 0; jj < compartments.size(); jj++)
            compartmentType.push_back(FROM_UTF8(compartments[jj]->getObjectName()));
          QComboTableItem * item = new QComboTableItem(table, compartmentType, false);
          table->setItem(row, 6, item);
          item->setCurrentItem(FROM_UTF8(compartments[0]->getObjectName()));
        }
    }
}

QString MetabolitesWidget::defaultObjectName() const
  {
    return "metabolite";
  }

CCopasiObject* MetabolitesWidget::createNewObject(const std::string & name)
{
  if (dataModel->getModel()->getCompartments().size() == 0)
    dataModel->getModel()->createCompartment("compartment");

  std::string nname = name;
  int i = 0;
  CMetab* pMetab;
  while (!(pMetab = dataModel->getModel()->createMetabolite(nname, "", 1.0, CMetab::METAB_VARIABLE)))
    {
      i++;
      nname = name;
      nname += (const char *)QString::number(i).utf8();
    }
  std::cout << " *** created Metabolite: " << nname << " : " << pMetab->getKey() << std::endl;
  return pMetab;
}

void MetabolitesWidget::deleteObjects(const std::vector<std::string> & keys)
{
  if (!dataModel->getModel())
    return;

  if (keys.size() == 0)
    return;

  QString metabList = "Are you sure you want to delete listed METABOLITE(S) ?\n";
  QString effectedReacList = "Following REACTION(S) reference above METABOLITE(S) and will be deleted -\n";
  int reacFound = 0;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++)
    {
      metabList.append(FROM_UTF8(GlobalKeys.get(keys[i])->getObjectName()));
      metabList.append(", ");

      //CMetab* metab =
      //  dynamic_cast< CMetab *>(GlobalKeys.get(keys[i]));

      std::set<std::string> effectedReacKeys = dataModel->getModel()->listReactionsDependentOnMetab(keys[i]);

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
          effectedReacList.append(FROM_UTF8(GlobalKeys.get(keys[i])->getObjectName()));
          effectedReacList.append("\n");
        }
    }

  metabList.remove(metabList.length() - 2, 2);

  QString msg = metabList;
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
    case 0:               // Yes or Enter
      {
        for (i = 0; i < imax; i++)
          {
            dataModel->getModel()->removeMetabolite(keys[i]);
          }

        for (i = 0; i < imax; i++)
          ListViews::notify(ListViews::METABOLITE, ListViews::DELETE, keys[i]);
        //TODO notify about reactions
        break;
      }
    case 1:               // No or Escape
      break;
    }
}

void MetabolitesWidget::slotBtnToggleClicked()
{
  C_INT32 choice;
  if (btnOK->isEnabled())
    choice = QMessageBox::question(this,
                                   "Toggle View",
                                   "There are changes in the table. Do you want to commit the changes or revert to the original values?",
                                   "Commit", "Revert", "Cancel", 0, 2);
  else
    choice = 0;

  if (choice == 2) return; //cancel

  if (choice == 0) saveTable(); //commit

  QHeader *tableHeader = table->horizontalHeader();

  if (mFlagConc)
    {
      tableHeader->setLabel(2, "Initial Number");
      tableHeader->setLabel(3, "Number");
      btnToggle->setText("&Show Concentrations");
      mFlagConc = false;
    }
  else
    {
      tableHeader->setLabel(2, "Initial Concentration");
      tableHeader->setLabel(3, "Concentration");
      btnToggle->setText("&Show Numbers");
      mFlagConc = true;
    }

  fillTable();
}
