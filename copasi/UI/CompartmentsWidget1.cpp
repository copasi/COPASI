/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CompartmentsWidget1.cpp,v $
   $Revision: 1.72 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/10/08 08:50:31 $
   End CVS Header */

/*******************************************************************
 **  $ CopasiUI/CompartmentsWidget1.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the individual
 ** Compartments----It is the second level of Compartments
 ********************************************************************/
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include <qlistbox.h>
#include <qvalidator.h>
#include <qmessagebox.h>
#include "copasi.h"
#include "utilities/CCopasiVector.h"
#include "CompartmentsWidget1.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"
#include "DataModelGUI.h"

/*
 *  Constructs a CompartmentsWidget1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
CompartmentsWidget1::CompartmentsWidget1(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    objKey("")
{
  if (!name)
    setName("CompartmentsWidget1");
  setCaption(trUtf8("CompartmentsWidget1"));
  CompartmentsWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "CompartmentsWidget1Layout");

  LineEdit4 = new QLineEdit(this, "LineEdit4");
  LineEdit4->setEnabled(FALSE);
  LineEdit4->setReadOnly(TRUE);
  CompartmentsWidget1Layout->addWidget(LineEdit4, 3, 1);

  LineEdit1 = new QLineEdit(this, "LineEdit1");
  CompartmentsWidget1Layout->addWidget(LineEdit1, 0, 1);

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Initial  Volume"));
  CompartmentsWidget1Layout->addWidget(TextLabel2, 2, 0);

  TextLabel2_2 = new QLabel(this, "TextLabel2_2");
  TextLabel2_2->setText(trUtf8("Transient Volume"));
  CompartmentsWidget1Layout->addWidget(TextLabel2_2, 3, 0);

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Compartment Name"));
  CompartmentsWidget1Layout->addWidget(TextLabel1, 0, 0);

  Line4 = new QFrame(this, "Line4");
  CompartmentsWidget1Layout->addMultiCellWidget(Line4, 1, 1, 0, 1);

  Line4_2 = new QFrame(this, "Line4_2");
  CompartmentsWidget1Layout->addMultiCellWidget(Line4_2, 4, 4, 0, 1);

  ListBox1 = new QListBox(this, "ListBox1");

  CompartmentsWidget1Layout->addMultiCellWidget(ListBox1, 5, 6, 1, 1);
  QSpacerItem* spacer = new QSpacerItem(131, 270, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CompartmentsWidget1Layout->addItem(spacer, 6, 0);

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Metabolite Name"));
  CompartmentsWidget1Layout->addWidget(TextLabel3, 5, 0);

  LineEdit3 = new QLineEdit(this, "LineEdit3");
  LineEdit3->setValidator(new QDoubleValidator(LineEdit3));
  CompartmentsWidget1Layout->addWidget(LineEdit3, 2, 1);

  Layout5 = new QHBoxLayout(0, 0, 6, "Layout5");

  commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit"));
  Layout5->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Revert"));
  Layout5->addWidget(cancelChanges);

  newCompartmentBtn = new QPushButton(this, "newCompartmentBtn");
  newCompartmentBtn->setText(trUtf8("New"));
  Layout5->addWidget(newCompartmentBtn);

  deleteCompartmentBtn = new QPushButton(this, "deleteCompartmentBtn");
  deleteCompartmentBtn->setText(trUtf8("Delete"));
  Layout5->addWidget(deleteCompartmentBtn);
  CompartmentsWidget1Layout->addMultiCellLayout(Layout5, 8, 8, 0, 1);

  Line4_3 = new QFrame(this, "Line4_3");
  CompartmentsWidget1Layout->addMultiCellWidget(Line4_3, 7, 7, 0, 1);

  setTabOrder(LineEdit1, LineEdit3);
  setTabOrder(LineEdit3, LineEdit4);
  setTabOrder(LineEdit4, ListBox1);
  setTabOrder(ListBox1, commitChanges);
  setTabOrder(commitChanges, cancelChanges);
  setTabOrder(cancelChanges, newCompartmentBtn);
  setTabOrder(newCompartmentBtn, deleteCompartmentBtn);

  // signals and slots connections
  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
  connect(newCompartmentBtn, SIGNAL(clicked()), this, SLOT(slotBtnNewClicked()));
  connect(deleteCompartmentBtn, SIGNAL(clicked()), this, SLOT(slotBtnDeleteClicked()));
  connect(ListBox1, SIGNAL(selected(const QString&)), this, SLOT(slotListBoxCurrentChanged(const QString&)));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CompartmentsWidget1::~CompartmentsWidget1()
{}

/* This function loads the compartments widget when its name is
  clicked in the tree   */
bool CompartmentsWidget1::loadFromCompartment(const CCompartment * compartn)
{
  if (!compartn) return false;

  LineEdit1->setText(FROM_UTF8(compartn->getObjectName()));

  const CCopasiVectorNS < CMetab > & Metabs = compartn->getMetabolites();
  C_INT32 noOfMetabolitesRows = Metabs.size();
  const CMetab *mtb;
  ListBox1->setAutoScrollBar(true);
  ListBox1->clear();
  C_INT32 j;
  for (j = 0; j < noOfMetabolitesRows; j++)
    {
      mtb = Metabs[j];
      ListBox1->insertItem(FROM_UTF8(mtb->getObjectName()));
    }

  volumeSave = QString::number(compartn->getInitialVolume());
  LineEdit3->setText(volumeSave);

  LineEdit4->setText(QString::number(compartn->getVolume()));
  LineEdit4->setReadOnly(true);

  return true;
}

bool CompartmentsWidget1::saveToCompartment()
{
  CCompartment* comp = dynamic_cast< CCompartment * >(GlobalKeys.get(objKey));
  if (!comp) return false;

  //name
  QString name(LineEdit1->text());
  if ((const char *)name.utf8() != comp->getObjectName())
    {
      comp->setName((const char *)name.utf8());
      protectedNotify(ListViews::COMPARTMENT, ListViews::RENAME, objKey);
    }

  //volume
  QString volume(LineEdit3->text());
  if (volume != volumeSave)
    {
      double m1;
      m1 = volume.toDouble();
      comp->setInitialVolume(m1);
      protectedNotify(ListViews::COMPARTMENT, ListViews::CHANGE, objKey);
    }
  return true;
}

void CompartmentsWidget1::slotBtnCancelClicked()
{
  enter(objKey); // reload
}

void CompartmentsWidget1::slotBtnOKClicked()
{
  saveToCompartment();
}

void CompartmentsWidget1::slotBtnNewClicked()
{
  std::string name = "compartment_0";
  int i = 0;
  CCompartment* pCom;
  while (!(pCom = dataModel->getModel()->createCompartment(name)))
    {
      i++;
      name = "compartment_";
      name += (const char *)QString::number(i).utf8();
    }
  protectedNotify(ListViews::COMPARTMENT, ListViews::ADD);
  enter(pCom->getKey());
}

void CompartmentsWidget1::slotBtnDeleteClicked()
{
  if (!dataModel->getModel())
    return;

  CCompartment* comp = dynamic_cast< CCompartment *>(GlobalKeys.get(objKey));

  QString compartmentList = "Are you sure you want to delete listed COMPARTMENT?\n";
  QString effectedMetabList = "Following METABOLITE(S) reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above METABOLITE(S) and will be deleted -\n";
  int metabFound = 0;
  int reacFound = 0;

  //unsigned C_INT32 i, imax = keys.size();
  //for (i = 0; i < imax; i++) //all compartments
  //{
  compartmentList.append(FROM_UTF8(comp->getObjectName()));
  compartmentList.append(", ");

  //CCompartment* comp = dynamic_cast< CCompartment *>(GlobalKeys.get(keys[i]));

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

      std::set<std::string> effectedReacKeys = dataModel->getModel()->listReactionsDependentOnCompartment(objKey);
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
  //}

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
    case 0:                      // Yes or Enter
      {
        unsigned C_INT32 size = dataModel->getModel()->getCompartments().size();
        unsigned C_INT32 index = dataModel->getModel()->getCompartments().getIndex(comp->getObjectName());
        /*for (i = 0; i < imax; i++)
          {
            dataModel->getModel()->removeCompartment(keys[i]);
          }*/
        dataModel->getModel()->removeCompartment(objKey);
        //for (i = 0; i < imax; i++)
        enter(dataModel->getModel()->getCompartments()[std::min(index, size - 2)]->getKey());
        protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, objKey);
        //TODO notify about metabs and reactions
        break;
      }
    case 1:                      // No or Escape
      break;
    }
}

void CompartmentsWidget1::slotListBoxCurrentChanged(const QString & C_UNUSED(m))
{
  //TODO do not really know what to do here. May be switch to metabolite widget?
}

bool CompartmentsWidget1::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
      return loadFromCompartment(dynamic_cast< CCompartment * >(GlobalKeys.get(objKey)));
      break;

    default:
      break;
    }
  return true;
}

bool CompartmentsWidget1::leave()
{
  return saveToCompartment();
}

bool CompartmentsWidget1::enter(const std::string & key)
{
  objKey = key;
  CCompartment* comp = dynamic_cast< CCompartment * >(GlobalKeys.get(key));

  if (comp) return loadFromCompartment(comp);
  else return false;
}
