// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/04/27 16:00:44 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQTSSAResultSubWidget.h"

#include <qvariant.h>
#include <qmessagebox.h>
#include <q3filedialog.h>
#include <qregexp.h>

#include "UI/qtUtilities.h"
#include "UI/CopasiFileDialog.h"
#include "report/CCopasiRootContainer.h"

#include "utilities/CAnnotatedMatrix.h"

const CArrayAnnotation * pResult;

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

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQTSSAResultSubWidget::languageChange()
{
  retranslateUi(this);
}

void CQTSSAResultSubWidget::saveDataToFile()
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

  std::ofstream file(utf8ToLocale(TO_UTF8(fileName)).c_str());

  if (file.fail()) return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiTask* mpTask =
    dynamic_cast<CTSSATask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Time Scale Separation Analysis"]);

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
      CColorScaleAdvanced * tcs = new CColorScaleAdvanced() ;
      tcs->setColorMin(QColor(240, 240, 240));
      tcs->setColorMax(QColor(0, 255, 0));
      mpArrayWidget->setColorCoding(tcs);
      mpArrayWidget->setColorScalingAutomatic(true);

    }


  pResult = pMethod->getTable(name);
  mpArrayWidget->setArrayAnnotation(pResult);


}

void CQTSSAResultSubWidget::changeLabelToTime()
{

  int s = mpSlider->value();

  mpLabel->setNum(0);

  if (s > 1)
    mpLabel->setNum((double)pMethod->returnCurrentTime(s - 1));


}

void CQTSSAResultSubWidget::changeLabelToStep()
{

  int s = mpSlider->value();

  mpLabel->setNum(s);

}


void CQTSSAResultSubWidget::slotTimeOrStepChanged()
{

  int s = mpSlider->value();

  if (mpButton1->isChecked())
    if (s > 1)
      mpLabel->setNum((double)pMethod->returnCurrentTime(s - 1));
    else
      mpLabel->setNum(0);

  if (mpButton2->isChecked())
    mpLabel->setNum(s);
}

void CQTSSAResultSubWidget::changeContents()
{

  if (mpIndex == 0)
    {

      mpTimeScaleWidget->show();
      mpArrayWidget->hide();
      mpBox1->hide();
      mpButton->setText("Show Tables");
      mpIndex = 1;

    }
  else
    {
      mpTimeScaleWidget->hide();
      mpBox1->show();
      mpArrayWidget->show();
      mpButton->setText("Show Time scales");
      mpIndex = 0;
    }
}

void CQTSSAResultSubWidget::init()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  pTSSATask =
    dynamic_cast<CTSSATask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Time Scale Separation Analysis"]);

  if (!pTSSATask) return;

  pProblem = dynamic_cast<CTSSAProblem*>(pTSSATask->getProblem());
  pModel = pProblem->getModel();

  pMethod = dynamic_cast<CTSSAMethod*>(pTSSATask->getMethod());

  mpLabel->setNum(0);

  connect(mpBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(slotTableChanged(/* int */)));

  //set colorsettings for ArrayAnnotationWidgets

  CColorScaleAdvanced * tcs = new CColorScaleAdvanced() ;
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));
  mpArrayWidget->setColorCoding(tcs);
  mpArrayWidget->setColorScalingAutomatic(true);


  connect(mpSlider, SIGNAL(valueChanged(int)), this, SLOT(changeInterval()));
  connect(mpButton, SIGNAL(clicked()), this, SLOT(changeContents()));
  connect(mpButton1, SIGNAL(clicked()), this, SLOT(changeLabelToTime()));
  connect(mpButton2, SIGNAL(clicked()), this, SLOT(changeLabelToStep()));

  mpBox1->setEditable(false);

  mpIndex = 0;
  mpTimeScaleWidget->hide();
  mpBox1->show();
  mpArrayWidget->show();

}

void CQTSSAResultSubWidget::displayResult()
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  pTSSATask =
    dynamic_cast<CTSSATask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Time Scale Separation Analysis"]);

  if (!pTSSATask) return;

  pProblem = dynamic_cast<CTSSAProblem*>(pTSSATask->getProblem());

  pModel = pProblem->getModel();

  pMethod = dynamic_cast<CTSSAMethod*>(pTSSATask->getMethod());

  QString a = FROM_UTF8(pModel->getTimeUnitName());

  mpLabel->setNum((double)pProblem->getStepNumber());

  mpSlider->setRange(1, pProblem->getStepNumber());

  mpSlider->setValue(mpSlider->minValue());


  mpBox1->clear();

  unsigned C_INT i;

  for (i = 0; i <  pMethod->getTableName().size(); i++)
    {
      mpBox1->insertItem(FROM_UTF8(pMethod->getTableName()[i]));
    }

  mpArrayWidget->switchToTable();
  mpSlider->setDisabled(false);

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
}

/**
 * Get the results for the requested step from ILDM-method.
 * Fill widgets with this results.
 **/

void CQTSSAResultSubWidget::changeInterval()
{

  slotTimeOrStepChanged();

  int s = mpSlider->value();

  if (pMethod->setAnnotationM(s))
    {
      std::string name  =  static_cast<std::string >(mpBox1->currentText().toUtf8());
      pResult = pMethod->getTable(name);

      mpArrayWidget->setArrayAnnotation(pResult);

      CVector< C_FLOAT64> vec = pMethod->getVec_TimeScale(s);
      mpTimeScaleWidget->paintTimeScale(vec);
    }
  else
    {

      mpSlider->setDisabled(true);
      mpArrayWidget->setArrayAnnotation(NULL);
      mpTimeScaleWidget->clearWidget();

    }
}


