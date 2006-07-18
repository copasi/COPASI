/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SensitivitiesWidget.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: tjohann $
   $Date: 2006/07/18 13:24:02 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qfiledialog.h>

#include <qvariant.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>
#include <qtoolbutton.h>

#include <algorithm>

#include "SensitivitiesWidget.h"
#include "DataModelGUI.h"
#include "qtUtilities.h"
#include "listviews.h"
#include "CProgressBar.h"
#include "copasiui3window.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CCopasiSelectionDialog.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "sensitivities/CSensTask.h"
#include "sensitivities/CSensProblem.h"
#include "model/CModel.h"
#include "utilities/CCopasiException.h"
#include "report/CKeyFactory.h"
#include "parametertable.h"

/**
 *  Constructs a SensitivitiesWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
SensitivitiesWidget::SensitivitiesWidget(QWidget* parent, const char* name, WFlags fl)
    : TaskWidget(parent, name, fl),
    mpSingleFunction(NULL),
    mpSingleVariable(NULL),
    mpSingleVariable2(NULL)
{
  // row where the header ends:
  const int fieldStart = 3;

  if (!name)
    setName("SensitivitiesWidget");
  setCaption(trUtf8("SensitivitiesWidget"));

  //if a mpMethodLayout is created here, it will be used by addMethodXXX() below.
  mpMethodLayout = new QGridLayout(this, 0, 1, 11, 6, "mpMethodLayout");

  mpHeaderWidget->setTaskName("Sensitivities");
  addHeaderToGrid();

  //  QSpacerItem* spacer2 = new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
  //mpMethodLayout->addItem(spacer2, 1, 1);

  addHLineToGrid(mpMethodLayout, 2, 2);

  QSpacerItem* spacer1 = new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
  mpMethodLayout->addItem(spacer1, 3, 3);

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Subtask Method:"));
  TextLabel1->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  mpMethodLayout->addWidget(TextLabel1, fieldStart + 1, 0);

  SubTaskChooser = new QComboBox(FALSE, this, "SubTaskChooser");
  SubTaskChooser->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, SubTaskChooser->sizePolicy().hasHeightForWidth()));
  mpMethodLayout->addWidget(SubTaskChooser, fieldStart + 1, 1);

  QSpacerItem* spacer2 = new QSpacerItem(4, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);
  mpMethodLayout->addItem(spacer2, fieldStart + 2, 0);

  addHLineToGrid(mpMethodLayout, fieldStart + 3, 2);

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Function:"));
  TextLabel2->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  mpMethodLayout->addWidget(TextLabel2, fieldStart + 4, 0);

  FunctionChooser = new QComboBox(FALSE, this, "TargetFunctionChooser");
  //  FunctionChooser->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, FunctionChooser->sizePolicy().hasHeightForWidth()));
  mpMethodLayout->addMultiCellWidget(FunctionChooser, fieldStart + 4, fieldStart + 4, 1, 1);

  FunctionLineEdit = new QLineEdit(this, "FunctionLineEdit");
  mpMethodLayout->addMultiCellWidget(FunctionLineEdit, fieldStart + 5, fieldStart + 5, 1, 1);
  FunctionLineEdit->setReadOnly(true);
  FunctionLineEdit->hide();

  SingleFunctionChooser = new QToolButton(this, "SingleFunctionChooser");
  mpMethodLayout->addWidget(SingleFunctionChooser, fieldStart + 5, 2);
  SingleFunctionChooser->hide();
  //  FunctionChoiceBox = new QListView(this, "FunctionChoiceBox");
  //  mpMethodLayout->addMultiCellWidget(FunctionChoiceBox,fieldStart+2, fieldStart+2, 2, 2);

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Variable:"));
  TextLabel3->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  mpMethodLayout->addWidget(TextLabel3, fieldStart + 6, 0);

  VariableChooser = new QComboBox(FALSE, this, "VariableChooser");
  //  VariableChooser->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, VariableChooser->sizePolicy().hasHeightForWidth()));
  mpMethodLayout->addMultiCellWidget(VariableChooser, fieldStart + 6, fieldStart + 6, 1, 1);

  VariableLineEdit = new QLineEdit(this, "VariableLineEdit");
  mpMethodLayout->addMultiCellWidget(VariableLineEdit, fieldStart + 7, fieldStart + 7, 1, 1);
  VariableLineEdit->setReadOnly(true);
  VariableLineEdit->hide();

  SingleVariableChooser = new QToolButton(this, "SingleVariableChooser");
  mpMethodLayout->addWidget(SingleVariableChooser, fieldStart + 7, 2);
  SingleVariableChooser->hide();

  TextLabel4 = new QLabel(this, "TextLabel4");
  TextLabel4->setText(trUtf8("Second Variable"));
  TextLabel4->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  mpMethodLayout->addWidget(TextLabel4, fieldStart + 8, 0);

  Variable2Chooser = new QComboBox(FALSE, this, "Variable2Chooser");
  //  Variable2Chooser->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, Variable2Chooser->sizePolicy().hasHeightForWidth()));
  mpMethodLayout->addMultiCellWidget(Variable2Chooser, fieldStart + 8, fieldStart + 8, 1, 1);

  Variable2LineEdit = new QLineEdit(this, "Variable2LineEdit");
  mpMethodLayout->addMultiCellWidget(Variable2LineEdit, fieldStart + 9, fieldStart + 9, 1, 1);
  Variable2LineEdit->setReadOnly(true);
  Variable2LineEdit->hide();

  SingleVariable2Chooser = new QToolButton(this, "SingleVariable2Chooser");
  mpMethodLayout->addWidget(SingleVariable2Chooser, fieldStart + 9, 2);
  SingleVariable2Chooser->hide();

  QSpacerItem* spacer3 = new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
  mpMethodLayout->addItem(spacer3, fieldStart + 10, fieldStart + 10);

  initCombos();

  addHLineToGrid(mpMethodLayout, fieldStart + 11, 2);

  addMethodParameterTable(4, fieldStart + 12);

  mpMethodLayout->addMultiCellWidget(mpBtnWidget,
                                     fieldStart + 13, fieldStart + 13,
                                     0, 2);
  mpBtnWidget->mpBtnRun->setEnabled(false);

  connect(SubTaskChooser, SIGNAL(activated(int)),
          this, SLOT(on_SubTaskChooser_activated(int)));
  connect(FunctionChooser, SIGNAL(activated(int)),
          this, SLOT(on_FunctionChooser_activated(int)));
  connect(VariableChooser, SIGNAL(activated(int)),
          this, SLOT(on_VariableChooser_activated(int)));
  connect(Variable2Chooser, SIGNAL(activated(int)),
          this, SLOT(on_Variable2Chooser_activated(int)));

  connect(SingleFunctionChooser, SIGNAL(clicked()),
          this, SLOT(on_SingleFunctionChooser_clicked()));
  connect(SingleVariableChooser, SIGNAL(clicked()),
          this, SLOT(on_SingleVariableChooser_clicked()));
  connect(SingleVariable2Chooser, SIGNAL(clicked()),
          this, SLOT(on_SingleVariable2Chooser_clicked()));

  mChoicesDone = 0;

  mpProblem = new CSensProblem();

  //  std::cout << mpProblem->getNumberOfVariables() << std::endl;

  //std::cout << mpProblem->getVariables(0).getListType() << std::endl;

  initCombos(mpProblem);
}

/*
 *  Destroys the object and frees any allocated resources
 */
SensitivitiesWidget::~SensitivitiesWidget()
{}

bool SensitivitiesWidget::saveTask()
{
  //saveCommon();
  //saveMethod();

  CSensTask* sensTask =
    dynamic_cast<CSensTask *>(GlobalKeys.get(mObjectKey));
  assert(sensTask);

  CSensProblem* problem =
    dynamic_cast<CSensProblem *>(sensTask->getProblem());
  assert(problem);

  CSensMethod* method =
    dynamic_cast<CSensMethod *>(sensTask->getMethod());
  assert(method);

  //...

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  if (mChanged) CCopasiDataModel::Global->changed();
  return true;
}

CCopasiMethod * SensitivitiesWidget::createMethod(const CCopasiMethod::SubType & type)
{return CSensMethod::createSensMethod(type);}

bool SensitivitiesWidget::runTask()
{
  //if (!commonBeforeRunTask()) return false;

  //commonAfterRunTask();

  //pListView->switchToOtherWidget(211, ""); //change to the results window

  return true;
}

bool SensitivitiesWidget::loadTask()
{
  //loadCommon();
  //loadMethod();

  CSensTask* sensTask =
    dynamic_cast<CSensTask *>(GlobalKeys.get(mObjectKey));
  assert(sensTask);

  CSensProblem* problem =
    dynamic_cast<CSensProblem *>(sensTask->getProblem());
  assert(problem);

  CSensMethod* method =
    dynamic_cast<CSensMethod *>(sensTask->getMethod());
  assert(method);

  //...

  mChanged = false;

  return true;
}

void
SensitivitiesWidget::initCombos()
{
  QStringList StringList;
  std::vector<int> mFunctionIndexTable, mVariableIndexTable;

  // SubTaskChooser combo
  int i = 0;
  while (CSensProblem::SubTaskName[i].length() > 0)
    {
      StringList.append(FROM_UTF8(CSensProblem::SubTaskName[i]));
      ++i;
    }

  SubTaskChooser->insertStringList(StringList);

  // FunctionChooser combo
  StringList.clear();
  updateFunctionsStringList(CSensProblem::unset);
  FunctionChooser->insertStringList(mFunctionsStringList);

  // VariableChooser combo
  updateVariablesStringList(CSensProblem::unset);
  VariableChooser->insertStringList(mVariablesStringList);
  Variable2Chooser->insertStringList(mVariablesStringList);
}

void
SensitivitiesWidget::initCombos(CSensProblem problem)
{
  SubTaskChooser->setCurrentItem((int)problem.getSubTaskType());
  on_SubTaskChooser_activated(problem.getSubTaskType());

  // add assertions of return values here with an error message box...
  initCombos(problem.getTargetFunctions(), SensitivitiesWidget::Function);

  initCombos(problem.getVariables(0), SensitivitiesWidget::Variable);

  if (problem.getNumberOfVariables() > 1)
    initCombos(problem.getVariables(1), SensitivitiesWidget::SecondVariable);
}

bool
SensitivitiesWidget::initCombos(CSensItem item, SensitivitiesWidget::ChoiceType type)
{
  std::vector<CObjectLists::ListType> listType;
  std::vector<CObjectLists::ListType>::iterator liter;

  if (type == SensitivitiesWidget::SubTask)
    return false;

  listType = mVariablesIndexTable;

  if (type == SensitivitiesWidget::Function)
    listType = mFunctionsIndexTable;

  liter = std::find(listType.begin(), listType.end(), item.getListType());
  int index = std::distance(listType.begin(), liter);

  if (liter != listType.end())
    {
      switch (type)
        {
        case (SensitivitiesWidget::Function):
                FunctionChooser->setCurrentItem(index);
          on_FunctionChooser_activated(index);
          break;

        case (SensitivitiesWidget::Variable):
                VariableChooser->setCurrentItem(index);
          on_VariableChooser_activated(index);
          break;

        case (SensitivitiesWidget::SecondVariable):
                Variable2Chooser->setCurrentItem(index);
          on_Variable2Chooser_activated(index);
        }
    }
  else
    return false;

  return true;
}

void
SensitivitiesWidget::updateFunctionsStringList(CSensProblem::SubTaskType type)
{
  std::vector<CObjectLists::ListType> functions;
  std::vector<CObjectLists::ListType>::iterator fiter;

  mFunctionsIndexTable.clear();
  mFunctionsStringList.clear();

  functions = CSensProblem::getPossibleTargetFunctions(type);

  for (fiter = functions.begin(); fiter != functions.end(); ++fiter)
    {
      mFunctionsStringList.append(FROM_UTF8(CObjectLists::ListTypeName[*fiter]));
      mFunctionsIndexTable.push_back(*fiter);
    }
}

void
SensitivitiesWidget::updateVariablesStringList(CSensProblem::SubTaskType type)
{
  std::vector<CObjectLists::ListType> variables;
  std::vector<CObjectLists::ListType>::iterator viter;

  mVariablesIndexTable.clear();
  mVariablesStringList.clear();

  variables = CSensProblem::getPossibleVariables(type);

  for (viter = variables.begin(); viter != variables.end(); ++viter)
    {
      mVariablesStringList.append(FROM_UTF8(CObjectLists::ListTypeName[*viter]));
      mVariablesIndexTable.push_back(*viter);
    }
}

// SLOTs
void
SensitivitiesWidget::on_SubTaskChooser_activated(int index)
{
  QStringList list;
  std::vector<CObjectLists::ListType>::iterator iter;

  bool enabled = true;
  if (index == 0)
    {
      enabled = false;
      mChoicesDone &= ~Choice_SubTask;
    }
  else
    {
      mChoicesDone |= Choice_SubTask;
      enabled = mChoicesDone == Choice_All;
    }

  mpBtnWidget->mpBtnRun->setEnabled(enabled);

  // memorise the state of the other combo boxes:
  CObjectLists::ListType oldChoiceFunc =
    (CObjectLists::ListType)mFunctionsIndexTable[ FunctionChooser->currentItem() ];
  CObjectLists::ListType oldChoiceVar =
    mVariablesIndexTable[ VariableChooser->currentItem() ];

  FunctionChooser->clear();
  updateFunctionsStringList((CSensProblem::SubTaskType)index);
  FunctionChooser->insertStringList(mFunctionsStringList);

  // if valid, set current item to oldChoiceFunc
  iter = std::find(mFunctionsIndexTable.begin(),
                   mFunctionsIndexTable.end(),
                   oldChoiceFunc);
  if (iter != mFunctionsIndexTable.end())
    FunctionChooser->setCurrentItem(std::distance(mFunctionsIndexTable.begin(), iter));
  else
    on_FunctionChooser_activated(0);

  list.clear();

  VariableChooser->clear();
  updateVariablesStringList((CSensProblem::SubTaskType)index);
  VariableChooser->insertStringList(mVariablesStringList);

  // if valid, set current item to oldChoiceVar
  iter = std::find(mVariablesIndexTable.begin(),
                   mVariablesIndexTable.end(),
                   oldChoiceVar);
  if (iter != mVariablesIndexTable.end())
    VariableChooser->setCurrentItem(std::distance(mVariablesIndexTable.begin(), iter));
  else
    {
      on_VariableChooser_activated(0);
      on_Variable2Chooser_activated(0);
    }
}

void
SensitivitiesWidget::on_FunctionChooser_activated(int index)
{
  bool enabled = false;
  bool editenabled = false;

  if (index == 0)
    mChoicesDone &= ~Choice_Function;
  else if (index == 1) // Single Object
    {
      editenabled = true;
      if (mpSingleFunction)
        mChoicesDone |= Choice_Function;
      else
        mChoicesDone &= ~Choice_Function;
    }
  else
    mChoicesDone |= Choice_Function;

  enabled = (mChoicesDone == Choice_All);

  SingleFunctionChooser->setShown(editenabled);
  FunctionLineEdit->setShown(editenabled);

  mpBtnWidget->mpBtnRun->setEnabled(enabled);

  mFunction = mFunctionsIndexTable[index];
}

void
SensitivitiesWidget::on_VariableChooser_activated(int index)
{
  bool enabled = false;
  bool editenabled = false;
  if (index == 0)
    mChoicesDone &= ~Choice_Variable;
  else if (index == 1) // Single Object
    {
      editenabled = true;
      if (mpSingleVariable)
        mChoicesDone |= Choice_Variable;
      else
        mChoicesDone &= ~Choice_Variable;
    }
  else
    mChoicesDone |= Choice_Variable;

  enabled = (mChoicesDone == Choice_All);

  VariableLineEdit->setShown(editenabled);
  SingleVariableChooser->setShown(editenabled);

  mpBtnWidget->mpBtnRun->setEnabled(enabled);

  mVariable = mVariablesIndexTable[index];
}

void
SensitivitiesWidget::on_Variable2Chooser_activated(int index)
{
  bool editenabled = false;

  if (index == 1) // Single Object:  handled in the slots of LineEdit.
    editenabled = true;

  SingleVariable2Chooser->setShown(editenabled);
  Variable2LineEdit->setShown(editenabled);

  mVariable2 = mVariablesIndexTable[index];
}

void
SensitivitiesWidget::on_SingleFunctionChooser_clicked()
{
  CCopasiObject* chosenObject;
  CCopasiSelectionDialog* browseDialog = new CCopasiSelectionDialog(this);

  browseDialog->setModel(CCopasiDataModel::Global->getModel());

  browseDialog->setSingleSelection(true);

  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  browseDialog->setOutputVector(selection);

  if (browseDialog->exec() == QDialog::Accepted && selection->size() != 0)
    {
      chosenObject = selection->at(0);
      if (chosenObject)
        {
          mChoicesDone |= Choice_Function;
          FunctionLineEdit->setText(FROM_UTF8(chosenObject->getObjectDisplayName()));
          mpSingleFunction = chosenObject;
        }
    }

  mpBtnWidget->mpBtnRun->setEnabled((mChoicesDone == Choice_All));
}

void
SensitivitiesWidget::on_SingleVariableChooser_clicked()
{
  CCopasiObject* chosenObject;
  CCopasiSelectionDialog* browseDialog = new CCopasiSelectionDialog(this);

  browseDialog->setModel(CCopasiDataModel::Global->getModel());

  browseDialog->setSingleSelection(true);

  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  browseDialog->setOutputVector(selection);

  if (browseDialog->exec() == QDialog::Accepted && selection->size() != 0)
    {
      chosenObject = selection->at(0);
      if (chosenObject)
        {
          mChoicesDone |= Choice_Variable;
          VariableLineEdit->setText(FROM_UTF8(chosenObject->getObjectDisplayName()));
          mpSingleVariable = chosenObject;
        }
    }

  mpBtnWidget->mpBtnRun->setEnabled((mChoicesDone == Choice_All));
}

void
SensitivitiesWidget::on_SingleVariable2Chooser_clicked()
{
  CCopasiObject* chosenObject;
  CCopasiSelectionDialog* browseDialog = new CCopasiSelectionDialog(this);

  browseDialog->setModel(CCopasiDataModel::Global->getModel());

  browseDialog->setSingleSelection(true);

  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  browseDialog->setOutputVector(selection);

  if (browseDialog->exec() == QDialog::Accepted && selection->size() != 0)
    {
      chosenObject = selection->at(0);
      if (chosenObject)
        {
          Variable2LineEdit->setText(FROM_UTF8(chosenObject->getObjectDisplayName()));
          mpSingleVariable2 = chosenObject;
        }
    }
}
