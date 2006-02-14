/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/COutputAssistant.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/02/14 14:35:30 $
   End CVS Header */

#include "COutputAssistant.h"
#include "report/CCopasiObject.h"
#include "utilities/CCopasiProblem.h"
#include "utilities/CCopasiTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "steadystate/CSteadyStateProblem.h"
#include "model/CObjectLists.h"
#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "plot/COutputDefinitionVector.h"
#include "report/CReportDefinition.h"
#include "report/CReportDefinitionVector.h"

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

  //concentrations plot
  tmp.first = 0;
  tmp.second.name = "Concentrations plot";
  tmp.second.description = "A plot of the variable metabolite concentrations vs. time.\nIt does not contain the concentrations of fixed metabolites.";
  tmp.second.isPlot = true;
  mMap.insert(tmp);

  //particle numbers plot
  tmp.first = 1;
  tmp.second.name = "Particle numbers plot";
  tmp.second.description = "A plot of the variable metabolite particle numbers vs. time.\nIt does not contain the particle numbers of fixed metabolites.";
  tmp.second.isPlot = true;
  mMap.insert(tmp);

  //complete concentrations plot
  tmp.first = 2;
  tmp.second.name = "Complete concentrations plot";
  tmp.second.description = "A plot of all the metabolite concentrations vs. time (including fixed metabolites).";
  tmp.second.isPlot = true;
  mMap.insert(tmp);

  //complete particle numbers plot
  tmp.first = 3;
  tmp.second.name = "Complete particle numbers plot";
  tmp.second.description = "A plot of all the metabolite particle numbers vs. time (including fixed metabolites).";
  tmp.second.isPlot = true;
  mMap.insert(tmp);

  //concentration rate plot
  tmp.first = 4;
  tmp.second.name = "Concentration rates plot";
  tmp.second.description = "A plot of the rate of change of all variable metabolite concentrations vs. time.\nIt does not contain the rates of fixed metabolites.";
  tmp.second.isPlot = true;
  mMap.insert(tmp); //not possible at the moment

  //particle rate plot
  tmp.first = 5;
  tmp.second.name = "Particle number rates plot";
  tmp.second.description = "A plot of the rate of change of all variable metabolite particle numbers vs. time.\nIt does not contain the rates of fixed metabolites.";
  tmp.second.isPlot = true;
  mMap.insert(tmp);

  //reaction particle flux
  tmp.first = 6;
  tmp.second.name = "Plot of reaction fluxes";
  tmp.second.description = "A plot of the fluxes of all reactions vs. time, in concentration/time unit.";
  tmp.second.isPlot = true;
  mMap.insert(tmp);

  //reaction particle flux
  tmp.first = 7;
  tmp.second.name = "Plot of reaction event fluxes";
  tmp.second.description = "A plot of the fluxes of all reactions vs. time, in reaction events/time unit.";
  tmp.second.isPlot = true;
  mMap.insert(tmp);

  //empty plot
  tmp.first = 999;
  tmp.second.name = "Empty plot";
  tmp.second.description = "A plot with nothing in it.";
  tmp.second.isPlot = true;
  mMap.insert(tmp);

  //now the reports

  //concentrations report
  tmp.first = 1000;
  tmp.second.name = "Concentrations table with time";
  tmp.second.description = "A table of the variable metabolite concentrations and time.\nIt does not contain the concentrations of fixed metabolites.";
  tmp.second.isPlot = false; //report
  mMap.insert(tmp);

  tmp.first = 1001;
  tmp.second.name = "Particle numbers table with time";
  tmp.second.description = "A table of the variable metabolite particle numbers and time.\nIt does not contain the particle numbers of fixed metabolites.";
  tmp.second.isPlot = false; //report
  mMap.insert(tmp);

  tmp.first = 1002;
  tmp.second.name = "Complete concentrations table with time";
  tmp.second.description = "A table of all metabolite concentrations (including fixed metabolites) and time.";
  tmp.second.isPlot = false; //report
  mMap.insert(tmp);

  tmp.first = 1003;
  tmp.second.name = "Complete particle numbers table with time";
  tmp.second.description = "A table of all metabolite particle numbers (including fixed metabolites) and time.";
  tmp.second.isPlot = false; //report
  mMap.insert(tmp);

  tmp.first = 1004;
  tmp.second.name = "Concentration rates table with time";
  tmp.second.description = "A table of the rate of change of all variable metabolite concentrations and time.\nIt does not contain the rates of fixed metabolites.";
  tmp.second.isPlot = false; //report
  mMap.insert(tmp);  //not possible at the moment

  tmp.first = 1005;
  tmp.second.name = "Particle number rates table with time";
  tmp.second.description = "A table of the rate of change of all variable metabolite particle numbers and time.\nIt does not contain the rates of fixed metabolites.";
  tmp.second.isPlot = false; //report
  mMap.insert(tmp);

  tmp.first = 1006;
  tmp.second.name = "Table of reaction fluxes with time";
  tmp.second.description = "A table of the fluxes of all reactions and time, in concentration/time unit.";
  tmp.second.isPlot = false; //report
  mMap.insert(tmp);

  tmp.first = 1007;
  tmp.second.name = "Table of reaction event fluxes with time";
  tmp.second.description = "A table of the fluxes of all reactions and time, in reaction events/time unit.";
  tmp.second.isPlot = false; //report
  mMap.insert(tmp);

  tmp.first = 1008;
  tmp.second.name = "Table of concentrations and fluxes with time";
  tmp.second.description = "A table of the concentrations of the variable metabolites, the fluxes of all reactions, and time. Fluxes are in concentration/time unit.";
  tmp.second.isPlot = false; //report
  mMap.insert(tmp);

  tmp.first = 1009;
  tmp.second.name = "Table of particle numbers and fluxes with time";
  tmp.second.description = "A table of the particle numbers of the variable metabolites, the fluxes of all reactions, and time. Fluxes are in particle/time unit.";
  tmp.second.isPlot = false; //report
  mMap.insert(tmp);

  tmp.first = 1999;
  tmp.second.name = "Empty table";
  tmp.second.description = "A table with nothing in it.";
  tmp.second.isPlot = false; //report
  mMap.insert(tmp);

  return true;
}

//static
CCopasiObject* COutputAssistant::createDefaultOutput(C_INT32 id, CCopasiTask * task)
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
    }

  if (isReport)
    {
      data1.insert(data1.begin(), pTime);
      return createTable(getItemName(id), data1, getItem(id).description);
    }
  else //plot
    {
      data2 = pTime;
      return createPlot(getItemName(id), data2, data1);
    }

  return NULL;
}

#include "plot/COutputDefinitionVector.h"

//static
CPlotSpecification* COutputAssistant::createPlot(const std::string & name,
    const CCopasiObject* x,
    const std::vector<const CCopasiObject*> & y)
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
    const std::string & comment)
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

  //pReport->setTaskType(taskType);
  pReport->setIsTable(true);
  pReport->setSeparator(CCopasiReportSeparator("\t"));

  for (it = d.begin(); it != itEnd; ++it)
    {
      if (!(*it)) continue;
      pReport->getTableAddr()->push_back((*it)->getCN());
    }

  return pReport;
}
