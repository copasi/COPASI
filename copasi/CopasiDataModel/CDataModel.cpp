// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#define USE_LAYOUT 1

#include <sbml/SBMLDocument.h>

#include "copasi/copasi.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/CopasiDataModel/CInfo.h"

#include "copasi/core/CDataTimer.h"
#include "copasi/commandline/COptions.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetabNameInterface.h"
#include "copasi/utilities/CTaskFactory.h"
#include "copasi/plot/COutputDefinitionVector.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/sbml/CSBMLExporter.h"
#include "copasi/sbml/SBMLImporter.h"
#include "copasi/sbml/SBMLIncompatibility.h"
#include "copasi/steadystate/CMCAProblem.h"
#include "copasi/lna/CLNAProblem.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/tss/CODEExporter.h"
#include "copasi/tss/CODEExporterC.h"
#include "copasi/tss/CODEExporterBM.h"
#include "copasi/tss/CODEExporterXPPAUT.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/core/CDataVector.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasi/xml/CCopasiXML.h"
#include "copasi/undo/CUndoData.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/trajectory/CTrajectoryTask.h"

#include "copasi/layout/CListOfLayouts.h"
#include "copasi/layout/CLayoutInitializer.h"
#include "copasi/core/CRootContainer.h"

#include <combine/combinearchive.h>
#include <combine/knownformats.h>
#include <combine/util.h>
#include <omex/CaContent.h>
#include <copasi/utilities/CCopasiMessage.h>
#include <copasi/utilities/CParameterEstimationUtils.h>

#include <sedml/SedDocument.h>
#include "copasi/sedml/SEDMLImporter.h"
#include "copasi/sedml/CSEDMLExporter.h"

#include "copasi/model/CModelExpansion.h"
#include "copasi/model/CModelParameter.h"

#include "copasi/MIRIAM/CModelMIRIAMInfo.h"

#ifdef COPASI_Versioning
#  include "copasi/versioning/CModelVersionHierarchy.h"
#endif // COPASI_Versioning

#include <copasi/parameterFitting/CFitProblem.h>
#include <copasi/parameterFitting/CExperimentSet.h>
#include <copasi/parameterFitting/CExperiment.h>

#include <copasi/shinyExport/uiShiny.c>
#include <copasi/shinyExport/serverShiny.c>

LIBCOMBINE_CPP_NAMESPACE_USE

// static
const CEnumAnnotation< std::string, CDataModel::ContentType >
CDataModel::ContentTypeNames( {"COPASI",
  "GEPASI",
  "SBML",
  "SED-ML",
  "OMEX"
});

// static
CDataModel::ContentType CDataModel::contentType(std::istream & content)
{
  std::string Line;
  size_t LinesRead = 0;
  unsigned C_INT32 isZip;

  content.read(reinterpret_cast< char * >(&isZip), 4);
  content.seekg(0);

  if (content.fail())
    return ContentType::__SIZE;

  if (isZip == 0x04034b50)
    return ContentType::OMEX;

  std::getline(content, Line);
  ++LinesRead;

  if (content.fail())
    return ContentType::__SIZE;

  if (!Line.compare(0, 8, "Version="))
    {
      content.seekg(0);
      CReadConfig GEPASI(content);

      std::string Version;

      if (GEPASI.getVariable("Version", "string", &Version) == 0
          && Version < "4")
        {
          content.seekg(0);
          return ContentType::GEPASI;
        }

      return ContentType::__SIZE;
    }

  while (LinesRead <= 10)
    {
      if (Line.find("<sedML") != std::string::npos
          || Line.find(":sedML") != std::string::npos)
        {
          content.seekg(0);
          return ContentType::SEDML;
        }

      if (Line.find("<sbml") != std::string::npos
          || Line.find(":sbml") != std::string::npos)
        {
          content.seekg(0);
          return ContentType::SBML;
        }

      if (Line.find("<COPASI") != std::string::npos
          || Line.find(":COPASI") != std::string::npos)
        {
          content.seekg(0);
          return ContentType::COPASI;
        }

      std::getline(content, Line);
      ++LinesRead;
    }

  return ContentType::__SIZE;
}

CDataModel::CDataModel(const bool withGUI)
  : CDataContainer("Root", NULL, "CN", CDataObject::DataModel)
  , COutputHandler()
  , mData(withGUI)
  , mOldData(withGUI)
  , mpInfo(NULL)
  , mTempFolders()
  , mNeedToSaveExperimentalData(false)
  , pOldMetabolites(new CDataVectorS< CMetabOld >)
{
  mpInfo = new CInfo(this);
  newModel(NULL, true);
  new CCopasiTimer(CCopasiTimer::Type::WALL, this);
  new CCopasiTimer(CCopasiTimer::Type::PROCESS, this);
}

// static
CDataModel * CDataModel::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CDataModel(data.getProperty(CData::OBJECT_NAME).toString(),
                        NO_PARENT);
}

// virtual
CData CDataModel::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CDataModel::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CDataModel::CDataModel(const std::string & name,
                       const CDataContainer * pParent,
                       const std::string & type,
                       bool withGUI)
  : CDataContainer(name, pParent, type, CDataObject::DataModel)
  , COutputHandler()
  , mData(withGUI)
  , mOldData(withGUI)
  , mpInfo(NULL)
  , mTempFolders()
  , mNeedToSaveExperimentalData(false)
  , pOldMetabolites(new CDataVectorS< CMetabOld >)
{
  newModel(NULL, true);
  new CCopasiTimer(CCopasiTimer::Type::WALL, this);
  new CCopasiTimer(CCopasiTimer::Type::PROCESS, this);
}

CDataModel::CDataModel(const CDataModel & src,
                       const CDataContainer * pParent)
  : CDataContainer(src, pParent)
  , COutputHandler(src)
  , mData(src.mData)
  , mOldData(src.mOldData)
  , mpInfo(NULL)
  , mTempFolders()
  , mNeedToSaveExperimentalData(false)
  , pOldMetabolites((src.pOldMetabolites != NULL) ? new CDataVectorS< CMetabOld >(*src.pOldMetabolites, NO_PARENT) : NULL)
{}

CDataModel::~CDataModel()
{
  CRegisteredCommonName::setEnabled(false);

  // Make sure that the old data is deleted
  deleteOldData();

  // Delete the current data
  mOldData = mData;
  deleteOldData();

  pdelete(pOldMetabolites);

  std::vector< std::string >::iterator it = mTempFolders.begin();

  for (; it != mTempFolders.end(); ++it)
    {
      Util::removeFileOrFolder(*it);
    }

  mTempFolders.clear();

  CRegisteredCommonName::setEnabled(true);
}

bool CDataModel::loadFromString(const std::string & content,
                                std::string referenceDir,
                                CProcessReport * pProcessReport,
                                const bool & deleteOldData)
{
  if (referenceDir.empty())
    {
      COptions::getValue("PWD", referenceDir);
    }

  std::istringstream Content(content);

  switch (CDataModel::contentType(Content))
    {
      case ContentType::COPASI:
        return loadModel(Content, referenceDir, pProcessReport, deleteOldData);
        break;

      case ContentType::GEPASI:
        return loadModel(Content, referenceDir, pProcessReport, deleteOldData);
        break;

      case ContentType::SBML:
        mData.mReferenceDir = referenceDir;
        return importSBMLFromString(content, pProcessReport, deleteOldData);
        break;

      case ContentType::SEDML:
        return importSEDMLFromString(content, referenceDir, pProcessReport, deleteOldData);
        break;

      case ContentType::OMEX:
      {
        std::string TmpDir;
        COptions::getValue("Tmp", TmpDir);

        std::string TmpFileName = CDirEntry::createTmpName(TmpDir, ".omex");
        std::ofstream(TmpFileName) << content;

        bool success = openCombineArchive(TmpFileName, pProcessReport, deleteOldData);

        CDirEntry::remove(TmpFileName);

        return success;
      }

      break;

      case ContentType::__SIZE:
        CCopasiMessage Message(CCopasiMessage::ERROR,
                               "Content not supported for string '%s'.",
                               content.substr(0, 512).c_str());
        break;
    }

  return false;
}

bool CDataModel::loadFromFile(const std::string & fileName,
                              CProcessReport * pProcessReport,
                              const bool & deleteOldData)
{
  std::string FileName = fileName;
  std::string PWD;
  COptions::getValue("PWD", PWD);

  if (CDirEntry::isRelativePath(FileName) && !CDirEntry::makePathAbsolute(FileName, PWD))
    FileName = CDirEntry::fileName(FileName);

  PWD = CDirEntry::dirName(FileName);

#ifdef WIN32
  std::ifstream File(CLocaleString::fromUtf8(FileName).c_str(), std::ios_base::binary);
#else
  std::ifstream File(CLocaleString::fromUtf8(FileName).c_str());
#endif

  if (File.fail())
    {
      CCopasiMessage Message(CCopasiMessage::ERROR,
                             "File error when opening '%s'.",
                             FileName.c_str());
      return false;
    }

  bool success = false;

  switch (CDataModel::contentType(File))
    {
      case ContentType::COPASI:
        success = loadModel(File, PWD, pProcessReport, deleteOldData);

        if (success)
          {
            mData.mSaveFileName = CDirEntry::normalize(FileName);
            mData.mReferenceDir = CDirEntry::dirName(mData.mSaveFileName);
          }

        break;

      case ContentType::GEPASI:
        success = loadModel(File, PWD, pProcessReport, deleteOldData);

        if (success)
          {
            mData.mSaveFileName = CDirEntry::dirName(FileName)
                                  + CDirEntry::Separator
                                  + CDirEntry::baseName(FileName);

            std::string Suffix = CDirEntry::suffix(FileName);

            if (strcasecmp(Suffix.c_str(), ".gps") != 0)
              mData.mSaveFileName += Suffix;

            mData.mSaveFileName += ".cps";

            mData.mSaveFileName = CDirEntry::normalize(mData.mSaveFileName);
            mData.mReferenceDir = CDirEntry::dirName(mData.mSaveFileName);
          }

        break;

      case ContentType::SBML:
        success = importSBML(FileName, pProcessReport, deleteOldData);
        break;

      case ContentType::SEDML:
        success = importSEDML(FileName, pProcessReport, deleteOldData);
        break;

      case ContentType::OMEX:
        success = openCombineArchive(FileName, pProcessReport, deleteOldData);
        break;

      case ContentType::__SIZE:
        CCopasiMessage Message(CCopasiMessage::ERROR,
                               "Content not supported for file '%s'.",
                               FileName.c_str());
        break;
    }

  return success;
}

bool CDataModel::loadModel(std::istream & in,
                           const std::string & pwd,
                           CProcessReport * pProcessReport,
                           const bool & deleteOldData)
{
  // During load no objects will be renamed;
  CRegisteredCommonName::setEnabled(false);

  CCopasiMessage::clearDeque();

  // Read enough characters of the file, into a char array, to determine the format
  char buffer[1024];
  in.read(buffer, 1023);

  // Make sure the stream pointer is at the beginning, for the subsequent true conditional
  in.seekg(0, std::ios_base::beg);

  // Properly NULL terminate the C-type "string" (so the string class constructor knows where it ends)
  buffer[1023] = 0x0;

  // create string (class), to have useful member functions
  std::string Line = buffer;

  if (!Line.compare(0, 8, "Version="))
    {
      CReadConfig inbuf(in);

      if (inbuf.getVersion() >= "4")
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         "Can't handle Gepasi Files with Version>=4.");

          CRegisteredCommonName::setEnabled(true);
          return false;
        }

      newModel(NULL, deleteOldData);
      mData.mContentType = ContentType::GEPASI;
      mData.mReferenceDir = pwd;

      if (mData.pModel->load(inbuf))
        {
          popData();
          CRegisteredCommonName::setEnabled(true);
          return false;
        }

      static_cast< CTrajectoryTask * >(&mData.pTaskList->operator[]("Time-Course"))->load(inbuf);

      static_cast< CSteadyStateTask * >(&mData.pTaskList->operator[]("Steady-State"))->load(inbuf);
    }
  else if (Line.find("<COPASI") != std::string::npos)
    {
      pushData();
      mData.mContentType = ContentType::COPASI;
      mData.mReferenceDir = pwd;

      CCopasiXML XML;
      XML.setFunctionList(&CRootContainer::getFunctionList()->loadedFunctions());
      XML.setDatamodel(this);

      SCopasiXMLGUI * pGUI = NULL;

      if (mData.mWithGUI)
        {
          pGUI = new SCopasiXMLGUI("GUI", this);
          XML.setGUI(pGUI);
        }

      try
        {
          if (!XML.load(in, pwd))
            {
              XML.freeModel();
              XML.freeTaskList();
              XML.freeReportList();
              XML.freePlotList();
              XML.freeGUI();
              XML.freeLayoutList();

              // restore the OldData
              popData();

              CRegisteredCommonName::setEnabled(true);
              return false;
            }
        }
      catch (...)
        {
          XML.freeModel();
          XML.freeTaskList();
          XML.freeReportList();
          XML.freePlotList();
          XML.freeGUI();
          XML.freeLayoutList();

          // restore the OldData
          popData();

          // rethrow the exception so the program flow should still be
          // the same as before
          CRegisteredCommonName::setEnabled(true);
          throw;
        }

      if (XML.getModel() != NULL)
        {
          mData.pModel = XML.getModel();
          add(mData.pModel, true);
        }

      if (XML.getTaskList() != NULL)
        {
          mData.pTaskList = XML.getTaskList();
          add(mData.pTaskList, true);
        }

      if (XML.getReportList() != NULL)
        {
          mData.pReportDefinitionList = XML.getReportList();
          add(mData.pReportDefinitionList, true);
        }

      if (XML.getPlotList() != NULL)
        {
          mData.pPlotDefinitionList = XML.getPlotList();
          add(mData.pPlotDefinitionList, true);
        }

      if (XML.getLayoutList() != NULL)
        {
          mData.pListOfLayouts = XML.getLayoutList();
          add(mData.pListOfLayouts, true);
        }

      if (mData.mWithGUI)
        {
          mData.pGUI = pGUI;
        }
    }
  else if (Line.find("<sbml") != std::string::npos)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCXML + 3, "sbml", 0);

      CRegisteredCommonName::setEnabled(true);
      return false;
    }
  else
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCXML + 13);

      CRegisteredCommonName::setEnabled(true);
      return false;
    }

  commonAfterLoad(pProcessReport, deleteOldData);

  CRegisteredCommonName::setEnabled(true);
  return true;
}

bool CDataModel::loadModel(const std::string & fileName,
                           CProcessReport * pProcessReport,
                           const bool & deleteOldData)
{
  std::string PWD;
  COptions::getValue("PWD", PWD);

  std::string FileName = fileName;

  if (CDirEntry::isRelativePath(FileName) && !CDirEntry::makePathAbsolute(FileName, PWD))
    FileName = CDirEntry::fileName(FileName);

  PWD = CDirEntry::dirName(FileName);

#ifdef WIN32
  std::ifstream File(CLocaleString::fromUtf8(FileName).c_str(), std::ios_base::binary);
#else
  std::ifstream File(CLocaleString::fromUtf8(FileName).c_str());
#endif

  if (File.fail())
    {
      CCopasiMessage Message(CCopasiMessage::RAW,
                             "File error when opening '%s'.",
                             FileName.c_str());
      return false;
    }

  if (!loadModel(File, PWD, pProcessReport, deleteOldData))
    {
      return false;
    }

  switch (mData.mContentType)
    {
      case ContentType::COPASI:
        mData.mSaveFileName = CDirEntry::normalize(FileName);
        // we have to store the reference directory
        mData.mReferenceDir = CDirEntry::dirName(mData.mSaveFileName);
        break;

      case ContentType::GEPASI:
        mData.mSaveFileName = CDirEntry::dirName(FileName)
                              + CDirEntry::Separator
                              + CDirEntry::baseName(FileName);

        {
          std::string Suffix = CDirEntry::suffix(FileName);

          if (strcasecmp(Suffix.c_str(), ".gps") != 0)
            mData.mSaveFileName += Suffix;
        }

        mData.mSaveFileName += ".cps";

        mData.mSaveFileName = CDirEntry::normalize(mData.mSaveFileName);
        // we have to store the reference directory
        mData.mReferenceDir = CDirEntry::dirName(mData.mSaveFileName);
        break;

      default:
        fatalError();
        break;
    }

  return true;
}

bool CDataModel::addModel(const std::string & fileName, CProcessReport * pProcessReport)
{
  bool result = false;

  CDataModel * pMergeDM = CRootContainer::addDatamodel();

  if (isProbablySBML(fileName))
    {
      try
        {
          result = pMergeDM->importSBML(fileName, pProcessReport, false);
        }
      catch (...)
        {
        }
    }
  else
    {

      try
        {
          result = pMergeDM->loadModel(fileName, pProcessReport, false);
        }
      catch (...)
        {
        }
    }

  C_INT32 numDatamodels = (C_INT32) CRootContainer::getDatamodelList()->size();
  CModel * pModel = NULL;
  CModel * pMergeModel = NULL;

  if (numDatamodels >= 2 && result) //after loading the model to be merged there should be at least 2 datamodels...
    {
      //the base model is assumed to be the first one
      pModel = getModel();
      //the model to be merged is the last one
      pMergeModel = (*CRootContainer::getDatamodelList())[numDatamodels - 1].getModel();
    }

  if (result && pModel && pMergeModel)
    {
      CModelExpansion expand(pModel);
      mLastAddedObjects = expand.copyCompleteModel(pMergeModel);
      CCopasiMessage::clearDeque();
    }

  if (pMergeModel)
    CRootContainer::removeDatamodel(numDatamodels - 1);

  return result;
}

bool CDataModel::loadModelParameterSets(const std::string & fileName,
                                        CProcessReport * pProcessReport)
{
  bool wasParameterSetLoaded = false;
  bool loaded = false;

  try
    {
      loaded = CRootContainer::addDatamodel()->loadModel(fileName, pProcessReport, false);
    }
  catch (...)
    {
    }

  C_INT32 numDatamodels = (C_INT32) CRootContainer::getDatamodelList()->size();

  if (numDatamodels == 0)
    return false;

  CModel * parameterSetModel = loaded ? ((*CRootContainer::getDatamodelList())[numDatamodels - 1]).getModel() : NULL;

  if (!parameterSetModel)
    return false;

  CModel * pModel = getModel();

  if (!pModel)
    return false;

  CDataVectorN< CModelParameterSet > & thisSet = pModel->getModelParameterSets();
  CCommonName thisModelsCn = pModel->getCN();

  CDataVectorN< CModelParameterSet > & loadedSet = parameterSetModel->getModelParameterSets();
  CCommonName loadedModelCn = parameterSetModel->getCN();

for (CModelParameterSet & set : loadedSet)
    {
for (CModelParameter * current : dynamic_cast< CModelParameterGroup & >(set))
        {
          replaceCnInGroup(current, loadedModelCn, thisModelsCn);
        }

      CModelParameterSet * clonedSet = new CModelParameterSet(set, pModel, true);
      std::string UniqueName = clonedSet->getObjectName();
      thisSet.createUniqueName(UniqueName);

      if (UniqueName != clonedSet->getObjectName())
        {
          if (clonedSet->diff(thisSet[clonedSet->getObjectName()], CCore::Framework::ParticleNumbers, false) == CModelParameter::CompareResult::Identical)
            {
              delete clonedSet;
              clonedSet = NULL;
            }
          else
            {
              clonedSet->setObjectName(UniqueName);
            }
        }

      if (clonedSet != NULL)
        {
          thisSet.add(clonedSet, true);
          wasParameterSetLoaded = true;
        }
    }

  CRootContainer::removeDatamodel(numDatamodels - 1);

  return wasParameterSetLoaded;
}

void CDataModel::replaceCnInGroup(CModelParameter * pParam,
                                  const std::string & oldCN,
                                  const std::string & newCN)
{
  CModelParameterGroup * group = dynamic_cast< CModelParameterGroup * >(pParam);

  if (!group)
    return;

for (CModelParameter * element : *group)
    {
      CModelParameterGroup * inside = dynamic_cast< CModelParameterGroup * >(element);

      if (inside)
        {
          replaceCnInGroup(inside, oldCN, newCN);
        }

      std::string cn = element->getCN();
      std::string::size_type start = cn.find(oldCN);

      if (start == std::string::npos)
        continue;

      cn.replace(start, oldCN.length(), newCN);

      element->setCN(CCommonName(cn));
    }
}

bool CDataModel::saveModelParameterSets(const std::string & fileName)
{
  CCopasiXML XML;
  XML.setModel(getModel());
  std::ofstream os(CLocaleString::fromUtf8(fileName).c_str());

  if (os.fail())
    return false;

  return XML.saveModelParameterSets(os, fileName);
}

void CDataModel::copyExperimentalDataTo(const std::string & path)
{
  CFitProblem * problem = dynamic_cast< CFitProblem * >(getTaskList()->operator[](CTaskEnum::TaskName[CTaskEnum::Task::parameterFitting]).getProblem());

  if (!problem)
    return;

  {
    CExperimentSet & experiments = problem->getExperimentSet();

    std::vector< std::string > fileNames = experiments.getFileNames();
    std::vector< std::string >::iterator it = fileNames.begin();

    std::map< std::string, std::string > renamedExperiments;
    std::map< std::string, std::string >::iterator renameIt;

    for (; it != fileNames.end(); ++it)
      {
        std::string destination = "./" + CDirEntry::fileName(*it);
        CDirEntry::makePathAbsolute(destination, path);

        int count = 0;

        while (CDirEntry::exist(destination))
          {
            std::stringstream str;
            str << "./" << CDirEntry::baseName(*it) << "_" << ++count << "." << Util::getExtension(*it);
            destination = str.str();
            CDirEntry::makePathAbsolute(destination, path);
          }

        renamedExperiments[*it] = destination;
        Util::copyFile(*it, destination);
      }

    // rename files
    for (renameIt = renamedExperiments.begin(); renameIt != renamedExperiments.end(); ++renameIt)
      {
        for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
          {
            CExperiment * current = experiments.getExperiment(i);

            if (current->getFileName() == renameIt->first)
              {
                current->setFileName(renameIt->second);
              }
          }
      }
  }

  {
    CExperimentSet & experiments = problem->getCrossValidationSet();

    std::vector< std::string > fileNames = experiments.getFileNames();
    std::vector< std::string >::iterator it = fileNames.begin();

    std::map< std::string, std::string > renamedExperiments;
    std::map< std::string, std::string >::iterator renameIt;

    for (; it != fileNames.end(); ++it)
      {
        std::string destination = "./" + CDirEntry::fileName(*it);
        CDirEntry::makePathAbsolute(destination, path);

        int count = 0;

        while (CDirEntry::exist(destination))
          {
            std::stringstream str;
            str << "./" << CDirEntry::baseName(*it) << "_" << ++count << "." << Util::getExtension(*it);
            destination = str.str();
            CDirEntry::makePathAbsolute(destination, path);
          }

        renamedExperiments[*it] = destination;
        Util::copyFile(*it, destination);
      }

    // rename files
    for (renameIt = renamedExperiments.begin(); renameIt != renamedExperiments.end(); ++renameIt)
      {
        for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
          {
            CExperiment * current = experiments.getExperiment(i);

            if (current->getFileName() == renameIt->first)
              {
                current->setFileName(renameIt->second);
              }
          }
      }
  }
}

bool CDataModel::saveModel(const std::string & fileName, CProcessReport * pProcessReport, bool overwriteFile, const bool & autoSave)
{
  CCopasiMessage::clearDeque();

  std::string FileName = (fileName != "") ? fileName : mData.mSaveFileName;

  std::string PWD;
  COptions::getValue("PWD", PWD);

  if (CDirEntry::isRelativePath(FileName) && !CDirEntry::makePathAbsolute(FileName, PWD))
    FileName = CDirEntry::fileName(FileName);

  if (CDirEntry::exist(FileName))
    {
      if (!overwriteFile)
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCDirEntry + 1,
                         FileName.c_str());
          return false;
        }

      if (!CDirEntry::isWritable(FileName))
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCDirEntry + 2,
                         FileName.c_str());
          return false;
        }
    }

  try
    {
      // We do not care whether the model compiles or not
      // We just save as much as we can
      mData.pModel->compileIfNecessary(pProcessReport);

      // Assure that the parameter set reflects all changes made to the model.
      mData.pModel->getActiveModelParameterSet().refreshFromModel(false);
    }

  catch (...)
    {
      return false;
    }

  if (mNeedToSaveExperimentalData)
    {
      copyExperimentalDataTo(CDirEntry::dirName(FileName));
      mNeedToSaveExperimentalData = false;
    }

  CCopasiXML XML;

  XML.setModel(mData.pModel);
  XML.setTaskList(mData.pTaskList);
  XML.setReportList(mData.pReportDefinitionList);
  XML.setPlotList(mData.pPlotDefinitionList);
  XML.setGUI(mData.pGUI);
  XML.setLayoutList(*mData.pListOfLayouts);
  XML.setDatamodel(this);
  bool success = true;

  if (!autoSave)
    {
      // We are first writing to a temporary file to prevent accidental
      // destruction of an existing file in case the save command fails.
      std::string TmpFileName;
      COptions::getValue("Tmp", TmpFileName);
      TmpFileName = CDirEntry::createTmpName(TmpFileName, ".cps");

      try
        {
          if (!XML.CCopasiXMLInterface::save(TmpFileName, CDirEntry::dirName(FileName)))
            {
              CDirEntry::remove(TmpFileName);
              success = false;
            }
        }

      catch (...)
        {
          CDirEntry::remove(TmpFileName);
          return false;
        }

      if (success && !CDirEntry::move(TmpFileName, FileName))
        success = false;
    }

  if (autoSave || !success)
    {
      try
        {
          if (!XML.CCopasiXMLInterface::save(FileName, CDirEntry::dirName(FileName)))
            return false;
        }

      catch (...)
        {
          return false;
        }
    }

  if (!autoSave)
    {
      changed(false);
      mData.mSaveFileName = CDirEntry::normalize(FileName);
      mData.mReferenceDir = CDirEntry::dirName(mData.mSaveFileName);
    }

  return true;
}

std::string CDataModel::saveModelToString(CProcessReport * pProcessReport)
{
  CCopasiMessage::clearDeque();

  std::string PWD;
  COptions::getValue("PWD", PWD);

  try
    {
      // We do not care whether the model compiles or not
      // We just save as much as we can
      mData.pModel->compileIfNecessary(pProcessReport);

      // Assure that the parameter set reflects all changes made to the model.
      mData.pModel->getActiveModelParameterSet().refreshFromModel(false);
    }

  catch (...)
    {
      return "";
    }

  CCopasiXML XML;

  XML.setModel(mData.pModel);
  XML.setTaskList(mData.pTaskList);
  XML.setReportList(mData.pReportDefinitionList);
  XML.setPlotList(mData.pPlotDefinitionList);
  XML.setGUI(mData.pGUI);
  XML.setLayoutList(*mData.pListOfLayouts);
  XML.setDatamodel(this);

  std::string TmpFileName;
  COptions::getValue("Tmp", TmpFileName);
  std::stringstream str;
  XML.save(str, TmpFileName);
  return str.str();
}

bool CDataModel::autoSave()
{
  if (!mData.mAutoSaveNeeded)
    return true;

  std::string AutoSave;

  COptions::getValue("Tmp", AutoSave);

  if (AutoSave == "")
    return false;

  AutoSave += CDirEntry::Separator + "tmp_";

  if (mData.mSaveFileName != "")
    AutoSave += CDirEntry::baseName(mData.mSaveFileName);
  else
    AutoSave += "untitled";

  AutoSave += ".cps";

  try
    {
      if (!saveModel(AutoSave, NULL, true, true))
        return false;
    }

  catch (...)
    {
      return false;
    }

  mData.mAutoSaveNeeded = false;
  return true;
}

bool CDataModel::newModel(CProcessReport * pProcessReport,
                          const bool & deleteOldData)
{
  //deal with the CModel
  pushData();

  // set content type to COPASI
  mData.mContentType = ContentType::COPASI;

  CRegisteredCommonName::setEnabled(false);
  commonAfterLoad(pProcessReport, deleteOldData);
  CRegisteredCommonName::setEnabled(true);

  return true;
}

bool CDataModel::importSBMLFromString(const std::string & sbmlDocumentText,
                                      CProcessReport * pProcessReport,
                                      const bool & deleteOldData)
{
  // During load no objects will be renamed;
  CRegisteredCommonName::setEnabled(false);

  pushData();

  CCopasiMessage::clearDeque();

  SBMLImporter importer;
  // Right now we always import the COPASI MIRIAM annotation if it is there.
  // Later this will be configurable by the user in the preferences dialog
  importer.setImportCOPASIMIRIAM(true);
  importer.setImportHandler(pProcessReport);
  //mCopasi2SBMLMap.clear();
  CModel * pModel = NULL;

  SBMLDocument * pSBMLDocument = NULL;
  std::map< const CDataObject *, SBase * > Copasi2SBMLMap;

  CListOfLayouts * pLol = NULL; //

  try
    {
      pModel = importer.parseSBML(sbmlDocumentText, pSBMLDocument, Copasi2SBMLMap, pLol, this);
    }

  catch (CCopasiException & except)
    {
      importer.restoreFunctionDB();
      importer.deleteCopasiModel();
      popData();

      CRegisteredCommonName::setEnabled(true);
      throw except;
    }

  catch (...)
    {
      importer.deleteCopasiModel();
      importer.restoreFunctionDB();
      popData();
      CRegisteredCommonName::setEnabled(true);

      throw;
    }

  if (pModel == NULL)
    {
      importer.restoreFunctionDB();
      importer.deleteCopasiModel();
      popData();

      CRegisteredCommonName::setEnabled(true);
      return false;
    }

  if (pModel != NULL)
    {
      mData.pModel = pModel;
      add(mData.pModel, true);
    }

  if (pLol != NULL)
    {
      mData.pListOfLayouts = pLol;
      add(mData.pListOfLayouts, true);
    }

  mData.pCurrentSBMLDocument = pSBMLDocument;
  mData.mCopasi2SBMLMap = Copasi2SBMLMap;
  mData.mContentType = ContentType::SBML;

  commonAfterLoad(pProcessReport, deleteOldData);

  CRegisteredCommonName::setEnabled(true);
  return true;
}

bool CDataModel::importSBML(const std::string & fileName,
                            CProcessReport * pProcessReport,
                            const bool & deleteOldData)
{
  // During load no objects will be renamed;
  CRegisteredCommonName::setEnabled(false);
  CCopasiMessage::clearDeque();

  std::string PWD;
  COptions::getValue("PWD", PWD);

  std::string FileName = fileName;

  if (CDirEntry::isRelativePath(FileName) && !CDirEntry::makePathAbsolute(FileName, PWD))
    FileName = CDirEntry::fileName(FileName);

  SBMLImporter importer;
  // Right now we always import the COPASI MIRIAM annotation if it is there.
  // Later this will be settable by the user in the preferences dialog
  importer.setImportCOPASIMIRIAM(true);
  importer.setImportHandler(pProcessReport);

  CModel * pModel = NULL;

  SBMLDocument * pSBMLDocument = NULL;
  std::map< const CDataObject *, SBase * > Copasi2SBMLMap;

  CListOfLayouts * pLol = NULL;

  pushData();

  try
    {
      // store the file name and reference dir, so the importer can use it
      mData.mSBMLFileName = CDirEntry::normalize(FileName);
      mData.mReferenceDir = CDirEntry::dirName(mData.mSBMLFileName);

      pModel = importer.readSBML(FileName, pSBMLDocument, Copasi2SBMLMap, pLol, this);
    }

  catch (CCopasiException & except)
    {
      importer.deleteCopasiModel();
      importer.restoreFunctionDB();
      popData();

      CRegisteredCommonName::setEnabled(true);
      throw except;
    }
  catch (...)
    {
      importer.deleteCopasiModel();
      importer.restoreFunctionDB();
      popData();
      CRegisteredCommonName::setEnabled(true);

      throw;
    }

  if (pModel == NULL)
    {
      importer.deleteCopasiModel();
      importer.restoreFunctionDB();
      popData();

      CRegisteredCommonName::setEnabled(true);
      return false;
    }

  if (pModel != NULL)
    {
      mData.pModel = pModel;
      add(mData.pModel, true);
    }

  if (pLol != NULL)
    {
      mData.pListOfLayouts = pLol;
      add(mData.pListOfLayouts, true);
    }

  mData.pCurrentSBMLDocument = pSBMLDocument;
  mData.mCopasi2SBMLMap = Copasi2SBMLMap;
  mData.mContentType = ContentType::SBML;

  commonAfterLoad(pProcessReport, deleteOldData);

  mData.mSaveFileName = CDirEntry::dirName(FileName)
                        + CDirEntry::Separator
                        + CDirEntry::baseName(FileName);

  std::string Suffix = CDirEntry::suffix(FileName);

  if (strcasecmp(Suffix.c_str(), ".xml") != 0)
    mData.mSaveFileName += Suffix;

  mData.mSaveFileName += ".cps";
  mData.mSaveFileName = CDirEntry::normalize(mData.mSaveFileName);
  // store the reference directory
  mData.mReferenceDir = CDirEntry::dirName(mData.mSaveFileName);
  mData.mSBMLFileName = CDirEntry::normalize(FileName);

  CRegisteredCommonName::setEnabled(true);
  return true;
}

std::string CDataModel::exportSBMLToString(CProcessReport * pProcessReport, int sbmlLevel, int sbmlVersion)
{
  SBMLDocument * pOrigSBMLDocument = NULL;

  // if we export an L2 model to L3 or vice versa, we have to throw away any prior information
  // about the current sbml document because libsbml does not support the conversion
  // so we need to make sure that all model elements are created from scratch from the corresponding COPASI elements
  if (this->mData.pCurrentSBMLDocument != NULL && ((this->mData.pCurrentSBMLDocument->getLevel() > 2 && sbmlLevel < 3) || (this->mData.pCurrentSBMLDocument->getLevel() < 3 && sbmlLevel > 2)))
    {
      pOrigSBMLDocument = this->mData.pCurrentSBMLDocument;
      this->mData.pCurrentSBMLDocument = NULL;
    }

  CCopasiMessage::clearDeque();
  static std::string failedCompile("The model cannot be exported, as it failed to compile. \n%s");

  try
    {
      if (!mData.pModel->compileIfNecessary(pProcessReport))
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, failedCompile.c_str(), CCopasiMessage::getAllMessageText().c_str());
          return "";
        }
    }
  catch (CCopasiException &)
    {
      // don't add the exception twice
      throw;
    }
  catch (...)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, failedCompile.c_str(), CCopasiMessage::getAllMessageText().c_str());
      return "";
    }

  CSBMLExporter exporter;
  // Per default export COPASIs MIRIAM annotation.
  // This should eventually be determined by a setting in the preferences
  // dialog.
  exporter.setExportCOPASIMIRIAM(true);
  exporter.setHandler(pProcessReport);
  std::string str = exporter.exportModelToString(*this, sbmlLevel, sbmlVersion);

  // only get the new model if it is not a Level 1 model
  // During export to Level 1 the function definitions have been deleted and therefore
  // all information associated with the function definitions will be gone if the user exports
  // to Level 2 after having exported to Level 1
  // This is actual vital to get around Bug 1086 as well.
  // Once I have a Level 1 model, all calls to setName on an
  // SBML object in that model also resets the id, which does not work with the current exporter
  if ((sbmlLevel != 1 || mData.pCurrentSBMLDocument == NULL) && pOrigSBMLDocument == NULL)
    {
      if (mData.pCurrentSBMLDocument != exporter.getSBMLDocument())
        {
          pdelete(mData.pCurrentSBMLDocument);
        }

      // disown the SBML Document from the exporter so we don't have to copy it
      exporter.disownSBMLDocument();
      mData.pCurrentSBMLDocument = exporter.getSBMLDocument();
      // we also need to get the new copasi2sbml map otherwise it contains invalid pointers
      // since the objects
      mData.mCopasi2SBMLMap.clear();
      std::map< const CDataObject *, SBase * >::const_iterator it = exporter.getCOPASI2SBMLMap().begin();
      std::map< const CDataObject *, SBase * >::const_iterator endit = exporter.getCOPASI2SBMLMap().end();

      while (it != endit)
        {
          mData.mCopasi2SBMLMap.insert(std::pair< CDataObject *, SBase * >(const_cast< CDataObject * >(it->first), it->second));
          ++it;
        }
    }
  // if we have saved the original SBML model somewhere
  // we have to reset it
  else if (pOrigSBMLDocument != NULL)
    {
      mData.pCurrentSBMLDocument = pOrigSBMLDocument;
    }

  return str;
}

bool CDataModel::exportSBML(const std::string & fileName,
                            bool overwriteFile,
                            int sbmlLevel,
                            int sbmlVersion,
                            bool /*exportIncomplete*/,
                            bool exportCOPASIMIRIAM,
                            CProcessReport * pProcessReport)
{
  CCopasiMessage::clearDeque();

  if (fileName == "")
    return false;

  std::string PWD;
  COptions::getValue("PWD", PWD);

  std::string FileName = fileName;

  if (CDirEntry::isRelativePath(FileName) && !CDirEntry::makePathAbsolute(FileName, PWD))
    FileName = CDirEntry::fileName(FileName);

  if (CDirEntry::exist(FileName))
    {
      if (!overwriteFile)
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCDirEntry + 1,
                         FileName.c_str());
          return false;
        }

      if (!CDirEntry::isWritable(FileName))
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCDirEntry + 2,
                         FileName.c_str());
          return false;
        }
    }

  CCopasiMessage::clearDeque();
  static std::string failedCompile("The model cannot be exported, as it failed to compile. \n%s");

  try
    {
      if (!mData.pModel->compileIfNecessary(pProcessReport))
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, failedCompile.c_str(),
                         CCopasiMessage::getAllMessageText().c_str());
          return false;
        }
    }
  catch (CCopasiException &)
    {
      // don't add the exception twice
      throw;
    }
  catch (...)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, failedCompile.c_str(),
                     CCopasiMessage::getAllMessageText().c_str());
      return false;
    }

  CSBMLExporter exporter;
  exporter.setHandler(pProcessReport);
  exporter.setExportCOPASIMIRIAM(exportCOPASIMIRIAM);
  SBMLDocument * pOrigSBMLDocument = NULL;

  // if we export an L2 model to L3 or vice versa, we have to throw away any prior information
  // about the current sbml document because libsbml does not support the conversion
  // so we need to make sure that all model elements are created from scratch from the corresponding COPASI elements
  if (this->mData.pCurrentSBMLDocument != NULL && ((this->mData.pCurrentSBMLDocument->getLevel() > 2 && sbmlLevel < 3) || (this->mData.pCurrentSBMLDocument->getLevel() < 3 && sbmlLevel > 2)))
    {
      pOrigSBMLDocument = this->mData.pCurrentSBMLDocument;
      this->mData.pCurrentSBMLDocument = NULL;
    }

  //exporter.setExportHandler(pProcessReport);
  if (!exporter.exportModel(*this, FileName, sbmlLevel, sbmlVersion, overwriteFile))
    return false;

  // only get the new model if it is not a Level 1 model
  // During export to Level 1 the function definitions have been deleted and therefore
  // all information associated with the function definitions will be gone if the user exports
  // to Level 2 after having exported to Level 1
  // This is actual vital to get around Bug 1086 as well.
  // Once I have a Level 1 model, all calls to setName on an
  // SBML object in that model also resets the id, which does not work with the current exporter
  if ((sbmlLevel != 1 || mData.pCurrentSBMLDocument == NULL) && pOrigSBMLDocument == NULL)
    {

      if (mData.pCurrentSBMLDocument != exporter.getSBMLDocument())
        pdelete(mData.pCurrentSBMLDocument);

      // disown the SBML Document from the exporter so we don't have to copy it
      exporter.disownSBMLDocument();
      mData.pCurrentSBMLDocument = exporter.getSBMLDocument();
      // we also need to get the new copasi2sbml map otherwise it contains invalid pointers
      // since the objects
      mData.mCopasi2SBMLMap.clear();
      std::map< const CDataObject *, SBase * >::const_iterator it = exporter.getCOPASI2SBMLMap().begin();
      std::map< const CDataObject *, SBase * >::const_iterator endit = exporter.getCOPASI2SBMLMap().end();

      while (it != endit)
        {
          mData.mCopasi2SBMLMap.insert(std::pair< CDataObject *, SBase * >(const_cast< CDataObject * >(it->first), it->second));
          ++it;
        }
    }
  // if we have saved the original SBML model somewhere
  // we have to reset it
  else if (pOrigSBMLDocument != NULL)
    {
      this->mData.pCurrentSBMLDocument = pOrigSBMLDocument;
    }

  mData.mSBMLFileName = FileName;
  return true;
}

std::string
CDataModel::exportMathModelToString(
  CProcessReport * pProcessReport,
  const std::string & filter)
{
  CODEExporter * pExporter = NULL;

  if (filter == "C Files (*.c)")
    {
      pExporter = new CODEExporterC;
    }
  else if (filter == "Berkeley Madonna Files (*.mmd)")
    {
      pExporter = new CODEExporterBM();
    }
  else if (filter == "XPPAUT (*.ode)")
    {
      pExporter = new CODEExporterXPPAUT;
    }

  if (pExporter == NULL)
    {
      return "";
    }

  try
    {
      if (!mData.pModel->compileIfNecessary(pProcessReport))
        return "";
    }

  catch (...)
    {
      return "";
    }

  CDataVector< CModelValue >::const_iterator it = mData.pModel->getModelValues().begin();
  CDataVector< CModelValue >::const_iterator end = mData.pModel->getModelValues().end();

  for (; it != end; ++it)
    if (it->isUsed())
      break;

  if (it != end)
    CCopasiMessage(CCopasiMessage::WARNING, MCODEExporter + 2);

  std::ostringstream os;

  if (!pExporter->exportToStream(this, os))
    {
      return "";
    }

  return os.str();
}

bool CDataModel::exportMathModel(const std::string & fileName, CProcessReport * pProcessReport, const std::string & filter, bool overwriteFile)
{
  CCopasiMessage::clearDeque();

  if (fileName == "")
    return false;

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
  else if (!CDirEntry::isWritable(CDirEntry::dirName(fileName)))
    {
      CCopasiMessage(CCopasiMessage::ERROR,
                     MCDirEntry + 2,
                     fileName.c_str());
      return false;
    }

  try
    {
      if (!mData.pModel->compileIfNecessary(pProcessReport))
        return false;
    }

  catch (...)
    {
      return false;
    }

  CDataVector< CModelValue >::const_iterator it = mData.pModel->getModelValues().begin();
  CDataVector< CModelValue >::const_iterator end = mData.pModel->getModelValues().end();

  for (; it != end; ++it)
    if (it->isUsed())
      break;

  if (it != end)
    CCopasiMessage(CCopasiMessage::WARNING, MCODEExporter + 2);

  CODEExporter * pExporter = NULL;

  if (filter == "C Files (*.c)")
    {
      pExporter = new CODEExporterC;
    }
  else if (filter == "Berkeley Madonna Files (*.mmd)")
    {
      pExporter = new CODEExporterBM();
    }
  else if (filter == "XPPAUT (*.ode)")
    {
      pExporter = new CODEExporterXPPAUT;
    }

  if (pExporter == NULL)
    {
      return false;
    }

  std::ofstream os(CLocaleString::fromUtf8(fileName).c_str(), std::ios::out);

  if (!os.good())
    {
      CCopasiMessage(CCopasiMessage::ERROR,
                     MCDirEntry + 3,
                     fileName.c_str());
      return false;
    }

  return pExporter->exportToStream(this, os);
}

void CDataModel::addCopasiFileToArchive(CombineArchive * archive,
                                        const std::string & targetName /*= "./copasi/model.cps"*/,
                                        CProcessReport * pProgressReport /*= NULL*/
                                       )
{
  if (archive == NULL)
    return;

  try
    {
      std::stringstream str;
      str << saveModelToString(pProgressReport);
      archive->addFile(str, targetName, KnownFormats::lookupFormat("copasi"), true);
    }
  catch (...)
    {
    }
}

bool CDataModel::exportShinyArchive(std::string fileName, bool includeCOPASI, bool includeData, bool overwriteFile, CProcessReport * pProgressReport)
{
  CCopasiMessage::clearDeque();

  std::string PWD;
  COptions::getValue("PWD", PWD);

  std::string fileBaseName = CDirEntry::baseName(fileName);

  if (CDirEntry::isRelativePath(fileName) && !CDirEntry::makePathAbsolute(fileName, PWD))
    fileName = CDirEntry::fileName(fileName);

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

      // delete existing file
      std::remove(fileName.c_str());
    }

  // set a temporary directory that we are are allowed to write to
  std::string tempDir;
  COptions::getValue("Tmp", tempDir);
  Util::setDefaultTempDir(tempDir);

  CombineArchive archive;

  std::map< std::string, std::string > renamedExperiments;
  std::map< std::string, std::string >::iterator renameIt;
  CFitProblem * problem = NULL;

  if (includeData)
    {
      // go through all experiments and find the files and add them to the archive
      // alter COPASI file (temporarily) to reference those files
      problem = dynamic_cast< CFitProblem * >(getTaskList()->operator[](CTaskEnum::TaskName[CTaskEnum::Task::parameterFitting]).getProblem());

      if (problem != NULL)
        {
          {
            CExperimentSet & experiments = problem->getExperimentSet();

            std::vector< std::string > fileNames = experiments.getFileNames();
            std::vector< std::string >::iterator it = fileNames.begin();

            for (; it != fileNames.end(); ++it)
              {
                //renamedExperiments[*it] = "./copasi/" + CDirEntry::fileName(*it);
                renamedExperiments[*it] = CDirEntry::fileName(*it);
                archive.addFile(*it, "./" + fileBaseName + "/copasi/" + CDirEntry::fileName(*it), KnownFormats::guessFormat(*it), false);
              }

            // rename files temporarily
            for (renameIt = renamedExperiments.begin(); renameIt != renamedExperiments.end(); ++renameIt)
              {
                for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
                  {
                    CExperiment * current = experiments.getExperiment(i);

                    if (current->getFileName() == renameIt->first)
                      {
                        current->setFileName(renameIt->second);
                      }
                  }
              }
          }
          {
            CExperimentSet & experiments = problem->getCrossValidationSet();

            std::vector< std::string > fileNames = experiments.getFileNames();
            std::vector< std::string >::iterator it = fileNames.begin();

            for (; it != fileNames.end(); ++it)
              {
                renamedExperiments[*it] = CDirEntry::fileName(*it);
                archive.addFile(*it, "./" + fileBaseName + "/copasi/" + CDirEntry::fileName(*it), KnownFormats::guessFormat(*it), false);
              }

            // rename files temporarily
            for (renameIt = renamedExperiments.begin(); renameIt != renamedExperiments.end(); ++renameIt)
              {
                for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
                  {
                    CExperiment * current = experiments.getExperiment(i);

                    if (current->getFileName() == renameIt->first)
                      {
                        current->setFileName(renameIt->second);
                      }
                  }
              }
          }
        }

      if (includeCOPASI)
        {
          addCopasiFileToArchive(&archive, "./" + fileBaseName + "/copasi/" + fileBaseName + ".cps", pProgressReport);
        }

      // restore filenames
      {
        CExperimentSet & experiments = problem->getExperimentSet();

        for (renameIt = renamedExperiments.begin(); renameIt != renamedExperiments.end(); ++renameIt)
          {
            for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
              {
                CExperiment * current = experiments.getExperiment(i);

                if (current->getFileNameOnly() == renameIt->second)
                  {
                    current->setFileName(renameIt->first);
                  }
              }
          }
      }
      {
        CExperimentSet & experiments = problem->getCrossValidationSet();

        for (renameIt = renamedExperiments.begin(); renameIt != renamedExperiments.end(); ++renameIt)
          {
            for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
              {
                CExperiment * current = experiments.getExperiment(i);

                if (current->getFileNameOnly() == renameIt->second)
                  {
                    current->setFileName(renameIt->first);
                  }
              }
          }
      }
    }

  archive.addFileFromString(shinyUIString, "./" + fileBaseName + "/ui.r", KnownFormats::lookupFormat("R"), true);
  archive.addFileFromString(shinyServerString, "./" + fileBaseName + "/server.r", KnownFormats::lookupFormat("R"), true);

  archive.writeToFile(fileName);
  return false;
}

/**
 * adds copasi message to stringstream, with optional title
 */
void addMessagesToStream(std::stringstream & msgs, CCopasiMessage::Type & highestError, const std::string & title)
{
  if (CCopasiMessage::size() == 0)
    return;

  auto curSev = CCopasiMessage::getHighestSeverity();

  if (curSev > highestError)
    highestError = curSev;

  if (!title.empty())
    msgs << std::endl
         << std::endl
         << title
         << std::endl
         << std::endl;

  msgs << CCopasiMessage::getAllMessageText();

  CCopasiMessage::clearDeque();
}

bool CDataModel::exportCombineArchive(
  std::string fileName,
  bool includeCOPASI,
  bool includeSBML,
  bool includeData,
  bool includeSEDML,
  bool overwriteFile,
  CProcessReport * pProgressReport,
  int sbmlLevel, int sbmlVersion,
  int sedmlLevel, int sedmlVersion)
{
  CCopasiMessage::clearDeque();

  std::string PWD;
  COptions::getValue("PWD", PWD);

  if (CDirEntry::isRelativePath(fileName) && !CDirEntry::makePathAbsolute(fileName, PWD))
    fileName = CDirEntry::fileName(fileName);

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

      // delete existing file
      std::remove(fileName.c_str());
    }

  // set a temporary directory that we are are allowed to write to
  std::string tempDir;
  COptions::getValue("Tmp", tempDir);
  Util::setDefaultTempDir(tempDir);

  CombineArchive archive;

  std::map< std::string, std::string > renamedExperiments;
  std::map< std::string, std::string >::iterator renameIt;
  CFitProblem * problem = NULL;

  std::stringstream msgs;
  CCopasiMessage::Type sev = CCopasiMessage::Type::RAW;

  if (includeData)
    {
      // go through all experiments and find the files and add them to the archive
      // alter COPASI file (temporarily) to reference those files
      problem = dynamic_cast< CFitProblem * >(getTaskList()->operator[](CTaskEnum::TaskName[CTaskEnum::Task::parameterFitting]).getProblem());

      if (problem != NULL)
        {
          {
            CExperimentSet & experiments = problem->getExperimentSet();

            std::vector< std::string > fileNames = experiments.getFileNames();
            std::vector< std::string >::iterator it = fileNames.begin();

            for (; it != fileNames.end(); ++it)
              {
                renamedExperiments[*it] = "./data/" + CDirEntry::fileName(*it);
                archive.addFile(*it, "./data/" + CDirEntry::fileName(*it), KnownFormats::guessFormat(*it), false);
              }

            // rename files temporarily
            for (renameIt = renamedExperiments.begin(); renameIt != renamedExperiments.end(); ++renameIt)
              {
                for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
                  {
                    CExperiment * current = experiments.getExperiment(i);

                    if (current->getFileName() == renameIt->first)
                      {
                        current->setFileName("." + renameIt->second);
                      }
                  }
              }
          }
          {
            CExperimentSet & experiments = problem->getCrossValidationSet();

            std::vector< std::string > fileNames = experiments.getFileNames();
            std::vector< std::string >::iterator it = fileNames.begin();

            for (; it != fileNames.end(); ++it)
              {
                renamedExperiments[*it] = "./data/" + CDirEntry::fileName(*it);
                archive.addFile(*it, "./data/" + CDirEntry::fileName(*it), KnownFormats::guessFormat(*it), false);
              }

            // rename files temporarily
            for (renameIt = renamedExperiments.begin(); renameIt != renamedExperiments.end(); ++renameIt)
              {
                for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
                  {
                    CExperiment * current = experiments.getExperiment(i);

                    if (current->getFileName() == renameIt->first)
                      {
                        current->setFileName("." + renameIt->second);
                      }
                  }
              }
          }
        }

      if (includeCOPASI)
        {
          addCopasiFileToArchive(&archive, "./copasi/model.cps", pProgressReport);
        }

      // restore filenames
      {
        CExperimentSet & experiments = problem->getExperimentSet();

        for (renameIt = renamedExperiments.begin(); renameIt != renamedExperiments.end(); ++renameIt)
          {
            for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
              {
                CExperiment * current = experiments.getExperiment(i);

                if (current->getFileNameOnly() == "." + renameIt->second)
                  {
                    current->setFileName(renameIt->first);
                  }
              }
          }
      }
      {
        CExperimentSet & experiments = problem->getCrossValidationSet();

        for (renameIt = renamedExperiments.begin(); renameIt != renamedExperiments.end(); ++renameIt)
          {
            for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
              {
                CExperiment * current = experiments.getExperiment(i);

                if (current->getFileNameOnly() == "." + renameIt->second)
                  {
                    current->setFileName(renameIt->first);
                  }
              }
          }
      }
    }

  if (includeCOPASI && !includeData)
    {
      addCopasiFileToArchive(&archive, "./copasi/model.cps", pProgressReport);
    }

  addMessagesToStream(msgs, sev, "Issues while creating COPASI file");

  if (includeSBML)
    {
      try
        {
          std::stringstream str;
          str << exportSBMLToString(pProgressReport, sbmlLevel, sbmlVersion);
          archive.addFile(str, "./sbml/model.xml", KnownFormats::lookupFormat("sbml"), !includeCOPASI);
        }
      catch (...)
        {
        }
    }

  addMessagesToStream(msgs, sev, "Issues while creating SBML file");

  if (includeSEDML)
    {
      std::stringstream str;
      XMLNamespaces namespaces;
      namespaces.add(SBMLNamespaces::getSBMLNamespaceURI(sbmlLevel, sbmlVersion), "sbml");
      str << exportSEDMLToString(pProgressReport, sedmlLevel, sedmlVersion, "../sbml/model.xml",
                                 &namespaces);
      archive.addFile(str, "./sedml/simulation.xml", KnownFormats::lookupFormat("sedml"), true);
    }

  addMessagesToStream(msgs, sev, "Issues while creating SED-ML file");

  try
    {
      archive.writeToFile(fileName);
    }
  catch (const std::exception &ex)
    {
      std::stringstream str;
      str << "Couldn't export combine archive due to: "
          << ex.what();

      CCopasiMessage(CCopasiMessage::ERROR, str.str().c_str());
      return false;
    }

  // add stored messages
  if (sev > CCopasiMessage::RAW)
    CCopasiMessage(sev, msgs.str().c_str());

  return true;
}


void addMessages(const std::string & title, std::stringstream & messageStream, const std::vector< CCopasiMessage > & messages)
{
  if (messages.size() == 0)
    return;

  messageStream << title << "\n";

  messageStream << "\n";

for (auto & message : messages)
    {
      auto startPos = message.getText().find_first_of("\n");
      auto text = message.getText().substr(startPos + 1);
      messageStream << " - " << text << "\n";
    }

  messageStream << "\n";
}

bool CDataModel::openCombineArchive(const std::string & fileName,
                                    CProcessReport * pProgressReport,
                                    const bool & deleteOldData,
                                    const SedmlImportOptions * pOptions)
{
  // TODO: figure out what to do with the archive, should we just extract all of it
  //       at a certain location? if so when should it be deleted.

  bool result = true;

  CombineArchive archive;

  if (!archive.initializeFromArchive(fileName))
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Invalid COMBINE archive.");
      return false;
    }

  std::string destinationDir;
  COptions::getValue("Tmp", destinationDir);
  destinationDir = CDirEntry::createTmpName(destinationDir, "");

  // apparently this creates the file too?
  if (CDirEntry::exist(destinationDir))
    CDirEntry::remove(destinationDir);

  if (!CDirEntry::createDir(destinationDir))
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Failed to create temporary directory.");
      return false;
    }

  archive.extractTo(destinationDir);
  mTempFolders.push_back(destinationDir);

  // read the master file
  const CaContent * content = archive.getMasterFile();
  bool haveCopasi = content != NULL && content->isFormat("copasi");

  // if we don't have one, or we have one we don't understand look for copasi file
  if (content == NULL ||
      (!content->isFormat("sbml") &&
       !content->isFormat("copasi") &&
       !content->isFormat("sedml")))
    {
      content = archive.getEntryByFormat("copasi");
      haveCopasi = content != NULL;

      if (!haveCopasi)
        {
          for (int i = 0; i < archive.getNumEntries(); ++i)
            {
              const CaContent * entry = archive.getEntry(i);

              if (entry->getFormat().substr(entry->getFormat().length() - 4) == "/xml" && entry->getLocation().find(".cps") != std::string::npos)
                {
                  content = entry;
                  haveCopasi = true;
                }
            }
        }
    }

  // otherwise look for an sedml file
  const CaContent * sedml_content =
    content != NULL && content->isFormat("sedml") ?
    content : archive.getEntryByFormat("sedml");

  // otherwise look for an sbml file
  const CaContent * sbml_content =
    content != NULL && content->isFormat("sbml") ?
    content : archive.getEntryByFormat("sbml");

  if (content == NULL && sbml_content == NULL && sedml_content == NULL)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "COMBINE archive without COPASI, SBML or SED-ML files.");
      return false;
    }

  bool loadedModel = false;

  int numMessagesBefore = CCopasiMessage::size();
  std::vector<CCopasiMessage> importCopasiMessages;
  std::vector< CCopasiMessage > importSedMLMessages;
  std::vector< CCopasiMessage > importSbmlMessages;

  if (haveCopasi || (content != NULL && content->isFormat("copasi")))
    {
      loadedModel = this->loadModel(destinationDir + "/" + content->getLocation(), pProgressReport, deleteOldData);

      if (loadedModel)
        {
          result = true;
          // figure out whether the file needs experimental data
          CFitProblem * pProblem = dynamic_cast< CFitProblem * >(getTaskList()->operator[](CTaskEnum::TaskName[CTaskEnum::Task::parameterFitting]).getProblem());

          if (pProblem != NULL)
            {
              CExperimentSet & experiments = pProblem->getExperimentSet();
              std::vector< std::string > experimentalDataFiles;

              for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
                {
                  CExperiment * experiment = experiments.getExperiment(i);
                  experimentalDataFiles.push_back(experiment->getFileNameOnly());
                }

              CExperimentSet & crossValidation = pProblem->getCrossValidationSet();
              std::vector< std::string > crossValidationFiles;

              for (size_t i = 0; i < crossValidation.getExperimentCount(); ++i)
                {
                  CExperiment * experiment = crossValidation.getExperiment(i);
                  crossValidationFiles.push_back(experiment->getFileNameOnly());
                }

              if (crossValidationFiles.size() + experimentalDataFiles.size() > 0)
                {
                  // need to save the files when saving the model
                  mNeedToSaveExperimentalData = true;
                }
            }

          // update report destinations

          std::string currentDir;
          CDirEntry::dirName(fileName);

          CDataVectorN< CCopasiTask > & tasks = *getTaskList();
          CDataVectorN< CCopasiTask >::iterator taskIt = tasks.begin();

          for (; taskIt != tasks.end(); ++taskIt)
            {
              std::string fileName = taskIt->getReport().getTarget();

              if (fileName.empty())
                continue;

              // if we have a relative filename, or a fileName that
              // points to a non-existing directory
              if (CDirEntry::isRelativePath(fileName) || !CDirEntry::exist(CDirEntry::dirName(fileName)))
                {
                  // we change the fileName to an absolute one
                  // with the current PWD
                  fileName = CDirEntry::fileName(fileName);

                  if (CDirEntry::isWritable(currentDir))
                    CDirEntry::makePathAbsolute(fileName, currentDir);

                  CCopasiMessage(CCopasiMessage::WARNING,
                                 "COMBINE archive import: The report target for the '%s' task has been changed to '%s'.",
                                 taskIt->getObjectName().c_str(), fileName.c_str());

                  taskIt->getReport().setTarget(fileName);
                }
            }
        }

      // save the messages
      while (numMessagesBefore < CCopasiMessage::size())
        {
          CCopasiMessage message = CCopasiMessage::getLastMessage();
          importCopasiMessages.push_back(message);
        }
    }

  numMessagesBefore = CCopasiMessage::size();

  if (loadedModel == false && sedml_content != NULL)
    {
      try
        {
          loadedModel = this->importSEDML(destinationDir + "/" + sedml_content->getLocation(), pProgressReport, deleteOldData, pOptions);
        }
      catch (const CCopasiException &)
        {
          // need to set model back as the import might have corrupted the
          // tasks
          newModel(NULL, true);
          loadedModel = false;
        }

      this->mData.mSEDMLFileName = "";
      this->mData.mSBMLFileName = "";

      // save the messages
      while (numMessagesBefore < CCopasiMessage::size())
        {
          CCopasiMessage message = CCopasiMessage::getLastMessage();
          importSedMLMessages.push_back(message);
        }

    }

  numMessagesBefore = CCopasiMessage::size();

  if (loadedModel == false && sbml_content != NULL)
    {
      loadedModel = this->importSBML(destinationDir + "/" + sbml_content->getLocation(), pProgressReport, deleteOldData);
      this->mData.mSBMLFileName = "";
    }

  // save the messages
  while (numMessagesBefore < CCopasiMessage::size())
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();
      importSbmlMessages.push_back(message);
    }


  std::stringstream messageStream;
  auto severity = loadedModel ? CCopasiMessage::WARNING : CCopasiMessage::ERROR;

  if (!importCopasiMessages.empty())
    {
      addMessages("Messages from attempted COPASI file import: ", messageStream, importCopasiMessages);

      if (sedml_content)
        {
          messageStream << "Attempting to import the SED-ML file instead." << std::endl;
        }
    }

  if (!importSedMLMessages.empty())
    {
      addMessages("Messages from attempted SED-ML file import: ", messageStream, importSedMLMessages);

      if (sbml_content)
        {
          messageStream << "Attempting to import the SBML file instead." << std::endl;
        }
    }

  if (!importSbmlMessages.empty())
    addMessages("Messages from attempted SBML file import: ", messageStream, importSbmlMessages);


  std::string additionalMessages = messageStream.str();

  if (!additionalMessages.empty())
    CCopasiMessage(severity, additionalMessages.c_str());

  this->mData.mSaveFileName = "";
  this->changed();

  return loadedModel;
}

// SEDML
bool CDataModel::importSEDMLFromString(const std::string & sedmlDocumentText,
                                       std::string referenceDir,
                                       CProcessReport * pProcessReport,
                                       const bool & deleteOldData,
                                       const SedmlImportOptions * pOptions)
{
  // During load no objects will be renamed;
  CRegisteredCommonName::setEnabled(false);

  pushData();
  mData.mReferenceDir = referenceDir;

  CCopasiMessage::clearDeque();

  SEDMLImporter importer;
  // Right now we always import the COPASI MIRIAM annotation if it is there.
  // Later this will be settable by the user in the preferences dialog
  // importer.setImportCOPASIMIRIAM(true);
  importer.setImportHandler(pProcessReport);
  //mCopasi2SBMLMap.clear();
  CModel * pModel = NULL;

  try
    {
      pModel = importer.parseSEDML(sedmlDocumentText, this, pOptions);
    }

  catch (CCopasiException & except)
    {
      importer.restoreFunctionDB();
      importer.deleteCopasiModel();
      popData();

      CRegisteredCommonName::setEnabled(true);
      throw except;
    }

  if (pModel == NULL)
    {
      importer.restoreFunctionDB();
      importer.deleteCopasiModel();
      popData();

      CRegisteredCommonName::setEnabled(true);
      return false;
    }

  importer.updateContent(mData, *this);

  commonAfterLoad(pProcessReport, deleteOldData);

  CRegisteredCommonName::setEnabled(true);
  return true;
}

bool CDataModel::importSEDML(const std::string & fileName,
                             CProcessReport * pProcessReport,
                             const bool & deleteOldData,
                             const SedmlImportOptions * pOptions)
{
  // During load no objects will be renamed;
  CRegisteredCommonName::setEnabled(false);

  CCopasiMessage::clearDeque();

  std::string PWD;
  COptions::getValue("PWD", PWD);

  std::string FileName = fileName;

  if (CDirEntry::isRelativePath(FileName) && !CDirEntry::makePathAbsolute(FileName, PWD))
    FileName = CDirEntry::fileName(FileName);

  std::ifstream File(CLocaleString::fromUtf8(FileName).c_str());

  SEDMLImporter importer;
  // Later this will be settable by the user in the preferences dialog
  // Later this will be settable by the user in the preferences dialog
  //   importer.setImportCOPASIMIRIAM(true);
  importer.setImportHandler(pProcessReport);

  CModel * pModel = NULL;

  SedDocument * pSEDMLDocument = NULL;
  std::map< CDataObject *, SedBase * > Copasi2SEDMLMap;
  std::map< CDataObject *, SBase * > Copasi2SBMLMap;

  SBMLDocument * pSBMLDocument = NULL;
  CListOfLayouts * pLol = NULL;
  COutputDefinitionVector * pLotList = NULL;

  pushData();

  try
    {
      // store the file name and reference dir, so the importer can use it
      mData.mSEDMLFileName = CDirEntry::normalize(FileName);
      mData.mReferenceDir = CDirEntry::dirName(mData.mSEDMLFileName);

      pModel = importer.readSEDML(FileName, this, pOptions);
    }

  catch (CCopasiException & except)
    {
      importer.restoreFunctionDB();
      importer.deleteCopasiModel();
      popData();

      CRegisteredCommonName::setEnabled(true);
      throw except;
    }

  if (pModel == NULL)
    {
      importer.restoreFunctionDB();
      importer.deleteCopasiModel();
      popData();

      CRegisteredCommonName::setEnabled(true);
      return false;
    }

  importer.updateContent(mData, *this);

  commonAfterLoad(pProcessReport, deleteOldData);

  mData.mSaveFileName = CDirEntry::dirName(FileName)
                        + CDirEntry::Separator
                        + CDirEntry::baseName(FileName);

  std::string Suffix = CDirEntry::suffix(FileName);

  if (strcasecmp(Suffix.c_str(), ".sedml") != 0)
    mData.mSaveFileName += Suffix;

  mData.mSaveFileName += ".cps";
  mData.mSaveFileName = CDirEntry::normalize(mData.mSaveFileName);

  // store the reference directory
  mData.mReferenceDir = CDirEntry::dirName(mData.mSaveFileName);
  mData.mSEDMLFileName = CDirEntry::normalize(FileName);

  CRegisteredCommonName::setEnabled(true);

  return true;
}

SedDocument * CDataModel::getCurrentSEDMLDocument()
{
  return mData.pCurrentSEDMLDocument;
}

bool CDataModel::setSEDMLFileName(const std::string & fileName)
{
  mData.mSEDMLFileName = CDirEntry::normalize(fileName);

  if (CDirEntry::isRelativePath(mData.mSEDMLFileName) && !CDirEntry::makePathAbsolute(mData.mSEDMLFileName, mData.mSaveFileName))
    mData.mSEDMLFileName = CDirEntry::fileName(mData.mSEDMLFileName);

  return true;
}

const std::string & CDataModel::getSEDMLFileName() const
{
  return mData.mSEDMLFileName;
}

std::map< CDataObject *, SedBase * > & CDataModel::getCopasi2SEDMLMap()
{
  return mData.mCopasi2SEDMLMap;
}

std::string CDataModel::exportSEDMLToString(CProcessReport * pProcessReport,
    int sedmlLevel,
    int sedmlVersion,
    const std::string & modelLocation,
    const XMLNamespaces * pAdditionalNamespaces)
{
  SedDocument * pOrigSEDMLDocument = NULL;

  CCopasiMessage::clearDeque();
  static std::string failedCompile("The model cannot be exported, as it failed to compile. \n%s");

  try
    {
      if (!mData.pModel->compileIfNecessary(pProcessReport))
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, failedCompile.c_str(), CCopasiMessage::getAllMessageText().c_str());
          return "";
        }
    }
  catch (CCopasiException &)
    {
      // don't add the exception twice
      throw;
    }
  catch (...)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, failedCompile.c_str(), CCopasiMessage::getAllMessageText().c_str());
      return "";
    }

  CSEDMLExporter exporter;

  if (pAdditionalNamespaces)
    exporter.setSBMLNamespaces(*pAdditionalNamespaces);

  std::string str = exporter.exportModelAndTasksToString(*this, modelLocation, sedmlLevel, sedmlVersion);

  // if we have saved the original SEDML model somewhere
  // we have to reset it
  if (pOrigSEDMLDocument != NULL)
    {
      mData.pCurrentSEDMLDocument = pOrigSEDMLDocument;
    }

  return str;
}

bool
CDataModel::exportSEDML(const std::string & fileName, bool overwriteFile,
                        int sedmlLevel, int sedmlVersion,
                        bool /*exportIncomplete*/, bool exportCOPASIMIRIAM,
                        CProcessReport * pProcessReport)
{
  CCopasiMessage::clearDeque();

  if (fileName == "")
    return false;

  std::string PWD;
  COptions::getValue("PWD", PWD);

  std::string FileName = fileName;

  if (CDirEntry::isRelativePath(FileName) && !CDirEntry::makePathAbsolute(FileName, PWD))
    FileName = CDirEntry::fileName(FileName);

  if (CDirEntry::exist(FileName))
    {
      if (!overwriteFile)
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCDirEntry + 1,
                         FileName.c_str());
          return false;
        }

      if (!CDirEntry::isWritable(FileName))
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCDirEntry + 2,
                         FileName.c_str());
          return false;
        }
    }

  CCopasiMessage::clearDeque();
  static std::string failedCompile("The model cannot be exported, as it failed to compile. \n%s");

  try
    {
      if (!mData.pModel->compileIfNecessary(pProcessReport))
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, failedCompile.c_str(), CCopasiMessage::getAllMessageText().c_str());
          return false;
        }
    }
  catch (CCopasiException &)
    {
      // don't add the exception twice
      throw;
    }
  catch (...)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, failedCompile.c_str(), CCopasiMessage::getAllMessageText().c_str());
      return false;
    }

  CSEDMLExporter exporter;

  SedDocument * pOrigSEDMLDocument = NULL;

  std::string sbmlDocument = exportSBMLToString(pProcessReport, 3, 1);
  // set namespaces to be written out on top of sbml document
  exporter.setSBMLNamespaces(3, 1);

  if (sbmlDocument == "")
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, "No support for exporting SEDML without SBML model");
    }

  if (!exporter.exportModelAndTasks(*this, FileName, sbmlDocument, sedmlLevel, sedmlVersion, overwriteFile))
    return false;

  return true;
}

void CDataModel::deleteOldData()
{
  pdelete(mOldData.pModel);
  pdelete(mOldData.pTaskList);
  pdelete(mOldData.pReportDefinitionList);
  pdelete(mOldData.pPlotDefinitionList);
  pdelete(mOldData.pListOfLayouts);
  pdelete(mOldData.pGUI);
  pdelete(mOldData.pCurrentSBMLDocument);
  pdelete(mOldData.mpUndoStack);

  pdelete(mOldData.pCurrentSEDMLDocument);

#ifdef COPASI_Versioning
  pdelete(mOldData.mpModelVersionHierarchy);
#endif // COPASI_Versioning
}

const CModel * CDataModel::getModel() const
{
  return mData.pModel;
}

const CDataModel::ContentType & CDataModel::getContentType() const
{
  if (mData.isValid())
    return mData.mContentType;

  return mOldData.mContentType;
}

CUndoStack * CDataModel::getUndoStack()
{
  if (mData.isValid())
    return mData.mpUndoStack;

  return mOldData.mpUndoStack;
}

CModel * CDataModel::getModel()
{
  if (mData.isValid())
    return mData.pModel;

  return mOldData.pModel;
}

CDataVectorN< CCopasiTask > * CDataModel::getTaskList()
{
  if (mData.isValid())
    return mData.pTaskList;

  return mOldData.pTaskList;
}

const CDataVectorN< CCopasiTask > * CDataModel::getTaskList() const
{
  if (mData.isValid())
    return mData.pTaskList;

  return mOldData.pTaskList;
}

CCopasiTask * CDataModel::addTask(const CTaskEnum::Task & taskType)
{
  CCopasiTask * pTask = NULL;
  pTask = CTaskFactory::create(taskType, mData.pTaskList);

  return pTask;
}

bool CDataModel::addDefaultTasks()
{
  size_t i;

  for (i = 0; i < CTaskEnum::TaskName.size(); i++)
    if (mData.pTaskList->getIndex(CTaskEnum::TaskName[i]) == C_INVALID_INDEX)
      addTask((CTaskEnum::Task) i);

  return true;
}

bool CDataModel::appendDependentTasks(CDataObject::ObjectSet candidates,
                                      CDataObject::DataObjectSet & dependentTasks) const
{
  dependentTasks.erase(NULL);
  size_t Size = dependentTasks.size();

  CDataObject::ObjectSet::const_iterator it = candidates.begin();
  CDataObject::ObjectSet::const_iterator end = candidates.end();

  CDataVectorN< CCopasiTask >::iterator itTask = mData.pTaskList->begin();
  CDataVectorN< CCopasiTask >::iterator endTask = mData.pTaskList->end();

  for (; it != end; ++it)
    {
      const CReportDefinition * pReportDefinition = dynamic_cast< const CReportDefinition * >(*it);

      if (pReportDefinition == NULL)
        continue;

      itTask = mData.pTaskList->begin();

      for (; itTask != endTask; ++itTask)
        {
          if (itTask->getReport().getReportDefinition() == pReportDefinition)
            {
              dependentTasks.insert(itTask);
            }
        }
    }

  dependentTasks.erase(NULL);
  return Size < dependentTasks.size();
}

CReportDefinition * CDataModel::addReport(const CTaskEnum::Task & taskType)
{
  CReportDefinition * pReport = NULL;

  switch (taskType)
    {
      case CTaskEnum::Task::steadyState:
        pReport = new CReportDefinition(CTaskEnum::TaskName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setSeparator("\t");
        pReport->getFooterAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Steady-State]"));
        break;

      case CTaskEnum::Task::timeCourse:
        pReport = new CReportDefinition(CTaskEnum::TaskName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setSeparator("\t");
        pReport->getHeaderAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Time-Course],Object=Description"));
        pReport->getFooterAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Time-Course],Object=Result"));
        break;

      case CTaskEnum::Task::scan:
        // No default report available.
        break;

      case CTaskEnum::Task::fluxMode:
        pReport = new CReportDefinition(CTaskEnum::TaskName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setSeparator("\t");
        pReport->getFooterAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"));
        break;

      case CTaskEnum::Task::optimization:
        pReport = new CReportDefinition(CTaskEnum::TaskName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator("\t");

        // Header
        pReport->getHeaderAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Optimization],Object=Description"));
        pReport->getHeaderAddr()->push_back(CCommonName("String=\\[Function Evaluations\\]"));
        pReport->getHeaderAddr()->push_back(CCommonName("Separator=\t"));
        pReport->getHeaderAddr()->push_back(CCommonName("String=\\[Best Value\\]"));
        pReport->getHeaderAddr()->push_back(CCommonName("Separator=\t"));
        pReport->getHeaderAddr()->push_back(CCommonName("String=\\[Best Parameters\\]"));

        // Body
        pReport->getBodyAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations"));
        pReport->getBodyAddr()->push_back(CCommonName("Separator=\t"));
        pReport->getBodyAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Value"));
        pReport->getBodyAddr()->push_back(CCommonName("Separator=\t"));
        pReport->getBodyAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Parameters"));

        // Footer
        pReport->getFooterAddr()->push_back(CCommonName("String=\n"));
        pReport->getFooterAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Optimization],Object=Result"));
        break;

        //**************************************************************************
      case CTaskEnum::Task::parameterFitting:
        pReport = new CReportDefinition(CTaskEnum::TaskName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator("\t");

        // Header
        pReport->getHeaderAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Parameter Estimation],Object=Description"));
        pReport->getHeaderAddr()->push_back(CCommonName("String=\\[Function Evaluations\\]"));
        pReport->getHeaderAddr()->push_back(CCommonName("Separator=\t"));
        pReport->getHeaderAddr()->push_back(CCommonName("String=\\[Best Value\\]"));
        pReport->getHeaderAddr()->push_back(CCommonName("Separator=\t"));
        pReport->getHeaderAddr()->push_back(CCommonName("String=\\[Best Parameters\\]"));

        // Body
        pReport->getBodyAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Function Evaluations"));
        pReport->getBodyAddr()->push_back(CCommonName("Separator=\t"));
        pReport->getBodyAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Best Value"));
        pReport->getBodyAddr()->push_back(CCommonName("Separator=\t"));
        pReport->getBodyAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Best Parameters"));

        // Footer
        pReport->getFooterAddr()->push_back(CCommonName("String=\n"));
        pReport->getFooterAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Parameter Estimation],Object=Result"));
        break;

        //**************************************************************************
      case CTaskEnum::Task::lyap:
        pReport = new CReportDefinition(CTaskEnum::TaskName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator("\t");

        // Header
        pReport->getHeaderAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Description"));

        // Footer
        pReport->getFooterAddr()->push_back(CCommonName("String=\n"));
        pReport->getFooterAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Result"));
        break;

        //**************************************************************************
      case CTaskEnum::Task::mca:
        pReport = new CReportDefinition(CTaskEnum::TaskName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator("\t");

        // Header
        pReport->getHeaderAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Description"));

        // Footer
        pReport->getFooterAddr()->push_back(CCommonName("String=\n"));
        pReport->getFooterAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Result"));
        break;

        //**************************************************************************
      case CTaskEnum::Task::lna:
        pReport = new CReportDefinition(CTaskEnum::TaskName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator("\t");

        // Header
        pReport->getHeaderAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Linear Noise Approximation],Object=Description"));

        // Footer
        pReport->getFooterAddr()->push_back(CCommonName("String=\n"));
        pReport->getFooterAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Linear Noise Approximation],Object=Result"));
        break;

        //**************************************************************************
      case CTaskEnum::Task::sens:
        pReport = new CReportDefinition(CTaskEnum::TaskName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator("\t");

        // Header
        pReport->getHeaderAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Sensitivities],Object=Description"));

        // Footer
        pReport->getFooterAddr()->push_back(CCommonName("String=\n"));
        pReport->getFooterAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Sensitivities],Object=Result"));
        break;

        //**************************************************************************
      case CTaskEnum::Task::tssAnalysis:
        pReport = new CReportDefinition(CTaskEnum::TaskName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator("\t");

        // Header
        pReport->getHeaderAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Time Scale Separation Analysis],Object=Description"));

        // Footer
        pReport->getFooterAddr()->push_back(CCommonName("String=\n"));
        pReport->getFooterAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Time Scale Separation Analysis],Object=Result"));
        break;

      case CTaskEnum::Task::moieties:
        pReport = new CReportDefinition(CTaskEnum::TaskName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator("\t");

        // Header
        pReport->getHeaderAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Moieties],Object=Description"));

        // Footer
        pReport->getFooterAddr()->push_back(CCommonName("String=\n"));
        pReport->getFooterAddr()->push_back(CCommonName("CN=Root,Vector=TaskList[Moieties],Object=Result"));
        break;

      default:
        return pReport;
    }

  if (pReport)
    mData.pReportDefinitionList->add(pReport, true);

  return pReport;
}

bool CDataModel::addDefaultReports()
{
  size_t i;

  for (i = 0; i < CTaskEnum::TaskName.size(); i++)
    {
      //try to create the report if it doesn't exist
      if (mData.pReportDefinitionList->getIndex(CTaskEnum::TaskName[i]) == C_INVALID_INDEX)
        {
          addReport((CTaskEnum::Task) i);
        }

      //see if the report exists now
      CReportDefinition * pReportDef = NULL;

      if (mData.pReportDefinitionList->getIndex(CTaskEnum::TaskName[i]) != C_INVALID_INDEX)
        pReportDef = &mData.pReportDefinitionList->operator[](CTaskEnum::TaskName[i]);

      //see if the task exists
      CCopasiTask * pTask = NULL;

      if (mData.pTaskList->getIndex(CTaskEnum::TaskName[i]) != C_INVALID_INDEX)
        pTask = &mData.pTaskList->operator[](CTaskEnum::TaskName[i]);

      if (pTask && pReportDef) //task and report definition exist
        {
          //if there is no report definition set the default
          if (!pTask->getReport().getReportDefinition())
            {
              pTask->getReport().setReportDefinition(pReportDef);
            }

          //TODO: also set the default report if no target file is set
          //even if a report is already set?
        }
    }

  return true;
}

const CReportDefinitionVector * CDataModel::getReportDefinitionList() const
{
  if (mData.isValid())
    return mData.pReportDefinitionList;

  return mOldData.pReportDefinitionList;
}

CReportDefinitionVector * CDataModel::getReportDefinitionList()
{
  if (mData.isValid())
    return mData.pReportDefinitionList;

  return mOldData.pReportDefinitionList;
}

const COutputDefinitionVector * CDataModel::getPlotDefinitionList() const
{
  if (mData.isValid())
    return mData.pPlotDefinitionList;

  return mOldData.pPlotDefinitionList;
}

COutputDefinitionVector * CDataModel::getPlotDefinitionList()
{
  if (mData.isValid())
    return mData.pPlotDefinitionList;

  return mOldData.pPlotDefinitionList;
}

const CListOfLayouts * CDataModel::getListOfLayouts() const
{
  if (mData.isValid())
    return mData.pListOfLayouts;

  return mOldData.pListOfLayouts;
}

CListOfLayouts * CDataModel::getListOfLayouts()
{
  if (mData.isValid())
    return mData.pListOfLayouts;

  return mOldData.pListOfLayouts;
}

SCopasiXMLGUI * CDataModel::getGUI()
{
  if (mData.isValid())
    return mData.pGUI;

  return mOldData.pGUI;
}

const std::string & CDataModel::getFileName() const
{
  return mData.mSaveFileName;
}

void CDataModel::setFileName(const std::string & fileName)
{
  mData.mSaveFileName = fileName;
}

std::string CDataModel::getDefaultFileName(const std::string & suffix) const
{
  std::string Default("untitled");

  if (!mData.mSaveFileName.empty())
    Default = CDirEntry::dirName(mData.mSaveFileName) + CDirEntry::Separator + CDirEntry::baseName(mData.mSaveFileName);

  return Default + suffix;
}

bool CDataModel::isChanged() const
{
  return mData.mChanged;
}

void CDataModel::changed(const bool & changed)
{
  mData.mChanged = changed;
  mData.mAutoSaveNeeded = changed;
}

SBMLDocument * CDataModel::getCurrentSBMLDocument()
{
  return mData.pCurrentSBMLDocument;
}

bool CDataModel::setSBMLFileName(const std::string & fileName)
{
  mData.mSBMLFileName = CDirEntry::normalize(fileName);

  if (CDirEntry::isRelativePath(mData.mSBMLFileName) && !CDirEntry::makePathAbsolute(mData.mSBMLFileName, mData.mSaveFileName))
    mData.mSBMLFileName = CDirEntry::fileName(mData.mSBMLFileName);

  return true;
}

const std::string & CDataModel::getSBMLFileName() const
{
  return mData.mSBMLFileName;
}

std::map< const CDataObject *, SBase * > & CDataModel::getCopasi2SBMLMap()
{
  return mData.mCopasi2SBMLMap;
}

#ifdef COPASI_Versioning
CModelVersionHierarchy * CDataModel::getModelVersionHierarchy()
{
  return mData.mpModelVersionHierarchy;
}
#endif // COPASI_Versioning

void CDataModel::removeSBMLIdFromFunctions()
{
  CFunctionDB * pFunDB = CRootContainer::getFunctionList();
  size_t i, iMax = pFunDB->loadedFunctions().size();

  for (i = 0; i < iMax; ++i)
    {
      pFunDB->loadedFunctions()[i].setSBMLId("");
    }
}

bool CDataModel::removeLayout(const std::string & key)
{
  CLayout * pLayout =
    dynamic_cast< CLayout * >(CRootContainer::getKeyFactory()->get(key));

  if (!pLayout)
    return false;

  //Check if Layout with that name exists
  size_t index =
    mData.pListOfLayouts->CDataVector< CLayout >::getIndex(pLayout);

  if (index == C_INVALID_INDEX)
    return false;

  mData.pListOfLayouts->CDataVector< CLayout >::remove(index);

  return true;
}

const std::string & CDataModel::getReferenceDirectory() const
{
  return mData.mReferenceDir;
}

CDataModel::CContent::CContent(const bool & withGUI)
  : pModel(NULL)
  , pTaskList(NULL)
  , pReportDefinitionList(NULL)
  , pPlotDefinitionList(NULL)
  , pListOfLayouts(NULL)
  , pGUI(NULL)
  , pCurrentSBMLDocument(NULL)
  , mWithGUI(withGUI)
  , mpUndoStack(NULL)
  , mSaveFileName()
  , mContentType(ContentType::__SIZE)
  , mChanged(false)
  , mAutoSaveNeeded(false)
  , mSBMLFileName("")
  , mCopasi2SBMLMap()
  , mReferenceDir("")
  , pCurrentSEDMLDocument(NULL)
  , mCopasi2SEDMLMap()
  , mSEDMLFileName("")

#ifdef COPASI_Versioning
  , mpModelVersionHierarchy(NULL)
#endif // COPASI_Versioning
{}

CDataModel::CContent::CContent(const CContent & src)
  : pModel(src.pModel)
  , pTaskList(src.pTaskList)
  , pReportDefinitionList(src.pReportDefinitionList)
  , pPlotDefinitionList(src.pPlotDefinitionList)
  , pListOfLayouts(src.pListOfLayouts)
  , pGUI(src.pGUI)
  , pCurrentSBMLDocument(src.pCurrentSBMLDocument)
  , mWithGUI(src.mWithGUI)
  , mpUndoStack(src.mpUndoStack)
  , mSaveFileName(src.mSaveFileName)
  , mContentType(src.mContentType)
  , mChanged(src.mChanged)
  , mAutoSaveNeeded(src.mAutoSaveNeeded)
  , mSBMLFileName(src.mSBMLFileName)
  , mCopasi2SBMLMap(src.mCopasi2SBMLMap)
  , mReferenceDir(src.mReferenceDir)
  , pCurrentSEDMLDocument(src.pCurrentSEDMLDocument)
  , mCopasi2SEDMLMap(src.mCopasi2SEDMLMap)
  , mSEDMLFileName(src.mSEDMLFileName)

#ifdef COPASI_Versioning
  , mpModelVersionHierarchy(src.mpModelVersionHierarchy)
#endif // COPASI_Versioning
{}

CDataModel::CContent::~CContent()
{}

CDataModel::CContent & CDataModel::CContent::operator=(const CContent & rhs)
{
  if (this != &rhs)
    {
      pModel = rhs.pModel;
      pTaskList = rhs.pTaskList;
      pReportDefinitionList = rhs.pReportDefinitionList;
      pPlotDefinitionList = rhs.pPlotDefinitionList;
      pListOfLayouts = rhs.pListOfLayouts;
      pGUI = rhs.pGUI;
      pCurrentSBMLDocument = rhs.pCurrentSBMLDocument;
      mWithGUI = rhs.mWithGUI;
      mpUndoStack = rhs.mpUndoStack;
      mSaveFileName = rhs.mSaveFileName;
      mContentType = rhs.mContentType;
      mChanged = rhs.mChanged;
      mAutoSaveNeeded = rhs.mAutoSaveNeeded;
      mSBMLFileName = rhs.mSBMLFileName;
      mReferenceDir = rhs.mReferenceDir;
      mCopasi2SBMLMap = rhs.mCopasi2SBMLMap;

      pCurrentSEDMLDocument = rhs.pCurrentSEDMLDocument;
      mCopasi2SEDMLMap = rhs.mCopasi2SEDMLMap;
      mSEDMLFileName = rhs.mSEDMLFileName;

#ifdef COPASI_Versioning
      mpModelVersionHierarchy = rhs.mpModelVersionHierarchy;
#endif // COPASI_Versioning
    }

  return *this;
}

bool CDataModel::CContent::isValid() const
{
  return (pModel != NULL && pTaskList != NULL && pReportDefinitionList != NULL && pPlotDefinitionList != NULL && pListOfLayouts != NULL && mpUndoStack != NULL && (pGUI != NULL || mWithGUI == false));
}

void CDataModel::pushData()
{
  // make sure the old data has been deleted.
  assert(mOldData.pModel == NULL && mOldData.pTaskList == NULL && mOldData.pReportDefinitionList == NULL && mOldData.pPlotDefinitionList == NULL && mOldData.pListOfLayouts == NULL && mOldData.pGUI == NULL);

  assert(mOldData.pCurrentSEDMLDocument == NULL);

#ifdef COPASI_Versioning
  assert(mOldData.mpModelVersionHierarchy == NULL);
#endif // COPASI_Versioning

  mOldData = mData;
  mData = CContent(mData.mWithGUI);
}

void CDataModel::popData()
{
  // Make sure the old data is valid
  assert(mOldData.pModel != NULL && mOldData.pTaskList != NULL && mOldData.pReportDefinitionList != NULL && mOldData.pPlotDefinitionList != NULL && mOldData.pListOfLayouts != NULL && (mOldData.pGUI != NULL || mOldData.mWithGUI == false));

#ifdef COPASI_Versioning
  assert(mOldData.mpModelVersionHierarchy != NULL);
#endif // COPASI_Versioning

  // TODO CRITICAL We need to clean up mData to avoid memory leaks.

  mData = mOldData;
  mOldData = CContent(mOldData.mWithGUI);
}

void CDataModel::commonAfterLoad(CProcessReport * pProcessReport,
                                 const bool & deleteOldData)
{
  if (mData.pModel == NULL)
    {
      mData.pModel = new CModel(this);
    }

  CMIRIAMInfo MIRIAM;
  MIRIAM.load(mData.pModel);
  MIRIAM.addDefaultCreator();
  MIRIAM.addDefaultCreatedDT();
  MIRIAM.save();

  if (mData.pListOfLayouts == NULL)
    {
      mData.pListOfLayouts = new CListOfLayouts("ListOflayouts", this);
    }

  if (mData.pTaskList == NULL)
    {
      mData.pTaskList = new CDataVectorN< CCopasiTask >("TaskList", this);
    }

  if (mData.pReportDefinitionList == NULL)
    {
      mData.pReportDefinitionList = new CReportDefinitionVector("ReportDefinitions", this);
    }

  if (mData.pPlotDefinitionList == NULL)
    {
      mData.pPlotDefinitionList = new COutputDefinitionVector("OutputDefinitions", this);
    }

  if (mData.mWithGUI && mData.pGUI == NULL)
    {
      mData.pGUI = new SCopasiXMLGUI("GUI", this);
    }

  if (mData.mpUndoStack == NULL)
    {
      mData.mpUndoStack = new CUndoStack(*this);
    }

  mpInfo->update();

#ifdef COPASI_Versioning

  if (mData.mpModelVersionHierarchy == NULL)
    {
      mData.mpModelVersionHierarchy = new CModelVersionHierarchy(*this);
    }

#endif // COPASI_Versioning

  // We have at least one task of every type
  addDefaultTasks();
  addDefaultReports();

  if (mOldData.pModel != NULL && mOldData.pModel != mData.pModel)
    {
      mOldData.pModel->setObjectParent(NULL);
      remove(mOldData.pModel);
    }
  else
    mOldData.pModel = NULL;

  if (mOldData.pTaskList != NULL && mOldData.pTaskList != mData.pTaskList)
    {
      mOldData.pTaskList->setObjectParent(NULL);
      remove(mOldData.pTaskList);
    }
  else
    mOldData.pTaskList = NULL;

  if (mOldData.pReportDefinitionList != NULL && mOldData.pReportDefinitionList != mData.pReportDefinitionList)
    {
      mOldData.pReportDefinitionList->setObjectParent(NULL);
      remove(mOldData.pReportDefinitionList);
    }
  else
    mOldData.pReportDefinitionList = NULL;

  if (mOldData.pPlotDefinitionList != NULL && mOldData.pPlotDefinitionList != mData.pPlotDefinitionList)
    {
      mOldData.pPlotDefinitionList->setObjectParent(NULL);
      remove(mOldData.pPlotDefinitionList);
    }
  else
    mOldData.pPlotDefinitionList = NULL;

  if (mOldData.pListOfLayouts != NULL && mOldData.pListOfLayouts != mData.pListOfLayouts)
    {
      mOldData.pListOfLayouts->setObjectParent(NULL);
      remove(mOldData.pListOfLayouts);
    }
  else
    mOldData.pListOfLayouts = NULL;

  if (mOldData.pGUI != NULL && mOldData.pGUI != mData.pGUI)
    {
      mOldData.pGUI->setObjectParent(NULL);
      remove(mOldData.pGUI);
    }
  else
    mOldData.pGUI = NULL;

  if (mOldData.pCurrentSBMLDocument == mData.pCurrentSBMLDocument)
    mOldData.pCurrentSBMLDocument = NULL;

  if (mOldData.mpUndoStack == mData.mpUndoStack)
    mOldData.mpUndoStack = NULL;

  if (mOldData.pCurrentSEDMLDocument == mData.pCurrentSEDMLDocument)
    mOldData.pCurrentSEDMLDocument = NULL;

  if (mData.pModel && mData.pModel->compileIfNecessary(pProcessReport))
    {
      mData.pModel->getActiveModelParameterSet().updateModel();
    }

  // We need to initialize all the task so that results are available

  // We suppress all errors and warnings
  size_t Size = CCopasiMessage::size();

  CDataVectorN< CCopasiTask >::iterator it = mData.pTaskList->begin();
  CDataVectorN< CCopasiTask >::iterator end = mData.pTaskList->end();

  for (; it != end; ++it)
    {
      try
        {
          // need to update math container, since the one set automatically
          // by the task factory might have set an invalid old one
          if (mData.pModel)
            {
              mData.pModel->compileIfNecessary(pProcessReport);
              it->setMathContainer(&mData.pModel->getMathContainer());
            }

          // need initialize, so that all objects are created for the
          // object browser
          if (!mData.mWithGUI && !it->isScheduled())
            continue;

          it->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);

          // but we should restore any possible changes made to the model
          // by the task, without updating the model
          it->restore(false);
        }

      catch (...)
        {}
    }

  // Remove error messages created by the task initialization as this may fail
  // due to incomplete task specification at this time.
  while (CCopasiMessage::size() > Size)
    CCopasiMessage::getLastMessage();

  if (mData.pModel)
    {
      bool status = mData.pModel->compileIfNecessary(pProcessReport);

      if (!status)
        {
          // the model failed to compile tell the user
          CValidity validity = mData.pModel->getValidity();
          ;

          CCopasiMessage(CCopasiMessage::WARNING, validity.getIssueMessages().c_str());
        }

      mData.pModel->updateInitialValues(CCore::Framework::ParticleNumbers);
    }

  changed(false);

  if (deleteOldData)
    {
      CDataModel::deleteOldData();
    }
}

CUndoData::CChangeSet CDataModel::applyData(const CUndoData & data)
{
  if (mData.mpUndoStack != NULL && !data.empty())
    {
      changed();
      return mData.mpUndoStack->record(data, true);
    }

  return CUndoData::CChangeSet();
}

CUndoData::CChangeSet CDataModel::recordData(const CUndoData & data)
{
  if (mData.mpUndoStack != NULL && !data.empty())
    {
      return mData.mpUndoStack->record(data, false);
    }

  return CUndoData::CChangeSet();
}

bool CDataModel::changeModelParameter(CDataObject * element, double value)
{
  if (element == NULL)
    return false;

  CDataObjectReference< double > * pRef =
    dynamic_cast< CDataObjectReference< double > * >(element);

  if (pRef != NULL)
    {
      if (pRef->getValuePointer() != NULL)
        {
          bool isInitialConcentration = pRef->getObjectName() == "InitialConcentration" && pRef->getObjectDataModel() != NULL && pRef->getObjectDataModel()->getModel() != NULL;

          if (isInitialConcentration)
            pRef->getObjectDataModel()->getModel()->updateInitialValues(pRef);

          *static_cast< double * >(pRef->getValuePointer()) = value;

          if (isInitialConcentration)
            pRef->getObjectDataModel()->getModel()->updateInitialValues(pRef);

          return true;
        }
    }

  CCopasiParameter * pParam = dynamic_cast< CCopasiParameter * >(element);

  if (pParam != NULL)
    {
      if (pParam->getValuePointer() != NULL)
        {
          *static_cast< double * >(pParam->getValuePointer()) = value;
          return true;
        }
    }

  return false;
}

void CDataModel::reparameterizeFromIniFile(const std::string & fileName)
{
  if (!getModel())
    return;

  std::ifstream ifs(fileName.c_str(), std::ios_base::in);

  if (!ifs.good())
    {
      return;
    }

  std::string line;

  while (std::getline(ifs, line))
    {
      // remove comments
      size_t pos = line.find(';');

      if (pos != std::string::npos)
        line = line.substr(0, pos);

      pos = line.rfind('=');

      if (pos == std::string::npos) // no equals sign found invalid
        continue;

      std::string key = ResultParser::trim(line.substr(0, pos));
      std::string value = ResultParser::trim(line.substr(pos + 1));

      if (key.empty() || value.empty())
        continue;

      double dValue = ResultParser::saveToDouble(value);

      CDataObject * element =
        const_cast< CDataObject * >(findObjectByDisplayName(key));

      if (element == NULL) // no such element, or no supported element
        continue;

      if (changeModelParameter(element, dValue))
        getModel()->setCompileFlag(); // mark as changed
    }

  getModel()->compileIfNecessary(NULL); // compile if needed
}

const CDataObject * CDataModel::findObjectByDisplayName(const std::string & displayString) const
{
  const CDataModel * dataModel = this;

  if (dataModel == NULL || displayString.empty())
    return NULL;

  const CModel * model = dataModel->getModel();

  if (displayString == "Time")
    return model;

  if (displayString == "Avogadro Constant")
    return dynamic_cast< const CDataObject * >(model->getObject("Reference=" + displayString));

  if (displayString == "Quantity Conversion Factor")
    return dynamic_cast< const CDataObject * >(model->getObject("Reference=" + displayString));

  size_t pos = displayString.find("Compartments[");

  if (pos != std::string::npos)
    {
      const CDataVectorN< CCompartment > & compartments = model->getCompartments();

      for (CDataVectorN< CCompartment >::const_iterator it = compartments.begin(); it != compartments.end(); ++it)
        {
          const CCompartment * current = it;

          if (current->getObjectDisplayName() == displayString)
            {
              return current;
            }
          else if (current->getInitialValueReference() != NULL && current->getInitialValueReference()->getObjectDisplayName() == displayString)
            {
              return current->getInitialValueReference();
            }
          else if (current->getValueReference() != NULL && current->getValueReference()->getObjectDisplayName() == displayString)
            {
              return current->getValueReference();
            }
          else if (current->getRateReference() != NULL && current->getRateReference()->getObjectDisplayName() == displayString)
            {
              return current->getRateReference();
            }
        }
    }

  pos = displayString.find("Values[");

  if (pos != std::string::npos)
    {
      const CDataVectorN< CModelValue > & values = model->getModelValues();

      for (CDataVectorN< CModelValue >::const_iterator it = values.begin(); it != values.end(); ++it)
        {
          const CModelValue * current = it;

          if (current->getObjectDisplayName() == displayString)
            {
              return current;
            }
          else if (current->getInitialValueReference() != NULL && current->getInitialValueReference()->getObjectDisplayName() == displayString)
            {
              return current->getInitialValueReference();
            }
          else if (current->getValueReference() != NULL && current->getValueReference()->getObjectDisplayName() == displayString)
            {
              return current->getValueReference();
            }
          else if (current->getRateReference() != NULL && current->getRateReference()->getObjectDisplayName() == displayString)
            {
              return current->getRateReference();
            }
        }
    }

  // no reasonable check for metabolites, so lets just go through them
  {
    const CDataVector< CMetab > & metabs = model->getMetabolites();

    for (CDataVector< CMetab >::const_iterator it = metabs.begin(); it != metabs.end(); ++it)
      {
        const CMetab * current = it;

        if (current->getObjectDisplayName() == displayString || CMetabNameInterface::createUniqueDisplayName(*current, true) == displayString)
          {
            return current;
          }
        else if (current->getInitialValueReference() != NULL && current->getInitialValueReference()->getObjectDisplayName() == displayString)
          {
            return current->getInitialValueReference();
          }
        else if (current->getInitialConcentrationReference() != NULL && current->getInitialConcentrationReference()->getObjectDisplayName() == displayString)
          {
            return current->getInitialConcentrationReference();
          }
        else if (current->getValueReference() != NULL && current->getValueReference()->getObjectDisplayName() == displayString)
          {
            return current->getValueReference();
          }
        else if (current->getConcentrationReference() != NULL && current->getConcentrationReference()->getObjectDisplayName() == displayString)
          {
            return current->getConcentrationReference();
          }
        else if (current->getRateReference() != NULL && current->getRateReference()->getObjectDisplayName() == displayString)
          {
            return current->getRateReference();
          }
        else if (current->getConcentrationRateReference() != NULL && current->getConcentrationRateReference()->getObjectDisplayName() == displayString)
          {
            return current->getConcentrationRateReference();
          }
      }
  }

  // try for local reaction parameters

  pos = displayString.find(")");

  if (pos != std::string::npos && (displayString.size() > (pos + 2)))
    {
      std::string reactionName = displayString.substr(1, pos - 1);
      std::string parameter = displayString.substr(pos + 2);

      size_t reactionIndex = model->getReactions().getIndex(reactionName);

      if (reactionIndex == C_INVALID_INDEX)
        return NULL;

      const CReaction & reaction = model->getReactions()[reactionIndex];
      size_t paramIndex = reaction.getParameterIndex(parameter);

      if (paramIndex == C_INVALID_INDEX)
        {
          // might be flux / particle flux
          if (parameter == "Flux")
            return reaction.getFluxReference();

          if (parameter == "ParticleFlux")
            return reaction.getParticleFluxReference();

          return NULL;
        }

      auto & paramObjects = reaction.getParameterObjects(paramIndex);

      if (!paramObjects.empty())
        return paramObjects[0];
    }

  return NULL;
}
