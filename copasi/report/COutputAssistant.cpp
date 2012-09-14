// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
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

#include "COutputAssistant.h"
#include "CCopasiObject.h"
#include "CReportDefinition.h"
#include "CReportDefinitionVector.h"

#include "utilities/CCopasiProblem.h"
#include "utilities/CCopasiTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "steadystate/CSteadyStateProblem.h"
#include "model/CObjectLists.h"
#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotColors.h"
#include "parameterFitting/CFitProblem.h"
#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CExperiment.h"
#include "scan/CScanProblem.h"

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
      else if (task->getType() == it->second.mTaskType || it->second.mTaskType == CCopasiTask::unset)
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
      case CCopasiTask::steadyState:
        return 1000;

      case CCopasiTask::timeCourse:
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
      case CCopasiTask::steadyState:
        return 0;

      case CCopasiTask::timeCourse:
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
  tmp.second.mTaskType = CCopasiTask::unset;
  mMap.insert(tmp);

  //concentrations plot
  tmp.first = 0;
  tmp.second.name = "Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of the variable species concentrations, variable compartment volumes, and variable global quantity values vs. time.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //particle numbers plot
  tmp.first = 1;
  tmp.second.name = "Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of the variable species particle numbers, variable compartment volumes, and variable global quantity values vs. time.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //complete concentrations plot
  tmp.first = 2;
  tmp.second.name = "Complete Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of all the species concentrations, compartment volumes, and all global quantity values vs. time (includes fixed ones).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //complete particle numbers plot
  tmp.first = 3;
  tmp.second.name = "Complete Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of all the species particle numbers, compartment volumes, and global quantity values vs. time (includes fixed ones).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //concentration rate plot
  tmp.first = 4;
  tmp.second.name = "Concentration Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A plot of the rate of change of concentrations of species, compartment volume, and global quantities, which are determined by ODEs or reactions vs. time.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //particle rate plot
  tmp.first = 5;
  tmp.second.name = "Particle Number Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A plot of the rate of change of particle numbers of all species, compartment volume, and global quantities, which are determined by ODEs or reactions vs. time.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //reaction particle flux
  tmp.first = 6;
  tmp.second.name = "Reaction Fluxes";
  tmp.second.description = "A plot of the fluxes of all reactions vs. time, in concentration/time unit.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //reaction particle flux
  tmp.first = 7;
  tmp.second.name = "Reaction Event Fluxes";
  tmp.second.description = "A plot of the fluxes of all reactions vs. time, in reaction events/time unit.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //fitting result plots
  tmp.first = 910;
  tmp.second.name = "Parameter Estimation Result";
  tmp.second.description = "Curves of all dependent values of all experiments are created in one plot. For each dependent value the experimental data, the fitted curve, and the weighted error are shown.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::parameterFitting;
  mMap.insert(tmp);

  //fitting result plots
  tmp.first = 911;
  tmp.second.name = "Plots of Parameter Estimation Results per Experiment";
  tmp.second.description = "For each experiment of the parameter estimation a plot is created. Each plot contains the experimental data, the fitted curve, and the weighted error for each dependent value.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::parameterFitting;
  mMap.insert(tmp);

  //fitting result plots
  tmp.first = 912;
  tmp.second.name = "Plots of Parameter Estimation Results per Dependent Value";
  tmp.second.description = "For each dependent value of the parameter estimation a plot is created. Each plot contains the experimental data, the fitted curves, and the weighted errors for each experiment a dependent value occurs.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::parameterFitting;
  mMap.insert(tmp);

  //fitting result plots
  tmp.first = 913;
  tmp.second.name = "Progress of Fit";
  tmp.second.description = "Plot of the sum of squares of residuals vs. number of function evaluations (for parameter estimation).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::parameterFitting;
  mMap.insert(tmp);

  //opt result plots
  tmp.first = 914;
  tmp.second.name = "Progress of Optimization";
  tmp.second.description = "Plot of the target function vs. number of function evaluations (for optimization).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::optimization;
  mMap.insert(tmp);

  //empty plot
  tmp.first = 998;
  tmp.second.name = "Empty";
  tmp.second.description = "A plot with nothing in it.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::unset;
  mMap.insert(tmp);

  // *****************************************************************

  //concentrations plot
  tmp.first = 200;
  tmp.second.name = "Scan of Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of the variable species concentrations, variable compartment volumes, and variable global quantity values vs. innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  //particle numbers plot
  tmp.first = 201;
  tmp.second.name = "Scan of Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of the variable species particle numbers, variable compartment volumes, and variable global quantity values vs. innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  //complete concentrations plot
  tmp.first = 202;
  tmp.second.name = "Scan of Complete Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of all the species concentrations, compartment volumes, and all global quantity values vs. innermost scan parameter (includes fixed ones).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  //complete particle numbers plot
  tmp.first = 203;
  tmp.second.name = "Scan of Complete Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A plot of all the species particle numbers, compartment volumes, and global quantity values vs. innermost scan parameter (includes fixed ones).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  //concentration rate plot
  tmp.first = 204;
  tmp.second.name = "Scan of Concentration Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A plot of the rate of change of concentrations of species, compartment volume, and global quantities, which are determined by ODEs or reactions vs. innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  //particle rate plot
  tmp.first = 205;
  tmp.second.name = "Scan of Particle Number Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A plot of the rate of change of particle numbers of all species, compartment volume, and global quantities, which are determined by ODEs or reactions vs. innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  //reaction particle flux
  tmp.first = 206;
  tmp.second.name = "Scan of Reaction Fluxes";
  tmp.second.description = "A plot of the fluxes of all reactions vs. innermost scan parameter, in concentration/time unit.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  //reaction particle flux
  tmp.first = 207;
  tmp.second.name = "Scan of Reaction Event Fluxes";
  tmp.second.description = "A plot of the fluxes of all reactions vs. innermost scan parameter, in reaction events/time unit.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  //eigenvalues plot
  tmp.first = 250;
  tmp.second.name = "Eigenvalues vs. scan parameter";
  tmp.second.description = "A plot of the real and imaginary parts of the eigenvalues of the Jacobian as a function of the innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::scan;
  tmp.second.mSecondaryTask = CCopasiTask::steadyState;
  mMap.insert(tmp);

  //parameter estimation residuals plot
  tmp.first = 251;
  tmp.second.name = "Parameter estimation target function vs. scan parameter";
  tmp.second.description = "A plot of the target function of parameter estimation as a function of the innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::scan;
  tmp.second.mSecondaryTask = CCopasiTask::parameterFitting;
  mMap.insert(tmp);

  //optimization residuals plot
  tmp.first = 252;
  tmp.second.name = "Optimization target function vs. scan parameter";
  tmp.second.description = "A plot of the target function of optimization as a function of the innermost scan parameter.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::scan;
  tmp.second.mSecondaryTask = CCopasiTask::optimization;
  mMap.insert(tmp);

  // *****************************************************************

  //now the reports
  tmp.first = 999;
  tmp.second.name = "-- Reports";
  tmp.second.description = "";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::unset;
  mMap.insert(tmp);

  //concentrations report
  tmp.first = 1000;
  tmp.second.name = "Time, Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of time, variable species concentrations, variable compartment volumes, and variable global quantity values.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1001;
  tmp.second.name = "Time, Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of time, variable species particle numbers, variable compartment volumes, and variable global quantity values.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1002;
  tmp.second.name = "Complete Time, Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of time, all species concentrations, all compartment volumes, and all global quantity values (includes fixed ones).";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1003;
  tmp.second.name = "Complete Time, Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of time, all species particle numbers, all compartment volumes, and all global quantity values (includes fixed ones).";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1004;
  tmp.second.name = "Time, Concentration Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A table of time and the rate of change of concentrations of species, compartment volumes, and global quantities which are determined by reactions or ODEs.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);  //not possible at the moment

  tmp.first = 1005;
  tmp.second.name = "Time, Particle Numbers Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A table of time and the rate of change of particle numbers of species, compartment volumes, and global quantities which are determined by reactions or ODEs.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1006;
  tmp.second.name = "Time and Reaction Fluxes";
  tmp.second.description = "A table of the fluxes of all reactions and time, in concentration/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1007;
  tmp.second.name = "Time and Reaction Event Fluxes";
  tmp.second.description = "A table of the fluxes of all reactions and time, in reaction events/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1008;
  tmp.second.name = "Time and all Variable Values (Concentration Units)";
  tmp.second.description = "This table includes all values which change over a time course. Species are measured in concentration unit and fluxes are in concentration/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1009;
  tmp.second.name = "Time and all Variable Values (Particle Number Units)";
  tmp.second.description = "This table includes all values which change over a time course. Species are measured in particle numbers and fluxes are in events/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //concentrations report
  tmp.first = 1200;
  tmp.second.name = "Scan Parameters, Time, Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of scan parameters, time, variable species concentrations, variable compartment volumes, and variable global quantity values.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  tmp.first = 1201;
  tmp.second.name = "Scan Parameters, Time, Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of scan parameters, time, variable species particle numbers, variable compartment volumes, and variable global quantity values.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  tmp.first = 1202;
  tmp.second.name = "Scan Parameters, Time, Complete Concentrations, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of scan parameters, time, all species concentrations, all compartment volumes, and all global quantity values (includes fixed ones).";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  tmp.first = 1203;
  tmp.second.name = "Scan Parameters, Time, Complete Particle Numbers, Volumes, and Global Quantity Values";
  tmp.second.description = "A table of scan parameters, time, all species particle numbers, all compartment volumes, and all global quantity values (includes fixed ones).";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  tmp.first = 1204;
  tmp.second.name = "Scan Parameters, Time, Concentration Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A table of scan parameters, time and the rate of change of concentrations of species, compartment volumes, and global quantities which are determined by reactions or ODEs.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);  //not possible at the moment

  tmp.first = 1205;
  tmp.second.name = "Scan Parameters, Time, Particle Numbers Rates, Volume Rates, and Global Quantity Rates";
  tmp.second.description = "A table of scan parameters, time and the rate of change of particle numbers of species, compartment volumes, and global quantities which are determined by reactions or ODEs.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  tmp.first = 1206;
  tmp.second.name = "Scan Parameters, Time and Reaction Fluxes";
  tmp.second.description = "A table of scan parameters and the fluxes of all reactions and time, in concentration/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  tmp.first = 1207;
  tmp.second.name = "Scan Parameters, Time and Reaction Event Fluxes";
  tmp.second.description = "A table of scan parameters and the fluxes of all reactions and time, in reaction events/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  tmp.first = 1208;
  tmp.second.name = "Scan Parameters, Time and all Variable Values (Concentration Units)";
  tmp.second.description = "This table includes scan parameters and all values which change over a time course. Species are measured in concentration unit and fluxes are in concentration/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  tmp.first = 1209;
  tmp.second.name = "Scan Parameters, Time and all Variable Values (Particle Number Units)";
  tmp.second.description = "This table includes scan parameters and all values which change over a time course. Species are measured in particle numbers and fluxes are in events/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::scan;
  mMap.insert(tmp);

  //eigenvalues report
  tmp.first = 1250;
  tmp.second.name = "Scan Parameters and Eigenvalues";
  tmp.second.description = "This table includes scan parameters and the real and imaginary parts of the eigenvalues of the reduced system's Jacobian.";
  tmp.second.isPlot = false;
  tmp.second.mTaskType = CCopasiTask::scan;
  tmp.second.mSecondaryTask = CCopasiTask::steadyState;
  mMap.insert(tmp);

  //parameter estimation target function  report
  tmp.first = 1251;
  tmp.second.name = "Scan Parameters and Target function of parameter estimation";
  tmp.second.description = "This table includes scan parameters and the target function of the parameter estimation.";
  tmp.second.isPlot = false;
  tmp.second.mTaskType = CCopasiTask::scan;
  tmp.second.mSecondaryTask = CCopasiTask::parameterFitting;
  mMap.insert(tmp);

  //optimization target function report
  tmp.first = 1252;
  tmp.second.name = "Scan Parameters and Target function of optimization";
  tmp.second.description = "This table includes scan parameters and the target function of the optimization.";
  tmp.second.isPlot = false;
  tmp.second.mTaskType = CCopasiTask::scan;
  tmp.second.mSecondaryTask = CCopasiTask::optimization;
  mMap.insert(tmp);

  tmp.first = 1999;
  tmp.second.name = "Empty";
  tmp.second.description = "A table with nothing in it.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::unset;
  mMap.insert(tmp);

  return true;
}

//static
CCopasiObject* COutputAssistant::createDefaultOutput(C_INT32 id, CCopasiTask * task, CCopasiDataModel* pDataModel, bool activate)
{
  if (task == NULL)
    {
      return NULL;
    }

  if (task->getProblem() == NULL)
    {
      return NULL;
    }

  CModel* pModel = task->getProblem()->getModel();

  if (pModel == NULL)
    {
      return NULL;
    }

  std::vector<const CCopasiObject*> data1, tmpdata;
  const CCopasiObject* data2 = NULL;

  //first handle the special cases (those not that are not numbered according to the systematic scheme)
  switch (id)
    {
      case 910:  // :TODO: Implement me!
      {
        CPlotSpecification * pPlotSpecification = NULL;
        CCopasiTask * pTask = (*pDataModel->getTaskList())["Parameter Estimation"];

        if (pTask == NULL) return NULL;

        CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(pTask->getProblem());

        if (pFitProblem == NULL) return NULL;

        const CExperimentSet & ExperimentSet = pFitProblem->getExperiementSet();
        size_t i, imax = ExperimentSet.getExperimentCount();

        std::vector< std::string > ChannelX;
        std::vector< std::string > Names;
        std::vector< unsigned C_INT32 > LineTypes;
        std::vector< unsigned C_INT32 > SymbolSubTypes;
        std::vector< unsigned C_INT32 > LineSubTypes;
        std::vector< std::string > Colors;

        unsigned C_INT32 colorcounter = 0;

        for (i = 0; i < imax; i++)
          {
            const CExperiment * pExperiment = ExperimentSet.getExperiment(i);
            const CCopasiVector< CFittingPoint > & FittingPoints = pExperiment->getFittingPoints();

            CCopasiVector< CFittingPoint >::const_iterator it = FittingPoints.begin();
            CCopasiVector< CFittingPoint >::const_iterator end = FittingPoints.end();

            if (it == end) continue;

            data2 =
              static_cast< const CCopasiObject * >((*it)->getObject(CCopasiObjectName("Reference=Independent Value")));

            for (; it != end; ++it)
              {
                std::string Name = (*it)->getObjectName();
                const CCopasiObject * pObject =
                  dynamic_cast< const CCopasiObject * >(pDataModel->getObject(Name));

                if (pObject != NULL)
                  Name = pObject->getObjectDisplayName();

                Name = pExperiment->getObjectName() + "," + Name;

                //1
                data1.push_back(static_cast< const CCopasiObject * >((*it)->getObject(CCopasiObjectName("Reference=Measured Value"))));
                ChannelX.push_back(data2->getCN());
                Names.push_back(Name + "(Measured Value)");
                LineTypes.push_back(3); //symbols & lines
                SymbolSubTypes.push_back(1); //fat cross
                LineSubTypes.push_back(1); //dotted
                Colors.push_back(CPlotColors::getCopasiColorStr(colorcounter));

                //2
                data1.push_back(static_cast< const CCopasiObject * >((*it)->getObject(CCopasiObjectName("Reference=Fitted Value"))));
                ChannelX.push_back(data2->getCN());
                Names.push_back(Name + "(Fitted Value)");

                if (pExperiment->getExperimentType() == CCopasiTask::timeCourse)
                  {
                    LineTypes.push_back(0); //curve
                    SymbolSubTypes.push_back(0); //default, this value is not used
                  }
                else
                  {
                    LineTypes.push_back(2); //symbols
                    SymbolSubTypes.push_back(1); //TODO
                  }

                LineSubTypes.push_back(0); //default, solid
                Colors.push_back(CPlotColors::getCopasiColorStr(colorcounter));

                //3
                data1.push_back(static_cast< const CCopasiObject * >((*it)->getObject(CCopasiObjectName("Reference=Weighted Error"))));
                ChannelX.push_back(data2->getCN());
                Names.push_back(Name + "(Weighted Error)");
                LineTypes.push_back(2); //symbols
                SymbolSubTypes.push_back(2); //circles
                LineSubTypes.push_back(0); //default, this value is not used
                Colors.push_back(CPlotColors::getCopasiColorStr(colorcounter));

                ++colorcounter;
              }
          }

        pPlotSpecification =
          createPlot(getItemName(id), data2, false, data1, false, getItem(id).mTaskType, pDataModel);

        if (pPlotSpecification != NULL)
          {
            CCopasiVector< CPlotItem > & Items = pPlotSpecification->getItems();
            CCopasiVector< CPlotItem >::const_iterator itItem = Items.begin();
            CCopasiVector< CPlotItem >::const_iterator endItem = Items.end();
            std::vector< std::string >::const_iterator itChannelX = ChannelX.begin();
            std::vector< std::string >::const_iterator itName = Names.begin();
            std::vector< unsigned C_INT32 >::const_iterator itLineType = LineTypes.begin();
            std::vector< unsigned C_INT32 >::const_iterator itSymbolSubType = SymbolSubTypes.begin();
            std::vector< unsigned C_INT32 >::const_iterator itLineSubType = LineSubTypes.begin();
            std::vector<std::string>::const_iterator itColor = Colors.begin();

            while (itItem != endItem)
              {
                (*itItem)->getChannels()[0] = CPlotDataChannelSpec(*itChannelX++);
                (*itItem)->setTitle(*itName++);
                (*itItem)->setActivity(COutputInterface::AFTER);
                (*itItem)->setValue("Line type", *itLineType++);
                (*itItem)->setValue("Symbol subtype", *itSymbolSubType++);
                (*itItem)->setValue("Line subtype", *itLineSubType++);
                (*itItem++)->setValue("Color", *itColor++);
              }
          }

        return pPlotSpecification;
      }
      break;

      case 911:
      {
        CPlotSpecification * pPlotSpecification = NULL;
        CCopasiTask * pTask = (*pDataModel->getTaskList())["Parameter Estimation"];

        if (pTask == NULL) return NULL;

        CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(pTask->getProblem());

        if (pFitProblem == NULL) return NULL;

        const CExperimentSet & ExperimentSet = pFitProblem->getExperiementSet();
        size_t i, imax = ExperimentSet.getExperimentCount();

        for (i = 0; i < imax; i++)
          {
            const CExperiment * pExperiment = ExperimentSet.getExperiment(i);
            const CCopasiVector< CFittingPoint > & FittingPoints = pExperiment->getFittingPoints();

            CCopasiVector< CFittingPoint >::const_iterator it = FittingPoints.begin();
            CCopasiVector< CFittingPoint >::const_iterator end = FittingPoints.end();

            if (it == end) continue;

            data2 = static_cast< const CCopasiObject * >((*it)->getObject(CCopasiObjectName("Reference=Independent Value")));
            data1.clear();

            for (; it != end; ++it)
              {
                data1.push_back(static_cast< const CCopasiObject * >((*it)->getObject(CCopasiObjectName("Reference=Measured Value"))));
                data1.push_back(static_cast< const CCopasiObject * >((*it)->getObject(CCopasiObjectName("Reference=Fitted Value"))));
                data1.push_back(static_cast< const CCopasiObject * >((*it)->getObject(CCopasiObjectName("Reference=Weighted Error"))));
              }

            pPlotSpecification =
              createPlot(pExperiment->getObjectName(), data2, false, data1, false, getItem(id).mTaskType, pDataModel);

            if (pPlotSpecification != NULL)
              {
                CCopasiVector< CPlotItem > & Items = pPlotSpecification->getItems();
                CCopasiVector< CPlotItem >::const_iterator itItem = Items.begin();
                CCopasiVector< CPlotItem >::const_iterator endItem = Items.end();
                it = FittingPoints.begin();

                unsigned C_INT32 LineType;

                if (pExperiment->getExperimentType() == CCopasiTask::timeCourse)
                  LineType = 0;
                else
                  LineType = 2;

                unsigned C_INT32 colorcounter = 0;

                while (itItem != endItem)
                  {
                    std::string Name = (*it++)->getObjectName();
                    const CCopasiObject * pObject =
                      dynamic_cast< const CCopasiObject * >(pDataModel->getObject(Name));

                    if (pObject != NULL)
                      Name = pObject->getObjectDisplayName();

                    (*itItem)->setTitle(Name + "(Measured Value)");
                    (*itItem)->setActivity(COutputInterface::AFTER);
                    (*itItem)->setValue("Line type", (unsigned C_INT32) 3); //symbols and lines
                    (*itItem)->setValue("Symbol subtype", (unsigned C_INT32) 1); //fat cross
                    (*itItem)->setValue("Line subtype", (unsigned C_INT32) 1); //dotted
                    (*itItem++)->setValue("Color", CPlotColors::getCopasiColorStr(colorcounter));

                    (*itItem)->setTitle(Name + "(Fitted Value)");
                    (*itItem)->setActivity(COutputInterface::AFTER);
                    (*itItem)->setValue("Line type", (unsigned C_INT32) LineType);
                    (*itItem)->setValue("Symbol subtype", (unsigned C_INT32) 0);
                    (*itItem++)->setValue("Color", CPlotColors::getCopasiColorStr(colorcounter));

                    (*itItem)->setTitle(Name + "(Weighted Error)");
                    (*itItem)->setActivity(COutputInterface::AFTER);
                    (*itItem)->setValue("Line type", (unsigned C_INT32) 2);
                    (*itItem)->setValue("Symbol subtype", (unsigned C_INT32) 2);
                    (*itItem++)->setValue("Color", CPlotColors::getCopasiColorStr(colorcounter));

                    ++colorcounter;
                  }
              }
          }

        return pPlotSpecification;
      }
      break;

      case 912:
      {
        CPlotSpecification * pPlotSpecification = NULL;
        CCopasiTask * pTask = (*pDataModel->getTaskList())["Parameter Estimation"];

        if (pTask == NULL) return NULL;

        CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(pTask->getProblem());

        if (pFitProblem == NULL) return NULL;

        const CExperimentSet & ExperimentSet = pFitProblem->getExperiementSet();
        size_t i, imax = ExperimentSet.getExperimentCount();

        std::map< const CCopasiObject *, CPlotSpecification * > PlotSpecMap;
        std::map< const CCopasiObject *, CPlotSpecification * >::iterator Found;

        for (i = 0; i < imax; i++)
          {
            const CExperiment * pExperiment = ExperimentSet.getExperiment(i);
            const CCopasiVector< CFittingPoint > & FittingPoints = pExperiment->getFittingPoints();

            CCopasiVector< CFittingPoint >::const_iterator it = FittingPoints.begin();
            CCopasiVector< CFittingPoint >::const_iterator end = FittingPoints.end();

            if (it == end) continue;

            std::string Name = pExperiment->getObjectName();
            CPlotDataChannelSpec ChannelX =
              (*it)->getObject(CCopasiObjectName("Reference=Independent Value"))->getCN();
            unsigned C_INT32 LineType;

            if (pExperiment->getExperimentType() == CCopasiTask::timeCourse)
              LineType = 0;
            else
              LineType = 2;

            for (; it != end; ++it)
              {
                const CCopasiObject * pObject =
                  dynamic_cast< const CCopasiObject * >(pDataModel->getObject((*it)->getObjectName()));

                if (pObject == NULL) continue;

                if ((Found = PlotSpecMap.find(pObject)) != PlotSpecMap.end())
                  pPlotSpecification = Found->second;
                else
                  {
                    unsigned C_INT32 i = 0;
                    std::ostringstream sname;
                    sname << pObject->getObjectDisplayName();

                    while (!(pPlotSpecification =
                               pDataModel->getPlotDefinitionList()->createPlotSpec(sname.str(),
                                   CPlotItem::plot2d)))
                      {
                        i++;
                        sname.str("");
                        sname << pObject->getObjectDisplayName() << "_" << i;
                      }

                    PlotSpecMap[pObject] = pPlotSpecification;
                  }

                if (pPlotSpecification != NULL)
                  {
                    //first determine color for the current curves
                    unsigned C_INT32 colorindex = (pPlotSpecification->getItems().size() / 3);

                    CPlotItem * pItem =
                      pPlotSpecification->createItem(Name + "(Measured Value)", CPlotItem::curve2d);
                    pItem->setActivity(COutputInterface::AFTER);
                    pItem->setValue("Line type", (unsigned C_INT32) 3); //symbols and lines
                    pItem->setValue("Line subtype", (unsigned C_INT32) 1); //dotted
                    pItem->setValue("Symbol subtype", (unsigned C_INT32) 1); //fat cross
                    pItem->setValue("Color", CPlotColors::getCopasiColorStr(colorindex));
                    pItem->addChannel(ChannelX);
                    pItem->addChannel((*it)->getObject(CCopasiObjectName("Reference=Measured Value"))->getCN());

                    pItem =
                      pPlotSpecification->createItem(Name + "(Fitted Value)", CPlotItem::curve2d);
                    pItem->setActivity(COutputInterface::AFTER);
                    pItem->setValue("Line type", LineType);
                    pItem->setValue("Symbol subtype", (unsigned C_INT32) 0);
                    pItem->setValue("Color", CPlotColors::getCopasiColorStr(colorindex));
                    pItem->addChannel(ChannelX);
                    pItem->addChannel((*it)->getObject(CCopasiObjectName("Reference=Fitted Value"))->getCN());

                    pItem =
                      pPlotSpecification->createItem(Name + "(Weighted Error)", CPlotItem::curve2d);
                    pItem->setActivity(COutputInterface::AFTER);
                    pItem->setValue("Line type", (unsigned C_INT32) 2);
                    pItem->setValue("Symbol subtype", (unsigned C_INT32) 2);
                    pItem->setValue("Color", CPlotColors::getCopasiColorStr(colorindex));
                    pItem->addChannel(ChannelX);
                    pItem->addChannel((*it)->getObject(CCopasiObjectName("Reference=Weighted Error"))->getCN());
                  }
              }
          }

        return pPlotSpecification;
      }
      break;

      case 913:
      {
        CPlotSpecification * pPlotSpecification = NULL;
        CCopasiTask * pTask = (*pDataModel->getTaskList())["Parameter Estimation"];

        if (pTask == NULL) return NULL;

        CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(pTask->getProblem());

        if (pFitProblem == NULL) return NULL;

        //        const C_FLOAT64 & SolutionValue = pFitProblem->getSolutionValue();

        data2 = static_cast< const CCopasiObject * >(pFitProblem->getObject(CCopasiObjectName("Reference=Function Evaluations")));
        data1.clear();
        data1.push_back(static_cast< const CCopasiObject * >(pFitProblem->getObject(CCopasiObjectName("Reference=Best Value"))));

        pPlotSpecification =
          createPlot("Progress of Fit" , data2, false, data1, false,  getItem(id).mTaskType, pDataModel);

        if (pPlotSpecification != NULL)
          {
            pPlotSpecification->setLogY(true);
            CCopasiVector< CPlotItem > & Items = pPlotSpecification->getItems();
            CCopasiVector< CPlotItem >::const_iterator itItem = Items.begin();
            CCopasiVector< CPlotItem >::const_iterator endItem = Items.end();

            while (itItem != endItem)
              {
                (*itItem)->setTitle("sum of squares");
                (*itItem)->setActivity(COutputInterface::DURING);
                (*itItem++)->setValue("Line type", (unsigned C_INT32) 0);
              }
          }

        return pPlotSpecification;
      }
      break;

      case 914:
      {
        CPlotSpecification * pPlotSpecification = NULL;
        CCopasiTask * pTask = (*pDataModel->getTaskList())["Optimization"];

        if (pTask == NULL) return NULL;

        COptProblem * pOptProblem = dynamic_cast< COptProblem * >(pTask->getProblem());

        if (pOptProblem == NULL) return NULL;

        //        const C_FLOAT64 & SolutionValue = pFitProblem->getSolutionValue();

        data2 = static_cast< const CCopasiObject * >(pOptProblem->getObject(CCopasiObjectName("Reference=Function Evaluations")));

        data1.clear();
        data1.push_back(static_cast< const CCopasiObject * >(pOptProblem->getObject(CCopasiObjectName("Reference=Best Value"))));

        pPlotSpecification =
          createPlot("Progress of Optimization" , data2, false, data1, false, getItem(id).mTaskType, pDataModel);

        if (pPlotSpecification != NULL)
          {
            pPlotSpecification->setLogY(true);
            CCopasiVector< CPlotItem > & Items = pPlotSpecification->getItems();
            CCopasiVector< CPlotItem >::const_iterator itItem = Items.begin();
            CCopasiVector< CPlotItem >::const_iterator endItem = Items.end();

            while (itItem != endItem)
              {
                (*itItem)->setTitle("target function");
                (*itItem)->setActivity(COutputInterface::DURING);
                (*itItem++)->setValue("Line type", (unsigned C_INT32) 0);
              }
          }

        return pPlotSpecification;
      }
      break;
    }

  //now deal with the systematically numbered cases
  bool isReport = (id >= 1000);
  C_INT32 idMod = id % 200;
  bool logY = false; //this is onyl used for plots; it indicates whether the y axis is plotted logarithmically

  const CCopasiObject* pTime = static_cast< const CCopasiObject * >(pModel->getObject(CCopasiObjectName("Reference=Time")));

  switch (idMod)
    {
      case 0:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_CONCENTRATIONS, pModel);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_COMPARTMENT_VOLUMES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 1:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_NUMBERS, pModel);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_COMPARTMENT_VOLUMES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 2:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_CONCENTRATIONS, pModel);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::COMPARTMENT_VOLUMES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::GLOBAL_PARAMETER_VALUES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 3:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_NUMBERS, pModel);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::COMPARTMENT_VOLUMES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::GLOBAL_PARAMETER_VALUES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 4:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_CONC_RATES, pModel);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::COMPARTMENT_RATES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::GLOBAL_PARAMETER_RATES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 5:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_PART_RATES, pModel);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::COMPARTMENT_RATES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::GLOBAL_PARAMETER_RATES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 6:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::REACTION_CONC_FLUXES, pModel);
        break;

      case 7:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::REACTION_PART_FLUXES, pModel);
        break;

      case 8:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_CONCENTRATIONS, pModel);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_COMPARTMENT_VOLUMES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_CONC_RATES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::COMPARTMENT_RATES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::GLOBAL_PARAMETER_RATES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::REACTION_CONC_FLUXES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_TRANSITION_TIME, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 9:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_NUMBERS, pModel);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_COMPARTMENT_VOLUMES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_PART_RATES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::COMPARTMENT_RATES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::GLOBAL_PARAMETER_RATES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::REACTION_PART_FLUXES, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::METAB_TRANSITION_TIME, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 50:
        data1 =
          CObjectLists::getListOfConstObjects(CObjectLists::REDUCED_JACOBIAN_EV_RE, pModel);
        tmpdata =
          CObjectLists::getListOfConstObjects(CObjectLists::REDUCED_JACOBIAN_EV_IM, pModel);
        data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
        break;

      case 51: //parameter estimation target function
      {
        CCopasiTask * pTask = (*pDataModel->getTaskList())["Parameter Estimation"];

        if (pTask == NULL) break;

        CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(pTask->getProblem());

        if (pFitProblem == NULL) break;

        data1.push_back(static_cast< const CCopasiObject * >(pFitProblem->getObject(CCopasiObjectName("Reference=Best Value"))));
        logY = true;
      }
      break;

      case 52: //optimization target function
      {
        CCopasiTask * pTask = (*pDataModel->getTaskList())["Optimization"];

        if (pTask == NULL) break;

        COptProblem * pOptProblem = dynamic_cast< COptProblem * >(pTask->getProblem());

        if (pOptProblem == NULL) break;

        data1.push_back(static_cast< const CCopasiObject * >(pOptProblem->getObject(CCopasiObjectName("Reference=Best Value"))));
      }
      break;
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
                  std::string tmpString = * pSP->getScanItem(i)->getValue("Object").pCN;

                  if (tmpString.size()) //the scan item references an object, this is the scan parameter
                    {
                      CCopasiDataModel* pDataModel = pSP->getObjectDataModel();
                      assert(pDataModel != NULL);
                      const CCopasiObject * tmpObject = pDataModel->getDataObject(tmpString);

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
                  std::string tmpString = * pSP->getScanItem(i)->getValue("Object").pCN;

                  if (tmpString.size()) //the scan item references an object, this is the scan parameter
                    {
                      CCopasiDataModel* pDataModel = pSP->getObjectDataModel();
                      assert(pDataModel != NULL);
                      const CCopasiObject * tmpObject = pDataModel->getDataObject(tmpString);

                      if (tmpObject)
                        {
                          data2 = tmpObject; //we only keep the last scan parameter we find, this is the innermost loop.
                          logX = pSP->getScanItem(i)->getValue("log").pBOOL;
                        }
                    }
                }
            }
        }
      else //time is on the x-axis
        {
          data2 = pTime;
        }

      return createPlot(getItemName(id), data2, logX, data1, logY, getItem(id).mTaskType, pDataModel);
    }

  return NULL;
}

#include "plot/COutputDefinitionVector.h"

//static
CPlotSpecification* COutputAssistant::createPlot(const std::string & name,
    const CCopasiObject * x,
    bool logX,
    const std::vector<const CCopasiObject*> & y,
    bool logY,
    const CCopasiTask::Type & /* taskType */,
    CCopasiDataModel* pDataModel)
{
  if (!x) return NULL;

  std::vector<const CCopasiObject *>::const_iterator it, itEnd = y.end();

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

  // Set the task type
  // :TODO: This is currently not implemented for plots.

  //create curves

  CPlotDataChannelSpec name1 = x->getCN();
  CPlotDataChannelSpec name2;
  std::string itemTitle;
  CPlotItem * plItem;

  for (it = y.begin(); it != itEnd; ++it)
    {
      if (!(*it)) continue;

      name2 = (*it)->getCN();
      itemTitle = static_cast< const CCopasiObject *>(*it)->getObjectDisplayName();

      plItem = pPl->createItem(itemTitle, CPlotItem::curve2d);
      plItem->addChannel(name1);
      plItem->addChannel(name2);
    }

  pPl->setLogX(logX);
  pPl->setLogY(logY);
  return pPl;
}

//static
CReportDefinition* COutputAssistant::createTable(const std::string & name,
    const std::vector<const CCopasiObject *> & d,
    const std::string & comment,
    const CCopasiTask::Type & taskType,
    CCopasiDataModel* pDataModel)
{
  std::vector<const CCopasiObject * >::const_iterator it, itEnd = d.end();

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
  pReport->setSeparator(CCopasiReportSeparator("\t"));

  for (it = d.begin(); it != itEnd; ++it)
    {
      if (!(*it)) continue;

      pReport->getTableAddr()->push_back((*it)->getCN());
    }

  return pReport;
}
