/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CMCAWidget.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: stupe $ 
   $Date: 2005/02/23 03:13:15 $
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

#include "qtUtilities.h"

#include "DataModelGUI.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "CMCAWidget.h"
#include "steadystate/CMCATask.h"
#include "steadystate/CMCAProblem.h"
#include "steadystate/CMCAMethod.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
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

  /*
  taskNameLabel = new QLabel(this, "taskNameLabel");
  taskNameLabel->setText(trUtf8("Task Name"));
  taskNameLabel->setAlignment(int(QLabel::AlignVCenter
                                  | QLabel::AlignRight));
  CMCAWidgetLayout->addWidget(taskNameLabel, 0, 0);

  taskName = new QLineEdit(this, "taskName");
  CMCAWidgetLayout->addWidget(taskName, 0, 1);
  */

  QHBoxLayout* tmpLayout = new QHBoxLayout();

  taskNameLabel = new QLabel(this, "taskNameLabel");
  //taskNameLabel->setText(trUtf8("Task Name"));
  taskNameLabel->setText(trUtf8("<h2>Metabolic<br>Control Analysis</h2>"));
  taskNameLabel->setAlignment(int(QLabel::AlignVCenter
                                  | QLabel::AlignLeft));
  //SteadyStateWidgetLayout->addWidget(taskNameLabel, 0, 0);
  tmpLayout->addWidget(taskNameLabel);

  QSpacerItem* tmpSpacer = new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::Minimum);
  tmpLayout->addItem(tmpSpacer);

  bExecutable = new QCheckBox(this, "bExecutable");
  bExecutable->setText(trUtf8("Task Executable"));
  // this is the child widget to edit an steadystatetask
  bExecutable->setChecked(parent == NULL);
  bExecutable->setEnabled(parent != NULL);
  //SteadyStateWidgetLayout->addWidget(bExecutable, 0, 2);
  tmpLayout->addWidget(bExecutable);

  CMCAWidgetLayout->addMultiCellLayout(tmpLayout, 0, 0, 1, 2);

  QSpacerItem* spacer2 = new QSpacerItem(0, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);
  CMCAWidgetLayout->addItem(spacer2, 1, 1);

  //********************

  taskSteadyState = new QCheckBox(this, "taskSteadyState");
  taskSteadyState->setText(trUtf8("perform Steady State Analysis"));
  taskSteadyState->setChecked(true);
  CMCAWidgetLayout->addWidget(taskSteadyState, 2, 1);

  line8_2 = new QFrame(this, "line8_2");
  line8_2->setFrameShape(QFrame::HLine);
  CMCAWidgetLayout->addMultiCellWidget(line8_2, 3, 3, 0, 2);

  //********** paramters table ******************
  parameterValueLabel = new QLabel(this, "parameterValueLabel");
  parameterValueLabel->setText(trUtf8("Method parameters"));
  parameterValueLabel->setAlignment(int(QLabel::AlignVCenter
                                        | QLabel::AlignRight));
  CMCAWidgetLayout->addWidget(parameterValueLabel, 4, 0);

  QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CMCAWidgetLayout->addItem(spacer, 5, 0);

  parameterTable = new QTable(this, "parameterTable");
  parameterTable->setNumRows(0);
  parameterTable->setNumCols(1);
  QHeader *colHeader = parameterTable->horizontalHeader();
  colHeader->setLabel(0, tr("Value"));
  parameterTable->setColumnStretchable(0, true);
  parameterTable->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  CMCAWidgetLayout->addMultiCellWidget(parameterTable, 4, 5, 1, 2);

  QSpacerItem* spacer_3 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CMCAWidgetLayout->addMultiCell(spacer_3, 6, 6, 0, 2);

  //********* line ********************
  line6 = new QFrame(this, "line6");
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  CMCAWidgetLayout->addMultiCellWidget(line6, 7, 7, 0, 2);

  //********* buttons *****************
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
  /*
  reportDefinitionButton = new QPushButton(this, "ReportDefinition");
  reportDefinitionButton->setText(trUtf8("ReportDefinition"));
  Layout2->addWidget(reportDefinitionButton);
  */
  CMCAWidgetLayout->addMultiCellLayout(Layout2, 8, 8, 0, 2);

  // signals and slots connections
  connect(bRunButton, SIGNAL(clicked()), this, SLOT(runMCATask()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelButtonClicked()));
  connect(parameterTable, SIGNAL(valueChanged(int, int)), this, SLOT(parameterValueChanged()));
  //connect(reportDefinitionButton, SIGNAL(clicked()), this, SLOT(ReportDefinitionClicked()));
  connect(taskSteadyState, SIGNAL(toggled(bool)), this, SLOT(taskSteadyStateToggled()));

  // tab order
  //setTabOrder(taskName, taskSteadyState);
  setTabOrder(taskSteadyState, parameterTable);
  setTabOrder(parameterTable, bRunButton);
  setTabOrder(bRunButton, cancelChange);

  //reportDefinitionButton->setEnabled(false);
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

void CMCAWidget::parameterValueChanged()
{
  qWarning("CMCAWidget::parameterValueChanged(): Not implemented yet!");
}

void CMCAWidget::runMCATask()
{
  saveMCATask();
  if (CCopasiDataModel::Global->isChanged())
    {
      const QApplication* qApp = dataModel->getQApp();
      if (qApp)
        {
          CopasiUI3Window* mainWidget = dynamic_cast<CopasiUI3Window*>(qApp->mainWidget());
          if (mainWidget)
            {
              if (!CCopasiDataModel::Global->autoSave())
                {
                  QMessageBox::question(mainWidget, "Temporary File Save Failed", "Unable to create temporary file .\nThis will not affect the running application but in case if\nthe application crashes with some unsaved changes those changes \nwill be lost.");
                  if (QMessageBox::question(mainWidget, "Please save the changes !!!", "Your model contains unsaved changes.\nDo you want to save those changes?", QMessageBox::Yes | QMessageBox::Default, QMessageBox::No | QMessageBox::Escape) == QMessageBox::Yes)
                    {
                      mainWidget->saveFile();
                    }
                }
            }
        }
    }
  if (bRunButton->text() != "Run")
    {
      hide();
      return;
    }

  CMCATask* mcaTask =
    dynamic_cast<CMCATask *>(GlobalKeys.get(objKey));
  assert(mcaTask);

  mcaTask->initialize();
  CMCAProblem* mcaProblem =
    dynamic_cast<CMCAProblem *>(mcaTask->getProblem());
  assert(mcaProblem);

  // if a steady state analysis is needed, run it first
  // if a steady state was found, set the flag in the mca task
  // set the resolution of the mca task
  if (mcaProblem->isSteadyStateRequested())
    {
      CSteadyStateTask* steadyStateTask =
        dynamic_cast<CSteadyStateTask *>((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);
      assert(steadyStateTask);

      dynamic_cast<CSteadyStateProblem*>(steadyStateTask->getProblem())->setInitialState(CCopasiDataModel::Global->getModel()->getInitialState());

      steadyStateTask->initialize();

      setCursor(Qt::WaitCursor);
      CProgressBar* tmpBar = new CProgressBar(dataModel);
      steadyStateTask->setProgressHandler(tmpBar);

      try
        {
          steadyStateTask->process();
        }

      catch (CCopasiException Exception)
        {
          QMessageBox mb("Copasi",
                         "Could not find a Steady State",
                         QMessageBox::NoIcon,
                         QMessageBox::Ok | QMessageBox::Escape,
                         QMessageBox::NoButton,
                         QMessageBox::NoButton);
          mb.exec();
        }

      tmpBar->finish(); pdelete(tmpBar);

      protectedNotify(ListViews::STATE, ListViews::CHANGE, CCopasiDataModel::Global->getModel()->getKey());

      unsetCursor();
      dynamic_cast<CMCAMethod*>(mcaTask->getMethod())->setSteadyStateStatus(steadyStateTask->getResult());
    }

  setCursor(Qt::WaitCursor);
  //CProgressBar* tmpBar = new CProgressBar(dataModel);
  //mMCATask->setProgressHandler(tmpBar);

  try
    {
      mcaTask->process();
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

  //tmpBar->finish(); pdelete(tmpBar);

  protectedNotify(ListViews::STATE, ListViews::CHANGE, CCopasiDataModel::Global->getModel()->getKey());

  unsetCursor();

  pListView->switchToOtherWidget(241, ""); //change to the results window
}

void CMCAWidget::loadMCATask()
{
  CMCATask* mcaTask =
    dynamic_cast<CMCATask *>(GlobalKeys.get(objKey));
  assert(mcaTask);

  CMCAProblem* mcaProblem =
    dynamic_cast<CMCAProblem *>(mcaTask->getProblem());
  assert(mcaProblem);

  CMCAMethod* mcaMethod =
    dynamic_cast<CMCAMethod *>(mcaTask->getMethod());
  assert(mcaMethod);

  //  taskName->setText(tr("Metabolic Control Analysis"));
  //  taskName->setEnabled(false);

  taskSteadyState->setChecked(mcaProblem->isSteadyStateRequested());
  this->initParameterTable();
}

void CMCAWidget::saveMCATask()
{
  CMCATask* mcaTask =
    dynamic_cast<CMCATask *>(GlobalKeys.get(objKey));
  assert(mcaTask);

  CMCAProblem* mcaProblem =
    dynamic_cast<CMCAProblem *>(mcaTask->getProblem());
  assert(mcaProblem);

  CMCAMethod* mcaMethod =
    dynamic_cast<CMCAMethod *>(mcaTask->getMethod());
  assert(mcaMethod);

  bool isSteadyStateRequested = taskSteadyState->isChecked();
  mcaProblem->setSteadyStateRequested(isSteadyStateRequested);

  unsigned int numMCAParameters = mcaMethod->size();
  unsigned int numSteadyStateParameters = 0;
  QString value;

  unsigned int k;

  CSteadyStateTask * pSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);
  assert(pSteadyStateTask);

  numSteadyStateParameters = pSteadyStateTask->getMethod()->size();

  if (this->taskSteadyState->isChecked())
    {
      for (k = 0; k < numMCAParameters; k++)
        {
          value = parameterTable->text(k, 0);
          setParameterValue(mcaMethod, k, value);
        }
      if (pSteadyStateTask && pSteadyStateTask->getMethod())
        {
          CSteadyStateMethod* sMethod = dynamic_cast<CSteadyStateMethod*>(pSteadyStateTask->getMethod());
          for (k = 0; k < numSteadyStateParameters; k++)
            {
              value = parameterTable->text(k + numMCAParameters, 0);
              setParameterValue(sMethod, k, value);
            }
        }
    }
  else
    {
      for (k = 0; k < numMCAParameters; k++)
        {
          value = parameterTable->text(k, 0);
          setParameterValue(mcaMethod, k, value);
        }
    }
}

bool CMCAWidget::enter(const std::string & key)
{
  if (!dynamic_cast<CMCATask *>(GlobalKeys.get(key))) return false;

  objKey = key;

  loadMCATask();;

  if (CCopasiDataModel::Global->getModel()->getTotSteps() == 0)
    {
      this->bRunButton->setEnabled(false);
    }
  else
    {
      this->bRunButton->setEnabled(true);
    }

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
      pReportDefinitionVector = CCopasiDataModel::Global->getReportDefinitionList();
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
  saveMCATask();
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
  // update should only be done when the user commits or leaves the widget
  /*
  CMCATask* mcaTask =
   dynamic_cast<CMCATask *>(GlobalKeys.get(objKey));
  assert(mcaTask);
  CMCAProblem* mcaProblem=dynamic_cast<CMCAProblem*>(mcaTask->getProblem()); 
  assert(mcaProblem); 
  mcaProblem->setSteadyStateRequested(taskSteadyState->isChecked());  
  */
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

  CSteadyStateTask * pSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);
  assert(pSteadyStateTask);

  numSteadyStateParameters = pSteadyStateTask->getMethod()->size();

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
      if (pSteadyStateTask && pSteadyStateTask->getMethod())
        {
          CSteadyStateMethod* sMethod = dynamic_cast<CSteadyStateMethod*>(pSteadyStateTask->getMethod());
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
