/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiDataModel/CCopasiDataModel.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/08 16:29:16 $
   End CVS Header */

#include "copasi.h"
#include "CCopasiDataModel.h"

#include "function/CFunctionDB.h"
#include "model/CModel.h"
#include "utilities/CCopasiVector.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CCopasiProblem.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "scan/CScanTask.h"
#include "optimization/COptTask.h"
#include "steadystate/CMCATask.h"
#include "report/CReportDefinitionVector.h"
#include "plot/CPlotSpecification.h"
#include "xml/CCopasiXML.h"
#include "sbml/SBMLImporter.h"
#include "sbml/SBMLExporter.h"

CCopasiDataModel::CCopasiDataModel():
    mpFunctionList(new CFunctionDB),
    mpModel(NULL),
    mpTaskList(NULL),
    mpReportDefinitionList(NULL),
    mpPlotDefinitionList(NULL),
    mChanged(false)
{
  mpFunctionList->load();
  newModel();
}

bool CCopasiDataModel::loadModel(const std::string & fileName)
{
  mChanged = false;

  std::ifstream File(fileName.c_str());

  if (File.fail())
    {
      CCopasiMessage Message(CCopasiMessage::RAW,
                             "File error when opening '%s'.",
                             fileName);
      return false;
    }

  std::string Line;
  File >> Line;

  if (!Line.compare(0, 8, "Version="))
    {
      File.close();
      CReadConfig inbuf(fileName.c_str());

      newModel();
      mpModel->load(inbuf);

      dynamic_cast<CSteadyStateTask *>((*mpTaskList)["Steady-State"])->load(inbuf);
      dynamic_cast<CTrajectoryTask *>((*mpTaskList)["Time-Course"])->load(inbuf);
    }
  else if (!Line.compare(0, 5, "<?xml"))
    {
      std::cout << "XML Format" << std::endl;
      File.seekg(0, std::ios_base::beg);

      CCopasiXML XML;

      XML.setFunctionList(mpFunctionList->loadedFunctions());

      if (!XML.load(File)) return false;

      newModel();

      if (XML.getModel())
        {
          pdelete(mpModel);
          mpModel = XML.getModel();
        }

      if (XML.getTaskList())
        {
          pdelete(mpTaskList);
          mpTaskList = XML.getTaskList();
          mpTaskList->setObjectName("TaskList");
          mpTaskList->setObjectParent(CCopasiContainer::Root);
          addDefaultTasks();
        }

      if (XML.getReportList())
        {
          pdelete(mpReportDefinitionList);
          mpReportDefinitionList = new CReportDefinitionVector;
          *static_cast< CCopasiVector< CReportDefinition > * >(mpReportDefinitionList) = *XML.getReportList();
        }

      if (XML.getPlotList())
        {
          pdelete(mpPlotDefinitionList);
          mpPlotDefinitionList = XML.getPlotList();
        }
    }

  if (mpModel) mpModel->setCompileFlag();

  return true;
}

bool CCopasiDataModel::saveModel(const std::string & fileName)
{
  if (fileName == "") return false;

  mpModel->compileIfNecessary();

  CCopasiXML XML;

  XML.setModel(*mpModel);
  XML.setTaskList(*mpTaskList);
  XML.setReportList(*mpReportDefinitionList);
  XML.setPlotList(*mpPlotDefinitionList);

  // We are first writing to a temporary stream to prevent accidental
  // destruction of an existing file in case the save command fails.
  std::ostringstream tmp;
  if (!XML.save(tmp)) return false;

  std::ofstream os(fileName.c_str());
  if (os.fail()) return false;

  os << tmp.str();
  return true;
}

bool CCopasiDataModel::newModel(CModel * pModel)
{
  mChanged = false;

  pdelete(mpModel);
  mpModel = (pModel) ? pModel : new CModel();

  pdelete(mpTaskList);
  mpTaskList = new CCopasiVectorN< CCopasiTask >("TaskList", CCopasiContainer::Root);

  // We have at least one task of every type
  addDefaultTasks();

  pdelete(mpReportDefinitionList);
  mpReportDefinitionList = new CReportDefinitionVector;

  pdelete(mpPlotDefinitionList);
  mpPlotDefinitionList = new CCopasiVectorN< CPlotSpecification >;

  return true;
}

bool CCopasiDataModel::importSBML(const std::string & fileName)
{
  SBMLImporter importer;
  CModel * pModel = importer.readSBML(fileName, mpFunctionList);

  if (pModel == NULL) return false;

  return newModel(pModel);
}

bool CCopasiDataModel::exportSBML(const std::string & fileName)
{
  if (fileName == "") return false;

  SBMLExporter exporter;

  exporter.exportSBML(mpModel, fileName.c_str());

  return true;
}

CModel * CCopasiDataModel::getModel()
{return mpModel;}

CCopasiVectorN< CCopasiTask > * CCopasiDataModel::getTaskList()
{return mpTaskList;}

// static
CCopasiTask * CCopasiDataModel::addTask(const CCopasiTask::Type & taskType)
{
  CCopasiTask * pTask = NULL;

  switch (taskType)
    {
    case CCopasiTask::steadyState:
      pTask = new CSteadyStateTask(mpTaskList);
      break;

    case CCopasiTask::timeCourse:
      pTask = new CTrajectoryTask(mpTaskList);
      break;

    case CCopasiTask::scan:
      pTask = new CScanTask(mpTaskList);
      break;

    case CCopasiTask::fluxMode:
      // :TODO: implement task for elementary flux mode analysis
      return pTask;
      break;

    case CCopasiTask::optimization:
      pTask = new COptTask(mpTaskList);
      break;

    case CCopasiTask::parameterFitting:
      // :TODO: implement task for parameter fitting
      return pTask;
      break;

    case CCopasiTask::mca:
      pTask = new CMCATask(mpTaskList);
      break;

    default:
      return pTask;
    }

  pTask->getProblem()->setModel(mpModel);
  mpTaskList->add(pTask);

  return pTask;
}

bool CCopasiDataModel::addDefaultTasks()
{
  if (mpTaskList->getIndex("Steady-State") == C_INVALID_INDEX)
    addTask(CCopasiTask::steadyState);

  if (mpTaskList->getIndex("Time-Course") == C_INVALID_INDEX)
    addTask(CCopasiTask::timeCourse);

  if (mpTaskList->getIndex("Scan") == C_INVALID_INDEX)
    addTask(CCopasiTask::scan);

  if (mpTaskList->getIndex("Elementary Flux Modes") == C_INVALID_INDEX)
    addTask(CCopasiTask::fluxMode);

  if (mpTaskList->getIndex("Optimization") == C_INVALID_INDEX)
    addTask(CCopasiTask::optimization);

  if (mpTaskList->getIndex("Parameter Fitting") == C_INVALID_INDEX)
    addTask(CCopasiTask::parameterFitting);

  if (mpTaskList->getIndex("Metabolic Control Analysis") == C_INVALID_INDEX)
    addTask(CCopasiTask::mca);

  return true;
}

CReportDefinitionVector * CCopasiDataModel::getReportDefinitionList()
{return mpReportDefinitionList;}

CCopasiVectorN< CPlotSpecification > * CCopasiDataModel::getPlotDefinitionList()
{return mpPlotDefinitionList;}

CFunctionDB * CCopasiDataModel::getFunctionList()
{return mpFunctionList;}

bool CCopasiDataModel::isChanged() const
  {return mChanged;}

void CCopasiDataModel::changed(const bool & changed)
{mChanged = changed;}

#ifdef XXXX
DataModel::DataModel()
{
  //this->populateData();
  model = NULL;
  mChanged = false;
  trajectorytask = NULL;
  steadystatetask = NULL;
  scantask = NULL;
  reportdefinitions = NULL;
  plotspecs = NULL;
  pOptFunction = NULL;
  mpCMCATask = NULL;
}

bool DataModel::createModel()
{
  mChanged = false;

  pdelete(model);
  model = new CModel();
  Copasi->pModel = model;

  pdelete(steadystatetask);
  steadystatetask = new CSteadyStateTask();
  steadystatetask->getProblem()->setModel(model);

  pdelete(trajectorytask);
  trajectorytask = new CTrajectoryTask();
  trajectorytask->getProblem()->setModel(model);

  pdelete(scantask);
  scantask = new CScanTask();
  scantask->getProblem()->setModel(model);

  pdelete(mpCMCATask);
  mpCMCATask = new CMCATask();
  mpCMCATask->getProblem()->setModel(model);
  dynamic_cast<CMCAMethod*>(mpCMCATask->getMethod())->setModel(model);

  pdelete(reportdefinitions);
  reportdefinitions = new CReportDefinitionVector();

  pdelete(plotspecs);
  plotspecs = new CPlotSpecification();

  pdelete(pOptFunction);
  pOptFunction = new COptFunction();

  return true;
}

bool DataModel::loadModel(const char* fileName)
{
  mChanged = false;

  std::ifstream File(fileName);

  if (File.fail())
    {
      CCopasiMessage Message(CCopasiMessage::RAW,
                             "File error when opening '%s'.",
                             fileName);
      return false;
    }

  std::string Line;
  File >> Line;

  if (!Line.compare(0, 8, "Version="))
    {
      File.close();
      pdelete(model);
      CReadConfig inbuf(fileName);
      model = new CModel();
      model->load(inbuf);

      pdelete(steadystatetask);
      steadystatetask = new CSteadyStateTask();
      steadystatetask->load(inbuf);

      pdelete(trajectorytask);
      trajectorytask = new CTrajectoryTask();
      trajectorytask->load(inbuf);

      pdelete(scantask);
      scantask = new CScanTask();
      scantask->getProblem()->setModel(model);

      pdelete(mpCMCATask);
      mpCMCATask = new CMCATask();
      mpCMCATask->getProblem()->setModel(model);
      dynamic_cast<CMCAMethod*>(mpCMCATask->getMethod())->setModel(model);

      pdelete(reportdefinitions);
      reportdefinitions = new CReportDefinitionVector();

      pdelete(plotspecs);
      plotspecs = new CPlotSpecification();

      pdelete(pOptFunction);
      pOptFunction = new COptFunction();
    }
  else if (!Line.compare(0, 5, "<?xml"))
    {
      std::cout << "XML Format" << std::endl;
      File.seekg(0, std::ios_base::beg);

      CCopasiXML XML;

      XML.setFunctionList(Copasi->pFunctionDB->loadedFunctions());

      CReportDefinitionVector * pNewReports = new CReportDefinitionVector();
      XML.setReportList(*pNewReports);

      CCopasiVectorN< CCopasiTask > TaskList;
      XML.setTaskList(TaskList);

      CPlotSpecification * pNewPlotSpecs = new CPlotSpecification();
      XML.setPlotList(*pNewPlotSpecs);

      if (!XML.load(File)) return false;

      pdelete(model);
      model = XML.getModel();

      pdelete(steadystatetask);
      pdelete(trajectorytask);
      pdelete(scantask);
      pdelete(mpCMCATask);

      unsigned C_INT32 i, imax = TaskList.size();
      for (i = 0; i < imax; i++)
        {
          switch (TaskList[i]->getType())
            {
            case CCopasiTask::steadyState:
              steadystatetask = dynamic_cast< CSteadyStateTask * >(TaskList[i]);
              break;

            case CCopasiTask::timeCourse:
              trajectorytask = dynamic_cast< CTrajectoryTask * >(TaskList[i]);
              break;

            case CCopasiTask::scan:
              scantask = dynamic_cast< CScanTask * >(TaskList[i]);
              break;

            case CCopasiTask::mca:
              mpCMCATask = dynamic_cast< CMCATask * >(TaskList[i]);
              break;
            }
        }

      if (!steadystatetask) steadystatetask = new CSteadyStateTask();
      steadystatetask->getProblem()->setModel(model);

      if (!trajectorytask) trajectorytask = new CTrajectoryTask();
      trajectorytask->getProblem()->setModel(model);

      if (!scantask) scantask = new CScanTask();
      scantask->getProblem()->setModel(model);

      if (!mpCMCATask) mpCMCATask = new CMCATask();
      mpCMCATask->getProblem()->setModel(model);
      dynamic_cast<CMCAMethod*>(mpCMCATask->getMethod())->setModel(model);

      pdelete(reportdefinitions);
      reportdefinitions = pNewReports;

      pdelete(plotspecs);
      plotspecs = pNewPlotSpecs;

      pdelete(pOptFunction);
      pOptFunction = new COptFunction();
    }

  if (model) model->setCompileFlag();

  return true;
}

bool DataModel::saveModel(const char* fileName)
{
  if (fileName == NULL) return false;

  model->compileIfNecessary();

  CCopasiXML XML;
  std::ofstream os(fileName);

  XML.setModel(*model);
  XML.setReportList(*reportdefinitions);

  CCopasiVectorN< CCopasiTask > TaskList;
  if (steadystatetask) TaskList.add(steadystatetask);
  if (trajectorytask) TaskList.add(trajectorytask);
  if (scantask) TaskList.add(scantask);
  if (mpCMCATask) TaskList.add(mpCMCATask);
  XML.setTaskList(TaskList);

  XML.setPlotList(*plotspecs);
  XML.save(os);

  return true;
}

bool DataModel::isChanged() const {return mChanged;}

void DataModel::changed(const bool & changed) {mChanged = changed;}

bool DataModel::importSBML(const char* fileName)
{
  mChanged = false;

  pdelete(pOptFunction);
  pOptFunction = new COptFunction();

  SBMLImporter importer;
  CModel * pModel = importer.readSBML(fileName, Copasi->pFunctionDB);

  if (pModel == NULL) return false;

  pdelete(model);
  model = pModel;

  Copasi->pModel = model;

  pdelete(steadystatetask);
  steadystatetask = new CSteadyStateTask();
  steadystatetask->getProblem()->setModel(model);

  pdelete(trajectorytask);
  trajectorytask = new CTrajectoryTask();
  trajectorytask->getProblem()->setModel(model);

  pdelete(scantask);
  scantask = new CScanTask();
  scantask->getProblem()->setModel(model);

  pdelete(mpCMCATask);
  mpCMCATask = new CMCATask();
  mpCMCATask->getProblem()->setModel(model);
  dynamic_cast<CMCAMethod*>(mpCMCATask->getMethod())->setModel(model);

  pdelete(reportdefinitions);
  reportdefinitions = new CReportDefinitionVector();

  pdelete(plotspecs);
  plotspecs = new CPlotSpecification();

  return true;
}

bool DataModel::exportSBML(const char* fileName)
{
  if (fileName == NULL) return false;

  SBMLExporter exporter;

  exporter.exportSBML(model, fileName);

  return true;
}
#endif // XXXX
