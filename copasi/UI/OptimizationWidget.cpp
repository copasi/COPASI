/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/OptimizationWidget.cpp,v $
   $Revision: 1.38 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/18 16:53:56 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 09/19
Comment : OptimizationWidget for UI of the optimization function
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlistbox.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qtextbrowser.h>
#include <qmessagebox.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>

#include "ScanWidget.h"
#include "ScanItemWidget.h"
#include "OptimizationItemWidget.h"
#include "OptimizationWidget.h"
#include "copasi.h"
#include "listviews.h"
#include "ObjectBrowserDialog.h"
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

#include "report/CKeyFactory.h"
#include "./icons/scanwidgetbuttonicon.xpm"

/*
 *  Constructs a OptimizationWidget as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
OptimizationWidget::OptimizationWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiParametersWidget(parent, name, fl),
    bUpdated(false)
{
  nSelectedObjects = 0;
  nTitleHeight = 16;
  activeObject = -1;
  selectedList.clear();

  QPixmap image0((const char**) image0_data);
  QPixmap image1((const char**) image1_data);
  QPixmap image2((const char**) image2_data);
  QPixmap image3((const char**) image3_data);

  /*
    if (!name)
      setName("OptimizationWidget");
    OptimizationWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "OptimizationWidgetLayout");
   
    layout18 = new QVBoxLayout(0, 0, 6, "layout18");
   
    layout17 = new QGridLayout(0, 1, 1, 0, 6, "layout17");
   
    //    expressionText = new QTextBrowser(this, "expressionText");
    //   expressionText = new QLineEdit(this, "expressionText");
    expressionText = new QLineEdit(this, "expressionText");
   
    layout17->addWidget(expressionText, 1, 1);
   
    expressionName = new QLineEdit(this, "expressionName");
    expressionName->setFrameShape(QLineEdit::LineEditPanel);
    expressionName->setFrameShadow(QLineEdit::Sunken);
   
    layout17->addWidget(expressionName, 0, 1);
   
    expressionEditlabel = new QLabel(this, "expressionEditlabel");
   
    layout17->addWidget(expressionEditlabel, 1, 0);
   
    expressionNameLabel = new QLabel(this, "expressionNameLabel");
   
    layout17->addWidget(expressionNameLabel, 0, 0);
    layout18->addLayout(layout17);
   
    bodyField_2 = new QFrame(this, "bodyField_2");
    bodyField_2->setFrameShape(QFrame::HLine);
    bodyField_2->setFrameShadow(QFrame::Sunken);
    bodyField_2->setFrameShape(QFrame::HLine);
    layout18->addWidget(bodyField_2);
   
    layout16 = new QHBoxLayout(0, 0, 6, "layout16");
   
    layout15 = new QVBoxLayout(0, 0, 6, "layout15");
   
    itemsLabel = new QLabel(this, "itemsLabel");
    layout15->addWidget(itemsLabel);
   
    layout14 = new QGridLayout(0, 1, 1, 0, 6, "layout14");
   
    downButton = new QPushButton(this, "downButton");
    downButton->setText(trUtf8(""));
    downButton->setPixmap(image1);
    layout14->addWidget(downButton, 1, 1);
   
    deleteButton = new QPushButton(this, "deleteButton");
    deleteButton->setText(trUtf8(""));
    deleteButton->setPixmap(image0);
   
    layout14->addWidget(deleteButton, 0, 1);
   
    addButton = new QPushButton(this, "addButton");
    addButton->setText(trUtf8(""));
    addButton->setPixmap(image2);
    layout14->addWidget(addButton, 0, 0);
   
    //manually change to add icon for alignment need
    upButton = new QPushButton(this, "upButton");
    upButton->setText(trUtf8(""));
    upButton->setPixmap(image3);
    layout14->addWidget(upButton, 1, 0);
   
    itemnamesTable = new QListBox(this, "itemnamesTable");
    itemnamesTable->insertItem(trUtf8("click here to add new item"));
    layout14->addMultiCellWidget(itemnamesTable, 2, 2, 0, 1);
   
    layout15->addLayout(layout14);
    layout16->addLayout(layout15);
   
    itemsTable = new ScanScrollView(this, 0, 0);
    OptimizationItemWidget* parameterTable = new OptimizationItemWidget(this, "parameterTable");
    itemsTable->setMinimumWidth(parameterTable->minimumSizeHint().width());
    pdelete(parameterTable);
    itemsTable->setVScrollBarMode(QScrollView::Auto);
    itemsTable->setHScrollBarMode(QScrollView::AlwaysOff); //Disable Horizonal Scroll
    itemsTable->setSelectedList(&selectedList);
   
    // itemsTable = new QListBox(this, "itemsTable");
    layout16->addWidget(itemsTable);
    layout18->addLayout(layout16);
   
    bodyField = new QFrame(this, "bodyField");
    bodyField->setFrameShape(QFrame::HLine);
    bodyField->setFrameShadow(QFrame::Sunken);
    bodyField->setFrameShape(QFrame::HLine);
    layout18->addWidget(bodyField);
   
    layout14_2 = new QHBoxLayout(0, 0, 6, "layout14_2");
   
    confirmButton = new QPushButton(this, "confirmButton");
    layout14_2->addWidget(confirmButton);
   
    cancelButton = new QPushButton(this, "cancelButton");
    layout14_2->addWidget(cancelButton);
    layout18->addLayout(layout14_2);
   
    OptimizationWidgetLayout->addLayout(layout18, 0, 0);
  */

  if (!name)
    setName("ExpressionWidget");
  ExpressionWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ExpressionWidgetLayout");

  bodyField = new QFrame(this, "bodyField");
  bodyField->setFrameShape(QFrame::HLine);
  bodyField->setFrameShadow(QFrame::Sunken);
  bodyField->setFrameShape(QFrame::HLine);

  ExpressionWidgetLayout->addMultiCellWidget(bodyField, 10, 10, 0, 2);

  layout14 = new QHBoxLayout(0, 0, 6, "layout14");

  confirmButton = new QPushButton(this, "confirmButton");
  layout14->addWidget(confirmButton);

  cancelButton = new QPushButton(this, "cancelButton");
  layout14->addWidget(cancelButton);

  ExpressionWidgetLayout->addMultiCellLayout(layout14, 11, 11, 0, 2);

  //******* 2nd set of copasi items added
  itemsTable2 = new ScanScrollView(this, 0, 0);
  OptimizationItemWidget* parameterTable2 = new OptimizationItemWidget(this, "parameterTable2");
  itemsTable2->setMinimumWidth(parameterTable2->minimumSizeHint().width());
  pdelete(parameterTable2);
  itemsTable2->setVScrollBarMode(QScrollView::Auto);
  itemsTable2->setHScrollBarMode(QScrollView::AlwaysOff); //Disable Horizonal Scroll
  itemsTable2->setSelectedList(&selectedList);

  ExpressionWidgetLayout->addWidget(itemsTable2, 9, 2);

  copasiItemsTableLayout = new QGridLayout(0, 1, 1, 0, 6, "copasiItemsTableLayout");

  downButton2 = new QPushButton(this, "downButton2");
  downButton2->setText(trUtf8(""));
  downButton2->setPixmap(image1);
  copasiItemsTableLayout->addWidget(downButton2, 2, 1);  //was layout 8

  deleteButton2 = new QPushButton(this, "deleteButton2");
  deleteButton2->setText(trUtf8(""));
  deleteButton2->setPixmap(image0);
  copasiItemsTableLayout->addWidget(deleteButton2, 1, 1);

  addButton2 = new QPushButton(this, "addButton2");
  addButton2->setText(trUtf8(""));
  addButton2->setPixmap(image2);
  copasiItemsTableLayout->addWidget(addButton2, 1, 0);

  //manually change to add icon for alignment need
  upButton2 = new QPushButton(this, "upButton2");
  upButton2->setText(trUtf8(""));
  upButton2->setPixmap(image3);
  copasiItemsTableLayout->addWidget(upButton2, 2, 0);

  itemnamesTable2 = new QListBox(this, "itemnamesTable2");
  copasiItemsTableLayout->addMultiCellWidget(itemnamesTable2, 3, 3, 0, 1);

  itemsLabel2 = new QLabel(this, "itemsLabel2");
  itemsLabel2->setText("Copasi Items");

  copasiItemsTableLayout->addMultiCellWidget(itemsLabel2, 0, 0, 0, 1);

  ExpressionWidgetLayout->addMultiCellLayout(copasiItemsTableLayout, 9, 9, 0, 1);

  // below is the code for the division line between the two items tables sections
  copasiItemsDivider = new QFrame(this, "copasiItemsDivider");
  copasiItemsDivider->setFrameShape(QFrame::HLine);
  copasiItemsDivider->setFrameShadow(QFrame::Sunken);
  copasiItemsDivider->setFrameShape(QFrame::HLine);

  ExpressionWidgetLayout->addMultiCellWidget(copasiItemsDivider, 8, 8, 0, 2);
  //********

  itemsTable = new ScanScrollView(this, 0, 0);
  OptimizationItemWidget* parameterTable = new OptimizationItemWidget(this, "parameterTable");
  itemsTable->setMinimumWidth(parameterTable->minimumSizeHint().width());
  pdelete(parameterTable);
  itemsTable->setVScrollBarMode(QScrollView::Auto);
  itemsTable->setHScrollBarMode(QScrollView::AlwaysOff); //Disable Horizonal Scroll
  itemsTable->setSelectedList(&selectedList);

  ExpressionWidgetLayout->addWidget(itemsTable, 7, 2);

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

  ExpressionWidgetLayout->addMultiCellLayout(layout8, 7, 7, 0, 1);

  bodyField_2 = new QFrame(this, "bodyField_2");
  bodyField_2->setFrameShape(QFrame::HLine);
  bodyField_2->setFrameShadow(QFrame::Sunken);
  bodyField_2->setFrameShape(QFrame::HLine);

  ExpressionWidgetLayout->addMultiCellWidget(bodyField_2, 6, 6, 0, 2);

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

  ExpressionWidgetLayout->addMultiCellLayout(layout7, 5, 5, 0, 2);

  bodyField_2_2 = new QFrame(this, "bodyField_2_2");
  bodyField_2_2->setFrameShape(QFrame::HLine);
  bodyField_2_2->setFrameShadow(QFrame::Sunken);
  bodyField_2_2->setFrameShape(QFrame::HLine);

  ExpressionWidgetLayout->addMultiCellWidget(bodyField_2_2, 4, 4, 0, 2);

  expressionName = new QLineEdit(this, "expressionName");
  expressionName->setFrameShape(QLineEdit::LineEditPanel);
  expressionName->setFrameShadow(QLineEdit::Sunken);

  ExpressionWidgetLayout->addMultiCellWidget(expressionName, 0, 0, 1, 2);

  methodCombo = new QComboBox(FALSE, this, "methodCombo");
  methodCombo->insertItem("Genetic algorithms(SA--)");
  methodCombo->insertItem("Random Search");

  ExpressionWidgetLayout->addMultiCellWidget(methodCombo, 2, 2, 1, 2);

  optimizationLabel = new QLabel(this, "optimizationLabel");

  ExpressionWidgetLayout->addWidget(optimizationLabel, 2, 0);

  expressionEditlabel = new QLabel(this, "expressionEditlabel");

  ExpressionWidgetLayout->addWidget(expressionEditlabel, 3, 0);

  expressionText = new QLineEdit(this, "expressionText");
  expressionText->setFrameShape(QLineEdit::LineEditPanel);
  expressionText->setFrameShadow(QLineEdit::Sunken);

  ExpressionWidgetLayout->addMultiCellWidget(expressionText, 3, 3, 1, 2);

  // added by Christine below used to indicate minimize or maximize optimization type
  qbuttongroup = new QButtonGroup(this, "buttonGroup");
  radioButtonLayout = new QHBoxLayout(qbuttongroup, 0, 6, "radioButtonLayout");
  maximizeRadio = new QRadioButton("Maximize", qbuttongroup, "maximizeRadio");
  maximizeRadio->setChecked(true);
  minimizeRadio = new QRadioButton("Minimize", qbuttongroup, "minimizeRadio");
  radioButtonLayout->addWidget(maximizeRadio);
  radioButtonLayout->addWidget(minimizeRadio);
  ExpressionWidgetLayout->addMultiCellWidget(qbuttongroup, 1, 1, 0, 2);

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

  SteadyStateKey = (new CSteadyStateTask(NULL))->getKey();
  TrajectoryKey = (new CTrajectoryTask(NULL))->getKey();
  pSteadyStateWidget = new SteadyStateWidget(NULL);
  pTrajectoryWidget = new TrajectoryWidget(NULL);
  pSteadyStateWidget->hide();
  pTrajectoryWidget->hide();
}

/*
 *  Destroys the object and frees any allocated resources
 */
OptimizationWidget::~OptimizationWidget()
{
  // no need to delete child widgets, Qt does it all for us
  CSteadyStateTask * sst =
    dynamic_cast< CSteadyStateTask * >(GlobalKeys.get(SteadyStateKey));
  pdelete(sst);

  CTrajectoryTask* tt =
    dynamic_cast< CTrajectoryTask * >(GlobalKeys.get(TrajectoryKey));
  pdelete(tt);
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void OptimizationWidget::languageChange()
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
}

bool OptimizationWidget::update(ListViews::ObjectType objectType,
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

bool OptimizationWidget::leave()
{
  slotBtnConfirmClicked();
  bUpdated = false;
  return true;
}

bool OptimizationWidget::enter(const std::string & key)
{
  objKey = key;
  COptFunction* func = dynamic_cast< COptFunction * >(GlobalKeys.get(key));
  pSteadyStateWidget->enter(SteadyStateKey);
  pTrajectoryWidget->enter(TrajectoryKey);

  if (func)
    return loadFromExpression(func);
  else
    return false;
}

bool OptimizationWidget::loadFromExpression(COptFunction*)
{
  bUpdated = false;
  COptFunction* func = dynamic_cast< COptFunction * >(GlobalKeys.get(objKey));
  expressionName->setText(FROM_UTF8(func->getObjectUniqueName()));
  //  expressionText->setText(func-> serialize a function to a std::stream
  return true;
}

void OptimizationWidget::addButtonClicked()
{
  ObjectBrowserDialog* pSelectedObjects = new ObjectBrowserDialog();
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

void OptimizationWidget::deleteButtonClicked()
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

void OptimizationWidget::upButtonClicked()
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

void OptimizationWidget::downButtonClicked()
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

bool OptimizationWidget::addNewOptItem(CCopasiObject* pObject)
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

void OptimizationWidget::ListBoxDoubleClicked(QListBoxItem * item)
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

void OptimizationWidget::mouseSelected(OptimizationItemWidget* pSelected)
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

void OptimizationWidget::slotBtnCancelClicked()
{}

void OptimizationWidget::slotBtnConfirmClicked()
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
}

void OptimizationWidget::viewMousePressEvent(QMouseEvent* e)
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
}

const std::string OptimizationWidget::getKey()
{
  return objKey;
}

void OptimizationWidget::steadystateEditing()
{
  pSteadyStateWidget->show();
}

void OptimizationWidget::timeEditing()
{
  pTrajectoryWidget->show();
}

void OptimizationWidget::steadystateEnable()
{
  steadystateEditButton->setEnabled(steadystateCheck->isChecked());
}

void OptimizationWidget::timeEnable()
{
  timeEditButton->setEnabled(timeCheck->isChecked());
}
