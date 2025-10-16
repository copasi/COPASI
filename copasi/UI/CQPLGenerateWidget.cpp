// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
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
    // CTaskEnum::Method::NelderMead,
    // CTaskEnum::Method::LevenbergMarquardt,
    // CTaskEnum::Method::HookeJeeves,
    // CTaskEnum::Method::Statistics,
    CTaskEnum::Method::DifferentialEvolution,
    CTaskEnum::Method::SRES,
    CTaskEnum::Method::EvolutionaryProgram,
    CTaskEnum::Method::GeneticAlgorithm,
    CTaskEnum::Method::GeneticAlgorithmSR,
    CTaskEnum::Method::HookeJeeves,
    CTaskEnum::Method::LevenbergMarquardt,
    CTaskEnum::Method::NL2SOL,
    CTaskEnum::Method::NelderMead,
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

  mpTxtPrefix->setText(FROM_UTF8((*pSettings).at("Prefix").get<std::string>()));

  auto & generate = (*pSettings)["Generate"];
  mpTxtIterations->setText(QString::number(generate.at("Iterations").get<int>()));
  mpTxtScanInterval->setText(QString::number(generate.at("Scan Interval").get<int>()));
  mpTxtLower->setText(FROM_UTF8(generate.at("Lower Adjustment").get<std::string>()));
  mpTxtUpper->setText(FROM_UTF8(generate.at("Upper Adjustment").get<std::string>()));
  mpChkDisableTasks->setChecked(generate.at("Disable Other Tasks").get<bool>());
  mpChkDisablePlots->setChecked(generate.at("Disable Other Plots").get<bool>());
  mpChkRunStatistics->setChecked((*pSettings)["Run Statistics"]);
  mpChkDeleteExisting->setChecked((*pSettings)["Delete Existing"]);
  bool isPE = (*pSettings)["IsParameterEstimation"];
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
  mpMethodWidget->setTask(mpOptTask);
  mpMethodWidget->setActiveMethod((CTaskEnum::Method)(generate.at("Method").get<int>()));
}

void CQPLGenerateWidget::saveSettings(CProfileSettings * pSettings)
{
  if (!pSettings)
    return;

  (*pSettings)["Directory"] = TO_UTF8(mpTxtTarget->text());
  (*pSettings)["IsParameterEstimation"] = mpChkIsParameterEstimation->isChecked();
  (*pSettings)["Run Statistics"] = mpChkRunStatistics->isChecked();
  (*pSettings)["Delete Existing"] = mpChkDeleteExisting->isChecked();

  auto & generate = (*pSettings)["Generate"];

  generate["Prefix"] = TO_UTF8(mpTxtPrefix->text());
  generate["Method"] = (int) mpMethodWidget->getActiveMethodType();
  generate["Iterations"] = mpTxtIterations->text().toInt();
  generate["Scan Interval"] = mpTxtScanInterval->text().toInt();
  generate["Lower Adjustment"] = TO_UTF8(mpTxtLower->text());
  generate["Upper Adjustment"] = TO_UTF8(mpTxtUpper->text());
  generate["Disable Other Tasks"] = mpChkDisableTasks->isChecked();
  generate["Disable Other Plots"] = mpChkDisablePlots->isChecked();

  // save method settings
  if (mpOptTask)
    {
      mpMethodWidget->saveMethod();
      generate["Settings"] = CProfileSettings::toJson(mpOptTask->getMethod());
    }

}

void CQPLGenerateWidget::browseDirectory()
{
  QString dir = QFileDialog::getExistingDirectory(this, "Select Directory", "", QFileDialog::ShowDirsOnly);
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

  if (settings.at("Delete Existing").get<bool>())
  {
    auto dir = QDir(mpTxtTarget->text());
    QStringList filters;
        filters << "*profile*.  cps" // Files containing "profile" and ending with "cps"
                << "*_high.txt"   // Files ending with "_high.txt"
                << "*_low.txt";   // Files ending with "_low.txt"

        // 3. Set the name filters on the QDir object
        dir.setNameFilters(filters);

        // 4. Optionally, set filtering options (e.g., only files, not directories)
        dir.setFilter(QDir::Files | QDir::NoDotAndDotDot); // To get only files, excluding "." and ".."

    QStringList matchingFiles = dir.entryList(QDir::Files | QDir::NoDotAndDotDot); // Apply filter here too for clarity
    for (const QString &fileName : matchingFiles) {
      QString fullPath = dir.absoluteFilePath(fileName);
      mpTxtMessages->appendPlainText(QString("Deleting %1").arg(fileName));
      QFile::remove(fullPath);
    }
  }

  generator.generateProfiles(&settings, dmGui->getDataModel());

  mpTxtMessages->clear();
  mpTxtMessages->setPlainText(FROM_UTF8(generator.getMessages()));
}
