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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQTSSAResultSubWidget.h"
#include "CQMessageBox.h"

#include "qtUtilities.h"
#include "CopasiFileDialog.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/tssanalysis/CTSSATask.h"
#include "copasi/tssanalysis/CTSSAProblem.h"
#include "copasi/core/CDataArray.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/model/CModel.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

const CDataArray * pResult;

/*
 *  Constructs a CQTSSAResultSubWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQTSSAResultSubWidget::CQTSSAResultSubWidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
  : CopasiWidget(parent, name, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTSSAResultSubWidget::~CQTSSAResultSubWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQTSSAResultSubWidget::saveDataToFile()
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          CopasiFileDialog::getDefaultFileName(".txt"), "Text Files (*.txt)", "Save to");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(this, fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  std::ofstream file(CLocaleString::fromUtf8(TO_UTF8(fileName)).c_str());

  if (file.fail()) return;

  assert(CRootContainer::getDatamodelList()->size() > 0);
  CCopasiTask* mpTask =
    dynamic_cast<CTSSATask *>(&mpDataModel->getTaskList()->operator[]("Time Scale Separation Analysis"));

  if (!mpTask) return;

  CCopasiProblem* mpProblem = mpTask->getProblem();

  mpProblem->printResult(&file);

  return;
}

void CQTSSAResultSubWidget::slotTableChanged()
{

  std::string name  =  static_cast<std::string >(mpBox1->currentText().toUtf8());

  if (name == "Reactions slow space" ||
      name == "Reactions contribution to the mode" ||
      name == "Reactions distribution between modes " ||
      name == "Reactions fast space" ||
      name == "Participation Index" ||
      name == "Fast Participation Index" ||
      name == "Slow Participation Index" ||
      name == "Normed Participation Index (by column)" ||
      name == "Normed Participation Index (by row)" ||
      name == "Importance Index" ||
      name == "Normed Importance Index (by row)")
    {
      CColorScaleSimple* tcs = new CColorScaleSimple();
      tcs->setSymmetric(true);
      mpArrayWidget->setColorCoding(tcs);
      mpArrayWidget->setColorScalingAutomatic(true);
    }
  else
    {
      //CColorScaleAdvanced * tcs = new CColorScaleAdvanced();
      //tcs->setColorMin(QColor(240, 240, 240));
      //tcs->setColorMax(QColor(0, 255, 0));

      CColorScaleSimple* tcs = new CColorScaleSimple();
      tcs->setSymmetric(true);

      mpArrayWidget->setColorCoding(tcs);
      mpArrayWidget->setColorScalingAutomatic(true);
    }

  pTSSATask =
    dynamic_cast< CTSSATask * >(&mpDataModel->getTaskList()->operator[]("Time Scale Separation Analysis"));

  if (!pTSSATask)
    return;

  pProblem = dynamic_cast< CTSSAProblem * >(pTSSATask->getProblem());
  pModel = &pTSSATask->getMathContainer()->getModel();

  pMethod = dynamic_cast< CTSSAMethod * >(pTSSATask->getMethod());
  pResult = pMethod->getTable(name);
  mpArrayWidget->setArrayAnnotation(pResult);
}

//set time and step number
void CQTSSAResultSubWidget::slotTimeAndStepChanged()
{

  int s = mpSlider->value();

  mpLabelTime->setNum((double)pMethod->getTimeForStep(s - 1));

  mpLabelStep->setNum(s);
}

//switch between time scale and table views
void CQTSSAResultSubWidget::changeContents()
{

  if (mpIndex == 0)
    {

      mpTimeScaleWidget->show();
      //mpArrayWidget->hide();
      //mpBox1->hide();
      //mpButton->setText("Show Tables");
      mpButton->setText("Hide Time scales");
      mpIndex = 1;
    }
  else
    {
      mpTimeScaleWidget->hide();
      //mpBox1->show();
      //mpArrayWidget->show();
      mpButton->setText("Show Time scales");
      mpIndex = 0;
    }
}

void CQTSSAResultSubWidget::init()
{
  assert(mpDataModel != NULL);
  pTSSATask =
    dynamic_cast<CTSSATask *>(&mpDataModel->getTaskList()->operator[]("Time Scale Separation Analysis"));

  if (!pTSSATask) return;

  pProblem = dynamic_cast<CTSSAProblem*>(pTSSATask->getProblem());
  pModel = & pTSSATask->getMathContainer()->getModel();

  pMethod = dynamic_cast<CTSSAMethod*>(pTSSATask->getMethod());

  mpLabelTime->setNum(0);
  mpLabelStep->setNum(0);

  connect(mpBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(slotTableChanged(/* int */)));

  //set colorsettings for ArrayAnnotationWidgets

  CColorScaleAdvanced * tcs = new CColorScaleAdvanced();
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));
  mpArrayWidget->setColorCoding(tcs);
  mpArrayWidget->setColorScalingAutomatic(true);

  connect(mpSlider, SIGNAL(valueChanged(int)), this, SLOT(changeInterval()));
  connect(mpButton, SIGNAL(clicked()), this, SLOT(changeContents()));
  connect(ButtonSaveData, SIGNAL(clicked()), this, SLOT(saveDataToFile()));

  mpBox1->setEditable(false);

  mpIndex = 0;
  mpTimeScaleWidget->hide();
  mpBox1->show();
  mpArrayWidget->show();
}

void CQTSSAResultSubWidget::displayResult()
{

  assert(mpDataModel != NULL);
  pTSSATask =
    dynamic_cast<CTSSATask *>(&mpDataModel->getTaskList()->operator[]("Time Scale Separation Analysis"));

  if (!pTSSATask) return;

  pProblem = dynamic_cast<CTSSAProblem*>(pTSSATask->getProblem());

  pModel = & pTSSATask->getMathContainer()->getModel();

  pMethod = dynamic_cast<CTSSAMethod*>(pTSSATask->getMethod());

  QString a = FROM_UTF8(pModel->getTimeUnitName());

  mpSlider->setRange(1, pProblem->getStepNumber());

  mpSlider->setValue(mpSlider->minimum());

  mpBox1->clear();

  unsigned C_INT i;

  for (i = 0; i <  pMethod->getTableNames().size(); i++)
    {
      mpBox1->insertItem(0, FROM_UTF8(pMethod->getTableNames()[i]));
    }

  mpArrayWidget->switchToTable();
  mpSlider->setDisabled(false);
  mpSlider->setFocus();

  changeInterval();
}

/**
 * Clear ArrayAnnotation-widgets.
 **/
void CQTSSAResultSubWidget::discardOldResults()
{
  mpArrayWidget->setArrayAnnotation(NULL);
  mpArrayWidget->clearWidget();
  mpTimeScaleWidget->clearWidget();
  mpSlider->setDisabled(true);
}

/**
 * Get the results for the requested step from the method.
 * Fill widgets with this results.
 **/

void CQTSSAResultSubWidget::changeInterval()
{
  // ensure we always have a valid method
  pMethod = dynamic_cast<CTSSAMethod*>(pTSSATask->getMethod());

  slotTimeAndStepChanged();

  int s = mpSlider->value();

  if (pMethod->setAnnotationM(s - 1))
    {
      std::string name = TO_UTF8(mpBox1->currentText());
      pResult = pMethod->getTable(name);

      mpArrayWidget->setArrayAnnotation(pResult);

      CVector< C_FLOAT64> vec = pMethod->getVec_TimeScale(s);
      mpTimeScaleWidget->paintTimeScale(vec);
    }
  else
    {

      //mpSlider->setDisabled(true);
      mpArrayWidget->setArrayAnnotation(NULL);
      mpTimeScaleWidget->clearWidget();
    }
}
