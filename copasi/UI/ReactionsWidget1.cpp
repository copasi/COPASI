/*********************************************************************
 **  $ CopasiUI/ReactionsWidget1.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the  information 
 ** obtained from the data model about the Recations----It is Basically 
 ** the Second level of Reactions.
 **********************************************************************/

#include <qgroupbox.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include "copasi.h"
#include "utilities/CCopasiVector.h"
#include "ReactionsWidget1.h"
#include "listviews.h"
#include "model/CModel.h"
#include "function/CFunctionDB.h"
#include "function/CFunctionParameters.h"
#include "function/CFunctionParameter.h"
#include "utilities/CGlobals.h"
#include "utilities/CMethodParameter.h"
#include "parametertable.h"
#include "report/CKeyFactory.h"
#include "MyLineEdit.h"

/*
 *  Constructs a ReactionsWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 */

ReactionsWidget1::ReactionsWidget1(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)

{
  if (!name)
    setName("ReactionsWidget1");
  setCaption(trUtf8("ReactionsWidget1"));
  ReactionsWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "ReactionsWidget1Layout");

  TextLabel4 = new QLabel(this, "TextLabel4");
  TextLabel4->setText(trUtf8("Name"));

  ReactionsWidget1Layout->addWidget(TextLabel4, 0, 0);

  TextLabel7 = new QLabel(this, "TextLabel7");
  TextLabel7->setText(trUtf8("Symbol Definition"));

  ReactionsWidget1Layout->addWidget(TextLabel7, 8, 0);

  Layout1 = new QHBoxLayout(0, 0, 6, "Layout1");

  commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("&Commit"));
  Layout1->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("&Cancel"));
  Layout1->addWidget(cancelChanges);

  newReaction = new QPushButton(this, "newReaction");
  newReaction->setText(trUtf8("&New"));
  Layout1->addWidget(newReaction);

  deleteReaction = new QPushButton(this, "deleteReaction");
  deleteReaction->setText(trUtf8("&Delete"));
  Layout1->addWidget(deleteReaction);

  ReactionsWidget1Layout->addMultiCellLayout(Layout1, 12, 12, 0, 3);

  TextLabel8 = new QLabel(this, "TextLabel8");
  TextLabel8->setText(trUtf8("Flux"));

  ReactionsWidget1Layout->addWidget(TextLabel8, 10, 0);

  Line2 = new QFrame(this, "Line2");
  Line2->setFrameShape(QFrame::HLine);
  Line2->setFrameShadow(QFrame::Sunken);
  Line2->setFrameShape(QFrame::HLine);

  ReactionsWidget1Layout->addMultiCellWidget(Line2, 6, 7, 0, 3);

  Line1 = new QFrame(this, "Line1");
  Line1->setFrameShape(QFrame::HLine);
  Line1->setFrameShadow(QFrame::Sunken);
  Line1->setFrameShape(QFrame::HLine);

  ReactionsWidget1Layout->addMultiCellWidget(Line1, 11, 11, 0, 3);

  Line3 = new QFrame(this, "Line3");
  Line3->setFrameShape(QFrame::HLine);
  Line3->setFrameShadow(QFrame::Sunken);
  Line3->setFrameShape(QFrame::HLine);

  ReactionsWidget1Layout->addMultiCellWidget(Line3, 1, 1, 0, 3);

  TextLabel6 = new QLabel(this, "TextLabel6");
  TextLabel6->setText(trUtf8("Kinetics"));

  ReactionsWidget1Layout->addWidget(TextLabel6, 4, 0);

  LineEdit1 = new QLineEdit(this, "LineEdit1");

  ReactionsWidget1Layout->addMultiCellWidget(LineEdit1, 0, 0, 1, 3);

  LineEdit2 = new MyLineEdit(this, "LineEdit2");
  LineEdit2->setFrameShape(QLineEdit::LineEditPanel);
  LineEdit2->setFrameShadow(QLineEdit::Sunken);

  ReactionsWidget1Layout->addMultiCellWidget(LineEdit2, 2, 2, 1, 3);

  ComboBox1 = new QComboBox(FALSE, this, "ComboBox1");

  ReactionsWidget1Layout->addMultiCellWidget(ComboBox1, 4, 4, 1, 3);

  Line4 = new QFrame(this, "Line4");
  Line4->setFrameShape(QFrame::HLine);
  Line4->setFrameShadow(QFrame::Sunken);
  Line4->setFrameShape(QFrame::HLine);

  ReactionsWidget1Layout->addMultiCellWidget(Line4, 3, 3, 0, 3);

  table = new ParameterTable(this, "table");

  ReactionsWidget1Layout->addMultiCellWidget(table, 7, 9, 1, 3);

  LineEdit3 = new QLineEdit(this, "LineEdit3");
  LineEdit3->setEnabled(FALSE);

  ReactionsWidget1Layout->addMultiCellWidget(LineEdit3, 10, 10, 1, 3);
  QSpacerItem* spacer = new QSpacerItem(80, 101, QSizePolicy::Minimum, QSizePolicy::Expanding);
  ReactionsWidget1Layout->addItem(spacer, 9, 0);

  TextLabel5 = new QLabel(this, "TextLabel5");
  TextLabel5->setText(trUtf8("Chemical Reaction"));

  ReactionsWidget1Layout->addWidget(TextLabel5, 2, 0);

  newKinetics = new QPushButton(this, "newKinetics");
  newKinetics->setText(trUtf8("&New Kinetics"));

  ReactionsWidget1Layout->addWidget(newKinetics, 5, 1);
  QSpacerItem* spacer_2 = new QSpacerItem(111, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  ReactionsWidget1Layout->addItem(spacer_2, 5, 2);

  CheckBox = new QCheckBox(this, "CheckBox");
  CheckBox->setText(trUtf8("Reversible"));

  ReactionsWidget1Layout->addWidget(CheckBox, 5, 3);

  setTabOrder(LineEdit1, LineEdit2);
  setTabOrder(LineEdit2, ComboBox1);
  setTabOrder(ComboBox1, newKinetics);
  setTabOrder(newKinetics, CheckBox);
  setTabOrder(CheckBox, table);
  setTabOrder(table, LineEdit3);
  setTabOrder(LineEdit3, commitChanges);
  setTabOrder(commitChanges, cancelChanges);
  setTabOrder(cancelChanges, newReaction);
  setTabOrder(newReaction, deleteReaction);

  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
  connect(newReaction, SIGNAL(clicked()), this, SLOT(slotBtnNewClicked()));

  connect(CheckBox, SIGNAL(clicked()), this, SLOT(slotCheckBoxClicked()));
  connect(ComboBox1, SIGNAL(activated(const QString &)), this, SLOT(slotComboBoxSelectionChanged(const QString &)));
  connect(LineEdit2, SIGNAL(edited()), this, SLOT(slotLineEditChanged()));

  //connect(table, SIGNAL(signalChanged(int, int, Qstring)), this, SLOT(slotTableChanged(int, int, QString)));
}

ReactionsWidget1::~ReactionsWidget1()
{}

/* This function loads the reactions widget when its name is
   clicked in the tree   */
bool ReactionsWidget1::loadFromReaction(const CReaction* reaction)
{
  // this loads the reaction into a CReactionInterface object.
  // the gui works on this object and later writes back the changes to the reaction
  mRi.initFromReaction(reaction->getName(), *(dataModel->getModel()));

  // update the widget.
  FillWidgetFromRI();

  return true; //TODO: really check
}

bool ReactionsWidget1::saveToReaction()
{
  //this writes all changes to the reaction
  mRi.writeBackToReaction(*(dataModel->getModel()));

  //this tells the gui what it needs to know.
  ListViews::notify(ListViews::REACTION, ListViews::CHANGE, objKey);

  //TODO: detect rename events (mRi.writeBackToReaction has to do this)
  return true;
}

void ReactionsWidget1::slotBtnCancelClicked()
{
  //let the user confirm
  enter(objKey); // reload
}

void ReactionsWidget1::slotBtnOKClicked()
{
  //let the user confirm?
  saveToReaction();
}

void ReactionsWidget1::slotCheckBoxClicked()
{
  // tell the reaction interface
  mRi.setReversibility(CheckBox->isChecked());

  // update the widget
  FillWidgetFromRI();
}

// the function has been changed
void ReactionsWidget1::slotComboBoxSelectionChanged(const QString & p2)
{
  // tell the reaction interface
  mRi.setFunction(p2.latin1());

  // update the widget
  FillWidgetFromRI();
}

/*This function is called when the "Chemical Reaction" LineEdit is changed.*/
void ReactionsWidget1::slotLineEditChanged()
{
  // tell the reaction interface
  mRi.setChemEqString(LineEdit2->text().latin1());

  // update the widget
  FillWidgetFromRI();
}

void ReactionsWidget1::slotBtnNewClicked()
{}

void ReactionsWidget1::FillWidgetFromRI()
{
  LineEdit1->setText(mRi.getReactionName().c_str());

  LineEdit2->setText(mRi.getChemEqString().c_str());

  //LineEdit3->setText(QString::number(reactn->getFlux())); //TODO

  // the reversibility checkbox
  CheckBox->setChecked(false);
  if (mRi.isReversible() == true)
    {
      CheckBox->setChecked(true);
    }

  // the function combobox
  QStringList comboEntries;
  ParameterTable::vectorOfStrings2QStringList(mRi.getListOfPossibleFunctions(), comboEntries);

  ComboBox1->clear();
  ComboBox1->insertStringList(comboEntries, -1);

  // if there is a current function the parameter table is initialized
  if (mRi.getFunctionName() != "")
    {
      ComboBox1->setCurrentText(mRi.getFunctionName().c_str());
      table->updateTable(mRi);
    }

  //TODO isValid()
  commitChanges->setEnabled(mRi.isValid());
}

void ReactionsWidget1::slotTableChanged(int index, int sub, QString newValue)
{
  //std::cout << "slotValueChanged " << index << " " << sub << " " << newValue <<  std::endl;

  // setValue
  if (mRi.getUsage(index) == "PARAMETER")
    {
      if (sub != 0) return;
      mRi.setValue(index, newValue.toDouble()); // TODO: check
    }
  else
    {
      if (sub == 0)
        {
          mRi.setMetab(index, table->text(table->mIndex2Line[index], 2).latin1());
        }
    }

  // update the widget
  FillWidgetFromRI();
}

bool ReactionsWidget1::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
      //TODO: we have to decide how to handle this
      break;

    default:
      break;
    }
  return true;
}

bool ReactionsWidget1::leave()
{
  //TODO: let the user confirm?
  return saveToReaction();
}

bool ReactionsWidget1::enter(const std::string & key)
{
  objKey = key;
  CReaction* reac = (CReaction*)(CCopasiContainer*)CKeyFactory::get(key);
  //TODO: check if it really is a compartment

  if (reac) return loadFromReaction(reac);
  else return false;
}
