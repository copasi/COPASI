/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiDataModel/CCopasiDataModel.cpp,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/09 14:11:53 $
   End CVS Header */

#include "copasi.h"
#include "copasiversion.h"
#include "CCopasiDataModel.h"

#include "commandline/COptions.h"
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
#include "steadystate/CMCAMethod.h"
#include "report/CReportDefinitionVector.h"
#include "plot/CPlotSpecification.h"
#include "xml/CCopasiXML.h"
#include "sbml/SBMLImporter.h"
#include "sbml/SBMLExporter.h"

CCopasiDataModel * CCopasiDataModel::Global = NULL;

CCopasiDataModel::CCopasiDataModel(const bool withGUI):
    mpVersion(new CVersion),
    mpFunctionList(new CFunctionDB),
    mpModel(NULL),
    mpTaskList(NULL),
    mpReportDefinitionList(NULL),
    mpPlotDefinitionList(NULL),
    mWithGUI(withGUI),
    mpGUI(NULL),
    mChanged(false),
    mAutoSaveNeeded(false),
    pOldMetabolites(new CCopasiVectorS < CMetabOld >)
{
  mpVersion->setVersion(COPASI_VERSION_MAJOR,
                        COPASI_VERSION_MINOR,
                        COPASI_VERSION_BUILD);

  mpFunctionList->load();
  newModel();
}

CCopasiDataModel::~CCopasiDataModel()
{
  pdelete(mpVersion);
  pdelete(mpFunctionList);
  pdelete(mpModel);
  pdelete(mpTaskList);
  pdelete(mpReportDefinitionList);
  pdelete(mpPlotDefinitionList);
  pdelete(mpGUI);
  pdelete(pOldMetabolites);
}

bool CCopasiDataModel::loadModel(const std::string & fileName)
{
  std::ifstream File(fileName.c_str());

  if (File.fail())
    {
      CCopasiMessage Message(CCopasiMessage::RAW,
                             "File error when opening '%s'.",
                             fileName.c_str());
      return false;
    }

  std::string Line;
  File >> Line;

  if (!Line.compare(0, 8, "Version="))
    {
      if (fileName.rfind(".gps") == fileName.length() - 4 ||
          fileName.rfind(".GPS") == fileName.length() - 4)
        mSaveFileName = fileName.substr(0, fileName.length() - 4) + ".cps";
      else
        mSaveFileName = fileName + ".cps";

      File.close();
      CReadConfig inbuf(fileName.c_str());

      newModel();
      mpModel->load(inbuf);

      dynamic_cast<CSteadyStateTask *>((*mpTaskList)["Steady-State"])->load(inbuf);
      dynamic_cast<CTrajectoryTask *>((*mpTaskList)["Time-Course"])->load(inbuf);
    }
  else if (!Line.compare(0, 5, "<?xml"))
    {
      mSaveFileName = fileName;

      std::cout << "XML Format" << std::endl;
      File.seekg(0, std::ios_base::beg);

      CCopasiXML XML;

      XML.setFunctionList(mpFunctionList->loadedFunctions());

      SCopasiXMLGUI *pGUI = NULL;

      if (mWithGUI)
        {
          pGUI = new SCopasiXMLGUI;
          XML.setGUI(*pGUI);
        }

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
          CCopasiContainer::Root->add(mpTaskList, true);
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
          mpPlotDefinitionList->setObjectName("PlotList");
          CCopasiContainer::Root->add(mpPlotDefinitionList, true);
        }

      if (mWithGUI)
        {
          pdelete(mpGUI);
          mpGUI = pGUI;
        }
    }

  if (mpModel) mpModel->setCompileFlag();

  changed(false);
  return true;
}

bool CCopasiDataModel::saveModel(const std::string & fileName,
                                 const bool & autoSave)
{
  std::string FileName = (fileName != "") ? fileName : mSaveFileName;

  mpModel->compileIfNecessary();

  CCopasiXML XML;

  XML.setModel(*mpModel);
  XML.setTaskList(*mpTaskList);
  XML.setReportList(*mpReportDefinitionList);
  XML.setPlotList(*mpPlotDefinitionList);
  XML.setGUI(*mpGUI);

  // We are first writing to a temporary stream to prevent accidental
  // destruction of an existing file in case the save command fails.
  std::ostringstream tmp;
  if (!XML.save(tmp)) return false;

  std::ofstream os(FileName.c_str());
  if (os.fail()) return false;

  os << tmp.str();
  if (os.fail()) return false;

  if (!autoSave) changed(false);

  return true;
}

bool CCopasiDataModel::autoSave()
{
  if (!mAutoSaveNeeded) return true;

  std::string AutoSave;
  int index;
  COptions::getValue("Tmp", AutoSave);
  if (AutoSave == "") return false;
#ifdef WIN32
  AutoSave += "\\";
#else
  AutoSave += "/";
#endif

  if ((index = mSaveFileName.find_last_of('\\')) == -1)
    index = mSaveFileName.find_last_of('/');
  //index = mSaveFileName.find_last_of('/' || '\\');
  AutoSave += "tmp_" + mSaveFileName.substr(index + 1, mSaveFileName.length() - index - 5) + ".cps";

  if (!saveModel(AutoSave, true)) return false;

  mAutoSaveNeeded = false;
  return true;
}

bool CCopasiDataModel::newModel(CModel * pModel)
{
  pdelete(mpModel);
  mpModel = (pModel) ? pModel : new CModel();

  pdelete(mpTaskList);
  mpTaskList = new CCopasiVectorN< CCopasiTask >("TaskList", CCopasiContainer::Root);

  // We have at least one task of every type
  addDefaultTasks();

  pdelete(mpReportDefinitionList);
  mpReportDefinitionList = new CReportDefinitionVector;

  pdelete(mpPlotDefinitionList);
  mpPlotDefinitionList = new CCopasiVectorN< CPlotSpecification >("PlotList", CCopasiContainer::Root);

  if (mWithGUI)
    {
      pdelete(mpGUI);
      mpGUI = new SCopasiXMLGUI;
    }

  changed(false);

  return true;
}

bool CCopasiDataModel::importSBML(const std::string & fileName)
{
  if (fileName.rfind(".xml") == fileName.length() - 4 ||
      fileName.rfind(".XML") == fileName.length() - 4)
    mSaveFileName = fileName.substr(0, fileName.length() - 4) + ".cps";
  else
    mSaveFileName = fileName + ".cps";

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
      // :TODO: implement task for optimization
      return pTask;
      break;

    case CCopasiTask::parameterFitting:
      // :TODO: implement task for parameter fitting
      return pTask;
      break;

    case CCopasiTask::mca:
      pTask = new CMCATask(mpTaskList);
      // :TODO: This must be avoided.
      static_cast<CMCAMethod *>(pTask->getMethod())->setModel(mpModel);
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

CCopasiVectorN<CPlotSpecification> * CCopasiDataModel::getPlotDefinitionList()
{return mpPlotDefinitionList;}

CFunctionDB * CCopasiDataModel::getFunctionList()
{return mpFunctionList;}

SCopasiXMLGUI * CCopasiDataModel::getGUI()
{return mpGUI;}

CVersion * CCopasiDataModel::getVersion()
{return mpVersion;}

bool CCopasiDataModel::isChanged() const
  {return mChanged;}

void CCopasiDataModel::changed(const bool & changed)
{
  mChanged = changed;
  mAutoSaveNeeded = changed;
}
