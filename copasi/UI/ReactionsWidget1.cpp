// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

/*********************************************************************
 **  $ CopasiUI/ReactionsWidget1.cpp
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the  information
 ** obtained from the data model about the Recations----It is Basically
 ** the Second level of Reactions.
 **********************************************************************/

#include <QWidget>

#include "copasi.h"
#include "ReactionsWidget1.h"
#include "listviews.h"
#include "parametertable.h"
#include "MyLineEdit.h"
#include "qtUtilities.h"
#include "ChemEqValidator.h"
#include "FunctionWidget1.h"
#include "CQMessageBox.h"

#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "function/CFunctionDB.h"
#include "function/CFunctionParameters.h"
#include "function/CFunctionParameter.h"
#include "report/CKeyFactory.h"

/*
 *  Constructs a ReactionsWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */

ReactionsWidget1::ReactionsWidget1(QWidget *parent, const char * name, Qt::WFlags f)
  : CopasiWidget(parent, name, f),
    mpRi(NULL),
    mKeyToCopy("")
{
  if (!name)
    setName("ReactionsWidget1");

  setCaption(trUtf8("ReactionsWidget1"));

  ReactionsWidget1Layout = new QGridLayout(this);
  ReactionsWidget1Layout->setMargin(11);
  ReactionsWidget1Layout->setSpacing(6);
  ReactionsWidget1Layout->setObjectName("ReactionsWidget1Layout");

  TextLabel7 = new QLabel(this, "TextLabel7");
  TextLabel7->setText(trUtf8("Symbol Definition"));
  TextLabel7->setAlignment(int(Qt::AlignVCenter
                               | Qt::AlignRight));
  ReactionsWidget1Layout->addWidget(TextLabel7, 8, 0);

  Line2 = new QFrame(this, "Line2");
  Line2->setFrameShape(QFrame::HLine);
  Line2->setFrameShadow(QFrame::Sunken);
  Line2->setFrameShape(QFrame::HLine);
  ReactionsWidget1Layout->addMultiCellWidget(Line2, 7, 7, 0, 3);

  // kinetics line
  TextLabel6 = new QLabel(this, "TextLabel6");
  TextLabel6->setText(trUtf8("Rate Law"));
  TextLabel6->setAlignment(int(Qt::AlignVCenter
                               | Qt::AlignRight));
  ReactionsWidget1Layout->addWidget(TextLabel6, 5, 0);

  ComboBox1 = new QComboBox(false, this, "ComboBox1");
  ReactionsWidget1Layout->addMultiCellWidget(ComboBox1, 5, 5, 1, 2);

  newKinetics = new QPushButton(this, "newKinetics");
  newKinetics->setText(trUtf8("&New Rate Law"));
  ReactionsWidget1Layout->addWidget(newKinetics, 5, 3);

  TextLabel8 = new QLabel(this, "TextLabel8");
  TextLabel8->setText(trUtf8("Flux"));
  TextLabel8->setAlignment(int(Qt::AlignVCenter
                               | Qt::AlignRight));
  ReactionsWidget1Layout->addWidget(TextLabel8, 6, 0);

  QPushButton* editKinetics = new QPushButton(this, "editKinetics");
  editKinetics->setText(trUtf8("&Edit Rate Law"));
  ReactionsWidget1Layout->addWidget(editKinetics, 6, 3);
  
  connect(editKinetics, SIGNAL(clicked()), this, SLOT(slotGotoFunction()));

  
  LineEdit3 = new QLineEdit(this, "LineEdit3");
  LineEdit3->setEnabled(false);
  ReactionsWidget1Layout->addMultiCellWidget(LineEdit3, 6, 6, 1, 2);

  // equation line
  TextLabel5 = new QLabel(this, "TextLabel5");
  TextLabel5->setText(trUtf8("Reaction"));
  TextLabel5->setAlignment(int(Qt::AlignVCenter
                               | Qt::AlignRight));
  ReactionsWidget1Layout->addWidget(TextLabel5, 2, 0);

  LineEdit2 = new MyLineEdit(this, "LineEdit2");
  LineEdit2->setValidator(new ChemEqValidator(LineEdit2));
  ReactionsWidget1Layout->addMultiCellWidget(LineEdit2, 2, 2, 1, 3);

  CheckBox = new QCheckBox(this, "CheckBox");
  CheckBox->setText(trUtf8("Reversible"));
  ReactionsWidget1Layout->addWidget(CheckBox, 3, 1);

  mpMultiCompartment = new QCheckBox(this, "mpMultiCompartment");
  mpMultiCompartment->setText(trUtf8("Multi Compartment"));
  mpMultiCompartment->setEnabled(false);
  ReactionsWidget1Layout->addWidget(mpMultiCompartment, 3, 2);

  Line4 = new QFrame(this, "Line4");
  Line4->setFrameShape(QFrame::HLine);
  Line4->setFrameShadow(QFrame::Sunken);
  Line4->setFrameShape(QFrame::HLine);
  ReactionsWidget1Layout->addMultiCellWidget(Line4, 4, 4, 0, 3);

  table = new ParameterTable(this, "table");
  table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  ReactionsWidget1Layout->addMultiCellWidget(table, 8, 9, 1, 3);
  ReactionsWidget1Layout->setRowStretch(9, 10);

  QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  ReactionsWidget1Layout->addItem(spacer, 10, 0);
  //ReactionsWidget1Layout->setRowStretch(10,1);

  setTabOrder(LineEdit2, CheckBox);
  setTabOrder(CheckBox, mpMultiCompartment);
  setTabOrder(mpMultiCompartment, ComboBox1);
  setTabOrder(ComboBox1, newKinetics);
  setTabOrder(newKinetics, table);

  connect(newKinetics, SIGNAL(clicked()), this, SLOT(slotNewFunction()));

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
  if (!reaction) return false;

  // this loads the reaction into a CReactionInterface object.
  // the gui works on this object and later writes back the changes to the reaction
  pdelete(mpRi);
  mpRi = new CReactionInterface((*CCopasiRootContainer::getDatamodelList())[0]->getModel());

  mpRi->initFromReaction(reaction->getKey());

  // update the widget.
  FillWidgetFromRI();

  return true; //TODO: really check
}

bool ReactionsWidget1::saveToReaction()
{
  CReaction* reac = dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (reac == NULL) return true;

  if (!LineEdit2->isValid()) return false;

  LineEdit2->slotForceUpdate();

  if (!mpRi->isValid()) return false;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL) return false;

  // Before we save any changes we must check whether any local reaction parameters,
  // which are used in any mathematical expression in the model are removed.
  // If that is the case the user must have option to cancel the changes or remove the
  // affected expressions.
  std::set< const CCopasiObject * > DeletedParameters = mpRi->getDeletedParameters();

  if (DeletedParameters.size() != 0)
    {
      QString ObjectType = "parameter(s)";
      QString Objects;

      std::set< const CCopasiObject * >::const_iterator itParameter, endParameter = DeletedParameters.end();
      std::set< const CCopasiObject * > DeletedObjects;

      for (itParameter = DeletedParameters.begin(); itParameter != endParameter; ++itParameter) //all parameters
        {
          Objects.append(FROM_UTF8((*itParameter)->getObjectName()) + ", ");
          DeletedObjects.insert(static_cast< const CCopasiObject * >((*itParameter)->getObject(CCopasiObjectName("Reference=Value"))));
        }

      Objects.remove(Objects.length() - 2, 2);

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(NULL, ObjectType,
                                    Objects, DeletedObjects);

      switch (choice)
        {
          case QMessageBox::Ok:

            for (itParameter = DeletedParameters.begin(); itParameter != endParameter; ++itParameter) //all parameters
              pModel->removeLocalReactionParameter((*itParameter)->getKey());

            protectedNotify(ListViews::REACTION, ListViews::DELETE, "");
            break;

          default:
            return true;
            break;
        }
    }

  // We need to check whether the current reaction still exists, since it is possible that
  // removing a local reaction parameter triggers its deletion.
  reac = dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (reac == NULL)
    {
      mpRi->setFunctionWithEmptyMapping("");

      protectedNotify(ListViews::REACTION, ListViews::DELETE, mKey);
      protectedNotify(ListViews::REACTION, ListViews::DELETE, ""); //Refresh all as there may be dependencies.
      return true;
    }

  //first check if new metabolites need to be created
  bool createdMetabs = mpRi->createMetabolites();
  bool createdObjects = mpRi->createOtherObjects();

  //this writes all changes to the reaction
  mpRi->writeBackToReaction(reac);

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  //(*CCopasiRootContainer::getDatamodelList())[0]->getModel()->compile();

  //this tells the gui what it needs to know.
  if (createdObjects)
    protectedNotify(ListViews::MODEL, ListViews::CHANGE, "");
  else
    {
      if (createdMetabs) protectedNotify(ListViews::METABOLITE, ListViews::ADD, "");

      // :TODO Bug 322: This should only be called when actual changes have been saved.
      if (this->isShown())
        protectedNotify(ListViews::REACTION, ListViews::CHANGE, mKey);
    }

  //TODO: detect rename events (mpRi->writeBackToReaction has to do this)

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  if (this->isShown())
    (*CCopasiRootContainer::getDatamodelList())[0]->changed();

  return true;
}

void ReactionsWidget1::slotCheckBoxClicked()
{
  LineEdit2->slotForceUpdate();

  // tell the reaction interface
  mpRi->setReversibility(CheckBox->isChecked(), "");

  // update the widget
  FillWidgetFromRI();
}

// the function has been changed
void ReactionsWidget1::slotComboBoxSelectionChanged(const QString & p2)
{
  // tell the reaction interface
  mpRi->setFunctionAndDoMapping(TO_UTF8(p2));

  // update the widget
  FillWidgetFromRI();
}

/*This function is called when the "Chemical Reaction" LineEdit is changed.*/
void ReactionsWidget1::slotLineEditChanged()
{
  //std::string rName = TO_UTF8(LineEdit1->text());

  std::string eq = TO_UTF8(LineEdit2->text());

  //first check if the string is a valid equation
  if (!CChemEqInterface::isValidEq(eq))
    {
      return;  // abort further processing
    }

  // tell the reaction interface
  //mpRi->setReactionName(rName);

  mpRi->setChemEqString(eq, "");

  // update the widget
  FillWidgetFromRI();
}

// added 5/19/04
void ReactionsWidget1::slotBtnNew()
{
  std::string name = "reaction_1";
  size_t i = 1;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  while (!pDataModel->getModel()->createReaction(name))
    {
      i++;
      name = "reaction_";
      name += TO_UTF8(QString::number(i));
    }

  std::string key = pDataModel->getModel()->getReactions()[name]->getKey();
  protectedNotify(ListViews::REACTION, ListViews::ADD, key);
//  enter(key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void ReactionsWidget1::slotBtnCopy()
{
  mKeyToCopy = mKey;
}

// Just added 5/18/04
void ReactionsWidget1::slotBtnDelete()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  CReaction * pReaction =
    dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (pReaction == NULL) return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(NULL, "reaction",
                                FROM_UTF8(pReaction->getObjectName()),
                                pReaction->getDeletedObjects());

  switch (choice)
    {
      case QMessageBox::Ok:                                                     // Yes or Enter
      {
        pDataModel->getModel()->removeReaction(mKey);

        mpRi->setFunctionWithEmptyMapping("");

        protectedNotify(ListViews::REACTION, ListViews::DELETE, mKey);
        protectedNotify(ListViews::REACTION, ListViews::DELETE, "");//Refresh all as there may be dependencies.
        break;
      }

      default:                                                     // No or Escape
        break;
    }
}

void ReactionsWidget1::FillWidgetFromRI()
{
  LineEdit2->setText(FROM_UTF8(mpRi->getChemEqString()));

  setFramework(mFramework);

  // the reversibility checkbox
  CheckBox->setChecked(false);

  if (mpRi->isReversible() == true)
    {
      CheckBox->setChecked(true);
    }

  mpMultiCompartment->setChecked(mpRi->isMulticompartment());

  // the function combobox
  QStringList comboEntries;
  vectorOfStrings2QStringList(mpRi->getListOfPossibleFunctions(), comboEntries);

  ComboBox1->clear();
  ComboBox1->insertStringList(comboEntries, -1);

  // if there is a current function the parameter table is initialized
  if (mpRi->getFunctionName() != "")
    {
      if (comboEntries.grep(FROM_UTF8(mpRi->getFunctionName())).size() == 0)
        ComboBox1->insertItem(FROM_UTF8(mpRi->getFunctionName()));

      ComboBox1->setCurrentText(FROM_UTF8(mpRi->getFunctionName()));
      ComboBox1->setToolTip(FROM_UTF8(mpRi->getFunctionDescription()));

      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      table->updateTable(*mpRi, *(*CCopasiRootContainer::getDatamodelList())[0]->getModel());
    }
  else
    {
      ComboBox1->insertItem("undefined");
      ComboBox1->setCurrentText("undefined");
      table->initTable();
    }
}

void ReactionsWidget1::slotTableChanged(int index, int sub, QString newValue)
{
  size_t Index = index;
  bool SkipFillWidget = false;

  // setValue
  if (mpRi->getUsage(Index) == CFunctionParameter::PARAMETER)
    {
      if (sub != 0) return;

      if (mpRi->isLocalValue(Index))
        {
          mpRi->setLocalValue(Index, newValue.toDouble()); // TODO: check
          SkipFillWidget = true;
        }
      else
        mpRi->setMapping(Index, TO_UTF8(newValue));
    }
  else if (mpRi->getUsage(Index) == CFunctionParameter::VOLUME)
    {
      if (sub != 0) return;

      mpRi->setMapping(Index, TO_UTF8(newValue));
    }
  else
    {
      if (sub == 0) //here we assume that vector parameters cannot be edited
        {
          mpRi->setMapping((int) Index, TO_UTF8(table->text((int) table->mIndex2Line[index], 3)));
        }
    }

  // update the widget
  int rrr = table->currentRow();
  int ccc = table->currentColumn();

  // We must avoid this call when only a local parameter value is changed.
  if (!SkipFillWidget)
    FillWidgetFromRI();

  table->setCurrentCell(rrr, ccc);
}

void ReactionsWidget1::slotParameterStatusChanged(int index, bool local)
{
  if (local)
    mpRi->setLocal(index);
  else
    mpRi->setMapping(index, "unknown"); //TODO keep global parameter

  // update the widget
  int rrr = table->currentRow();
  int ccc = table->currentColumn();
  FillWidgetFromRI();
  table->setCurrentCell(rrr, ccc);
}


void ReactionsWidget1::slotGotoFunction()
{
  CReaction * pReaction =
    dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mKey));
  if (pReaction == NULL) return;
  const CFunction * pFunc = pReaction->getFunction();
  if (pFunc == NULL) return;
  
  mpListView->switchToOtherWidget(C_INVALID_INDEX, pFunc->getKey());
  
}

void ReactionsWidget1::slotNewFunction()
{
  // FunctionWidget1 * fw = new FunctionWidget1(NULL);
  // fw->show();
  // TODO: we could think about calling the function widget as a dialogue here...

  std::string name = std::string("Rate Law for ") + mpObject->getObjectName();
  std::string nname = name;
  size_t i = 0;
  CCopasiVectorN<CFunction>& FunctionList
    = CCopasiRootContainer::getFunctionList()->loadedFunctions();
  CFunction* pFunc;

  while (FunctionList.getIndex(nname) != C_INVALID_INDEX)
    {
      i++;
      nname = name + "_";
      nname += TO_UTF8(QString::number(i));
    }

  CCopasiRootContainer::getFunctionList()->add(pFunc = new CKinFunction(nname), true);
  protectedNotify(ListViews::FUNCTION, ListViews::ADD, pFunc->getKey());

  mpListView->switchToOtherWidget(C_INVALID_INDEX, pFunc->getKey());
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
        return loadFromReaction(dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mKey)));
        break;

      default:
        break;
    }

  return true;
}

bool ReactionsWidget1::leave()
{
  saveToReaction();
  return true; //always return true. That means that the widget can be
  //left without saving
}

bool ReactionsWidget1::enterProtected()
{
  CReaction* reac = NULL;

  if (mKeyToCopy != "")
    {
      reac = dynamic_cast<CReaction *>(CCopasiRootContainer::getKeyFactory()->get(mKeyToCopy));
      mKeyToCopy = "";
    }
  else
    {
      reac = dynamic_cast< CReaction * >(mpObject);
    }

  if (reac)
    return loadFromReaction(reac);

  mpListView->switchToOtherWidget(114, "");
  return false;
}

void ReactionsWidget1::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);

  const CReaction * pReaction = dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  const CModel * pModel = NULL;

  if (pReaction != NULL)
    pModel = dynamic_cast<const CModel *>(pReaction->getObjectAncestor("Model"));

  QString Units;

  switch (mFramework)
    {
      case 0:

        if (pModel)
          Units = FROM_UTF8(pModel->getQuantityRateUnitsDisplayString());

        if (!Units.isEmpty())
          Units = " (" + Units + ")";

        TextLabel8->setText("Flux" + Units);

        if (pReaction != NULL)
          LineEdit3->setText(QString::number(pReaction->getFlux(), 'g', 10));

        break;

      case 1:

        if (pModel)
          Units = FROM_UTF8(pModel->getFrequencyUnitsDisplayString());

        if (!Units.isEmpty())
          Units = " (" + Units + ")";

        TextLabel8->setText("Particle Flux" + Units);

        if (pReaction != NULL)
          LineEdit3->setText(QString::number(pReaction->getParticleFlux(), 'g', 10));

        break;
    }
}
