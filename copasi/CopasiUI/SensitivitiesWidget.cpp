/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SensitivitiesWidget.cpp,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: tjohann $
   $Date: 2006/07/21 11:27:37 $
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
#include <qimage.h>

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

static const unsigned char button_image_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
    0x5c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xa5, 0x93, 0x4d, 0x4f, 0x13,
    0x71, 0x10, 0x87, 0x9f, 0xff, 0xee, 0xd6, 0xd6, 0xb6, 0xdb, 0x52, 0x5a,
    0x40, 0x81, 0x16, 0x85, 0x5a, 0x5e, 0x04, 0xa2, 0xa9, 0x26, 0x26, 0x98,
    0x88, 0x89, 0x07, 0xaf, 0xc6, 0x0f, 0xe8, 0x47, 0xc0, 0x98, 0x78, 0x30,
    0x6a, 0x0c, 0x97, 0x62, 0xc4, 0x82, 0xc8, 0x6b, 0x63, 0x43, 0xaa, 0xa0,
    0xad, 0x5d, 0xe8, 0xf2, 0x62, 0x29, 0xdd, 0x6d, 0x3b, 0x1e, 0x10, 0x22,
    0x41, 0xf4, 0xe0, 0x9c, 0x26, 0x33, 0xf3, 0xfc, 0x0e, 0xbf, 0x99, 0x51,
    0x99, 0x4c, 0x86, 0xff, 0x09, 0xe3, 0x6f, 0x4d, 0x9f, 0xaf, 0x2c, 0xae,
    0xab, 0x61, 0xdb, 0x65, 0xb6, 0xb6, 0x2a, 0x78, 0xbd, 0x06, 0x3d, 0x3d,
    0x77, 0xd4, 0x3f, 0x05, 0x4c, 0xd3, 0x96, 0x4a, 0xe5, 0x80, 0x6c, 0xb6,
    0x40, 0xa1, 0x50, 0xc7, 0xeb, 0x15, 0x62, 0x31, 0x61, 0x60, 0x20, 0x4a,
    0x38, 0x5c, 0x91, 0xdd, 0xdd, 0x76, 0x75, 0xae, 0x80, 0xcf, 0x57, 0x97,
    0xf9, 0xf9, 0x0d, 0xe6, 0xe6, 0x2c, 0x82, 0x41, 0xc5, 0xc4, 0x44, 0x37,
    0x89, 0x44, 0x02, 0x91, 0x1f, 0x18, 0x86, 0xf0, 0x3b, 0x7c, 0x46, 0xc0,
    0xb6, 0xbf, 0xca, 0xcc, 0xcc, 0x67, 0x2c, 0xeb, 0x80, 0x64, 0xd2, 0xc3,
    0xe8, 0x68, 0x2f, 0xe1, 0xf0, 0x80, 0x72, 0x1c, 0x00, 0x3f, 0xae, 0xfb,
    0x17, 0x0f, 0xf2, 0xf9, 0x9c, 0x64, 0xe7, 0x4a, 0x04, 0xfc, 0x1a, 0x93,
    0x93, 0x7d, 0xf4, 0xf5, 0x5d, 0x53, 0x67, 0xc7, 0xcf, 0x11, 0xc8, 0xe7,
    0xd7, 0x64, 0x61, 0xe1, 0x3b, 0x83, 0xa9, 0x20, 0xe9, 0xf4, 0x75, 0x9a,
    0x4d, 0xdf, 0x29, 0x38, 0xac, 0xd6, 0x44, 0x73, 0x04, 0x6b, 0x7d, 0x95,
    0xda, 0x4e, 0x85, 0x50, 0x7b, 0x94, 0xee, 0xe1, 0x34, 0x5f, 0x1b, 0x09,
    0x65, 0x94, 0x4a, 0x39, 0xc9, 0x66, 0xbf, 0x91, 0x4c, 0x06, 0x19, 0x1b,
    0xeb, 0x3a, 0x05, 0x07, 0xdc, 0x05, 0xd9, 0x2f, 0x16, 0x59, 0x5a, 0x5a,
    0xa2, 0xb4, 0xd1, 0xc4, 0xda, 0x0f, 0x50, 0x6f, 0x18, 0xb4, 0x7b, 0x3e,
    0x71, 0x75, 0x3e, 0xc7, 0xed, 0xc7, 0x0f, 0xc4, 0x98, 0x9d, 0x9d, 0xc7,
    0x34, 0x03, 0xa4, 0x52, 0x09, 0x74, 0xbd, 0xf7, 0x04, 0xbe, 0xb0, 0xf1,
    0x42, 0x16, 0x3f, 0xac, 0x91, 0x2b, 0x18, 0x78, 0xc2, 0x31, 0xe2, 0x63,
    0x6d, 0xdc, 0x1c, 0xe9, 0xc7, 0x17, 0x08, 0x52, 0xdb, 0xb6, 0xc9, 0x3e,
    0x7f, 0x49, 0x7e, 0xe6, 0x15, 0x86, 0x65, 0xd9, 0x8c, 0x8f, 0xb7, 0x61,
    0x9a, 0xc9, 0x13, 0x58, 0xcf, 0x3f, 0x93, 0x77, 0xaf, 0x57, 0xd8, 0xb9,
    0x18, 0x65, 0xf0, 0x5e, 0x92, 0xc1, 0xf1, 0x1b, 0xb8, 0x44, 0x14, 0x40,
    0x03, 0xd0, 0xcd, 0x4d, 0xb1, 0x1b, 0x21, 0x76, 0xec, 0x6f, 0x67, 0xd7,
    0x98, 0x08, 0x94, 0xe5, 0xcd, 0xdb, 0x45, 0x0e, 0x82, 0x31, 0x26, 0x1f,
    0x3d, 0x04, 0x7f, 0x5c, 0xfd, 0x6e, 0xbe, 0x6e, 0xbd, 0x97, 0xcc, 0xf4,
    0x3a, 0x5e, 0xd1, 0xb8, 0x9c, 0x7e, 0x88, 0xd1, 0xd1, 0x11, 0xa1, 0x54,
    0x72, 0xb0, 0xac, 0x15, 0xe9, 0xe8, 0x18, 0x51, 0xf5, 0xba, 0xcd, 0x8f,
    0xea, 0x01, 0xa1, 0x78, 0x83, 0x20, 0x45, 0xcc, 0xe6, 0xb6, 0xb4, 0x9a,
    0x0d, 0xaa, 0xd5, 0x2a, 0x85, 0x8f, 0xab, 0x7c, 0x59, 0x2c, 0x72, 0xa8,
    0x5d, 0x62, 0xfc, 0xfe, 0x18, 0x46, 0xf7, 0x5d, 0xa5, 0xa6, 0xa6, 0x9e,
    0xc8, 0xf4, 0xf4, 0x17, 0xa2, 0x51, 0x97, 0x91, 0xe1, 0x5e, 0xa2, 0xa1,
    0x06, 0x9b, 0xb3, 0x4f, 0x29, 0xe7, 0xca, 0x38, 0xc5, 0x0b, 0x38, 0x7b,
    0xa0, 0xeb, 0x1a, 0x8e, 0x3f, 0x42, 0x35, 0x10, 0xa3, 0x2b, 0xd5, 0xc6,
    0xc8, 0xad, 0x21, 0x22, 0xf1, 0xb4, 0x02, 0x50, 0x99, 0x4c, 0x86, 0x5a,
    0xad, 0x20, 0xcb, 0xcb, 0x6b, 0x2c, 0x2f, 0x7b, 0xa8, 0x1f, 0x2a, 0xdc,
    0x9a, 0x8d, 0xb3, 0x5f, 0xa7, 0xbe, 0x27, 0xe8, 0x2d, 0xa1, 0x27, 0x2e,
    0xa4, 0x46, 0x4d, 0xae, 0x0c, 0xc5, 0x69, 0xef, 0x8a, 0xa0, 0x79, 0xfa,
    0x4f, 0xfc, 0x52, 0xc7, 0xdf, 0xe8, 0xf1, 0x6c, 0x8a, 0xeb, 0x7a, 0x68,
    0xb5, 0xe4, 0xa8, 0xd3, 0x82, 0x96, 0x80, 0xae, 0x0c, 0xfc, 0xc1, 0x10,
    0xd2, 0xda, 0xe1, 0xd0, 0xe9, 0x3c, 0x73, 0x5c, 0x27, 0x26, 0xba, 0xee,
    0xd1, 0x0a, 0x35, 0xed, 0x57, 0x41, 0x83, 0xe3, 0xb4, 0x76, 0x08, 0xd0,
    0xf9, 0xc7, 0x4b, 0xfc, 0x09, 0x52, 0xcb, 0x07, 0x62, 0x36, 0x43, 0x92,
    0xc6, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60,
    0x82
  };

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
  QSize lineEditFormat;
  QImage img;

  img.loadFromData(button_image_data, sizeof(button_image_data), "PNG");

  // row where the header ends:
  const int fieldStart = 3;

  if (!name)
    setName("SensitivitiesWidget");
  setCaption(trUtf8("SensitivitiesWidget"));

  //if a mpMethodLayout is created here, it will be used by addMethodXXX() below.
  mpMethodLayout = new QGridLayout(this, 0, 1, 11, 6, "mpMethodLayout");

  mpHeaderWidget->setTaskName("Sensitivities");
  addHeaderToGrid();

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
  lineEditFormat = FunctionLineEdit->sizeHint();
  FunctionLineEdit->resize(lineEditFormat);
  mpMethodLayout->addMultiCellWidget(FunctionLineEdit, fieldStart + 5, fieldStart + 5, 1, 1);
  FunctionLineEdit->setText("[Please Choose Object.] --->");
  FunctionLineEdit->setReadOnly(true);
  FunctionLineEdit->hide();

  SingleFunctionChooser = new QToolButton(this, "SingleFunctionChooser");
  mpMethodLayout->addWidget(SingleFunctionChooser, fieldStart + 5, 2);
  SingleFunctionChooser->setMaximumSize(lineEditFormat.height(),
                                         lineEditFormat.height());
  SingleFunctionChooser->setIconSet(QIconSet(img));
  SingleFunctionChooser->hide();

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Variable:"));
  TextLabel3->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  mpMethodLayout->addWidget(TextLabel3, fieldStart + 6, 0);

  VariableChooser = new QComboBox(FALSE, this, "VariableChooser");

  mpMethodLayout->addMultiCellWidget(VariableChooser, fieldStart + 6, fieldStart + 6, 1, 1);

  VariableLineEdit = new QLineEdit(this, "VariableLineEdit");
  VariableLineEdit->resize(lineEditFormat);
  mpMethodLayout->addMultiCellWidget(VariableLineEdit, fieldStart + 7, fieldStart + 7, 1, 1);
  VariableLineEdit->setText("[Please Choose Object.] --->");
  VariableLineEdit->setReadOnly(true);
  VariableLineEdit->hide();

  SingleVariableChooser = new QToolButton(this, "SingleVariableChooser");
  mpMethodLayout->addWidget(SingleVariableChooser, fieldStart + 7, 2);
  SingleVariableChooser->setMaximumSize(lineEditFormat.height(),
                                         lineEditFormat.height());
  SingleVariableChooser->setIconSet(QIconSet(img));
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
  Variable2LineEdit->resize(lineEditFormat);
  mpMethodLayout->addMultiCellWidget(Variable2LineEdit, fieldStart + 9, fieldStart + 9, 1, 1);
  Variable2LineEdit->setText("[Please Choose Object.] --->");
  Variable2LineEdit->setReadOnly(true);
  Variable2LineEdit->hide();

  SingleVariable2Chooser = new QToolButton(this, "SingleVariable2Chooser");
  mpMethodLayout->addWidget(SingleVariable2Chooser, fieldStart + 9, 2);
  SingleVariable2Chooser->setMaximumSize(lineEditFormat.height(),
                                          lineEditFormat.height());
  SingleVariable2Chooser->setIconSet(QIconSet(img));
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
