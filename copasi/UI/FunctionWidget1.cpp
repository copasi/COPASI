// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/FunctionWidget1.cpp,v $
//   $Revision: 1.177 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/13 19:21:58 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "FunctionWidget1.h"

#include "copasi.h"
#include "listviews.h"
#include "CQMessageBox.h"
#include "FunctionWidget1.h"
#include "qtUtilities.h"
#include "CTabWidget.h"

#include "tex/CMathMLToTeX.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
#include "model/CModel.h"
#include "utilities/CCopasiException.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "function/CKinFunction.h"
#include "report/CKeyFactory.h"
#include "utilities/CDimension.h"

#include "CopasiFileDialog.h"

#include <QComboBox>
#include <QToolTip>

#define COL_NAME 0
#define COL_USAGE 1
#define COL_UNIT 2

/*
 *  Constructs a CScanWidgetScan as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
FunctionWidget1::FunctionWidget1(QWidget* parent, const char* name, Qt::WindowFlags fl):
    CopasiWidget(parent, name, fl),
    flagChanged(false),
    isValid(false),
    mIgnoreFcnDescriptionChange(false),
    mpFunction(NULL)
{
  setupUi(this);

  init();
}

//! Destructor
FunctionWidget1::~FunctionWidget1()
{
  //pdelete(mMmlWidget);
  //pdelete(mScrollView);
  pdelete(mpFunction);
}

void FunctionWidget1::init()
{
  // change the default signal-slot connection
  // disconnect(mpExpressionEMSW->mpExpressionWidget,
  //            SIGNAL(textChanged()),
  //            mpExpressionEMSW->mpExpressionWidget,
  //            SLOT(slotTextChanged()));
  mpExpressionEMSW->mpExpressionWidget->setFunction("");
  connect(mpExpressionEMSW->mpExpressionWidget->getValidator(), SIGNAL(stateChanged(bool)), this, SLOT(slotFcnDescriptionChanged(bool)));

  // hide all unnecessary buttons
  mpExpressionEMSW->mpBtnExpressionObject->hide();
  // mpExpressionEMSW->mpBtnViewExpression->hide();

  // overwrite the tip
  mpExpressionEMSW->mpBtnSaveExpression->setToolTip(tr("save formula"));
  mpExpressionEMSW->mpBtnEditExpression->setToolTip(tr("edit formula"));

  mpFunction = NULL;
}

bool FunctionWidget1::loadParameterTable()
{
  QColor subsColor(255, 210, 210);
  QColor prodColor(210, 255, 210);
  QColor modiColor(250, 250, 190);
  QColor paraColor(210, 210, 255);
  QColor volColor(210, 210, 255);
  QColor timeColor(210, 210, 210);
  QColor color;

  size_t i, j;
  CFunctionParameters & params = mpFunction->getVariables();

  // list of usages for combobox
  QStringList Usages;

  for (i = 0; CFunctionParameter::RoleNameDisplay[i] != ""; i++)
    {
      if (dynamic_cast<CKinFunction *>(mpFunction) &&
          CFunctionParameter::VARIABLE == (CFunctionParameter::Role) i) continue;

      Usages += (FROM_UTF8(CFunctionParameter::RoleNameDisplay[i]));
    }

  //create list of data types (for combobox)
  QStringList functionType;

  for (i = 0; CFunctionParameter::DataTypeName[i] != ""; i++)
    functionType += (FROM_UTF8(CFunctionParameter::DataTypeName[i]));

  //find parameter units
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  CFindDimensions ddd(mpFunction, pModel->getQuantityUnitEnum() == CModel::dimensionlessQuantity,
                      pModel->getVolumeUnitEnum() == CModel::dimensionlessVolume,
                      pModel->getTimeUnitEnum() == CModel::dimensionlessTime,
                      pModel->getAreaUnitEnum() == CModel::dimensionlessArea,
                      pModel->getLengthUnitEnum() == CModel::dimensionlessLength
                     );

  ddd.setUseHeuristics(true);
  std::vector<std::string> units = ddd.findDimensionsBoth(pDataModel);

  CFunctionParameter::Role usage;
  QString qUsage;

  //C_INT32 noOffunctParams = functParam.size();
  Table1->setRowCount((int) params.size());

  for (j = 0; j < params.size(); j++)
    {
      usage = params[j]->getUsage();

      if (usage == CFunctionParameter::VARIABLE &&
          dynamic_cast<CKinFunction *>(mpFunction))
        {
          usage = CFunctionParameter::PARAMETER;
          params[j]->setUsage(usage);
        }

      qUsage = FROM_UTF8(CFunctionParameter::RoleNameDisplay[usage]);

      switch (usage)
        {
          case CFunctionParameter::SUBSTRATE:
            color = subsColor;
            break;
          case CFunctionParameter::PRODUCT:
            color = prodColor;
            break;
          case CFunctionParameter::MODIFIER:
            color = modiColor;
            break;
          case CFunctionParameter::PARAMETER:
            color = paraColor;
            break;
          case CFunctionParameter::VOLUME:
            color = volColor;
            break;
          case CFunctionParameter::TIME:
            color = timeColor;
            break;
          case CFunctionParameter::VARIABLE:
            color = QColor(250, 250, 250);
            break;
          default :
            qUsage = "unknown";
            color = QColor(255, 20, 20);
        }

      // col. 0 (name)
      QString Name = FROM_UTF8(params[j]->getObjectName());

      if (!params[j]->isUsed())
        Name += " (unused)";

      if (Table1->item((int) j, COL_NAME) == NULL)
        {
          QTableWidgetItem *newItem = new QTableWidgetItem(Name);
          newItem->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
          Table1->setItem((int) j, COL_NAME, newItem);
        }
      else
        Table1->item((int) j, COL_NAME)->setText(Name);

      Table1->item((int) j, COL_NAME)->setBackground(QBrush(color));

      // col. 1 (description)
      QTableWidgetItem *newItem2 = new QTableWidgetItem();
      newItem2->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
      Table1->setItem((int) j, COL_USAGE, newItem2);
      Table1->item((int) j, COL_USAGE)->setBackground(QBrush(color));

      QComboBox *comboItem = new QComboBox(Table1);
      comboItem->addItems(Usages);
      comboItem->setCurrentIndex(comboItem->findText(qUsage));
      comboItem->setDisabled(mReadOnly);

      Table1->setCellWidget((int) j, COL_USAGE, comboItem);

      // connection between comboItem and its parent, Table1
      connect(comboItem, SIGNAL(activated(const QString &)), this, SLOT(slotTableValueChanged(const QString &)));
      comboItem->setObjectName(QString::number(j));  // just need to save the row index

      //col. 2 (units)
      QString strUnit = FROM_UTF8(units[j]);

      if (Table1->item((int) j, COL_UNIT) == NULL)
        {
          QTableWidgetItem *newItem = new QTableWidgetItem(strUnit);
          newItem->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
          Table1->setItem((int) j, COL_UNIT, newItem);
        }
      else
        Table1->item((int) j, COL_UNIT)->setText(strUnit);

      Table1->item((int) j, COL_UNIT)->setBackground(QBrush(color));
    }

  Table1->horizontalHeader()->setStretchLastSection(true);
  Table1->resizeColumnsToContents();
  Table1->resizeRowsToContents();

  /*
  Table1->setFixedSize(Table1->horizontalHeader()->length() + 10,
                       Table1->verticalHeader()->length() + 30);
  */

  return true;
}

//! Function to generate the text representation of the usage restrictions
bool FunctionWidget1::loadUsageTable()
{
  std::vector<std::string> stringlist;
  bool checkSubstrates = false;
  bool checkProducts = false;

  if (RadioButton1->isChecked() == true)
    {
      stringlist.push_back("Only reversible reactions");
      checkSubstrates = true;
      checkProducts = true;
    }
  else if (RadioButton2->isChecked() == true)
    {
      stringlist.push_back("Only irreversible reactions");
      checkSubstrates = true;
    }

  //substrates
  if (checkSubstrates)
    {
      if (mpFunction->getVariables().isVector(CFunctionParameter::SUBSTRATE))
        {
          stringlist.push_back("At least one substrate");
        }
      else if (mpFunction->getObjectName() != "Constant flux (irreversible)" &&
               mpFunction->getObjectName() != "Constant flux (reversible)")
        {
          std::stringstream ss;

          if (mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::SUBSTRATE) == 0)
            {
              ss << "No substrate";
            }
          else
            {
              ss << "Exactly "
              << mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::SUBSTRATE)
              << " substrate";

              if (mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::SUBSTRATE) > 1)
                ss << "s"; //plural
            }

          stringlist.push_back(ss.str());
        }
    }

  //products
  if (checkProducts)
    {
      if (mpFunction->getVariables().isVector(CFunctionParameter::PRODUCT))
        {
          stringlist.push_back("At least one product");
        }
      else if (mpFunction->getObjectName() != "Constant flux (reversible)")
        {
          std::stringstream ss;

          if (mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::PRODUCT) == 0 &&
              mpFunction->getObjectName() != "Constant flux (reversible)")
            {
              ss << "No product";
            }
          else
            {
              ss << "Exactly "
              << mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::PRODUCT)
              << " product";

              if (mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::PRODUCT) > 1)
                ss << "s"; //plural
            }

          stringlist.push_back(ss.str());
        }
    }

  if (stringlist.size() == 0)
    stringlist.push_back("None");

  size_t row;

  QString Restrictions("");
  QString Separator("");

  for (row = 0; row < stringlist.size(); ++row)
    {
      Restrictions += Separator + FROM_UTF8(stringlist[row]);
      Separator = ", ";
    }

  mpEditApplicationRestrictions->setText(Restrictions);

  return true;
}

bool FunctionWidget1::loadReversibility(TriLogic rev)
{
  switch (rev)
    {
      case TriUnspecified:
        RadioButton3->setEnabled(true);
        RadioButton3->setChecked(true);
        break;

      case TriFalse:
        RadioButton2->setEnabled(true);
        RadioButton2->setChecked(true);
        break;

      case TriTrue:
        RadioButton1->setEnabled(true);
        RadioButton1->setChecked(true);
        break;
    }

  return true;
}

bool FunctionWidget1::loadFromFunction(const CFunction* func)
{
  if (func != NULL)
    {
      pdelete(mpFunction);
      mpFunction = dynamic_cast<CFunction *>(CEvaluationTree::copy(*func));
      flagChanged = false;
    }

  if (mpFunction == NULL)
    return false;

  // function name
  LineEdit1->setText(FROM_UTF8(mpFunction->getObjectName()));

  /* Insert line breaks in the function description */
  std::string desc = mpFunction->getInfix();
  size_t l = 0;
  size_t n = 0;
  size_t len = desc.length();

  while (len - l > 65)
    {
      n = l;
      l = l + 65;

      while (l > n)
        {
          char ch = desc.at(l);

          if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == ',') || (ch == ' '))
            break;

          l--;
        }

      // We did not find a suitable place to break the line
      if (l == n) l += 65;

      desc.insert(l, 1, '\n');
    }

  mReadOnly = (mpFunction->getType() == CFunction::PreDefined ||
               mpFunction->getType() == CFunction::MassAction);


  RadioButton1->setEnabled(!mReadOnly);
  RadioButton2->setEnabled(!mReadOnly);
  RadioButton3->setEnabled(!mReadOnly);

  LineEdit1->setReadOnly(mReadOnly);

  mpExpressionEMSW->setReadOnly(mReadOnly);

  cancelChanges->setEnabled(!mReadOnly);
  deleteFcn->setEnabled(!mReadOnly);
  commitChanges->setEnabled(isValid && !mReadOnly);

  // formula expression
  mIgnoreFcnDescriptionChange = true;
  mpExpressionEMSW->mpExpressionWidget->setFunction(mpFunction->getInfix());
  mIgnoreFcnDescriptionChange = false;

  mpExpressionEMSW->updateWidget();


  //radio buttons
  loadReversibility(mpFunction->isReversible());

  //parameter table
  loadParameterTable();

  // application table
  loadUsageTable(/*pFunction->getVariables().getUsageRanges()*/);

  isValid = mpFunction->isUsable();

  flagChanged = false;

  return true;
}

bool FunctionWidget1::copyFunctionContentsToFunction(const CFunction* src, CFunction* target)
{
  //Parameters
  CFunctionParameters &functParam = target->getVariables();
  const CFunctionParameters &pfunctParam = src->getVariables();
  CFunctionParameter::DataType Type;
  size_t index;
  size_t i, j;

  if (src->getInfix() != target->getInfix())
    target->setInfix(src->getInfix());

  for (i = 0; i < pfunctParam.size(); i++)
    {
      // check if function parameter exists in pFunctionParameter
      if ((index = functParam.findParameterByName(pfunctParam[i]->getObjectName(),
                   Type)) != C_INVALID_INDEX)
        // match found
        {
          if (functParam[index]->getUsage() != pfunctParam[i]->getUsage())
            {
              //changed = true;
              // update usage
              functParam[index]->setUsage(pfunctParam[i]->getUsage());
              //functParam[pfunctParam[i]->getObjectName()]->setUsage(functParam[i]->getUsage());
            }

          if (functParam[index]->getType() != pfunctParam[i]->getType())
            {
              //changed = true;
              // update type
              functParam[index]->setType(pfunctParam[i]->getType());
            }
        }
      else
        {// match not found
          //changed = true;
          functParam.add(*pfunctParam[i]);
        }
    }

  // remove extra parameters existing in functParam, compare functParam to pfunctParam
  if (pfunctParam.size() != functParam.size())
    {
      for (j = 0; j < functParam.size(); j++)
        {
          if ((index = pfunctParam.findParameterByName(functParam[j]->getObjectName(),
                       Type)) == C_INVALID_INDEX)
            // the lines below occurs if new functionParameter does not exist in pfunctParam
            {
              //changed = true;
              // remove the extra parameter in functParam
              functParam.remove(functParam[j]->getObjectName());
            }
        }
    } //TODO: this is probably much too complicated

  return true;
}

bool FunctionWidget1::functionParametersChanged()
{
  CFunction* func = dynamic_cast<CFunction*>(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (!func) return false;

  return (!(func->getVariables() == mpFunction->getVariables()));
}

bool FunctionWidget1::saveToFunction()
{
  CFunction* func = dynamic_cast<CFunction*>(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (!func) return false;

  //name
  QString name(LineEdit1->text());

  if (func->getObjectName() != TO_UTF8(name))
    {
      // We need to check whether other trees call the current one.
      std::set<std::string> dependentTrees;
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

      if ((*CCopasiRootContainer::getDatamodelList())[0]->getModel())
        {
          dependentTrees =
            CCopasiRootContainer::getFunctionList()->listDependentTrees(func->getObjectName());
        }

      if (dependentTrees.size() > 0)
        {
          std::set<std::string>::iterator it = dependentTrees.begin();
          std::set<std::string>::iterator end = dependentTrees.end();

          QString trees;

          for (; it != end; it++)
            {
              trees.append(FROM_UTF8(*it));
              trees.append(" ---> ");
              trees.append(FROM_UTF8(mpFunction->getObjectName()));
              trees.append("\n");
            }

          QString msg1 = "Cannot change Function. ";
          msg1.append("Following dependencies with listed Function(s) exist:\n");
          msg1.append(trees);

          CQMessageBox::information(this, "Delete not possible",
                                    msg1, QMessageBox::Ok, QMessageBox::Ok);
          return false;
        }

      if (!func->setObjectName(TO_UTF8(name)))
        {
          QString msg;
          msg = "Unable to rename function '" + FROM_UTF8(func->getObjectName()) + "'\n"
                + "to '" + name + "' since a function with that name already exists.";

          CQMessageBox::information(this,
                                    "Unable to rename Function",
                                    msg,
                                    QMessageBox::Ok, QMessageBox::Ok);

          LineEdit1->setText(FROM_UTF8(func->getObjectName()));
        }
      else
        protectedNotify(ListViews::FUNCTION, ListViews::RENAME, mKey);
    }

  //radio buttons
  TriLogic tmpl;

  if (RadioButton1->isChecked() == true)
    {
      tmpl = TriTrue;
    }
  else if (RadioButton2->isChecked() == true)
    {
      tmpl = TriFalse;
    }
  else
    {
      tmpl = TriUnspecified;
    }

  if (tmpl != func->isReversible())
    {
      func->setReversible(tmpl);
      flagChanged = true;
    }

  if (flagChanged)
    {
      copyFunctionContentsToFunction(mpFunction, func);

      protectedNotify(ListViews::FUNCTION, ListViews::CHANGE, mKey);

      if (mpDataModel != NULL)
        {
          mpDataModel->changed();
        }

      flagChanged = false;
    }

  func->compile();

  return true;
}

//************** slots for changes in the widgets *************************************

//! Slot for changing the function description

/*!
   This slot function is called whenever the function description is changed.
 */
void FunctionWidget1::slotFcnDescriptionChanged(bool valid)
{

  if (mIgnoreFcnDescriptionChange ||
      (mpFunction == NULL))
    return;

  isValid = valid;

  if (isValid)
    {
      try
        {
          if (!mpFunction->setInfix(TO_UTF8(mpExpressionEMSW->getText())) ||
              !mpFunction->compile())
            {
              isValid = true;
            }
        }
      catch (...)
        {
          isValid = false;
        }
    }

  if (isValid)
    {
      flagChanged = true;
      //parameter table
      loadParameterTable();

      // application table
      loadUsageTable();

      commitChanges->setEnabled(true);
    }
  else
    {
      if (CCopasiMessage::peekLastMessage().getNumber() == MCFunction + 4)
        {
          CQMessageBox::critical(this, "Function Error",
                                 CCopasiMessage::getLastMessage().getText().c_str(),
                                 QMessageBox::Ok | QMessageBox::Default,
                                 QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }

      commitChanges->setEnabled(false);
    }
}

//! Slot for changing the table value
void FunctionWidget1::slotTableValueChanged(const QString &string)
{
  int curRow = sender()->objectName().toInt();

  QComboBox *comboItem = (QComboBox *) sender();

  flagChanged = true;

  CFunctionParameters &functParam = mpFunction->getVariables();

  // surely, we are in COL_USAGE... thus we don't need to check it anymore
  CFunctionParameter::Role usage = (CFunctionParameter::Role)(comboItem->findText(string));
  functParam[curRow]->setUsage(usage);

  //update tables
  loadParameterTable();
  loadUsageTable();
}

//! Slot for changing the reversibility of the function
void FunctionWidget1::slotReversibilityChanged()
{
  loadUsageTable();
}

//**************** slots for buttons *********************************************

//! Slot for being activated wehenver Cancel button is clicked
void FunctionWidget1::slotCancelButtonClicked()
{
  enter(mKey); // reload
}

//! Slot for being activated wehenver Commit button is clicked
void FunctionWidget1::slotCommitButtonClicked()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  if (pModel == NULL)
    return;

  // :TODO: We should check what changes have been done to the function //
  CFunctionDB * pFunctionDB = CCopasiRootContainer::getFunctionList();

  if (pFunctionDB == NULL)
    return;

  CEvaluationTree * pFunction = dynamic_cast<CEvaluationTree *>(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (pFunction == NULL) return;

  bool Used = false;

  if (functionParametersChanged())
    {
      QString msg =
        QString("Cannot modify function: \n  %1\n").arg(FROM_UTF8(pFunction->getObjectName()));

      std::set< const CCopasiObject * > Functions;
      std::set< const CCopasiObject * > Reactions;
      std::set< const CCopasiObject * > Metabolites;
      std::set< const CCopasiObject * > Values;
      std::set< const CCopasiObject * > Compartments;
      std::set< const CCopasiObject * > Events;

      std::set< const CCopasiObject * > DeletedObjects = pFunction->getDeletedObjects();

      Used |= pFunctionDB->appendDependentFunctions(DeletedObjects, Functions);

      if (Functions.size() > 0)
        {
          msg.append("Following functions(s) reference above:\n  ");

          std::set< const CCopasiObject * >::const_iterator it = Functions.begin();
          std::set< const CCopasiObject * >::const_iterator end = Functions.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      Used |= pModel->appendDependentModelObjects(DeletedObjects, Reactions, Metabolites,
              Compartments, Values, Events);

      if (Reactions.size() > 0)
        {
          msg.append("Following reactions(s) reference above:\n  ");

          std::set< const CCopasiObject * >::const_iterator it = Reactions.begin();
          std::set< const CCopasiObject * >::const_iterator end = Reactions.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Metabolites.size() > 0)
        {
          msg.append("Following species reference above:\n  ");

          std::set< const CCopasiObject * >::const_iterator it = Metabolites.begin();
          std::set< const CCopasiObject * >::const_iterator end = Metabolites.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Values.size() > 0)
        {
          msg.append("Following global quantities reference above:\n  ");

          std::set< const CCopasiObject * >::const_iterator it = Values.begin();
          std::set< const CCopasiObject * >::const_iterator end = Values.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Compartments.size() > 0)
        {
          msg.append("Following compartment(s) reference above:\n  ");

          std::set< const CCopasiObject * >::const_iterator it = Compartments.begin();
          std::set< const CCopasiObject * >::const_iterator end = Compartments.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Events.size() > 0)
        {
          msg.append("Following event(s) reference above:\n  ");

          std::set< const CCopasiObject * >::const_iterator it = Events.begin();
          std::set< const CCopasiObject * >::const_iterator end = Events.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Used)
        {
          CQMessageBox::information(this, "Modification not possible",
                                    msg, QMessageBox::Ok, QMessageBox::Ok);

          return;
        }
    }

  if (isValid)
    {
      saveToFunction();
      mpExpressionEMSW->updateWidget();
    }

  //update pFunction values

  /* Remove line breaks from the function description */
  /*std::string desc = TO_UTF8(textBrowser->text());
  unsigned int loc = 0;
  while (1)
    {
      loc = desc.find('\n', loc);
      if (loc == std::string::npos)
        break;
      desc.erase(loc, 1);
    }
  textBrowser->setText(FROM_UTF8(desc));*/
}

//! Slot for being activated wehenver New button is clicked
void FunctionWidget1::slotNewButtonClicked()
{
  slotCommitButtonClicked();

  std::string name = "function";
  int i = 0;
  CFunction* pFunc;
  CCopasiVectorN<CFunction>& FunctionList
  = CCopasiRootContainer::getFunctionList()->loadedFunctions();

  while (FunctionList.getIndex(name) != C_INVALID_INDEX)
    {
      i++;
      name = "function_";
      name += TO_UTF8(QString::number(i));
    }

  CCopasiRootContainer::getFunctionList()->add(pFunc = new CKinFunction(name), true);

  std::string key = pFunc->getKey();
  protectedNotify(ListViews::FUNCTION, ListViews::ADD, key);
  enter(key);
  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

//! Slot for being activated whenever Delete button is clicked
void FunctionWidget1::slotDeleteButtonClicked()
{
  CFunctionDB * pFunctionDB = CCopasiRootContainer::getFunctionList();

  if (pFunctionDB == NULL)
    return;

  CEvaluationTree * pFunction = dynamic_cast<CEvaluationTree *>(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (pFunction == NULL)
    return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(NULL, "function",
                                FROM_UTF8(pFunction->getObjectName()),
                                pFunction->getDeletedObjects());

  /* Check if user chooses to deleted Functions */
  switch (choice)
    {
      case QMessageBox::Ok:                                                    // Yes or Enter
      {
        size_t index =
          CCopasiRootContainer::getFunctionList()->loadedFunctions().getIndex(mpFunction->getObjectName());

        CCopasiRootContainer::getFunctionList()->removeFunction(mKey);
        std::string deletedKey = mKey;

        size_t size =
          CCopasiRootContainer::getFunctionList()->loadedFunctions().size();

        QObject *pParent = parent();
        CTabWidget * pTabWidget = NULL;

        while (pParent != NULL &&
               (pTabWidget = dynamic_cast< CTabWidget *>(pParent)) == NULL)
          {
            pParent = pParent->parent();
          }

        if (pTabWidget != NULL)
          {
            if (size > 0)
              pTabWidget->enter(CCopasiRootContainer::getFunctionList()->loadedFunctions()[std::min(index, size - 1)]->getKey());
            else
              pTabWidget->enter("");
          }

        protectedNotify(ListViews::FUNCTION, ListViews::DELETE, deletedKey);
        protectedNotify(ListViews::FUNCTION, ListViews::DELETE, "");//Refresh all as there may be dependencies.
        break;
      }

      default:                                                    // No or Escape
        break;
    }
}

//***********  slot for editing requests on the function formula (mMmlWidget) *****


//************************  standard interface to COPASI widgets ******************

//! Function to update the COPASI widgets
bool FunctionWidget1::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
      case ListViews::MODEL:
      case ListViews::FUNCTION:
        return loadFromFunction(dynamic_cast< CFunction * >(CCopasiRootContainer::getKeyFactory()->get(mKey)));
        break;

      default:
        break;
    }

  return true;
}

bool FunctionWidget1::leave()
{
  slotCommitButtonClicked();

  //mScrollView->hide();
  return true;
}

bool FunctionWidget1::enterProtected()
{
  CFunction* func = dynamic_cast<CFunction*>(mpObject);

  if (func)
    return loadFromFunction(func);

  mpListView->switchToOtherWidget(5, "");
  return false;
}
