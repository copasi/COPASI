/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CMCAWidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/25 13:23:24 $
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

#include "CMCAWidget.h"
#include "steadystate/CMCATask.h"
#include "steadystate/CMCAProblem.h"
#include "steadystate/CMCAMethod.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateMethod.h"
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
 *  Constructs a CMCAWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
CMCAWidget::CMCAWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    pParent(parent)
{
  if (!name)
    setName("CMCAWidget");
  setCaption(trUtf8("CMCAWidget"));
  CMCAWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "CMCAWidgetLayout");

  taskNameLabel = new QLabel(this, "taskNameLabel");
  taskNameLabel->setText(trUtf8("Task Name"));

  CMCAWidgetLayout->addWidget(taskNameLabel, 0, 0);
  QSpacerItem* spacer = new QSpacerItem(91, 400, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CMCAWidgetLayout->addItem(spacer, 5, 0);

  parameterValueLabel = new QLabel(this, "parameterValueLabel");
  parameterValueLabel->setText(trUtf8("Parameter value"));
  CMCAWidgetLayout->addWidget(parameterValueLabel, 4, 0);

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

  CMCAWidgetLayout->addMultiCellLayout(Layout2, 7, 7, 0, 2);

  line6 = new QFrame(this, "line6");
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  CMCAWidgetLayout->addMultiCellWidget(line6, 6, 6, 0, 2);

  taskName = new QLineEdit(this, "taskName");
  CMCAWidgetLayout->addWidget(taskName, 0, 1);

  parameterTable = new QTable(this, "parameterTable");
  parameterTable->setNumRows(0);
  parameterTable->setNumCols(1);
  QHeader *colHeader = parameterTable->horizontalHeader();
  colHeader->setLabel(0, tr("Value"));
  CMCAWidgetLayout->addMultiCellWidget(parameterTable, 4, 5, 1, 2);

  taskSteadyState = new QCheckBox(this, "taskSteadyState");
  taskSteadyState->setText(trUtf8("perform Steady State Analysis"));
  taskSteadyState->setChecked(true);
  CMCAWidgetLayout->addWidget(taskSteadyState, 2, 1);

  line8_2 = new QFrame(this, "line8_2");
  line8_2->setFrameShape(QFrame::HLine);

  CMCAWidgetLayout->addMultiCellWidget(line8_2, 3, 3, 0, 2);

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
CMCAWidget::~CMCAWidget()
{}

void CMCAWidget::CancelButtonClicked()
{
  loadMCATask();
}

void CMCAWidget::CommitButtonClicked()
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

void CMCAWidget::parameterValueChanged()
{
  qWarning("CMCAWidget::parameterValueChanged(): Not implemented yet!");
}

void CMCAWidget::runMCATask()
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

void CMCAWidget::loadMCATask()
{
  CMCATask* mMCATask =
    dynamic_cast<CMCATask *>(GlobalKeys.get(objKey));
  assert(mMCATask);

  CMCAProblem* mcaproblem =
    dynamic_cast<CMCAProblem *>(mMCATask->getProblem());
  assert(mcaproblem);

  CMCAMethod* mcamethod =
    dynamic_cast<CMCAMethod *>(mMCATask->getMethod());
  assert(mcamethod);

  taskName->setText(tr("Metabolic Control Analysis"));
  taskName->setEnabled(false);

  //bool bSteadyState = mcaproblem->isSteadyStateRequested();
  this->initParameterTable();
}

bool CMCAWidget::enter(const std::string & key)
{
  if (!dynamic_cast<CMCATask *>(GlobalKeys.get(key))) return false;

  objKey = key;

  loadMCATask();;

  return true;
}

bool CMCAWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action),
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

bool CMCAWidget::leave()
{
  //let the user confirm?
  return true;
}

void CMCAWidget::ReportDefinitionClicked()
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

void CMCAWidget::taskSteadyStateToggled()
{
  if (!taskSteadyState->isChecked())
  {}
  else
  {}
  this->initParameterTable();
}

void CMCAWidget::initParameterTable()
{
  int i, j;
  for (i = 0; i < this->parameterTable->numCols();++i)
    {
      for (j = 0; j < this->parameterTable->numRows();++j)
        {
          this->parameterTable->clearCell(j, i);
        }
    }
  CMCATask* mMCATask =
    dynamic_cast<CMCATask *>(GlobalKeys.get(objKey));
  assert(mMCATask);

  CMCAMethod* mcamethod =
    dynamic_cast<CMCAMethod *>(mMCATask->getMethod());
  assert(mcamethod);

  unsigned int numMCAParameters = mcamethod->size();
  unsigned int numSteadyStateParameters = 0;
  QTableItem* pItem;
  QString value;
  QString strname;

  QHeader *rowHeader = parameterTable->verticalHeader();

  unsigned int k;
  if (this->dataModel->getSteadyStateTask())
    {
      numSteadyStateParameters = this->dataModel->getSteadyStateTask()->getMethod()->size();
    }
  if (this->taskSteadyState->isChecked())
    {
      parameterTable->setNumRows(numMCAParameters + numSteadyStateParameters);
      CCopasiParameter::Type Type;
      for (k = 0; k < numMCAParameters; k++)
        {
          strname = FROM_UTF8(mcamethod->getName(k));
          rowHeader->setLabel(k, tr(strname));

          value = getParameterValue(mcamethod, k, &Type);
          pItem = new QTableItem (parameterTable, QTableItem::Always, value);
          parameterTable->setItem(k, 0, pItem);
        }
      if (this->dataModel->getSteadyStateTask() && this->dataModel->getSteadyStateTask()->getMethod())
        {
          CSteadyStateMethod* sMethod = dynamic_cast<CSteadyStateMethod*>(this->dataModel->getSteadyStateTask()->getMethod());
          for (k = 0; k < numSteadyStateParameters; k++)
            {
              strname = FROM_UTF8(sMethod->getName(k));
              rowHeader->setLabel(k + numMCAParameters, tr(strname));

              value = getParameterValue(sMethod, k, &Type);
              pItem = new QTableItem (parameterTable, QTableItem::Always, value);
              parameterTable->setItem(k + numMCAParameters, 0, pItem);
            }
        }
    }
  else
    {
      parameterTable->setNumRows(numMCAParameters);
      CCopasiParameter::Type Type;
      for (k = 0; k < numMCAParameters; k++)
        {
          strname = FROM_UTF8(mcamethod->getName(k));
          rowHeader->setLabel(k, tr(strname));

          value = getParameterValue(mcamethod, k, &Type);
          pItem = new QTableItem (parameterTable, QTableItem::Always, value);
          parameterTable->setItem(k, 0, pItem);
        }
    }
}
