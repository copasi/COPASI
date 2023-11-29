// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QImage>
#include <QFrame>
#include <QtCore/QtDebug>

#include <algorithm>

#include "SensitivitiesWidget.h"
#include "DataModelGUI.h"
#include "qtUtilities.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskMethodWidget.h"
#include "CCopasiSelectionDialog.h"
#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/sensitivities/CSensTask.h"
#include "copasi/sensitivities/CSensProblem.h"
#include "copasi/sensitivities/CSensMethod.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/report/CKeyFactory.h"
#include "CQSensResultWidget.h"

/**
 *  Constructs a SensitivitiesWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
SensitivitiesWidget::SensitivitiesWidget(QWidget *parent, const char *name, Qt::WindowFlags fl)
  : TaskWidget(parent, name, fl),
    mpSingleFunction(NULL),
    mpSingleVariable(NULL),
    mpSingleVariable2(NULL)
{
  setupUi(this);
  init();
  retranslateUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
SensitivitiesWidget::~SensitivitiesWidget()
{}

void SensitivitiesWidget::init()
{
  mpHeaderWidget->setTaskName("Sensitivities");
  verticalLayout->insertWidget(0, mpHeaderWidget);  // header
  // verticalLayout->insertSpacing(1, 14);      // space between header and body
  mpMethodWidget->showMethodParameters(true);
  verticalLayout->addWidget(mpMethodWidget);
  verticalLayout->addWidget(mpBtnWidget);     // 'footer'
  // icons
  SingleFunctionChooser->setIcon(CQIconResource::icon(CQIconResource::copasi));
  SingleVariableChooser->setIcon(CQIconResource::icon(CQIconResource::copasi));
  SingleVariable2Chooser->setIcon(CQIconResource::icon(CQIconResource::copasi));
  // initialization
  initCombos();
}

bool SensitivitiesWidget::saveTaskProtected()
{
  CSensTask *sensTask =
    dynamic_cast<CSensTask *>(mpObject);

  if (sensTask == NULL)
    return false;

  CSensProblem *problem =
    dynamic_cast<CSensProblem *>(sensTask->getProblem());

  if (problem == NULL)
    return false;

  CSensMethod *method =
    dynamic_cast<CSensMethod *>(sensTask->getMethod());

  if (method == NULL)
    return false;

  // subtask
  problem->setSubTaskType((CSensProblem::SubTaskType)SubTaskChooser->currentIndex());
  // target function
  CSensItem TargetFunctions;

  if (FunctionChooser->getCurrentObjectList() == CObjectLists::SINGLE_OBJECT)
    {
      if (mpSingleFunction)
        TargetFunctions.setSingleObjectCN(mpSingleFunction->getCN());
    }
  else
    TargetFunctions.setListType(FunctionChooser->getCurrentObjectList());

  if (problem->getTargetFunctions() != TargetFunctions)
    {
      problem->setTargetFunctions(TargetFunctions);
      mChanged = true;
    }

  // variables 1
  CSensItem FirstVariables;

  if (VariableChooser->getCurrentObjectList() == CObjectLists::SINGLE_OBJECT)
    {
      if (mpSingleVariable)
        FirstVariables.setSingleObjectCN(mpSingleVariable->getCN());
    }
  else
    FirstVariables.setListType(VariableChooser->getCurrentObjectList());

  if (problem->getNumberOfVariables() < 1 ||
      problem->getVariables(0) != FirstVariables)
    {
      problem->changeVariables(0, FirstVariables);
      mChanged = true;
    }

  //variables 2
  CSensItem SecondVariables;

  if (Variable2Chooser->getCurrentObjectList() == CObjectLists::SINGLE_OBJECT)
    {
      if (mpSingleVariable2)
        SecondVariables.setSingleObjectCN(mpSingleVariable2->getCN());
    }
  else
    SecondVariables.setListType(Variable2Chooser->getCurrentObjectList());

  if (problem->getNumberOfVariables() < 2 ||
      problem->getVariables(1) != SecondVariables)
    {
      problem->changeVariables(1, SecondVariables);
      mChanged = true;
    }

  // Bug 322: This should only be called when actual changes have been saved.
  if (mChanged)
    {
      if (mpDataModel != NULL)
        {
          mpDataModel->changed();
        }

      mChanged = false;
    }

  return true;
}

bool SensitivitiesWidget::runTask()
{
  if (FunctionChooser->getCurrentObjectList() != CObjectLists::SINGLE_OBJECT)
    {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
      FunctionLineEdit->setText("[Please Choose Object.] --->");
#else
      FunctionLineEdit->setText(QApplication::translate("SensitivitiesWidget", "[Please Choose Object.] --->", 0, QApplication::UnicodeUTF8));
#endif
    }

  if (!commonBeforeRunTask()) return false;

  bool success = true;

  if (!commonRunTask()) success = false;

  return success;
}

bool SensitivitiesWidget::taskFinishedEvent()
{
  bool success = true;
  //setup the result widget
  CQSensResultWidget *pResult =
    dynamic_cast<CQSensResultWidget *>(mpListView->createWidgetFromId(ListViews::WidgetType::SensitivitiesResult));

  if (pResult) pResult->newResult();

  if (success && isVisible()) mpListView->switchToOtherWidget(ListViews::WidgetType::SensitivitiesResult, std::string()); //change to the results window

  return success;
}

bool SensitivitiesWidget::loadTaskProtected()
{
  CSensTask *sensTask =
    dynamic_cast<CSensTask *>(mpObject);
  assert(sensTask);
  CSensProblem *problem =
    dynamic_cast<CSensProblem *>(sensTask->getProblem());
  assert(problem);
  //CSensMethod* method =
  //  dynamic_cast<CSensMethod *>(sensTask->getMethod());
  //assert(method);
  //mSubTaskType = problem->getSubTaskType();
  SubTaskChooser->setCurrentIndex((int)problem->getSubTaskType());
  updateComboBoxes(problem->getSubTaskType());
  CSensItem tmp = problem->getTargetFunctions();

  if (tmp.isSingleObject())
    {
      FunctionChooser->setCurrentObjectList(CObjectLists::SINGLE_OBJECT);
      mpSingleFunction = CObjectInterface::DataObject(mpDataModel->getObjectFromCN(tmp.getSingleObjectCN()));

      if (mpSingleFunction)
        FunctionLineEdit->setText(FROM_UTF8(mpSingleFunction->getObjectDisplayName()));
    }
  else
    {
      mpSingleFunction = NULL;
      FunctionChooser->setCurrentObjectList(tmp.getListType());
    }

  //variables 1
  if (problem->getNumberOfVariables() > 0)
    {
      tmp = problem->getVariables(0);

      if (tmp.isSingleObject())
        {
          VariableChooser->setCurrentObjectList(CObjectLists::SINGLE_OBJECT);
          mpSingleVariable = CObjectInterface::DataObject(mpDataModel->getObjectFromCN(tmp.getSingleObjectCN()));

          if (mpSingleVariable)
            VariableLineEdit->setText(FROM_UTF8(mpSingleVariable->getObjectDisplayName()));
        }
      else
        VariableChooser->setCurrentObjectList(tmp.getListType());
    }
  else
    {
      VariableChooser->setCurrentObjectList(CObjectLists::EMPTY_LIST);
      mpSingleVariable = NULL;
    }

  //variables 2
  if (problem->getNumberOfVariables() > 1)
    {
      tmp = problem->getVariables(1);

      if (tmp.isSingleObject())
        {
          Variable2Chooser->setCurrentObjectList(CObjectLists::SINGLE_OBJECT);
          mpSingleVariable2 = CObjectInterface::DataObject(mpDataModel->getObjectFromCN(tmp.getSingleObjectCN()));

          if (mpSingleVariable2)
            Variable2LineEdit->setText(FROM_UTF8(mpSingleVariable2->getObjectDisplayName()));
        }
      else
        Variable2Chooser->setCurrentObjectList(tmp.getListType());
    }
  else
    {
      Variable2Chooser->setCurrentObjectList(CObjectLists::EMPTY_LIST);
      mpSingleVariable2 = NULL;
    }

  //  initCombos(problem);
  mChanged = false;
  updateAllLineditEnable();
  return true;
}

//**************************************************************************

void SensitivitiesWidget::updateLineeditEnable(const SensWidgetComboBox *box, QWidget *w1, QWidget *w2)
{
  if (!box) return;

  bool enable = false;

  if (box->getCurrentObjectList() == CObjectLists::SINGLE_OBJECT)
    enable = true;

  if (w1) w1->setVisible(enable);

  if (w2) w2->setVisible(enable);
}

void SensitivitiesWidget::updateAllLineditEnable()
{
  /*
    updateLineeditEnable(FunctionChooser, FunctionLineEdit, SingleFunctionChooserButton);
    updateLineeditEnable(VariableChooser, VariableLineEdit, SingleVariableChooserButton);
    updateLineeditEnable(Variable2Chooser, Variable2LineEdit, SingleVariable2ChooserButton);
  */
  updateLineeditEnable(FunctionChooser, FunctionLineEdit, SingleFunctionChooser);
  updateLineeditEnable(VariableChooser, VariableLineEdit, SingleVariableChooser);
  updateLineeditEnable(Variable2Chooser, Variable2LineEdit, SingleVariable2Chooser);
}

void
SensitivitiesWidget::initCombos()
{
  QStringList StringList;
  //std::vector<int> mFunctionIndexTable, mVariableIndexTable;
  // SubTaskChooser combo
  int i = 0;

  while (CSensProblem::SubTaskName[i].length() > 0)
    {
      StringList.append(FROM_UTF8(CSensProblem::SubTaskName[i]));
      ++i;
    }

  SubTaskChooser->insertItems(SubTaskChooser->count(), StringList);
  SubTaskChooser->setCurrentIndex(0);
  updateComboBoxes((CSensProblem::SubTaskType)0);
}

void SensitivitiesWidget::updateComboBoxes(CSensProblem::SubTaskType type)
{
  FunctionChooser->fillFromList(CSensProblem::getPossibleTargetFunctions(type));
  VariableChooser->fillFromList(CSensProblem::getPossibleVariables(type));
  Variable2Chooser->fillFromList(CSensProblem::getPossibleVariables(type));
}

// ******************* SLOTs *******************************+

void
//SensitivitiesWidget::on_SubTaskChooser_activated(int)
SensitivitiesWidget::slotChooseSubTask(int)
{
  CSensProblem::SubTaskType subTaskType = (CSensProblem::SubTaskType)SubTaskChooser->currentIndex();
  updateComboBoxes(subTaskType);
  updateAllLineditEnable();
}

void
//SensitivitiesWidget::on_FunctionChooser_activated(int a)
SensitivitiesWidget::slotChooseFunction(int)
{
  updateAllLineditEnable();
}

void
//SensitivitiesWidget::on_VariableChooser_activated(int)
SensitivitiesWidget::slotChooseVariable(int)
{
  updateAllLineditEnable();
}

void
//SensitivitiesWidget::on_Variable2Chooser_activated(int)
SensitivitiesWidget::slotChooseVariable2(int)
{
  updateAllLineditEnable();
}

void
//SensitivitiesWidget::on_SingleFunctionChooser_clicked()
SensitivitiesWidget::slotChooseSingleFunction()
{
  const CDataObject *pObject =
    CCopasiSelectionDialog::getObjectSingle(this,
        CQSimpleSelectionTree::Variables |
        CQSimpleSelectionTree::ObservedValues |
        CQSimpleSelectionTree::EventTarget);

  if (pObject)
    {
      FunctionLineEdit->setText(FROM_UTF8(pObject->getObjectDisplayName()));
      mpSingleFunction = pObject;
      FunctionChooser->setCurrentObjectList(CObjectLists::SINGLE_OBJECT);
    }
}

void
//SensitivitiesWidget::on_SingleVariableChooser_clicked()
SensitivitiesWidget::slotChooseSingleVariable()
{
  const CDataObject *pObject =
    CCopasiSelectionDialog::getObjectSingle(this,
        CQSimpleSelectionTree::InitialTime |
        CQSimpleSelectionTree::Parameters);

  if (pObject)
    {
      VariableLineEdit->setText(FROM_UTF8(pObject->getObjectDisplayName()));
      mpSingleVariable = pObject;
      VariableChooser->setCurrentObjectList(CObjectLists::SINGLE_OBJECT);
    }
}

void
//SensitivitiesWidget::on_SingleVariable2Chooser_clicked()
SensitivitiesWidget::slotChooseSingleVariable2()
{
  const CDataObject *pObject =
    CCopasiSelectionDialog::getObjectSingle(this,
        CQSimpleSelectionTree::InitialTime |
        CQSimpleSelectionTree::Parameters);

  if (pObject)
    {
      Variable2LineEdit->setText(FROM_UTF8(pObject->getObjectDisplayName()));
      mpSingleVariable2 = pObject;
      Variable2Chooser->setCurrentObjectList(CObjectLists::SINGLE_OBJECT);
    }
}
