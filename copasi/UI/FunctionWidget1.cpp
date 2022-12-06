// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/UI/FunctionWidget1.h"

#include "copasi/copasi.h"
#include "copasi/UI/listviews.h"
#include "copasi/UI/CQMessageBox.h"
#include "copasi/UI/FunctionWidget1.h"
#include "copasi/UI/qtUtilities.h"

#include "copasi/tex/CMathMLToTeX.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CKinFunction.h"
#include "copasi/utilities/CUnitValidator.h"

#include "copasi/commandline/CConfigurationFile.h"

#include "copasi/UI/CopasiFileDialog.h"

#include <QComboBox>
#include <QToolTip>
#include <QApplication>

#ifdef DELETE
#  undef DELETE
#endif

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
  mpFunction(NULL),
  mObjectCNToCopy("")
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

  for (i = 0; i < CFunctionParameter::RoleNameDisplay.size(); i++)
    {
      if (dynamic_cast<CKinFunction *>(mpFunction) &&
          CFunctionParameter::Role::VARIABLE == (CFunctionParameter::Role) i) continue;

      Usages += (FROM_UTF8(CFunctionParameter::RoleNameDisplay[i]));
    }

  //create list of data types (for combobox)
  QStringList functionType;

  for (i = 0; i < CFunctionParameter::DataTypeName.size(); i++)
    functionType += (FROM_UTF8(CFunctionParameter::DataTypeName[i]));

  //find parameter units
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  // Determine the units of the variables depending on the type
  std::vector< std::vector < CUnit > >Variables(4);
  CUnit Time(pModel->getTimeUnit());
  CUnit Volume(pModel->getVolumeUnit());
  CUnit Area(pModel->getAreaUnit());
  CUnit Length(pModel->getLengthUnit());
  CUnit Quantity(pModel->getQuantityUnit());

  for (i = 0; i < params.size(); ++i)
    {
      switch (params[i]->getUsage())
        {
          case CFunctionParameter::Role::SUBSTRATE:
          case CFunctionParameter::Role::PRODUCT:
          case CFunctionParameter::Role::MODIFIER:
            // These depend on the dimensions of the compartment
            Variables[0].push_back(Quantity * Volume.exponentiate(-1.0)); // This is just to compare the results
            Variables[1].push_back(Quantity * Length.exponentiate(-1.0));
            Variables[2].push_back(Quantity * Area.exponentiate(-1.0));
            Variables[3].push_back(Quantity * Volume.exponentiate(-1.0));
            break;

          case CFunctionParameter::Role::PARAMETER:
          case CFunctionParameter::Role::VARIABLE:
          case CFunctionParameter::Role::TEMPORARY:
            Variables[0].push_back(CUnit());
            Variables[1].push_back(CUnit());
            Variables[2].push_back(CUnit());
            Variables[3].push_back(CUnit());
            break;

          case CFunctionParameter::Role::VOLUME:
            // These depend on the dimensions of the compartment
            Variables[0].push_back(CUnit());
            Variables[1].push_back(Length);
            Variables[2].push_back(Area);
            Variables[3].push_back(Volume);
            break;

          case CFunctionParameter::Role::TIME:
            Variables[0].push_back(Time);
            Variables[1].push_back(Time);
            Variables[2].push_back(Time);
            Variables[3].push_back(Time);
            break;
        }
    }

  std::vector < CUnit > Target(4);
  Target[0] = Quantity * Time.exponentiate(-1.0);
  Target[1] = Quantity * Length.exponentiate(-1.0) * Time.exponentiate(-1.0);
  Target[2] = Quantity * Area.exponentiate(-1.0) * Time.exponentiate(-1.0);
  Target[3] = Quantity * Volume.exponentiate(-1.0) * Time.exponentiate(-1.0);

  // Handle units
  CMathContainer & Container = pModel->getMathContainer();
  CUnitValidator Validator(Container, *mpFunction);

  std::vector< std::vector < CValidatedUnit > > ValidatedVariables(4);
  Validator.validateUnits(Target[0], Variables[0]);
  ValidatedVariables[0] = Validator.getVariableUnits();
  Validator.validateUnits(Target[1], Variables[1]);
  ValidatedVariables[1] = Validator.getVariableUnits();
  Validator.validateUnits(Target[2], Variables[2]);
  ValidatedVariables[2] = Validator.getVariableUnits();
  Validator.validateUnits(Target[3], Variables[3]);
  ValidatedVariables[3] = Validator.getVariableUnits();

  CFunctionParameter::Role usage;
  QString qUsage;

  //C_INT32 noOffunctParams = functParam.size();
  Table1->setRowCount(0);
  Table1->setRowCount((int) params.size());
  Table1->blockSignals(true);

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  QPalette Palette = QGuiApplication::palette();
#else
  QPalette Palette = QApplication::palette();
#endif
  QColor Foreground = Palette.color(QPalette::Active, QPalette::Text);
  QColor Background = Palette.color(QPalette::Active, QPalette::Base);

  bool isDarkTheme = (Foreground.redF() + Foreground.greenF() + Foreground.blueF() > Background.redF() + Background.greenF() + Background.blueF());

  for (j = 0; j < params.size(); j++)
    {
      usage = params[j]->getUsage();

      if (usage == CFunctionParameter::Role::VARIABLE &&
          dynamic_cast<CKinFunction *>(mpFunction))
        {
          usage = CFunctionParameter::Role::PARAMETER;
          params[j]->setUsage(usage);
        }

      qUsage = FROM_UTF8(CFunctionParameter::RoleNameDisplay[usage]);

      switch (usage)
        {
          case CFunctionParameter::Role::SUBSTRATE:
            color = subsColor;
            break;

          case CFunctionParameter::Role::PRODUCT:
            color = prodColor;
            break;

          case CFunctionParameter::Role::MODIFIER:
            color = modiColor;
            break;

          case CFunctionParameter::Role::PARAMETER:
            color = paraColor;
            break;

          case CFunctionParameter::Role::VOLUME:
            color = volColor;
            break;

          case CFunctionParameter::Role::TIME:
            color = timeColor;
            break;

          case CFunctionParameter::Role::VARIABLE:
            color = QColor(250, 250, 250);
            break;

          default :
            qUsage = "unknown";
            color = QColor(255, 20, 20);
            break;
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

      if (isDarkTheme)
        Table1->item((int) j, COL_NAME)->setForeground(QBrush(color));
      else
        Table1->item((int) j, COL_NAME)->setBackground(QBrush(color));

      // col. 1 (description)
      QTableWidgetItem *newItem2 = new QTableWidgetItem();
      newItem2->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
      Table1->setItem((int) j, COL_USAGE, newItem2);

      if (isDarkTheme)
        Table1->item((int) j, COL_USAGE)->setForeground(QBrush(color));
      else
        Table1->item((int) j, COL_USAGE)->setBackground(QBrush(color));

      QComboBox *comboItem = new QComboBox(Table1);
      comboItem->addItems(Usages);
      comboItem->setCurrentIndex(comboItem->findText(qUsage));
      comboItem->setDisabled(mReadOnly);

      Table1->setCellWidget((int) j, COL_USAGE, comboItem);

      // connection between comboItem and its parent, Table1
      connect(comboItem, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotTableValueChanged(const QString &)));
      comboItem->setObjectName(QString::number(j));  // just need to save the row index

      //col. 2 (units)
      QString strUnit = FROM_UTF8(ValidatedVariables[0][j] == ValidatedVariables[3][j] ?
                                  ValidatedVariables[0][j].getExpression() :
                                  ValidatedVariables[3][j].getExpression() + " or " + ValidatedVariables[0][j].getExpression());

      if (mpFunction->getType() == CEvaluationTree::MassAction &&
          j % 2 == 0)
        {
          strUnit = "?";
        }

      if (Table1->item((int) j, COL_UNIT) == NULL)
        {
          QTableWidgetItem *newItem = new QTableWidgetItem(strUnit);
          newItem->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
          Table1->setItem((int) j, COL_UNIT, newItem);
        }
      else
        Table1->item((int) j, COL_UNIT)->setText(strUnit);

      if (isDarkTheme)
        Table1->item((int) j, COL_UNIT)->setForeground(QBrush(color));
      else
        Table1->item((int) j, COL_UNIT)->setBackground(QBrush(color));
    }

  Table1->blockSignals(false);
  Table1->horizontalHeader()->setStretchLastSection(true);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      Table1->resizeColumnsToContents();
      Table1->resizeRowsToContents();
    }

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
      if (mpFunction->getVariables().isVector(CFunctionParameter::Role::SUBSTRATE))
        {
          stringlist.push_back("At least one substrate");
        }
      else if (mpFunction->getObjectName() != "Constant flux (irreversible)" &&
               mpFunction->getObjectName() != "Constant flux (reversible)")
        {
          std::stringstream ss;

          if (mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::Role::SUBSTRATE) == 0)
            {
              ss << "No substrate";
            }
          else
            {
              ss << "Exactly "
                 << mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::Role::SUBSTRATE)
                 << " substrate";

              if (mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::Role::SUBSTRATE) > 1)
                ss << "s"; //plural
            }

          stringlist.push_back(ss.str());
        }
    }

  //products
  if (checkProducts)
    {
      if (mpFunction->getVariables().isVector(CFunctionParameter::Role::PRODUCT))
        {
          stringlist.push_back("At least one product");
        }
      else if (mpFunction->getObjectName() != "Constant flux (reversible)")
        {
          std::stringstream ss;

          if (mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::Role::PRODUCT) == 0 &&
              mpFunction->getObjectName() != "Constant flux (reversible)")
            {
              ss << "No product";
            }
          else
            {
              ss << "Exactly "
                 << mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::Role::PRODUCT)
                 << " product";

              if (mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::Role::PRODUCT) > 1)
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

      flagChanged = !mObjectCNToCopy.empty();
      mObjectCNToCopy.clear();
    }

  if (mpFunction == NULL)
    return false;

  // function name
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

  mReadOnly = mpFunction->isReadOnly() && !flagChanged;

  RadioButton1->setEnabled(!mReadOnly);
  RadioButton2->setEnabled(!mReadOnly);
  RadioButton3->setEnabled(!mReadOnly);

  mpExpressionEMSW->setReadOnly(mReadOnly);

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

  CIssue issue = mpFunction->getValidity().getFirstWorstIssue();
  isValid = issue;

  return true;
}

bool FunctionWidget1::copyFunctionContentsToFunction(const CFunction* src, CFunction* target)
{
  //Parameters
  CFunctionParameters &functParam = target->getVariables();
  const CFunctionParameters &pfunctParam = src->getVariables();
  size_t index;
  size_t i, j;

  if (src->getInfix() != target->getInfix())
    target->setInfix(src->getInfix());

  for (i = 0; i < pfunctParam.size(); i++)
    {
      // check if function parameter exists in pFunctionParameter
      if ((index = functParam.findParameterByName(pfunctParam[i]->getObjectName())) != C_INVALID_INDEX)
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
        {
          // match not found
          //changed = true;
          functParam.add(*pfunctParam[i]);
        }
    }

  // remove extra parameters existing in functParam, compare functParam to pfunctParam
  if (pfunctParam.size() != functParam.size())
    {
      for (j = 0; j < functParam.size(); j++)
        {
          if ((index = pfunctParam.findParameterByName(functParam[j]->getObjectName())) == C_INVALID_INDEX)
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
  CFunction* func = dynamic_cast<CFunction*>(mpObject);

  if (!func) return false;

  return (!(func->getVariables() == mpFunction->getVariables()));
}

bool FunctionWidget1::saveToFunction()
{
  CFunction* func = dynamic_cast<CFunction*>(mpObject);

  if (!func) return false;

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

      protectedNotify(ListViews::ObjectType::FUNCTION, ListViews::CHANGE, mObjectCN);

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

  std::string oldInfix = mpFunction->getInfix();

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
      if (oldInfix == mpFunction->getInfix())
        return;

      flagChanged = true;
      //parameter table
      loadParameterTable();

      // application table
      loadUsageTable();
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

//! Slot for being activated wehenver New button is clicked
void FunctionWidget1::slotBtnNew()
{
  std::string name = "function_1";
  int i = 1;
  CFunction* pFunc;
  CDataVectorN<CFunction>& FunctionList
    = CRootContainer::getFunctionList()->loadedFunctions();

  while (FunctionList.getIndex(name) != C_INVALID_INDEX)
    {
      i++;
      name = "function_";
      name += TO_UTF8(QString::number(i));
    }

  CRootContainer::getFunctionList()->add(pFunc = new CKinFunction(name), true);

  CCommonName CN = pFunc->getCN();
  protectedNotify(ListViews::ObjectType::FUNCTION, ListViews::ADD, CN);
  // enter(key);
  mpListView->switchToOtherWidget(ListViews::WidgetType::FunctionDetail, CN);
}

void FunctionWidget1::slotBtnCopy()
{
  mObjectCNToCopy = mObjectCN;
}

//! Slot for being activated whenever Delete button is clicked
void FunctionWidget1::slotBtnDelete()
{
  CFunctionDB * pFunctionDB = CRootContainer::getFunctionList();

  if (pFunctionDB == NULL)
    return;

  CEvaluationTree * pFunction = dynamic_cast<CEvaluationTree *>(mpObject);

  if (pFunction == NULL)
    return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(this, "function",
                                FROM_UTF8(pFunction->getObjectName()),
                                pFunction);

  /* Check if user chooses to deleted Functions */
  switch (choice)
    {
      case QMessageBox::Ok:                                                    // Yes or Enter
      {
        CRootContainer::getFunctionList()->loadedFunctions().remove(mpObject->getObjectName());

        protectedNotify(ListViews::ObjectType::FUNCTION, ListViews::DELETE, mObjectCN);
        protectedNotify(ListViews::ObjectType::FUNCTION, ListViews::DELETE, std::string());//Refresh all as there may be dependencies.
        break;
      }

      default:                                                    // No or Escape
        break;
    }
}

//***********  slot for editing requests on the function formula (mMmlWidget) *****

//************************  standard interface to COPASI widgets ******************

//! Function to update the COPASI widgets
bool FunctionWidget1::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  if (mIgnoreUpdates || !isVisible())
    {
      return true;
    }

  switch (objectType)
    {
      case ListViews::ObjectType::MODEL:
        loadFromFunction(dynamic_cast< CFunction * >(mpObject));
        break;

      case ListViews::ObjectType::FUNCTION:

        if (cn == mObjectCN)
          {
            switch (action)
              {
                case ListViews::CHANGE:
                  loadFromFunction(dynamic_cast< CFunction * >(mpObject));
                  break;

                case ListViews::DELETE:
                  mObjectCN.clear();
                  mpObject = NULL;
                  break;

                default:
                  break;
              }
          }

        break;

      default:
        break;
    }

  return true;
}

bool FunctionWidget1::leaveProtected()
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();

  if (pModel == NULL)
    return true;

  // :TODO: We should check what changes have been done to the function //
  CFunctionDB * pFunctionDB = CRootContainer::getFunctionList();

  if (pFunctionDB == NULL)
    return true;

  CEvaluationTree * pFunction = dynamic_cast<CEvaluationTree *>(mpObject);

  if (pFunction == NULL)
    return true;

  bool Used = false;

  if (functionParametersChanged())
    {
      QString msg =
        QString("Cannot modify function: \n  %1\n").arg(FROM_UTF8(pFunction->getObjectName()));

      CDataObject::DataObjectSet Functions;
      CDataObject::DataObjectSet Reactions;
      CDataObject::DataObjectSet Metabolites;
      CDataObject::DataObjectSet Values;
      CDataObject::DataObjectSet Compartments;
      CDataObject::DataObjectSet Events;
      CDataObject::DataObjectSet EventAssignments;

      CDataObject::ObjectSet DeletedObjects;
      DeletedObjects.insert(pFunction);

      Used |= pFunctionDB->appendDependentFunctions(DeletedObjects, Functions);

      if (Functions.size() > 0)
        {
          msg.append("Following functions(s) reference above:\n  ");

          std::set< const CDataObject * >::const_iterator it = Functions.begin();
          std::set< const CDataObject * >::const_iterator end = Functions.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      Used |= pModel->appendAllDependents(DeletedObjects, Reactions, Metabolites,
                                          Compartments, Values, Events, EventAssignments);

      if (Reactions.size() > 0)
        {
          msg.append("Following reactions(s) reference above:\n  ");

          std::set< const CDataObject * >::const_iterator it = Reactions.begin();
          std::set< const CDataObject * >::const_iterator end = Reactions.end();

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

          std::set< const CDataObject * >::const_iterator it = Metabolites.begin();
          std::set< const CDataObject * >::const_iterator end = Metabolites.end();

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

          std::set< const CDataObject * >::const_iterator it = Values.begin();
          std::set< const CDataObject * >::const_iterator end = Values.end();

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

          std::set< const CDataObject * >::const_iterator it = Compartments.begin();
          std::set< const CDataObject * >::const_iterator end = Compartments.end();

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

          std::set< const CDataObject * >::const_iterator it = Events.begin();
          std::set< const CDataObject * >::const_iterator end = Events.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (EventAssignments.size() > 0)
        {
          bool first = true;

          std::set< const CDataObject * >::const_iterator it = EventAssignments.begin();
          std::set< const CDataObject * >::const_iterator end = EventAssignments.end();

          for (; it != end; ++it)
            {
              const CDataObject * pEvent = (*it)->getObjectAncestor("Event");

              if (Events.find(pEvent) == Events.end())
                {
                  if (first)
                    {
                      msg.append("Following event assignment(s) reference above and will be deleted:\n  ");
                      first = false;
                    }

                  const CDataObject * pObject = CRootContainer::getKeyFactory()->get((*it)->getObjectName());
                  std::string ObjectName = (pObject != NULL) ? pObject->getObjectName() : (*it)->getObjectName();
                  msg.append(FROM_UTF8(pEvent->getObjectName() + ": " + ObjectName));
                  msg.append("\n  ");
                }
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Used)
        {
          CQMessageBox::information(this, "Modification not possible",
                                    msg, QMessageBox::Ok, QMessageBox::Ok);

          return true;
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

  //mScrollView->hide();
  return true;
}

bool FunctionWidget1::enterProtected()
{
  CFunction * func = NULL;

  if (mObjectCNToCopy != "")
    {
      //func = dynamic_cast<CFunction*>(CRootContainer::getKeyFactory()->get(mObjectCNToCopy));
      func = const_cast<CFunction*>(dynamic_cast<const CFunction*>(CRootContainer::getRoot()->getObject(mObjectCNToCopy)));
    }
  else
    {
      func = dynamic_cast<CFunction*>(mpObject);
    }

  if (func)
    return loadFromFunction(func);

  mpListView->switchToOtherWidget(ListViews::WidgetType::Functions, std::string());
  return false;
}
