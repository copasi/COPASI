// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQPLGenerateWidget.h"
#include "qtUtilities.h"
#include "DataModelGUI.h"

#include <QFileDialog>

#include <copasi/utilities/CProfileSettings.h>
#include <copasi/utilities/CProfileGenerator.h>

#include <copasi/core/CRootContainer.h>
#include <copasi/CopasiDataModel/CDataModel.h>
#include <copasi/CopasiTaskTypes.h>

CQPLGenerateWidget::CQPLGenerateWidget(QWidget * parent)
  : QWidget(parent)
  , mpOptTask(NULL)
{
  setupUi(this);

  CTaskEnum::Method validMethods[] = {
    // local
    CTaskEnum::Method::LevenbergMarquardt,
    CTaskEnum::Method::NelderMead,
    CTaskEnum::Method::HookeJeeves,

    // statistic
    CTaskEnum::Method::Statistics,

    // others
    CTaskEnum::Method::DifferentialEvolution,
    CTaskEnum::Method::SRES,
    CTaskEnum::Method::EvolutionaryProgram,
    CTaskEnum::Method::GeneticAlgorithm,
    CTaskEnum::Method::GeneticAlgorithmSR,
    CTaskEnum::Method::NL2SOL,
    CTaskEnum::Method::ParticleSwarm,
    CTaskEnum::Method::Praxis,
    CTaskEnum::Method::RandomSearch,
    CTaskEnum::Method::ScatterSearch,
    CTaskEnum::Method::SimulatedAnnealing,
    CTaskEnum::Method::SteepestDescent,
    CTaskEnum::Method::TruncatedNewton,
    CTaskEnum::Method::UnsetMethod
  };

  mpMethodWidget->setValidMethods(validMethods);
  mpMethodWidget->showMethodParameters(true);
  mpMethodWidget->showMethodCheckbox(true);
}

CQPLGenerateWidget::~CQPLGenerateWidget()
{
  mpMethodWidget->setTask(NULL);
  pdelete(mpOptTask);
}

void CQPLGenerateWidget::loadSettings(const CProfileSettings * pSettings)
{
  if (!pSettings)
    return;

  mpTxtTarget->setText(FROM_UTF8(pSettings->getDirectory()));

  mpTxtPrefix->setText(FROM_UTF8(pSettings->strValue("Prefix")));

  mpTxtScanInterval->setText(QString::number(pSettings->intValue("Generate", "Scan Interval")));
  mpTxtLower->setText(FROM_UTF8(pSettings->strValue("Generate", "Lower Adjustment")));
  mpTxtUpper->setText(FROM_UTF8(pSettings->strValue("Generate", "Upper Adjustment")));
  mpChkDisableTasks->setChecked(pSettings->boolValue("Generate", "Disable Other Tasks"));
  mpChkDisablePlots->setChecked(pSettings->boolValue("Generate", "Disable Other Plots"));
  mpChkLog->setChecked(pSettings->boolValue("Generate", "Logarithmic"));
  mpChkContinue->setChecked(pSettings->boolValue("Generate", "Continue from current State"));
  mpChkRunStatistics->setChecked(pSettings->boolValue("Run Statistics"));
  mpChkDeleteExisting->setChecked(pSettings->boolValue("Delete Existing"));
  bool isPE = pSettings->boolValue("IsParameterEstimation");
  mpChkIsParameterEstimation->setChecked(isPE);

  if (CRootContainer::getDatamodelList()->size() == 0)
    return;

  auto taskName = isPE ? CTaskEnum::TaskName[CTaskEnum::Task::parameterFitting]
  :CTaskEnum::TaskName[CTaskEnum::Task::optimization];
  auto& pDataModel = (*CRootContainer::getDatamodelList())[0];
  mpMethodWidget->setTask(NULL);
  pdelete(mpOptTask);
  mpOptTask = isPE ? new CFitTask(*dynamic_cast< CFitTask * >(&pDataModel.getTaskList()->operator[](taskName)), NO_PARENT)
                   : new COptTask(*dynamic_cast< COptTask * >(&pDataModel.getTaskList()->operator[](taskName)), NO_PARENT);
  int methodType = pSettings->intValue("Generate", "Method", -1);
  if (methodType == -1)
    methodType  = (int)CTaskEnum::MethodName.toEnum(pSettings->strValue("Generate", "Method"), CTaskEnum::Method::NelderMead);
  mpOptTask->setMethodType((CTaskEnum::Method)(methodType));
  if (pSettings->at("Generate").contains("Settings"))
    CProfileSettings::fromJson(mpOptTask->getMethod(), pSettings->at("Generate")["Settings"]);

  mpMethodWidget->setTask(mpOptTask);
  mpMethodWidget->setActiveMethod((CTaskEnum::Method)(methodType));

  mpMethodWidget->loadMethod();
}

void CQPLGenerateWidget::saveSettings(CProfileSettings * pSettings)
{
  if (!pSettings)
    return;

  (*pSettings)["Directory"] = TO_UTF8(mpTxtTarget->text());
  (*pSettings)["Prefix"] = TO_UTF8(mpTxtPrefix->text());
  (*pSettings)["IsParameterEstimation"] = mpChkIsParameterEstimation->isChecked();
  (*pSettings)["Run Statistics"] = mpChkRunStatistics->isChecked();
  (*pSettings)["Delete Existing"] = mpChkDeleteExisting->isChecked();

  auto & generate = (*pSettings)["Generate"];

  generate["Method"] = CTaskEnum::MethodName[mpMethodWidget->getActiveMethodType()];
  generate["Scan Interval"] = mpTxtScanInterval->text().toInt();
  generate["Lower Adjustment"] = TO_UTF8(mpTxtLower->text());
  generate["Upper Adjustment"] = TO_UTF8(mpTxtUpper->text());
  generate["Disable Other Tasks"] = mpChkDisableTasks->isChecked();
  generate["Disable Other Plots"] = mpChkDisablePlots->isChecked();
  generate["Logarithmic"] = mpChkLog->isChecked();
  generate["Continue from current State"] = mpChkContinue->isChecked();

  // save method settings
  if (mpOptTask)
    {
      mpMethodWidget->saveMethod();
      generate["Settings"] = CProfileSettings::toJson(mpOptTask->getMethod());
    }
}

void CQPLGenerateWidget::browseDirectory()
{
  QString dir = QFileDialog::getExistingDirectory(this, "Select Directory", mpTxtTarget->text(), QFileDialog::ShowDirsOnly);
  if (dir.isEmpty())
    return;

  mpTxtTarget->setText(dir);
}

void CQPLGenerateWidget::generateFiles()
{
  CProfileSettings settings;
  saveSettings(&settings);
  CProfileGenerator generator;
  auto * dmGui = getDataModel();
  if (!dmGui)
    return;

  // clear previous messages
  mpTxtMessages->clear();

  if (settings.at("Delete Existing").get<bool>())
  {
    auto dir = QDir(mpTxtTarget->text());
    QStringList filters;
    filters << mpTxtPrefix->text() + "*profile*.cps" // Files containing "profile" and ending with "cps"
            << mpTxtPrefix->text() + "*_high.txt"    // Files ending with "_high.txt"
            << mpTxtPrefix->text() + "*_low.txt";    // Files ending with "_low.txt"

    // Set the name filters on the QDir object
    dir.setNameFilters(filters);

    // Optionally, set filtering options (e.g., only files, not directories)
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot); // To get only files, excluding "." and ".."

    QStringList matchingFiles = dir.entryList(QDir::Files | QDir::NoDotAndDotDot); // Apply filter here too for clarity

    if (!matchingFiles.empty())
    mpTxtMessages->appendPlainText(QString("Found %1 existing files from previous run, deleting as requested:").arg(matchingFiles.count()));

    for (const QString &fileName : matchingFiles) {
      QString fullPath = dir.absoluteFilePath(fileName);
      mpTxtMessages->appendPlainText(QString("Deleting %1").arg(fileName));
      QFile::remove(fullPath);
    }

    mpTxtMessages->appendPlainText("");
  }

  generator.generateProfiles(&settings, dmGui->getDataModel());

  mpTxtMessages->appendPlainText(FROM_UTF8(generator.getMessages()));
}
