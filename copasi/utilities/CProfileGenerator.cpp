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

#include <copasi/parameterFitting/CFitProblem.h>
#include <copasi/parameterFitting/CExperimentSet.h>

#include <copasi/plot/COutputDefinitionVector.h>

#include <copasi/scan/CScanProblem.h>

#include <copasi/utilities/json.hpp>

void CProfileGenerator::getCurrentSolution()
{
  if (!mpDM || !mpSettings)
    return;

  mCurrentSolution.mIsParameterEstimation = mpSettings->getValue< bool >("IsParameterEstimation");

  auto& task = mCurrentSolution.mIsParameterEstimation ? (*mpDM->getTaskList())["Parameter Estimation"]
                                                         : (*mpDM->getTaskList())["Optimization"];

  auto* pProblem = dynamic_cast<COptProblem*>(task.getProblem());
  
  if (!pProblem)
    return;
  
  // run current solution statistics if needed
  if (mpSettings->getValue< bool >("Run Statistics"))
  {
    auto method = task.getMethod()->getSubType();
    auto report = task.getReport().getTarget();
    auto updateModel = task.isUpdateModel();
    auto calculateStats = pProblem->getCalculateStatistics();
    
    try {
      task.setUpdateModel(true);
      pProblem->setCalculateStatistics(true);
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
  }

}

void CProfileGenerator::saveBaseModel()
{
  if (!mpSettings || !mpDM || !mpGroup)
    return;

  int scanInterval = mpGroup->getValue< int >("Scan Interval");
  int numIterations = mpGroup->getValue< int >("Iterations");

  // change opt method and apply method settings
  auto& task = mCurrentSolution.mIsParameterEstimation ? (*mpDM->getTaskList())["Parameter Estimation"]
                                                       : (*mpDM->getTaskList())["Optimization"];

  task.setMethodType((CTaskEnum::Method) mpGroup->getValue< int >("Method"));

  if (task.getMethod()->getParameter("Iteration Limit"))
    task.getMethod()->getParameter("Iteration Limit")->setValue<int>(numIterations);

  // make the adjustments from the settings
  // disable tasks
  if (mpGroup->getValue< bool >("Disable Other Tasks"))
  {
    // disable all tasks except the one we are interested in
    auto& tasks = *mpDM->getTaskList();
    for (auto& task : tasks)
    {
        task.setScheduled(false);
    }
  }

  // disable existing plots
  if (mpGroup->getValue< bool >("Disable Other Plots"))
  {
    auto& plots = *mpDM->getPlotDefinitionList();
    for (auto& plot : plots)
    {
        plot.setActive(false);
    }
  }

  // disable statistics on opt task
  dynamic_cast<COptProblem*>(task.getProblem())->setCalculateStatistics(false);

  // create scan task
  auto & scanTask = (*mpDM->getTaskList())["Scan"];
  scanTask.setScheduled(true);

  auto* pProblem = dynamic_cast<CScanProblem*>(scanTask.getProblem());

  pProblem->setSubtask(mCurrentSolution.mIsParameterEstimation ? CTaskEnum::Task::parameterFitting
  : CTaskEnum::Task::optimization);
  pProblem->setContinueFromCurrentState(false);
  pProblem->setOutputInSubtask(false);
  pProblem->setOutputSpecification("");
  pProblem->clearScanItems();
  pProblem->addScanItem(CScanProblem::SCAN_LINEAR, scanInterval);


  // save updated base model 
  mpDM->saveModel(mCpsModelFile, NULL, true);

}

double
CProfileGenerator::getValueAdjustment(double value, std::string adjustment, double explicitValue/*=0.0*/, double std_dev/*=0.0*/)
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

  bool has_percent = adjustment.find('%') != std::string::npos;
  double adj_value;
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

  if (has_percent || is_declarative)
    return adj_value;

  return value * adj_value;
}


CProfileGenerator::CProfileGenerator()
  : mpDM(NULL)
  , mpSettings(NULL)
  , mpOptTask(NULL)
  , mpOptProblem(NULL)
  , mpGroup(NULL)
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
  
  // first of all create a copy of the current model
  // save the model in the target directory, including experimental data
  // for parameter estimation tasks

  // create target directory, if it does not exist yet
  mDirectory = mpSettings->getValue< std::string >("Directory");
  if (!CDirEntry::createDir(mDirectory))
    {
      mMessages << "Could not create target directory: " << mDirectory << std::endl;
      return;
    }

  // save original model in target directory
  if (mCurrentSolution.mIsParameterEstimation)
    pDM->copyExperimentalDataTo(mDirectory);

  mCpsModelFile = mDirectory + "/" + mPrefix + "original.cps";
  pDM->saveModel(mCpsModelFile, NULL, true);

  // now create a new data model, and loading the file we just saved
  mpDM = CRootContainer::addDatamodel();
  if (!mpDM->loadFromFile(mCpsModelFile))
    {
      mMessages << "E: Could not load model from file: " << mCpsModelFile << std::endl;
      return;
    }

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

  mpGroup = mpSettings->getGroup("Generate");
  if (!mpGroup)
  {
    mMessages << "Could not find generate settings, stopping." << std::endl;
    return;
  }


  mPrefix = mpGroup->getValue< std::string >("Prefix");

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
  std::string info_file = mDirectory + "/" + mPrefix + "info.json";
  std::ofstream info_stream(info_file);
  info_stream << info.dump(4);
  info_stream.close();


  // now, for each parameter, generate a copasi file with a scan task
  // that runs a scan for the selected parameter while re-optimizing the 
  // other parameters
  mLowerAdjustment = mpGroup->getValue< std::string >("Lower Adjustment");
  mUpperAdjustment = mpGroup->getValue< std::string >("Upper Adjustment");

  auto& task = mCurrentSolution.mIsParameterEstimation ? (*mpDM->getTaskList())["Parameter Estimation"]
                                                         : (*mpDM->getTaskList())["Optimization"];

  auto* pProblem = dynamic_cast<COptProblem*>(task.getProblem());

  CCopasiParameterGroup optItems = *pProblem->getGroup("OptimizationItemList");
  
  for (int i = 0; i < mCurrentSolution.mParameterCNs.size(); ++i)
  {
    auto& cn = mCurrentSolution.mParameterCNs[i];
    auto& name = mCurrentSolution.mParameterNames[i];
    auto& value = mCurrentSolution.mParameterValues[i];
    auto& std_dev = mCurrentSolution.mParameterSDs[i];

    auto adjusted_lower = getValueAdjustment(value, mLowerAdjustment, value, std_dev);
    auto adjusted_upper = getValueAdjustment(value, mUpperAdjustment, value, std_dev);

    auto scan_interval = mpGroup->getValue< int >("Scan Interval");
    auto num_iterations = mpGroup->getValue< int >("Iterations");

    // remove the opt items for the current cn
    
    auto* list = pProblem->getGroup("OptimizationItemList");
    *list = optItems;
    pProblem->elevateChildren();
    
    list = pProblem->getGroup("OptimizationItemList");

    mMessages << "Number of Parameters to optimize: " << list->size() << std::endl;
    for (int g = list->size() - 1; g >= 0; --g)
    {
      auto *current = dynamic_cast<COptItem*>( list->getParameter(g));
      if (!current)
      {
        // this item is invalid, get rid of it now
        list->removeParameter(g);
        continue;
      }
      if (current->getObjectCN() == cn)
      {
        list->removeParameter(g);
        break;
      }
    }
    
    mMessages << "Number of Parameters left to optimize: " << list->size() << std::endl;
    
    // add to message log
    mMessages << "Generating profiles for parameter " << name << " with value " << value << " and std_dev " << std_dev << std::endl;
    mMessages << "Adjusted lower: " << adjusted_lower << ", adjusted upper: " << adjusted_upper << std::endl;

    
    auto& scan_task = (*mpDM->getTaskList())["Scan"];

    auto* pProblem = dynamic_cast<CScanProblem*>(scan_task.getProblem());

    std::string direction = "high";

    pProblem->clearScanItems();
    auto *item = pProblem->addScanItem(CScanProblem::SCAN_LINEAR, scan_interval);
    item->setValue("Object", CRegisteredCommonName(cn));
    item->setValue("Minimum", value);
    item->setValue("Maximum", adjusted_upper);
    item->setValue("log", false);

    scan_task.updateMatrices();
    
    auto* plot = COutputAssistant::createDefaultOutput(251, &scan_task, mpDM);
    if (plot)
    plot->setObjectName(std::string("opt = ") + std::to_string(value));
    
    auto* report = COutputAssistant::createDefaultOutput(1251, &scan_task, mpDM);
    scan_task.getReport().setTarget(mDirectory + "/" + mPrefix + "profile_" + std::to_string(i) + "_" + direction + ".txt");
    dynamic_cast<CReportDefinition*>(report)->setPrecision(10);
    scan_task.getReport().setAppend(false);
    scan_task.getReport().setConfirmOverwrite(false);


    // save the model as file with the index and parameter name
    std::string filename = mDirectory + "/" + mPrefix + "profile_" + std::to_string(i) + "_" + direction + ".cps";
    mpDM->saveModel(filename, NULL, true);

    // remove the report
    mpDM->getReportDefinitionList()->removeReportDefinition(report->getKey());

    // now the other direction
    direction = "low";
    pProblem->clearScanItems();
    item = pProblem->addScanItem(CScanProblem::SCAN_LINEAR, scan_interval);
    item->setValue("Object", CRegisteredCommonName(cn));
    item->setValue("Minimum", adjusted_lower);
    item->setValue("Maximum", value);
    item->setValue("log", false);

    scan_task.updateMatrices();
    report = COutputAssistant::createDefaultOutput(1251, &scan_task, mpDM);
    dynamic_cast<CReportDefinition*>(report)->setPrecision(10);
    scan_task.getReport().setTarget(mDirectory + "/" + mPrefix + "profile_" + std::to_string(i) + "_" + direction + ".txt");

    filename = mDirectory + "/" + mPrefix + "profile_" + std::to_string(i) + "_" + direction + ".cps";
    mpDM->saveModel(filename, NULL, true);
    // remove the report
    mpDM->getReportDefinitionList()->removeReportDefinition(report->getKey());

  }

}

std::string CProfileGenerator::getMessages() const
{
  return mMessages.str();
}
