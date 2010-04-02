// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/03/21 15:21:13 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <qvariant.h>
#include <qmessagebox.h>
#include <q3filedialog.h>
#include <qregexp.h>

#include "UI/qtUtilities.h"
#include "UI/CopasiFileDialog.h"
#include "optimization/COptProblem.h"
#include "optimization/COptTask.h"
#include "CQTSSATimeScaleWidget.h"
#include "tssanalysis/CTSSATask.h"
#include "tssanalysis/CTSSAProblem.h"
#include "report/CCopasiRootContainer.h"

#include "tssanalysis/CILDMMethod.h"
#include "tssanalysis/CILDMModifiedMethod.h"
#include "tssanalysis/CCSPMethod.h"

#include "utilities/CAnnotatedMatrix.h"
#include "model/CModel.h"

CTSSATask* pTSSTask;
CTSSAProblem* pProblem;

CCSPMethod *pCSPMethod;
CILDMMethod *pILDMMethod;
CILDMModifiedMethod *pILDMModifiedMethod;

CQTSSATimeScaleWidget* mpTimeScaleWidgetILDM;
CQTSSATimeScaleWidget* mpTimeScaleWidgetILDMModified;

CModel* pModel;

const CArrayAnnotation * pResult;
const CArrayAnnotation * pResult2;
const CArrayAnnotation * pResult3;
const CArrayAnnotation * pResult4;
const CArrayAnnotation * pResult5; //NEW TAB

/* temporary tables */

const CArrayAnnotation * pResultTMP1;
const CArrayAnnotation * pResultTMP2;
const CArrayAnnotation * pResultTMP3;

/* ILDM Modified */
const CArrayAnnotation * pResult_M;
const CArrayAnnotation * pResult2_M;
const CArrayAnnotation * pResult3_M;
const CArrayAnnotation * pResult4_M;

/* CSP */
const CArrayAnnotation * pResultCSP;
const CArrayAnnotation * pResult2CSP;
const CArrayAnnotation * pResult3CSP;
const CArrayAnnotation * pResult4CSP;
const CArrayAnnotation * pResult5CSP;

/* CSP normed tables */
const CArrayAnnotation * pResult3NormedCSP;
const CArrayAnnotation * pResult4NormedRowCSP;
const CArrayAnnotation * pResult4NormedColumnCSP;
const CArrayAnnotation * pResult5NormedRowCSP;

bool mILDM = true;
bool mILDMModified = false;

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

void CQTSSAResultSubWidget::displayOptimizationTab(bool displayOptTab)
{
  if (displayOptTab)
    {
      tabWidget2->insertTab(tab, "OptimizationResults", 0);
      tabWidget2->setCurrentPage(0);
    }
  else
    tabWidget2->removePage(tab);
}

void CQTSSAResultSubWidget::toggleView()
{
  /*  if (comboBox->currentItem() == 0)
      dataTable->showConcentrations(true);
    else
      dataTable->showConcentrations(false);*/
}

void CQTSSAResultSubWidget::init()
{

  tabWidget2->setTabEnabled(TabPage, false);
  tabWidget2->setTabEnabled(tab4, false);

  mpTimeScaleWidgetILDM = new CQTSSATimeScaleWidget();
  mTabWidget->addTab(mpTimeScaleWidgetILDM, "Timescale");

  //set colorsettings for ArrayAnnotationWidgets
  CColorScaleAdvanced * tcs ; //= new CColorScaleAdvanced();
  //tcs->setColorMin(QColor(240, 240, 240));
  //tcs->setColorMax(QColor(0, 255, 0));

  // ILDM
  // mVslow_metab widget
  tcs = new CColorScaleAdvanced();
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));
  pArrayWidget->setColorCoding(tcs);
  pArrayWidget->setColorScalingAutomatic(true);
  // mVslow widget
  tcs = new CColorScaleAdvanced();
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));
  pArrayWidget2->setColorCoding(tcs);
  pArrayWidget2->setColorScalingAutomatic(true);
  // mVslow_space widget
  tcs = new CColorScaleAdvanced();
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));
  pArrayWidget3->setColorCoding(tcs);
  pArrayWidget3->setColorScalingAutomatic(true);
  // mVslow_space widget
  tcs = new CColorScaleAdvanced();
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));
  pArrayWidget4->setColorCoding(tcs);
  pArrayWidget4->setColorScalingAutomatic(true);

  //NEW TAB
  // mReacSlowSpace widget
  CColorScaleSimple* pcss = new CColorScaleSimple();
  //tcs->setColorMin(QColor(240, 240, 240));
  //tcs->setColorMax(QColor(0, 255, 0));
  pcss->setSymmetric(true);
  pArrayWidget_3_2->setColorCoding(pcss);
  pArrayWidget_3_2->setColorScalingAutomatic(true);

  /* temporary tabs */

  CColorScaleSimple* ttTMP1 = new CColorScaleSimple();
  ttTMP1->setSymmetric(true);
  pArrayWidgetTMP1->setColorCoding(ttTMP1);
  pArrayWidgetTMP1->setColorScalingAutomatic(true);

  CColorScaleSimple* ttTMP2 = new CColorScaleSimple();
  ttTMP2->setSymmetric(true);
  pArrayWidgetTMP2->setColorCoding(ttTMP2);
  pArrayWidgetTMP2->setColorScalingAutomatic(true);

  CColorScaleSimple* ttTMP3 = new CColorScaleSimple();
  ttTMP3->setSymmetric(true);
  pArrayWidgetTMP3->setColorCoding(ttTMP3);
  pArrayWidgetTMP3->setColorScalingAutomatic(true);

  // ILDM Modified

  mpTimeScaleWidgetILDMModified = new CQTSSATimeScaleWidget();
  mTabWidget_4->addTab(mpTimeScaleWidgetILDMModified, "Timescale");

  // mVslow_metab widget
  tcs = new CColorScaleAdvanced();
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));
  pArrayWidget_5->setColorCoding(tcs);
  pArrayWidget_5->setColorScalingAutomatic(true);
  // mVslow widget
  tcs = new CColorScaleAdvanced();
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));
  pArrayWidget2_5->setColorCoding(tcs);
  pArrayWidget2_5->setColorScalingAutomatic(true);
  // mVslow_space widget
  tcs = new CColorScaleAdvanced();
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));
  pArrayWidget3_5->setColorCoding(tcs);
  pArrayWidget3_5->setColorScalingAutomatic(true);
  // mVslow_space widget
  tcs = new CColorScaleAdvanced();
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));
  pArrayWidget4_5->setColorCoding(tcs);
  pArrayWidget4_5->setColorScalingAutomatic(true);

  // Amplitude widget
  tcs = new CColorScaleAdvanced();
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));
  pArrayWidget_3->setColorCoding(tcs);
  pArrayWidget_3->setColorScalingAutomatic(true);
  // Radical Pointer widget
  tcs = new CColorScaleAdvanced();
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));
  pArrayWidget2_3->setColorCoding(tcs);
  pArrayWidget2_3->setColorScalingAutomatic(true);
  // Fast Reaction Pointer widget
  //tcs = new CColorScaleAdvanced();
  //tcs->setColorMin(QColor(240, 240, 240));
  //tcs->setColorMax(QColor(0, 255, 0));
  //pArrayWidget3_3->setColorCoding(tcs);
  //pArrayWidget3_3->setColorScalingAutomatic(true);

  // Participation Index widget
  CColorScaleSimple* pics = new CColorScaleSimple();
  pics->setSymmetric(true);
  pArrayWidget4_3->setColorCoding(pics);
  pArrayWidget4_3->setColorScalingAutomatic(true);

  // Importance Index widget
  CColorScaleSimple* iics = new CColorScaleSimple();
  iics->setSymmetric(true);
  pArrayWidget4_3_2->setColorCoding(iics);
  pArrayWidget4_3_2->setColorScalingAutomatic(true);

  /* CSP normed tables */

  // Normed Fast Reaction Pointer widget
  tcs = new CColorScaleAdvanced();
  tcs->setColorMin(QColor(240, 240, 240));
  tcs->setColorMax(QColor(0, 255, 0));
  pArrayWidget3_3->setColorCoding(tcs);
  pArrayWidget3_3->setColorScalingAutomatic(true);

  // Normed Participation Index (by row) widget
  CColorScaleSimple* npircs = new CColorScaleSimple();
  npircs->setSymmetric(true);
  pArrayWidgetNPIr->setColorCoding(npircs);
  pArrayWidgetNPIr->setColorScalingAutomatic(true);

  // Normed Participation Index (by column) widget
  CColorScaleSimple* npiccs = new CColorScaleSimple();
  npiccs->setSymmetric(true);
  pArrayWidgetNPIc->setColorCoding(npiccs);
  pArrayWidgetNPIc->setColorScalingAutomatic(true);

  // Normed Importance Index (by row) widget
  CColorScaleSimple* niircs = new CColorScaleSimple();
  niircs->setSymmetric(true);
  pArrayWidgetNIIr->setColorCoding(niircs);
  pArrayWidgetNIIr->setColorScalingAutomatic(true);

  connect(mSlider, SIGNAL(valueChanged(int)), this, SLOT(changeILDMInterval()));
  connect(mSlider_4, SIGNAL(valueChanged(int)), this, SLOT(changeILDMModifiedInterval()));
  connect(mSlider_3, SIGNAL(valueChanged(int)), this, SLOT(changeCSPInterval()));

  connect(tabWidget2, SIGNAL(currentChanged(QWidget *)), this, SLOT(hideButtons()));

  dataTable->setNumRows(10);
  displayOptimizationTab(false);

#ifndef WITH_CSPMETHOD
  displayCSPDevelopment(false);
#endif

  //the combobox for switching particle number/concentration is obsolete and does not work
  comboBox->hide();
}

CTimeSeriesTable* CQTSSAResultSubWidget::table()
{
  return dataTable;
}

/**
 * Fill the combobox mpSelectStep with count of steps the ILDM
 * Method is calculating with.
 **/
void CQTSSAResultSubWidget::setStepNumber()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CTSSATask* pTSSTask =
    dynamic_cast<CTSSATask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Time Scale Separation Analysis"]);

  if (!pTSSTask) return;

  // pTSSMethod = dynamic_cast<CTSSAMethod*>(pTSSTask->getMethod());
  //if (!pTSSMethod) return;
  //  pTimeScaleSeperation = dynamic_cast<CILDMMethod*>(pTSSTask->getMethod());

  pProblem = dynamic_cast<CTSSAProblem*>(pTSSTask->getProblem());
  CModel* pModel = pProblem->getModel();

  if (mILDM)
    {
      pILDMMethod = dynamic_cast<CILDMMethod*>(pTSSTask->getMethod());

      QString a = FROM_UTF8(pModel->getTimeUnitName());
      // mLabel7->setText(a);
      mLabel6->setNum((double)pProblem->getStepNumber());
      mSlider->setRange(1, pProblem->getStepNumber());
      mSlider->setValue(mSlider->minValue());
      changeILDMInterval();
    }
  else if (mILDMModified)
    {
      pILDMModifiedMethod = dynamic_cast<CILDMModifiedMethod*>(pTSSTask->getMethod());

      QString a = FROM_UTF8(pModel->getTimeUnitName());
      // mLabel7->setText(a);

      mLabel6_6->setNum((double)pProblem->getStepNumber());
      mSlider_4->setRange(1, pProblem->getStepNumber());
      mSlider_4->setValue(mSlider_4->minValue());
      changeILDMModifiedInterval();
    }
  else
    {
      pCSPMethod = dynamic_cast<CCSPMethod*>(pTSSTask->getMethod());

      QString a = FROM_UTF8(pModel->getTimeUnitName());
      // mLabel7_3->setText(a);
      mLabel6_3->setNum((double)pProblem->getStepNumber());
      mSlider_3->setRange(1, pProblem->getStepNumber());
      mSlider_3->setValue(mSlider_3->minValue());
      //mSlider->setRange(1, pProblem->getStepNumber());
      //mSlider->setValue(mSlider->minValue());
      changeCSPInterval();
    }
}

/**
 * Clear ArrayAnnotation-widgets.
 **/
void CQTSSAResultSubWidget::discardOldResults()
{
  pArrayWidget->setArrayAnnotation(NULL);
  pArrayWidget2->setArrayAnnotation(NULL);
  pArrayWidget3->setArrayAnnotation(NULL);
  pArrayWidget4->setArrayAnnotation(NULL);
  pArrayWidget_3_2->setArrayAnnotation(NULL); //NEW TAB

  pArrayWidget_5->setArrayAnnotation(NULL);
  pArrayWidget2_5->setArrayAnnotation(NULL);
  pArrayWidget3_5->setArrayAnnotation(NULL);
  pArrayWidget4_5->setArrayAnnotation(NULL);

  pArrayWidget_3->setArrayAnnotation(NULL);
  pArrayWidget2_3->setArrayAnnotation(NULL);
  pArrayWidget3_3->setArrayAnnotation(NULL);
  pArrayWidget4_3->setArrayAnnotation(NULL);
  pArrayWidget4_3_2->setArrayAnnotation(NULL);

  pArrayWidgetNPIr->setArrayAnnotation(NULL);
  pArrayWidgetNPIc->setArrayAnnotation(NULL);
  pArrayWidgetNIIr->setArrayAnnotation(NULL);

  mLabel2->setNum(0);
  mLabel4->setNum(0);
  mLabel6->setNum(0);

  mLabel2_6->setNum(0);
  mLabel4_6->setNum(0);
  mLabel6_6->setNum(0);

  mLabel2_3->setNum(0);
  mLabel4_3->setNum(0);
  mLabel6_3->setNum(0);

  mpTimeScaleWidgetILDM->clearWidget();
  mpTimeScaleWidgetILDMModified->clearWidget();

  tabWidget2->setTabEnabled(TabPage_ILDM, false);
  tabWidget2->setTabEnabled(TabPage_ILDMM, false);
  tabWidget2->setTabEnabled(TabPage_CSP, false);

  //tabWidget2->setTabEnabled(TabPage, false);
  //tabWidget2->setTabEnabled(TabPage_4, false);
}

/**
 * Get the results for the requested step from ILDM-method.
 * Fill widgets with this results.
 **/
void CQTSSAResultSubWidget::changeILDMInterval()
{
  int step = mSlider->value();

  if (step == 1)
    mLabel2->setNum(0);
  else
    mLabel2->setNum((double)pILDMMethod->returnCurrentTime(step - 2));

  mLabel4->setNum(step);

  pILDMMethod->setAnnotationM(step);
  pResult = pILDMMethod->getVslowPrintAnn();
  pResult2 = pILDMMethod->getVslowMetabPrintAnn();
  pResult3 = pILDMMethod->getVslowSpacePrintAnn();
  pResult4 = pILDMMethod->getVfastSpacePrintAnn();
  pResult5 = pILDMMethod->getReacSlowSpacePrintAnn(); // NEW TAB
  pArrayWidget->setArrayAnnotation(pResult);
  pArrayWidget2->setArrayAnnotation(pResult2);
  pArrayWidget3->setArrayAnnotation(pResult3);
  pArrayWidget4->setArrayAnnotation(pResult4);
  pArrayWidget_3_2->setArrayAnnotation(pResult5); //NEW TAB
  mpTimeScaleWidgetILDM->paintTimeScale(pILDMMethod->getVec_TimeScale(step));

  /* temporary tables */

  pResultTMP1 = pILDMMethod->getTMP1PrintAnn();
  pResultTMP2 = pILDMMethod->getTMP2PrintAnn();
  pResultTMP3 = pILDMMethod->getTMP3PrintAnn();
  pArrayWidgetTMP1->setArrayAnnotation(pResultTMP1);
  pArrayWidgetTMP2->setArrayAnnotation(pResultTMP2);
  pArrayWidgetTMP3->setArrayAnnotation(pResultTMP3);
}

/**
 * Get the results for the requested step from CSP-method.
 * Fill widgets with this results.
 **/
void CQTSSAResultSubWidget::changeCSPInterval()
{

  int step = mSlider_3->value();
  //int step = mSlider->value();

  if (step == 1)
    mLabel2_3->setNum(0);
  else
    mLabel2_3->setNum((double)pCSPMethod->returnCurrentTime(step - 1));

  mLabel4_3->setNum(step);

  pCSPMethod->setAnnotationM(step);

  pResultCSP = pCSPMethod->getAmplitudeAnn();
  pResult2CSP = pCSPMethod->getRadicalPointerAnn();
  pResult3CSP = pCSPMethod->getFastReactionPointerAnn();
  pResult4CSP = pCSPMethod->getParticipationIndexAnn();
  pResult5CSP = pCSPMethod->getImportanceIndexAnn();
  pResult3NormedCSP = pCSPMethod->getFastReactionPointerNormedAnn();
  pResult4NormedRowCSP = pCSPMethod->getParticipationIndexNormedRowAnn();
  pResult4NormedColumnCSP = pCSPMethod->getParticipationIndexNormedColumnAnn();
  pResult5NormedRowCSP = pCSPMethod->getImportanceIndexNormedRowAnn();

  pArrayWidget_3->setArrayAnnotation(pResultCSP);
  pArrayWidget2_3->setArrayAnnotation(pResult2CSP);
  //pArrayWidget3_3->setArrayAnnotation(pResult3CSP);
  pArrayWidget4_3->setArrayAnnotation(pResult4CSP);
  pArrayWidget4_3_2->setArrayAnnotation(pResult5CSP);
  pArrayWidget3_3->setArrayAnnotation(pResult3NormedCSP);
  pArrayWidgetNPIr->setArrayAnnotation(pResult4NormedRowCSP);
  pArrayWidgetNPIc->setArrayAnnotation(pResult4NormedColumnCSP);
  pArrayWidgetNIIr->setArrayAnnotation(pResult5NormedRowCSP);
}
/**
 * Hide the above buttons if ILDM-tab is currently active.
 **/
void CQTSSAResultSubWidget::hideButtons()
{

  if ((tabWidget2->currentPageIndex() == 1) || (tabWidget2->currentPageIndex() == 2) || (tabWidget2->currentPageIndex() == 3))
    {
      comboBox->setDisabled(true);
    }
  else
    {
      comboBox->setEnabled(true);
    }

  ButtonSaveData->setEnabled(true);

#if 0 //TO REMOVE

  if ((tabWidget2->currentPageIndex() == 3))
    {
      ButtonSaveData->setDisabled(true);
    }
  else
    {
      ButtonSaveData->setEnabled(true);
    }

#endif
}
/**
 * Able / Disable the slider.
 **/
void CQTSSAResultSubWidget::setStepSelectionDisabled(bool set)
{
  mSlider->setDisabled(set);
  mSlider_3->setDisabled(set);
  mSlider_4->setDisabled(set);
}

void CQTSSAResultSubWidget::activateTab(int tab)
{
  tabWidget2->setCurrentPage(tab);
}

void CQTSSAResultSubWidget::changeToCSP()
{
  mILDM = false;
  mILDMModified = false;
  tabWidget2->setTabEnabled(TabPage_ILDM, false);
  tabWidget2->setTabEnabled(TabPage_ILDMM, false);
  tabWidget2->setTabEnabled(TabPage_CSP, true);
  activateTab(3);
}

void CQTSSAResultSubWidget::changeToILDM()
{
  mILDM = true;
  mILDMModified = false;
  tabWidget2->setTabEnabled(TabPage_ILDM, true);
  tabWidget2->setTabEnabled(TabPage_ILDMM, false);
  tabWidget2->setTabEnabled(TabPage_CSP, false);

  //tabWidget2->setTabEnabled(TabPage, true);
  //tabWidget2->setTabEnabled(TabPage_4, false);
  activateTab(1);
}

void CQTSSAResultSubWidget::changeToILDMModified()
{
  mILDM = false;
  mILDMModified = true;
  tabWidget2->setTabEnabled(TabPage_ILDM, false);
  tabWidget2->setTabEnabled(TabPage_ILDMM, true);
  tabWidget2->setTabEnabled(TabPage_CSP, false);
  activateTab(2);
}

void CQTSSAResultSubWidget::changeILDMModifiedInterval()
{
  int step = mSlider_4->value();

  if (step == 1)
    mLabel2_6->setNum(0);
  else
    mLabel2_6->setNum((double)pILDMModifiedMethod->returnCurrentTime(step - 2));

  mLabel4_6->setNum(step);

  pILDMModifiedMethod->setAnnotationM(step);
  pResult_M = pILDMModifiedMethod->getVslowPrintAnn();
  pResult2_M = pILDMModifiedMethod->getVslowMetabPrintAnn();
  pResult3_M = pILDMModifiedMethod->getVslowSpacePrintAnn();
  pResult4_M = pILDMModifiedMethod->getVfastSpacePrintAnn();
  pArrayWidget_5->setArrayAnnotation(pResult_M);
  pArrayWidget2_5->setArrayAnnotation(pResult2_M);
  pArrayWidget3_5->setArrayAnnotation(pResult3_M);
  pArrayWidget4_5->setArrayAnnotation(pResult4_M);
  mpTimeScaleWidgetILDMModified->paintTimeScale(pILDMModifiedMethod->getVec_TimeScale(step));
}

void CQTSSAResultSubWidget::displayCSPDevelopment(bool /* displayCSPTab */)
{
  tabWidget2->removePage(TabPage_CSP);
}

