// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"

#include "CQSensResultWidget.h"

#include <QMessageBox>

#include "qtUtilities.h"
#include "copasi/sensitivities/CSensTask.h"
#include "copasi/sensitivities/CSensProblem.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/core/CDataVector.h"

#include "copasi/UI/CopasiFileDialog.h"
#include "copasi/sensitivities/CSensTask.h"
#include "copasi/commandline/CLocaleString.h"

/*
 *  Constructs a CQSensResultWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQSensResultWidget::CQSensResultWidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
  : CopasiWidget(parent, name, fl),
    mpResult(NULL)
{
  setupUi(this);

  CColorScaleBiLog * tcs = new CColorScaleBiLog();
  mArrayWidget->setColorCoding(tcs);
  mArrayWidget->setColorScalingAutomatic(true);
  mArrayWidget->setSortingEnabled(true);

  //scaled array
  CColorScaleAverage* tcs2 = new CColorScaleAverage();
  mArrayWidgetScaled->setColorCoding(tcs2);
  tcs2->setFactor(3.0);
  mArrayWidgetScaled->setColorScalingAutomatic(true);
  mArrayWidgetScaled->setSortingEnabled(true);

  //scaled array
  CColorScaleAverage* tcs3 = new CColorScaleAverage();
  mArrayWidgetCollapsed->setColorCoding(tcs3);
  tcs3->setFactor(3.0);
  mArrayWidgetCollapsed->setColorScalingAutomatic(true);
  mArrayWidgetCollapsed->setSortingEnabled(true);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQSensResultWidget::~CQSensResultWidget()
{}

void CQSensResultWidget::newResult()
{
  // clear the old one
  clearArrays();

  CSensTask * pTask =
    dynamic_cast<CSensTask*>(&mpDataModel->getTaskList()->operator[]("Sensitivities"));

  if (!pTask)
    return;

  CSensProblem * pProblem = dynamic_cast< CSensProblem * >(pTask->getProblem());

  if (!pProblem)
    return;

  mpResult = pProblem->getResultAnnotated();
  mpScaledResult = pProblem->getScaledResultAnnotated();

  mArrayWidget->setArrayAnnotation(mpResult);
  mArrayWidgetScaled->setArrayAnnotation(mpScaledResult);

  //tab for collapsed result
  if (pProblem->collapsRequested())
    {
      mpCollapsedResult = pProblem->getCollapsedResultAnnotated();
      mpTab->setTabEnabled(mpTab->indexOf(mArrayWidgetCollapsed), true);
    }
  else
    {
      mpCollapsedResult = NULL;
      mpTab->setTabEnabled(mpTab->indexOf(mArrayWidgetCollapsed), false);
    }

  mArrayWidgetCollapsed->setArrayAnnotation(mpCollapsedResult);
}

void CQSensResultWidget::clearArrays()
{
  mArrayWidget->setArrayAnnotation(NULL);
  mArrayWidgetScaled->setArrayAnnotation(NULL);
  mArrayWidgetCollapsed->setArrayAnnotation(NULL);
}

//*************************************

bool CQSensResultWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  /*  if (this->isShown())
      return loadFromBackend();
    else
      return true;*/
  return true;
}

bool CQSensResultWidget::leaveProtected()
{
  return true;
}

bool CQSensResultWidget::enterProtected()
{
  //clear the widget if the pointer to the result has changed
  CSensTask * pTask =
    dynamic_cast<CSensTask*>(&mpDataModel->getTaskList()->operator[]("Sensitivities"));

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

void CQSensResultWidget::saveToFile()
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          CopasiFileDialog::getDefaultFileName(".txt"), "TEXT Files (*.txt)", "Save to");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(this, fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  std::ofstream file(CLocaleString::fromUtf8(TO_UTF8(fileName)).c_str());

  if (file.fail())
    return;

  assert(mpDataModel != NULL);
  CSensTask * pTask =
    dynamic_cast<CSensTask*>(&mpDataModel->getTaskList()->operator[]("Sensitivities"));

  if (pTask != NULL)
    file << pTask->getResult();

//    pTask->print(&file);

  return;
}
