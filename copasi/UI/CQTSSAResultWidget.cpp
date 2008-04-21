// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTSSAResultWidget.cpp,v $
//   $Revision: 1.3.4.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/27 19:02:09 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include "tssanalysis/CILDMMethod.h"
#include "tssanalysis/CTSSATask.h"

CTSSATask* pTask;
CILDMMethod* pTSSILDM;

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

bool CQTSSAResultWidget::update(ListViews::ObjectType objectType,
                                ListViews::Action action,
                                const std::string & /* key */)
{
  if (objectType == ListViews::MODEL &&
      action == ListViews::ADD)
    mCentralWidget->table()->setTimeSeries(CTimeSeries());

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
  pTSSILDM = dynamic_cast<CILDMMethod*>(pTask->getMethod());

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
