/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiDataModel/CCopasiDataModel.cpp,v $
   $Revision: 1.28 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2005/06/08 16:27:54 $
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
#include "utilities/CDirEntry.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "scan/CScanTask.h"
#include "optimization/COptTask.h"
#include "steadystate/CMCATask.h"
#include "steadystate/CMCAMethod.h"
#include "report/CReportDefinitionVector.h"
#include "report/CKeyFactory.h" 
//#include "plot/CPlotSpecification.h"
#include "plot/COutputDefinitionVector.h"
#include "xml/CCopasiXML.h"
#include "sbml/SBMLImporter.h"
#include "sbml/SBMLExporter.h"

CDataModelRenameHandler::CDataModelRenameHandler(CCopasiDataModel* dm)
    : mpDataModel(dm)
{}

bool CDataModelRenameHandler::handle(const std::string & oldCN, const std::string & newCN) const
  {
    //std::cout << "CDataModelRenameHandler::handle()" << std::endl;
    //std::cout << " old: " << oldCN << std::endl;
    //std::cout << " new: " << newCN << std::endl;

    const std::set<CRegisteredObjectName*> nameSet = CRegisteredObjectName::getSet();

    //std::cout << " ************ " << nameSet.size() << std::endl;
    std::set<CRegisteredObjectName*>::const_iterator it, itEnd = nameSet.end();
    for (it = nameSet.begin(); it != itEnd; ++it)
      {
        if (oldCN.compare(0, oldCN.size(), **it, 0, oldCN.size()) == 0)
          {
            std::cout << "   match:   " << **it << std::endl;
            (**it).replace(0, oldCN.size(), newCN);
            std::cout << "     -->    " << **it << std::endl;
          }
        else
          {
            //std::cout << "            " << **it << std::endl;
          }
      }

    //std::cout << " " << std::endl;
    return true;
  }

//********************************************************************

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
    mRenameHandler(this),
    mpCurrentSBMLDocument(NULL),
    pOldMetabolites(new CCopasiVectorS < CMetabOld >)
{
  mpVersion->setVersion(COPASI_VERSION_MAJOR,
                        COPASI_VERSION_MINOR,
                        COPASI_VERSION_BUILD);

  mpUndefined = new CFunction("undefined");
  GlobalKeys.remove(mpUndefined->getKey());
  GlobalKeys.addFix("UndefinedFunction", mpUndefined);

  mpFunctionList->load();
  newModel();
  CCopasiObject::setRenameHandler(&mRenameHandler); //TODO where in the contructor should this be called?
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
  pdelete(mpCurrentSBMLDocument);
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
      File.close();
      CReadConfig inbuf(fileName.c_str());

      newModel();
      mpModel->load(inbuf);

      dynamic_cast<CSteadyStateTask *>((*mpTaskList)["Steady-State"])->load(inbuf);
      dynamic_cast<CTrajectoryTask *>((*mpTaskList)["Time-Course"])->load(inbuf);

      mSaveFileName = CDirEntry::dirName(fileName)
                      + CDirEntry::Separator
                      + CDirEntry::baseName(fileName);

      std::string Suffix = CDirEntry::suffix(fileName);
      if (strcasecmp(Suffix.c_str(), ".gps") != 0)
        mSaveFileName += Suffix;

      mSaveFileName += ".cps";
    }
  else if (!Line.compare(0, 5, "<?xml"))
    {
      //std::cout << "XML Format" << std::endl;
      File.seekg(0, std::ios_base::beg);

      CCopasiXML XML;

      XML.setFunctionList(mpFunctionList->loadedFunctions());

      SCopasiXMLGUI *pGUI = NULL;

      if (mWithGUI)
        {
          pGUI = new SCopasiXMLGUI;
          XML.setGUI(*pGUI);
        }

      if (!XML.load(File))
        {
          XML.freeModel();
          XML.freeTaskList();
          XML.freeReportList();
          XML.freePlotList();
          XML.freeGUI();

          return false;
        }

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
          mpReportDefinitionList = XML.getReportList();
          addDefaultReports();
        }

      if (XML.getPlotList())
        {
          pdelete(mpPlotDefinitionList);
          mpPlotDefinitionList = XML.getPlotList();
        }

      if (mWithGUI)
        {
          pdelete(mpGUI);
          mpGUI = pGUI;
        }

      mSaveFileName = fileName;
    }

  if (mpModel) mpModel->setCompileFlag();

  changed(false);
  return true;
}

bool CCopasiDataModel::saveModel(const std::string & fileName, bool overwriteFile,
                                 const bool & autoSave)
{
  std::string FileName = (fileName != "") ? fileName : mSaveFileName;

  if (CDirEntry::exist(FileName))
    {
      if (!overwriteFile)
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCDirEntry + 1,
                         FileName.c_str());
          return false;
        }

      if (!CDirEntry::isWritable(fileName))
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCDirEntry + 2,
                         FileName.c_str());
          return false;
        }
    }

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

  // Remember for future saves.
  mSaveFileName = FileName;
  return true;
}

bool CCopasiDataModel::autoSave()
{
  if (!mAutoSaveNeeded) return true;

  std::string AutoSave;
  int index;
  COptions::getValue("Tmp", AutoSave);
  if (AutoSave == "") return false;

  AutoSave += CDirEntry::Separator + "tmp_";

  if (mSaveFileName != "")
    {
      index = mSaveFileName.find_last_of(CDirEntry::Separator);
#ifdef WIN32 // WIN32 also understands '/' as the separator.
      if (index == C_INVALID_INDEX)
        index = mSaveFileName.find_last_of("/");
#endif
      AutoSave += mSaveFileName.substr(index + 1,
                                       mSaveFileName.length() - index - 5);
    }
  AutoSave += ".cps";

  if (!saveModel(AutoSave, true)) return false;

  mAutoSaveNeeded = false;
  return true;
}

bool CCopasiDataModel::newModel(CModel * pModel)
{
  pdelete(mpModel);

  if (pModel)
    mpModel = pModel;
  else
    {
      mpModel = new CModel();
      mSaveFileName = "";
    }

  pdelete(mpTaskList);
  mpTaskList = new CCopasiVectorN< CCopasiTask >("TaskList", CCopasiContainer::Root);

  // We have at least one task of every type
  addDefaultTasks();

  pdelete(mpReportDefinitionList);
  mpReportDefinitionList = new CReportDefinitionVector;
  addDefaultReports();

  pdelete(mpPlotDefinitionList);
  mpPlotDefinitionList = new COutputDefinitionVector;

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
  SBMLImporter importer;
  CModel * pModel = importer.readSBML(fileName, mpFunctionList, mpCurrentSBMLDocument, mCopasi2SBMLMap);

  if (pModel == NULL) return false;

  mSaveFileName = CDirEntry::dirName(fileName)
                  + CDirEntry::Separator
                  + CDirEntry::baseName(fileName);

  std::string Suffix = CDirEntry::suffix(fileName);
  if (strcasecmp(Suffix.c_str(), ".xml") != 0)
    mSaveFileName += Suffix;

  mSaveFileName += ".cps";

  return newModel(pModel);
}

bool CCopasiDataModel::exportSBML(const std::string & fileName, bool overwriteFile)
{
  if (fileName == "") return false;

  if (CDirEntry::exist(fileName))
    {
      if (!overwriteFile)
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCDirEntry + 1,
                         fileName.c_str());
          return false;
        }

      if (!CDirEntry::isWritable(fileName))
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCDirEntry + 2,
                         fileName.c_str());
          return false;
        }
    }

  SBMLExporter exporter;

  return exporter.exportSBML(mpModel, fileName.c_str(), overwriteFile);
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
      pTask = new COptTask(mpTaskList);
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
  unsigned C_INT32 i;
  for (i = 0; CCopasiTask::TypeName[i] != ""; i++)
    if (mpTaskList->getIndex(CCopasiTask::TypeName[i]) == C_INVALID_INDEX)
      addTask((CCopasiTask::Type) i);

  return true;
}

std::set<std::string> CCopasiDataModel::listTaskDependentOnReport(const std::string & key)
{
  std::set<std::string> TaskKeys;

  CReportDefinition * pReportDefinition
  = dynamic_cast< CReportDefinition * >(GlobalKeys.get(key));
  if (!pReportDefinition) return TaskKeys;

  unsigned C_INT32 i, imax = mpTaskList->size();
  for (i = 0; i < imax; i++)
    if (pReportDefinition == (*mpTaskList)[i]->getReport().getReportDefinition())
      TaskKeys.insert((*mpTaskList)[i]->getKey());

  return TaskKeys;
}

CReportDefinition * CCopasiDataModel::addReport(const CCopasiTask::Type & taskType)
{
  CReportDefinition * pReport = NULL;

  switch (taskType)
    {
    case CCopasiTask::steadyState:
      pReport = new CReportDefinition(CCopasiTask::TypeName[taskType]);
      pReport->setTaskType(taskType);
      pReport->setComment("Automatically generated report.");
      pReport->setIsTable(false);
      pReport->setSeparator(CCopasiReportSeparator("\t"));
      pReport->getBodyAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Steady-State]"));
      break;

    case CCopasiTask::timeCourse:
      // No default report available.
      break;

    case CCopasiTask::scan:
      // No default report available.
      break;

    case CCopasiTask::fluxMode:
      // :TODO: implement task for elementary flux mode analysis
      break;

    case CCopasiTask::optimization:
      // :TODO: implement task for optimization
      break;

    case CCopasiTask::parameterFitting:
      // :TODO: implement task for parameter fitting
      break;

    case CCopasiTask::mca:
      // :TODO: implement default report for MCA
      break;

    default:
      return pReport;
    }

  if (pReport) mpReportDefinitionList->add(pReport, true);

  return pReport;
}

bool CCopasiDataModel::addDefaultReports()
{
  unsigned C_INT32 i;
  for (i = 0; CCopasiTask::TypeName[i] != ""; i++)
    if (mpReportDefinitionList->getIndex(CCopasiTask::TypeName[i]) == C_INVALID_INDEX)
      addReport((CCopasiTask::Type) i);

  return true;
}

CReportDefinitionVector * CCopasiDataModel::getReportDefinitionList()
{return mpReportDefinitionList;}

COutputDefinitionVector * CCopasiDataModel::getPlotDefinitionList()
{return mpPlotDefinitionList;}

CFunctionDB * CCopasiDataModel::getFunctionList()
{return mpFunctionList;}

SCopasiXMLGUI * CCopasiDataModel::getGUI()
{return mpGUI;}

CVersion * CCopasiDataModel::getVersion()
{return mpVersion;}

const std::string & CCopasiDataModel::getFileName() const
  {return mSaveFileName;}

bool CCopasiDataModel::isChanged() const
  {return mChanged;}

void CCopasiDataModel::changed(const bool & changed)
{
  mChanged = changed;
  mAutoSaveNeeded = changed;
}
