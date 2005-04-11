/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MetabolitesWidget.cpp,v $
   $Revision: 1.117 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/11 20:45:07 $
   End CVS Header */

#include "MetabolitesWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>

//#include "MyTable.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "listviews.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"

std::vector<const CCopasiObject*> MetabolitesWidget::getObjects() const
  {
    CCopasiVector<CMetab>& tmp = CCopasiDataModel::Global->getModel()->getMetabolites();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void MetabolitesWidget::init()
{
  mOT = ListViews::METABOLITE;
  mFlagConc = true;
  mExtraLayout->addStretch();
  btnToggle = new QPushButton("&Show Numbers", this);
  mExtraLayout->addWidget(btnToggle);
  connect(btnToggle, SIGNAL(clicked ()), this,
          SLOT(slotBtnToggleClicked()));

  numCols = 8;
  table->setNumCols(numCols);
  //table->QTable::setNumRows(1);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Initial Concentration");
  tableHeader->setLabel(3, "Concentration");
  tableHeader->setLabel(4, "Fixed");
  table->setColumnWidth(4, 40);
  tableHeader->setLabel(5, "Status");
  tableHeader->setLabel(6, "Compartment");
  tableHeader->setLabel(7, "Rate");

  //this restricts users from editing concentration values on the table
  table->setColumnReadOnly (3, true);
  //this restricts users from editing status values on the table
  table->setColumnReadOnly (5, true);
  table->setColumnReadOnly (7, true);
}

void MetabolitesWidget::showHeaders()
{
  /* <-- to show the units for the quantities */

  QHeader *tableHeader = table->horizontalHeader();
  if (mFlagConc)
    {
      tableHeader->setLabel(2, "Initial Concentration\n(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getQuantityUnit()) + "/" + \
                            FROM_UTF8(CCopasiDataModel::Global->getModel()->getVolumeUnit()) + ")");
      tableHeader->setLabel(3, "Concentration\n(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getQuantityUnit()) + "/" + \
                            FROM_UTF8(CCopasiDataModel::Global->getModel()->getVolumeUnit()) + ")");

      tableHeader->setLabel(7, "Rate\n(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getQuantityUnit()) + \
                            "/(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getVolumeUnit()) + "*" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnit()) + "))");
    }
  else
    {
      tableHeader->setLabel(2, "Initial Number");
      tableHeader->setLabel(3, "Number");
      tableHeader->setLabel(7, "Number rate");
    }

  /* --> */
}

void MetabolitesWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CMetab* pMetab = (const CMetab*)obj;
  showHeaders();

  //1: name

  table->setText(row, 1, FROM_UTF8(pMetab->getObjectName()));

  //2,3,7: Concentrations, Numbers

  if (mFlagConc)
    {
      table->setText(row, 2, QString::number(pMetab->getInitialConcentration()));
      table->setText(row, 3, QString::number(pMetab->getConcentration()));

      table->setText(row, 7, QString::number(pMetab->getConcentrationRate()));
    }
  else
    {
      table->setText(row, 2, QString::number(pMetab->getInitialNumber()));
      table->setText(row, 3, QString::number(pMetab->getNumber()));

      table->setText(row, 7, QString::number(pMetab->getNumberRate()));
    }

  //4: Fixed
  QCheckTableItem * fixedCB;
  fixedCB = new QCheckTableItem(table, "");
  if (pMetab->getStatus() == CMetab::METAB_FIXED)
    fixedCB->setChecked(true);
  table->setItem(row, 4, fixedCB);

  //5: Status
  table->setText(row, 5, FROM_UTF8(CMetab::StatusName[pMetab->getStatus()]));

  //6: Compartment
  QStringList compartmentType;
  const CCopasiVector < CCompartment > & compartments = CCopasiDataModel::Global->getModel()->getCompartments();
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
  bool fixed = ((QCheckTableItem*)(table->item(row, 4)))->isChecked();
  if (fixed)
    {
      if (pMetab->getStatus() != CMetab::METAB_FIXED)
        {
          pMetab->setStatus(CMetab::METAB_FIXED);
          CCopasiDataModel::Global->getModel()->setCompileFlag();
        }
    }
  else
    {
      if (pMetab->getStatus() == CMetab::METAB_FIXED)
        {
          pMetab->setStatus(CMetab::METAB_VARIABLE);
          CCopasiDataModel::Global->getModel()->setCompileFlag();
        }
    }

  //6: compartment
  QString Compartment(table->text(row, 6));
  if (((const char *)Compartment.utf8() != pMetab->getCompartment()->getObjectName()) //has changed
      && (Compartment != ""))
    {
      std::string CompartmentToRemove = pMetab->getCompartment()->getObjectName();
      if (!CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)Compartment.utf8()]->addMetabolite(pMetab))
        {
          QString msg;
          msg = "Unable to move metabolite '" + FROM_UTF8(pMetab->getObjectName()) + "'\n"
                + "from compartment '" + FROM_UTF8(CompartmentToRemove) + "' to compartment '" + Compartment + "'\n"
                + "since a metabolite with that name already exist in the target compartment.";

          QMessageBox::warning(this,
                               "Unable to move Metabolite",
                               msg,
                               QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);

          return;
        }
      CCopasiDataModel::Global->getModel()->getCompartments()[CompartmentToRemove]->getMetabolites().remove(pMetab->getObjectName());
      CCopasiDataModel::Global->getModel()->setCompileFlag();
      CCopasiDataModel::Global->getModel()->initializeMetabolites();
      //protectedNotify(ListViews::MODEL, ListViews::CHANGE, "");
      ListViews::notify(ListViews::METABOLITE, ListViews::CHANGE, "");
      ListViews::notify(ListViews::COMPARTMENT, ListViews::CHANGE, "");

      /*unsigned C_INT32 index = CCopasiDataModel::Global->getModel()->
                               getCompartments().getIndex((const char *)Compartment.utf8());
      if (index != C_INVALID_INDEX)
        {
          CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)Compartment.utf8()]->addMetabolite(pMetab);
          CCopasiDataModel::Global->getModel()->
          getCompartments()[pMetab->getCompartment()->getObjectName()]->
          getMetabolites().remove(pMetab->getObjectName());
          CCopasiDataModel::Global->getModel()->initializeMetabolites();
          ListViews::notify(ListViews::COMPARTMENT,
                            ListViews::CHANGE, "");
        }*/
    } //TODO check if changing the compartment of a metabolite really works. NO!!!

  //CCopasiDataModel::Global->getModel()->setCompileFlag();
}

void MetabolitesWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  //2,3,7: Concentrations, Numbers
  if (exc != 2)
    {
      if (mFlagConc)
        {
          table->setText(row, 2, QString::number(1.0));
          table->setText(row, 3, "");
        }
      else
        {
          table->setText(row, 2, QString::number(100.0));
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
      const CCopasiVector < CCompartment > & compartments = CCopasiDataModel::Global->getModel()->getCompartments();
      if (true /*compartments.size()*/)
        {
          for (unsigned C_INT32 jj = 0; jj < compartments.size(); jj++)
            compartmentType.push_back(FROM_UTF8(compartments[jj]->getObjectName()));
          QComboTableItem * item = new QComboTableItem(table, compartmentType, false);
          table->setItem(row, 6, item);
          if (compartments.size()) item->setCurrentItem(FROM_UTF8(compartments[0]->getObjectName()));
        }
    }

  //7: Rate
  table->setText(row, 7, "");
}

QString MetabolitesWidget::defaultObjectName() const
  {
    return "metabolite";
  }

CCopasiObject* MetabolitesWidget::createNewObject(const std::string & name)
{
  if (CCopasiDataModel::Global->getModel()->getCompartments().size() == 0)
    CCopasiDataModel::Global->getModel()->createCompartment("compartment");

  std::string nname = name;
  int i = 0;
  CMetab* pMetab;
  while (!(pMetab = CCopasiDataModel::Global->getModel()->createMetabolite(nname, "", 1.0, CMetab::METAB_VARIABLE)))
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
  if (!CCopasiDataModel::Global->getModel())
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

      std::set<std::string> effectedReacKeys = CCopasiDataModel::Global->getModel()->listReactionsDependentOnMetab(keys[i]);

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
    case 0:                                     // Yes or Enter
      {
        for (i = 0; i < imax; i++)
          {
            CCopasiDataModel::Global->getModel()->removeMetabolite(keys[i]);
          }

        for (i = 0; i < imax; i++)
          ListViews::notify(ListViews::METABOLITE, ListViews::DELETE, keys[i]);
        //TODO notify about reactions
        break;
      }
    case 1:                                     // No or Escape
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
      tableHeader->setLabel(7, "Number rate");
      btnToggle->setText("&Show Concentrations");
      mFlagConc = false;
    }
  else
    {
      tableHeader->setLabel(2, "Initial Concentration");
      tableHeader->setLabel(3, "Concentration");
      tableHeader->setLabel(7, "Concentration rate");
      btnToggle->setText("&Show Numbers");
      mFlagConc = true;
    }

  fillTable();
}
