/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ReactionsWidget1.cpp,v $
   $Revision: 1.169 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/06/02 19:56:23 $
   End CVS Header */

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
#include <qmessagebox.h>
#include <qtooltip.h>

#include "copasi.h"
#include "utilities/CCopasiVector.h"
#include "ReactionsWidget1.h"
#include "listviews.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "function/CFunctionDB.h"
#include "function/CFunctionParameters.h"
#include "function/CFunctionParameter.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "parametertable.h"
#include "report/CKeyFactory.h"
#include "MyLineEdit.h"
#include "qtUtilities.h"
#include "ChemEqValidator.h"
#include "FunctionWidget1.h"

/*
 *  Constructs a ReactionsWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 */

ReactionsWidget1::ReactionsWidget1(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f),
    objKey("")

{
  if (!name)
    setName("ReactionsWidget1");
  setCaption(trUtf8("ReactionsWidget1"));

  ReactionsWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "ReactionsWidget1Layout");

  TextLabel4 = new QLabel(this, "TextLabel4");
  TextLabel4->setText(trUtf8("Name"));
  TextLabel4->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  ReactionsWidget1Layout->addWidget(TextLabel4, 0, 0);

  TextLabel7 = new QLabel(this, "TextLabel7");
  TextLabel7->setText(trUtf8("Symbol Definition"));
  TextLabel7->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  ReactionsWidget1Layout->addWidget(TextLabel7, 8, 0);

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

  ReactionsWidget1Layout->addMultiCellLayout(Layout1, 12, 12, 0, 3);

  //

  Line2 = new QFrame(this, "Line2");
  Line2->setFrameShape(QFrame::HLine);
  Line2->setFrameShadow(QFrame::Sunken);
  Line2->setFrameShape(QFrame::HLine);
  ReactionsWidget1Layout->addMultiCellWidget(Line2, 6, 7, 0, 3);

  /*Line1 = new QFrame(this, "Line1");
  Line1->setFrameShape(QFrame::HLine);
  Line1->setFrameShadow(QFrame::Sunken);
  Line1->setFrameShape(QFrame::HLine);
  ReactionsWidget1Layout->addMultiCellWidget(Line1, 11, 11, 0, 3);*/

  /*Line3 = new QFrame(this, "Line3");
  Line3->setFrameShape(QFrame::HLine);
  Line3->setFrameShadow(QFrame::Sunken);
  Line3->setFrameShape(QFrame::HLine);
  ReactionsWidget1Layout->addMultiCellWidget(Line3, 1, 1, 0, 3);*/

  // kinetics line
  TextLabel6 = new QLabel(this, "TextLabel6");
  TextLabel6->setText(trUtf8("Kinetics"));
  TextLabel6->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  ReactionsWidget1Layout->addWidget(TextLabel6, 4, 0);

  ComboBox1 = new QComboBox(FALSE, this, "ComboBox1");
  ReactionsWidget1Layout->addMultiCellWidget(ComboBox1, 4, 4, 1, 2);

  newKinetics = new QPushButton(this, "newKinetics");
  newKinetics->setText(trUtf8("&New Kinetics"));
  ReactionsWidget1Layout->addWidget(newKinetics, 4, 3);

  TextLabel8 = new QLabel(this, "TextLabel8");
  TextLabel8->setText(trUtf8("Flux"));
  TextLabel8->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  ReactionsWidget1Layout->addWidget(TextLabel8, 5, 0);

  LineEdit3 = new QLineEdit(this, "LineEdit3");
  LineEdit3->setEnabled(FALSE);
  ReactionsWidget1Layout->addMultiCellWidget(LineEdit3, 5, 5, 1, 2);

  //name
  LineEdit1 = new MyLineEdit(this, "LineEdit1");
  ReactionsWidget1Layout->addMultiCellWidget(LineEdit1, 0, 0, 1, 3);

  // equation line
  TextLabel5 = new QLabel(this, "TextLabel5");
  TextLabel5->setText(trUtf8("Chemical Equation"));
  TextLabel5->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  ReactionsWidget1Layout->addWidget(TextLabel5, 2, 0);

  LineEdit2 = new MyLineEdit(this, "LineEdit2");
  LineEdit2->setValidator(new ChemEqValidator(LineEdit2));
  ReactionsWidget1Layout->addMultiCellWidget(LineEdit2, 2, 2, 1, 2);

  CheckBox = new QCheckBox(this, "CheckBox");
  CheckBox->setText(trUtf8("Reversible"));
  ReactionsWidget1Layout->addWidget(CheckBox, 2, 3);

  Line4 = new QFrame(this, "Line4");
  Line4->setFrameShape(QFrame::HLine);
  Line4->setFrameShadow(QFrame::Sunken);
  Line4->setFrameShape(QFrame::HLine);
  ReactionsWidget1Layout->addMultiCellWidget(Line4, 3, 3, 0, 3);

  table = new ParameterTable(this, "table");
  ReactionsWidget1Layout->addMultiCellWidget(table, 7, 9, 1, 3);

  QSpacerItem* spacer = new QSpacerItem(80, 101, QSizePolicy::Minimum, QSizePolicy::Expanding);
  ReactionsWidget1Layout->addItem(spacer, 9, 0);

  setTabOrder(LineEdit1, LineEdit2);
  setTabOrder(LineEdit2, CheckBox);
  setTabOrder(CheckBox, ComboBox1);
  setTabOrder(ComboBox1, newKinetics);
  setTabOrder(newKinetics, table);
  setTabOrder(table, commitChanges);
  setTabOrder(commitChanges, cancelChanges);
  setTabOrder(cancelChanges, newReaction);
  setTabOrder(newReaction, deleteReaction); //TODO !!!!!

  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
  connect(newReaction, SIGNAL(clicked()), this, SLOT(slotBtnNewClicked()));
  connect(deleteReaction, SIGNAL(clicked()), this, SLOT(slotBtnDeleteClicked()));

  connect(newKinetics, SIGNAL(clicked()), this, SLOT(slotNewFunction()));

  connect(CheckBox, SIGNAL(clicked()), this, SLOT(slotCheckBoxClicked()));
  connect(ComboBox1, SIGNAL(activated(const QString &)), this, SLOT(slotComboBoxSelectionChanged(const QString &)));
  connect(LineEdit2, SIGNAL(edited()), this, SLOT(slotLineEditChanged()));
  connect(LineEdit1, SIGNAL(edited()), this, SLOT(slotNameChanged()));

  //connect(table, SIGNAL(signalChanged(int, int, Qstring)), this, SLOT(slotTableChanged(int, int, QString)));
}

ReactionsWidget1::~ReactionsWidget1()
{}

/* This function loads the reactions widget when its name is
   clicked in the tree   */
bool ReactionsWidget1::loadFromReaction(const CReaction* reaction)
{
  if (!reaction) return false;

  TextLabel8->setText(tr("Flux ("
                         + FROM_UTF8(CCopasiDataModel::Global->getModel()->getQuantityUnit())
                         + "/" + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnit()) + ")"));

  // this loads the reaction into a CReactionInterface object.
  // the gui works on this object and later writes back the changes to the reaction
  mRi.initFromReaction(*(CCopasiDataModel::Global->getModel()), reaction->getKey());

  // update the widget.
  FillWidgetFromRI();

  return true; //TODO: really check
}

bool ReactionsWidget1::saveToReaction()
{
  LineEdit2->slotForceUpdate();
  //std::cout << "SaveToReaction " << std::endl;
  if (!mRi.isValid()) return false;

  //first check if new metabolites need to be created
  bool createdMetabs = mRi.createMetabolites(*(CCopasiDataModel::Global->getModel()));

  mRi.setReactionName((const char *)LineEdit1->text().utf8());

  //this writes all changes to the reaction
  if (!mRi.writeBackToReaction(*(CCopasiDataModel::Global->getModel())))
    {
      CCopasiObject * pReaction = GlobalKeys.get(objKey);
      if (mRi.getReactionName() != pReaction->getObjectName())
        {
          QString msg;
          msg = "Unable to rename reaction '" + FROM_UTF8(pReaction->getObjectName()) + "'\n"
                + "to '" + FROM_UTF8(mRi.getReactionName()) + "' since a reation with that name already exists.";

          QMessageBox::warning(this,
                               "Unable to rename Reaction",
                               msg,
                               QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);

          mRi.setReactionName(pReaction->getObjectName());
          LineEdit1->setText(FROM_UTF8(mRi.getReactionName()));
        }
    }

  //CCopasiDataModel::Global->getModel()->compile();

  //this tells the gui what it needs to know.
  if (createdMetabs) protectedNotify(ListViews::METABOLITE, ListViews::ADD, "");
  protectedNotify(ListViews::REACTION, ListViews::CHANGE, objKey);

  //TODO: detect rename events (mRi.writeBackToReaction has to do this)

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  CCopasiDataModel::Global->changed();

  return true;
}

void ReactionsWidget1::slotBtnCancelClicked()
{enter(objKey);}

void ReactionsWidget1::slotBtnOKClicked()
{
  LineEdit2->slotForceUpdate();
  saveToReaction();
}

void ReactionsWidget1::slotCheckBoxClicked()
{
  LineEdit2->slotForceUpdate();

  // tell the reaction interface
  mRi.setReversibility(CheckBox->isChecked());

  // update the widget
  FillWidgetFromRI();
}

// the function has been changed
void ReactionsWidget1::slotComboBoxSelectionChanged(const QString & p2)
{
  // tell the reaction interface
  mRi.setFunction((const char *)p2.utf8());

  // update the widget
  FillWidgetFromRI();
}

/*This function is called when the "Chemical Reaction" LineEdit is changed.*/
void ReactionsWidget1::slotLineEditChanged()
{
  //std::string rName = (const char *)LineEdit1->text().utf8();

  std::string eq = (const char *)LineEdit2->text().utf8();

  //first check if the string is a valid equation
  if (!CChemEqInterface::isValidEq(eq))
    {
      //debugging
      //std::cout << "Not a valid equation!\n\n";
      return;  // abort further processing
    }

  // tell the reaction interface
  //mRi.setReactionName(rName);

  mRi.setChemEqString(eq);

  // update the widget
  FillWidgetFromRI();
}

void ReactionsWidget1::slotNameChanged()
{
  std::string rName = (const char *)LineEdit1->text().utf8();
  mRi.setReactionName(rName);
}

// added 5/19/04
void ReactionsWidget1::slotBtnNewClicked()
{
  std::string name = "reaction";
  int i = 0;
  while (!CCopasiDataModel::Global->getModel()->createReaction(name))
    {
      i++;
      name = "reaction_";
      name += QString::number(i).utf8();
    }
  protectedNotify(ListViews::REACTION, ListViews::ADD);
  enter(CCopasiDataModel::Global->getModel()->getReactions()[name]->getKey());
  //pListView->switchToOtherWidget(mKeys[row]);
}

// Just added 5/18/04
void ReactionsWidget1::slotBtnDeleteClicked()
{
  if (CCopasiDataModel::Global->getModel())
    {
      QString reacList = "Are you sure you want to delete the reaction?\n";
      reacList.append(FROM_UTF8(mRi.getReactionName()));

      int choice = QMessageBox::warning(this, "CONFIRM DELETE",
                                        reacList,
                                        "Continue", "Cancel", 0, 0, 1);

      switch (choice)
        {
        case 0:                                    // Yes or Enter
          {
            //unsigned C_INT32 size = CCopasiDataModel::Global->pFunctionDB->loadedFunctions().size();
            unsigned C_INT32 size = CCopasiDataModel::Global->getModel()->getReactions().size();
            //unsigned C_INT32 index = CCopasiDataModel::Global->pFunctionDB->loadedFunctions().getIndex(pFunction->getObjectName());
            unsigned C_INT32 index = CCopasiDataModel::Global->getModel()->getReactions().getIndex(mRi.getReactionName());
            //CCopasiDataModel::Global->getModel()->removeReaction(mKeys[ToBeDeleted[i]]);
            CCopasiDataModel::Global->getModel()->removeReaction(objKey);
            //enter(CCopasiDataModel::Global->pFunctionDB->loadedFunctions()[std::min(index, size - 1)]->getKey());

            // this invalidates the reaction interface
            // so that the writeBackToReactionFunction is not called
            // after deleting a reaction.
            mRi.setFunction("", true);
            if (size > 1)
              {
                enter(CCopasiDataModel::Global->getModel()->getReactions()[std::min(index, size - 2)]->getKey());
              }

            protectedNotify(ListViews::REACTION, ListViews::DELETE, objKey);

            break;
          }

        default:                                           // No or Escape
          break;
        }
    }
}

void ReactionsWidget1::FillWidgetFromRI()
{
  std::cout << "FillWidget " << std::endl;
  LineEdit1->setText(FROM_UTF8(mRi.getReactionName()));

  LineEdit2->setText(FROM_UTF8(mRi.getChemEqString()));

  CReaction* reac = dynamic_cast< CReaction * >(GlobalKeys.get(objKey));
  if (reac)
    LineEdit3->setText(QString::number(reac->getFlux()));
  else
    LineEdit3->setText("");

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
      ComboBox1->setCurrentText(FROM_UTF8(mRi.getFunctionName()));
      QToolTip::add(ComboBox1, FROM_UTF8(mRi.getFunctionDescription()));

      table->updateTable(mRi, *CCopasiDataModel::Global->getModel());
    }
  else
    table->initTable();

  //TODO isValid()
  commitChanges->setEnabled(mRi.isValid());
}

void ReactionsWidget1::slotTableChanged(int index, int sub, QString newValue)
{
  std::cout << "slotValueChanged " << index << " " << sub << " " << newValue << std::endl;

  // setValue
  if (mRi.getUsage(index) == "PARAMETER")
    {
      if (sub != 0) return;

      if (mRi.isLocalValue(index))
        mRi.setValue(index, newValue.toDouble()); // TODO: check
      else
        mRi.setGlobalParameter(index, (const char *)newValue.utf8());
    }
  else if (mRi.getUsage(index) == "VOLUME")
    {
      if (sub != 0) return;
      mRi.setCompartment(index, (const char *)newValue.utf8());
    }
  else
    {
      if (sub == 0) //here we assume that vector parameters cannot be edited
        {
          mRi.setMetab(index, (const char *)table->text(table->mIndex2Line[index], 3).utf8());
        }
    }

  // update the widget
  int rrr = table->currentRow();
  int ccc = table->currentColumn();
  FillWidgetFromRI();
  table->setCurrentCell(rrr, ccc);
}

void ReactionsWidget1::slotParameterStatusChanged(int index, bool local)
{
  if (local)
    mRi.setValue(index /*, 0.1*/);
  else
    mRi.setGlobalParameter(index, "unknown");

  // update the widget
  int rrr = table->currentRow();
  int ccc = table->currentColumn();
  FillWidgetFromRI();
  table->setCurrentCell(rrr, ccc);
}

void ReactionsWidget1::slotNewFunction()
{
  // FunctionWidget1 * fw = new FunctionWidget1(NULL);
  // fw->show();
  // TODO: we could think about calling the function widget as a dialogue here...

  std::string name = std::string("Kinetics_for_") + (const char *)LineEdit1->text().utf8();
  std::string nname = name;
  int i = 0;
  CFunction* pFunc;
  while (!(pFunc = CCopasiDataModel::Global->getFunctionList()->createFunction(nname, CFunction::UserDefined)))
    {
      i++;
      nname = name;
      nname += (const char *)QString::number(i).utf8();
    }
  std::cout << " *** created Function: " << nname << " : " << pFunc->getKey() << std::endl;
  protectedNotify(ListViews::FUNCTION, ListViews::ADD);

  pListView->switchToOtherWidget(0, pFunc->getKey());
}

bool ReactionsWidget1::update(ListViews::ObjectType objectType,
                              ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
      return loadFromReaction(dynamic_cast< CReaction * >(GlobalKeys.get(objKey)));
      break;

    default:
      break;
    }
  return true;
}

bool ReactionsWidget1::leave()
{
  return saveToReaction();
}

bool ReactionsWidget1::enter(const std::string & key)
{
  objKey = key;
  CReaction* reac = dynamic_cast< CReaction * >(GlobalKeys.get(key));

  if (reac) return loadFromReaction(reac);
  else return false;
}
