/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSensResultWidget.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: ssahle $
   $Date: 2007/01/10 17:08:16 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include <qpushbutton.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qtable.h>

#include "copasi.h"

#include "CQSensResultWidget.h"
//#include "StateSubwidget.h"
//#include "CTimeSeriesTable.h"
#include "qtUtilities.h"
#include "sensitivities/CSensTask.h"
#include "sensitivities/CSensProblem.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiVector.h"

#include <qtabwidget.h>

/*
 *  Constructs a CQSensResultWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQSensResultWidget::CQSensResultWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    mpResult(NULL)
{
  if (!name)
    setName("CQSensResultWidget");
  setCaption("CQSensResultWidget");

  mWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "CQSensResultWidgetLayout");

  // **********  Label **************
  mLabelTitle = new QLabel(this, "SensLabel");
  mLabelTitle->setText("Sensitivities");
  mLabelTitle->setAlignment(int(QLabel::AlignVCenter
                                | QLabel::AlignLeft));
  mLabelTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  mWidgetLayout->addWidget(mLabelTitle, 0, 0);

  // tab widget
  mpTab = new QTabWidget(this, "TabWidget");
  mWidgetLayout->addMultiCellWidget(mpTab, 1, 2, 0, 2);

  // unscaled array
  mArrayWidget = new CQArrayAnnotationsWidget(mpTab, "ArrayWidget");
  //mArrayWidget->setColorCoding(new CColorScale1());
  //CColorScaleAverage * tcs = new CColorScaleAverage();
  CColorScaleBiLog * tcs = new CColorScaleBiLog();
  mArrayWidget->setColorCoding(tcs);
  //tcs->setMinMax(-1,1);
  //tcs->setSymmetric(true);
  //tcs->setFactor(3.0);
  mArrayWidget->setColorScalingAutomatic(true);
  mpTab->addTab(mArrayWidget, "unscaled");

  //scaled array
  mArrayWidgetScaled = new CQArrayAnnotationsWidget(mpTab, "ArrayWidget2");
  //mArrayWidgetScaled->setColorCoding(new CColorScale1());
  CColorScaleAverage* tcs2 = new CColorScaleAverage();
  mArrayWidgetScaled->setColorCoding(tcs2);
  //tcs2->setMinMax(-1,1);
  //tcs2->setSymmetric(true);
  tcs2->setFactor(3.0);
  mArrayWidgetScaled->setColorScalingAutomatic(true);
  mpTab->addTab(mArrayWidgetScaled, "scaled");
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQSensResultWidget::~CQSensResultWidget()
{}

void CQSensResultWidget::newResult()
{
  CSensTask * pTask =
    dynamic_cast<CSensTask*>((*CCopasiDataModel::Global->getTaskList())["Sensitivities"]);
  if (!pTask)
    {
      clearArrays();
      return;
    }

  CSensProblem * pProblem = dynamic_cast< CSensProblem * >(pTask->getProblem());
  if (!pProblem)
    {
      clearArrays();
      return;
    }

  mpResult = pProblem->getResultAnnotated();
  mpScaledResult = pProblem->getScaledResultAnnotated();

  mArrayWidget->setArrayAnnotation(mpResult);
  mArrayWidgetScaled->setArrayAnnotation(mpScaledResult);
}

void CQSensResultWidget::clearArrays()
{
  mArrayWidget->setArrayAnnotation(NULL);
  mArrayWidgetScaled->setArrayAnnotation(NULL);
}

//*************************************

bool CQSensResultWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action
                                C_UNUSED(action), const std::string & C_UNUSED(key))
{
  /*  if (this->isShown())
      return loadFromBackend();
    else
      return true;*/
  return true;
}

bool CQSensResultWidget::leave()
{
  return true;
}

bool CQSensResultWidget::enter(const std::string & C_UNUSED(key))
{
  //clear the widget if the pointer to the result has changed
  CSensTask * pTask =
    dynamic_cast<CSensTask*>((*CCopasiDataModel::Global->getTaskList())["Sensitivities"]);
  if (!pTask)
    {
      clearArrays();
      return false;
    }

  CSensProblem * pProblem = dynamic_cast< CSensProblem * >(pTask->getProblem());
  if (!pProblem)
    {
      clearArrays();
      return false;
    }

  if (mpResult != pProblem->getResultAnnotated())
    {
      clearArrays();
      return false;
    }

  return true;
}
