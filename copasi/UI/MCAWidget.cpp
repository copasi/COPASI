/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MCAWidget.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/21 15:09:02 $
   End CVS Header */

#include <qfiledialog.h>

#include <qvariant.h>
#include <qcheckbox.h>
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

#include "DataModelGUI.h"
#include "qtUtilities.h"

#include "MCAWidget.h" 
//#include "steadystate/CMCATask.h"
//#include "steadystate/CMca.h"
#include "model/CModel.h"
#include "listviews.h"
#include "utilities/CCopasiException.h"
#include "report/CKeyFactory.h"
#include "report/CReportDefinitionVector.h"
#include "report/CReport.h"
#include "report/CReportDefinition.h"
#include "CReportDefinitionSelect.h"
#include "CProgressBar.h"
#include "copasiui3window.h"
#include "qmessagebox.h"
#include "qapplication.h"

/**
 *  Constructs a MCAWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
MCAWidget::MCAWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    pParent(parent)
{
  if (!name)
    setName("MCAWidget");
  setCaption(trUtf8("MCAWidget"));
  MCAWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "MCAWidgetLayout");

  taskNameLabel = new QLabel(this, "taskNameLabel");
  taskNameLabel->setText(trUtf8("Task Name"));

  MCAWidgetLayout->addWidget(taskNameLabel, 0, 0);
  QSpacerItem* spacer = new QSpacerItem(91, 400, QSizePolicy::Minimum, QSizePolicy::Expanding);
  MCAWidgetLayout->addItem(spacer, 5, 0);

  parameterValueLabel = new QLabel(this, "parameterValueLabel");
  parameterValueLabel->setText(trUtf8("Parameter value"));
  MCAWidgetLayout->addWidget(parameterValueLabel, 4, 0);

  Layout2 = new QHBoxLayout(0, 0, 6, "Layout2");

  bRunButton = new QPushButton(this, "bRunButton");
  if (parent == NULL)
    bRunButton->setText(trUtf8("OK"));
  else
    bRunButton->setText(trUtf8("Run"));
  bRunButton->setEnabled(true /*(parent == NULL)*/);
  Layout2->addWidget(bRunButton);

  cancelChange = new QPushButton(this, "cancelChange");
  cancelChange->setText(trUtf8("Revert"));
  Layout2->addWidget(cancelChange);

  reportDefinitionButton = new QPushButton(this, "ReportDefinition");
  reportDefinitionButton->setText(trUtf8("ReportDefinition"));
  Layout2->addWidget(reportDefinitionButton);

  MCAWidgetLayout->addMultiCellLayout(Layout2, 7, 7, 0, 2);

  line6 = new QFrame(this, "line6");
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  MCAWidgetLayout->addMultiCellWidget(line6, 6, 6, 0, 2);

  taskName = new QLineEdit(this, "taskName");
  MCAWidgetLayout->addWidget(taskName, 0, 1);

  parameterTable = new QTable(this, "parameterTable");
  parameterTable->setNumRows(0);
  parameterTable->setNumCols(1);
  QHeader *colHeader = parameterTable->horizontalHeader();
  colHeader->setLabel(0, tr("Value"));
  MCAWidgetLayout->addMultiCellWidget(parameterTable, 4, 5, 1, 2);

  taskSteadyState = new QCheckBox(this, "taskSteadyState");
  taskSteadyState->setText(trUtf8("perform Steady State Analysis"));
  MCAWidgetLayout->addWidget(taskSteadyState, 2, 2);

  line8_2 = new QFrame(this, "line8_2");
  line8_2->setFrameShape(QFrame::HLine);

  MCAWidgetLayout->addMultiCellWidget(line8_2, 3, 3, 0, 2);

  // signals and slots connections
  connect(bRunButton, SIGNAL(clicked()), this, SLOT(runMCATask()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelButtonClicked()));
  connect(parameterTable, SIGNAL(valueChanged(int, int)), this, SLOT(parameterValueChanged()));
  connect(reportDefinitionButton, SIGNAL(clicked()), this, SLOT(ReportDefinitionClicked()));
  connect(taskSteadyState, SIGNAL(toggled(bool)), this, SLOT(taskSteadyStateToggled()));

  // tab order
  setTabOrder(taskName, taskSteadyState);
  setTabOrder(taskSteadyState, parameterTable);
  setTabOrder(parameterTable, bRunButton);
  setTabOrder(bRunButton, cancelChange);

  reportDefinitionButton->setEnabled(false);
}

/*
 *  Destroys the object and frees any allocated resources
 */
MCAWidget::~MCAWidget()
{}

void MCAWidget::CancelButtonClicked()
{
  loadMCATask();
}

void MCAWidget::CommitButtonClicked()
{
  /*
  CMCATask* mMCATask =
  dynamic_cast<CMCATask *>(GlobalKeys.get(objKey));
  assert(mMCATask);

  CMcaProblem* mcaproblem =
  dynamic_cast<CMCAProblem *>(mMCATask->getProblem());
  assert(mcaproblem);

  CMca* mcamethod =
  dynamic_cast<CMca *>(mMCATask->getMethod());
  assert(mcamethod);

  loadMCATask();
  */
}

void MCAWidget::parameterValueChanged()
{
  qWarning("MCAWidget::parameterValueChanged(): Not implemented yet!");
}

void MCAWidget::runMCATask()
{
  if (dataModel->isChanged())
    {
      const QApplication* qApp = dataModel->getQApp();
      if (qApp)
        {
          CopasiUI3Window* mainWidget = dynamic_cast<CopasiUI3Window*>(qApp->mainWidget());
          if (mainWidget)
            {
              if (QMessageBox::question(mainWidget, "Model Changed", "Your model contains unsaved changes.\nDo you want to save those changes?", QMessageBox::Yes | QMessageBox::Default, QMessageBox::No | QMessageBox::Escape) == QMessageBox::Yes)
                {
                  mainWidget->saveFile();
                }
            }
        }
    }
  CommitButtonClicked();

  if (bRunButton->text() != "Run")
    {
      hide();
      return;
    }
  /*
    CMCATask* mMCATask =
      dynamic_cast<CMCATask *>(GlobalKeys.get(objKey));
    assert(mMCATask);
   
    mMCATask->initialize();
   
    setCursor(Qt::WaitCursor);
    CProgressBar* tmpBar = new CProgressBar(dataModel);
    mMCATask->setProgressHandler(tmpBar);
   
    try
      {
        mMCATask->process();
      }
   
    catch (CCopasiException Exception)
      {
        QMessageBox mb("Copasi",
                       "Could not finish metabolic control analysis.",
                       QMessageBox::NoIcon,
                       QMessageBox::Ok | QMessageBox::Escape,
                       QMessageBox::NoButton,
                       QMessageBox::NoButton);
        mb.exec();
      }
   
    tmpBar->finish(); pdelete(tmpBar);
   
    protectedNotify(ListViews::STATE, ListViews::CHANGE, dataModel->getModel()->getKey());
   
    unsetCursor();
   
    //pListView->switchToOtherWidget(211, ""); //change to the results window
    */
}

void MCAWidget::loadMCATask()
{
  /*
  CMCATask* mMCATask =
  dynamic_cast<CMCATask *>(GlobalKeys.get(objKey));
  assert(mMCATask);

  CMCAProblem* mcaproblem =
  dynamic_cast<CMCAProblem *>(mMCATask->getProblem());
  assert(mcaproblem);

  CMca* mcamethod =
  dynamic_cast<CMCA *>(mMCATask->getMethod());
  assert(mcamethod);

  taskName->setText(tr("Metabolic Control Analysis"));
  taskName->setEnabled(false);

  bool bSteadyState = mcaproblem->isSteadyStateRequested();

  QTableItem * pItem;
  QString value;
  QString strname;

  parameterTable->setNumRows(steadystatemethod->size());
  QHeader *rowHeader = parameterTable->verticalHeader();

  unsigned C_INT32 i;
  CCopasiParameter::Type Type;
  for (i = 0; i < mcamethod->size(); i++)
  {
    strname = FROM_UTF8(mcamethod->getName(i));
    rowHeader->setLabel(i, tr(strname));

    value = getParameterValue(mcamethod, i, &Type);
    pItem = new QTableItem (parameterTable, QTableItem::Always, value);
    parameterTable->setItem(i, 0, pItem);
  }
  */
}

bool MCAWidget::enter(const std::string & key)
{
  /*
  if (!dynamic_cast<MCATask *>(GlobalKeys.get(key))) return false;

  objKey = key;

  loadMCATask();;

  return true;
  */
}

bool MCAWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action),
                       const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::FUNCTION:
      break;
    case ListViews::MODEL:
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

bool MCAWidget::leave()
{
  //let the user confirm?
  return true;
}

void MCAWidget::ReportDefinitionClicked()
{
  /*
  CMCATask* mcaTask =
    dynamic_cast< CMCATask * >(GlobalKeys.get(objKey));
  assert(mcaTask);

  CReportDefinitionSelect * pSelectDlg = new CReportDefinitionSelect(pParent);
  pSelectDlg->setReport(&mcaTask->getReport());
  pSelectDlg->loadReportDefinitionVector();
  pSelectDlg->exec();

  delete pSelectDlg;
  */
}

void MCAWidget::taskSteadyStateToggled()
{
  if (!taskSteadyState->isChecked())
  {}
  else
    {}}
