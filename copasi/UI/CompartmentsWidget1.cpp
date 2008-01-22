// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CompartmentsWidget1.cpp,v $
//   $Revision: 1.93.8.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/22 18:51:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
#include <qhbox.h>

#include "copasi.h"

#include "CompartmentsWidget1.h"
#include "listviews.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CMetab.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiVector.h"
#include "report/CKeyFactory.h"

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

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Compartment Name"));
  TextLabel1->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  CompartmentsWidget1Layout->addWidget(TextLabel1, 0, 0);

  LineEdit1 = new QLineEdit(this, "LineEdit1");
  CompartmentsWidget1Layout->addWidget(LineEdit1, 0, 1);

  //*********************

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Initial  Volume"));
  TextLabel2->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  CompartmentsWidget1Layout->addWidget(TextLabel2, 2, 0);

  QHBox* tmp = new QHBox(this);
  LineEdit3 = new QLineEdit(tmp, "LineEdit3");
  LineEdit3->setValidator(new QDoubleValidator(LineEdit3));
  CompartmentsWidget1Layout->addWidget(tmp, 2, 1);

  //*********************

  TextLabel2_2 = new QLabel(this, "TextLabel2_2");
  TextLabel2_2->setText(trUtf8("Transient Volume"));
  TextLabel2_2->setAlignment(int(QLabel::AlignVCenter
                                 | QLabel::AlignRight));
  CompartmentsWidget1Layout->addWidget(TextLabel2_2, 3, 0);

  LineEdit4 = new QLineEdit(this, "LineEdit4");
  LineEdit4->setEnabled(FALSE);
  LineEdit4->setReadOnly(TRUE);
  CompartmentsWidget1Layout->addWidget(LineEdit4, 3, 1);

  //*********************

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Species"));
  TextLabel3->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  CompartmentsWidget1Layout->addWidget(TextLabel3, 5, 0);

  QSpacerItem* spacer2 = new QSpacerItem(131, 270, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CompartmentsWidget1Layout->addItem(spacer2, 6, 0);

  ListBox1 = new QListBox(this, "ListBox1");
  ListBox1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  CompartmentsWidget1Layout->addMultiCellWidget(ListBox1, 5, 6, 1, 1);

  //QSpacerItem* spacer_2 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  //CompartmentsWidget1Layout->addMultiCell(spacer_2, 7, 7, 1, 1);

  //*********************

  Line4 = new QFrame(this, "Line4");
  //Line4->setFrameShape(QFrame::HLine);
  CompartmentsWidget1Layout->addMultiCellWidget(Line4, 1, 1, 0, 1);

  Line4_2 = new QFrame(this, "Line4_2");
  Line4_2->setFrameShape(QFrame::HLine);
  CompartmentsWidget1Layout->addMultiCellWidget(Line4_2, 4, 4, 0, 1);

  //Line4_3 = new QFrame(this, "Line4_3");
  //CompartmentsWidget1Layout->addMultiCellWidget(Line4_3, 7, 7, 0, 1);

  //*********************

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
  ListBox1->triggerUpdate(true);

  volumeSave = QString::number(compartn->getInitialValue());
  LineEdit3->setText(volumeSave);

  LineEdit4->setText(QString::number(compartn->getValue()));
  LineEdit4->setReadOnly(true);

  /* <---for displaying units in the Widget */
  TextLabel2_2->setText("Transient Volume\n(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getVolumeUnitName()) + ")");
  TextLabel2->setText("Initial  Volume\n(" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getVolumeUnitName()) + ")");
  /* ---> */
  currentCompt = compartn;
  return true;
}
void CompartmentsWidget1::slotListBoxCurrentChanged(const QString & C_UNUSED(m))
{
  const CCopasiVectorNS < CMetab > & Metabs = currentCompt->getMetabolites();
  C_INT32 noOfMetabolitesRows = Metabs.size();
  const CMetab *mtb;
  std::string mMetName;
  C_INT32 j;
  for (j = 0; j < noOfMetabolitesRows; j++)
    {
      mtb = Metabs[j];
      mMetName = mtb->getObjectName();
      if (ListBox1->currentText() == mtb->getObjectName().c_str())
        {
          pListView->switchToOtherWidget(0, mtb->getKey());
        }
    }
}

bool CompartmentsWidget1::saveToCompartment()
{
  CCompartment* comp = dynamic_cast< CCompartment * >(GlobalKeys.get(objKey));
  if (!comp) return true;

  int cursor = 0;
  QString tmpstring = LineEdit3->text();
  if (LineEdit3->validator()->validate(tmpstring, cursor) == QValidator::Intermediate)
    {
      CQMessageBox::information(this, "Invalid Input", "Please check Initial Volume. It must be specified.",
                                QMessageBox::Ok, QMessageBox::NoButton);
      return false;
    }

  //name
  QString name(LineEdit1->text());
  if ((const char *)name.utf8() != comp->getObjectName())
    {
      if (!comp->setObjectName((const char *)name.utf8()))
        {
          QString msg;
          msg = "Unable to rename compartment '" + FROM_UTF8(comp->getObjectName()) + "'\n"
                + "to '" + name + "' since a compartment with that name already exists.";

          CQMessageBox::information(this,
                                    "Unable to rename Compartment",
                                    msg,
                                    QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);

          LineEdit1->setText(FROM_UTF8(comp->getObjectName()));
        }
      else
        protectedNotify(ListViews::COMPARTMENT, ListViews::RENAME, objKey);
    }

  //volume
  QString volume(LineEdit3->text());
  if (volume != volumeSave)
    {
      double m1;
      m1 = volume.toDouble();
      comp->setInitialValue(m1);
      protectedNotify(ListViews::COMPARTMENT, ListViews::CHANGE, objKey);
      volumeSave = volume;
    }

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  CCopasiDataModel::Global->changed();

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
  slotBtnOKClicked();

  std::string name = "compartment";
  int i = 0;
  CCompartment* pCom;
  while (!(pCom = CCopasiDataModel::Global->getModel()->createCompartment(name)))
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
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL)
    return;

  CCompartment* comp = dynamic_cast< CCompartment *>(GlobalKeys.get(objKey));
  if (comp == NULL) return;

  QString compartmentList = "Are you sure you want to delete listed COMPARTMENT(S) ?\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedMetabList = Following SPECIES reference above COMPARTMENT(S) and will be deleted - \n;
  QString effectedReacList = "Following REACTION(S) reference above COMPARTMENT(S) and will be deleted -\n";
  QString effectedValueList = "Following MODEL VALUE(S) reference above COMPARTMENT(S) and will be deleted -\n";

  bool compartmentFound = false;
  bool metabFound = false;
  bool reacFound = false;
  bool valueFound = false;

  compartmentList.append(FROM_UTF8(comp->getObjectName()));
  compartmentList.append(", ");

  std::set< const CCopasiObject * > Reactions;
  pModel->appendDependentReactions(comp->getDeletedObjects(), Reactions);

  if (Reactions.size() > 0)
    {
      reacFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Reactions.end();
      for (it = Reactions.begin(); it != itEnd; ++it)
        {
          effectedReacList.append(FROM_UTF8((*it)->getObjectName()));
          effectedReacList.append(", ");
        }

      effectedReacList.remove(effectedReacList.length() - 2, 2);
      effectedReacList.append("  ---> ");
      effectedReacList.append(FROM_UTF8(comp->getObjectName()));
      effectedReacList.append("\n");
    }

  std::set< const CCopasiObject * > Metabolites;
  pModel->appendDependentMetabolites(comp->getDeletedObjects(), Metabolites);

  if (Metabolites.size() > 0)
    {
      metabFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Metabolites.end();
      for (it = Metabolites.begin(); it != itEnd; ++it)
        {
          effectedMetabList.append(FROM_UTF8((*it)->getObjectName()));
          effectedMetabList.append(", ");
        }

      effectedMetabList.remove(effectedMetabList.length() - 2, 2);
      effectedMetabList.append("  ---> ");
      effectedMetabList.append(FROM_UTF8(comp->getObjectName()));
      effectedMetabList.append("\n");
    }

  std::set< const CCopasiObject * > Values;
  pModel->appendDependentModelValues(comp->getDeletedObjects(), Values);

  if (Values.size() > 0)
    {
      valueFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Values.end();
      for (it = Values.begin(); it != itEnd; ++it)
        {
          effectedValueList.append(FROM_UTF8((*it)->getObjectName()));
          effectedValueList.append(", ");
        }

      effectedValueList.remove(effectedValueList.length() - 2, 2);
      effectedValueList.append("  ---> ");
      effectedValueList.append(FROM_UTF8(comp->getObjectName()));
      effectedValueList.append("\n");
    }

  std::set< const CCopasiObject * > Compartments;
  pModel->appendDependentCompartments(comp->getDeletedObjects(), Compartments);

  if (Compartments.size() > 0)
    {
      compartmentFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Compartments.end();
      for (it = Compartments.begin(); it != itEnd; ++it)
        {
          effectedCompartmentList.append(FROM_UTF8((*it)->getObjectName()));
          effectedCompartmentList.append(", ");
        }

      effectedCompartmentList.remove(effectedCompartmentList.length() - 2, 2);
      effectedCompartmentList.append("  ---> ");
      effectedCompartmentList.append(FROM_UTF8(comp->getObjectName()));
      effectedCompartmentList.append("\n");
    }

  compartmentList.remove(compartmentList.length() - 2, 2);

  QString msg = compartmentList;

  if (compartmentFound)
    {
      msg.append("\n \n");
      msg.append(effectedCompartmentList);
    }

  if (metabFound)
    {
      msg.append("\n \n");
      msg.append(effectedMetabList);
    }

  if (reacFound)
    {
      msg.append("\n \n");
      msg.append(effectedReacList);
    }

  if (valueFound)
    {
      msg.append("\n \n");
      msg.append(effectedValueList);
    }

  C_INT32 choice = 0;
  if (metabFound || reacFound || valueFound || valueFound)
    choice = CQMessageBox::question(this,
                                    "CONFIRM DELETE",
                                    msg,
                                    "Continue", "Cancel", 0, 1, 1);

  switch (choice)
    {
    case 0:                                 // Yes or Enter
      {
        unsigned C_INT32 Index =
          CCopasiDataModel::Global->getModel()->getCompartments().getIndex(comp->getObjectName());
        CCopasiDataModel::Global->getModel()->removeCompartment(objKey);

        unsigned C_INT32 Size =
          CCopasiDataModel::Global->getModel()->getCompartments().size();

        if (Size > 0)
          enter(CCopasiDataModel::Global->getModel()->getCompartments()[std::min(Index, Size - 1)]->getKey());
        else
          enter("");

        protectedNotify(ListViews::COMPARTMENT, ListViews::DELETE, objKey);

        //TODO notify about metabs and reactions
        break;
      }
    default:                                 // No or Escape
      break;
    }
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

  if (comp)
    return loadFromCompartment(comp);
  else
    pListView->switchToOtherWidget(111, "");

  return false;
}
