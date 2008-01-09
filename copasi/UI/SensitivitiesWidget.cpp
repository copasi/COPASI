// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SensitivitiesWidget.cpp,v $
//   $Revision: 1.25 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/09 14:53:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qfiledialog.h>

#include <qvariant.h>
#include <qcheckbox.h>
//#include <qcombobox.h>
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
//#include "listviews.h"
//#include "CProgressBar.h"
//#include "copasiui3window.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CCopasiSelectionDialog.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "sensitivities/CSensTask.h"
#include "sensitivities/CSensProblem.h"
#include "model/CModel.h"
#include "utilities/CCopasiException.h"
#include "report/CKeyFactory.h"
//#include "parametertable.h"
#include "CQSensResultWidget.h"

SensWidgetComboBox::SensWidgetComboBox(QWidget * parent, const char * name)
    : QComboBox(FALSE, parent, name)
{}

void SensWidgetComboBox::fillFromList(const std::vector<CObjectLists::ListType> & list)
{
  //store old selection
  CObjectLists::ListType oldItem = getCurrentObjectList();

  mIndexTable = list;

  //fill combobox
  clear();
  std::vector<CObjectLists::ListType>::const_iterator it, itEnd = mIndexTable.end();
  for (it = mIndexTable.begin(); it != itEnd; ++it)
    insertItem(FROM_UTF8(CObjectLists::ListTypeName[*it]));

  //restore old selection, if possible
  if (!setCurrentObjectList(oldItem))
    setCurrentItem(0);
}

CObjectLists::ListType SensWidgetComboBox::getCurrentObjectList() const
  {
    unsigned int index = currentItem();
    if (index < mIndexTable.size())
      return mIndexTable[currentItem()];
    else
      return CObjectLists::EMPTY_LIST;
  }

bool SensWidgetComboBox::setCurrentObjectList(CObjectLists::ListType lt)
{
  std::vector<CObjectLists::ListType>::const_iterator it;
  it = std::find(mIndexTable.begin(),
                 mIndexTable.end(),
                 lt);

  if (it == mIndexTable.end()) return false;

  setCurrentItem(it - mIndexTable.begin());
  return true;
}

//**************** SensitivitiesWidget *********************************

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

  //addHLineToGrid(mpMethodLayout, 2, 2);

  //QSpacerItem* spacer1 = new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
  //mpMethodLayout->addItem(spacer1, 3, 3);

  //******** subtask ******************

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Subtask Method"));
  TextLabel1->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  mpMethodLayout->addWidget(TextLabel1, fieldStart + 1, 0);

  SubTaskChooser = new QComboBox(FALSE, this, "SubTaskChooser");
  SubTaskChooser->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, SubTaskChooser->sizePolicy().hasHeightForWidth()));
  mpMethodLayout->addWidget(SubTaskChooser, fieldStart + 1, 1);

  QSpacerItem* spacer2 = new QSpacerItem(4, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);
  mpMethodLayout->addItem(spacer2, fieldStart + 2, 0);

  addHLineToGrid(mpMethodLayout, fieldStart + 3, 2);

  //*********** function *******************

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Function"));
  TextLabel2->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  mpMethodLayout->addWidget(TextLabel2, fieldStart + 4, 0);

  FunctionChooser = new SensWidgetComboBox(this, "TargetFunctionChooser");
  //  FunctionChooser->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, FunctionChooser->sizePolicy().hasHeightForWidth()));
  mpMethodLayout->addMultiCellWidget(FunctionChooser, fieldStart + 4, fieldStart + 4, 1, 1);

  FunctionLineEdit = new QLineEdit(this, "FunctionLineEdit");
  lineEditFormat = FunctionLineEdit->sizeHint();
  FunctionLineEdit->resize(lineEditFormat);
  mpMethodLayout->addMultiCellWidget(FunctionLineEdit, fieldStart + 5, fieldStart + 5, 1, 1);
  FunctionLineEdit->setText("[Please Choose Object.] --->");
  FunctionLineEdit->setReadOnly(true);
  FunctionLineEdit->setEnabled(false); //hide();

  SingleFunctionChooser = new QToolButton(this, "SingleFunctionChooser");
  mpMethodLayout->addWidget(SingleFunctionChooser, fieldStart + 5, 2);
  SingleFunctionChooser->setMaximumSize(lineEditFormat.height(),
                                        lineEditFormat.height());
  SingleFunctionChooser->setIconSet(QIconSet(img));
  SingleFunctionChooser->setEnabled(false); //hide();

  //*********** variable 1 **********************

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Variable"));
  TextLabel3->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  mpMethodLayout->addWidget(TextLabel3, fieldStart + 6, 0);

  VariableChooser = new SensWidgetComboBox(this, "VariableChooser");

  mpMethodLayout->addMultiCellWidget(VariableChooser, fieldStart + 6, fieldStart + 6, 1, 1);

  VariableLineEdit = new QLineEdit(this, "VariableLineEdit");
  VariableLineEdit->resize(lineEditFormat);
  mpMethodLayout->addMultiCellWidget(VariableLineEdit, fieldStart + 7, fieldStart + 7, 1, 1);
  VariableLineEdit->setText("[Please Choose Object.] --->");
  VariableLineEdit->setReadOnly(true);
  VariableLineEdit->setEnabled(false); //hide();

  SingleVariableChooser = new QToolButton(this, "SingleVariableChooser");
  mpMethodLayout->addWidget(SingleVariableChooser, fieldStart + 7, 2);
  SingleVariableChooser->setMaximumSize(lineEditFormat.height(),
                                        lineEditFormat.height());
  SingleVariableChooser->setIconSet(QIconSet(img));
  SingleVariableChooser->setEnabled(false); //hide();

  //********** variable 2 **********************

  TextLabel4 = new QLabel(this, "TextLabel4");
  TextLabel4->setText(trUtf8("Second Variable"));
  TextLabel4->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  mpMethodLayout->addWidget(TextLabel4, fieldStart + 8, 0);

  Variable2Chooser = new SensWidgetComboBox(this, "Variable2Chooser");
  //  Variable2Chooser->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, Variable2Chooser->sizePolicy().hasHeightForWidth()));
  mpMethodLayout->addMultiCellWidget(Variable2Chooser, fieldStart + 8, fieldStart + 8, 1, 1);

  Variable2LineEdit = new QLineEdit(this, "Variable2LineEdit");
  Variable2LineEdit->resize(lineEditFormat);
  mpMethodLayout->addMultiCellWidget(Variable2LineEdit, fieldStart + 9, fieldStart + 9, 1, 1);
  Variable2LineEdit->setText("[Please Choose Object.] --->");
  Variable2LineEdit->setReadOnly(true);
  Variable2LineEdit->setEnabled(false); //hide();

  SingleVariable2Chooser = new QToolButton(this, "SingleVariable2Chooser");
  mpMethodLayout->addWidget(SingleVariable2Chooser, fieldStart + 9, 2);
  SingleVariable2Chooser->setMaximumSize(lineEditFormat.height(),
                                         lineEditFormat.height());
  SingleVariable2Chooser->setIconSet(QIconSet(img));
  SingleVariable2Chooser->setEnabled(false); //hide();

  //**********************************************

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

  //mChoicesDone = 0;
}

/*
 *  Destroys the object and frees any allocated resources
 */
SensitivitiesWidget::~SensitivitiesWidget()
{}

bool SensitivitiesWidget::saveTask()
{
  saveCommon();
  saveMethod();

  CSensTask* sensTask =
    dynamic_cast<CSensTask *>(GlobalKeys.get(mObjectKey));
  assert(sensTask);

  CSensProblem* problem =
    dynamic_cast<CSensProblem *>(sensTask->getProblem());
  assert(problem);

  CSensMethod* method =
    dynamic_cast<CSensMethod *>(sensTask->getMethod());
  assert(method);

  // subtask
  problem->setSubTaskType((CSensProblem::SubTaskType)SubTaskChooser->currentItem());

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
  if (mChanged) CCopasiDataModel::Global->changed();

  return true;
}

CCopasiMethod * SensitivitiesWidget::createMethod(const CCopasiMethod::SubType & type)
{return CSensMethod::createSensMethod(type);}

bool SensitivitiesWidget::runTask()
{
  if (!commonBeforeRunTask()) return false;

  bool success = true;
  if (!commonRunTask()) success = false;

  if (!commonAfterRunTask()) success = false;

  //setup the result widget
  CQSensResultWidget *pResult =
    dynamic_cast<CQSensResultWidget*>(mpListView->findWidgetFromId(341));
  if (pResult) pResult->newResult();

  if (success && isShown()) mpListView->switchToOtherWidget(341, ""); //change to the results window

  return success;
}

bool SensitivitiesWidget::loadTask()
{
  loadCommon();
  loadMethod();

  CSensTask* sensTask =
    dynamic_cast<CSensTask *>(GlobalKeys.get(mObjectKey));
  assert(sensTask);

  CSensProblem* problem =
    dynamic_cast<CSensProblem *>(sensTask->getProblem());
  assert(problem);

  CSensMethod* method =
    dynamic_cast<CSensMethod *>(sensTask->getMethod());
  assert(method);

  //mSubTaskType = problem->getSubTaskType();
  SubTaskChooser->setCurrentItem((int)problem->getSubTaskType());
  updateComboBoxes(problem->getSubTaskType());

  CSensItem tmp = problem->getTargetFunctions();

  //target function
  if (tmp.isSingleObject())
    {
      FunctionChooser->setCurrentObjectList(CObjectLists::SINGLE_OBJECT);
      mpSingleFunction = CCopasiContainer::ObjectFromName(tmp.getSingleObjectCN());
      if (mpSingleFunction)
        FunctionLineEdit->setText(FROM_UTF8(mpSingleFunction->getObjectDisplayName()));
    }
  else
    FunctionChooser->setCurrentObjectList(tmp.getListType());

  //variables 1
  if (problem->getNumberOfVariables() > 0)
    {
      tmp = problem->getVariables(0);
      if (tmp.isSingleObject())
        {
          VariableChooser->setCurrentObjectList(CObjectLists::SINGLE_OBJECT);
          mpSingleVariable = CCopasiContainer::ObjectFromName(tmp.getSingleObjectCN());
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
          mpSingleVariable2 = CCopasiContainer::ObjectFromName(tmp.getSingleObjectCN());
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
  updateRunButton();
  return true;
}

//**************************************************************************

void SensitivitiesWidget::updateLineeditEnable(const SensWidgetComboBox* box, QWidget* w1, QWidget* w2)
{
  if (!box) return;
  bool enable = false;

  if (box->getCurrentObjectList() == CObjectLists::SINGLE_OBJECT)
    enable = true;

  if (w1) w1->setEnabled(enable);
  if (w2) w2->setEnabled(enable);
}

void SensitivitiesWidget::updateAllLineditEnable()
{
  updateLineeditEnable(FunctionChooser, FunctionLineEdit, SingleFunctionChooser);
  updateLineeditEnable(VariableChooser, VariableLineEdit, SingleVariableChooser);
  updateLineeditEnable(Variable2Chooser, Variable2LineEdit, SingleVariable2Chooser);
}

bool SensitivitiesWidget::checkSingleObject(const SensWidgetComboBox* box, const CCopasiObject * object)
{
  if (box->getCurrentObjectList() != CObjectLists::SINGLE_OBJECT)
    return true;

  if (object) return true;

  return false;
}

void SensitivitiesWidget::updateRunButton()
{
  bool enable = true;

  if (VariableChooser->currentText() == FROM_UTF8(CObjectLists::ListTypeName[CObjectLists::EMPTY_LIST]))
    enable = false;

  //single object case
  if (!checkSingleObject(FunctionChooser, mpSingleFunction))
    enable = false;
  if (!checkSingleObject(VariableChooser, mpSingleVariable))
    enable = false;
  if (!checkSingleObject(Variable2Chooser, mpSingleVariable2))
    enable = false;

  mpBtnWidget->mpBtnRun->setEnabled(enable);
}

//************************************************************************

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

  SubTaskChooser->insertStringList(StringList);
  SubTaskChooser->setCurrentItem(0);
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
SensitivitiesWidget::on_SubTaskChooser_activated(int)
{
  CSensProblem::SubTaskType subTaskType = (CSensProblem::SubTaskType)SubTaskChooser->currentItem();
  updateComboBoxes(subTaskType);

  updateAllLineditEnable();
  updateRunButton();
}

void
SensitivitiesWidget::on_FunctionChooser_activated(int)
{
  updateAllLineditEnable();
  updateRunButton();
}

void
SensitivitiesWidget::on_VariableChooser_activated(int)
{
  updateAllLineditEnable();
  updateRunButton();
}

void
SensitivitiesWidget::on_Variable2Chooser_activated(int)
{
  updateAllLineditEnable();
  updateRunButton();
}

void
SensitivitiesWidget::on_SingleFunctionChooser_clicked()
{
  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, CCopasiSimpleSelectionTree::TRANSIENT_VALUE);

  if (pObject)
    {
      FunctionLineEdit->setText(FROM_UTF8(pObject->getObjectDisplayName()));
      mpSingleFunction = pObject;
      FunctionChooser->setCurrentObjectList(CObjectLists::SINGLE_OBJECT);
    }

  updateRunButton();
}

void
SensitivitiesWidget::on_SingleVariableChooser_clicked()
{
  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, CCopasiSimpleSelectionTree::INITIAL_VALUE);

  if (pObject)
    {
      VariableLineEdit->setText(FROM_UTF8(pObject->getObjectDisplayName()));
      mpSingleVariable = pObject;
      VariableChooser->setCurrentObjectList(CObjectLists::SINGLE_OBJECT);
    }

  updateRunButton();
}

void
SensitivitiesWidget::on_SingleVariable2Chooser_clicked()
{
  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, CCopasiSimpleSelectionTree::INITIAL_VALUE);

  if (pObject)
    {
      Variable2LineEdit->setText(FROM_UTF8(pObject->getObjectDisplayName()));
      mpSingleVariable2 = pObject;
      Variable2Chooser->setCurrentObjectList(CObjectLists::SINGLE_OBJECT);
    }

  updateRunButton();
}
