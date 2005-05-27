/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MetabolitesWidget.cpp,v $
   $Revision: 1.121 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/05/27 16:10:47 $
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

#define COL_MARK               0
#define COL_NAME               1
#define COL_ICONCENTRATION     2
#define COL_INUMBER            3
#define COL_CONCENTRATION      4
#define COL_NUMBER             5
#define COL_FIXED              6
#define COL_STATUS             7
#define COL_COMPARTMENT        8
#define COL_OLDCOMPARTMENT     9
#define COL_CRATE             10
#define COL_NRATE             11

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
  mExtraLayout->addStretch();
  btnToggle = new QPushButton("&Show Numbers", this);
  mExtraLayout->addWidget(btnToggle);
  connect(btnToggle, SIGNAL(clicked ()), this,
          SLOT(slotBtnToggleClicked()));

  numCols = 12;
  table->setNumCols(numCols);
  //table->QTable::setNumRows(1);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(COL_MARK, "Status");

  tableHeader->setLabel(COL_NAME, "Name");

  tableHeader->setLabel(COL_ICONCENTRATION, "Initial Concentration\n(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getQuantityUnit()) + "/" + \
                        FROM_UTF8(CCopasiDataModel::Global->getModel()->getVolumeUnit()) + ")");

  tableHeader->setLabel(COL_INUMBER, "Initial Number");

  tableHeader->setLabel(COL_CONCENTRATION, "Concentration\n(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getQuantityUnit()) + "/" + \
                        FROM_UTF8(CCopasiDataModel::Global->getModel()->getVolumeUnit()) + ")");
  table->setColumnReadOnly (COL_CONCENTRATION, true);

  tableHeader->setLabel(COL_NUMBER, "Number");

  table->setColumnReadOnly (COL_NUMBER, true);

  tableHeader->setLabel(COL_FIXED, "Fixed");
  table->setColumnWidth(COL_FIXED, 40);

  tableHeader->setLabel(COL_STATUS, "Status");
  table->setColumnReadOnly (COL_STATUS, true);

  tableHeader->setLabel(COL_COMPARTMENT, "Compartment");

  tableHeader->setLabel(COL_OLDCOMPARTMENT, "Old Compartment");
  table->setColumnReadOnly (COL_OLDCOMPARTMENT, true);
  table->hideColumn(COL_OLDCOMPARTMENT);

  tableHeader->setLabel(COL_CRATE, "Rate\n(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getQuantityUnit()) + \
                        "/(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getVolumeUnit()) + "*" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnit()) + "))");
  table->setColumnReadOnly (COL_CRATE, true);

  tableHeader->setLabel(COL_NRATE, "Number Rate");
  table->setColumnReadOnly (COL_NRATE, true);

  // We start with the concentration showing.
  mFlagConc = true;
  table->hideColumn(COL_INUMBER);
  table->hideColumn(COL_NUMBER);
  table->hideColumn(COL_NRATE);
}

void MetabolitesWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CMetab* pMetab = static_cast<const CMetab *>(obj);

  //1: name

  table->setText(row, COL_NAME, FROM_UTF8(pMetab->getObjectName()));

  table->setText(row, COL_ICONCENTRATION, QString::number(pMetab->getInitialConcentration()));

  table->setText(row, COL_INUMBER, QString::number(pMetab->getInitialNumber()));

  table->setText(row, COL_CONCENTRATION, QString::number(pMetab->getConcentration()));
  table->setText(row, COL_NUMBER, QString::number(pMetab->getNumber()));

  //4: Fixed
  QCheckTableItem * fixedCB;
  fixedCB = new QCheckTableItem(table, "");
  if (pMetab->getStatus() == CModelEntity::FIXED)
    fixedCB->setChecked(true);
  table->setItem(row, COL_FIXED, fixedCB);

  //5: Status
  table->setText(row, COL_STATUS, FROM_UTF8(CMetab::StatusName[pMetab->getStatus()]));

  //6: Compartment
  QStringList compartmentType;
  const CCopasiVector < CCompartment > & compartments = CCopasiDataModel::Global->getModel()->getCompartments();
  for (unsigned C_INT32 jj = 0; jj < compartments.size(); jj++)
    compartmentType.push_back(FROM_UTF8(compartments[jj]->getObjectName()));
  QComboTableItem * item = new QComboTableItem(table, compartmentType, false);
  table->setItem(row, COL_COMPARTMENT, item);
  item->setCurrentItem(FROM_UTF8(pMetab->getCompartment()->getObjectName()));
  table->setText(row, COL_OLDCOMPARTMENT,
                 FROM_UTF8(pMetab->getCompartment()->getObjectName()));

  table->setText(row, COL_CRATE, QString::number(pMetab->getConcentrationRate()));
  table->setText(row, COL_NRATE, QString::number(pMetab->getNumberRate()));
}

void MetabolitesWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CMetab* pMetab = static_cast<CMetab *>(obj);

  //6: compartment
  // This must be set first for setInitialConcentration and
  // setInitialNumber to work correctly.
  QString Compartment(table->text(row, COL_COMPARTMENT));
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
        }
      else
        {
          CCopasiDataModel::Global->getModel()->getCompartments()[CompartmentToRemove]->getMetabolites().remove(pMetab->getObjectName());
          CCopasiDataModel::Global->getModel()->setCompileFlag();
          CCopasiDataModel::Global->getModel()->initializeMetabolites();
          //protectedNotify(ListViews::MODEL, ListViews::CHANGE, "");
          ListViews::notify(ListViews::METABOLITE, ListViews::CHANGE, "");
          ListViews::notify(ListViews::COMPARTMENT, ListViews::CHANGE, "");
        }
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

  //2: for Initial Concentration and Initial Number
  if (mFlagConc)
    pMetab->setInitialConcentration(table->text(row, COL_ICONCENTRATION).toDouble());
  else
    pMetab->setInitialNumber(table->text(row, COL_INUMBER).toDouble());

  //fixed? //TODO
  bool fixed = ((QCheckTableItem*)(table->item(row, COL_FIXED)))->isChecked();
  if (fixed)
    {
      if (pMetab->getStatus() != CModelEntity::FIXED)
        {
          pMetab->setStatus(CModelEntity::FIXED);
          CCopasiDataModel::Global->getModel()->setCompileFlag();
        }
    }
  else
    {
      if (pMetab->getStatus() == CModelEntity::FIXED)
        {
          pMetab->setStatus(CModelEntity::REACTIONS);
          CCopasiDataModel::Global->getModel()->setCompileFlag();
        }
    }

  //CCopasiDataModel::Global->getModel()->setCompileFlag();
}

void MetabolitesWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != COL_ICONCENTRATION)
    table->setText(row, COL_ICONCENTRATION, QString::number(1.0));
  if (exc != COL_INUMBER)
    table->setText(row, COL_INUMBER, QString::number(100.0));
  if (exc != COL_CONCENTRATION)
    table->setText(row, COL_CONCENTRATION, "");
  if (exc != COL_NUMBER)
    table->setText(row, COL_NUMBER, "");
  if (exc != COL_FIXED)
    {
      QCheckTableItem * fixedCB;
      fixedCB = new QCheckTableItem(table, "");
      fixedCB->setChecked(false);
      table->setItem(row, COL_FIXED, fixedCB);
    }
  if (exc != COL_STATUS)
    table->setText(row, COL_STATUS, "");
  if (exc != COL_COMPARTMENT)
    {
      QStringList compartmentType;
      const CCopasiVector < CCompartment > & compartments = CCopasiDataModel::Global->getModel()->getCompartments();
      if (true /*compartments.size()*/)
        {
          for (unsigned C_INT32 jj = 0; jj < compartments.size(); jj++)
            compartmentType.push_back(FROM_UTF8(compartments[jj]->getObjectName()));
          QComboTableItem * item = new QComboTableItem(table, compartmentType, false);
          table->setItem(row, COL_COMPARTMENT, item);
          if (compartments.size()) item->setCurrentItem(FROM_UTF8(compartments[0]->getObjectName()));
        }
    }
  if (exc != COL_CRATE)
    table->setText(row, COL_CRATE, "");
  if (exc != COL_NRATE)
    table->setText(row, COL_NRATE, "");
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
  while (!(pMetab = CCopasiDataModel::Global->getModel()->createMetabolite(nname, "", 1.0, CModelEntity::REACTIONS)))
    {
      i++;
      nname = name + "_";
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
    case 0:                                         // Yes or Enter
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
    case 1:                                         // No or Escape
      break;
    }
}

void MetabolitesWidget::slotBtnToggleClicked()
{
  QHeader *tableHeader = table->horizontalHeader();

  if (mFlagConc)
    {
      table->hideColumn(COL_ICONCENTRATION);
      table->hideColumn(COL_CONCENTRATION);
      table->hideColumn(COL_CRATE);

      table->showColumn(COL_INUMBER);
      table->showColumn(COL_NUMBER);
      table->showColumn(COL_NRATE);

      btnToggle->setText("&Show Concentrations");
      mFlagConc = false;
    }
  else
    {
      table->showColumn(COL_ICONCENTRATION);
      table->showColumn(COL_CONCENTRATION);
      table->showColumn(COL_CRATE);

      table->hideColumn(COL_INUMBER);
      table->hideColumn(COL_NUMBER);
      table->hideColumn(COL_NRATE);

      btnToggle->setText("&Show Numbers");
      mFlagConc = true;
    }

  //  fillTable();
}

void MetabolitesWidget::valueChanged(unsigned C_INT32 row, unsigned C_INT32 col)
{
  switch (col)
    {
    case COL_ICONCENTRATION:
      initialConcentrationChanged(row);
      break;

    case COL_INUMBER:
      initialNumberChanged(row);
      break;

    case COL_COMPARTMENT:
      compartmentChanged(row);
      break;

    default:
      break;
    }
  return;
}

void MetabolitesWidget::initialConcentrationChanged(unsigned C_INT32 row)
{
  const CMetab * pMetab
  = static_cast< CMetab * >(GlobalKeys.get(mKeys[row]));

  const CCompartment * pCompartment
  = CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)table->text(row, COL_OLDCOMPARTMENT).utf8()];

  if (!pMetab || !pCompartment) return;

  table->setText(row, COL_INUMBER,
                 QString::number(CMetab::convertToNumber(table->text(row, COL_ICONCENTRATION).toDouble(),
                                                         *pCompartment,
                                                         *CCopasiDataModel::Global->getModel())));
  return;
}

void MetabolitesWidget::initialNumberChanged(unsigned C_INT32 row)
{
  const CMetab * pMetab
  = static_cast< CMetab * >(GlobalKeys.get(mKeys[row]));

  const CCompartment * pCompartment
  = CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)table->text(row, COL_OLDCOMPARTMENT).utf8()];

  if (!pMetab || !pCompartment) return;

  table->setText(row, COL_ICONCENTRATION,
                 QString::number(CMetab::convertToNumber(table->text(row, COL_INUMBER).toDouble(),
                                                         *pCompartment,
                                                         *CCopasiDataModel::Global->getModel())));
  return;
}

void MetabolitesWidget::compartmentChanged(unsigned C_INT32 row)
{
  const CMetab * pMetab
  = static_cast< CMetab * >(GlobalKeys.get(mKeys[row]));

  const CCompartment * pCompartment
  = CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)table->text(row, COL_OLDCOMPARTMENT).utf8()];

  if (!pMetab || !pCompartment) return;

  C_FLOAT64 Factor = 1.0 / pCompartment->getInitialVolume();

  QString Compartment = table->text(row, COL_COMPARTMENT);
  table->setText(row, COL_OLDCOMPARTMENT, Compartment);

  pCompartment
  = CCopasiDataModel::Global->getModel()->getCompartments()[(const char *)Compartment.utf8()];
  Factor *= pCompartment->getInitialVolume();

  table->setText(row, COL_INUMBER,
                 QString::number(Factor * table->text(row, COL_INUMBER).toDouble()));
  table->setText(row, COL_NUMBER,
                 QString::number(Factor * table->text(row, COL_NUMBER).toDouble()));

  return;
}
