/*******************************************************************
 **  $ CopasiUI/ScanWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the 
 ** Scan Widget
 ********************************************************************/
#include <qfiledialog.h>
#include <qvbox.h>
#include <qvariant.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qscrollview.h>
#include <qtoolbutton.h>
#include <qcanvas.h>
#include <qlistbox.h>

#include "copasi.h"
#include "ScanWidget.h"
#include "scan/CScanTask.h"
#include "scan/CScanProblem.h"
#include "scan/CScanMethod.h"
#include "model/CModel.h"
#include "listviews.h"
#include "ScanItemWidget.h"
#include "ObjectBrowser.h"
#include "ObjectBrowserItem.h"

#include "SteadyStateWidget.h"
#include "TrajectoryWidget.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"

int ScanWidget::nSelectedObjects = 0;
int ScanWidget::nTitleHeight = 16;

/*
 *  Constructs a ScanWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ScanWidget::ScanWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  if (!name)
    setName("ScanWidget");
  setCaption(trUtf8("ScanWidget"));
  ScanWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ScanWidgetLayout");

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Problem"));

  ScanWidgetLayout->addWidget(TextLabel1, 0, 0);

  taskName = new QLineEdit(this, "taskName");

  ScanWidgetLayout->addWidget(taskName, 0, 1);

  Line2 = new QFrame(this, "Line2");
  Line2->setFrameShape(QFrame::HLine);
  Line2->setFrameShadow(QFrame::Sunken);
  Line2->setFrameShape(QFrame::HLine);

  ScanWidgetLayout->addMultiCellWidget(Line2, 5, 5, 0, 2);

  sExecutable = new QCheckBox(this, "sExecutable");
  sExecutable->setText(trUtf8("Scan Executable"));

  ScanWidgetLayout->addWidget(sExecutable, 0, 2);

  Layout2 = new QHBoxLayout(0, 0, 6, "Layout2");

  commitChange = new QPushButton(this, "commitChange");
  commitChange->setText(trUtf8("Scan"));
  Layout2->addWidget(commitChange);

  cancelChange = new QPushButton(this, "cancelChange");
  cancelChange->setText(trUtf8("Cancel"));
  Layout2->addWidget(cancelChange);

  ScanWidgetLayout->addMultiCellLayout(Layout2, 6, 6, 0, 2);

  Line1 = new QFrame(this, "Line1");
  Line1->setFrameShape(QFrame::HLine);
  Line1->setFrameShadow(QFrame::Sunken);
  Line1->setFrameShape(QFrame::HLine);

  ScanWidgetLayout->addMultiCellWidget(Line1, 1, 1, 0, 2);

  Line1_2 = new QFrame(this, "Line1_2");
  Line1_2->setFrameShape(QFrame::HLine);
  Line1_2->setFrameShadow(QFrame::Sunken);
  Line1_2->setFrameShape(QFrame::HLine);

  ScanWidgetLayout->addMultiCellWidget(Line1_2, 3, 3, 0, 2);

  Layout4 = new QHBoxLayout(0, 0, 6, "Layout4");

  Layout3 = new QHBoxLayout(0, 0, 6, "Layout3");

  steadyState = new QCheckBox(this, "steadyState");
  steadyState->setText(trUtf8("Steady State"));
  Layout3->addWidget(steadyState);

  eSteadyState = new QToolButton(this, "eSteadyState");
  eSteadyState->setText(trUtf8("Edit Steady"));
  Layout3->addWidget(eSteadyState);
  Layout4->addLayout(Layout3);

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8(""));
  Layout4->addWidget(TextLabel3);

  Layout4_2 = new QHBoxLayout(0, 0, 6, "Layout4_2");

  trajectory = new QCheckBox(this, "trajectory");
  trajectory->setText(trUtf8("Trajectory"));
  Layout4_2->addWidget(trajectory);

  eTrajectory = new QToolButton(this, "eTrajectory");
  eTrajectory->setText(trUtf8("Edit Trajectory"));
  Layout4_2->addWidget(eTrajectory);
  Layout4->addLayout(Layout4_2);

  ScanWidgetLayout->addMultiCellLayout(Layout4, 2, 2, 0, 2);

  Layout8 = new QHBoxLayout(0, 0, 6, "Layout8");

  Layout7 = new QVBoxLayout(0, 0, 6, "Layout7");

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Scan Items"));
  Layout7->addWidget(TextLabel2);

  Layout6 = new QGridLayout(0, 1, 1, 0, 6, "Layout6");

  deleteButton = new QPushButton(this, "deleteButton");
  deleteButton->setText(trUtf8("(-) Delete"));

  Layout6->addWidget(deleteButton, 0, 1);

  downButton = new QPushButton(this, "downButton");
  downButton->setText(trUtf8("(v) Down"));

  Layout6->addWidget(downButton, 1, 1);

  addButton = new QPushButton(this, "addButton");
  addButton->setText(trUtf8("(+) Add"));

  Layout6->addWidget(addButton, 0, 0);

  upButton = new QPushButton(this, "upButton");
  upButton->setText(trUtf8("(^) Up "));

  Layout6->addWidget(upButton, 1, 0);

  ObjectListBox = new QListBox(this, "ObjectListBox");
  ObjectListBox->insertItem(trUtf8(""));

  Layout6->addMultiCellWidget(ObjectListBox, 2, 2, 0, 1);
  Layout7->addLayout(Layout6);
  Layout8->addLayout(Layout7);

  scrollview = new ScanScrollView(this, 0, 0);
  scrollview->setVScrollBarMode(QScrollView::Auto);
  scrollview->setSelectedList(&selectedList);
  Layout8->addWidget(scrollview);

  ScanWidgetLayout->addMultiCellLayout(Layout8, 4, 4, 0, 2);

  // tab order
  setTabOrder(taskName, sExecutable);
  setTabOrder(sExecutable, trajectory);
  setTabOrder(trajectory, steadyState);
  setTabOrder(steadyState, addButton);
  setTabOrder(addButton, deleteButton);
  setTabOrder(deleteButton, upButton);
  setTabOrder(upButton, downButton);
  setTabOrder(downButton, ObjectListBox);
  setTabOrder(ObjectListBox, scrollview);
  setTabOrder(scrollview, commitChange);
  setTabOrder(commitChange, cancelChange);

  connect(this, SIGNAL(hide_me()), (ListViews*)parent, SLOT(slotHideWidget()));
  connect(this, SIGNAL(show_me()), (ListViews*)parent, SLOT(slotShowWidget()));

  connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
  connect(upButton, SIGNAL(clicked()), this, SLOT(upButtonClicked()));
  connect(downButton, SIGNAL(clicked()), this, SLOT(downButtonClicked()));

  connect(commitChange, SIGNAL(clicked()), this, SLOT(CommitChangeButton()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelChangeButton()));

  connect(steadyState, SIGNAL(clicked()), this, SLOT(SteadyStateButtonClicked()));
  connect(trajectory, SIGNAL(clicked()), this, SLOT(TrajectoryButtonClicked()));
  connect(sExecutable, SIGNAL(clicked()), this, SLOT(ScanButtonClicked()));

  connect(ObjectListBox, SIGNAL(clicked(QListBoxItem*)), this, SLOT(ListBoxClicked(QListBoxItem*)));
  connect(ObjectListBox, SIGNAL(doubleClicked(QListBoxItem*)), this, SLOT(ListBoxDoubleClicked(QListBoxItem*)));

  connect(eSteadyState, SIGNAL(clicked()), this, SLOT(SteadyStateEditing()));
  connect(eTrajectory, SIGNAL(clicked()), this, SLOT(TrajectoryEditing()));

  scanTask = NULL;
  activeObject = -1;
  selectedList.clear();

  nTitleHeight = fontMetrics().height() + 6;

  pSteadyStateWidget = new SteadyStateWidget(NULL);
  pSteadyStateWidget->hide();
  pTrajectoryWidget = new TrajectoryWidget(NULL);
  pTrajectoryWidget->hide();

  pSteadyStateWidget->loadSteadyStateTask(new CSteadyStateTask());
  pTrajectoryWidget->loadTrajectoryTask(new CTrajectoryTask());

  eSteadyState->setEnabled(steadyState->isChecked());
  eTrajectory->setEnabled(trajectory->isChecked());
}

void ScanWidget::SteadyStateEditing()
{
  pSteadyStateWidget->show();
}

void ScanWidget::TrajectoryEditing()
{
  pTrajectoryWidget->show();
}

ScanWidget::~ScanWidget()
{
  pdelete(scanTask);
  pdelete(pTrajectoryWidget);
  pdelete(pSteadyStateWidget);
  // no need to pdelete child widgets, Qt does it all for us
}

void ScanWidget::addButtonClicked()
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

  int i = 0;
  for (; i < pSelectedVector->size(); i++)
    if ((*pSelectedVector)[i])
      break;

  if (i >= pSelectedVector->size()) //no result returned
    {
      pdelete(pSelectedVector);
      return;
    }

  if (addNewScanItem((*pSelectedVector)[i]))
    ObjectListBox->insertItem ((*pSelectedVector)[i]->getObjectUniqueName().c_str(), nSelectedObjects - 1);

  pdelete(pSelectedVector);
}

void ScanWidget::deleteButtonClicked()
{
  if (activeObject < 0 || activeObject >= selectedList.size() / 2)  // not a valid entry
    return;

  emit hide_me();

  CCopasiObject* pObject = ((ScanItemWidget*)(selectedList[activeObject * 2 + 1]))->getObject();
  scanTask->getProblem()->removeScanItem(pObject->getCN().c_str());
  scrollview->removeChild(selectedList[2*activeObject]);
  scrollview->removeChild(selectedList[2*activeObject + 1]);

  ObjectListBox->removeItem (activeObject);

  int i = activeObject + 1;
  int offsetY = ((ScanItemWidget*)selectedList[1])->minimumSizeHint().height() + nTitleHeight;

  for (; i < selectedList.size() / 2; i++)
    {
      scrollview->moveChild(selectedList[2*i], 0, (i - 1)*offsetY);
      scrollview->moveChild(selectedList[2*i + 1], 0, (i - 1)*offsetY + nTitleHeight);
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
  if (activeObject >= 0)
    {
      CCopasiObject* pObject = ((ScanItemWidget*)(selectedList[activeObject * 2 + 1]))->getObject();
      ScanLineEdit* activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
      activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
      activeTitle->setText(pObject->getObjectUniqueName().c_str());
    }
  nSelectedObjects--;
  scrollview->resizeContents(0, offsetY*selectedList.size() / 2);
  emit show_me();

  if (activeObject >= 0)
    ListBoxClicked(ObjectListBox->item(activeObject));

  // to verify the size of the mparameterlist in ScanProblem
  // scanTask->getProblem()->paraCount();
}

void ScanWidget::upButtonClicked()
{
  if (activeObject <= 0 || activeObject >= selectedList.size() / 2)  // not a valid entry
    return;

  emit hide_me();

  CCopasiObject* pObjectDown = ((ScanItemWidget*)selectedList[2 * activeObject + 1])->getObject();
  CCopasiObject* pObjectUp = ((ScanItemWidget*)selectedList[2 * activeObject - 1])->getObject();
  ((ScanItemWidget*)selectedList[2*activeObject + 1])->setObject(pObjectUp);
  ((ScanItemWidget*)selectedList[2*activeObject - 1])->setObject(pObjectDown);
  ((ScanItemWidget*)selectedList[2*activeObject + 1])->loadObject();
  ((ScanItemWidget*)selectedList[2*activeObject - 1])->loadObject();
  activeObject--;

  //deactivate
  //lower one
  ScanLineEdit* activeTitle = (ScanLineEdit*)(selectedList[(activeObject + 1) * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(160, 160, 255));
  activeTitle->setText(pObjectUp->getObjectUniqueName().c_str());

  //activate
  //upper one
  activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
  activeTitle->setText(pObjectDown->getObjectUniqueName().c_str());

  //Update ListBox
  QString tmp = ObjectListBox->text (activeObject);
  ObjectListBox->changeItem (NULL, ObjectListBox->text(activeObject + 1) , activeObject);
  ObjectListBox->changeItem (NULL, tmp, activeObject + 1);

  scanTask->getProblem()->swapScanItem(activeObject + 1, activeObject);

  emit show_me();
  if (activeObject >= 0)
    ListBoxClicked(ObjectListBox->item(activeObject));
}

void ScanWidget::downButtonClicked()
{
  if (activeObject < 0 || activeObject >= selectedList.size() / 2 - 1)  // not a valid entry
    return;

  emit hide_me();
  activeObject++;
  CCopasiObject* pObjectDown = ((ScanItemWidget*)selectedList[2 * activeObject + 1])->getObject();
  CCopasiObject* pObjectUp = ((ScanItemWidget*)selectedList[2 * activeObject - 1])->getObject();
  ((ScanItemWidget*)selectedList[2*activeObject + 1])->setObject(pObjectUp);
  ((ScanItemWidget*)selectedList[2*activeObject - 1])->setObject(pObjectDown);
  ((ScanItemWidget*)selectedList[2*activeObject + 1])->loadObject();
  ((ScanItemWidget*)selectedList[2*activeObject - 1])->loadObject();

  //upper one
  ScanLineEdit* activeTitle = (ScanLineEdit*)(selectedList[(activeObject - 1) * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(160, 160, 255));
  activeTitle->setText(pObjectDown->getObjectUniqueName().c_str());

  //bottom one
  activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
  activeTitle->setText(pObjectUp->getObjectUniqueName().c_str());

  //Update ListBox
  QString tmp = ObjectListBox->text (activeObject);
  ObjectListBox->changeItem (NULL, ObjectListBox->text(activeObject - 1) , activeObject);
  ObjectListBox->changeItem (NULL, tmp, activeObject - 1);

  scanTask->getProblem()->swapScanItem(activeObject - 1, activeObject);

  emit show_me();
  if (activeObject >= 0)
    ListBoxClicked(ObjectListBox->item(activeObject));
}

void ScanWidget::CancelChangeButton()
{}

void ScanWidget::CommitChangeButton()
{
  scanTask->process();
}

void ScanWidget::ScanButtonClicked()
{
  scanTask->setRequested(sExecutable->isChecked());
  commitChange->setEnabled(sExecutable->isChecked());
}

void ScanWidget::SteadyStateButtonClicked()
{
  CScanProblem *scanProblem = scanTask->getProblem();
  scanProblem->setProcessSteadyState(steadyState->isChecked());
  eSteadyState->setEnabled(steadyState->isChecked());
}

void ScanWidget::TrajectoryButtonClicked()
{
  CScanProblem *scanProblem = scanTask->getProblem();
  scanProblem->setProcessTrajectory(trajectory->isChecked());
  eTrajectory->setEnabled(trajectory->isChecked());
  if (trajectory->isChecked())
    {}}

void ScanWidget::loadScan(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
      pSteadyStateWidget->setModel(mModel);
      pTrajectoryWidget->setModel(mModel);

      taskName->setText(tr("Scan"));
      scanTask = new CScanTask();
      CScanProblem *scanProblem = scanTask->getProblem();

      scanProblem->setModel(model);
      scanProblem->setSteadyStateTask(pSteadyStateWidget->mSteadyStateTask);
      scanProblem->setTrajectoryTask(pTrajectoryWidget->mTrajectoryTask);

      if (scanTask->isRequested() == true)
        sExecutable->setChecked(true);
      else
        sExecutable->setChecked(false);

      if (scanProblem->processTrajectory() == true)
        trajectory->setChecked(true);
      else
        trajectory->setChecked(false);

      if (scanProblem->processSteadyState() == true)
        steadyState->setChecked(true);
      else
        steadyState->setChecked(false);

      //      emit hide_me();
      //QMessageBox::information(this, "Metabolites Widget", QString::number(scanProblem->getListSize()));
      for (C_INT32 i = 0; i < scanProblem->getListSize(); i++)
        {
          /*
                    CMethodParameterList *itemList = scanProblem->getScanItem(i);
                    itemList->getName();
                    parameterTable = new QTable(scrollview, "parameterTable");
                    parameterTable->setNumCols(1);
                    parameterTable->setFocusPolicy(QWidget::WheelFocus);
                    parameterTable->horizontalHeader()->setLabel(0, "Value");
             pObject->getCN();
                    for (C_INT32 j = 0; j < itemList->size(); j++)
                      {
                        parameterTable->setNumRows(itemList->size());
                        //rowHeader->setLabel(j, itemList(j).c_str());
           
                        parameterTable->verticalHeader()->setLabel(j, itemList->getName(j).c_str());
                        parameterTable->setText(j, 0, QString::number(itemList->getValue(j)));
                      }
                    vBox->insertChild(parameterTable);
                    vBox->setSpacing(15);
          */
        }

      //     emit show_me();
      //      scrollview->addChild(vBox);
      //      ScanWidgetLayout->addMultiCellWidget(scrollview, 4, 9, 1, 4);
      //      scrollview->setVScrollBarMode(QScrollView::Auto);
    }
}

bool ScanWidget::addNewScanItem(CCopasiObject* pObject)
{
  if (!pObject)
    return false;

  if (scanTask->getProblem()->bExisted(pObject->getCN().c_str()))
    return false;

  int widgetOffset;
  emit hide_me();
  ScanItemWidget* parameterTable = new ScanItemWidget(this, "parameterTable");
  widgetOffset = nTitleHeight + nSelectedObjects * (parameterTable->minimumSizeHint().height() + nTitleHeight);

  ScanLineEdit* newTitleBar = new ScanLineEdit(this, "newTitleBar");
  newTitleBar->setFixedSize(QSize(scrollview->visibleWidth(), nTitleHeight));
  newTitleBar->setPaletteForegroundColor(QColor(255, 255, 0));
  newTitleBar->setPaletteBackgroundColor(QColor(160, 160, 255));
  pObject->getObjectUniqueName();
  newTitleBar->setText(pObject->getObjectUniqueName().c_str());
  newTitleBar->setReadOnly(TRUE);

  scrollview->addChild(newTitleBar, 0, widgetOffset - nTitleHeight);
  selectedList.push_back(newTitleBar);

  parameterTable->setObject(pObject);
  if (scrollview->visibleWidth() >= parameterTable->minimumSizeHint().width())
    parameterTable->setFixedWidth(scrollview->visibleWidth());
  else
    parameterTable->setFixedWidth(parameterTable->minimumSizeHint().width());

  parameterTable->setFixedHeight(parameterTable->minimumSizeHint().height());
  parameterTable->setObject(pObject);
  parameterTable->loadObject();

  scrollview->addChild(parameterTable, 0 , widgetOffset);
  scrollview->setVScrollBarMode(QScrollView::Auto);
  scrollview->resizeContents(0, widgetOffset + parameterTable->minimumSizeHint().height());
  selectedList.push_back(parameterTable);

  nSelectedObjects++;
  //  if (pObject->isContainer())
  scanTask->getProblem()->addScanItem(CMethodParameterList(pObject->getCN().c_str(), (CCopasiContainer*)pObject, pObject->getObjectType()));
  emit show_me();
  return true;
}

void ScanWidget::ListBoxDoubleClicked(QListBoxItem * item)
{
  if (ObjectListBox->index(item) == nSelectedObjects)
    addButtonClicked();
}

void ScanWidget::ListBoxClicked(QListBoxItem * item)
{
  if (nSelectedObjects && ObjectListBox->index(item) >= 0) //select an object
    {
      double newActiveObject = ObjectListBox->index(item) + 0.5;
      QPoint point(0, newActiveObject * (((ScanItemWidget*)selectedList[1])->minimumSizeHint().height() + nTitleHeight));
      QMouseEvent e(QEvent::MouseButtonPress, point, Qt::LeftButton, Qt::LeftButton);
      scrollview->center(e.x(), e.y());
      viewMousePressEvent(&e);
      //emit scrollview(&e);
    }
}

void ScanWidget::mouseSelected(ScanItemWidget* pSelected)
{
  if (selectedList.size() == 0)
    return;

  int i = 1;
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

  ObjectListBox->setSelected(ObjectListBox->currentItem(), false);
  ObjectListBox->setSelected(activeObject, true);

  QFrame* activeTitle = (QFrame*)(selectedList[activeObject * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
  emit show_me();
}

void ScanWidget::viewMousePressEvent(QMouseEvent* e)
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
  if (ObjectListBox->currentItem() != -1)
    ObjectListBox->setSelected(ObjectListBox->currentItem(), false);
  ObjectListBox->setSelected(activeObject, true);

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

ScanScrollView::ScanScrollView(QWidget* parent, const char* name, WFlags fl)
    : QScrollView(parent, name, fl)
{
  pSelectedList = NULL;
  mParent = (ScanWidget*)parent;
}

void ScanScrollView::contentsMousePressEvent(class QMouseEvent *e)
{
  QScrollView::contentsMousePressEvent(e);
  mParent->viewMousePressEvent(e);
}
void ScanScrollView:: resizeEvent(QResizeEvent * e)
{
  QScrollView::resizeEvent(e);
  if (!pSelectedList)
    return;
  unsigned i;
  for (i = 0; i < pSelectedList->size(); i++)
    {
      (*pSelectedList)[i]->setFixedWidth(visibleWidth());
    }
  //
}

void ScanScrollView::setSelectedList(std::vector<QWidget*>* pNewSelectedList)
{
  pSelectedList = pNewSelectedList;
}
