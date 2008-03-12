// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TimeSeriesWidget.cpp,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 00:32:59 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlayout.h>

#include "copasi.h"

#include "TimeSeriesWidget.h"
#include "TimeSeriesSubwidget.h"
#include "CTimeSeriesTable.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiVector.h"
#include "trajectory/CTrajectoryTask.h"

/*
 *  Constructs a TimeSeriesWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
TimeSeriesWidget::TimeSeriesWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    objKey("")
{
  if (!name)
    setName("TimeSeriesWidget");
  setCaption(trUtf8("TimeSeriesWidget"));

  mWidgetLayout = new QGridLayout(this, 1, 1, 0, -1, "Layout");

  mCentralWidget = new TimeSeriesSubWidget(this, "TimeSeriesSubwidget");
  mWidgetLayout->addWidget(mCentralWidget, 0, 0);

  mCentralWidget->setFramework(mFramework);
}

/*
 *  Destroys the object and frees any allocated resources
 */
TimeSeriesWidget::~TimeSeriesWidget()
{}

bool TimeSeriesWidget::loadFromBackend()
{
  mCentralWidget->displayOptimizationTab(false);
  mCentralWidget->table()->setTimeSeries(dynamic_cast<CTrajectoryTask *>((*CCopasiDataModel::Global->getTaskList())["Time-Course"])->getTimeSeries());
  return true;
}

bool TimeSeriesWidget::saveToBackend()
{
  return true;
}

bool TimeSeriesWidget::update(ListViews::ObjectType objectType,
                              ListViews::Action action,
                              const std::string & /* key */)
{
  if (objectType == ListViews::MODEL &&
      action == ListViews::ADD)
    mCentralWidget->table()->setTimeSeries(CTimeSeries());

  return true;
}

bool TimeSeriesWidget::leave()
{
  //return saveToCompartment();
  return true;
}

bool TimeSeriesWidget::enter(const std::string & /* key */)
{
  return true;
}

void TimeSeriesWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);

  mCentralWidget->setFramework(mFramework);
}
