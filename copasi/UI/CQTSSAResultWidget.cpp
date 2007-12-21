// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTSSAResultWidget.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: isurovts $
//   $Date: 2007/12/21 11:44:52 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include <qpushbutton.h>
#include <qlayout.h>
#include "copasi.h"

#include "CQTSSAResultWidget.h"
#include "CQTSSAResultSubWidget.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiVector.h"
#include "tssanalysis/CTSSATask.h"
#include "CTimeSeriesTable.h"

//#include "report/CKeyFactory.h"
#include "qtUtilities.h"
#include "tssanalysis/CTSSAMethod.h"

#include "tssanalysis/CTSSATask.h"

CTSSATask* pTask;
CTSSAMethod* pTSSILDM;

/*
 *  Constructs a CQTSSAResultWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQTSSAResultWidget::CQTSSAResultWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    objKey("")
{
  if (!name)
    setName("CQTSSAResultWidget");
  setCaption(trUtf8("CQTSSAResultWidget"));

  mWidgetLayout = new QGridLayout(this, 1, 1, 0, -1, "Layout");

  mCentralWidget = new CQTSSAResultSubWidget(this, "CQTSSAResultSubWidget");
  mWidgetLayout->addWidget(mCentralWidget, 0, 0);

  /*commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit"));
  Layout5->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Revert"));
  Layout5->addWidget(cancelChanges);*/

  // signals and slots connections
  //connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  //connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTSSAResultWidget::~CQTSSAResultWidget()
{}

bool CQTSSAResultWidget::loadFromBackend()
{
  mCentralWidget->displayOptimizationTab(false);
  mCentralWidget->table()->setTimeSeries(dynamic_cast<CTSSATask *>((*CCopasiDataModel::Global->getTaskList())["Time Scale Separation Analysis"])->getTimeSeries());
  return true;
}

bool CQTSSAResultWidget::saveToBackend()
{
  return true;
}

/*void CQTSSAResultWidget::slotBtnCancelClicked()
{
  enter(objKey); // reload
}*/

/*void CQTSSAResultWidget::slotBtnOKClicked()
{
  saveToCompartment();
}*/

bool CQTSSAResultWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (this->isShown())
    return loadFromBackend();
  else
    return true;
}

bool CQTSSAResultWidget::leave()
{
  //return saveToCompartment();
  return true;
}

bool CQTSSAResultWidget::enter(const std::string & C_UNUSED(key))
{
  pTask =
    dynamic_cast<CTSSATask *>((*CCopasiDataModel::Global->getTaskList())["Time Scale Separation Analysis"]);
  pTSSILDM = dynamic_cast<CTSSAMethod*>(pTask->getMethod());

  if (!pTSSILDM->mCurrentStep)
    {
      mCentralWidget->setStepSelectionDisabled(true);
      mCentralWidget->discardOldResults();
    }
  else
    mCentralWidget->setStepSelectionDisabled(false);

  return loadFromBackend();
  /*objKey = key;
  CCompartment* comp = dynamic_cast< CCompartment * >(GlobalKeys.get(key));

  if (comp) return loadFromCompartment(comp);
  else return false;*/
}
