/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TSSWidget.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/05 13:41:09 $
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
#include "CopasiDataModel/CCopasiDataModel.h"
#include "qtUtilities.h"

#include "TSSWidget.h"
#include "tss/CTSSTask.h"
#include "tss/CTSSProblem.h"
#include "model/CModel.h"
#include "listviews.h"
#include "utilities/CCopasiException.h"
#include "report/CKeyFactory.h"
#include "CProgressBar.h"
#include "copasiui3window.h"
#include "qmessagebox.h"

/**
 *  Constructs a TSSWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
TSSWidget::TSSWidget(QWidget* parent, const char* name, WFlags fl)
    : TaskWidget(parent, name, fl)
{
  if (!name)
    setName("TSSWidget");
  setCaption(trUtf8("TSSWidget"));

  //********** name ********************
  taskNameLabel->setText(trUtf8("<h2>Time scale separation</h2>"));
  //taskNameLabel->setAlignment(int(QLabel::AlignVCenter
  //                                | QLabel::AlignRight));
  TaskWidgetLayout->addMultiCellLayout(nameLayout, 0, 0, 1, 2);

  tmpLine = new QFrame(this, "line");
  tmpLine->setFrameShape(QFrame::HLine);
  //line8_2->setFrameShadow(QFrame::Sunken);
  TaskWidgetLayout->addMultiCellWidget(tmpLine, 1, 1, 0, 2);

  addMethodParameterTableToLayout(2, 2);

  // signals and slots connections
  //connect(taskJacobian, SIGNAL(toggled(bool)), this, SLOT(taskJacobianToggled()));

  // tab order
  //setTabOrder(ExportFileButton, reportDefinitionButton);
}

/*
 *  Destroys the object and frees any allocated resources
 */
TSSWidget::~TSSWidget()
{}

bool TSSWidget::saveTask()
{
  saveExecutable();
  saveMethodParameters();

  CTSSTask* tssTask =
    dynamic_cast<CTSSTask *>(GlobalKeys.get(objKey));
  assert(tssTask);

  CTSSProblem* problem =
    dynamic_cast<CTSSProblem *>(tssTask->getProblem());
  assert(problem);

  CTSSMethod* method =
    dynamic_cast<CTSSMethod *>(tssTask->getMethod());
  assert(method);

  //...

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  CCopasiDataModel::Global->changed();
  return true;
}

bool TSSWidget::runTask()
{
  if (!commonBeforeRunTask()) return false;

  /*
  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(GlobalKeys.get(objKey));
  assert(mSteadyStateTask);

  mSteadyStateTask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL);

  try
    {
      if (!mSteadyStateTask->process(true))
        {
          mProgressBar->finish();
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
            {
              mProgressBar->finish();
              QMessageBox::warning(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(), QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
              CCopasiMessage::clearDeque();
            }
        }
      else if (setInitialState->isChecked())
        {
          const CState *currentState = mSteadyStateTask->getState();
          if (currentState)
            (CCopasiDataModel::Global->getModel())->setInitialState(currentState);
        }
    }

  catch (CCopasiException Exception)
    {
      mProgressBar->finish();
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          mProgressBar->finish();
          QMessageBox::warning(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(), QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }
    }

  mSteadyStateTask->restore();
  */

  commonAfterRunTask();

  //pListView->switchToOtherWidget(211, ""); //change to the results window

  return true;
}

bool TSSWidget::loadTask()
{
  loadExecutable();
  loadMethodParameters();

  CTSSTask* tssTask =
    dynamic_cast<CTSSTask *>(GlobalKeys.get(objKey));
  assert(tssTask);

  CTSSProblem* problem =
    dynamic_cast<CTSSProblem *>(tssTask->getProblem());
  assert(problem);

  CTSSMethod* method =
    dynamic_cast<CTSSMethod *>(tssTask->getMethod());
  assert(method);

  //...

  return true;
}
