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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*
 *  CMCAResultSubwidget.cpp
 *
 *
 *  Created by Paul on 4/2/10.
 *
 */

#include "CMCAResultSubwidget.h"

#include <QtCore/QFileInfo>
#include <QLineEdit>
#include <QCheckBox>
#include <QPainter>
#include <QMessageBox>

#include "copasi/copasi.h"

#include "qtUtilities.h"
#include "CopasiFileDialog.h"

#include "copasi/model/CModel.h"
#include "copasi/steadystate/CMCAMethod.h"
#include "copasi/core/CDataArray.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/steadystate/CMCATask.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/CopasiDataModel/CDataModel.h"

/*
 *  Constructs a CMCAResultSubwidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CMCAResultSubwidget::CMCAResultSubwidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
  : CopasiWidget(parent, name, fl)
  , mMCAMethod(NULL)
{
  setupUi(this);

  mpArrayElasticities->setSortingEnabled(true);
  mpArrayFCC->setSortingEnabled(true);
  mpArrayCCC->setSortingEnabled(true);

  clear();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CMCAResultSubwidget::~CMCAResultSubwidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void CMCAResultSubwidget::loadAll(const CMCAMethod * mcaMethod)
{
  mMCAMethod = mcaMethod;

  if (mcaMethod)
    {
      if (mcaMethod->getSteadyStateStatus() == CSteadyStateMethod::found)
        {
          mTopLabel->setText("Steady State found. All coefficients available.");
          this->loadElasticities(mcaMethod);
          this->loadConcentrationCCs(mcaMethod);
          this->loadFluxCCs(mcaMethod);
          mTabWidget->setTabEnabled(1, true);
          mTabWidget->setTabEnabled(2, true);
        }
      else
        {
          this->loadElasticities(mcaMethod);
          mTabWidget->setTabEnabled(1, false);
          mTabWidget->setTabEnabled(2, false);

          if (mcaMethod->getSteadyStateStatus() == CSteadyStateMethod::foundEquilibrium)
            mTopLabel->setText("Equilibrium steady state. Only elasticities available!");

          if (mcaMethod->getSteadyStateStatus() == CSteadyStateMethod::foundNegative)
            mTopLabel->setText("Invalid steady state (negative concentrations)!");

          if (mcaMethod->getSteadyStateStatus() == CSteadyStateMethod::notFound)
            mTopLabel->setText("No steady state found. Only elasticities available!");
        }
    }
  else
    {
      clear();
      return;
    }
}

void CMCAResultSubwidget::loadElasticities(const CMCAMethod * mcaMethod)
{
  const CDataArray * elasticitiesAnn;

  if (mComboScale->currentIndex() == 0)
    {
      elasticitiesAnn = mcaMethod->getScaledElasticitiesAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayElasticities->setColorCoding(tcs);
      mpArrayElasticities->setColorScalingAutomatic(true);
    }
  else
    {
      elasticitiesAnn = mcaMethod->getUnscaledElasticitiesAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayElasticities->setColorCoding(tcs);
      mpArrayElasticities->setColorScalingAutomatic(true);
    }

  mpArrayElasticities->setArrayAnnotation(elasticitiesAnn);
}

void CMCAResultSubwidget::loadConcentrationCCs(const CMCAMethod * mcaMethod)
{
  const CDataArray * CCCAnn;

  if (mComboScale->currentIndex() == 0)
    {
      CCCAnn = mcaMethod->getScaledConcentrationCCAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayCCC->setColorCoding(tcs);
        mpArrayCCC->setColorScalingAutomatic(false);
          tcs->setWhitepoint(0.005);
          tcs->setMaxIntensityPoint(2.0);

    }
  else
    {
      CCCAnn = mcaMethod->getUnscaledConcentrationCCAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayCCC->setColorCoding(tcs);
      mpArrayCCC->setColorScalingAutomatic(true);
        
    }

  mpArrayCCC->setArrayAnnotation(CCCAnn);
}

void CMCAResultSubwidget::loadFluxCCs(const CMCAMethod * mcaMethod)
{
  const CDataArray * FCCAnn;

  if (mComboScale->currentIndex() == 0)
    {
      FCCAnn = mcaMethod->getScaledFluxCCAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayFCC->setColorCoding(tcs);
      mpArrayFCC->setColorScalingAutomatic(false);
        tcs->setWhitepoint(0.005);
        tcs->setMaxIntensityPoint(2.0);
    }
  else
    {
      FCCAnn = mcaMethod->getUnscaledFluxCCAnn();

      CColorScaleBiLog * tcs = new CColorScaleBiLog();
      mpArrayFCC->setColorCoding(tcs);
      mpArrayFCC->setColorScalingAutomatic(true);
    }

  mpArrayFCC->setArrayAnnotation(FCCAnn);
}

void CMCAResultSubwidget::slotSave()
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
  CCopasiTask* mpTask =
    dynamic_cast<CMCATask *>(&mpDataModel->getTaskList()->operator[]("Metabolic Control Analysis"));

  if (mpTask != NULL)
    file << mpTask->getResult();

//    mpTask->printResult(file);

  return;
}

void CMCAResultSubwidget::slotScaled()
{
  loadAll(mMCAMethod);
}

void CMCAResultSubwidget::clear()
{
  mTopLabel->setText("No result available, please execute the MCA task.");

  mpArrayElasticities->setArrayAnnotation(NULL);
  mpArrayFCC->setArrayAnnotation(NULL);
  mpArrayCCC->setArrayAnnotation(NULL);

  return;
}
