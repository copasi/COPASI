// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CProfileGenerator.h"

#include "CProfileSettings.h"
#include "CDirEntry.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CDataVector.h"
#include "copasi/core/CRootContainer.h"
#include "CCopasiTask.h"
#include "CCopasiMethod.h"

#include <copasi/utilities/CCopasiException.h>
#include <copasi/report/CReportDefinitionVector.h>
#include <copasi/report/COutputAssistant.h>

#include <copasi/optimization/COptTask.h>
#include <copasi/optimization/COptProblem.h>
#include <copasi/optimization/COptItem.h>

#include <copasi/parameterFitting/CFitTask.h>
#include <copasi/parameterFitting/CFitProblem.h>
#include <copasi/parameterFitting/CExperimentSet.h>

#include <copasi/plot/COutputDefinitionVector.h>

#include <copasi/scan/CScanProblem.h>

#include <copasi/utilities/json.hpp>

#include <iomanip>
#include <sstream>

std::string zeroPad(int number, int width)
{
  std::ostringstream oss;
  oss << std::setw(width) << std::setfill('0') << number;
  return oss.str();
}

void CProfileGenerator::getCurrentSolution()
{
  if (!mpDM || !mpSettings)
    return;

  mCurrentSolution.mIsParameterEstimation = (*mpSettings)["IsParameterEstimation"];

  auto& task = mCurrentSolution.mIsParameterEstimation ? (*mpDM->getTaskList())["Parameter Estimation"]
                                                         : (*mpDM->getTaskList())["Optimization"];

  auto* pProblem = dynamic_cast<COptProblem*>(task.getProblem());

  if (!pProblem)
    return;

  // run current solution statistics if needed
  if ((*mpSettings)["Run Statistics"])
  {
    auto method = task.getMethod()->getSubType();
    auto report = task.getReport().getTarget();
    auto updateModel = task.isUpdateModel();
    auto calculateStats = pProblem->getCalculateStatistics();

    try {
      task.setUpdateModel(true);
      pProblem->setCalculateStatistics(true);
      pProblem->setRandomizeStartValues(false);
      task.setMethodType(CTaskEnum::Method::Statistics);
      task.getReport().setTarget("");

      task.initialize(CCopasiTask::OUTPUT_UI, NULL, NULL);
      task.process(true);
      task.restore();
    }
    catch(const CCopasiException& ex)
    {
      mMessages << "Running the solution statistics failed with " << ex.getMessage().getText();
    }
    catch (...) {
      mMessages << "Running the solution statistics failed";
    }

    // restore values
    task.setUpdateModel(updateModel);
    pProblem->setCalculateStatistics(calculateStats);
    task.setMethodType(method);
    task.getReport().setTarget(report);
  }

  // retrieve current solution

  mCurrentSolution.mObjectiveValue = pProblem->getSolutionValue();
  mMessages << "Task is " << (mCurrentSolution.mIsParameterEstimation ? "Parameter Estimation" : "Optimization") << std::endl;
  mMessages << "Objective value: " << mCurrentSolution.mObjectiveValue << std::endl;

  mCurrentSolution.mParameterCNs.clear();
  mCurrentSolution.mParameterValues.clear();
  mCurrentSolution.mParameterSDs.clear();
  mCurrentSolution.mParameterNames.clear();

  const CVector< C_FLOAT64 > * stddeves = NULL;
  if (mCurrentSolution.mIsParameterEstimation)
    {
      auto* pFitProblem = dynamic_cast< CFitProblem * >(pProblem);
      stddeves = &(pFitProblem->getVariableStdDeviations());
      if (stddeves->size() == 0)
      {
          mMessages << "No standard deviations available, ignoring." << std::endl;
          stddeves = NULL;
      }

      mCurrentSolution.mNumDataPoints = pFitProblem->getExperimentSet().getValidValueCount();
    }

  auto& parameters = pProblem->getOptItemList();
  for (int i = 0; i < parameters.size(); ++i)
  {
    auto * item = parameters[i];
    auto & cn = item->getObjectCN();
    mCurrentSolution.mParameterCNs.push_back(cn);

    auto * obj = mpDM->getObject(cn);
    if (!obj)
      {
        mMessages << "Could not find object for fitItem: " << cn << " ignoring." << std::endl;
        continue;
      }

    mCurrentSolution.mParameterNames.push_back(obj->getObjectDisplayName());
    mCurrentSolution.mParameterValues.push_back(item->getStartValue());
    if (stddeves && stddeves->size() > i)
      mCurrentSolution.mParameterSDs.push_back(stddeves->operator[](i));
    else
      mCurrentSolution.mParameterSDs.push_back(std::numeric_limits< double >::quiet_NaN());
  }
}

void CProfileGenerator::saveBaseModel()
{
  if (!mpSettings || !mpDM || !mpSettings)
    return;

  auto & generate = (*mpSettings)["Generate"];
  int scanInterval = generate.at("Scan Interval").get<int>();

  // change opt method and apply method settings
  auto& task = mCurrentSolution.mIsParameterEstimation ? (*mpDM->getTaskList())["Parameter Estimation"]
                                                       : (*mpDM->getTaskList())["Optimization"];

  auto settingsStr = mpSettings->dump(4);

  int methodType = mpSettings->intValue("Generate", "Method", -1);
  if (methodType == -1)
    methodType = (int) CTaskEnum::MethodName.toEnum(mpSettings->strValue("Generate", "Method"), CTaskEnum::Method::NelderMead);

  task.setMethodType((CTaskEnum::Method) methodType);
  // apply method specific parameters
  if (generate.contains("Settings"))
  {
      CProfileSettings::fromJson(task.getMethod(), generate.at("Settings"));
  }

  // make the adjustments from the settings
  // disable tasks
  if (generate.at("Disable Other Tasks").get<bool>())
  {
    // disable all tasks except the one we are interested in
    auto& tasks = *mpDM->getTaskList();
    for (auto& task : tasks)
    {
        task.setScheduled(false);
    }
  }

  // disable existing plots
  if (generate.at("Disable Other Plots").get<bool>())
  {
    auto& plots = *mpDM->getPlotDefinitionList();
    for (auto& plot : plots)
    {
        plot.setActive(false);
    }
  }

  // disable statistics on opt task
  dynamic_cast<COptProblem*>(task.getProblem())->setCalculateStatistics(false);
  // disable random start values!
  dynamic_cast< COptProblem * >(task.getProblem())->setRandomizeStartValues(false);

  // create scan task
  auto & scanTask = (*mpDM->getTaskList())["Scan"];
  scanTask.setScheduled(true);

  auto* pProblem = dynamic_cast<CScanProblem*>(scanTask.getProblem());

  pProblem->setSubtask(mCurrentSolution.mIsParameterEstimation ? CTaskEnum::Task::parameterFitting
  : CTaskEnum::Task::optimization);
  pProblem->setContinueFromCurrentState(generate.at("Continue from current State").get< bool >());
  pProblem->setOutputInSubtask(false);
  pProblem->setOutputSpecification("");
  pProblem->clearScanItems();
  pProblem->addScanItem(CScanProblem::SCAN_LINEAR, scanInterval);

  // save updated base model
  mpDM->saveModel(mCpsModelFile, NULL, true);
}

double
CProfileGenerator::getValueAdjustment(double value, std::string adjustment, double explicitValue /*=0.0*/, double std_dev /*=0.0*/)
{
  if (adjustment.empty() || adjustment == "default")
    return explicitValue;

  if (adjustment.length() > 2 && adjustment.substr(adjustment.length() - 2) == "SD" && std_dev != 0.0)
    return value + std::stod(adjustment.substr(0, adjustment.length() - 2)) * std_dev;

  bool is_additive = adjustment[0] == '+';
  if (is_additive)
    adjustment = adjustment.substr(1);

  bool is_declarative = adjustment[0] == '=';
  if (is_declarative)
    adjustment = adjustment.substr(1);

  bool is_multiplicative = adjustment[0] == '*';
  if (is_multiplicative)
    adjustment = adjustment.substr(1);

  bool has_percent = adjustment.find('%') != std::string::npos;
  double adj_value;
  try
    {
      if (has_percent)
        {
          adj_value = std::stod(adjustment.substr(0, adjustment.find('%'))) / 100.0;
          adj_value *= value;
        }
      else
        {
          adj_value = std::stod(adjustment);
        }

      if ((adj_value < 0 || is_additive) && !is_declarative)
        return value + adj_value;

      if (is_multiplicative)
        return value * adj_value;

      return adj_value;
    }
  catch (std::invalid_argument &)
    {
      // leave value unadjusted.
      return value;
    }
}

CProfileGenerator::CProfileGenerator()
  : mpDM(NULL)
  , mpSettings(NULL)
  , mpOptTask(NULL)
  , mpOptProblem(NULL)
{
}

CProfileGenerator::~CProfileGenerator()
{
}

void CProfileGenerator::generateProfiles(CProfileSettings * pSettings, CDataModel * pDM)
{
  if (!pSettings || !pDM)
    return;

  mpSettings = pSettings;

  // save settings
  mpSettings->save();

  // first of all create a copy of the current model
  // save the model in the target directory, including experimental data
  // for parameter estimation tasks

  // create target directory, if it does not exist yet
  mDirectory = (*mpSettings)["Directory"];
  if (!CDirEntry::createDir(mDirectory))
    {
      mMessages << "Could not create target directory: " << mDirectory << std::endl;
      return;
    }

  mPrefix = (*mpSettings)["Prefix"];

  // save original model in target directory
  mCpsModelFile = mDirectory + "/" + mPrefix + "original.cps";
  auto oldFileName = pDM->getFileName();

  // if parameter estimation, store original experiment filenames
  {
    std::vector< std::string > originalExperimentFiles;
    auto * task = dynamic_cast< CFitTask * >(&pDM->getTaskList()->operator[](CTaskEnum::TaskName[CTaskEnum::Task::parameterFitting]));
    auto * problem = dynamic_cast< CFitProblem * >(task->getProblem());
    auto & expSet = problem->getExperimentSet();
    if (mCurrentSolution.mIsParameterEstimation)
      {
        originalExperimentFiles = expSet.getFileNamesOnly();
      }

    // save model
    pDM->saveModel(mCpsModelFile, NULL, true);

    // restore original filenames
    pDM->setFileName(oldFileName);
    if (mCurrentSolution.mIsParameterEstimation)
      {
        expSet.setFileNames(originalExperimentFiles);
      }
  }

  // now create a new data model, and loading the file we just saved
  mpDM = CRootContainer::addDatamodel();
  if (!mpDM->loadFromFile(mCpsModelFile))
    {
      mMessages << "E: Could not load model from file: " << mCpsModelFile << std::endl;
      return;
    }

  // save original model in target directory
  if (mCurrentSolution.mIsParameterEstimation)
    mpDM->copyExperimentalDataTo(mDirectory, mPrefix, true);

  mpDM->saveModel(mCpsModelFile, NULL, true);

  // get current solution
  getCurrentSolution();

  // sanity check, stop if objective value is inf, nan or max double
  if (std::isinf(mCurrentSolution.mObjectiveValue)
    || std::isnan(mCurrentSolution.mObjectiveValue)
    || mCurrentSolution.mObjectiveValue == std::numeric_limits<double>::max())
  {
      mMessages << "objective value seems bad, generate profiles for good fits only, stopping." << std::endl;
      return;
  }

  // stop if no parameters are selected
  if (mCurrentSolution.mParameterCNs.empty())
  {
    mMessages << "no opt items defined, stopping." << std::endl;
    return;
  }

  saveBaseModel();

  // create a nlohman::json object to store the information about the run
  nlohmann::json info;
  info["num_params"] = mCurrentSolution.mParameterCNs.size();
  info["num_data"] = mCurrentSolution.mNumDataPoints;
  info["obj"] = mCurrentSolution.mObjectiveValue;
  info["param_sds"] = mCurrentSolution.mParameterSDs;
  info["param_values"] = mCurrentSolution.mParameterValues;
  info["param_names"] = mCurrentSolution.mParameterNames;

  // save as '.info.json' in the target directory
  {
    std::string info_file = mDirectory + "/" + mPrefix + "info.json";
    std::ofstream info_stream(info_file);
    info_stream << info.dump(4);
    info_stream.close();
  }

  // save settings in the target directory
  {
    std::string settings_file = mDirectory + "/" + mPrefix + "settings.json";
    std::ofstream settings_stream(settings_file);
    settings_stream << mpSettings->dump(4);
    settings_stream.close();
  }

  // now, for each parameter, generate a copasi file with a scan task
  // that runs a scan for the selected parameter while re-optimizing the
  // other parameters
  mLowerAdjustment = (*mpSettings)["Generate"].at("Lower Adjustment").get<std::string>();
  mUpperAdjustment = (*mpSettings)["Generate"].at("Upper Adjustment").get<std::string>();

  auto& optTask = dynamic_cast<COptTask&> ((*mpDM->getTaskList())["Optimization"]);
  auto & fitTask = dynamic_cast< CFitTask & >((*mpDM->getTaskList())["Parameter Estimation"]);
  auto * pFitProblem = dynamic_cast< CFitProblem * >(fitTask.getProblem());

  auto& task = mCurrentSolution.mIsParameterEstimation ? fitTask
                                                         : optTask;

  auto* pProblem = dynamic_cast<COptProblem*>(task.getProblem());

  CCopasiParameterGroup optItems = *pProblem->getGroup("OptimizationItemList");
  mMessages << "Number of Parameters to optimize: " << optItems.size() << std::endl;

  auto itemsJson = CProfileSettings::toJson(&optItems);

  bool haveAffected = false;

  for (int i = 0; i < mCurrentSolution.mParameterCNs.size(); ++i)
  {
    auto& cn = mCurrentSolution.mParameterCNs[i];
    auto& name = mCurrentSolution.mParameterNames[i];
    auto& value = mCurrentSolution.mParameterValues[i];
    auto& std_dev = mCurrentSolution.mParameterSDs[i];

    auto adjusted_lower = getValueAdjustment(value, mLowerAdjustment, value, std_dev);
    auto adjusted_upper = getValueAdjustment(value, mUpperAdjustment, value, std_dev);

    auto scan_interval = (*mpSettings)["Generate"].at("Scan Interval").get<int>();
    auto num_iterations = (*mpSettings)["Generate"].at("Iterations").get<int>();

    auto * list = pProblem->getGroup("OptimizationItemList");

    // remove all
    for (int g = (int)list->size() - 1; g >= 0; --g)
      list->removeParameter(g);

    std::string itemName = mCurrentSolution.mIsParameterEstimation ? "FitItem" : "OptimizationItem";

    // recreate from array
    for (const auto & current : itemsJson[itemName])
    {
      auto currentCN = current["ObjectCN"].get< std::string >();

      // skip current cn
      if (cn == currentCN)
        continue;

      auto start_value = current["StartValue"].get< double >();
      auto upper_bound = CRegisteredCommonName(current["UpperBound"].get< std::string >());
      auto lower_bound = CRegisteredCommonName(current["LowerBound"].get< std::string >());

      auto & newItem = mCurrentSolution.mIsParameterEstimation ?
        pFitProblem->addFitItem(CRegisteredCommonName(currentCN)) :
        pProblem->addOptItem(CRegisteredCommonName(currentCN));
      newItem.setStartValue(start_value);
      newItem.setLowerBound(lower_bound);
      newItem.setUpperBound(upper_bound);

      if (!mCurrentSolution.mIsParameterEstimation)
        continue;

      auto& pFitItem = dynamic_cast< CFitItem & >(newItem);
      auto affected_cross_validation_experiments = current["Affected Cross Validation Experiments"];
      auto affected_experiments = current["Affected Experiments"];
      if (!affected_experiments.is_null() && affected_experiments.contains("Experiment Key"))
      {
          std::vector< std::string > keys;
          try
          {
              keys = affected_experiments["Experiment Key"].get< std::vector< std::string > >();
          }
          catch (...)
          {
              keys.push_back(affected_experiments["Experiment Key"].get< std::string >());
          }
          for (const auto & entry : keys)
          {
            pFitItem.addExperiment(entry);
            haveAffected = true;
          }
      }

      if (!affected_cross_validation_experiments.is_null() && affected_cross_validation_experiments.contains("Experiment Key"))
        {
          std::vector< std::string > keys;
          try
            {
              keys = affected_cross_validation_experiments["Experiment Key"].get< std::vector< std::string > >();
            }
          catch (...)
            {
              keys.push_back(affected_cross_validation_experiments["Experiment Key"].get< std::string >());
            }
          for (const auto & entry : keys)
            pFitItem.addCrossValidation(entry);
        }
    }

    mMessages << "Number of Parameters left to optimize: " << list->size() << std::endl;

    // add to message log
    mMessages << "Generating profiles for parameter " << name << " with value " << value << " and std_dev " << std_dev << std::endl;
    mMessages << "Adjusted lower: " << adjusted_lower << ", adjusted upper: " << adjusted_upper << std::endl;

    // add warning
    if (adjusted_lower > value)
      mMessages << "WARNING: lower value is greater than the current best value. The lower scan will be invalid." << std::endl;

    if (adjusted_upper < value)
      mMessages << "WARNING: upper value is smaller than the current best value. The upper scan will be invalid." << std::endl;

    auto& scan_task = (*mpDM->getTaskList())["Scan"];

    auto* pProblem = dynamic_cast<CScanProblem*>(scan_task.getProblem());

    std::string direction = "high";

    pProblem->clearScanItems();
    auto *item = pProblem->addScanItem(CScanProblem::SCAN_LINEAR, scan_interval);
    item->setValue("Object", CRegisteredCommonName(cn));
    item->setValue("Minimum", value);
    item->setValue("Maximum", adjusted_upper);
    item->setValue("log", (*mpSettings)["Generate"].at("Logarithmic").get<bool>());

    scan_task.updateMatrices();

    auto * plot = COutputAssistant::createDefaultOutput(mCurrentSolution.mIsParameterEstimation ? 251 : 252, &scan_task, mpDM);
    if (plot)
    plot->setObjectName(std::string("opt = ") + std::to_string(value));

    auto * report = COutputAssistant::createDefaultOutput(mCurrentSolution.mIsParameterEstimation ? 1251 : 1252, &scan_task, mpDM);
    scan_task.getReport().setTarget(mDirectory + "/" + mPrefix + "profile_" + zeroPad(i,5) + "_" + direction + ".txt");
    dynamic_cast<CReportDefinition*>(report)->setPrecision(10);
    scan_task.getReport().setAppend(false);
    scan_task.getReport().setConfirmOverwrite(false);

    // save the model as file with the index and parameter name
    std::string filename = mDirectory + "/" + mPrefix + "profile_" + zeroPad(i,5) + "_" + direction + ".cps";
    mpDM->saveModel(filename, NULL, true);

    // remove the report
    mpDM->getReportDefinitionList()->removeReportDefinition(report->getKey());

    // remove the plot
    if (plot)
    mpDM->getPlotDefinitionList()->removePlotSpec(plot->getKey());

    // now the other direction
    direction = "low";
    pProblem->clearScanItems();
    item = pProblem->addScanItem(CScanProblem::SCAN_LINEAR, scan_interval);
    item->setValue("Object", CRegisteredCommonName(cn));
    item->setValue("Minimum", adjusted_lower);
    item->setValue("Maximum", value);
    item->setValue("log", false);

    scan_task.updateMatrices();

    plot = COutputAssistant::createDefaultOutput(mCurrentSolution.mIsParameterEstimation ? 251 : 252, &scan_task, mpDM);
    if (plot)
      plot->setObjectName(std::string("opt = ") + std::to_string(value));

    report = COutputAssistant::createDefaultOutput(mCurrentSolution.mIsParameterEstimation ? 1251 : 1252, &scan_task, mpDM);
    dynamic_cast<CReportDefinition*>(report)->setPrecision(10);
    scan_task.getReport().setTarget(mDirectory + "/" + mPrefix + "profile_" + zeroPad(i,5) + "_" + direction + ".txt");

    filename = mDirectory + "/" + mPrefix + "profile_" + zeroPad(i,5) + "_" + direction + ".cps";
    mpDM->saveModel(filename, NULL, true);
    // remove the report
    mpDM->getReportDefinitionList()->removeReportDefinition(report->getKey());
    // remove the plot
    if (plot)
      mpDM->getPlotDefinitionList()->removePlotSpec(plot->getKey());
  }

  if (haveAffected)
    mMessages << "WARNING: the model uses parameters specific to certain experiments, this can currently not be run independent of other experiments. " << std::endl;
}

std::string CProfileGenerator::getMessages() const
{
  return mMessages.str();
}
