/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TSSWidget.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/06 15:14:24 $
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

  //setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));
  //setMinimumSize(QSize(0, 0));
  TSSWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "TSSWidgetLayout");

  mpHeaderWidget->setTaskName("Time Scale Separation");
  TSSWidgetLayout->addWidget(mpHeaderWidget, 0, 1);

  addHLineToGridLayout(TSSWidgetLayout, 1, 1);

  //mpGridLayout = new QGridLayout(0, 1, 1, 0, 6, "mpGridLayout");

  mpTblParameter = new QTable(this, "mpTblParameter");
  mpTblParameter->setNumCols(mpTblParameter->numCols() + 1);
  mpTblParameter->horizontalHeader()->setLabel(mpTblParameter->numCols() - 1, tr("Value"));
  mpTblParameter->setNumRows(mpTblParameter->numRows() + 1);

  mpTblParameter->verticalHeader()->setLabel(mpTblParameter->numRows() - 1, tr("Name"));
  mpTblParameter->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0,
                                mpTblParameter->sizePolicy().hasHeightForWidth()));

  mpTblParameter->setMinimumSize(QSize(0, 110));
  mpTblParameter->setNumRows(1);
  mpTblParameter->setNumCols(1);

  addMethodParameterTableToGridLayout(mpTblParameter, TSSWidgetLayout, 2, 1);

  QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  TSSWidgetLayout->addMultiCell(spacer, 4, 4, 0, 1);

  //TSSWidgetLayout->addWidget(mpTblParameter, 1, 1);

  //mpLblParameter = new QLabel(this, "mpLblParameter");
  //mpLblParameter->setText("Method parameters");
  //mpLblParameter->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
  //mpLblParameter->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, //mpLblParameter->sizePolicy().hasHeightForWidth()));
  //mpLblParameter->setMinimumSize(QSize(0, 0));
  //mpLblParameter->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  //TSSWidgetLayout->addWidget(mpLblParameter, 1, 0);
  //TSSWidgetLayout->addLayout(mpGridLayout);

  TSSWidgetLayout->addMultiCellWidget(mpBtnWidget, 5, 5, 0, 1);
}

/*
 *  Destroys the object and frees any allocated resources
 */
TSSWidget::~TSSWidget()
{}

bool TSSWidget::saveTask()
{
  saveExecutable();
  saveMethodParameters(mpTblParameter);

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
  CCopasiDataModel::Global->changed();
  return true;
}

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
  loadExecutable();
  loadMethodParameters(mpTblParameter);

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

  return true;
}
