/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/OptimizationWidget.cpp,v $
   $Revision: 1.20 $
   $Name:  $
   $Author: lixu1 $ 
   $Date: 2003/10/16 20:00:29 $
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
//#include <qtable.h>
#include <qlistbox.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qtextbrowser.h>

#include "ScanWidget.h"
#include "ScanItemWidget.h"
#include "OptimizationItemWidget.h"
#include "OptimizationWidget.h"
#include "copasi.h"
#include "listviews.h"
#include "ObjectBrowser.h"
#include "utilities/CGlobals.h"
#include "utilities/CMethodParameter.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "function/CKinFunction.h"
#include "optimization/COptFunction.h"

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
  languageChange();
  clearWState(WState_Polished);

  // tab order
  setTabOrder(expressionName, expressionText);
  setTabOrder(expressionText, addButton);
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

  connect(this, SIGNAL(hide_me()), (ListViews*)parent, SLOT(slotHideWidget()));
  connect(this, SIGNAL(show_me()), (ListViews*)parent, SLOT(slotShowWidget()));

  connect(itemnamesTable, SIGNAL(clicked(QListBoxItem*)), this, SLOT(ListBoxClicked(QListBoxItem*)));
  connect(itemnamesTable, SIGNAL(doubleClicked(QListBoxItem*)), this, SLOT(ListBoxDoubleClicked(QListBoxItem*)));

  connect(this, SIGNAL(hide_me()), (ListViews*)parent, SLOT(slotHideWidget()));
  connect(this, SIGNAL(show_me()), (ListViews*)parent, SLOT(slotShowWidget()));

  nTitleHeight = fontMetrics().height() + 6;
  expressionName->setText("Optimization Task");
  expressionName->setEnabled(false);

  expressionText->setText("-inf|Function  <|<=|== Optimization Item <|<=|== +inf|Function");
  expressionText->setEnabled(false);
}

/*
 *  Destroys the object and frees any allocated resources
 */
OptimizationWidget::~OptimizationWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void OptimizationWidget::languageChange()
{
  setCaption(tr("Expression"));
  expressionEditlabel->setText(tr("Expression"));
  expressionNameLabel->setText(tr("Expression Name"));
  itemsLabel->setText(tr("Copasi Items"));
  downButton->setText(QString::null);
  deleteButton->setText(QString::null);
  addButton->setText(QString::null);
  upButton->setText(QString::null);
  confirmButton->setText(tr("confirm"));
  cancelButton->setText(tr("cancel"));
}

bool OptimizationWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
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
  //let the user confirm?
  if (bUpdated && (QMessageBox::warning(NULL, "Report Definition Save", "Do you want to save the change you have made to this Report Definition ?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes))
    {
      slotBtnConfirmClicked();
      bUpdated = false;
    }
  return true;
}

bool OptimizationWidget::enter(const std::string & key)
{
  objKey = key;
  COptFunction* func = (COptFunction*)(CCopasiContainer*)CKeyFactory::get(key);
  //TODO: check if it really is a compartment

  if (func)
    return loadFromExpression(func);
  else
    return false;
}

bool OptimizationWidget::loadFromExpression(COptFunction*)
{
  bUpdated = false;
  COptFunction* func = (COptFunction*)(CCopasiContainer*)CKeyFactory::get(objKey);
  expressionName->setText(func->getObjectUniqueName().c_str());
  //  expressionText->setText(func-> serialize a function to a std::stream
  return true;
}

void OptimizationWidget::addButtonClicked()
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
    itemnamesTable->insertItem ((*pSelectedVector)[i]->getObjectUniqueName().c_str(), nSelectedObjects - 1);

  pdelete(pSelectedVector);
}

void OptimizationWidget::deleteButtonClicked()
{
  if (activeObject < 0 || activeObject >= selectedList.size() / 2)  // not a valid entry
    return;

  emit hide_me();

  COptFunction* optFunction = (COptFunction*)CKeyFactory::get(objKey);
  CCopasiObject* pOptObject = ((OptimizationItemWidget*)(selectedList[activeObject * 2 + 1]))->getCopasiObject();
  if (optFunction->mParaList.size() > 0)  // for reloading
    optFunction->removeItem(pOptObject->getCN().c_str());

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
      activeTitle->setText(pOptObject->getCN().c_str());
    }

  nSelectedObjects--;
  itemsTable->resizeContents(0, offsetY*selectedList.size() / 2);

  emit show_me();

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

  COptFunction* optFunction = (COptFunction*)CKeyFactory::get(objKey);

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
  activeTitle->setText(pObjectUp->getCN().c_str());

  //activate
  //upper one
  activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
  activeTitle->setText(pObjectDown->getCN().c_str());

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

  COptFunction* optFunction = (COptFunction*)CKeyFactory::get(objKey);

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
  activeTitle->setText(pObjectDown->getCN().c_str());

  //bottom one
  activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
  activeTitle->setText(pObjectUp->getCN().c_str());

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

  COptFunction* optFunction = (COptFunction*)(CCopasiContainer*)CKeyFactory::get(objKey);
  // need further work
  if (optFunction->bExisted(pObject->getCN().c_str()))
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

  newTitleBar->setText(pObject->getCN().c_str());
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
  COptFunction* func = (COptFunction*)(CCopasiContainer*)CKeyFactory::get(objKey);
  unsigned i;
  for (i = 0; i < func->mParaList.size(); i++)
    {
      //      func->mMinList[i] = ((OptimizationItemWidget*)(selectedList[i * 2 + 1]))->getItemLowerLimit();
      //      func->mMaxList[i] = ((OptimizationItemWidget*)(selectedList[i * 2 + 1]))->getItemUpperLimit();
      func->mMinOperList.push_back(((OptimizationItemWidget*)(selectedList[i * 2 + 1]))->getItemLowerOper());
      func->mMaxOperList.push_back(((OptimizationItemWidget*)(selectedList[i * 2 + 1]))->getItemUpperOper());
    }
  //  func->compile();
  func->connect();
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
