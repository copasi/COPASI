/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ScanWidget.cpp,v $
   $Revision: 1.169 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/09/23 18:28:18 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 06/03 
Comment : Copasi ScanWidget including:
 
Contains: front end of Scan Objects from given dataModel,
 
Contact: Please contact lixu1@vt.edu.
 *********************************************************/
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
#include <qmessagebox.h>

#include "copasi.h"

#include "ScanWidget.h"
#include "scan/CScanTask.h"
#include "scan/CScanProblem.h"
#include "scan/CScanMethod.h"
#include "model/CModel.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "ScanItemWidget.h"
#include "ObjectBrowser.h"
#include "ObjectBrowserItem.h"
#include "SteadyStateWidget.h"
#include "TrajectoryWidget.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "report/CKeyFactory.h"
#include "CReportDefinitionSelect.h"
#include "qtUtilities.h"

#include "./icons/scanwidgetbuttonicon.xpm"

/*
 *  Constructs a ScanWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ScanWidget::ScanWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiParametersWidget(parent, name, f),
    pParent(parent)
{
  nSelectedObjects = 0;
  nTitleHeight = 16;
  activeObject = -1;
  selectedList.clear();

  if (!name)
    setName("ScanWidget");

  QPixmap image0((const char**) image0_data);
  QPixmap image1((const char**) image1_data);
  QPixmap image2((const char**) image2_data);
  QPixmap image3((const char**) image3_data);

  setCaption(trUtf8("ScanWidget"));
  ScanWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ScanWidgetLayout");

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

  scanButton = new QPushButton(this, "scanButton");
  scanButton->setText(trUtf8("Scan"));
  Layout2->addWidget(scanButton);

  cancelChange = new QPushButton(this, "cancelChange");
  cancelChange->setText(trUtf8("cancelChange"));
  Layout2->addWidget(cancelChange);

  reportDefinitionButton = new QPushButton(this, "ReportDefinition");
  reportDefinitionButton->setText(trUtf8("ReportDefinition"));
  Layout2->addWidget(reportDefinitionButton);

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

  Layout24 = new QHBoxLayout(0, 0, 6, "Layout24");

  Layout7 = new QVBoxLayout(0, 0, 6, "Layout7");

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Scan Items"));
  Layout7->addWidget(TextLabel2);

  Layout6 = new QGridLayout(0, 1, 1, 0, 6, "Layout6");

  deleteButton = new QPushButton(this, "deleteButton");
  deleteButton->setText(trUtf8(""));
  deleteButton->setPixmap(image0);

  Layout6->addWidget(deleteButton, 0, 1);

  downButton = new QPushButton(this, "downButton");
  downButton->setText(trUtf8(""));
  downButton->setPixmap(image1);

  Layout6->addWidget(downButton, 1, 1);

  addButton = new QPushButton(this, "addButton");
  addButton->setText(trUtf8(""));
  addButton->setPixmap(image2);

  Layout6->addWidget(addButton, 0, 0);

  upButton = new QPushButton(this, "upButton");
  upButton->setText(trUtf8(""));
  upButton->setPixmap(image3);

  Layout6->addWidget(upButton, 1, 0);

  ObjectListBox = new QListBox(this, "ObjectListBox");
  ObjectListBox->insertItem(trUtf8("click here to add new item"));

  Layout6->addMultiCellWidget(ObjectListBox, 2, 2, 0, 1);
  Layout7->addLayout(Layout6);
  Layout24->addLayout(Layout7);

  scrollview = new ScanScrollView(this, 0, 0);
  ScanItemWidget* parameterTable = new ScanItemWidget(this, "parameterTable");
  scrollview->setMinimumWidth(parameterTable->minimumSizeHint().width());
  pdelete(parameterTable);
  scrollview->setVScrollBarMode(QScrollView::Auto);
  scrollview->setHScrollBarMode(QScrollView::AlwaysOff); //Disable Horizonal Scroll
  scrollview->setSelectedList(&selectedList);
  Layout24->addWidget(scrollview);

  ScanWidgetLayout->addMultiCellLayout(Layout24, 4, 4, 0, 2);

  // tab order
  setTabOrder(taskName, sExecutable);
  setTabOrder(sExecutable, steadyState);
  setTabOrder(steadyState, trajectory);
  setTabOrder(trajectory, addButton);
  setTabOrder(addButton, deleteButton);
  setTabOrder(deleteButton, upButton);
  setTabOrder(upButton, downButton);
  setTabOrder(downButton, scrollview);
  setTabOrder(scrollview, ObjectListBox);
  setTabOrder(ObjectListBox, scanButton);
  setTabOrder(scanButton, cancelChange);
  setTabOrder(cancelChange, reportDefinitionButton);

  //  connect(this, SIGNAL(hide_me()), (ListViews*)parent, SLOT(slotHideWidget()));
  //  connect(this, SIGNAL(show_me()), (ListViews*)parent, SLOT(slotShowWidget()));

  connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
  connect(upButton, SIGNAL(clicked()), this, SLOT(upButtonClicked()));
  connect(downButton, SIGNAL(clicked()), this, SLOT(downButtonClicked()));

  connect(scanButton, SIGNAL(clicked()), this, SLOT(runScanTask()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelChangeButton()));
  connect(reportDefinitionButton, SIGNAL(clicked()), this, SLOT(ReportDefinitionClicked()));

  connect(steadyState, SIGNAL(clicked()), this, SLOT(SteadyStateButtonClicked()));
  connect(trajectory, SIGNAL(clicked()), this, SLOT(TrajectoryButtonClicked()));
  connect(sExecutable, SIGNAL(clicked()), this, SLOT(ScanCheckBoxClicked()));

  connect(ObjectListBox, SIGNAL(clicked(QListBoxItem*)), this, SLOT(ListBoxClicked(QListBoxItem*)));
  connect(ObjectListBox, SIGNAL(doubleClicked(QListBoxItem*)), this, SLOT(ListBoxDoubleClicked(QListBoxItem*)));

  connect(eSteadyState, SIGNAL(clicked()), this, SLOT(SteadyStateEditing()));
  connect(eTrajectory, SIGNAL(clicked()), this, SLOT(TrajectoryEditing()));

  nTitleHeight = fontMetrics().height() + 6;

  scanTaskKey = (new CScanTask())->getKey();
  SteadyStateKey = (new CSteadyStateTask())->getKey();
  TrajectoryKey = (new CTrajectoryTask())->getKey();
  pSteadyStateWidget = new SteadyStateWidget(NULL);
  pTrajectoryWidget = new TrajectoryWidget(NULL);
  pSteadyStateWidget->hide();
  pTrajectoryWidget->hide();

  //pSteadyStateWidget->loadSteadyStateTask(new CSteadyStateTask());
  //pTrajectoryWidget->loadTrajectoryTask(/*new CTrajectoryTask()*/);

  sExecutable->setEnabled(false);
  scanButton->setEnabled(false);

  steadyState->setEnabled(false);
  eSteadyState->setEnabled(false);

  trajectory->setEnabled(false);
  eTrajectory->setEnabled(false);

  reportDefinitionButton->setEnabled(false);
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
  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
  pdelete(scanTask);

  CSteadyStateTask* sst =
    dynamic_cast< CSteadyStateTask * >(GlobalKeys.get(SteadyStateKey));
  pdelete(sst);

  CTrajectoryTask* tt =
    dynamic_cast< CTrajectoryTask * >(GlobalKeys.get(TrajectoryKey));
  pdelete(tt);

  selectedList.clear();
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

  unsigned C_INT32 i = 0;
  for (; i < pSelectedVector->size(); i++)
    if ((*pSelectedVector)[i])
      break;

  if (i >= pSelectedVector->size()) //no result returned
    {
      pdelete(pSelectedVector);
      return;
    }

  if (addNewScanItem((*pSelectedVector)[i]))
    ObjectListBox->insertItem (FROM_UTF8((*pSelectedVector)[i]->getObjectUniqueName()), nSelectedObjects - 1);

  pdelete(pSelectedVector);
}

void ScanWidget::deleteButtonClicked()
{
  int pp = selectedList.size();
  if (activeObject < 0 || activeObject >= selectedList.size() / 2)  // not a valid entry
    return;

  emit hide_me();

  ((ScanItemWidget*)selectedList[1])->setFirstWidget(false);

  CCopasiParameterGroup* pScanObject = ((ScanItemWidget*)(selectedList[activeObject * 2 + 1]))->getScanObject();
  //  if (!GlobalKeys.get(scanTaskKey))
  //   return;
  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
  if (((CScanProblem *)scanTask->getProblem())->getListSize() > 0)  // for reloading
    ((CScanProblem *)scanTask->getProblem())->
    removeScanItem(pScanObject-> /*CCopasiParameter::*/getObjectName());
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
  if ((activeObject >= 0) && (((CScanProblem *)scanTask->getProblem())->getListSize() > 0))
    {
      CCopasiObject* pScanObject = ((ScanItemWidget*)(selectedList[activeObject * 2 + 1]))->getScanObject();
      ScanLineEdit* activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
      activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
      //      activeTitle->setText(pObject->getObjectUniqueName().);
      activeTitle->setText(FROM_UTF8(pScanObject->getCN()));
    }
  nSelectedObjects--;
  scrollview->resizeContents(0, offsetY*selectedList.size() / 2);

  if ((selectedList.size() > 0) && (((CScanProblem *)scanTask->getProblem())->getListSize() > 0))
    {
      ((ScanItemWidget*)selectedList[1])->setFirstWidget(true);
    }

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
  ((ScanItemWidget*)selectedList[1])->setFirstWidget(false);

  CCopasiParameterGroup* pScanObjectDown = ((ScanItemWidget*)selectedList[2 * activeObject + 1])->getScanObject();
  CCopasiParameterGroup* pScanObjectUp = ((ScanItemWidget*)selectedList[2 * activeObject - 1])->getScanObject();
  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));

  ((ScanItemWidget*)selectedList[2*activeObject + 1])->setScanObject(((CScanProblem *)scanTask->getProblem())->getScanItem(activeObject - 1));
  ((ScanItemWidget*)selectedList[2*activeObject - 1])->setScanObject(((CScanProblem *)scanTask->getProblem())->getScanItem(activeObject));
  ((ScanItemWidget*)selectedList[2*activeObject + 1])->updateObject();
  ((ScanItemWidget*)selectedList[2*activeObject - 1])->updateObject();
  activeObject--;

  //deactivate
  //lower one
  ScanLineEdit* activeTitle = (ScanLineEdit*)(selectedList[(activeObject + 1) * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(160, 160, 255));
  activeTitle->setText(FROM_UTF8(pScanObjectUp-> /*CCopasiParameter::*/getObjectName()));

  //activate
  //upper one
  activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
  activeTitle->setText(FROM_UTF8(pScanObjectDown-> /*CCopasiParameter::*/getObjectName()));

  //Update ListBox
  QString tmp = ObjectListBox->text (activeObject);
  ObjectListBox->changeItem (NULL, ObjectListBox->text(activeObject + 1) , activeObject);
  ObjectListBox->changeItem (NULL, tmp, activeObject + 1);

  ((CScanProblem *)scanTask->getProblem())->swapScanItem(activeObject + 1, activeObject);

  ((ScanItemWidget*)selectedList[1])->setFirstWidget(true);
  emit show_me();
  if (activeObject >= 0)
    ListBoxClicked(ObjectListBox->item(activeObject));
}

void ScanWidget::downButtonClicked()
{
  if (activeObject < 0 || activeObject >= selectedList.size() / 2 - 1)  // not a valid entry
    return;

  emit hide_me();

  ((ScanItemWidget*)selectedList[1])->setFirstWidget(false);

  activeObject++;
  CCopasiParameterGroup* pObjectDown = ((ScanItemWidget*)selectedList[2 * activeObject + 1])->getScanObject();
  CCopasiParameterGroup* pObjectUp = ((ScanItemWidget*)selectedList[2 * activeObject - 1])->getScanObject();
  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
  ((ScanItemWidget*)selectedList[2*activeObject + 1])->setScanObject(((CScanProblem *)scanTask->getProblem())->getScanItem(activeObject - 1));
  ((ScanItemWidget*)selectedList[2*activeObject - 1])->setScanObject(((CScanProblem *)scanTask->getProblem())->getScanItem(activeObject));
  ((ScanItemWidget*)selectedList[2*activeObject + 1])->updateObject();
  ((ScanItemWidget*)selectedList[2*activeObject - 1])->updateObject();

  //upper one
  ScanLineEdit* activeTitle = (ScanLineEdit*)(selectedList[(activeObject - 1) * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(160, 160, 255));
  activeTitle->setText(FROM_UTF8(pObjectDown-> /*CCopasiParameter::*/getObjectName()));

  //bottom one
  activeTitle = (ScanLineEdit*)(selectedList[activeObject * 2]);
  activeTitle->setPaletteBackgroundColor(QColor(0, 0, 255));
  activeTitle->setText(FROM_UTF8(pObjectUp-> /*CCopasiParameter::*/getObjectName()));

  //Update ListBox
  QString tmp = ObjectListBox->text (activeObject);
  ObjectListBox->changeItem (NULL, ObjectListBox->text(activeObject - 1) , activeObject);
  ObjectListBox->changeItem (NULL, tmp, activeObject - 1);

  ((CScanProblem *)scanTask->getProblem())->swapScanItem(activeObject - 1, activeObject);

  ((ScanItemWidget*)selectedList[1])->setFirstWidget(true);

  emit show_me();
  if (activeObject >= 0)
    ListBoxClicked(ObjectListBox->item(activeObject));
}

void ScanWidget::CancelChangeButton()
{}

void ScanWidget::ScanCheckBoxClicked()
{
  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
  scanTask->setRequested(sExecutable->isChecked());
  scanButton->setEnabled(sExecutable->isChecked());
}

void ScanWidget::runScanTask()
{
  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));

  std::ofstream output;
  if (scanTask->getReport().getTarget() != "")
    {
      if (scanTask->getReport().append())
        output.open(scanTask->getReport().getTarget().c_str(), std::ios_base::out | std::ios_base::app);
      else
        output.open(scanTask->getReport().getTarget().c_str(), std::ios_base::out);
    }
  if (output.is_open())
    scanTask->initializeReporting(output);
  else //ask if user insists on proceeding
    {
      if (QMessageBox::information (NULL, "No output specified,",
                                    "No report output target defined, Copasi cannot creat output for you.\n Do you want to continue running scan task with no output?",
                                    QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
        return;
    }

  scanTask->process();

  ((ListViews*)pParent)->notify(ListViews::STATE, ListViews::CHANGE, dataModel->getModel()->getKey());
  unsetCursor();
}

void ScanWidget::SteadyStateButtonClicked()
{
  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
  CScanProblem *scanProblem = ((CScanProblem *)scanTask->getProblem());
  scanProblem->setProcessSteadyState(steadyState->isChecked());
  eSteadyState->setEnabled(steadyState->isChecked());
}

void ScanWidget::TrajectoryButtonClicked()
{
  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
  CScanProblem *scanProblem = ((CScanProblem *)scanTask->getProblem());
  scanProblem->setProcessTrajectory(trajectory->isChecked());
  eTrajectory->setEnabled(trajectory->isChecked());
  if (trajectory->isChecked())
    {}}

void ScanWidget::loadScan()
{
  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));

  if (!scanTask) return;

  // @comment: UI Stuff
  taskName->setText(tr("Scan"));
  CScanProblem *scanProblem = ((CScanProblem *)scanTask->getProblem());
  mModel = scanProblem->getModel();

  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast< CSteadyStateTask * >(GlobalKeys.get(SteadyStateKey));
  assert(mSteadyStateTask);

  CSteadyStateProblem * mSteadystateproblem =
    (CSteadyStateProblem *) mSteadyStateTask->getProblem();
  mSteadystateproblem->setModel(mModel);

  CTrajectoryTask* mTrajectoryTask =
    dynamic_cast< CTrajectoryTask * >(GlobalKeys.get(TrajectoryKey));
  assert(mTrajectoryTask);

  CTrajectoryProblem * mTrajectoryproblem =
    (CTrajectoryProblem *) mTrajectoryTask->getProblem();
  mTrajectoryproblem->setModel(mModel);

  scanProblem->setSteadyStateTask(mSteadyStateTask);
  scanProblem->setTrajectoryTask(mTrajectoryTask);
  scanProblem->setProcessSteadyState(steadyState->isChecked());
  scanProblem->setProcessTrajectory(trajectory->isChecked());

  sExecutable->setEnabled(true);
  if (scanTask->isRequested() == true)
    {
      sExecutable->setChecked(true);
      scanButton->setEnabled(true);
    }
  else
    {
      sExecutable->setChecked(false);
      scanButton->setEnabled(false);
    }
  steadyState->setEnabled(true);
  if (scanProblem->processTrajectory())
    trajectory->setChecked(true);
  else
    trajectory->setChecked(false);

  trajectory->setEnabled(true);
  if (scanProblem->processSteadyState())
    steadyState->setChecked(true);
  else
    steadyState->setChecked(false);

  if (((CScanProblem *)scanTask->getProblem())->getListSize() == 0)
    {
      activeObject = ObjectListBox->count() - 1; //because of the empty item
      activeObject --;  // list base start from 1, but list base start from 0;
      while (activeObject >= 0)
        deleteButtonClicked();
      ObjectListBox->clear();
      ObjectListBox->insertItem(trUtf8("click here to add new item"));
    }
}

bool ScanWidget::addNewScanItem(CCopasiObject* pObject)
{
  if (!pObject)
    return false;

  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
  if (((CScanProblem *)scanTask->getProblem())->bExisted(pObject->getCN()))
    return false;

  int widgetOffset;
  int ScanItemWidgetWidth;
  emit hide_me();

  if (selectedList.size() > 0)
    {
      ((ScanItemWidget*)selectedList[1])->setFirstWidget(false);
    }
  //by default isFirstWidget is set as false,
  ScanItemWidget* parameterTable = new ScanItemWidget(this, "parameterTable");
  ScanItemWidgetWidth = scrollview->visibleWidth();

  widgetOffset = nTitleHeight + nSelectedObjects * (parameterTable->minimumSizeHint().height() + nTitleHeight);

  ScanLineEdit* newTitleBar = new ScanLineEdit(this, "newTitleBar");
  newTitleBar->setFixedSize(QSize(ScanItemWidgetWidth, nTitleHeight));
  newTitleBar->setPaletteForegroundColor(QColor(255, 255, 0));
  newTitleBar->setPaletteBackgroundColor(QColor(160, 160, 255));

  newTitleBar->setText(FROM_UTF8(pObject->getCN()));
  newTitleBar->setReadOnly(TRUE);

  scrollview->addChild(newTitleBar, 0, widgetOffset - nTitleHeight);
  selectedList.push_back(newTitleBar);

  parameterTable->setFixedWidth(ScanItemWidgetWidth);
  parameterTable->setFixedHeight(parameterTable->minimumSizeHint().height());

  scrollview->addChild(parameterTable, 0 , widgetOffset);
  scrollview->setVScrollBarMode(QScrollView::Auto);
  scrollview->resizeContents(ScanItemWidgetWidth, widgetOffset + parameterTable->minimumSizeHint().height());
  selectedList.push_back(parameterTable);

  nSelectedObjects++;
  //  if (pObject->isContainer())
  ((CScanProblem *)scanTask->getProblem())->addScanItem(pObject->getCN());
  parameterTable->setScanObject(((CScanProblem *)scanTask->getProblem())->
                                getScanItem(nSelectedObjects - 1));
  parameterTable->setCopasiObject(pObject);
  parameterTable->loadObject();

  ((ScanItemWidget*)selectedList[1])->setFirstWidget(true);

  emit show_me();
  return true;
}

void ScanWidget::ListBoxDoubleClicked(QListBoxItem * item)
{
  if (ObjectListBox->index(item) >= nSelectedObjects)
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

  unsigned C_INT32 i = 1;
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

bool ScanWidget::enter(const std::string & key)
{
  if (!dynamic_cast< CScanTask * >(GlobalKeys.get(key))) return false;

  scanTaskKey = key;

  pSteadyStateWidget->enter(SteadyStateKey);
  pTrajectoryWidget->enter(TrajectoryKey);
  loadScan();

  return true;
}

bool ScanWidget::leave()
{
  //let the user confirm?
  return true;
}

bool ScanWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::MODEL:
      // check if there is a list of Report Defs
      CReportDefinitionVector* pReportDefinitionVector;
      pReportDefinitionVector = dataModel->getReportDefinitionVectorAddr();
      if (pReportDefinitionVector)
        reportDefinitionButton->setEnabled(true);
      break;
    default:
      break;
    }
  return true;
}

void ScanWidget::ReportDefinitionClicked()
{
  CReportDefinitionSelect* pSelectDlg = new CReportDefinitionSelect(pParent);
  CScanTask* scanTask = (CScanTask*)(CCopasiContainer*)GlobalKeys.get(scanTaskKey);
  pSelectDlg->setReport(&(scanTask->getReport()));
  pSelectDlg->loadReportDefinitionVector();
  if (pSelectDlg->exec () == QDialog::Rejected)
    {
      return;
    }
}
/****************************************
 * The implementation of ScanScrollView 
 ****************************************/

ScanScrollView::ScanScrollView(QWidget* parent, const char* name, WFlags fl)
    : QScrollView(parent, name, fl)
{
  pSelectedList = NULL;
  mParent = (CopasiParametersWidget*)parent;
}

void ScanScrollView::contentsMousePressEvent(class QMouseEvent *e)
{
  QScrollView::contentsMousePressEvent(e);
  mParent->viewMousePressEvent(e);
}
void ScanScrollView:: resizeEvent(QResizeEvent * e)
{
  if (e)
    QScrollView::resizeEvent(e);
  if (!pSelectedList)
    return;
  QScrollView::repaintContents(true);
  unsigned i;
  for (i = 0; i < pSelectedList->size(); i++)
    {
      (*pSelectedList)[i]->setFixedWidth(visibleWidth());
    }
}

void ScanScrollView::setSelectedList(std::vector<QWidget*>* pNewSelectedList)
{
  pSelectedList = pNewSelectedList;
}

void ScanScrollView::viewportResizeEvent (QResizeEvent * e)
{
  if (e)
    QScrollView::viewportResizeEvent(e);
  if (!pSelectedList)
    return;
  QScrollView::repaintContents(true);
  unsigned i;
  for (i = 0; i < pSelectedList->size(); i++)
    {
      (*pSelectedList)[i]->setFixedWidth(visibleWidth());
    }
}
