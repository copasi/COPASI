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
#include "model/model.h"
#include "function/CFunctionDB.h"
#include "function/CFunctionParameters.h"
#include "function/CFunctionParameter.h"
#include "utilities/CGlobals.h"

/*
 *  Constructs a ReactionsWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 */

ReactionsWidget1::ReactionsWidget1(QWidget *parent, const char * name, WFlags f)
    : QWidget(parent, name, f)

{
  if (!name)
    setName("ReactionsWidget1");
  resize(568, 479);
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
  commitChanges->setText(trUtf8("&Commit Changes"));
  Layout1->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("&Cancel Changes"));
  Layout1->addWidget(cancelChanges);

  newReaction = new QPushButton(this, "newReaction");
  newReaction->setText(trUtf8("&New Reaction"));
  Layout1->addWidget(newReaction);

  deleteReaction = new QPushButton(this, "deleteReaction");
  deleteReaction->setText(trUtf8("&Delete Reaction"));
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

  table = new QTable(this, "table");
  table->setNumCols(table->numCols() + 1); table->horizontalHeader()->setLabel(table->numCols() - 1, trUtf8("Value"));
  table->setNumRows(0);
  table->setNumCols(1);

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

  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
  connect(this, SIGNAL(signal_emitted(const QString &)), (ListViews*)parent, SLOT(slotReactionTableChanged(const QString &)));
  connect(CheckBox, SIGNAL(clicked()), this, SLOT(slotCheckBoxClicked()));
  connect(ComboBox1, SIGNAL(activated(const QString &)), this, SLOT(slotComboBoxSelectionChanged(const QString &)));
  connect(LineEdit2, SIGNAL(edited()), this, SLOT(slotLineEditChanged()));
  connect(newReaction, SIGNAL(clicked()), this, SLOT(slotBtnNewClicked()));
  connect(this, SIGNAL(new_reaction()), (ListViews*)parent, SLOT(slotNewReaction()));

  connect(this, SIGNAL(leaf(CModel*)), (ListViews*)parent, SLOT(loadReactionsNodes(CModel*)));
  connect(this, SIGNAL(updated()), (ListViews*)parent, SLOT(dataModelUpdated()));
}

ReactionsWidget1::~ReactionsWidget1()
{}

/*This function is used to connect this class to the listviews
    class to basically choose the right widget to display   */
int ReactionsWidget1::isName(QString setValue)
{
  if (mModel == NULL)
    {
      return 0;
    }

  if (mModel->getReactions().getIndex((std::string) setValue) != C_INVALID_INDEX)
    {
      loadName(setValue);
      name = setValue;
      return 1;
    }
  else
    return 0;
}

/*This function is to load the model for the reactions*/
void ReactionsWidget1::loadReactions(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
    }
}

/* This function loads the reactions widget when its name is
   clicked in the tree   */
void ReactionsWidget1::loadName(QString setValue)
{
  if (mModel == NULL)
    {
      return;
    }

  name = setValue;
  CReaction *reactn;
  CCopasiVectorNS < CReaction > & reactions = mModel->getReactions();
  reactn = reactions[(std::string)setValue.latin1()];
  TriLogic reversible;
  if (reactn->isReversible() == false)
    reversible = TriFalse;
  else
    reversible = TriTrue;

  const CCopasiVectorN < CFunction > & Functions =
    Copasi->pFunctionDB->suitableFunctions(reactn->getChemEq().getSubstrates().size(),
                                           reactn->getChemEq().getSubstrates().size(),
                                           reversible);
  //const CFunction *function;

  const CChemEq * chemEq;

  QHeader *tableHeader1 = table->horizontalHeader();
  QHeader *tableHeader2 = table->verticalHeader();

  ComboBox1->clear();

  LineEdit1->setText(reactn->getName().c_str());
  Reaction1_Name = new QString(reactn->getName().c_str());

  chemEq = & reactn->getChemEq();
  LineEdit2->setText(chemEq->getChemicalEquationConverted().c_str());

  LineEdit3->setText(QString::number(reactn->getFlux()));

  //function = &reactn->getFunction();  // function seems not to be used afterwards
  //function1 = &reactn->getFunction(); // function1 seems not to be used either
  //ComboBox1->insertItem(function->getName().c_str(), m);

  QStringList comboEntries;
  QString comboEntry;
  unsigned int temp2;

  for (temp2 = 0; temp2 < Functions.size(); temp2++)
    {
      const CFunction *function = Functions[temp2];
      comboEntry = function->getName().c_str();
      comboEntries.push_front(comboEntry);
    }

  ComboBox1->insertStringList(comboEntries, -1);
  CheckBox->setChecked(false);

  if (reactn->isReversible() == true)
    {
      CheckBox->setChecked(true);
    }

  table->setNumCols(1);

  //Required for the suitablefunctions comboBox.
  num_substrates = reactn->getId2Substrates().size();
  num_products = reactn->getId2Products().size();

  numrows = reactn->getId2Substrates().size() +
            reactn->getId2Products().size() +
            reactn->getId2Modifiers().size() +
            reactn->getId2Parameters().size();

  table->setNumRows(numrows);
  table->ensureCellVisible(numrows + 1, 0);

  tableHeader1->setLabel(0, "Value");
  table->setColumnWidth (0, 200);
  unsigned int line = 0;
  unsigned int l;
  unsigned int k;

  CCopasiVector < CReaction::CId2Metab > & react1z = reactn->getId2Substrates();
  const CCopasiVector < CChemEqElement > * react1 = &reactn->getChemEq().getSubstrates();
  const CChemEqElement *cchem;
  int z = 0;

  for (k = 0; k < react1z.size(); k++)
    {
      tableHeader2->setLabel(line, react1z[k]->getIdentifierName().c_str());

      //for the combo box
      QStringList comboEntries1;

      for (l = 0; l < react1->size(); l++)
        {
          cchem = (*react1)[l];
          QString overall = cchem->getMetaboliteName().c_str();
          overall += "{";
          overall += cchem->getMetabolite().getCompartment()->getName().c_str();
          overall += "}";
          comboEntries1.push_back(overall);
        }

      QString temp = comboEntries1[z];
      //comboEntries1.push_front(temp);
      QComboTableItem * item = new QComboTableItem(table, comboEntries1, false);
      item->setCurrentItem(temp);
      //item = QComboTableItem(table, comboEntries1, false);
      /*if(comboEntries1.contains(temp)>1)
      {
      comboEntries1.remove(temp);
      }*/ 
      //item->setStringList(comboEntries1);
      z++;
      table->setItem(line, 0, item);
      line++;
    }

  CCopasiVector < CReaction::CId2Metab > & react2z = reactn->getId2Products();
  const CCopasiVector < CChemEqElement > * react2 = &reactn->getChemEq().getProducts();
  z = 0;

  for (k = 0; k < react2z.size(); k++)
    {
      tableHeader2->setLabel(line, react2z[k]->getIdentifierName().c_str());

      //for the combo box
      QStringList comboEntries1;

      for (l = 0; l < react2->size(); l++)
        {
          cchem = (*react2)[l];
          QString overall = cchem->getMetaboliteName().c_str();
          overall += "{";
          overall += cchem->getMetabolite().getCompartment()->getName().c_str();
          overall += "}";
          comboEntries1.push_back(overall);
        }

      QString temp = comboEntries1[z];
      QComboTableItem * item = new QComboTableItem(table, comboEntries1, false);
      item->setCurrentItem(temp);
      z++;
      table->setItem(line, 0, item);
      line++;
    }

  const CCopasiVector < CReaction::CId2Metab > & react3z = reactn->getId2Modifiers();
  const CCopasiVectorN< CMetab > & Metabolites = mModel->getMetabolites();
  const CMetab * Metabolite;
  z = 0;

  for (k = 0; k < react3z.size(); k++)
    {
      tableHeader2->setLabel(line, react3z[k]->getIdentifierName().c_str());

      //for the combo box
      QStringList comboEntries1;

      for (l = 0; l < Metabolites.size(); l++)
        {
          Metabolite = Metabolites[l];
          QString overall = Metabolite->getName().c_str();
          overall += "{";
          overall += Metabolite->getCompartment()->getName().c_str();
          overall += "}";
          comboEntries1.push_back(overall);
        }

      QString temp = comboEntries1[z];
      QComboTableItem * item = new QComboTableItem(table, comboEntries1, false);
      item->setCurrentItem(temp);
      z++;
      table->setItem(line, 0, item);
      line++;
    }

  CCopasiVector < CReaction::CId2Param > & react4z = reactn->getId2Parameters();

  for (k = 0; k < react4z.size(); k++)
    {
      tableHeader2->setLabel(line, react4z[k]->getIdentifierName().c_str());
      table->clearCell(line, 0);
      table->setText(line, 0, QString::number(react4z[k]->getValue()));
      line++;
    }
  if (&reactn->getFunction())
    ComboBox1->setCurrentText(reactn->getFunction().getName().c_str());

  //  slotComboBoxSelectionChanged(reactn->getFunction().getName().c_str());
  //emit sideySignal();
}

/*This slot is activated when the cancel button is clicked.It basically cancels any changes that
  are made.It does this by emiiting a signal whcih si connected to the listviews and it reloads 
  the widget with the initial values.*/
void ReactionsWidget1::slotBtnCancelClicked()
{
  //QMessageBox::information(this, "Reactions Widget", "Do you really want to cancel changes");
  emit signal_emitted(*Reaction1_Name);
}

/*This slot is connected to the commit changes button.There is a difference between commit
  changes and save changes using the icon on the toolbar, but I am not sure  what each one 
  does and what is the difference between them.Have to ask Dr Hoops about it.*/
void ReactionsWidget1::slotBtnOKClicked()
{
  /*This code is to save the changes in the reaction*/
  CCopasiVectorNS < CReaction > & reactions = mModel->getReactions();
  CReaction *reactn2;
  reactn2 = reactions[(std::string)name.latin1()];
  reactn2->setName(std::string(LineEdit1->text()));
  name = LineEdit1->text();
  emit updated();
  emit leaf(mModel);
  emit signal_emitted(*Reaction1_Name);
  //   CChemEq * chem;
  //   chem = & reactn1->getChemEq();
  //   chem->setChemicalEquation(chemical_reaction->latin1());
  //   reactn1->setChemEq(chemical_reaction->latin1());
  //   reactn1->save(*Rtn);
  //   Copasi->Model->save(*Rtn);
}

/*This slot is activated when the check box is clicked.It needs to have functionality to
  make and update changes in the "Chemical Reaction" Text box and the "Kinetics" Combobox.*/

void ReactionsWidget1::slotCheckBoxClicked()
{
  CCopasiVectorNS < CReaction > & reactions = mModel->getReactions();
  reactn1 = reactions[(std::string)name.latin1()];
  const CChemEq * chemEq1;

  chemEq1 = & reactn1->getChemEq();
  std::string chemEq2 = chemEq1->getChemicalEquationConverted();
  QString chemical_reaction = chemEq2.c_str();
  TriLogic reversible;
  if (reactn1->isReversible())
    {
      reversible = TriTrue;
    }
  else
    {
      reversible = TriFalse;
    }

  if (CheckBox->isChecked() == false && reactn1->isReversible() == true)
    {
      int i = chemical_reaction.find ("=", 0, true);
      chemical_reaction = chemical_reaction.replace(i, 1, "->");
      reversible = TriFalse;
    }
  else if (CheckBox->isChecked() == true && reactn1->isReversible() == false)
    {
      int i = chemical_reaction.find ("->", 0, true);
      chemical_reaction = chemical_reaction.replace(i, 2, "=");
      reversible = TriTrue;
    }
  const std::string chemEq3 = chemical_reaction.latin1();
  //chemEq1->setChemicalEquation(chemEq3); //is this really necessary?
  reactn1->setChemEq(chemEq3);

  LineEdit2->setText(chemEq1->getChemicalEquationConverted().c_str());

  ComboBox1->clear();
  const CCopasiVectorN < CFunction > & Functions =
    Copasi->pFunctionDB->suitableFunctions(reactn1->getChemEq().getSubstrates().size(),
                                           reactn1->getChemEq().getSubstrates().size(),
                                           reversible);
  QStringList comboEntries;
  QString comboEntry;
  unsigned int temp2;

  for (temp2 = 0; temp2 < Functions.size(); temp2++)
    {
      const CFunction *function = Functions[temp2];
      comboEntry = function->getName().c_str();
      comboEntries.push_back(comboEntry);
    }

  ComboBox1->insertStringList(comboEntries, -1);
  QString comboValue = ComboBox1->currentText();
  slotComboBoxSelectionChanged(comboValue);
  //QMessageBox::information(this, "Reactions Widget", "You need to change the Chemical Equation and a select a new Kinetics type");
}

void ReactionsWidget1::slotComboBoxSelectionChanged(const QString & p2)
{
  const std::string & p1 = p2.latin1();
  CFunction * function = Copasi->pFunctionDB->findLoadFunction(p1);
  CFunctionParameters &functionParameters = function->getParameters();

  int count_substrates = 0;
  int count_products = 0;
  int count_parameters = 0;
  int count_modifiers = 0;

  std::string usagetypes[20];
  std::string substrate_name[20];
  std::string product_name[20];
  std::string modifier_name[20];
  std::string parameter_name[20];
  unsigned int count = 0;

  //for clearing the values of the table
  for (count = 0; count < table->numRows(); count++)
    {
      table->clearCell(count, 0);
    }

  unsigned int z = 0;
  unsigned int line = 0;
  QStringList comboEntries1;
  QStringList substrates;
  QStringList products;
  QString chemical_reaction = LineEdit2->text();
  //unsigned int start = 0;
  QStringList individual_elements = QStringList::split ("+", chemical_reaction, false);
  QString all_elements = individual_elements.join (" ");
  QStringList individual_elements1 = QStringList::split (" ", all_elements, false);

  unsigned int m, n;
  for (m = 0; m <= individual_elements1.size() - 1; m++)
    {
      if ((individual_elements1[m] == "->") || (individual_elements1[m] == "="))
        {
          m++;
          break;
        }
      substrates.push_back(individual_elements1[m]);
      //substrates[start] = individual_elements1[m];
      // QMessageBox::information(this, substrates[start], "substrates ");
      //start++;
    }

  // start = 0;
  for (n = m; n <= individual_elements1.size() - 1; n++)
    {
      if (individual_elements1[m] == "+")
        {
          n++;
          break;
        }
      products.push_back(individual_elements1[n]);
      //products[start] = individual_elements1[n];
      //QMessageBox::information(this, products[start], "products ");
      //start++;
    }
  unsigned int i;
  for (i = 0; i < functionParameters.size(); i++)
    {
      std::string p4 = functionParameters[i]->getUsage();
      usagetypes[i] = p4;

      if (p4 == "SUBSTRATE")
        {
          substrate_name[count_substrates] = functionParameters[i]->getName();
          count_substrates++;
        }
      else if (p4 == "PRODUCT")
        {
          product_name[count_products] = functionParameters[i]->getName();
          count_products++;
        }
      else if (p4 == "MODIFIER")
        {
          modifier_name[count_modifiers] = functionParameters[i]->getName();
          count_modifiers++;
        }

      else if (p4 == "PARAMETER")
        {
          parameter_name[count_parameters] = functionParameters[i]->getName();
          count_parameters++;
        }

      count = 0;
      unsigned int index = count_substrates;
      unsigned int countofsubstrates = count_substrates;
      unsigned int countofproducts = count_products;
      QHeader *tableHeader2 = table->verticalHeader();

      int index1;
      for (index1 = 0; index1 <= (count_products - 1); index1++)
        {
          substrate_name[index] = product_name[index1];
          index++;
        }

      for (index1 = 0; index1 <= (count_modifiers - 1); index1++)
        {
          substrate_name[index] = modifier_name[index1];
          index++;
        }

      for (index1 = 0; index1 <= (count_parameters - 1); index1++)
        {
          substrate_name[index] = parameter_name[index1];
          index++;
        }

      unsigned int length = index - 1;
      table->setNumRows(index);
      for (; count <= length; count++)
        {
          tableHeader2->setLabel(count, substrate_name[count].c_str());
        }

      unsigned int z = 0;
      unsigned int k;
      unsigned int line = 0;
      QString temp;
      for (k = 1; k <= countofsubstrates; k++)
        {
          QComboTableItem * item1 = new QComboTableItem(table, substrates, true);
          table->setItem(line, 0, item1);
          temp = substrates[z];
          item1->setCurrentItem(temp);
          z++;
          line++;
        }

      z = 0;
      for (k = 1; k <= countofproducts; k++)
        {
          QComboTableItem * item1 = new QComboTableItem(table, products, true);
          table->setItem(line, 0, item1);
          temp = products[z];
          item1->setCurrentItem(temp);
          z++;
          line++;
        }

      //std::vector < CMetab * > metabolites = mModel->getMetabolites();
      //  C_INT32 noOfMetabolitesRows = metabolites.size();
      //  CMetab *metab;
      //  QStringList comboEntries1;
      //  for (C_INT32 j = 0; j < noOfMetabolitesRows; j++)
      // {
      //     metab = metabolites[j];
      // comboEntries1.push_back(metab->getName().c_str());
      //}
      for (index1 = 0; index1 <= (count_modifiers - 1); index1++)
        {
          table->setText(line, 0, "1");
          line++;
        }

      for (index1 = 0; index1 <= (count_parameters - 1); index1++)
        {
          table->setText(line, 0, "1");
          line++;
        }
    }
}

/*This function is called when the "Chemical Reaction" LineEdit is changed.*/
void ReactionsWidget1::slotLineEditChanged()
{
  const QString & chemreactn = LineEdit2->text();
  const std::string & changed_chemical_reaction = chemreactn.latin1();
  CCopasiVectorNS < CReaction > & reactions1 = mModel->getReactions();
  CReaction *reactn1;
  reactn1 = reactions1[(std::string)name];
  const CChemEq * chemEq1;
  chemEq1 = & reactn1->getChemEq();
  //bool status;
  //status = chemEq1->setChemicalEquation(changed_chemical_reaction); //is this necessary?
  reactn1->setChemEq(changed_chemical_reaction);
  if (reactn1->isReversible() == true)
    {
      CheckBox->setChecked(true);
    }
  else
    {
      CheckBox->setChecked(false);
    }
  slotCheckBoxClicked();
}

void ReactionsWidget1::slotBtnNewClicked()
{
  // QMessageBox::information(this, "Reactions Widget", "adding a new reaction");
  emit new_reaction();
}
