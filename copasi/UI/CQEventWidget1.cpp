// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEventWidget1.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/10/30 16:08:52 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qtooltip.h>

#include "copasi.h"
#include "CQEventWidget1.h"
#include "listviews.h"
#include "MyLineEdit.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"

CQEventWidget1::CQEventWidget1(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f),
    objKey("")
{
  if (!name)
    setName("EventWidget1");
  setCaption(trUtf8("EventWidget1"));

  EventWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "EventWidget1Layout");

  TextLabel4 = new QLabel(this, "TextLabel4");
  TextLabel4->setText(trUtf8("Name"));
  TextLabel4->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  EventWidget1Layout->addWidget(TextLabel4, 0, 0);

  //Buttons:
  Layout1 = new QHBoxLayout(0, 0, 6, "Layout1");

  commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit"));
  Layout1->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Revert"));
  Layout1->addWidget(cancelChanges);

  newReaction = new QPushButton(this, "newReaction");
  newReaction->setText(trUtf8("&New"));
  Layout1->addWidget(newReaction);

  deleteReaction = new QPushButton(this, "deleteReaction");
  deleteReaction->setText(trUtf8("&Delete"));
  Layout1->addWidget(deleteReaction);

  EventWidget1Layout->addMultiCellLayout(Layout1, 11, 11, 0, 3);

  //

  Line2 = new QFrame(this, "Line2");
  Line2->setFrameShape(QFrame::HLine);
  Line2->setFrameShadow(QFrame::Sunken);
  Line2->setFrameShape(QFrame::HLine);
  EventWidget1Layout->addMultiCellWidget(Line2, 7, 7, 0, 3);

  //name
  LineEdit1 = new MyLineEdit(this, "LineEdit1");
  EventWidget1Layout->addMultiCellWidget(LineEdit1, 0, 0, 1, 3);

  QSpacerItem* spacer = new QSpacerItem(80, 101, QSizePolicy::Minimum, QSizePolicy::Expanding);
  EventWidget1Layout->addItem(spacer, 10, 0);

  setTabOrder(LineEdit1, commitChanges);
  setTabOrder(commitChanges, cancelChanges);
  setTabOrder(cancelChanges, newReaction);
  setTabOrder(newReaction, deleteReaction); //TODO !!!!!

  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
  connect(newReaction, SIGNAL(clicked()), this, SLOT(slotBtnNewClicked()));
  connect(deleteReaction, SIGNAL(clicked()), this, SLOT(slotBtnDeleteClicked()));

  connect(LineEdit1, SIGNAL(edited()), this, SLOT(slotNameChanged()));
}

CQEventWidget1::~CQEventWidget1()
{}

bool CQEventWidget1::loadFromEvent(const CEvent* pEvent)
{
  if (!pEvent) return false;

  return true; //TODO: really check
}

bool CQEventWidget1::saveToEvent()
{
  CEvent* pEvent = dynamic_cast< CEvent * >(GlobalKeys.get(objKey));
  if (!pEvent) return true;

  //mpRi->setReactionName((const char *)LineEdit1->text().utf8());

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  CCopasiDataModel::Global->changed();

  return true;
}

void CQEventWidget1::slotBtnCancelClicked()
{
  enter(objKey);
}

void CQEventWidget1::slotBtnOKClicked()
{
  saveToEvent();
}

void CQEventWidget1::slotNameChanged()
{
  std::string rName = (const char *)LineEdit1->text().utf8();
}

// added 5/19/04
void CQEventWidget1::slotBtnNewClicked()
{
  slotBtnOKClicked();

  std::string name = "event";
  int i = 0;
  while (!CCopasiDataModel::Global->getModel()->createEvent(name))
    {
      i++;
      name = "event_";
      name += QString::number(i).utf8();
    }
  protectedNotify(ListViews::EVENT, ListViews::ADD);
  enter(CCopasiDataModel::Global->getModel()->getEvents()[name]->getKey());
  //pListView->switchToOtherWidget(mKeys[row]);
}

void CQEventWidget1::slotBtnDeleteClicked()
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL)
    return;

  CEvent * pEvent =
    dynamic_cast< CEvent * >(GlobalKeys.get(objKey));
  if (pEvent == NULL) return;

  QString eventList = "Are you sure you want to delete listed REACTION(S) ?\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above REACTION(S) and will be deleted -\n";
  QString effectedMetabList = "Following METABOLITE(S) reference above REACTION(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above REACTION(S) and will be deleted -\n";
  QString effectedValueList = "Following MODEL VALUE(S) reference above REACTION(S) and will be deleted -\n";

  bool compartmentFound = false;
  bool metabFound = false;
  bool reacFound = false;
  bool valueFound = false;

  eventList.append(FROM_UTF8(pEvent->getObjectName()));
  eventList.append(", ");

  std::set< const CCopasiObject * > Reactions;
  std::set< const CCopasiObject * > Metabolites;
  std::set< const CCopasiObject * > Values;
  std::set< const CCopasiObject * > Compartments;

  pModel->appendDependentModelObjects(pEvent->getDeletedObjects(),
                                      Reactions, Metabolites, Compartments, Values);

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
      //effectedReacList.append("  ---> ");
      //effectedReacList.append(FROM_UTF8(pEvent->getObjectName()));
      effectedReacList.append("\n");
    }

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
      //effectedMetabList.append("  ---> ");
      //effectedMetabList.append(FROM_UTF8(pEvent->getObjectName()));
      effectedMetabList.append("\n");
    }

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
      //effectedValueList.append("  ---> ");
      //effectedValueList.append(FROM_UTF8(pEvent->getObjectName()));
      effectedValueList.append("\n");
    }

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
      //effectedCompartmentList.append("  ---> ");
      //effectedCompartmentList.append(FROM_UTF8(pEvent->getObjectName()));
      effectedCompartmentList.append("\n");
    }

  eventList.remove(eventList.length() - 2, 2);

  QString msg = eventList;

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
    case 0:                                                     // Yes or Enter
      {
        unsigned C_INT32 index
        //= CCopasiDataModel::Global->getModel()->getEvents().getIndex(eventName);
        = 0; //TODO

        CCopasiDataModel::Global->getModel()->removeEvent(objKey);
        unsigned C_INT32 size
        = CCopasiDataModel::Global->getModel()->getEvents().size();

        if (size > 0)
          enter(CCopasiDataModel::Global->getModel()->getEvents()[std::min(index, size - 1)]->getKey());
        else
          enter("");

        protectedNotify(ListViews::EVENT, ListViews::DELETE, objKey);
        break;
      }
    default:                                                     // No or Escape
      break;
    }
}

bool CQEventWidget1::update(ListViews::ObjectType objectType,
                            ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
      return loadFromEvent(dynamic_cast< CEvent * >(GlobalKeys.get(objKey)));
      break;

    default:
      break;
    }
  return true;
}

bool CQEventWidget1::leave()
{
  saveToEvent();
  return true; //always return true. That means that the widget can be
  //left without saving
}

bool CQEventWidget1::enter(const std::string & key)
{
  objKey = key;
  CEvent* pEvent = dynamic_cast< CEvent * >(GlobalKeys.get(key));

  if (pEvent)
    return loadFromEvent(pEvent);

  pListView->switchToOtherWidget(114, ""); //TODO
  return false;
}
