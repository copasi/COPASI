/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MetabolitesWidget1.cpp,v $
   $Revision: 1.88 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/24 11:46:27 $
   End CVS Header */

/*******************************************************************
 **  $ CopasiUI/MetaboliteWidget1.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the individual
 ** Metabolites----It is the second level of Metabolites
 ********************************************************************/
#include "mathematics.h"

#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>

#include "copasi.h"
#include "MetabolitesWidget1.h"
#include "model/CModel.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"

/*
 *  Constructs a MetabolitesWidget1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
MetabolitesWidget1::MetabolitesWidget1(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    objKey("")
{
  if (!name) setName("MetabolitesWidget1");
  setCaption(trUtf8("MetabolitesWidget1"));

  MetabolitesWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "MetabolitesWidget1Layout");

  mLblName = new QLabel(this, "mLblName");
  mLblName->setText(trUtf8("Metabolite Name"));
  MetabolitesWidget1Layout->addWidget(mLblName, 0, 0);

  mEditName = new QLineEdit(this, "mEditName");
  //  mEditName->setFrameShape(QLineEdit::LineEditPanel);
  //  mEditName->setFrameShadow(QLineEdit::Sunken);
  MetabolitesWidget1Layout->addMultiCellWidget(mEditName, 0, 0, 1, 3);

  mLblCompartment = new QLabel(this, "mLblCompartment");
  mLblCompartment->setText(trUtf8("Compartment Name"));
  MetabolitesWidget1Layout->addWidget(mLblCompartment, 1, 0);

  mComboCompartment = new QComboBox(FALSE, this, "mComboCompartment");
  MetabolitesWidget1Layout->addMultiCellWidget(mComboCompartment, 1, 1, 1, 3);

  Line1 = new QFrame(this, "Line1");
  Line1->setFrameShape(QFrame::HLine);
  Line1->setFrameShadow(QFrame::Sunken);
  Line1->setFrameShape(QFrame::HLine);
  MetabolitesWidget1Layout->addMultiCellWidget(Line1, 2, 2, 0, 3);

  mLblInitStatus = new QLabel(this, "mLblInitStatus");
  mLblInitStatus->setText(trUtf8("Metabolite status"));
  MetabolitesWidget1Layout->addWidget(mLblInitStatus, 3, 0);

  mCheckStatus = new QCheckBox(this, "mCheckStatus");
  mCheckStatus->setText("fixed");
  //mCheckStatus->setChecked(false);
  mCheckStatus->setChecked(true);
  MetabolitesWidget1Layout->addWidget(mCheckStatus, 3, 1);

  mLblStatus = new QLabel(this, "mLblStatus");
  mLblStatus->setText(trUtf8("Model Status"));
  MetabolitesWidget1Layout->addWidget(mLblStatus, 3, 2);

  mEditStatus = new QLineEdit(this, "mEditStatus");
  mEditStatus->setEnabled(false);
  MetabolitesWidget1Layout->addWidget(mEditStatus, 3, 3);

  //  QSpacerItem* spacer = new QSpacerItem(100, 70, QSizePolicy::Minimum, QSizePolicy::Expanding);
  //  MetabolitesWidget1Layout->addItem(spacer, 4, 2);
  //  QSpacerItem* spacer_2 = new QSpacerItem(100, 70, QSizePolicy::Minimum, QSizePolicy::Expanding);
  //  MetabolitesWidget1Layout->addItem(spacer_2, 4, 0);

  Line2 = new QFrame(this, "Line2");
  Line2->setFrameShape(QFrame::HLine);
  Line2->setFrameShadow(QFrame::Sunken);
  Line2->setFrameShape(QFrame::HLine);

  MetabolitesWidget1Layout->addMultiCellWidget(Line2, 4, 4, 0, 3);

  mLblInitConcentration = new QLabel(this, "mLblInitConcentration");
  mLblInitConcentration->setText(trUtf8("Initial  Concentration"));
  MetabolitesWidget1Layout->addWidget(mLblInitConcentration, 6, 0);

  mEditInitConcentration = new QLineEdit(this, "mEditInitConcentration");
  MetabolitesWidget1Layout->addWidget(mEditInitConcentration, 6, 1);

  mLblConcentration = new QLabel(this, "mLblConcentration");
  mLblConcentration->setText(trUtf8("Transient Concentration"));
  MetabolitesWidget1Layout->addWidget(mLblConcentration, 6, 2);

  mEditConcentration = new QLineEdit(this, "mEditConcentration");
  mEditConcentration->setEnabled(false);
  MetabolitesWidget1Layout->addWidget(mEditConcentration, 6, 3);

  mLblInitNumber = new QLabel(this, "mLblInitNumber");
  mLblInitNumber->setText(trUtf8("Initial  Number"));
  MetabolitesWidget1Layout->addWidget(mLblInitNumber, 7, 0);

  mEditInitNumber = new QLineEdit(this, "mEditInitNumber");
  MetabolitesWidget1Layout->addWidget(mEditInitNumber, 7, 1);

  mLblNumber = new QLabel(this, "mLblNumber");
  mLblNumber->setText(trUtf8("Transient Number"));
  MetabolitesWidget1Layout->addWidget(mLblNumber, 7, 2);

  mEditNumber = new QLineEdit(this, "mEditNumber");
  mEditNumber->setEnabled(FALSE);
  MetabolitesWidget1Layout->addWidget(mEditNumber, 7, 3);

  mLblTransitionTime = new QLabel(this, "mLblTransitionTime");
  mLblTransitionTime->setText(trUtf8("Transition Time"));
  MetabolitesWidget1Layout->addWidget(mLblTransitionTime, 8, 2);

  mEditTransitionTime = new QLineEdit(this, "mEditTransitionTime");
  mEditTransitionTime->setEnabled(FALSE);
  MetabolitesWidget1Layout->addWidget(mEditTransitionTime, 8, 3);

  QSpacerItem* spacer_3 = new QSpacerItem(470, 70, QSizePolicy::Minimum, QSizePolicy::Expanding);
  MetabolitesWidget1Layout->addMultiCell(spacer_3, 9, 9, 0, 3);

  Line3 = new QFrame(this, "Line3");
  Line3->setFrameShape(QFrame::HLine);
  Line3->setFrameShadow(QFrame::Sunken);
  Line3->setFrameShape(QFrame::HLine);

  MetabolitesWidget1Layout->addMultiCellWidget(Line3, 10, 10, 0, 3);

  Layout7 = new QHBoxLayout(0, 0, 6, "Layout7");

  commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit"));
  Layout7->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Revert"));
  Layout7->addWidget(cancelChanges);

  newMetaboliteBtn = new QPushButton(this, "newMetaboliteBtn");
  newMetaboliteBtn->setText(trUtf8("New"));
  Layout7->addWidget(newMetaboliteBtn);

  deleteMetaboliteBtn = new QPushButton(this, "deleteMetaboliteBtn");
  deleteMetaboliteBtn->setText(trUtf8("Delete"));
  Layout7->addWidget(deleteMetaboliteBtn);

  MetabolitesWidget1Layout->addMultiCellLayout(Layout7, 11, 11, 0, 3);

  setTabOrder(mEditName, mComboCompartment);
  setTabOrder(mComboCompartment, mCheckStatus);
  setTabOrder(mCheckStatus, mEditInitConcentration);
  setTabOrder(mEditInitConcentration, mEditInitNumber);
  setTabOrder(mEditInitNumber, commitChanges);
  setTabOrder(commitChanges, cancelChanges);
  setTabOrder(cancelChanges, newMetaboliteBtn);
  setTabOrder(newMetaboliteBtn, deleteMetaboliteBtn);

  // OK button
  connect(commitChanges, SIGNAL(clicked()),
          this, SLOT(slotBtnOKClicked()));
  // Cancel button
  connect(cancelChanges, SIGNAL(clicked()),
          this, SLOT(slotBtnCancelClicked()));
  connect(newMetaboliteBtn, SIGNAL(clicked()),
          this, SLOT(slotBtnNewClicked()));
  connect(deleteMetaboliteBtn, SIGNAL(clicked()),
          this, SLOT(slotBtnDeleteClicked()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
MetabolitesWidget1::~MetabolitesWidget1()
{
  // no need to delete child widgets, Qt does it all for us
}

/* This function loads the metabolites widget when its name is
   clicked in the tree   */
bool MetabolitesWidget1::loadFromMetabolite(const CMetab* metab)
{
  if (!metab) return false;

  CCopasiVectorNS< CCompartment > & allcompartments = dataModel->getModel()->getCompartments();
  CCompartment *compt;
  mComboCompartment->clear();
  mEditName->setText(FROM_UTF8(metab->getObjectName()));
  //Metabolite1_Name = new QString(metab->getObjectName().);

  mEditInitConcentration->setText(QString::number(metab->getInitialConcentration()));

  mEditConcentration->setText(QString::number(metab->getConcentration()));
  mEditConcentration->setReadOnly(true);

  mEditNumber->setText(QString::number(metab->getNumber()));
  mEditNumber->setReadOnly(true);

  mEditInitNumber->setText(QString::number(metab->getInitialNumber()));

  mEditTransitionTime->setText(QString::number(metab->getTransitionTime()));
  mEditTransitionTime->setReadOnly(true);

  if (metab->getStatus() == CMetab::METAB_FIXED)
    mCheckStatus->setChecked(true);
  else
    mCheckStatus->setChecked(false);

  mEditStatus->setText(FROM_UTF8(CMetab::StatusName[metab->getStatus()]));

  mComboCompartment->setDuplicatesEnabled (false);
  unsigned C_INT32 m;
  for (m = 0; m < allcompartments.size(); m++)
    {
      //showMessage("mudita","It comes here");

      compt = allcompartments[m];
      //mComboCompartment->insertStringList(compt->getObjectName().,j);
      mComboCompartment->insertItem(FROM_UTF8(compt->getObjectName()));
    }
  mComboCompartment->setCurrentText(FROM_UTF8(metab->getCompartment()->getObjectName()));

  return true;
}

bool MetabolitesWidget1::saveToMetabolite()
{
  //find pointer to metab from key
  CMetab* metab = dynamic_cast< CMetab * >(GlobalKeys.get(objKey));
  if (!metab) return false;

  //name
  QString name(mEditName->text());
  if ((const char *)name.utf8() != metab->getObjectName())
    {
      metab->setName((const char *)name.utf8());
      //TODO: update the reactions (the real thing, not the gui)
      //      propably not necessary anymore when reaction uses keys instead of names
      ListViews::notify(ListViews::METABOLITE, ListViews::RENAME, objKey);
    }

  //compartment
  QString Compartment = mComboCompartment->currentText();
  if ((const char *)Compartment.utf8() != metab->getCompartment()->getObjectName())
    {
      std::string CompartmentToRemove = metab->getCompartment()->getObjectName();
      dataModel->getModel()->getCompartments()[(const char *)Compartment.utf8()]->addMetabolite(metab);
      dataModel->getModel()->getCompartments()[CompartmentToRemove]->getMetabolites().remove(metab->getObjectName());
      dataModel->getModel()->initializeMetabolites();
      //ListViews::notify(ListViews::MODEL, ListViews::CHANGE, "");
      ListViews::notify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
      ListViews::notify(ListViews::COMPARTMENT, ListViews::CHANGE, "");
    }

  //for Initial Concentration and Initial Number
  QString initialConcentration(mEditInitConcentration->text());
  double temp1;
  temp1 = initialConcentration.toDouble();
  if (fabs(temp1 - metab->getInitialConcentration()) > 1e-10)
    {
      metab->setInitialConcentration(temp1);
      metab->setConcentration(temp1);
      ListViews::notify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
      dataModel->getModel()->setCompileFlag();
    }

  else
    {
      QString initialNumber(mEditInitNumber->text());
      C_FLOAT64 temp2;
      temp2 = initialNumber.toDouble();
      if (fabs(temp2 - metab->getInitialNumber()) > 1e-3) //TODO: this is extremely ugly
        {
          metab->setInitialNumber(temp2);
          metab->setNumber(temp2);
          ListViews::notify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
          dataModel->getModel()->setCompileFlag();
        }
    }

  //fixed?
  if (mCheckStatus->isChecked() == true)
    {
      if (metab->getStatus() != CMetab::METAB_FIXED)
        {
          metab->setStatus(CMetab::METAB_FIXED);
          ListViews::notify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
          dataModel->getModel()->setCompileFlag();
        }
    }
  else
    {
      if (metab->getStatus() != CMetab::METAB_VARIABLE)
        {
          metab->setStatus(CMetab::METAB_VARIABLE);
          ListViews::notify(ListViews::METABOLITE, ListViews::CHANGE, objKey);
          dataModel->getModel()->setCompileFlag();
        }
    }
  enter(objKey); //this is a hack to update the initial number when the initial concentration has changed and vice versa

  return true; //TODO: really check
}

void MetabolitesWidget1::slotBtnCancelClicked()
{
  //let the user confirm
  enter(objKey); // reload
}

void MetabolitesWidget1::slotBtnOKClicked()
{
  //let the user confirm?
  saveToMetabolite();
}

void MetabolitesWidget1::slotBtnNewClicked()
{
  if (dataModel->getModel()->getCompartments().size() == 0)
    dataModel->getModel()->createCompartment("compartment");

  std::string name = "metabolite";
  int i = 0;
  CMetab* pMetab;
  while (!(pMetab = dataModel->getModel()->createMetabolite(name, "", 1.0, CMetab::METAB_VARIABLE)))
    {
      i++;
      name = "metabolite_";
      name += (const char *)QString::number(i).utf8();
    }
  enter(pMetab->getKey());
  ListViews::notify(ListViews::METABOLITE, ListViews::ADD);
}

void MetabolitesWidget1::slotBtnDeleteClicked()
{
  if (!dataModel->getModel())
    return;

  QString metabList = "Are you sure you want to delete listed METABOLITE(S) ?\n";
  QString effectedReacList = "Following REACTION(S) reference above METABOLITE(S) and will be deleted -\n";
  int reacFound = 0;

  //unsigned C_INT32 i, imax = keys.size();
  //for (i = 0; i < imax; i++)
  //  {
  //metabList.append(FROM_UTF8(GlobalKeys.get(keys[i])->getObjectName()));
  metabList.append(FROM_UTF8(GlobalKeys.get(objKey)->getObjectName()));
  metabList.append(", ");

  //CMetab* metab =
  //  dynamic_cast< CMetab *>(GlobalKeys.get(keys[i]));

  std::set<std::string> effectedReacKeys = dataModel->getModel()->listReactionsDependentOnMetab(objKey);

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
      effectedReacList.append(FROM_UTF8(GlobalKeys.get(objKey)->getObjectName()));
      effectedReacList.append("\n");
    }
  //}

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
    case 0:                    // Yes or Enter
      {
        unsigned C_INT32 size = Copasi->pModel->getMetabolites().size();
        //unsigned C_INT32 index = Copasi->pFunctionDB->loadedFunctions().getIndex(pFunction->getObjectName());
        unsigned C_INT32 index = Copasi->pModel->getMetabolites().getIndex(GlobalKeys.get(objKey));
        /*for (i = 0; i < imax; i++)
               {
                 dataModel->getModel()->removeMetabolite(keys[i]);
               }*/
        dataModel->getModel()->removeMetabolite(objKey);
        enter(Copasi->pModel->getMetabolites()[std::min(index, size - 2)]->getKey());
        //for (i = 0; i < imax; i++)
        ListViews::notify(ListViews::METABOLITE, ListViews::DELETE, objKey);
        //TODO notify about reactions
        break;
      }
    case 1:                    // No or Escape
      break;
    }
}

bool MetabolitesWidget1::update(ListViews::ObjectType objectType,
                                ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  switch (objectType)
    {
    case ListViews::STATE:
    case ListViews::MODEL:
      //TODO: check if it really is a compartment
      return loadFromMetabolite(dynamic_cast< CMetab * >(GlobalKeys.get(objKey)));
      break;

    default:
      break;
    }
  return true;
}

bool MetabolitesWidget1::leave()
{
  //let the user confirm?
  return saveToMetabolite();
}

bool MetabolitesWidget1::enter(const std::string & key)
{
  objKey = key;
  CMetab* metab = dynamic_cast< CMetab * >(GlobalKeys.get(key));
  //TODO: check if it really is a compartment

  if (metab) return loadFromMetabolite(metab);
  else return false;
}
