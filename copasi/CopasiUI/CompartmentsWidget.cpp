/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CompartmentsWidget.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:44 $
   End CVS Header */

/*******************************************************************
 **  $ CopasiUI/CompartmentsWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the 
 ** Compartments----It is Basically the First level of Compartments
 ********************************************************************/
#include "CompartmentsWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>

#include "MyTable.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"
#include "DataModelGUI.h"

std::vector<const CCopasiObject*> CompartmentsWidget::getObjects() const
  {
    CCopasiVectorN<CCompartment>& tmp = dataModel->getModel()->getCompartments();
    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(tmp[i]);

    return ret;
  }

void CompartmentsWidget::init()
{
  mOT = ListViews::COMPARTMENT;
  numCols = 3;
  table->setNumCols(numCols);
  //table->QTable::setNumRows(1);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Volume");
}

void CompartmentsWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  const CCompartment* pComp = (const CCompartment*)obj;
  table->setText(row, 1, FROM_UTF8(pComp->getObjectName()));
  table->setText(row, 2, QString::number(pComp->getVolume()));
}

void CompartmentsWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CCompartment* pComp = (CCompartment*)obj;
  pComp->setInitialVolume(table->text(row, 2).toDouble());
}

void CompartmentsWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != 2)
    table->setText(row, 2, QString::number(1.0));
}

QString CompartmentsWidget::defaultObjectName() const
  {
    return "compartment";
  }

//specific
/*void CompartmentsWidget::createNewObject()
{
  std::string name = "compartment_0";
  int i = 0;
  while (!dataModel->getModel()->createCompartment(name))
    {
      i++;
      name = "compartment_";
      name += (const char *)QString::number(i).utf8();
    }
  table->setText(table->numRows() - 1, 1, FROM_UTF8(name));
  table->setNumRows(table->numRows());
  ListViews::notify(ListViews::COMPARTMENT, ListViews::ADD);
}*/

CCopasiObject* CompartmentsWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CCompartment* pCom;
  while (!(pCom = dataModel->getModel()->createCompartment(nname)))
    {
      i++;
      nname = name;
      nname += (const char *)QString::number(i).utf8();
    }
  std::cout << " *** created Compartment: " << nname << " : " << pCom->getKey() << std::endl;
  return pCom;
}

void CompartmentsWidget::deleteObjects(const std::vector<std::string> & keys)
{
  if (!dataModel->getModel())
    return;

  if (keys.size() == 0)
    return;

  QString compartmentList = "Are you sure you want to delete listed COMPARTMENT(S) ?\n";
  QString effectedMetabList = "Following METABOLITE(S) reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above METABOLITE(S) and will be deleted -\n";
  int metabFound = 0;
  int reacFound = 0;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++) //all compartments
    {
      compartmentList.append(FROM_UTF8(GlobalKeys.get(keys[i])->getObjectName()));
      compartmentList.append(", ");

      CCompartment* comp =
        dynamic_cast< CCompartment *>(GlobalKeys.get(keys[i]));

      const CCopasiVectorNS < CMetab > & Metabs = comp->getMetabolites();
      unsigned C_INT32 noOfMetabs = Metabs.size();

      if (noOfMetabs > 0)
        {
          metabFound = 1;
          unsigned C_INT32 k;
          for (k = 0; k < noOfMetabs; k++)
            {
              effectedMetabList.append(FROM_UTF8(Metabs[k]->getObjectName()));
              effectedMetabList.append(", ");
            }

          effectedMetabList.remove(effectedMetabList.length() - 2, 2);
          effectedMetabList.append("  ---> ");
          effectedMetabList.append(FROM_UTF8(comp->getObjectName()));
          effectedMetabList.append("\n");

          std::set<std::string> effectedReacKeys = dataModel->getModel()->listReactionsDependentOnCompartment(keys[i]);
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
              effectedReacList.append(FROM_UTF8(comp->getObjectName()));
              effectedReacList.append("\n");
            }
        }
    }

  compartmentList.remove(compartmentList.length() - 2, 2);

  QString msg = compartmentList;
  if (metabFound == 1)
    {
      msg.append("\n \n");
      msg.append(effectedMetabList);
      if (reacFound == 1)
        {
          msg.append("\n \n");
          msg.append(effectedReacList);
        }
    }

  C_INT32 choice;
  if (metabFound == 1)
    choice = QMessageBox::warning(this,
                                  "CONFIRM DELETE",
                                  msg,
                                  "Continue", "Cancel", 0, 0, 1);
  else
    choice = 0;

  switch (choice)
    {
    case 0:                // Yes or Enter
      {
        for (i = 0; i < imax; i++)
          {
            dataModel->getModel()->removeCompartment(keys[i]);
          }

        for (i = 0; i < imax; i++)
          ListViews::notify(ListViews::COMPARTMENT, ListViews::DELETE, keys[i]);
        //TODO notify about metabs and reactions
        break;
      }
    case 1:                // No or Escape
      break;
    }
}
