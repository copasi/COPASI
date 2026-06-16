// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <sstream>
#include <initializer_list>

#include "COutputAssistant.h"
#include "copasi/core/CDataObject.h"
#include "CReportDefinition.h"
#include "CReportDefinitionVector.h"

#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/steadystate/CSteadyStateProblem.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CObjectLists.h"
#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/plot/COutputDefinitionVector.h"
#include "copasi/plot/CPlotColors.h"
#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/parameterFitting/CExperimentSet.h"
#include "copasi/parameterFitting/CExperiment.h"
#include "copasi/scan/CScanProblem.h"
#include "copasi/optimization/COptProblem.h"
#include "copasi/plot/CPlotItem.h"
#include "copasi/output/COutputHandler.h"

#include <copasi/core/CDataArray.h>

//******* COutputAssistant **********************************

//static member variables
COutputAssistant::Map COutputAssistant::mMap;
const std::string COutputAssistant::emptyString("");
const CDefaultOutputDescription COutputAssistant::emptyItem;

//static
std::vector<C_INT32> COutputAssistant::getListOfDefaultOutputDescriptions(const CCopasiTask * task)
{
  //initializes the map on first call only
  initialize();

  std::vector<C_INT32> ret;

  //problem = NULL; //DEBUG only!!!

  //if (!problem) //generate full list
  //  {

  Map::const_iterator it, itEnd = mMap.end();

  for (it = mMap.begin(); it != itEnd; ++it)
    {
      if (!task) //if no task is specified add all descriptions
        {
          ret.push_back(it->first);
        }
      else if (task->getType() == it->second.mTaskType || it->second.mTaskType == CTaskEnum::Task::UnsetTask ||
               (task->getType() == CTaskEnum::Task::crosssection && it->second.mTaskType == CTaskEnum::Task::timeCourse)
              )
        //add descriptions with matching task type
        {
          //if (secondaryTask matches) TODO
          ret.push_back(it->first);
        }
    }

  return ret;
}

//static
C_INT32 COutputAssistant::getDefaultReportIndex(const CCopasiProblem * problem)
{
  if (!problem) return - 1;

  switch (problem->getType())
    {
      case CTaskEnum::Task::steadyState:
        return 1000;

      case CTaskEnum::Task::timeCourse:
        return 1000;

      default:
        return - 1;
    }
}

//       steadyState = 0,
//       timeCourse,
//       scan,
//       fluxMode,
//       optimization,
//       parameterFitting,
//       mca,
//       lyap,
// #ifdef COPASI_DEBUG
//       tss,
// #endif // COPASI_DEBUG
//       sens,
// #ifdef COPASI_SSA
//       ssa,
// #endif // COPASI_SSA
//       unset,

//static
C_INT32 COutputAssistant::getDefaultPlotIndex(const CCopasiProblem * problem)
{
  if (!problem) return - 1;

  switch (problem->getType())
    {
      case CTaskEnum::Task::steadyState:
        return 0;

      case CTaskEnum::Task::timeCourse:
        return 0;

      default:
        return - 1;
    }
}

//static
const std::string & COutputAssistant::getItemName(C_INT32 id)
{
  Map::const_iterator it = mMap.find(id);

  if (it == mMap.end())
    return emptyString;
  else
    return it->second.name;
}

//static
const CDefaultOutputDescription & COutputAssistant::getItem(C_INT32 id)
{
  Map::const_iterator it = mMap.find(id);

  if (it == mMap.end())
    return emptyItem;
  else
    return it->second;
}

C_INT32
COutputAssistant::findItemByName(const std::string& name, bool isPlot /*= true*/)
{
  if (mMap.empty())
    initialize();

  for (auto & entry : mMap)
    {
      if (entry.second.isPlot == isPlot && entry.second.name == name)
        return entry.first;
    }

  return -1;
}

/**
 numbering scheme:

 0-99: time course plots
200-299: plots with scan parameter on x-axis

above 1000: reports

1000-1099: reports with time and some other variables
1200-1299: reports with scan parameters and some other variables

the meaning of the last two digits should be the same in all those cases.

Special plots, e.g. for parameter estimation, use numbers 900-998.
 **/

//static
bool COutputAssistant::initialize()
{
  //if map is already constructed do nothing
  if (mMap.size()) return true;

  std::pair<C_INT32, CDefaultOutputDescription> tmp;

  //first the plots
  tmp.first = -1;
  tmp.second.name = "-- Plots";
  tmp.second.description = "";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::UnsetTask;
  mMap.insert(tmp);

  //concentrations plot
  tmp.first = 0;
  tmp.second.name = "Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of the variable species concentrations, variable compartment volumes, and variable global quantity values vs. time.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  //particle numbers plot
  tmp.first = 1;
  tmp.second.name = "Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of the variable species particle numbers, variable compartment volumes, and variable global quantity values vs. time.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  //complete concentrations plot
  tmp.first = 2;
  tmp.second.name = "Complete Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of all the species concentrations, compartment volumes, and all global quantity values vs. time (includes fixed ones).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  //complete particle numbers plot
  tmp.first = 3;
  tmp.second.name = "Complete Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of all the species particle numbers, compartment volumes, and global quantity values vs. time (includes fixed ones).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  //concentration rate plot
  tmp.first = 4;
  tmp.second.name = "Concentration Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A plot of the rate of change of concentrations of species, compartment volume, and global quantities, which are determined by ODEs or reactions vs. time.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  //particle rate plot
  tmp.first = 5;
  tmp.second.name = "Particle Number Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A plot of the rate of change of particle numbers of all species, compartment volume, and global quantities, which are determined by ODEs or reactions vs. time.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  //reaction particle flux
  tmp.first = 6;
  tmp.second.name = "Reaction Fluxes";
  tmp.second.description = "A plot of the fluxes of all reactions vs. time, in concentration/time unit.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  //reaction particle flux
  tmp.first = 7;
  tmp.second.name = "Reaction Event Fluxes";
  tmp.second.description = "A plot of the fluxes of all reactions vs. time, in reaction events/time unit.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  //fitting result plots
  tmp.first = 910;
  tmp.second.name = "Parameter Estimation Result";
  tmp.second.description = "Curves of all dependent values of all experiments are created in one plot. For each dependent value the experimental data, the fitted curve, and the weighted error are shown.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::parameterFitting;
  tmp.second.options = {
    {"Measured Values", true, "Displays Measured Values"},
    {"Fitted Values", true, "Displays Fitted Values"},
    {"Weighted Errors", false, "Displays Weighted Errors"},
    {"Validation Measured", false, "Displays Validation Data"},
    {"Validation Fitted", false, "Displays Validation Fitted Values"},
    {"Validation Errors", false, "Displays Weighted Validation Errors"},
  };
  mMap.insert(tmp);

  //fitting result plots
  tmp.first = 911;
  tmp.second.name = "Plots of Parameter Estimation Results per Experiment";
  tmp.second.description = "For each experiment of the parameter estimation a plot is created. Each plot contains the experimental data, the fitted curve, and the weighted error for each dependent value.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::parameterFitting;
  tmp.second.options = {
    {"Measured Values", true, "Displays Measured Values"},
    {"Fitted Values", true, "Displays Fitted Values"},
    {"Weighted Errors", false, "Displays Weighted Errors"},
    {"Validation Measured", false, "Displays Validation Data"},
    {"Validation Fitted", false, "Displays Validation Fitted Values"},
    {"Validation Errors", false, "Displays Weighted Validation Errors"},
  };
  mMap.insert(tmp);

  //fitting result plots
  tmp.first = 912;
  tmp.second.name = "Plots of Parameter Estimation Results per Dependent Value";
  tmp.second.description = "For each dependent value of the parameter estimation a plot is created. Each plot contains the experimental data, the fitted curves, and the weighted errors for each experiment a dependent value occurs.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::parameterFitting;
  tmp.second.options = {
    {"Measured Values", true, "Displays Measured Values"},
    {"Fitted Values", true, "Displays Fitted Values"},
    {"Weighted Errors", false, "Displays Weighted Errors"},
    {"Validation Measured", false, "Displays Validation Data"},
    {"Validation Fitted", false, "Displays Validation Fitted Values"},
    {"Validation Errors", false, "Displays Weighted Validation Errors"},
  };
  mMap.insert(tmp);

  //fitting validation plots
  tmp.first = 920;
  tmp.second.name = "Parameter Estimation Validation Result";
  tmp.second.description = "Curves of all dependent values of all validation data are created in one plot. For each dependent value the validation data, the fitted curve, and the weighted error are shown.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::parameterFitting;
  tmp.second.options = {{"Measured Values", true, "Displays Measured Values"},
    {"Fitted Values", true, "Displays Fitted Values"},
    {"Weighted Errors", false, "Displays Weighted Errors"}
  };
  mMap.insert(tmp);

  // need to reset the options
  tmp.second.options = {};

  //fitting result plots
  tmp.first = 913;
  tmp.second.name = "Progress of Fit";
  tmp.second.description = "Plot of the sum of squares of residuals vs. number of function evaluations (for parameter estimation).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::parameterFitting;
  mMap.insert(tmp);

  //opt result plots
  tmp.first = 914;
  tmp.second.name = "Progress of Optimization";
  tmp.second.description = "Plot of the target function vs. number of function evaluations (for optimization).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::optimization;
  mMap.insert(tmp);

  //empty plot
  tmp.first = 998;
  tmp.second.name = "Create New";
  tmp.second.description = "A plot with nothing in it.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::UnsetTask;
  mMap.insert(tmp);

  // *****************************************************************

  //concentrations plot
  tmp.first = 200;
  tmp.second.name = "Scan of Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of the variable species concentrations, variable compartment volumes, and variable global quantity values vs. innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  //particle numbers plot
  tmp.first = 201;
  tmp.second.name = "Scan of Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of the variable species particle numbers, variable compartment volumes, and variable global quantity values vs. innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  //complete concentrations plot
  tmp.first = 202;
  tmp.second.name = "Scan of Complete Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of all the species concentrations, compartment volumes, and all global quantity values vs. innermost scan parameter (includes fixed ones).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  //complete particle numbers plot
  tmp.first = 203;
  tmp.second.name = "Scan of Complete Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of all the species particle numbers, compartment volumes, and global quantity values vs. innermost scan parameter (includes fixed ones).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  //concentration rate plot
  tmp.first = 204;
  tmp.second.name = "Scan of Concentration Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A plot of the rate of change of concentrations of species, compartment volume, and global quantities, which are determined by ODEs or reactions vs. innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  //particle rate plot
  tmp.first = 205;
  tmp.second.name = "Scan of Particle Number Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A plot of the rate of change of particle numbers of all species, compartment volume, and global quantities, which are determined by ODEs or reactions vs. innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  //reaction particle flux
  tmp.first = 206;
  tmp.second.name = "Scan of Reaction Fluxes";
  tmp.second.description = "A plot of the fluxes of all reactions vs. innermost scan parameter, in concentration/time unit.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  //reaction particle flux
  tmp.first = 207;
  tmp.second.name = "Scan of Reaction Event Fluxes";
  tmp.second.description = "A plot of the fluxes of all reactions vs. innermost scan parameter, in reaction events/time unit.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  //eigenvalues plot
  tmp.first = 250;
  tmp.second.name = "Eigenvalues vs. scan parameter";
  tmp.second.description = "A plot of the real and imaginary parts of the eigenvalues of the Jacobian as a function of the innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  tmp.second.mSecondaryTask = CTaskEnum::Task::steadyState;
  mMap.insert(tmp);

  //parameter estimation residuals plot
  tmp.first = 251;
  tmp.second.name = "Parameter estimation target function vs. scan parameter";
  tmp.second.description = "A plot of the target function of parameter estimation as a function of the innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  tmp.second.mSecondaryTask = CTaskEnum::Task::parameterFitting;
  mMap.insert(tmp);

  //optimization residuals plot
  tmp.first = 252;
  tmp.second.name = "Optimization target function vs. scan parameter";
  tmp.second.description = "A plot of the target function of optimization as a function of the innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  tmp.second.mSecondaryTask = CTaskEnum::Task::optimization;
  mMap.insert(tmp);

#ifdef WITH_TIME_SENS

  // 61 time sensitivities: time vs scaled state sensitivities
  tmp.first = 61;
  tmp.second.name = "Time Course Sensitivities time vs. scaled state sensitivities";
  tmp.second.description = "A plot of time vs. scaled state sensitivities.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeSens;
  mMap.insert(tmp);

  // 62 time sensitivities: time vs scaled target sensitivities
  tmp.first = 62;
  tmp.second.name = "Time Course Sensitivities time vs. scaled target sensitivities";
  tmp.second.description = "A plot of time vs. scaled target sensitivities.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeSens;
  mMap.insert(tmp);

  // 63 time sensitivities: time vs state sensitivities
  tmp.first = 63;
  tmp.second.name = "Time Course Sensitivities time vs. state sensitivities";
  tmp.second.description = "A plot of time vs. state sensitivities.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeSens;
  mMap.insert(tmp);

  // 64 time sensitivities: time vs target sensitivities
  tmp.first = 64;
  tmp.second.name = "Time Course Sensitivities time vs. target sensitivities";
  tmp.second.description = "A plot of time vs. target sensitivities.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeSens;
  mMap.insert(tmp);

#endif

  // *****************************************************************

  //now the reports
  tmp.first = 999;
  tmp.second.name = "-- Reports";
  tmp.second.description = "";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::UnsetTask;
  mMap.insert(tmp);

  //concentrations report
  tmp.first = 1000;
  tmp.second.name = "Time, Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of time, variable species concentrations, variable compartment volumes, and variable global quantity values.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1001;
  tmp.second.name = "Time, Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of time, variable species particle numbers, variable compartment volumes, and variable global quantity values.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1002;
  tmp.second.name = "Complete Time, Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of time, all species concentrations, all compartment volumes, and all global quantity values (includes fixed ones).";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1003;
  tmp.second.name = "Complete Time, Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of time, all species particle numbers, all compartment volumes, and all global quantity values (includes fixed ones).";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1004;
  tmp.second.name = "Time, Concentration Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A table of time and the rate of change of concentrations of species, compartment volumes, and global quantities which are determined by reactions or ODEs.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);  //not possible at the moment

  tmp.first = 1005;
  tmp.second.name = "Time, Particle Numbers Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A table of time and the rate of change of particle numbers of species, compartment volumes, and global quantities which are determined by reactions or ODEs.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1006;
  tmp.second.name = "Time and Reaction Fluxes";
  tmp.second.description = "A table of the fluxes of all reactions and time, in concentration/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1007;
  tmp.second.name = "Time and Reaction Event Fluxes";
  tmp.second.description = "A table of the fluxes of all reactions and time, in reaction events/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1008;
  tmp.second.name = "Time and all Variable Values (Concentration Units)";
  tmp.second.description = "This table includes all values which change over a time course. Species are measured in concentration unit and fluxes are in concentration/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1009;
  tmp.second.name = "Time and all Variable Values (Particle Number Units)";
  tmp.second.description = "This table includes all values which change over a time course. Species are measured in particle numbers and fluxes are in events/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::timeCourse;
  mMap.insert(tmp);

  //concentrations report
  tmp.first = 1200;
  tmp.second.name = "Scan Parameters, Time, Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of scan parameters, time, variable species concentrations, variable compartment volumes, and variable global quantity values.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  tmp.first = 1201;
  tmp.second.name = "Scan Parameters, Time, Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of scan parameters, time, variable species particle numbers, variable compartment volumes, and variable global quantity values.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  tmp.first = 1202;
  tmp.second.name = "Scan Parameters, Time, Complete Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of scan parameters, time, all species concentrations, all compartment volumes, and all global quantity values (includes fixed ones).";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  tmp.first = 1203;
  tmp.second.name = "Scan Parameters, Time, Complete Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of scan parameters, time, all species particle numbers, all compartment volumes, and all global quantity values (includes fixed ones).";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  tmp.first = 1204;
  tmp.second.name = "Scan Parameters, Time, Concentration Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A table of scan parameters, time and the rate of change of concentrations of species, compartment volumes, and global quantities which are determined by reactions or ODEs.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);  //not possible at the moment

  tmp.first = 1205;
  tmp.second.name = "Scan Parameters, Time, Particle Numbers Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A table of scan parameters, time and the rate of change of particle numbers of species, compartment volumes, and global quantities which are determined by reactions or ODEs.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  tmp.first = 1206;
  tmp.second.name = "Scan Parameters, Time and Reaction Fluxes";
  tmp.second.description = "A table of scan parameters and the fluxes of all reactions and time, in concentration/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  tmp.first = 1207;
  tmp.second.name = "Scan Parameters, Time and Reaction Event Fluxes";
  tmp.second.description = "A table of scan parameters and the fluxes of all reactions and time, in reaction events/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  tmp.first = 1208;
  tmp.second.name = "Scan Parameters, Time and all Variable Values (Concentration Units)";
  tmp.second.description = "This table includes scan parameters and all values which change over a time course. Species are measured in concentration unit and fluxes are in concentration/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  tmp.first = 1209;
  tmp.second.name = "Scan Parameters, Time and all Variable Values (Particle Number Units)";
  tmp.second.description = "This table includes scan parameters and all values which change over a time course. Species are measured in particle numbers and fluxes are in events/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  mMap.insert(tmp);

  //eigenvalues report
  tmp.first = 1250;
  tmp.second.name = "Scan Parameters and Eigenvalues";
  tmp.second.description = "This table includes scan parameters and the real and imaginary parts of the eigenvalues of the reduced system's Jacobian.";
  tmp.second.isPlot = false;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  tmp.second.mSecondaryTask = CTaskEnum::Task::steadyState;
  mMap.insert(tmp);

  //parameter estimation target function  report
  tmp.first = 1251;
  tmp.second.name = "Scan Parameters and Target function of parameter estimation";
  tmp.second.description = "This table includes scan parameters and the target function of the parameter estimation.";
  tmp.second.isPlot = false;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  tmp.second.mSecondaryTask = CTaskEnum::Task::parameterFitting;
  mMap.insert(tmp);

  //optimization target function report
  tmp.first = 1252;
  tmp.second.name = "Scan Parameters and Target function of optimization";
  tmp.second.description = "This table includes scan parameters and the target function of the optimization.";
  tmp.second.isPlot = false;
  tmp.second.mTaskType = CTaskEnum::Task::scan;
  tmp.second.mSecondaryTask = CTaskEnum::Task::optimization;
  mMap.insert(tmp);

#ifdef WITH_TIME_SENS

  // 61 time sensitivities: time vs scaled state sensitivities
  tmp.first = 1061;
  tmp.second.name = "Time Course Sensitivities time vs. scaled state sensitivities";
  tmp.second.description = "A report of time vs. scaled state sensitivities.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeSens;
  mMap.insert(tmp);

  // 62 time sensitivities: time vs scaled target sensitivities
  tmp.first = 1062;
  tmp.second.name = "Time Course Sensitivities time vs. scaled target sensitivities";
  tmp.second.description = "A report of time vs. scaled target sensitivities.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeSens;
  mMap.insert(tmp);

  // 63 time sensitivities: time vs state sensitivities
  tmp.first = 1063;
  tmp.second.name = "Time Course Sensitivities time vs. state sensitivities";
  tmp.second.description = "A report of time vs. state sensitivities.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeSens;
  mMap.insert(tmp);

  // 64 time sensitivities: time vs target sensitivities
  tmp.first = 1064;
  tmp.second.name = "Time Course Sensitivities time vs. target sensitivities";
  tmp.second.description = "A report of time vs. target sensitivities.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CTaskEnum::Task::timeSens;
  mMap.insert(tmp);

#endif

  tmp.first = 1999;
  tmp.second.name = "Create New";
  tmp.second.description = "A table with nothing in it.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CTaskEnum::Task::UnsetTask;
  mMap.insert(tmp);

  return true;
}

namespace
{

std::string getFittingPointDisplayName(const CFittingPoint & point,
                                       const CExperiment * pExperiment,
                                       CDataModel * pDataModel)
{
  std::string Name = point.getModelObjectCN();
  const CDataObject * pObject =
    dynamic_cast< const CDataObject * >(pDataModel->getObject(Name));

  if (pObject != NULL)
    Name = pObject->getObjectDisplayName();

  if (pExperiment != NULL)
    Name = pExperiment->getObjectName() + "," + Name;

  return Name;
}

void applyMeasuredItemStyle(CPlotItem & item, unsigned C_INT32 colorIndex)
{
  item.setValue("Line type", (unsigned C_INT32) 3);      // symbols and lines
  item.setValue("Symbol subtype", (unsigned C_INT32) 1); // fat cross
  item.setValue("Line subtype", (unsigned C_INT32) 1);   // dotted
  item.setValue("Color", CPlotColors::getCopasiColorStr(colorIndex));
}

void applyFittedItemStyle(CPlotItem & item, bool isTimeCourse, unsigned C_INT32 colorIndex)
{
  item.setValue("Line type", isTimeCourse ? (unsigned C_INT32) 0 : (unsigned C_INT32) 2);

  if (isTimeCourse)
    item.setValue("Symbol subtype", (unsigned C_INT32) 0);
  else
    item.setValue("Symbol subtype", (unsigned C_INT32) CPlotItem::SymbolType::Square);

  item.setValue("Line subtype", (unsigned C_INT32) 0); // solid
  item.setValue("Color", CPlotColors::getCopasiColorStr(colorIndex));
}

void applyErrorItemStyle(CPlotItem & item, unsigned C_INT32 colorIndex)
{
  item.setValue("Line type", (unsigned C_INT32) 2);      // symbols
  item.setValue("Symbol subtype", (unsigned C_INT32) 2); // circles
  item.setValue("Line subtype", (unsigned C_INT32) 0);
  item.setValue("Color", CPlotColors::getCopasiColorStr(colorIndex));
}

std::string fittingSeriesTitle(const std::string & prefix, const std::string & label)
{
  return prefix + "(" + label + ")";
}

void addCombinedFittingPointItems(const CFittingPoint & point,
                                  const CExperiment * pExperiment,
                                  const CDataObject * pXAxis,
                                  CDataModel * pDataModel,
                                  const SFittingPlotOptions & options,
                                  unsigned C_INT32 colorIndex,
                                  bool isTimeCourse,
                                  std::vector< const CDataObject * > & data,
                                  std::vector< std::string > & channelX,
                                  std::vector< std::string > & names,
                                  std::vector< unsigned C_INT32 > & lineTypes,
                                  std::vector< unsigned C_INT32 > & symbolSubTypes,
                                  std::vector< unsigned C_INT32 > & lineSubTypes,
                                  std::vector< std::string > & colors)
{
  const std::string Name = getFittingPointDisplayName(point, pExperiment, pDataModel);
  const std::string xChannel = pXAxis->getCN();

  if (options.needMeasured)
    {
      data.push_back(static_cast< const CDataObject * >(point.getChildObject(CCommonName("Reference=Measured Value"))));
      channelX.push_back(xChannel);
      names.push_back(fittingSeriesTitle(Name, options.measuredLabel));
      lineTypes.push_back(3);
      symbolSubTypes.push_back(options.isValdation 
        ? (int) CPlotItem::SymbolType::xCross 
        : (int) CPlotItem::SymbolType::LargeCross
      );
      lineSubTypes.push_back(1);
      colors.push_back(CPlotColors::getCopasiColorStr(colorIndex));
    }

  if (options.needFitted)
    {
      data.push_back(static_cast< const CDataObject * >(point.getChildObject(CCommonName("Reference=Fitted Value"))));
      channelX.push_back(xChannel);
      names.push_back(fittingSeriesTitle(Name, options.fittedLabel));

      if (isTimeCourse)
        {
          lineTypes.push_back(0);
          symbolSubTypes.push_back(0);
        }
      else
        {
          lineTypes.push_back(2);
          symbolSubTypes.push_back((unsigned C_INT32) CPlotItem::SymbolType::Square);
        }

      lineSubTypes.push_back(0);
      colors.push_back(CPlotColors::getCopasiColorStr(colorIndex));
    }

  if (options.needErrors)
    {
      data.push_back(static_cast< const CDataObject * >(point.getChildObject(CCommonName("Reference=Weighted Error"))));
      channelX.push_back(xChannel);
      names.push_back(fittingSeriesTitle(Name, options.errorLabel));
      lineTypes.push_back(2);
      symbolSubTypes.push_back((int) CPlotItem::SymbolType::Circle);
      lineSubTypes.push_back(0);
      colors.push_back(CPlotColors::getCopasiColorStr(colorIndex));
    }
}

void applyCombinedPlotItemStyles(CPlotSpecification * pPlotSpecification,
                                 const std::vector< std::string > & channelX,
                                 const std::vector< std::string > & names,
                                 const std::vector< unsigned C_INT32 > & lineTypes,
                                 const std::vector< unsigned C_INT32 > & symbolSubTypes,
                                 const std::vector< unsigned C_INT32 > & lineSubTypes,
                                 const std::vector< std::string > & colors)
{
  if (pPlotSpecification == NULL)
    return;

  CDataVector< CPlotItem > & Items = pPlotSpecification->getItems();
  CDataVector< CPlotItem >::iterator itItem = Items.begin();
  CDataVector< CPlotItem >::iterator endItem = Items.end();
  std::vector< std::string >::const_iterator itChannelX = channelX.begin();
  std::vector< std::string >::const_iterator itName = names.begin();
  std::vector< unsigned C_INT32 >::const_iterator itLineType = lineTypes.begin();
  std::vector< unsigned C_INT32 >::const_iterator itSymbolSubType = symbolSubTypes.begin();
  std::vector< unsigned C_INT32 >::const_iterator itLineSubType = lineSubTypes.begin();
  std::vector< std::string >::const_iterator itColor = colors.begin();

  while (itItem != endItem)
    {
      itItem->getChannels()[0] = CPlotDataChannelSpec(CCommonName(*itChannelX++));
      itItem->setTitle(*itName++);
      itItem->setActivity(COutputInterface::AFTER);
      itItem->setValue("Line type", *itLineType++);
      itItem->setValue("Symbol subtype", *itSymbolSubType++);
      itItem->setValue("Line subtype", *itLineSubType++);
      itItem->setValue("Color", *itColor++);
      itItem++;
    }
}

void configureFittingPlotItems(CPlotSpecification * pPlotSpecification,
                               const CDataVector< CFittingPoint > & fittingPoints,
                               CDataModel * pDataModel,
                               const SFittingPlotOptions & options,
                               bool isTimeCourse)
{
  if (pPlotSpecification == NULL)
    return;

  CDataVector< CPlotItem > & Items = pPlotSpecification->getItems();
  CDataVector< CPlotItem >::iterator itItem = Items.begin();
  CDataVector< CPlotItem >::iterator endItem = Items.end();
  CDataVector< CFittingPoint >::const_iterator it = fittingPoints.begin();
  unsigned C_INT32 colorIndex = 0;

  while (itItem != endItem)
    {
      const std::string Name = getFittingPointDisplayName(*it++, NULL, pDataModel);

      if (options.needMeasured)
        {
          itItem->setTitle(fittingSeriesTitle(Name, options.measuredLabel));
          itItem->setActivity(COutputInterface::AFTER);
          applyMeasuredItemStyle(*itItem, colorIndex);
          itItem++;
        }

      if (options.needFitted)
        {
          itItem->setTitle(fittingSeriesTitle(Name, options.fittedLabel));
          itItem->setActivity(COutputInterface::AFTER);
          applyFittedItemStyle(*itItem, isTimeCourse, colorIndex);
          itItem++;
        }

      if (options.needErrors)
        {
          itItem->setTitle(fittingSeriesTitle(Name, options.errorLabel));
          itItem->setActivity(COutputInterface::AFTER);
          applyErrorItemStyle(*itItem, colorIndex);
          itItem++;
        }

      ++colorIndex;
    }
}

void addDependentValuePlotItems(CPlotSpecification * pPlotSpecification,
                                const CExperiment * pExperiment,
                                const CFittingPoint & point,
                                const CPlotDataChannelSpec & channelX,
                                const SFittingPlotOptions & options,
                                bool isTimeCourse,
                                size_t colorIndex)
{
  if (pPlotSpecification == NULL)
    return;

  const std::string experimentName = pExperiment->getObjectName();
  CPlotItem * pItem = NULL;

  if (options.needMeasured)
    {
      pItem = pPlotSpecification->createItem(fittingSeriesTitle(experimentName, options.measuredLabel), CPlotItem::curve2d);
      pItem->setActivity(COutputInterface::AFTER);
      applyMeasuredItemStyle(*pItem, colorIndex);
      pItem->addChannel(channelX);
      pItem->addChannel(point.getChildObject(CCommonName("Reference=Measured Value"))->getCN());
    }

  if (options.needFitted)
    {
      pItem = pPlotSpecification->createItem(fittingSeriesTitle(experimentName, options.fittedLabel), CPlotItem::curve2d);
      pItem->setActivity(COutputInterface::AFTER);
      applyFittedItemStyle(*pItem, isTimeCourse, colorIndex);
      pItem->addChannel(channelX);
      pItem->addChannel(point.getChildObject(CCommonName("Reference=Fitted Value"))->getCN());
    }

  if (options.needErrors)
    {
      pItem = pPlotSpecification->createItem(fittingSeriesTitle(experimentName, options.errorLabel), CPlotItem::curve2d);
      pItem->setActivity(COutputInterface::AFTER);
      applyErrorItemStyle(*pItem, colorIndex);
      pItem->addChannel(channelX);
      pItem->addChannel(point.getChildObject(CCommonName("Reference=Weighted Error"))->getCN());
    }
}

void appendToCombinedFittingPlot(CPlotSpecification * pPlotSpecification,
                                 const std::vector< const CDataObject * > & yData,
                                 const std::vector< std::string > & channelX,
                                 const std::vector< std::string > & names,
                                 const std::vector< unsigned C_INT32 > & lineTypes,
                                 const std::vector< unsigned C_INT32 > & symbolSubTypes,
                                 const std::vector< unsigned C_INT32 > & lineSubTypes,
                                 const std::vector< std::string > & colors)
{
  if (pPlotSpecification == NULL)
    return;

  std::vector< std::string >::const_iterator itChannelX = channelX.begin();
  std::vector< std::string >::const_iterator itName = names.begin();
  std::vector< unsigned C_INT32 >::const_iterator itLineType = lineTypes.begin();
  std::vector< unsigned C_INT32 >::const_iterator itSymbolSubType = symbolSubTypes.begin();
  std::vector< unsigned C_INT32 >::const_iterator itLineSubType = lineSubTypes.begin();
  std::vector< std::string >::const_iterator itColor = colors.begin();
  std::vector< const CDataObject * >::const_iterator itY = yData.begin();
  std::vector< const CDataObject * >::const_iterator endY = yData.end();

  while (itY != endY)
    {
      CPlotItem * pItem = pPlotSpecification->createItem(*itName++, CPlotItem::curve2d);
      pItem->setActivity(COutputInterface::AFTER);
      pItem->addChannel(CPlotDataChannelSpec(CCommonName(*itChannelX++)));
      pItem->addChannel((*itY++)->getCN());
      pItem->setValue("Line type", *itLineType++);
      pItem->setValue("Symbol subtype", *itSymbolSubType++);
      pItem->setValue("Line subtype", *itLineSubType++);
      pItem->setValue("Color", *itColor++);
    }
}

} // namespace

SFittingPlotOptions
COutputAssistant::getExperimentFittingPlotOptions(const std::vector<COutputOption>* pOptions)
{
  SFittingPlotOptions options = {
    isOptionEnabled(pOptions, "Measured Values", true),
    isOptionEnabled(pOptions, "Fitted Values", true),
    isOptionEnabled(pOptions, "Weighted Errors", false),
    false,
    "", "", ""
  };
  options.setExperimentLabels();
  return options;
}

SFittingPlotOptions
COutputAssistant::getValidationFittingPlotOptions(const std::vector<COutputOption>* pOptions)
{
  SFittingPlotOptions options = {
    isOptionEnabled(pOptions, "Validation Measured", false),
    isOptionEnabled(pOptions, "Validation Fitted", false),
    isOptionEnabled(pOptions, "Validation Errors", false),
    true,
    "", "", ""
  };
  options.setValidationLabels();
  return options;
}

CFitProblem*
COutputAssistant::getParameterEstimationProblem(CDataModel* pDataModel)
{
  if (pDataModel == NULL)
    return NULL;

  CCopasiTask * pTask = &pDataModel->getTaskList()->operator[]("Parameter Estimation");

  if (pTask == NULL)
    return NULL;

  return dynamic_cast< CFitProblem * >(pTask->getProblem());
}

CPlotSpecification*
COutputAssistant::createCombinedFittingPlot(C_INT32 id,
                                          CDataModel* pDataModel,
                                          const CExperimentSet& experimentSet,
                                          const SFittingPlotOptions& options,
                                          CPlotSpecification* pExistingPlot)
{
  if (!options.hasAny())
    return pExistingPlot;

  std::vector< const CDataObject * > yData;
  const CDataObject * pXAxis = NULL;

  std::vector< std::string > channelX;
  std::vector< std::string > names;
  std::vector< unsigned C_INT32 > lineTypes;
  std::vector< unsigned C_INT32 > symbolSubTypes;
  std::vector< unsigned C_INT32 > lineSubTypes;
  std::vector< std::string > colors;

  unsigned C_INT32 colorIndex = 0;

  if (pExistingPlot != NULL)
    {
      unsigned C_INT32 seriesPerPoint = 0;

      if (options.needMeasured)
        seriesPerPoint++;

      if (options.needFitted)
        seriesPerPoint++;

      if (options.needErrors)
        seriesPerPoint++;

      if (seriesPerPoint > 0)
        colorIndex = pExistingPlot->getItems().size() / seriesPerPoint;
    }

  const size_t imax = experimentSet.getExperimentCount();

  for (size_t i = 0; i < imax; i++)
    {
      const CExperiment * pExperiment = experimentSet.getExperiment(i);
      const CDataVector< CFittingPoint > & fittingPoints = pExperiment->getFittingPoints();
      CDataVector< CFittingPoint >::const_iterator it = fittingPoints.begin();
      CDataVector< CFittingPoint >::const_iterator end = fittingPoints.end();

      if (it == end)
        continue;

      pXAxis = static_cast< const CDataObject * >(it->getChildObject(CCommonName("Reference=Independent Value")));
      const bool isTimeCourse = pExperiment->getExperimentType() == CTaskEnum::Task::timeCourse;

      for (; it != end; ++it)
        {
          addCombinedFittingPointItems(*it, pExperiment, pXAxis, pDataModel, options, colorIndex, isTimeCourse,
                                       yData, channelX, names, lineTypes, symbolSubTypes, lineSubTypes, colors);
          ++colorIndex;
        }
    }

  if (yData.empty())
    return pExistingPlot;

  if (pExistingPlot == NULL)
    {
      CPlotSpecification * pPlotSpecification =
        createPlot(getItemName(id), pXAxis, false, yData, false, getItem(id).mTaskType, pDataModel);

      applyCombinedPlotItemStyles(pPlotSpecification, channelX, names, lineTypes, symbolSubTypes, lineSubTypes, colors);

      return pPlotSpecification;
    }

  appendToCombinedFittingPlot(pExistingPlot, yData, channelX, names, lineTypes, symbolSubTypes, lineSubTypes, colors);

  return pExistingPlot;
}

CPlotSpecification*
COutputAssistant::createPerExperimentFittingPlot(C_INT32 id,
                                                   CDataModel* pDataModel,
                                                   const CExperimentSet& experimentSet,
                                                   const SFittingPlotOptions& options)
{
  if (!options.hasAny())
    return NULL;

  CPlotSpecification * pPlotSpecification = NULL;
  const size_t imax = experimentSet.getExperimentCount();

  for (size_t i = 0; i < imax; i++)
    {
      const CExperiment * pExperiment = experimentSet.getExperiment(i);
      const bool isTimeCourse = pExperiment->getExperimentType() == CTaskEnum::Task::timeCourse;
      const CDataVector< CFittingPoint > & fittingPoints = pExperiment->getFittingPoints();
      CDataVector< CFittingPoint >::const_iterator it = fittingPoints.begin();
      CDataVector< CFittingPoint >::const_iterator end = fittingPoints.end();

      if (it == end)
        continue;

      const CDataObject * pXAxis =
        static_cast< const CDataObject * >(it->getChildObject(CCommonName("Reference=Independent Value")));
      std::vector< const CDataObject * > data;

      for (; it != end; ++it)
        {
          if (options.needMeasured)
            data.push_back(static_cast< const CDataObject * >(it->getChildObject(CCommonName("Reference=Measured Value"))));

          if (options.needFitted)
            data.push_back(static_cast< const CDataObject * >(it->getChildObject(CCommonName("Reference=Fitted Value"))));

          if (options.needErrors)
            data.push_back(static_cast< const CDataObject * >(it->getChildObject(CCommonName("Reference=Weighted Error"))));
        }

      pPlotSpecification =
        createPlot(pExperiment->getObjectName(), pXAxis, false, data, false, getItem(id).mTaskType, pDataModel);

      configureFittingPlotItems(pPlotSpecification, pExperiment->getFittingPoints(), pDataModel, options, isTimeCourse);
    }

  return pPlotSpecification;
}

CPlotSpecification*
COutputAssistant::createPerDependentValueFittingPlot(C_INT32 id,
                                                     CDataModel* pDataModel,
                                                     const CExperimentSet& experimentSet,
                                                     const SFittingPlotOptions& options,
                                                     std::map<const CDataObject*, CPlotSpecification*>* pPlotSpecMap)
{
  if (!options.hasAny())
    return NULL;

  CPlotSpecification * pPlotSpecification = NULL;
  std::map< const CDataObject *, CPlotSpecification * > localPlotSpecMap;
  std::map< const CDataObject *, CPlotSpecification * > & plotSpecMap =
    (pPlotSpecMap != NULL) ? *pPlotSpecMap : localPlotSpecMap;
  const size_t imax = experimentSet.getExperimentCount();

  for (size_t i = 0; i < imax; i++)
    {
      const CExperiment * pExperiment = experimentSet.getExperiment(i);
      const bool isTimeCourse = pExperiment->getExperimentType() == CTaskEnum::Task::timeCourse;
      const CDataVector< CFittingPoint > & fittingPoints = pExperiment->getFittingPoints();
      CDataVector< CFittingPoint >::const_iterator it = fittingPoints.begin();
      CDataVector< CFittingPoint >::const_iterator end = fittingPoints.end();

      if (it == end)
        continue;

      const CPlotDataChannelSpec channelX =
        it->getChildObject(CCommonName("Reference=Independent Value"))->getCN();

      for (; it != end; ++it)
        {
          const CDataObject * pObject =
            dynamic_cast< const CDataObject * >(pDataModel->getObject(it->getModelObjectCN()));

          if (pObject == NULL)
            continue;

          std::map< const CDataObject *, CPlotSpecification * >::iterator found = plotSpecMap.find(pObject);

          if (found != plotSpecMap.end())
            pPlotSpecification = found->second;
          else
            {
              unsigned C_INT32 suffix = 0;
              std::ostringstream sname;
              sname << pObject->getObjectDisplayName();

              while (!(pPlotSpecification =
                         pDataModel->getPlotDefinitionList()->createPlotSpec(sname.str(), CPlotItem::plot2d)))
                {
                  suffix++;
                  sname.str("");
                  sname << pObject->getObjectDisplayName() << "_" << suffix;
                }

              pPlotSpecification->addTaskType(CTaskEnum::Task::parameterFitting);
              pPlotSpecification->assertParameter("plot engine", CCopasiParameter::Type::STRING, std::string("QCustomPlot"));
              plotSpecMap[pObject] = pPlotSpecification;
            }

          const size_t colorIndex = pPlotSpecification->getItems().size() / 3;
          addDependentValuePlotItems(pPlotSpecification, pExperiment, *it, channelX, options, isTimeCourse, colorIndex);
        }
    }

  return pPlotSpecification;
}

CPlotSpecification*
COutputAssistant::createProgressPlot(C_INT32 id,
                                     CDataModel* pDataModel,
                                     const CDataObject* pXData,
                                     const CDataObject* pYData,
                                     const std::string& plotTitle,
                                     const std::string& itemTitle)
{
  std::vector< const CDataObject * > data;

  if (pYData != NULL)
    data.push_back(pYData);

  CPlotSpecification * pPlotSpecification =
    createPlot(plotTitle, pXData, false, data, false, getItem(id).mTaskType, pDataModel);

  if (pPlotSpecification != NULL)
    {
      pPlotSpecification->setLogY(true);
      CDataVector< CPlotItem > & Items = pPlotSpecification->getItems();
      CDataVector< CPlotItem >::iterator itItem = Items.begin();
      CDataVector< CPlotItem >::iterator endItem = Items.end();

      while (itItem != endItem)
        {
          itItem->setTitle(itemTitle);
          itItem->setActivity(COutputInterface::DURING);
          itItem->setValue("Line type", (unsigned C_INT32) CPlotItem::LineType::LinesAndSymbols);
          itItem++;
        }
    }

  return pPlotSpecification;
}

CPlotSpecification*
COutputAssistant::createParameterEstimationPlot(C_INT32 id,
                                                CDataModel* pDataModel,
                                                const std::vector<COutputOption>* pOptions)
{
  switch (id)
    {
      case 910:
      {
        CFitProblem * pFitProblem = getParameterEstimationProblem(pDataModel);

        if (pFitProblem == NULL)
          return NULL;

        const SFittingPlotOptions experimentOptions = getExperimentFittingPlotOptions(pOptions);
        const SFittingPlotOptions validationOptions = getValidationFittingPlotOptions(pOptions);
        CPlotSpecification * pPlotSpecification = NULL;

        if (experimentOptions.hasAny())
          pPlotSpecification =
            createCombinedFittingPlot(id, pDataModel, pFitProblem->getExperimentSet(), experimentOptions, pPlotSpecification);

        if (validationOptions.hasAny())
          pPlotSpecification =
            createCombinedFittingPlot(id, pDataModel, pFitProblem->getCrossValidationSet(), validationOptions, pPlotSpecification);

        return pPlotSpecification;
      }

      case 920:
      {
        CFitProblem * pFitProblem = getParameterEstimationProblem(pDataModel);

        if (pFitProblem == NULL)
          return NULL;

        SFittingPlotOptions options = getExperimentFittingPlotOptions(pOptions);
        options.setValidationLabels();

        return createCombinedFittingPlot(id, pDataModel, pFitProblem->getCrossValidationSet(), options);
      }

      case 911:
      case 912:
      {
        CFitProblem * pFitProblem = getParameterEstimationProblem(pDataModel);

        if (pFitProblem == NULL)
          return NULL;

        const SFittingPlotOptions experimentOptions = getExperimentFittingPlotOptions(pOptions);
        const SFittingPlotOptions validationOptions = getValidationFittingPlotOptions(pOptions);
        CPlotSpecification * pPlotSpecification = NULL;

        if (id == 911)
          {
            if (experimentOptions.hasAny())
              pPlotSpecification =
                createPerExperimentFittingPlot(id, pDataModel, pFitProblem->getExperimentSet(), experimentOptions);

            if (validationOptions.hasAny())
              pPlotSpecification =
                createPerExperimentFittingPlot(id, pDataModel, pFitProblem->getCrossValidationSet(), validationOptions);

            return pPlotSpecification;
          }

        std::map< const CDataObject *, CPlotSpecification * > plotSpecMap;

        if (experimentOptions.hasAny())
          pPlotSpecification =
            createPerDependentValueFittingPlot(id, pDataModel, pFitProblem->getExperimentSet(), experimentOptions, &plotSpecMap);

        if (validationOptions.hasAny())
          pPlotSpecification =
            createPerDependentValueFittingPlot(id, pDataModel, pFitProblem->getCrossValidationSet(), validationOptions, &plotSpecMap);

        return pPlotSpecification;
      }

      case 913:
      {
        CFitProblem * pFitProblem = getParameterEstimationProblem(pDataModel);

        if (pFitProblem == NULL)
          return NULL;

        return createProgressPlot(id, pDataModel,
                                  static_cast< const CDataObject * >(pFitProblem->getChildObject(CCommonName("Reference=Function Evaluations"))),
                                  static_cast< const CDataObject * >(pFitProblem->getChildObject(CCommonName("Reference=Best Value"))),
                                  "Progress of Fit",
                                  "sum of squares");
      }

      case 914:
      {
        CCopasiTask * pTask = &pDataModel->getTaskList()->operator[]("Optimization");

        if (pTask == NULL)
          return NULL;

        COptProblem * pOptProblem = dynamic_cast< COptProblem * >(pTask->getProblem());

        if (pOptProblem == NULL)
          return NULL;

        return createProgressPlot(id, pDataModel,
                                  static_cast< const CDataObject * >(pOptProblem->getChildObject(CCommonName("Reference=Function Evaluations"))),
                                  static_cast< const CDataObject * >(pOptProblem->getChildObject(CCommonName("Reference=Best Value"))),
                                  "Progress of Optimization",
                                  "target function");
      }

      default:
        return NULL;
    }
}

//static
CDataObject*
COutputAssistant::createDefaultOutput(
  C_INT32 id, CCopasiTask * task, CDataModel* pDataModel, bool activate,
  const std::vector< COutputOption > * pOptions)
{
  if (task == NULL)
    {
      return NULL;
    }

  if (task->getProblem() == NULL)
    {
      return NULL;
    }

  const CModel & Model = task->getMathContainer()->getModel();

  std::vector<const CDataObject*> data1, tmpdata;

  const CDataObject* data2 = NULL;

  //first handle the special cases (those not that are not numbered according to the systematic scheme)
  switch (id)
    {
      case 910:
      case 911:
      case 912:
      case 913:
      case 914:
      case 920:
        return createParameterEstimationPlot(id, pDataModel, pOptions);
    }

  //now deal with the systematically numbered cases
  bool isReport = (id >= 1000);
  C_INT32 idMod = id % 200;
  bool logY = false; //this is onyl used for plots; it indicates whether the y axis is plotted logarithmically

  const CDataObject* pTime = static_cast< const CDataObject * >(Model.getChildObject(CCommonName("Reference=Time")));

  switch (idMod)
    {
      case 0:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_CONCENTRATIONS, &Model);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_COMPARTMENT_VOLUMES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 1:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_NUMBERS, &Model);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_COMPARTMENT_VOLUMES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 2:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_CONCENTRATIONS, &Model);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::COMPARTMENT_VOLUMES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::GLOBAL_PARAMETER_VALUES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 3:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_NUMBERS, &Model);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::COMPARTMENT_VOLUMES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::GLOBAL_PARAMETER_VALUES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 4:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_CONC_RATES, &Model);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::COMPARTMENT_RATES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::GLOBAL_PARAMETER_RATES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 5:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_PART_RATES, &Model);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::COMPARTMENT_RATES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::GLOBAL_PARAMETER_RATES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 6:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::REACTION_CONC_FLUXES, &Model);
        break;

      case 7:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::REACTION_PART_FLUXES, &Model);
        break;

      case 8:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_CONCENTRATIONS, &Model);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_COMPARTMENT_VOLUMES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_CONC_RATES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::COMPARTMENT_RATES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::GLOBAL_PARAMETER_RATES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::REACTION_CONC_FLUXES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_TRANSITION_TIME, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 9:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_NUMBERS, &Model);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_COMPARTMENT_VOLUMES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_PART_RATES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::COMPARTMENT_RATES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::GLOBAL_PARAMETER_RATES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::REACTION_PART_FLUXES, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_TRANSITION_TIME, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 50:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::REDUCED_JACOBIAN_EV_RE, &Model);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::REDUCED_JACOBIAN_EV_IM, &Model);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 51: //parameter estimation target function
      {
        CCopasiTask * pTask = &pDataModel->getTaskList()->operator[]("Parameter Estimation");

        if (pTask == NULL) break;

        CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(pTask->getProblem());

        if (pFitProblem == NULL) break;

        data1.push_back(static_cast< const CDataObject * >(pFitProblem->getChildObject(CCommonName("Reference=Best Value"))));
        logY = true;
      }
      break;

      case 52: //optimization target function
      {
        CCopasiTask * pTask = &pDataModel->getTaskList()->operator[]("Optimization");

        if (pTask == NULL) break;

        COptProblem * pOptProblem = dynamic_cast< COptProblem * >(pTask->getProblem());

        if (pOptProblem == NULL) break;

        data1.push_back(static_cast< const CDataObject * >(pOptProblem->getChildObject(CCommonName("Reference=Best Value"))));
      }
      break;

#ifdef WITH_TIME_SENS

      case 61: // time sensitivities: time vs scaled state sensitivities
      {
        CCopasiTask * pTask = &pDataModel->getTaskList()->operator[]("Time-Course Sensitivities");

        if (pTask == NULL) break;

        pTask->updateMatrices();

        CCopasiProblem * pProblem = pTask->getProblem();

        if (pProblem == NULL) break;

        const CDataArray* pArray = dynamic_cast<const CDataArray*>(pProblem->getChildObject(CCommonName("Array=Scaled State Sensitivities array")));
        add2DDataArrayToVector(data1, pArray);

        break;
      }

      case 62: // time sensitivities: time vs scaled target sensitivities
      {
        CCopasiTask * pTask = &pDataModel->getTaskList()->operator[]("Time-Course Sensitivities");

        if (pTask == NULL) break;

        pTask->updateMatrices();

        CCopasiProblem * pProblem = pTask->getProblem();

        if (pProblem == NULL) break;

        const CDataArray* pArray = dynamic_cast<const CDataArray*>(pProblem->getChildObject(CCommonName("Array=Scaled Target Sensitivities array")));
        add2DDataArrayToVector(data1, pArray);

        break;
      }

      case 63: // time sensitivities: time vs state sensitivities
      {
        CCopasiTask * pTask = &pDataModel->getTaskList()->operator[]("Time-Course Sensitivities");

        if (pTask == NULL) break;

        pTask->updateMatrices();

        CCopasiProblem * pProblem = pTask->getProblem();

        if (pProblem == NULL) break;

        const CDataArray* pArray = dynamic_cast<const CDataArray*>(pProblem->getChildObject(CCommonName("Array=State Sensitivities array")));

        add2DDataArrayToVector(data1, pArray);
        break;
      }

      case 64:// time sensitivities: time vs target sensitivities
      {
        CCopasiTask * pTask = &pDataModel->getTaskList()->operator[]("Time-Course Sensitivities");

        if (pTask == NULL) break;

        pTask->updateMatrices();

        CCopasiProblem * pProblem = pTask->getProblem();

        if (pProblem == NULL) break;

        const CDataArray* pArray = dynamic_cast<const CDataArray*>(pProblem->getChildObject(CCommonName("Array=Target Sensitivities array")));
        add2DDataArrayToVector(data1, pArray);

        break;
      }

#endif
    }

  if (isReport)
    {
      data1.insert(data1.begin(), pTime); //in any case, add time to the report

      if (1200 <= id && id < 1300) //we need to add the scan parameters
        {
          tmpdata.clear();
          CScanProblem* pSP = dynamic_cast<CScanProblem*>(task->getProblem());

          if (pSP) //we really have a scan problem
            {
              size_t num_scanitems = pSP->getNumberOfScanItems();
              size_t i;

              for (i = 0; i < num_scanitems; ++i)
                {
                  CCommonName & tmpString = pSP->getScanItem(i)->getValue< CRegisteredCommonName >("Object");

                  if (tmpString.size()) //the scan item references an object, this is the scan parameter
                    {
                      const CDataObject * tmpObject = CObjectInterface::DataObject(pSP->getObjectFromCN(tmpString));

                      if (tmpObject)
                        tmpdata.push_back(tmpObject);
                    }
                }

              data1.insert(data1.begin(), tmpdata.begin(), tmpdata.end());
            }
        }

      CReportDefinition* pReportDef = createTable(getItemName(id), data1, getItem(id).description, getItem(id).mTaskType, pDataModel);

      if (activate && pReportDef)
        {
          task->getReport().setReportDefinition(pReportDef);
          //TODO: also set a default filename?
        }

      return pReportDef;
    }
  else //plot
    {
      bool logX = false;

      if (200 <= id && id < 300) //we need to find the inner scan item for the x-axis
        {
          data2 = NULL;
          CScanProblem* pSP = dynamic_cast<CScanProblem*>(task->getProblem());

          if (pSP) //we really have a scan problem
            {
              size_t num_scanitems = pSP->getNumberOfScanItems();
              size_t i;

              for (i = 0; i < num_scanitems; ++i)
                {
                  CCommonName & tmpString = pSP->getScanItem(i)->getValue< CRegisteredCommonName >("Object");

                  if (tmpString.size()) //the scan item references an object, this is the scan parameter
                    {
                      const CDataObject * tmpObject = CObjectInterface::DataObject(pSP->getObjectFromCN(tmpString));

                      if (tmpObject)
                        {
                          data2 = tmpObject; //we only keep the last scan parameter we find, this is the innermost loop.
                          logX = (pSP->getScanItem(i)->getValue< bool >("log"));
                        }
                    }
                }
            }
        }
      else //time is on the x-axis
        {
          data2 = pTime;
        }

      return createPlot(getItemName(id), data2, logX, data1, logY, getItem(id).mTaskType, pDataModel, task);
    }

  return NULL;
}

#include "copasi/plot/COutputDefinitionVector.h"

//static
CPlotSpecification* COutputAssistant::createPlot(const std::string & name,
    const CDataObject * x,
    bool logX,
    const std::vector<const CDataObject*> & y,
    bool logY,
    const CTaskEnum::Task & taskType,
    CDataModel* pDataModel,
    CCopasiTask *task /*= NULL*/)
{
  if (!x) return NULL;

  std::vector<const CDataObject *>::const_iterator it, itEnd = y.end();

  //create plot with unique name
  unsigned C_INT32 i = 0;
  CPlotSpecification* pPl;
  std::ostringstream sname;
  sname << name;
  assert(pDataModel != NULL);

  while (!(pPl = pDataModel->getPlotDefinitionList()->createPlotSpec(sname.str(),
                 CPlotItem::plot2d)))
    {
      i++;
      sname.str("");
      sname << name << "_" << i;
    }

  // Set the task type for specific ones
  switch (taskType)
    {
      case CTaskEnum::Task::parameterFitting:
        pPl->addTaskType(taskType);
        pPl->addTaskType(CTaskEnum::Task::scan);
        break;

      case CTaskEnum::Task::optimization:
      case CTaskEnum::Task::scan:
#ifdef WITH_TIME_SENS
      case CTaskEnum::Task::timeSens:
#endif
        pPl->addTaskType(taskType);
        break;

      default:
        // not narrowing others by default, as for example time course plots would
        // could also be interesting for scan, TSS, cross section and the like
        break;
    }

  //create curves

  CPlotDataChannelSpec name1 = x->getCN();
  CPlotDataChannelSpec name2;
  std::string itemTitle;
  CPlotItem * plItem;

  CScanProblem* problem = task != NULL ? dynamic_cast<CScanProblem*>(task->getProblem()) : NULL;
  bool isCrossSection = (problem != NULL && problem->getSubtask() == CTaskEnum::Task::crosssection) ||
                        (task != NULL && task->getType() == CTaskEnum::Task::crosssection);

  bool isTimeSense =
#ifdef WITH_TIME_SENS
    (problem != NULL && problem->getSubtask() == CTaskEnum::Task::timeSens) ||
    (task != NULL && task->getType() == CTaskEnum::Task::timeSens);
#else
    false;
#endif

  for (it = y.begin(); it != itEnd; ++it)
    {
      if (!(*it)) continue;

      name2 = (*it)->getCN();
      itemTitle = static_cast< const CDataObject *>(*it)->getObjectDisplayName();

      // remove "TaskList[Time-Course Sensitivities]." from title if present
      if (isTimeSense)
        {
          std::string prefix = "TaskList[Time-Course Sensitivities].";
          size_t pos = itemTitle.find(prefix);
          if (pos != std::string::npos)
            {
              itemTitle = itemTitle.substr(pos + prefix.length());
            }

          prefix = " array";
          pos = itemTitle.find(prefix);
          if (pos != std::string::npos)
            {
              itemTitle = itemTitle.substr(0, pos) + itemTitle.substr(pos + prefix.length());
            }
        }

      plItem = pPl->createItem(itemTitle, CPlotItem::curve2d);
      plItem->addChannel(name1);
      plItem->addChannel(name2);

      if (isCrossSection)
        {
          // disable line
          plItem->setValue("Line type", (unsigned int) 2); // use symbols
          plItem->setValue("Symbol subtype", (unsigned int)2); // use symbols
        }
    }

  pPl->setLogX(logX);
  pPl->setLogY(logY);

  // set default plot engine to customplot for new plots
  pPl->assertParameter("plot engine", CCopasiParameter::Type::STRING, std::string("QCustomPlot"));

  return pPl;
}
bool
COutputAssistant::isOptionEnabled(
  const std::vector< COutputOption >* pOptions,
  const std::string & name,
  bool defaultValue /*= true*/)
{
  if (!pOptions)
    return defaultValue;

  for (auto entry : *pOptions)
    if (entry.name == name)
      return entry.enabled;

  return defaultValue;
}

//static
CReportDefinition* COutputAssistant::createTable(const std::string & name,
    const std::vector<const CDataObject *> & d,
    const std::string & comment,
    const CTaskEnum::Task & taskType,
    CDataModel* pDataModel)
{
  std::vector<const CDataObject * >::const_iterator it, itEnd = d.end();

  //create plot with unique name
  unsigned C_INT32 i = 0;
  CReportDefinition * pReport = NULL;
  std::ostringstream sname;
  sname << name;
  assert(pDataModel != NULL);

  while (!(pReport = pDataModel->getReportDefinitionList()->createReportDefinition(sname.str(), comment)))
    {
      i++;
      sname.str("");
      sname << name << "_" << i;
    }

  // Set the task type
  pReport->setTaskType(taskType);

  pReport->setIsTable(true);
  pReport->setSeparator("\t");

  for (it = d.begin(); it != itEnd; ++it)
    {
      if (!(*it)) continue;

      pReport->getTableAddr()->push_back((*it)->getCN());
    }

  return pReport;
}

void COutputAssistant::add2DDataArrayToVector(std::vector<const CDataObject *> &pVector, const CDataArray* pArray)
{
  if (pArray == NULL)
    return;

  if (pArray->dimensionality() != 2) //2d matrix
    return;

  size_t nrows = pArray->size()[0];
  size_t ncols = pArray->size()[1];

  for (size_t i = 0; i < nrows; ++i)
    for (size_t j = 0; j < ncols; ++j)
      pVector.push_back(static_cast<const CDataObject *>(
                          pArray->addElementReference((C_INT32) i, (C_INT32) j)));
}
