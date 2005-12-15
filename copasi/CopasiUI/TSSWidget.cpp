/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/TSSWidget.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/12/15 17:00:49 $
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

#include "TSSWidget.h"
#include "DataModelGUI.h"
#include "qtUtilities.h"
#include "listviews.h"
#include "CProgressBar.h"
#include "copasiui3window.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "tss/CTSSTask.h"
#include "tss/CTSSProblem.h"
#include "model/CModel.h"
#include "utilities/CCopasiException.h"
#include "report/CKeyFactory.h"

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

  //if a mpMethodLayout is created here, it will be used by addMethodXXX() below.
  mpMethodLayout = new QGridLayout(this, 1, 1, 11, 6, "mpMethodLayout");

  //TSSWidgetLayout->insertWidget(0, mpHeaderWidget);

  mpHeaderWidget->setTaskName("Time Scale Separation");
  addHeaderToGrid();
  addHLineToGrid(mpMethodLayout, 1, 2);

  addMethodSelectionBox(CTSSTask::ValidMethods);
  addMethodParameterTable();

  //QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  //mpMethodLayout->addMultiCell(spacer, 10, 10, 0, 1);

  mpMethodLayout->addMultiCellWidget(mpBtnWidget, 11, 11, 0, 2);
}

/*
 *  Destroys the object and frees any allocated resources
 */
TSSWidget::~TSSWidget()
{}

bool TSSWidget::saveTask()
{
  saveCommon();
  saveMethod();

  CTSSTask* tssTask =
    dynamic_cast<CTSSTask *>(GlobalKeys.get(mObjectKey));
  assert(tssTask);

  CTSSProblem* problem =
    dynamic_cast<CTSSProblem *>(tssTask->getProblem());
  assert(problem);

  CTSSMethod* method =
    dynamic_cast<CTSSMethod *>(tssTask->getMethod());
  assert(method);

  //...

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  if (mChanged) CCopasiDataModel::Global->changed();
  return true;
}

CCopasiMethod * TSSWidget::createMethod(const CCopasiMethod::SubType & type)
{return CTSSMethod::createTSSMethod(type);}

bool TSSWidget::runTask()
{
  if (!commonBeforeRunTask()) return false;

  /*
  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(GlobalKeys.get(mObjectKey));
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
  loadCommon();
  loadMethod();

  CTSSTask* tssTask =
    dynamic_cast<CTSSTask *>(GlobalKeys.get(mObjectKey));
  assert(tssTask);

  CTSSProblem* problem =
    dynamic_cast<CTSSProblem *>(tssTask->getProblem());
  assert(problem);

  CTSSMethod* method =
    dynamic_cast<CTSSMethod *>(tssTask->getMethod());
  assert(method);

  //...

  mChanged = false;

  return true;
}
