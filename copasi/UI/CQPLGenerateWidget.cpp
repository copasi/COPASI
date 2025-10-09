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
{
  setupUi(this);
  
  CTaskEnum::Method validMethods[] = {
    CTaskEnum::Method::NelderMead,
    CTaskEnum::Method::LevenbergMarquardt,
    CTaskEnum::Method::HookeJeeves,
    CTaskEnum::Method::Statistics,
    CTaskEnum::Method::UnsetMethod
  };
  
  mpMethodWidget->setValidMethods(validMethods);
  mpMethodWidget->showMethodParameters(true);
  mpMethodWidget->showMethodCheckbox(true);
}

void CQPLGenerateWidget::loadSettings(const CProfileSettings * pSettings)
{
  if (!pSettings)
    return;

  mpTxtTarget->setText(FROM_UTF8(pSettings->getDirectory()));
  auto * pGroup = pSettings->getGroup("Generate");
  if (!pGroup)
    return;

  mpTxtPrefix->setText(FROM_UTF8(pGroup->getValue<std::string>("Prefix")));
  mpTxtIterations->setText(QString::number(pGroup->getValue< int >("Iterations")));
  mpTxtScanInterval->setText(QString::number(pGroup->getValue< int >("Scan Interval")));
  mpTxtLower->setText(FROM_UTF8(pGroup->getValue< std::string >("Lower Adjustment")));
  mpTxtUpper->setText(FROM_UTF8(pGroup->getValue< std::string >("Upper Adjustment")));
  mpChkDisableTasks->setChecked(pGroup->getValue< bool >("Disable Other Tasks"));
  mpChkDisablePlots->setChecked(pGroup->getValue< bool >("Disable Other Plots"));
  mpChkRunStatistics->setChecked(pSettings->getValue< bool >("Run Statistics"));
  mpChkDeleteExisting->setChecked(pSettings->getValue< bool >("Delete Existing"));
  bool isPE = pSettings->getValue< bool >("IsParameterEstimation");
  mpChkIsParameterEstimation->setChecked(isPE);
  
  if (CRootContainer::getDatamodelList()->size() == 0)
    return;
  
  auto taskName = isPE ? CTaskEnum::TaskName[CTaskEnum::Task::parameterFitting]
  :CTaskEnum::TaskName[CTaskEnum::Task::optimization];
  auto& pDataModel = (*CRootContainer::getDatamodelList())[0];
  mpMethodWidget->setTask(dynamic_cast<CCopasiTask*>(&pDataModel.getTaskList()->operator[](taskName)));
  mpMethodWidget->setActiveMethod((CTaskEnum::Method)(pGroup->getValue<int>("Method")));
}

void CQPLGenerateWidget::saveSettings(CProfileSettings * pSettings)
{
  if (!pSettings)
    return;

  pSettings->setValue< std::string >("Directory", TO_UTF8(mpTxtTarget->text()));
  pSettings->setValue< bool >("IsParameterEstimation", mpChkIsParameterEstimation->isChecked());
  pSettings->setValue< bool >("Run Statistics", mpChkRunStatistics->isChecked());
  pSettings->setValue< bool >("Delete Existing", mpChkDeleteExisting->isChecked());
  
  auto * pGroup = pSettings->getGroup("Generate");
  if (!pGroup)
    return;

  pGroup->setValue< std::string >("Prefix", TO_UTF8(mpTxtPrefix->text()));
  pGroup->setValue< int >("Method", (int) mpMethodWidget->getActiveMethodType());
  pGroup->setValue< int >("Iterations", mpTxtIterations->text().toInt());
  pGroup->setValue< int >("Scan Interval", mpTxtScanInterval->text().toInt());
  pGroup->setValue< std::string >("Lower Adjustment", TO_UTF8(mpTxtLower->text()));
  pGroup->setValue< std::string >("Upper Adjustment", TO_UTF8(mpTxtUpper->text()));
  pGroup->setValue< bool >("Disable Other Tasks", mpChkDisableTasks->isChecked());
  pGroup->setValue< bool >("Disable Other Plots", mpChkDisablePlots->isChecked());
  
  
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

  if (settings.getValue<bool>("Delete Existing"))
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
      QFile::remove(fullPath);
    }
  }
  
  generator.generateProfiles(&settings, dmGui->getDataModel());

  mpTxtMessages->clear();
  mpTxtMessages->setPlainText(FROM_UTF8(generator.getMessages()));
}
