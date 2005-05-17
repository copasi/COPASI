/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ParamFittingWidget.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/17 17:50:40 $
   End CVS Header */

/********************************************************
Author: chlee
Version : 1.xx  <first>
Description: 
Date: 09/19
Comment : ParameterFittingWidget for UI of the param fitting function
 *********************************************************/

#include "ParamFittingWidget.h"
#include "copasi.h"
#include "trajectory/CTrajectoryTask.h"
#include "steadystate/CSteadyStateTask.h"
#include "TrajectoryWidget.h"
#include "SteadyStateWidget.h" 
//#include "OptimizationItemWidget.h"
#include "ParamFittingItemWidget.h"
#include "ScanScrollView.h"

#include <qbuttongroup.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlistbox.h>
#include <qpushbutton.h>
#include <qradiobutton.h>

/*#include <qvariant.h>
#include <qtextedit.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qtextbrowser.h>
#include <qmessagebox.h>
 
#include "ScanWidget.h"
#include "ScanItemWidget.h"
#include "OptimizationItemWidget.h"
#include "OptimizationWidget.h"
#include "copasi.h"
#include "listviews.h"
#include "ObjectBrowser.h"
#include "utilities/CGlobals.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "function/CKinFunction.h"
#include "optimization/COptFunction.h"
#include "trajectory/CTrajectoryTask.h"
#include "steadystate/CSteadyStateTask.h"
#include "TrajectoryWidget.h"
#include "SteadyStateWidget.h"
#include "utilities/CCopasiException.h"
#include "qtUtilities.h"
 
#include "report/CKeyFactory.h"*/
#include "./icons/scanwidgetbuttonicon.xpm"

/*
 *  Constructs a ParamFittingWidget as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ParamFittingWidget::ParamFittingWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiParametersWidget(parent, name, fl)
    /*ParamFittingWidget::ParamFittingWidget(QWidget* parent, const char* name, WFlags fl)
        : CopasiParametersWidget(parent, name, fl),
        bUpdated(false)*/
{
  if (!name)
    setName("ParamFittingWidget");
  setCaption(trUtf8("ParamFittingWidget"));

  globalSelectedList.clear();
  localSelectedList.clear();
  /*****nSelectedObjects = 0;
  nTitleHeight = 16;
  activeObject = -1;
  selectedList.clear();***/

  // this is for button images? from Liang's code + - up and down button icons
  QPixmap image0((const char**) image0_data);
  QPixmap image1((const char**) image1_data);
  QPixmap image2((const char**) image2_data);
  QPixmap image3((const char**) image3_data);

  ParamFittingWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ParamFittingWidgetLayout");

  // 1st line of param optimization gui
  dataFileLabel = new QLabel(this, "dataFileLabel");
  dataFileLabel->setText(trUtf8("Data File"));
  ParamFittingWidgetLayout->addWidget(dataFileLabel, 0, 0);

  dataFileText = new QLineEdit(this, "dataFileText");
  dataFileText->setFrameShape(QLineEdit::LineEditPanel);
  dataFileText->setFrameShadow(QLineEdit::Sunken);
  ParamFittingWidgetLayout->addMultiCellWidget(dataFileText, 0, 0, 1, 3);

  dataButtonsLayout = new QHBoxLayout(this, 0, 6, "dataButtonsLayout");
  browseButton = new QPushButton("Browse", this, "browseButton");
  dataButtonsLayout->addWidget(browseButton);
  dataFormatButton = new QPushButton(this, "dataFormatButton");
  dataFormatButton->setText(trUtf8("Data File Format"));
  dataButtonsLayout->addWidget(dataFormatButton);
  ParamFittingWidgetLayout->addMultiCellLayout(dataButtonsLayout, 0, 0, 4, 4);
  //ParamFittingWidgetLayout->addWidget(dataFormatButton, 0,4);

  // division line between data and method
  divisionLine = new QFrame(this, "divisionLine");
  divisionLine->setFrameShape(QFrame::HLine);
  divisionLine->setFrameShadow(QFrame::Sunken);
  divisionLine->setFrameShape(QFrame::HLine);
  ParamFittingWidgetLayout->addMultiCellWidget(divisionLine, 1, 1, 0, 4);

  optimizationMethodLabel = new QLabel(this, "optimizationMethodLabel");
  optimizationMethodLabel->setText(trUtf8("Optimization Method"));
  ParamFittingWidgetLayout->addWidget(optimizationMethodLabel, 2, 0);

  // 2nd gui line
  // ***** Methods needs to be defined and modified accordingly
  methodCombo = new QComboBox(FALSE, this, "methodCombo");
  methodCombo->insertItem("Steepest descent");
  methodCombo->insertItem("Genetic algorithms(SA--)");
  methodCombo->insertItem("Random Search");
  ParamFittingWidgetLayout->addMultiCellWidget(methodCombo, 2, 2, 1, 3);

  methodInfoButton = new QPushButton(this, "methodInfoButton");
  methodInfoButton->setText(trUtf8("Method Info"));
  ParamFittingWidgetLayout->addWidget(methodInfoButton, 2, 4);
  /*//this button is for changing parameters change according to combobox method selection
  adjustParamButton = new QPushButton(this, "adjustParamButton");
  adjustParamButton->setText(trUtf8("Adjust Parameters"));
  ParamFittingWidgetLayout->addWidget(adjustParamButton,1,4);*/

  // The following code is for the next two gui lines for showing method parameters
  // labels line/ this would be dynamically generated and displayed based on selected method
  methodParamLabelsLayout = new QHBoxLayout(this, 0, 10, "methodParamLabelsLayout");
  sampleLabel1 = new QLabel("Param1", this, "sampleLabel1");
  sampleLabel2 = new QLabel("Param2", this, "sampleLabel2");
  sampleLabel3 = new QLabel("Param3", this, "sampleLabel3");
  sampleLabel4 = new QLabel("Param4", this, "sampleLabel4");
  methodParamLabelsLayout -> addWidget(sampleLabel1);
  methodParamLabelsLayout -> addWidget(sampleLabel2);
  methodParamLabelsLayout -> addWidget(sampleLabel3);
  methodParamLabelsLayout -> addWidget(sampleLabel4);
  ParamFittingWidgetLayout->addMultiCellLayout(methodParamLabelsLayout, 3, 3, 0, 3);
  // text field label entry line
  methodParamTextboxLayout = new QHBoxLayout(this, 0, 10, "methodParamLabelsLayout");
  methodParam1Text = new QLineEdit(this, "methodParam1Text");
  methodParam2Text = new QLineEdit(this, "methodParam2Text");
  methodParam3Text = new QLineEdit(this, "methodParam3Text");
  methodParam4Text = new QLineEdit(this, "methodParam4Text");
  methodParamTextboxLayout -> addWidget(methodParam1Text);
  methodParamTextboxLayout -> addWidget(methodParam2Text);
  methodParamTextboxLayout -> addWidget(methodParam3Text);
  methodParamTextboxLayout -> addWidget(methodParam4Text);
  ParamFittingWidgetLayout->addMultiCellLayout(methodParamTextboxLayout, 4, 4, 0, 3);

  //this button is for changing parameters change according to combobox method selection
  adjustParamButton = new QPushButton(this, "adjustParamButton");
  adjustParamButton->setText(trUtf8("Adjust Parameters"));
  ParamFittingWidgetLayout->addWidget(adjustParamButton, 4, 4);

  // this is for the division line
  divisionLine1 = new QFrame(this, "divisionLine1");
  divisionLine1->setFrameShape(QFrame::HLine);
  divisionLine1->setFrameShadow(QFrame::Sunken);
  divisionLine1->setFrameShape(QFrame::HLine);

  ParamFittingWidgetLayout->addMultiCellWidget(divisionLine1, 5, 5, 0, 4);

  //3rd gui line: type of experiment to run: steady state or time course with parameter
  //adjustment edit button options
  steadyStateOrTimeLayout = new QHBoxLayout(this, 0, 6, "steadyStateOrTimeLayout");
  //qbuttongroup = new QButtonGroup(this, "buttonGroup");
  //radioButtonLayout = new QVBoxLayout(qbuttongroup, 0, 6, "radioButtonLayout");
  //steadyStateRadio = new QRadioButton("Steady State", qbuttongroup, "steadyStateRadio");
  //steadyStateRadio->setChecked(true);
  //timeCourseRadio = new QRadioButton("Time Course", qbuttongroup, "timeCourseRadio");
  //radioButtonLayout->addWidget(steadyStateRadio);
  //radioButtonLayout->addWidget(timeCourseRadio);
  //ParamFittingWidgetLayout->addMultiCellWidget(qbuttongroup, 3, 5, 0, 2);
  steadyStateCheck = new QCheckBox("Steady State", this, "steadystateCheck");
  steadyStateOrTimeLayout->addWidget(steadyStateCheck);
  steadyStateEditButton = new QPushButton(this, "steadyStateEditButton");
  steadyStateEditButton->setText(trUtf8("Settings"));
  steadyStateOrTimeLayout->addWidget(steadyStateEditButton);
  QSpacerItem* spacer = new QSpacerItem(99, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  steadyStateOrTimeLayout->addItem(spacer);
  timeCheck = new QCheckBox("Time Course", this, "timeCheck");
  steadyStateOrTimeLayout->addWidget(timeCheck);
  timeEditButton = new QPushButton(this, "timeEditButton");
  timeEditButton->setText(trUtf8("Settings"));
  steadyStateOrTimeLayout->addWidget(timeEditButton);
  ParamFittingWidgetLayout->addMultiCellLayout(steadyStateOrTimeLayout, 6, 6, 0, 4);

  // this is for the division line
  divisionLine2 = new QFrame(this, "divisionLine1");
  divisionLine2->setFrameShape(QFrame::HLine);
  divisionLine2->setFrameShadow(QFrame::Sunken);
  divisionLine2->setFrameShape(QFrame::HLine);

  ParamFittingWidgetLayout->addMultiCellWidget(divisionLine2, 7, 7, 0, 4);

  // 4th & 5th gui line: interface for the selection of global items -- table
  globalCopasiItemsLabel = new QLabel("Global Parameters: ", this, "dataFileLabel");
  ParamFittingWidgetLayout->addMultiCellWidget(globalCopasiItemsLabel, 8, 8, 0, 4);
  globalCopasiItemsLayout = new QGridLayout(0, 1, 1, 0, 6, "globalCopasiItemsLayout");
  globalDownButton = new QPushButton(this, "globalDownButton");
  globalDownButton->setText(trUtf8(""));
  globalDownButton->setPixmap(image1);
  globalCopasiItemsLayout->addWidget(globalDownButton, 2, 1);
  globalDeleteButton = new QPushButton(this, "globalDeleteButton");
  globalDeleteButton->setText(trUtf8(""));
  globalDeleteButton->setPixmap(image0);
  globalCopasiItemsLayout->addWidget(globalDeleteButton, 1, 1);
  globalAddButton = new QPushButton(this, "globalAddButton");
  globalAddButton->setText(trUtf8(""));
  globalAddButton->setPixmap(image2);
  globalCopasiItemsLayout->addWidget(globalAddButton, 1, 0);
  //manually change to add icon for alignment need
  globalUpButton = new QPushButton(this, "globalUpButton");
  globalUpButton->setText(trUtf8(""));
  globalUpButton->setPixmap(image3);
  globalCopasiItemsLayout->addWidget(globalUpButton, 2, 0);
  globalItemnamesTable = new QListBox(this, "globalItemnamesTable");
  globalCopasiItemsLayout->addMultiCellWidget(globalItemnamesTable, 3, 3, 0, 1);
  globalItemsLabel = new QLabel(this, "globalItemsLabel");
  globalItemsLabel->setText("Copasi Items");
  globalCopasiItemsLayout->addMultiCellWidget(globalItemsLabel, 0, 0, 0, 1);
  ParamFittingWidgetLayout->addMultiCellLayout(globalCopasiItemsLayout, 9, 9, 0, 0);

  globalItemsTable = new ScanScrollView(this, 0, 0);
  ParamFittingItemWidget* parameterTable = new ParamFittingItemWidget(this, "parameterTable");
  globalItemsTable->setMinimumWidth(parameterTable->minimumSizeHint().width());
  pdelete(parameterTable);
  globalItemsTable->setVScrollBarMode(QScrollView::Auto);
  globalItemsTable->setHScrollBarMode(QScrollView::AlwaysOff); //Disable Horizonal Scroll
  globalItemsTable->setSelectedList(&globalSelectedList);
  // different from Liang's two part add 0,1 and 0,2
  ParamFittingWidgetLayout->addMultiCellWidget(globalItemsTable, 9, 9, 1, 4);

  // this is for the division line
  divisionLine3 = new QFrame(this, "divisionLine1");
  divisionLine3->setFrameShape(QFrame::HLine);
  divisionLine3->setFrameShadow(QFrame::Sunken);
  divisionLine3->setFrameShape(QFrame::HLine);
  ParamFittingWidgetLayout->addMultiCellWidget(divisionLine3, 11, 11, 0, 4);

  // 6th & 7th gui line: interface for the selection of local items -- table
  localCopasiItemsLayout = new QGridLayout(0, 1, 1, 0, 6, "localCopasiItemsLayout");
  localCopasiItemsLabel = new QLabel("Per Experiment Parameters: ", this, "dataFileLabel");
  ParamFittingWidgetLayout->addMultiCellWidget(localCopasiItemsLabel, 12, 12, 0, 4);
  localDownButton = new QPushButton(this, "localDownButton");
  localDownButton->setText(trUtf8(""));
  localDownButton->setPixmap(image1);
  localCopasiItemsLayout->addWidget(localDownButton, 2, 1);
  localDeleteButton = new QPushButton(this, "localDeleteButton");
  localDeleteButton->setText(trUtf8(""));
  localDeleteButton->setPixmap(image0);
  localCopasiItemsLayout->addWidget(localDeleteButton, 1, 1);
  localAddButton = new QPushButton(this, "localAddButton");
  localAddButton->setText(trUtf8(""));
  localAddButton->setPixmap(image2);
  localCopasiItemsLayout->addWidget(localAddButton, 1, 0);
  //manually change to add icon for alignment need
  localUpButton = new QPushButton(this, "localUpButton");
  localUpButton->setText(trUtf8(""));
  localUpButton->setPixmap(image3);
  localCopasiItemsLayout->addWidget(localUpButton, 2, 0);
  localItemnamesTable = new QListBox(this, "localItemnamesTable");
  localCopasiItemsLayout->addMultiCellWidget(localItemnamesTable, 3, 3, 0, 1);
  localItemsLabel = new QLabel(this, "llobalItemsLabel");
  localItemsLabel->setText("Copasi Items");
  localCopasiItemsLayout->addMultiCellWidget(localItemsLabel, 0, 0, 0, 1);
  ParamFittingWidgetLayout->addMultiCellLayout(localCopasiItemsLayout, 13, 13, 0, 0);

  localItemsTable = new ScanScrollView(this, 0, 0);
  ParamFittingItemWidget* parameterTable2 = new ParamFittingItemWidget(this, "parameterTable2");
  localItemsTable->setMinimumWidth(parameterTable2->minimumSizeHint().width());
  pdelete(parameterTable2);
  localItemsTable->setVScrollBarMode(QScrollView::Auto);
  localItemsTable->setHScrollBarMode(QScrollView::AlwaysOff); //Disable Horizonal Scroll
  localItemsTable->setSelectedList(&localSelectedList);
  // Different from Liang's two part addition...
  ParamFittingWidgetLayout->addMultiCellWidget(localItemsTable, 13, 13, 1, 4);

  // this is for the division line
  divisionLine4 = new QFrame(this, "divisionLine1");
  divisionLine4->setFrameShape(QFrame::HLine);
  divisionLine4->setFrameShadow(QFrame::Sunken);
  divisionLine4->setFrameShape(QFrame::HLine);
  ParamFittingWidgetLayout->addMultiCellWidget(divisionLine4, 15, 15, 0, 4);

  // 8th main gui line: this line shows the result after user Runs Parameter Fitting with selected parameters
  //resultLayout = new QGridLayout(this,2,1,0,-1,"resultLayout");
  resultLabel = new QLabel(this, "resultLabel");
  resultLabel->setText(trUtf8("RESULTS"));
  //resultLayout->addWidget(resultLabel,0,0);
  ParamFittingWidgetLayout->addWidget(resultLabel, 16, 0);
  resultFieldLayout = new QHBoxLayout(0, 1, 3, "resultFieldLayout");
  sumOfSqLabel = new QLabel(this, "sumOfSqLabel");
  sumOfSqLabel->setText(trUtf8("Sum of Squares "));
  resultFieldLayout->addWidget(sumOfSqLabel);
  sumOfSqText = new QLineEdit(this, "sumOfSqText");
  resultFieldLayout->addWidget(sumOfSqText);
  QSpacerItem* spacer2 = new QSpacerItem(99, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  resultFieldLayout->addItem(spacer2);
  iterationsLabel = new QLabel(this, "iterationsLabel");
  iterationsLabel->setText(trUtf8("Iterations "));
  resultFieldLayout->addWidget(iterationsLabel);
  iterationsText = new QLineEdit(this, "iterationsText");
  resultFieldLayout->addWidget(iterationsText);
  //resultLayout->addMultiCellLayout(resultFieldLayout,1,1,0,1);
  //ParamFittingWidgetLayout->addMultiCellLayout(resultLayout, 7,7,0,4);
  ParamFittingWidgetLayout->addMultiCellLayout(resultFieldLayout, 17, 17, 0, 4);

  // this is for the division line
  divisionLine5 = new QFrame(this, "divisionLine1");
  divisionLine5->setFrameShape(QFrame::HLine);
  divisionLine5->setFrameShadow(QFrame::Sunken);
  divisionLine5->setFrameShape(QFrame::HLine);
  ParamFittingWidgetLayout->addMultiCellWidget(divisionLine5, 18, 18, 0, 4);

  // last line: buttons line
  buttonLayout = new QHBoxLayout(0, 0, 6, "buttonLayout");
  runButton = new QPushButton("Run", this, "runButton");
  buttonLayout->addWidget(runButton);
  cancelButton = new QPushButton("Cancel", this, "cancelButton");
  buttonLayout->addWidget(cancelButton);
  ParamFittingWidgetLayout->addMultiCellLayout(buttonLayout, 19, 19, 0, 4);

  /****
  bodyField = new QFrame(this, "bodyField");
  bodyField->setFrameShape(QFrame::HLine);
  bodyField->setFrameShadow(QFrame::Sunken);
  bodyField->setFrameShape(QFrame::HLine);

  ExpressionWidgetLayout->addMultiCellWidget(bodyField, 7, 7, 0, 2);

  layout14 = new QHBoxLayout(0, 0, 6, "layout14");

  confirmButton = new QPushButton(this, "confirmButton");
  layout14->addWidget(confirmButton);

  cancelButton = new QPushButton(this, "cancelButton");
  layout14->addWidget(cancelButton);

  ExpressionWidgetLayout->addMultiCellLayout(layout14, 8, 8, 0, 2);

  itemsTable = new ScanScrollView(this, 0, 0);
  OptimizationItemWidget* parameterTable = new OptimizationItemWidget(this, "parameterTable");
  itemsTable->setMinimumWidth(parameterTable->minimumSizeHint().width());
  pdelete(parameterTable);
  itemsTable->setVScrollBarMode(QScrollView::Auto);
  itemsTable->setHScrollBarMode(QScrollView::AlwaysOff); //Disable Horizonal Scroll
  itemsTable->setSelectedList(&selectedList);

  ExpressionWidgetLayout->addWidget(itemsTable, 6, 2);

  layout8 = new QGridLayout(0, 1, 1, 0, 6, "layout8");

  downButton = new QPushButton(this, "downButton");
  downButton->setText(trUtf8(""));
  downButton->setPixmap(image1);
  layout8->addWidget(downButton, 2, 1);

  deleteButton = new QPushButton(this, "deleteButton");
  deleteButton->setText(trUtf8(""));
  deleteButton->setPixmap(image0);
  layout8->addWidget(deleteButton, 1, 1);

  addButton = new QPushButton(this, "addButton");
  addButton->setText(trUtf8(""));
  addButton->setPixmap(image2);
  layout8->addWidget(addButton, 1, 0);

  //manually change to add icon for alignment need
  upButton = new QPushButton(this, "upButton");
  upButton->setText(trUtf8(""));
  upButton->setPixmap(image3);
  layout8->addWidget(upButton, 2, 0);

  itemnamesTable = new QListBox(this, "itemnamesTable");
  layout8->addMultiCellWidget(itemnamesTable, 3, 3, 0, 1);

  itemsLabel = new QLabel(this, "itemsLabel");

  layout8->addMultiCellWidget(itemsLabel, 0, 0, 0, 1);

  ExpressionWidgetLayout->addMultiCellLayout(layout8, 6, 6, 0, 1);

  bodyField_2 = new QFrame(this, "bodyField_2");
  bodyField_2->setFrameShape(QFrame::HLine);
  bodyField_2->setFrameShadow(QFrame::Sunken);
  bodyField_2->setFrameShape(QFrame::HLine);

  ExpressionWidgetLayout->addMultiCellWidget(bodyField_2, 5, 5, 0, 2);

  layout7 = new QHBoxLayout(0, 0, 6, "layout7");

  steadystateCheck = new QCheckBox(this, "steadystateCheck");
  layout7->addWidget(steadystateCheck);

  steadystateEditButton = new QPushButton(this, "steadystateEditButton");
  layout7->addWidget(steadystateEditButton);
  QSpacerItem* spacer = new QSpacerItem(101, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout7->addItem(spacer);

  timeCheck = new QCheckBox(this, "timeCheck");
  layout7->addWidget(timeCheck);

  timeEditButton = new QPushButton(this, "timeEditButton");
  layout7->addWidget(timeEditButton);

  ExpressionWidgetLayout->addMultiCellLayout(layout7, 4, 4, 0, 2);

  bodyField_2_2 = new QFrame(this, "bodyField_2_2");
  bodyField_2_2->setFrameShape(QFrame::HLine);
  bodyField_2_2->setFrameShadow(QFrame::Sunken);
  bodyField_2_2->setFrameShape(QFrame::HLine);

  ExpressionWidgetLayout->addMultiCellWidget(bodyField_2_2, 3, 3, 0, 2);

  expressionName = new QLineEdit(this, "expressionName");
  expressionName->setFrameShape(QLineEdit::LineEditPanel);
  expressionName->setFrameShadow(QLineEdit::Sunken);

  ExpressionWidgetLayout->addMultiCellWidget(expressionName, 0, 0, 1, 2);

  methodCombo = new QComboBox(FALSE, this, "methodCombo");
  methodCombo->insertItem("Genetic algorithms(SA--)");
  methodCombo->insertItem("Random Search");

  ExpressionWidgetLayout->addMultiCellWidget(methodCombo, 1, 1, 1, 2);

  optimizationLabel = new QLabel(this, "optimizationLabel");

  ExpressionWidgetLayout->addWidget(optimizationLabel, 1, 0);

  expressionEditlabel = new QLabel(this, "expressionEditlabel");

  ExpressionWidgetLayout->addWidget(expressionEditlabel, 2, 0);

  expressionText = new QLineEdit(this, "expressionText");
  expressionText->setFrameShape(QLineEdit::LineEditPanel);
  expressionText->setFrameShadow(QLineEdit::Sunken);

  ExpressionWidgetLayout->addMultiCellWidget(expressionText, 2, 2, 1, 2);

  expressionNameLabel = new QLabel(this, "expressionNameLabel");

  ExpressionWidgetLayout->addWidget(expressionNameLabel, 0, 0);

  languageChange();
  clearWState(WState_Polished);

  // tab order
  setTabOrder(expressionName, methodCombo);
  setTabOrder(methodCombo, expressionText);
  setTabOrder(expressionText, steadystateCheck);
  setTabOrder(steadystateCheck, steadystateEditButton);
  setTabOrder(steadystateEditButton, timeCheck);
  setTabOrder(timeCheck, timeEditButton);
  setTabOrder(timeEditButton, addButton);
  setTabOrder(addButton, deleteButton);
  setTabOrder(deleteButton, upButton);
  setTabOrder(upButton, downButton);
  setTabOrder(downButton, itemnamesTable);
  setTabOrder(itemnamesTable, itemsTable);
  setTabOrder(itemsTable, confirmButton);
  setTabOrder(confirmButton, cancelButton);

  connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
  connect(upButton, SIGNAL(clicked()), this, SLOT(upButtonClicked()));
  connect(downButton, SIGNAL(clicked()), this, SLOT(downButtonClicked()));

  connect(confirmButton, SIGNAL(clicked()), this, SLOT(slotBtnConfirmClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));

  //  connect(this, SIGNAL(hide_me()), (ListViews*)parent, SLOT(slotHideWidget()));
  //  connect(this, SIGNAL(show_me()), (ListViews*)parent, SLOT(slotShowWidget()));

  connect(itemnamesTable, SIGNAL(clicked(QListBoxItem*)), this, SLOT(ListBoxClicked(QListBoxItem*)));
  connect(itemnamesTable, SIGNAL(doubleClicked(QListBoxItem*)), this, SLOT(ListBoxDoubleClicked(QListBoxItem*)));

  //  connect(this, SIGNAL(hide_me()), (ListViews*)parent, SLOT(slotHideWidget()));
  //  connect(this, SIGNAL(show_me()), (ListViews*)parent, SLOT(slotShowWidget()));

  connect(steadystateCheck, SIGNAL(clicked()), this, SLOT(steadystateEnable()));
  connect(timeCheck, SIGNAL(clicked()), this, SLOT(timeEnable()));

  connect(steadystateEditButton, SIGNAL(clicked()), this, SLOT(steadystateEditing()));
  connect(timeEditButton, SIGNAL(clicked()), this, SLOT(timeEditing()));

  nTitleHeight = fontMetrics().height() + 6;
  expressionName->setText("Optimization Task");
  expressionName->setEnabled(false);

  expressionText->setText("-inf|Function  <|<=|== Optimization Item <|<=|== +inf|Function");
  expressionText->setEnabled(false);

  itemnamesTable->insertItem(trUtf8("click here to add new item"));

  steadystateEditButton->setEnabled(false);
  timeEditButton->setEnabled(false);

  SteadyStateKey = (new CSteadyStateTask())->getKey();
  TrajectoryKey = (new CTrajectoryTask())->getKey();
  pSteadyStateWidget = new SteadyStateWidget(NULL);
  pTrajectoryWidget = new TrajectoryWidget(NULL);
  pSteadyStateWidget->hide();
  pTrajectoryWidget->hide();*/
}

/*
 *  Destroys the object and frees any allocated resources
 */
ParamFittingWidget::~ParamFittingWidget()
{
  // no need to delete child widgets, Qt does it all for us
  /*CSteadyStateTask * sst =
    dynamic_cast< CSteadyStateTask * >(GlobalKeys.get(SteadyStateKey));
  pdelete(sst);

  CTrajectoryTask* tt =
    dynamic_cast< CTrajectoryTask * >(GlobalKeys.get(TrajectoryKey));
  pdelete(tt);*/
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */ 
/*void ParamFittingWidget::languageChange()
{
  setCaption(tr("Expression"));
  confirmButton->setText(tr("confirm"));
  cancelButton->setText(tr("cancel"));
  addButton->setText(QString::null);
  deleteButton->setText(QString::null);
  downButton->setText(QString::null);
  itemsLabel->setText(tr("Copasi Items"));
  upButton->setText(QString::null);
  steadystateCheck->setText(tr("Steady State"));
  steadystateEditButton->setText(tr("edit"));
  timeCheck->setText(tr("Time Course"));
  timeEditButton->setText(tr("edit"));
  optimizationLabel->setText(tr("Optimization Method"));
  expressionEditlabel->setText(tr("Expression"));
  expressionNameLabel->setText(tr("Name"));
}*/

bool ParamFittingWidget::update(ListViews::ObjectType objectType,
                                ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::MODEL:
      break;

    default:
      break;
    }
  return true;
}

bool ParamFittingWidget::leave()
{
  /******slotBtnConfirmClicked();
  bUpdated = false;******/
  return true;
}

bool ParamFittingWidget::enter(const std::string & key)
{
  objKey = key;
  /****objKey = key;
  COptFunction* func = dynamic_cast< COptFunction * >(GlobalKeys.get(key)); ***/ 
  //TODO: check if it really is a compartment
  // pSteadyStateWidget->enter(SteadyStateKey);
  // pTrajectoryWidget->enter(TrajectoryKey);

  /***********if (func)
    return loadFromExpression(func);
  else******/
  return false;
}

/********bool ParamFittingWidget::loadFromExpression(COptFunction*)
{
  bUpdated = false;
  COptFunction* func = dynamic_cast< COptFunction * >(GlobalKeys.get(objKey));
  expressionName->setText(FROM_UTF8(func->getObjectUniqueName()));
  //  expressionText->setText(func-> serialize a function to a std::stream
  return true;
}
 
void ParamFittingWidget::addButtonClicked()
{
  ObjectBrowser* pSelectedObjects = new ObjectBrowser();
  std::vector<CCopasiObject*>* pSelectedVector = new std::vector<CCopasiObject*>();
  pSelectedObjects->setOutputVector(pSelectedVector);
 
  if (pSelectedObjects->exec () == QDialog::Rejected)
    {
      pdelete(pSelectedVector);
      return;
    }
 
  if (pSelectedVector->size() == 0)
    {
      pdelete(pSelectedVector);
      return;
    }
 
  unsigned int i = 0;
  for (; i < pSelectedVector->size(); i++)
    if ((*pSelectedVector)[i])
      break;
 
  if (i >= pSelectedVector->size()) //no result returned
    {
      pdelete(pSelectedVector);
      return;
    }
 
  if (addNewOptItem((*pSelectedVector)[i]))
    itemnamesTable->insertItem (FROM_UTF8((*pSelectedVector)[i]->getObjectUniqueName()), nSelectedObjects - 1);
 
  pdelete(pSelectedVector);
}
 
void ParamFittingWidget::deleteButtonClicked()
{
  if (activeObject < 0 || activeObject >= selectedList.size() / 2)  // not a valid entry
    return;
 
  emit hide_me();
 
  COptFunction* optFunction =
    dynamic_cast< COptFunction *>(GlobalKeys.get(objKey));
  CCopasiObject* pOptObject =
    ((OptimizationItemWidget*)(selectedList[activeObject * 2 + 1]))->getCopasiObject();
  if (optFunction->mParaList.size() > 0)  // for reloading
    optFunction->removeItem(pOptObject->getCN());
 
  itemsTable->removeChild(selectedList[2*activeObject]);
  itemsTable->removeChild(selectedList[2*activeObject + 1]);
 
  itemnamesTable->removeItem (activeObject);
 
  unsigned int i = activeObject + 1;
  int offsetY = ((OptimizationItemWidget*)selectedList[1])->minimumSizeHint().height() + nTitleHeight;
 
  for (; i < selectedList.size() / 2; i++)
    {
      itemsTable->moveChild(selectedList[2*i], 0, (i - 1)*offsetY);
      itemsTable->moveChild(selectedList[2*i + 1], 0, (i - 1)*offsetY + nTitleHeight);
    }
 
  std::vector<QWidget*>::iterator it = selectedList.begin();
  std::vector<QWidget*>::iterator BeginDel;
  std::vector<QWidget*>::iterator ToDel;
  while (it < selectedList.end())
    {
      if (it - selectedList.begin() == 2*activeObject)
        {
          BeginDel = it;
          pdelete (*it);
          ToDel = ++it;
          pdelete (*ToDel);
          ++ToDel;
          selectedList.erase(BeginDel, ToDel);
          break;
        }
      it++;
      it++;
    }
 
  activeObject--;
  if ((activeObject >= 0) && (optFunction->mParaList.size() > 0))
    {
      pOptObject = ((OptimizationItemWidget*)(selectedList[activeObject * 2 + 1]))->getCopasiObject();
      ScanLineEdit* activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
      activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
      activeTitle->setText(FROM_UTF8(pOptObject->getCN()));
    }
 
  nSelectedObjects--;
  itemsTable->resizeContents(0, offsetY*selectedList.size() / 2);
 
  emit show_me();
 
  //update the active
  if (activeObject >= 0)
    ListBoxClicked(itemnamesTable->item(activeObject));
 
  // to verify the size of the mparameterlist in ScanProblem
  // optFunction->getProblem()->paraCount();
}
 
void ParamFittingWidget::upButtonClicked()
{
  if (activeObject <= 0 || activeObject >= selectedList.size() / 2)  // not a valid entry
    return;
 
  emit hide_me();
 
  std::string mDownMin = ((OptimizationItemWidget*)selectedList[2 * activeObject + 1])->getItemLowerLimit();
  std::string mUpMin = ((OptimizationItemWidget*)selectedList[2 * activeObject - 1])->getItemLowerLimit();
  std::string mDownMax = ((OptimizationItemWidget*)selectedList[2 * activeObject + 1])->getItemUpperLimit();
  std::string mUpMax = ((OptimizationItemWidget*)selectedList[2 * activeObject - 1])->getItemUpperLimit();
 
  std::string mDownLowerOp = ((OptimizationItemWidget*)selectedList[2 * activeObject + 1]) ->getItemLowerOper();
  std::string mUpLowerOp = ((OptimizationItemWidget*)selectedList[2 * activeObject - 1]) ->getItemLowerOper();
  std::string mDownUpperOp = ((OptimizationItemWidget*)selectedList[2 * activeObject + 1]) ->getItemUpperOper();
  std::string mUpUpperOp = ((OptimizationItemWidget*)selectedList[2 * activeObject - 1]) ->getItemUpperOper();
 
  CCopasiObject* pObjectDown = ((OptimizationItemWidget*)selectedList[2 * activeObject + 1])->getCopasiObject();
  CCopasiObject* pObjectUp = ((OptimizationItemWidget*)selectedList[2 * activeObject - 1])->getCopasiObject();
 
  COptFunction* optFunction =
    dynamic_cast< COptFunction * >(GlobalKeys.get(objKey));
 
  ((OptimizationItemWidget*)selectedList[2*activeObject + 1])->setCopasiObjectPtr(pObjectUp);
  ((OptimizationItemWidget*)selectedList[2*activeObject - 1])->setCopasiObjectPtr(pObjectDown);
 
  ((OptimizationItemWidget*)selectedList[2*activeObject + 1])->setItemUpperOper(mUpUpperOp);
  ((OptimizationItemWidget*)selectedList[2*activeObject - 1])->setItemUpperOper(mDownUpperOp);
  ((OptimizationItemWidget*)selectedList[2*activeObject + 1])->setItemLowerOper(mUpLowerOp);
  ((OptimizationItemWidget*)selectedList[2*activeObject - 1])->setItemLowerOper(mDownLowerOp);
 
  ((OptimizationItemWidget*)selectedList[2*activeObject + 1])->setItemUpperLimit(mUpMax);
  ((OptimizationItemWidget*)selectedList[2*activeObject - 1])->setItemUpperLimit(mDownMax);
  ((OptimizationItemWidget*)selectedList[2*activeObject + 1])->setItemLowerLimit(mUpMin);
  ((OptimizationItemWidget*)selectedList[2*activeObject - 1])->setItemLowerLimit(mDownMin);
 
  //back end change
  CCopasiObject* tmpObj = optFunction->mParaList [activeObject - 1];
  optFunction->mParaList [activeObject - 1] = optFunction->mParaList [activeObject];
  optFunction->mParaList [activeObject] = tmpObj;
 
  CKinFunction* tmpFunc = optFunction->mMinFunctionList [activeObject - 1];
  optFunction->mMinFunctionList [activeObject - 1] = optFunction->mMinFunctionList [activeObject];
  optFunction->mMinFunctionList [activeObject] = tmpFunc;
 
  tmpFunc = optFunction->mMaxFunctionList [activeObject - 1];
  optFunction->mMaxFunctionList [activeObject - 1] = optFunction->mMaxFunctionList [activeObject];
  optFunction->mMaxFunctionList [activeObject] = tmpFunc;
 
  std::string tmpStr = optFunction->mMinList [activeObject - 1];
  optFunction->mMinList [activeObject - 1] = optFunction->mMinList [activeObject];
  optFunction->mMinList [activeObject] = tmpStr;
 
  tmpStr = optFunction->mMaxList [activeObject - 1];
  optFunction->mMaxList [activeObject - 1] = optFunction->mMaxList [activeObject];
  optFunction->mMaxList [activeObject] = tmpStr;
 
  activeObject--;
 
  //deactivate
  //lower one
  ScanLineEdit* activeTitle = (ScanLineEdit*)(selectedList[(activeObject + 1) * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(160, 160, 255));
  activeTitle->setText(FROM_UTF8(pObjectUp->getCN()));
 
  //activate
  //upper one
  activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
  activeTitle->setText(FROM_UTF8(pObjectDown->getCN()));
 
  //Update ListBox
  QString tmp = itemnamesTable->text (activeObject);
  itemnamesTable->changeItem (NULL, itemnamesTable->text(activeObject + 1) , activeObject);
  itemnamesTable->changeItem (NULL, tmp, activeObject + 1);
 
  emit show_me();
  if (activeObject >= 0)
    ListBoxClicked(itemnamesTable->item(activeObject));
}
 
void ParamFittingWidget::downButtonClicked()
{
  if (activeObject < 0 || activeObject >= selectedList.size() / 2 - 1)  // not a valid entry
    return;
 
  emit hide_me();
 
  activeObject++;
 
  std::string mDownMin = ((OptimizationItemWidget*)selectedList[2 * activeObject + 1])->getItemLowerLimit();
  std::string mUpMin = ((OptimizationItemWidget*)selectedList[2 * activeObject - 1])->getItemLowerLimit();
  std::string mDownMax = ((OptimizationItemWidget*)selectedList[2 * activeObject + 1])->getItemUpperLimit();
  std::string mUpMax = ((OptimizationItemWidget*)selectedList[2 * activeObject - 1])->getItemUpperLimit();
 
  std::string mDownLowerOp = ((OptimizationItemWidget*)selectedList[2 * activeObject + 1]) ->getItemLowerOper();
  std::string mUpLowerOp = ((OptimizationItemWidget*)selectedList[2 * activeObject - 1]) ->getItemLowerOper();
  std::string mDownUpperOp = ((OptimizationItemWidget*)selectedList[2 * activeObject + 1]) ->getItemUpperOper();
  std::string mUpUpperOp = ((OptimizationItemWidget*)selectedList[2 * activeObject - 1]) ->getItemUpperOper();
 
  CCopasiObject* pObjectDown = ((OptimizationItemWidget*)selectedList[2 * activeObject + 1])->getCopasiObject();
  CCopasiObject* pObjectUp = ((OptimizationItemWidget*)selectedList[2 * activeObject - 1])->getCopasiObject();
 
  COptFunction* optFunction =
    dynamic_cast< COptFunction * >(GlobalKeys.get(objKey));
 
  ((OptimizationItemWidget*)selectedList[2*activeObject + 1])->setCopasiObjectPtr(pObjectUp);
  ((OptimizationItemWidget*)selectedList[2*activeObject - 1])->setCopasiObjectPtr(pObjectDown);
 
  ((OptimizationItemWidget*)selectedList[2*activeObject + 1])->setItemUpperOper(mUpUpperOp);
  ((OptimizationItemWidget*)selectedList[2*activeObject - 1])->setItemUpperOper(mDownUpperOp);
  ((OptimizationItemWidget*)selectedList[2*activeObject + 1])->setItemLowerOper(mUpLowerOp);
  ((OptimizationItemWidget*)selectedList[2*activeObject - 1])->setItemLowerOper(mDownLowerOp);
 
  ((OptimizationItemWidget*)selectedList[2*activeObject + 1])->setItemUpperLimit(mUpMax);
  ((OptimizationItemWidget*)selectedList[2*activeObject - 1])->setItemUpperLimit(mDownMax);
  ((OptimizationItemWidget*)selectedList[2*activeObject + 1])->setItemLowerLimit(mUpMin);
  ((OptimizationItemWidget*)selectedList[2*activeObject - 1])->setItemLowerLimit(mDownMin);
 
  //back end change
  CCopasiObject* tmpObj = optFunction->mParaList [activeObject - 1];
  optFunction->mParaList [activeObject - 1] = optFunction->mParaList [activeObject];
  optFunction->mParaList [activeObject] = tmpObj;
 
  CKinFunction* tmpFunc = optFunction->mMinFunctionList [activeObject - 1];
  optFunction->mMinFunctionList [activeObject - 1] = optFunction->mMinFunctionList [activeObject];
  optFunction->mMinFunctionList [activeObject] = tmpFunc;
 
  tmpFunc = optFunction->mMaxFunctionList [activeObject - 1];
  optFunction->mMaxFunctionList [activeObject - 1] = optFunction->mMaxFunctionList [activeObject];
  optFunction->mMaxFunctionList [activeObject] = tmpFunc;
 
  std::string tmpStr = optFunction->mMinList [activeObject - 1];
  optFunction->mMinList [activeObject - 1] = optFunction->mMinList [activeObject];
  optFunction->mMinList [activeObject] = tmpStr;
 
  tmpStr = optFunction->mMaxList [activeObject - 1];
  optFunction->mMaxList [activeObject - 1] = optFunction->mMaxList [activeObject];
  optFunction->mMaxList [activeObject] = tmpStr;
 
  //upper one
  ScanLineEdit* activeTitle = (ScanLineEdit*)(selectedList[(activeObject - 1) * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(160, 160, 255));
  activeTitle->setText(FROM_UTF8(pObjectDown->getCN()));
 
  //bottom one
  activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
  activeTitle->setText(FROM_UTF8(pObjectUp->getCN()));
 
  //Update ListBox
  QString tmp = itemnamesTable->text (activeObject);
  itemnamesTable->changeItem (NULL, itemnamesTable->text(activeObject - 1) , activeObject);
  itemnamesTable->changeItem (NULL, tmp, activeObject - 1);
 
  emit show_me();
  if (activeObject >= 0)
    ListBoxClicked(itemnamesTable->item(activeObject));
}
 
bool ParamFittingWidget::addNewOptItem(CCopasiObject* pObject)
{
  if (!pObject)
    return false;
 
  COptFunction* optFunction =
    dynamic_cast< COptFunction * >(GlobalKeys.get(objKey));
  // cannot be found in the list
  if (optFunction->Index(pObject->getCN()) != C_INVALID_INDEX)
    return false;
 
  int widgetOffset;
  int ScanItemWidgetWidth;
  emit hide_me();
 
  //by default isFirstWidget is set as false,
  OptimizationItemWidget* parameterTable = new OptimizationItemWidget(this, "parameterTable");
 
  ScanItemWidgetWidth = itemsTable->visibleWidth();
 
  widgetOffset = nTitleHeight + nSelectedObjects * (parameterTable->minimumSizeHint().height() + nTitleHeight);
 
  ScanLineEdit* newTitleBar = new ScanLineEdit(this, "newTitleBar");
  newTitleBar->setFixedSize(QSize(ScanItemWidgetWidth, nTitleHeight));
  newTitleBar->setPaletteForegroundColor(QColor(255, 255, 0));
  newTitleBar->setPaletteBackgroundColor(QColor(160, 160, 255));
 
  newTitleBar->setText(FROM_UTF8(pObject->getCN()));
  newTitleBar->setReadOnly(TRUE);
 
  itemsTable->addChild(newTitleBar, 0, widgetOffset - nTitleHeight);
  selectedList.push_back(newTitleBar);
 
  parameterTable->setFixedWidth(ScanItemWidgetWidth);
  parameterTable->setFixedHeight(parameterTable->minimumSizeHint().height());
 
  itemsTable->addChild(parameterTable, 0 , widgetOffset);
  itemsTable->setVScrollBarMode(QScrollView::Auto);
  itemsTable->resizeContents(ScanItemWidgetWidth, widgetOffset + parameterTable->minimumSizeHint().height());
  selectedList.push_back(parameterTable);
 
  nSelectedObjects++;
 
  //insert a new item
 
  unsigned int i;
  i = optFunction->addItem(pObject); // automatically creat the 5 fields; +/-inf, upper/lower bound, object pointer
 
  parameterTable->setCopasiObjectPtr(pObject);
  parameterTable->setItemLowerLimit(optFunction->mMinList[i]);
  parameterTable->setItemUpperLimit(optFunction->mMaxList[i]);
 
  emit show_me();
  return true;
}
 
void ParamFittingWidget::ListBoxDoubleClicked(QListBoxItem * item)
{
  if (itemnamesTable->index(item) >= nSelectedObjects)
    addButtonClicked();
}
 
void OptimizationWidget::ListBoxClicked(QListBoxItem * item)
{
  if (nSelectedObjects && itemnamesTable->index(item) >= 0) //select an object
    {
      double newActiveObject = itemnamesTable->index(item) + 0.5;
      QPoint point(0, newActiveObject * (((OptimizationItemWidget*)selectedList[1])->minimumSizeHint().height() + nTitleHeight));
      QMouseEvent e(QEvent::MouseButtonPress, point, Qt::LeftButton, Qt::LeftButton);
      itemsTable->center(e.x(), e.y());
      viewMousePressEvent(&e);
      //emit itemsTable(&e);
    }
}
 
void ParamFittingWidget::mouseSelected(OptimizationItemWidget* pSelected)
{
  if (selectedList.size() == 0)
    return;
 
  unsigned int i = 1;
  for (; (i < selectedList.size()) && (pSelected != selectedList[i]); i += 2)
;
  if (pSelected != selectedList[i]) //not find
    return;
 
  emit hide_me();
  if (activeObject >= 0)
    {
      QFrame* activeTitle = (QFrame*)(selectedList[activeObject * 2]);
      activeTitle->setPaletteBackgroundColor(QColor(160, 160, 255));
    }
 
  activeObject = i / 2;
 
  itemnamesTable->setSelected(itemnamesTable->currentItem(), false);
  itemnamesTable->setSelected(activeObject, true);
 
  QFrame* activeTitle = (QFrame*)(selectedList[activeObject * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
  emit show_me();
}
 
void ParamFittingWidget::slotBtnCancelClicked()
{}
 
void ParamFittingWidget::slotBtnConfirmClicked()
{
  COptFunction* func =
    dynamic_cast< COptFunction * >(GlobalKeys.get(objKey));
  unsigned i;
  for (i = 0; i < func->mParaList.size(); i++)
    {
      func->mMinList[i] = ((OptimizationItemWidget*)(selectedList[i * 2 + 1]))->getItemLowerLimit();
      func->mMaxList[i] = ((OptimizationItemWidget*)(selectedList[i * 2 + 1]))->getItemUpperLimit();
      func->mMinOperList.push_back(((OptimizationItemWidget*)(selectedList[i * 2 + 1]))->getItemLowerOper());
      func->mMaxOperList.push_back(((OptimizationItemWidget*)(selectedList[i * 2 + 1]))->getItemUpperOper());
    }
 
  bool up;
  for (i = 0; i < func->mParaList.size(); i++)
    {
      try
        {
          if (func->mMinList[i] != "-inf")
            {
              if (!func->mMinFunctionList[i])
                func->mMinFunctionList[i] = new CKinFunction();
              up = false;
              func->mMinFunctionList[i]->setDescription(func->mMinList[i]);
              // will automatically call the compile function for CKinFunction
            }
 
          if (func->mMaxList[i] != "+inf")
            {
              if (!func->mMaxFunctionList[i])
                func->mMaxFunctionList[i] = new CKinFunction();
              up = true;
              func->mMaxFunctionList[i]->setDescription(func->mMaxList[i]);
              // will automatically call the compile function for CKinFunction
            }
        }
      catch (CCopasiException Exception)
        {
          std::string warning_msg = "Invalid function expression. with common name<";
          warning_msg += func->mParaList[i]->getCN();
          if (up)
            warning_msg += ">\n Please check the upper bound function again \n";
          else
            warning_msg += ">\n Please check the lower bound function again \n";
          warning_msg += "Do you still want to keep your input ? \nPress <Yes> to keep.";
 
          if (QMessageBox::warning(this, "Invalid Function Input",
                                   FROM_UTF8(warning_msg),
                                   QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
            {
              activeObject = i;
              if (up)
                {
                  func->mMaxList[i] = "";
                  ((OptimizationItemWidget*)(selectedList[activeObject * 2 + 1]))->lineUpper->setText("");
                }
              else
                {
                  func->mMinList[i] = "";
                  ((OptimizationItemWidget*)(selectedList[activeObject * 2 + 1]))->lineLower->setText("");
                }
            } //end of if
        } //end of catch
    } //end of for
 
  // :TODO Bug 322: This should only be called when actual changes have been saved.
  CCopasiDataModel::Global->changed();
 
}
 
void ParamFittingWidget::viewMousePressEvent(QMouseEvent* e)
{
  if (selectedList.size() == 0)
    return;
  emit hide_me();
  if (activeObject >= 0)
    {
      QFrame* activeTitle = (QFrame*)(selectedList[activeObject * 2]);
      activeTitle->setPaletteBackgroundColor(QColor(160, 160, 255));
    }
 
  activeObject = e->y() / (((ScanItemWidget*)selectedList[1])->minimumSizeHint().height() + nTitleHeight);
  if (itemnamesTable->currentItem() != -1)
    itemnamesTable->setSelected(itemnamesTable->currentItem(), false);
  itemnamesTable->setSelected(activeObject, true);
 
  if (activeObject >= selectedList.size() / 2)
    {
      emit show_me();
      activeObject = -1;
      return;
    }
 
  QFrame* activeTitle = (QFrame*)(selectedList[activeObject * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
  emit show_me();
}*/

void ParamFittingWidget::viewMousePressEvent(QMouseEvent* e)
{}

const std::string ParamFittingWidget::getKey()
{
  return objKey;
}

/*void ParamFittingWidget::steadystateEditing()
{
  pSteadyStateWidget->show();
}
 
void ParamFittingWidget::timeEditing()
{
  pTrajectoryWidget->show();
}
 
void ParamFittingWidget::steadystateEnable()
{
  steadystateEditButton->setEnabled(steadystateCheck->isChecked());
}
 
void ParamFittingWidget::timeEnable()
{
  timeEditButton->setEnabled(timeCheck->isChecked());
}**********/
