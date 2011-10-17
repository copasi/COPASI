// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSensResultWidget.cpp,v $
//   $Revision: 1.19 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/17 16:20:36 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CQSensResultWidget.h"

#include <QMessageBox>

#include "qtUtilities.h"
#include "sensitivities/CSensTask.h"
#include "sensitivities/CSensProblem.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "utilities/CCopasiVector.h"

#include "UI/CopasiFileDialog.h"
#include "sensitivities/CSensTask.h"
#include "commandline/CLocaleString.h"

/*
 *  Constructs a CQSensResultWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQSensResultWidget::CQSensResultWidget(QWidget* parent, const char* name, Qt::WFlags fl)
    : CopasiWidget(parent, name, fl),
    mpResult(NULL)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQSensResultWidget::~CQSensResultWidget()
{}

void CQSensResultWidget::init()
{
  // unscaled array
  CColorScaleBiLog * tcs = new CColorScaleBiLog();
  mArrayWidget->setColorCoding(tcs);
  mArrayWidget->setColorScalingAutomatic(true);

  //scaled array
  CColorScaleAverage* tcs2 = new CColorScaleAverage();
  mArrayWidgetScaled->setColorCoding(tcs2);
  tcs2->setFactor(3.0);
  mArrayWidgetScaled->setColorScalingAutomatic(true);

  //scaled array
  CColorScaleAverage* tcs3 = new CColorScaleAverage();
  mArrayWidgetCollapsed->setColorCoding(tcs3);
  tcs3->setFactor(3.0);
  mArrayWidgetCollapsed->setColorScalingAutomatic(true);
}

void CQSensResultWidget::newResult()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  // clear the old one
  clearArrays();

  CSensTask * pTask =
    dynamic_cast<CSensTask*>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Sensitivities"]);

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

bool CQSensResultWidget::enterProtected()
{
  //clear the widget if the pointer to the result has changed
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CSensTask * pTask =
    dynamic_cast<CSensTask*>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Sensitivities"]);

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
                                          "untitled.txt", "TEXT Files (*.txt)", "Save to");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  std::ofstream file(CLocaleString::fromUtf8(TO_UTF8(fileName)).c_str());

  if (file.fail())
    return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CSensTask * pTask =
    dynamic_cast<CSensTask*>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Sensitivities"]);

  if (pTask != NULL)
    file << pTask->getResult();

//    pTask->print(&file);

  return;
}
