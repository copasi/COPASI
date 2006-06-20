/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/COutputAssistant.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/06/20 13:19:50 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
#include "plot/COutputDefinitionVector.h"
#include "parameterFitting/CFitProblem.h"
#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CExperiment.h"

//******* COutputAssistant **********************************

//static member variables
COutputAssistant::Map COutputAssistant::mMap;
const std::string COutputAssistant::emptyString("");
const CDefaultOutputDescription COutputAssistant::emptyItem;

//static
std::vector<C_INT32> COutputAssistant::getListOfDefaultOutputDescriptions(const CCopasiProblem * problem)
{
  //initializes the map on first call only
  initialize();

  std::vector<C_INT32> ret;

  problem = NULL; //DEBUG only!!!
  if (!problem) //generate full list
    {
      Map::const_iterator it, itEnd = mMap.end();
      for (it = mMap.begin(); it != itEnd; ++it)
        ret.push_back(it->first);

      return ret;
    }

  const CModel* pModel = problem->getModel();
  if (!pModel) return ret;

  //TODO use CObjectLists::existsFixedMetab()

  const CTrajectoryProblem* tp = dynamic_cast<const CTrajectoryProblem*>(problem);
  if (tp)
    {
      return ret;
    }

  const CSteadyStateProblem* ssp = dynamic_cast<const CSteadyStateProblem*>(problem);
  if (ssp)
    {
      return ret;
    }

  return ret;
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
  tmp.second.name = "Concentrations plot";
  tmp.second.description = "A plot of the variable metabolite concentrations vs. time. It does not contain the concentrations of fixed metabolites.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //particle numbers plot
  tmp.first = 1;
  tmp.second.name = "Particle numbers plot";
  tmp.second.description = "A plot of the variable metabolite particle numbers vs. time. It does not contain the particle numbers of fixed metabolites.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //complete concentrations plot
  tmp.first = 2;
  tmp.second.name = "Complete concentrations plot";
  tmp.second.description = "A plot of all the metabolite concentrations vs. time (including fixed metabolites).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //complete particle numbers plot
  tmp.first = 3;
  tmp.second.name = "Complete particle numbers plot";
  tmp.second.description = "A plot of all the metabolite particle numbers vs. time (including fixed metabolites).";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //concentration rate plot
  tmp.first = 4;
  tmp.second.name = "Concentration rates plot";
  tmp.second.description = "A plot of the rate of change of all variable metabolite concentrations vs. time. It does not contain the rates of fixed metabolites.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp); //not possible at the moment

  //particle rate plot
  tmp.first = 5;
  tmp.second.name = "Particle number rates plot";
  tmp.second.description = "A plot of the rate of change of all variable metabolite particle numbers vs. time. It does not contain the rates of fixed metabolites.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //reaction particle flux
  tmp.first = 6;
  tmp.second.name = "Plot of reaction fluxes";
  tmp.second.description = "A plot of the fluxes of all reactions vs. time, in concentration/time unit.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //reaction particle flux
  tmp.first = 7;
  tmp.second.name = "Plot of reaction event fluxes";
  tmp.second.description = "A plot of the fluxes of all reactions vs. time, in reaction events/time unit.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  //fitting result plots
  tmp.first = 10;
  tmp.second.name = "Plots of parameter estimation results";
  tmp.second.description = "For each experiment of the parameter estimation a plot is created. Each plot contains the experimental data, the fitted curve, and the weighted error for each dependent vale.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::parameterFitting;
  mMap.insert(tmp);

  //empty plot
  tmp.first = 99;
  tmp.second.name = "Empty plot";
  tmp.second.description = "A plot with nothing in it.";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::unset;
  mMap.insert(tmp);

  //now the reports
  tmp.first = 999;
  tmp.second.name = "-- Reports";
  tmp.second.description = "";
  tmp.second.isPlot = true;
  tmp.second.mTaskType = CCopasiTask::unset;
  mMap.insert(tmp);

  //concentrations report
  tmp.first = 1000;
  tmp.second.name = "Concentrations table with time";
  tmp.second.description = "A table of the variable metabolite concentrations and time. It does not contain the concentrations of fixed metabolites.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1001;
  tmp.second.name = "Particle numbers table with time";
  tmp.second.description = "A table of the variable metabolite particle numbers and time. It does not contain the particle numbers of fixed metabolites.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1002;
  tmp.second.name = "Complete concentrations table with time";
  tmp.second.description = "A table of all metabolite concentrations (including fixed metabolites) and time.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1003;
  tmp.second.name = "Complete particle numbers table with time";
  tmp.second.description = "A table of all metabolite particle numbers (including fixed metabolites) and time.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1004;
  tmp.second.name = "Concentration rates table with time";
  tmp.second.description = "A table of the rate of change of all variable metabolite concentrations and time. It does not contain the rates of fixed metabolites.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);  //not possible at the moment

  tmp.first = 1005;
  tmp.second.name = "Particle number rates table with time";
  tmp.second.description = "A table of the rate of change of all variable metabolite particle numbers and time. It does not contain the rates of fixed metabolites.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1006;
  tmp.second.name = "Table of reaction fluxes with time";
  tmp.second.description = "A table of the fluxes of all reactions and time, in concentration/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1007;
  tmp.second.name = "Table of reaction event fluxes with time";
  tmp.second.description = "A table of the fluxes of all reactions and time, in reaction events/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1008;
  tmp.second.name = "Table of concentrations and fluxes with time";
  tmp.second.description = "A table of the concentrations of the variable metabolites, the fluxes of all reactions, and time. Fluxes are in concentration/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1009;
  tmp.second.name = "Table of particle numbers and fluxes with time";
  tmp.second.description = "A table of the particle numbers of the variable metabolites, the fluxes of all reactions, and time. Fluxes are in particle/time unit.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::timeCourse;
  mMap.insert(tmp);

  tmp.first = 1999;
  tmp.second.name = "Empty table";
  tmp.second.description = "A table with nothing in it.";
  tmp.second.isPlot = false; //report
  tmp.second.mTaskType = CCopasiTask::unset;
  mMap.insert(tmp);

  return true;
}

//static
CCopasiObject* COutputAssistant::createDefaultOutput(C_INT32 id, CCopasiTask * task, bool activate)
{
  if (!task)
    {
      //std::cout << "task==NULL in COutputAssistant::createDefaultOutput()" << std::endl;
      return NULL;
    }
  if (!task->getProblem())
    {
      //std::cout << "problem==NULL in COutputAssistant::createDefaultOutput()" << std::endl;
      return NULL;
    }

  CModel* pModel = task->getProblem()->getModel();
  if (!pModel)
    {
      //std::cout << "model==NULL in COutputAssistant::createDefaultOutput()" << std::endl;
      return NULL;
    }

  bool isReport = (id >= 1000);
  C_INT32 idMod = id % 1000;

  const CCopasiObject* pTime = pModel->getObject(CCopasiObjectName("Reference=Time"));

  std::vector<const CCopasiObject*> data1, tmpdata;
  const CCopasiObject* data2;

  switch (idMod)
    {
    case 0:
      data1 = CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_CONCENTRATIONS, pModel);
      break;
    case 1:
      data1 = CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_NUMBERS, pModel);
      break;
    case 2:
      data1 = CObjectLists::getListOfConstObjects(CObjectLists::ALL_METAB_CONCENTRATIONS, pModel);
      break;
    case 3:
      data1 = CObjectLists::getListOfConstObjects(CObjectLists::ALL_METAB_NUMBERS, pModel);
      break;
    case 4:
      data1 = CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_CONC_RATES, pModel);
      break; //not possible at the moment
    case 5:
      data1 = CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_PART_RATES, pModel);
      break;
    case 6:
      data1 = CObjectLists::getListOfConstObjects(CObjectLists::REACTION_CONC_FLUXES, pModel);
      break;
    case 7:
      data1 = CObjectLists::getListOfConstObjects(CObjectLists::REACTION_PART_FLUXES, pModel);
      break;
    case 8:
      data1 = CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_CONCENTRATIONS, pModel);
      tmpdata = CObjectLists::getListOfConstObjects(CObjectLists::REACTION_CONC_FLUXES, pModel);
      data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
      break;
    case 9:
      data1 = CObjectLists::getListOfConstObjects(CObjectLists::NON_CONST_METAB_NUMBERS, pModel);
      tmpdata = CObjectLists::getListOfConstObjects(CObjectLists::REACTION_PART_FLUXES, pModel);
      data1.insert(data1.end(), tmpdata.begin(), tmpdata.end());
      break;

    case 10:
      CPlotSpecification * pPlotSpecification = NULL;
      CCopasiTask * pTask = (*CCopasiDataModel::Global->getTaskList())["Parameter Estimation"];
      if (pTask == NULL) return NULL;

      CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(pTask->getProblem());
      if (pFitProblem == NULL) return NULL;

      const CExperimentSet & ExperimentSet = pFitProblem->getExperiementSet();
      unsigned C_INT32 i, imax = ExperimentSet.size();

      for (i = 0; i < imax; i++)
        {
          const CExperiment * pExperiment = ExperimentSet.getExperiment(i);
          const CCopasiVector< CFittingPoint > & FittingPoints = pExperiment->getFittingPoints();

          CCopasiVector< CFittingPoint >::const_iterator it = FittingPoints.begin();
          CCopasiVector< CFittingPoint >::const_iterator end = FittingPoints.end();

          if (it == end) continue;

          data2 = (*it)->getObject(CCopasiObjectName("Reference=Independent Value"));
          data1.clear();

          for (; it != end; ++it)
            {
              data1.push_back((*it)->getObject(CCopasiObjectName("Reference=Measured Value")));
              data1.push_back((*it)->getObject(CCopasiObjectName("Reference=Fitted Value")));
              data1.push_back((*it)->getObject(CCopasiObjectName("Reference=Weighted Error")));
            }

          pPlotSpecification =
            createPlot(pExperiment->getObjectName(), data2, data1, getItem(id).mTaskType);

          const CCopasiVector< CPlotItem > & Items = pPlotSpecification->getItems();
          CCopasiVector< CPlotItem >::const_iterator itItem = Items.begin();
          CCopasiVector< CPlotItem >::const_iterator endItem = Items.end();
          it = FittingPoints.begin();

          unsigned C_INT32 LineType;
          if (pExperiment->getExperimentType() == CCopasiTask::timeCourse)
            LineType = 0;
          else
            LineType = 2;

          while (itItem != endItem)
            {
              std::string Name = (*it++)->getObjectName();
              CCopasiObject * pObject = CCopasiContainer::ObjectFromName(Name);
              if (pObject != NULL)
                Name = pObject->getObjectDisplayName();

              const_cast< CPlotItem *>(*itItem)->setTitle(Name + "(Measured Value)");
              const_cast< CPlotItem *>(*itItem)->setActivity(COutputInterface::AFTER);
              const_cast< CPlotItem *>(*itItem++)->setValue("Line type", (unsigned C_INT32) 2);

              const_cast< CPlotItem *>(*itItem)->setTitle(Name + "(Fitted Value)");
              const_cast< CPlotItem *>(*itItem)->setActivity(COutputInterface::AFTER);
              const_cast< CPlotItem *>(*itItem++)->setValue("Line type", (unsigned C_INT32) LineType);

              const_cast< CPlotItem *>(*itItem)->setTitle(Name + "(Weighted Error)");
              const_cast< CPlotItem *>(*itItem)->setActivity(COutputInterface::AFTER);
              const_cast< CPlotItem *>(*itItem++)->setValue("Line type", (unsigned C_INT32) 2);
            }
        }

      return pPlotSpecification;
      break;
    }

  if (isReport)
    {
      data1.insert(data1.begin(), pTime);
      CReportDefinition* pReportDef = createTable(getItemName(id), data1, getItem(id).description, getItem(id).mTaskType);
      if (activate && pReportDef)
        {
          task->getReport().setReportDefinition(pReportDef);
          //TODO: also set a default filename?
        }
      return pReportDef;
    }
  else //plot
    {
      data2 = pTime;
      return createPlot(getItemName(id), data2, data1, getItem(id).mTaskType);
    }

  return NULL;
}

#include "plot/COutputDefinitionVector.h"

//static
CPlotSpecification* COutputAssistant::createPlot(const std::string & name,
    const CCopasiObject* x,
    const std::vector<const CCopasiObject*> & y,
    const CCopasiTask::Type & /* taskType */)
{
  if (!x) return NULL;

  std::vector<const CCopasiObject*>::const_iterator it, itEnd = y.end();

#ifdef COPASI_DEBUG
  std::cout << "COutputAssistant::createPlot:" << std::endl;
  std::cout << " name: " << name << std::endl;

  std::cout << x -> getObjectDisplayName() << std::endl;

  for (it = y.begin(); it != itEnd; ++it)
    std::cout << (*it)->getObjectDisplayName() << std::endl;
#endif // COPASI_DEBUG

  //create plot with unique name
  unsigned C_INT32 i = 0;
  CPlotSpecification* pPl;
  std::ostringstream sname;
  sname << name;
  while (!(pPl = CCopasiDataModel::Global->getPlotDefinitionList()->createPlotSpec(sname.str(),
                 CPlotItem::plot2d)))
    {
      i++;
      sname.str("");
      sname << name << "_" << i;
    }

  // Set the task type
  // :TODO: This is currently not implmented for plots.

  //create curves

  CPlotDataChannelSpec name1 = x->getCN();
  CPlotDataChannelSpec name2;
  std::string itemTitle;
  CPlotItem * plItem;

  for (it = y.begin(); it != itEnd; ++it)
    {
      if (!(*it)) continue;
      name2 = (*it)->getCN();
      itemTitle = (*it)->getObjectDisplayName();
      //std::cout << itemTitle << " : " << name2 << std::endl;

      plItem = pPl->createItem(itemTitle, CPlotItem::curve2d);
      plItem->addChannel(name1);
      plItem->addChannel(name2);
    }

  return pPl;
}

//static
CReportDefinition* COutputAssistant::createTable(const std::string & name,
    const std::vector<const CCopasiObject*> & d,
    const std::string & comment,
    const CCopasiTask::Type & taskType)
{
  std::vector<const CCopasiObject*>::const_iterator it, itEnd = d.end();

#ifdef COPASI_DEBUG
  std::cout << "COutputAssistant::createTable:" << std::endl;
  std::cout << " name: " << name << std::endl;
  for (it = d.begin(); it != itEnd; ++it)
    std::cout << (*it)->getObjectDisplayName() << std::endl;
#endif // COPASI_DEBUG

  //create plot with unique name
  unsigned C_INT32 i = 0;
  CReportDefinition * pReport = NULL;
  std::ostringstream sname;
  sname << name;
  while (!(pReport = CCopasiDataModel::Global->getReportDefinitionList()->createReportDefinition(sname.str(), comment)))
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
