/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SensitivitiesWidget.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: tjohann $
   $Date: 2006/06/29 17:22:29 $
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

#include "SensitivitiesWidget.h"
#include "DataModelGUI.h"
#include "qtUtilities.h"
#include "listviews.h"
#include "CProgressBar.h"
#include "copasiui3window.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"

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
    : TaskWidget(parent, name, fl)
{
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

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Function:"));
  TextLabel2->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  mpMethodLayout->addWidget(TextLabel2, fieldStart + 2, 0);

  FunctionChooser = new QComboBox(FALSE, this, "TargetFunctionChooser");
  //  FunctionChooser->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, FunctionChooser->sizePolicy().hasHeightForWidth()));
  mpMethodLayout->addMultiCellWidget(FunctionChooser, fieldStart + 2, fieldStart + 2, 1, 1);

  FunctionLineEdit = new QLineEdit(this, "FunctionLineEdit");
  FunctionLineEdit->setDisabled(true);
  mpMethodLayout->addMultiCellWidget(FunctionLineEdit, fieldStart + 2, fieldStart + 2, 2, 2);

  //  FunctionChoiceBox = new QListView(this, "FunctionChoiceBox");
  //  mpMethodLayout->addMultiCellWidget(FunctionChoiceBox,fieldStart+2, fieldStart+2, 2, 2);

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Variable:"));
  TextLabel3->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  mpMethodLayout->addWidget(TextLabel3, fieldStart + 3, 0);

  VariableChooser = new QComboBox(FALSE, this, "VariableChooser");
  //  VariableChooser->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, VariableChooser->sizePolicy().hasHeightForWidth()));
  mpMethodLayout->addMultiCellWidget(VariableChooser, fieldStart + 3, fieldStart + 3, 1, 1);

  VariableLineEdit = new QLineEdit(this, "VariableLineEdit");
  VariableLineEdit->setDisabled(true);
  mpMethodLayout->addMultiCellWidget(VariableLineEdit, fieldStart + 3, fieldStart + 3, 2, 2);

  TextLabel4 = new QLabel(this, "TextLabel4");
  TextLabel4->setText(trUtf8("Second Variable"));
  TextLabel4->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  mpMethodLayout->addWidget(TextLabel4, fieldStart + 4, 0);

  VariableChooser2 = new QComboBox(FALSE, this, "VariableChooser2");
  //  VariableChooser2->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, VariableChooser2->sizePolicy().hasHeightForWidth()));
  mpMethodLayout->addMultiCellWidget(VariableChooser2, fieldStart + 4, fieldStart + 4, 1, 1);

  VariableLineEdit2 = new QLineEdit(this, "VariableLineEdit2");
  VariableLineEdit2->setDisabled(true);
  mpMethodLayout->addMultiCellWidget(VariableLineEdit2, fieldStart + 4, fieldStart + 4, 2, 2);
  //  VariableChoiceBox = new QListView(this, "VariableChoiceBox");
  //  mpMethodLayout->addMultiCellWidget(VariableChoiceBox,fieldStart+3, fieldStart+3, 2, 2);

  QSpacerItem* spacer2 = new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
  mpMethodLayout->addItem(spacer2, fieldStart + 5, fieldStart + 5);

  initCombos();

  addHLineToGrid(mpMethodLayout, fieldStart + 6, 2);

  addMethodParameterTable(4, fieldStart + 7);

  mpMethodLayout->addMultiCellWidget(mpBtnWidget, 11, 11, 0, 2);
  mpBtnWidget->mpBtnRun->setEnabled(false);

  connect(SubTaskChooser, SIGNAL(activated(int)),
           this, SLOT(on_SubTaskChooser_activated(int)));
  connect(FunctionChooser, SIGNAL(activated(int)),
           this, SLOT(on_FunctionChooser_activated(int)));
  connect(VariableChooser, SIGNAL(activated(int)),
           this, SLOT(on_VariableChooser_activated(int)));
  connect(VariableChooser2, SIGNAL(activated(int)),
           this, SLOT(on_VariableChooser2_activated(int)));

  mChoicesDone = 0;
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
      StringList.append(CSensProblem::SubTaskName[i]);
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
  VariableChooser2->insertStringList(mVariablesStringList);
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
      mFunctionsStringList.append(CObjectLists::ListTypeName[*fiter]);
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
      mVariablesStringList.append(CObjectLists::ListTypeName[*viter]);
      mVariablesIndexTable.push_back(*viter);
    }
}

/*
std::vector<QCheckListItem *>
SensitivitiesWidget::initCheckboxes(CObjectLists::ListType type)
{
  std::vector<QCheckListItem *> choices;


  choices.clear();


  // if type is 'unset' return empty vector:
  //  if ((int) type == 0)
  //    return choices;


  QCheckListItem *test =
    new QCheckListItem(FunctionChoiceBox, "parent", QCheckListItem::CheckBox);
  choices.push_back(test);
  FunctionChoiceBox->ensureItemVisible(test);


  QCheckListItem *test2 =
    new QCheckListItem(test, "child", QCheckListItem::CheckBox);
  choices.push_back(test2);


  return choices;
}
 */

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
      mChoicesDone &= ~1;
    }
  else
    {
      mChoicesDone |= 1;
      enabled = mChoicesDone == 7;
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
      on_VariableChooser2_activated(0);
    }
}

void
SensitivitiesWidget::on_FunctionChooser_activated(int index)
{
  FunctionLineEdit->clear();

  bool enabled = false;
  bool editenabled = false;
  if (index == 0)
    mChoicesDone &= ~2;
  else if (index == 1) // Single Object
    {
      editenabled = true;
      mChoicesDone &= ~2;
    }
  else
    {
      mChoicesDone |= 2;
      enabled = (mChoicesDone == 7);
      FunctionLineEdit->setText(mFunctionsStringList[index]);
    }

  FunctionLineEdit->setEnabled(editenabled);
  mpBtnWidget->mpBtnRun->setEnabled(enabled);
}

void
SensitivitiesWidget::on_VariableChooser_activated(int index)
{
  VariableLineEdit->clear();

  bool enabled = false;
  bool editenabled = false;
  if (index == 0)
    mChoicesDone &= ~4;
  else if (index == 1) // Single Object
    {
      editenabled = true;
      mChoicesDone &= ~4;
    }
  else
    {
      mChoicesDone |= 4;
      enabled = (mChoicesDone == 7);
      VariableLineEdit->setText(mVariablesStringList[index]);
    }

  VariableLineEdit->setEnabled(editenabled);
  mpBtnWidget->mpBtnRun->setEnabled(enabled);
}

void
SensitivitiesWidget::on_VariableChooser2_activated(int index)
{
  VariableLineEdit2->clear();

  bool enabled = false;
  if (index == 1) // Single Object
    enabled = true;
  else
    VariableLineEdit2->setText(mVariablesStringList[index]);

  VariableLineEdit2->setEnabled(enabled);
}
