// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QtGui/QImage>
#include <QtGui/QFrame>
#include <QtCore/QtDebug>

#include <algorithm>

#include "SensitivitiesWidget.h"
#include "DataModelGUI.h"
#include "qtUtilities.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskMethodWidget.h"
#include "CCopasiSelectionDialog.h"
#include "resourcesUI/CQIconResource.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "sensitivities/CSensTask.h"
#include "sensitivities/CSensProblem.h"
#include "sensitivities/CSensMethod.h"
#include "model/CModel.h"
#include "utilities/CCopasiException.h"
#include "report/CKeyFactory.h"
#include "CQSensResultWidget.h"

/**
 *  Constructs a SensitivitiesWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
SensitivitiesWidget::SensitivitiesWidget(QWidget* parent, const char* name, Qt::WFlags fl)
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

bool SensitivitiesWidget::saveTask()
{
  saveCommon();
  saveMethod();

  CSensTask* sensTask =
    dynamic_cast<CSensTask *>(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (sensTask == NULL)
    return false;

  CSensProblem* problem =
    dynamic_cast<CSensProblem *>(sensTask->getProblem());

  if (problem == NULL)
    return false;

  CSensMethod* method =
    dynamic_cast<CSensMethod *>(sensTask->getMethod());

  if (method == NULL)
    return false;

  // subtask
  problem->setSubTaskType((CSensProblem::SubTaskType)SubTaskChooser->currentIndex());

  CSensItem tmp;

  // target function
  if (FunctionChooser->getCurrentObjectList() == CObjectLists::SINGLE_OBJECT)
    {
      if (mpSingleFunction)
        tmp.setSingleObjectCN(mpSingleFunction->getCN());
    }
  else
    tmp.setListType(FunctionChooser->getCurrentObjectList());

  problem->changeTargetFunctions(tmp);

  // variables 1
  if (VariableChooser->getCurrentObjectList() == CObjectLists::SINGLE_OBJECT)
    {
      if (mpSingleVariable)
        tmp.setSingleObjectCN(mpSingleVariable->getCN());
    }
  else
    tmp.setListType(VariableChooser->getCurrentObjectList());

  problem->removeVariables();

  if (tmp.getListType() != CObjectLists::EMPTY_LIST)
    problem->addVariables(tmp);
  else
    return true;

  //variables 2
  CSensItem tmp2;

  if (Variable2Chooser->getCurrentObjectList() == CObjectLists::SINGLE_OBJECT)
    {
      if (mpSingleVariable2)
        tmp2.setSingleObjectCN(mpSingleVariable2->getCN());
    }
  else
    tmp2.setListType(Variable2Chooser->getCurrentObjectList());

  // write variables to problem
  problem->removeVariables();

  if (tmp.getListType() != CObjectLists::EMPTY_LIST)
    {
      problem->addVariables(tmp);

      if (tmp2.getListType() != CObjectLists::EMPTY_LIST)
        problem->addVariables(tmp2);
    }

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  // However we do not track the changes for the variables we just delete them and add them again.
  if (true)
    {
      if (mpDataModel != NULL)
        {
          mpDataModel->changed();
        }

      mChanged = false;
    }

  return true;
}

CCopasiMethod * SensitivitiesWidget::createMethod(const CCopasiMethod::SubType & type)
{return CSensMethod::createMethod(type);}

bool SensitivitiesWidget::runTask()
{
  if (FunctionChooser->getCurrentObjectList() != CObjectLists::SINGLE_OBJECT)
    FunctionLineEdit->setText(QApplication::translate("SensitivitiesWidget", "[Please Choose Object.] --->", 0, QApplication::UnicodeUTF8));

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
    dynamic_cast<CQSensResultWidget*>(mpListView->findWidgetFromId(341));

  if (pResult) pResult->newResult();

  if (success && isVisible()) mpListView->switchToOtherWidget(341, ""); //change to the results window

  return success;
}

bool SensitivitiesWidget::loadTask()
{
  loadCommon();
  loadMethod();

  CSensTask* sensTask =
    dynamic_cast<CSensTask *>(CCopasiRootContainer::getKeyFactory()->get(mKey));
  assert(sensTask);

  CSensProblem* problem =
    dynamic_cast<CSensProblem *>(sensTask->getProblem());
  assert(problem);

  //CSensMethod* method =
  //  dynamic_cast<CSensMethod *>(sensTask->getMethod());
  //assert(method);

  //mSubTaskType = problem->getSubTaskType();
  SubTaskChooser->setCurrentIndex((int)problem->getSubTaskType());
  updateComboBoxes(problem->getSubTaskType());

  CSensItem tmp = problem->getTargetFunctions();

  //target function
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  if (tmp.isSingleObject())
    {
      FunctionChooser->setCurrentObjectList(CObjectLists::SINGLE_OBJECT);
      mpSingleFunction = pDataModel->getDataObject(tmp.getSingleObjectCN());

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
          mpSingleVariable = pDataModel->getDataObject(tmp.getSingleObjectCN());

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
          mpSingleVariable2 = pDataModel->getDataObject(tmp.getSingleObjectCN());

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

void SensitivitiesWidget::updateLineeditEnable(const SensWidgetComboBox* box, QWidget* w1, QWidget* w2)
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
  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this,
        CQSimpleSelectionTree::Variables |
        CQSimpleSelectionTree::ObservedValues);

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
  const CCopasiObject * pObject =
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
  const CCopasiObject * pObject =
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
