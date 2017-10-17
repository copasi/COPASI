// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#define USE_LAYOUT 1

#include <sbml/SBMLDocument.h>

#ifdef COPASI_SEDML
#include <sedml/SedDocument.h>
#include "sedml/SEDMLImporter.h"
#include "sedml/CSEDMLExporter.h"
#endif

#include "copasi.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#include "copasi/core/CDataTimer.h"
#include "commandline/COptions.h"
#include "commandline/CConfigurationFile.h"
#include "commandline/CLocaleString.h"
#include "function/CFunctionDB.h"
#include "model/CModel.h"
#include "model/CMetabNameInterface.h"
#include "utilities/CTaskFactory.h"
#include "plot/COutputDefinitionVector.h"
#include "report/CKeyFactory.h"
#include "report/CReportDefinitionVector.h"
#include "sbml/CSBMLExporter.h"
#include "sbml/SBMLImporter.h"
#include "sbml/SBMLIncompatibility.h"
#include "steadystate/CMCAProblem.h"
#include "lna/CLNAProblem.h"
#include "trajectory/CTrajectoryProblem.h"
#include "tss/CODEExporter.h"
#include "tss/CODEExporterC.h"
#include "tss/CODEExporterBM.h"
#include "tss/CODEExporterXPPAUT.h"
#include "trajectory/CTrajectoryProblem.h"
#include "utilities/CCopasiException.h"
#include "utilities/CCopasiProblem.h"
#include "copasi/core/CDataVector.h"
#include "utilities/CDirEntry.h"
#include "xml/CCopasiXML.h"
#include "undo/CUndoStack.h"
#include "undo/CUndoData.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"

#include "layout/CListOfLayouts.h"
#include "layout/CLayoutInitializer.h"
#include "copasi/core/CRootContainer.h"

#ifdef WITH_COMBINE_ARCHIVE
# include <combine/combinearchive.h>
# include <combine/knownformats.h>
# include <combine/util.h>
# include <omex/CaContent.h>
# include <copasi/utilities/CCopasiMessage.h>
#endif // WITH_COMBINE_ARCHIVE

#include <copasi/parameterFitting/CFitProblem.h>
#include <copasi/parameterFitting/CExperimentSet.h>
#include <copasi/parameterFitting/CExperiment.h>

CDataModel::CDataModel(const bool withGUI):
  CDataContainer("Root", NULL, "CN", CDataObject::DataModel),
  COutputHandler(),
  mData(withGUI),
  mOldData(withGUI),
  mTempFolders(),
  mNeedToSaveExperimentalData(false),
  pOldMetabolites(new CDataVectorS < CMetabOld >)
{
  newModel(NULL, true);
  new CCopasiTimer(CCopasiTimer::Type::WALL, this);
  new CCopasiTimer(CCopasiTimer::Type::PROCESS, this);
}

// static
CDataModel * CDataModel::fromData(const CData & data)
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
bool CDataModel::applyData(const CData & data)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CDataModel::CDataModel(const std::string & name,
                       const CDataContainer * pParent,
                       const std::string & type,
                       bool withGUI):
  CDataContainer(name, pParent, type, CDataObject::DataModel),
  COutputHandler(),
  mData(withGUI),
  mOldData(withGUI),
  mTempFolders(),
  mNeedToSaveExperimentalData(false),
  pOldMetabolites(new CDataVectorS < CMetabOld >)
{
  newModel(NULL, true);
  new CCopasiTimer(CCopasiTimer::Type::WALL, this);
  new CCopasiTimer(CCopasiTimer::Type::PROCESS, this);
}

CDataModel::CDataModel(const CDataModel & src,
                       const CDataContainer * pParent):
  CDataContainer(src, pParent),
  COutputHandler(src),
  mData(src.mData),
  mOldData(src.mOldData),
  mTempFolders(),
  mNeedToSaveExperimentalData(false),
  pOldMetabolites((src.pOldMetabolites != NULL) ? new CDataVectorS < CMetabOld >(*src.pOldMetabolites, NO_PARENT) : NULL)
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

#ifdef WITH_COMBINE_ARCHIVE

  std::vector<std::string>::iterator it = mTempFolders.begin();

  for (; it != mTempFolders.end(); ++it)
    {
      Util::removeFileOrFolder(*it);
    }

  mTempFolders.clear();

#endif
}

bool CDataModel::loadModel(std::istream & in,
                           const std::string & pwd,
                           CProcessReport* pProcessReport,
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
      mData.mFileType = FileType::Gepasi;
      mData.mReferenceDir = pwd;

      if (mData.pModel->load(inbuf))
        {
          popData();
          CRegisteredCommonName::setEnabled(true);
          return false;
        }

      static_cast<CTrajectoryTask *>(&mData.pTaskList->operator[]("Time-Course"))->load(inbuf);

      static_cast<CSteadyStateTask *>(&mData.pTaskList->operator[]("Steady-State"))->load(inbuf);
    }
  else if (Line.find("<COPASI") != std::string::npos)
    {
      pushData();
      mData.mFileType = FileType::CopasiML;
      mData.mReferenceDir = pwd;

      CCopasiXML XML;
      XML.setFunctionList(&CRootContainer::getFunctionList()->loadedFunctions());
      XML.setDatamodel(this);

      SCopasiXMLGUI *pGUI = NULL;

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
                           CProcessReport* pProcessReport,
                           const bool & deleteOldData)
{
  std::string PWD;
  COptions::getValue("PWD", PWD);

  std::string FileName = fileName;

  if (CDirEntry::isRelativePath(FileName) &&
      !CDirEntry::makePathAbsolute(FileName, PWD))
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

  switch (mData.mFileType)
    {
      case FileType::CopasiML:
        mData.mSaveFileName = CDirEntry::normalize(FileName);
        // we have to store the reference directory
        mData.mReferenceDir = CDirEntry::dirName(mData.mSaveFileName);
        break;

      case FileType::Gepasi:
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

#ifdef WITH_COMBINE_ARCHIVE
void CDataModel::copyExperimentalDataTo(const std::string& path)
{
  CFitProblem* problem = dynamic_cast<CFitProblem*>((*getTaskList())[static_cast< size_t >(CTaskEnum::Task::parameterFitting)].getProblem());

  if (!problem) return;

  {
    CExperimentSet& experiments = problem->getExperimentSet();

    std::vector<std::string> fileNames = experiments.getFileNames();
    std::vector<std::string>::iterator it = fileNames.begin();

    std::map<std::string, std::string> renamedExperiments;
    std::map<std::string, std::string>::iterator renameIt;

    for (; it != fileNames.end(); ++it)
      {
        std::string destination = "./" + CDirEntry::fileName(*it);
        CDirEntry::makePathAbsolute(destination, path);

        int count = 0;

        while (CDirEntry::exist(destination))
          {
            std::stringstream str; str << "./" << CDirEntry::baseName(*it) << "_" << ++count << "." << Util::getExtension(*it);
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
            CExperiment* current = experiments.getExperiment(i);

            if (current->getFileName() == renameIt->first)
              {
                current->setFileName(renameIt->second);
              }
          }
      }
  }

  {
    CExperimentSet& experiments = problem->getCrossValidationSet();

    std::vector<std::string> fileNames = experiments.getFileNames();
    std::vector<std::string>::iterator it = fileNames.begin();

    std::map<std::string, std::string> renamedExperiments;
    std::map<std::string, std::string>::iterator renameIt;

    for (; it != fileNames.end(); ++it)
      {
        std::string destination = "./" + CDirEntry::fileName(*it);
        CDirEntry::makePathAbsolute(destination, path);

        int count = 0;

        while (CDirEntry::exist(destination))
          {
            std::stringstream str; str << "./" << CDirEntry::baseName(*it) << "_" << ++count << "." << Util::getExtension(*it);
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
            CExperiment* current = experiments.getExperiment(i);

            if (current->getFileName() == renameIt->first)
              {
                current->setFileName(renameIt->second);
              }
          }
      }
  }
}
#endif // WITH_COMBINE_ARCHIVE

bool
CDataModel::saveModel(const std::string & fileName, CProcessReport* pProcessReport,
                      bool overwriteFile,
                      const bool & autoSave)
{
  CCopasiMessage::clearDeque();

  std::string FileName = (fileName != "") ? fileName : mData.mSaveFileName;

  std::string PWD;
  COptions::getValue("PWD", PWD);

  if (CDirEntry::isRelativePath(FileName) &&
      !CDirEntry::makePathAbsolute(FileName, PWD))
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

#ifdef WITH_COMBINE_ARCHIVE

  if (mNeedToSaveExperimentalData)
    {
      copyExperimentalDataTo(CDirEntry::dirName(FileName));
      mNeedToSaveExperimentalData = false;
    }

#endif // WITH_COMBINE_ARCHIVE

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
          if (!XML.CCopasiXMLInterface::save(TmpFileName, FileName))
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
          if (!XML.CCopasiXMLInterface::save(FileName, FileName))
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
  if (!mData.mAutoSaveNeeded) return true;

  std::string AutoSave;

  COptions::getValue("Tmp", AutoSave);

  if (AutoSave == "") return false;

  AutoSave += CDirEntry::Separator + "tmp_";

  if (mData.mSaveFileName != "")
    AutoSave += CDirEntry::baseName(mData.mSaveFileName);
  else
    AutoSave += "untitled";

  AutoSave += ".cps";

  try
    {
      if (!saveModel(AutoSave, NULL, true, true)) return false;
    }

  catch (...)
    {
      return false;
    }

  mData.mAutoSaveNeeded = false;
  return true;
}

bool CDataModel::newModel(CProcessReport* pProcessReport,
                          const bool & deleteOldData)
{
  //deal with the CModel
  pushData();

  CRegisteredCommonName::setEnabled(false);
  commonAfterLoad(pProcessReport, deleteOldData);
  CRegisteredCommonName::setEnabled(true);

  return true;
}

bool CDataModel::importSBMLFromString(const std::string& sbmlDocumentText,
                                      CProcessReport* pImportHandler,
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
  importer.setImportHandler(pImportHandler);
  //mCopasi2SBMLMap.clear();
  CModel* pModel = NULL;

  SBMLDocument * pSBMLDocument = NULL;
  std::map<const CDataObject*, SBase*> Copasi2SBMLMap;

  CListOfLayouts * pLol = NULL; //

  try
    {
      pModel = importer.parseSBML(sbmlDocumentText, CRootContainer::getFunctionList(),
                                  pSBMLDocument, Copasi2SBMLMap, pLol, this);
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
  mData.mFileType = FileType::SBML;

  commonAfterLoad(pImportHandler, deleteOldData);

  CRegisteredCommonName::setEnabled(true);
  return true;
}

bool CDataModel::importSBML(const std::string & fileName,
                            CProcessReport* pImportHandler,
                            const bool & deleteOldData)
{
  // During load no objects will be renamed;
  CRegisteredCommonName::setEnabled(false);
  CCopasiMessage::clearDeque();

  std::string PWD;
  COptions::getValue("PWD", PWD);

  std::string FileName = fileName;

  if (CDirEntry::isRelativePath(FileName) &&
      !CDirEntry::makePathAbsolute(FileName, PWD))
    FileName = CDirEntry::fileName(FileName);

  std::ifstream File(CLocaleString::fromUtf8(FileName).c_str());

  SBMLImporter importer;
  // Right now we always import the COPASI MIRIAM annotation if it is there.
  // Later this will be settable by the user in the preferences dialog
  importer.setImportCOPASIMIRIAM(true);
  importer.setImportHandler(pImportHandler);

  CModel* pModel = NULL;

  SBMLDocument * pSBMLDocument = NULL;
  std::map<const CDataObject*, SBase*> Copasi2SBMLMap;

  CListOfLayouts * pLol = NULL;

  pushData();

  try
    {
      // store the file name and reference dir, so the importer can use it
      mData.mSBMLFileName = CDirEntry::normalize(FileName);
      mData.mReferenceDir = CDirEntry::dirName(mData.mSBMLFileName);

      pModel = importer.readSBML(FileName, CRootContainer::getFunctionList(),
                                 pSBMLDocument, Copasi2SBMLMap, pLol, this);
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
  mData.mFileType = FileType::SBML;

  commonAfterLoad(pImportHandler, deleteOldData);

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

std::string CDataModel::exportSBMLToString(CProcessReport* pExportHandler, int sbmlLevel, int sbmlVersion)
{
  CCopasiMessage::clearDeque();
  SBMLDocument* pOrigSBMLDocument = NULL;

  // if we export an L2 model to L3 or vice versa, we have to throw away any prior information
  // about the current sbml document because libsbml does not support the conversion
  // so we need to make sure that all model elements are created from scratch from the corresponding COPASI elements
  if (this->mData.pCurrentSBMLDocument != NULL &&
      ((this->mData.pCurrentSBMLDocument->getLevel() > 2 && sbmlLevel < 3) ||
       (this->mData.pCurrentSBMLDocument->getLevel() < 3 && sbmlLevel > 2)
      )
     )
    {
      pOrigSBMLDocument = this->mData.pCurrentSBMLDocument;
      this->mData.pCurrentSBMLDocument = NULL;
    }

  CCopasiMessage::clearDeque();
  static std::string failedCompile("The model cannot be exported, as it failed to compile. \n%s");

  try
    {
      if (!mData.pModel->compileIfNecessary(pExportHandler))
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, failedCompile.c_str(), CCopasiMessage::getAllMessageText().c_str());
          return "";
        }
    }
  catch (CCopasiException&)
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
  exporter.setHandler(pExportHandler);
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
      std::map<const CDataObject*, SBase*>::const_iterator it = exporter.getCOPASI2SBMLMap().begin();
      std::map<const CDataObject*, SBase*>::const_iterator endit = exporter.getCOPASI2SBMLMap().end();

      while (it != endit)
        {
          mData.mCopasi2SBMLMap.insert(std::pair<CDataObject*, SBase*>(const_cast<CDataObject*>(it->first), it->second));
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

bool
CDataModel::exportSBML(const std::string & fileName,
                       bool overwriteFile,
                       int sbmlLevel,
                       int sbmlVersion,
                       bool /*exportIncomplete*/,
                       bool exportCOPASIMIRIAM,
                       CProcessReport* pExportHandler)
{
  CCopasiMessage::clearDeque();

  if (fileName == "") return false;

  std::string PWD;
  COptions::getValue("PWD", PWD);

  std::string FileName = fileName;

  if (CDirEntry::isRelativePath(FileName) &&
      !CDirEntry::makePathAbsolute(FileName, PWD))
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
      if (!mData.pModel->compileIfNecessary(pExportHandler))
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, failedCompile.c_str(),
                         CCopasiMessage::getAllMessageText().c_str());
          return false;
        }
    }
  catch (CCopasiException&)
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
  exporter.setHandler(pExportHandler);
  exporter.setExportCOPASIMIRIAM(exportCOPASIMIRIAM);
  SBMLDocument* pOrigSBMLDocument = NULL;

  // if we export an L2 model to L3 or vice versa, we have to throw away any prior information
  // about the current sbml document because libsbml does not support the conversion
  // so we need to make sure that all model elements are created from scratch from the corresponding COPASI elements
  if (this->mData.pCurrentSBMLDocument != NULL &&
      ((this->mData.pCurrentSBMLDocument->getLevel() > 2 && sbmlLevel < 3) ||
       (this->mData.pCurrentSBMLDocument->getLevel() < 3 && sbmlLevel > 2)
      )
     )
    {
      pOrigSBMLDocument = this->mData.pCurrentSBMLDocument;
      this->mData.pCurrentSBMLDocument = NULL;
    }

  //exporter.setExportHandler(pExportHandler);
  if (!exporter.exportModel(*this, FileName, sbmlLevel, sbmlVersion, overwriteFile)) return false;

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
      std::map<const CDataObject*, SBase*>::const_iterator it = exporter.getCOPASI2SBMLMap().begin();
      std::map<const CDataObject*, SBase*>::const_iterator endit = exporter.getCOPASI2SBMLMap().end();

      while (it != endit)
        {
          mData.mCopasi2SBMLMap.insert(std::pair<CDataObject*, SBase*>(const_cast<CDataObject*>(it->first), it->second));
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
  CProcessReport* pProcessReport,
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
    if (it->isUsed()) break;

  if (it != end)
    CCopasiMessage(CCopasiMessage::WARNING, MCODEExporter + 2);

  std::ostringstream os;

  if (!pExporter->exportToStream(this, os))
    {
      return "";
    }

  return os.str();
}

bool CDataModel::exportMathModel(const std::string & fileName, CProcessReport* pProcessReport,
                                 const std::string & filter, bool overwriteFile)
{
  CCopasiMessage::clearDeque();

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
    if (it->isUsed()) break;

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

#ifdef WITH_COMBINE_ARCHIVE

void
CDataModel::addCopasiFileToArchive(CombineArchive *archive,
                                   const std::string& targetName /*= "./copasi/model.cps"*/,
                                   CProcessReport * pProgressReport /*= NULL*/
                                  )
{
  if (archive == NULL) return;

  try
    {
      std::stringstream str; str << saveModelToString(pProgressReport);
      archive->addFile(str, targetName, KnownFormats::lookupFormat("copasi"), true);
    }
  catch (...)
    {
    }
}

bool CDataModel::exportCombineArchive(std::string fileName, bool includeCOPASI, bool includeSBML, bool includeData, bool includeSEDML, bool overwriteFile, CProcessReport * pProgressReport)
{
  CCopasiMessage::clearDeque();

  std::string PWD;
  COptions::getValue("PWD", PWD);

  if (CDirEntry::isRelativePath(fileName) &&
      !CDirEntry::makePathAbsolute(fileName, PWD))
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

  CombineArchive archive;

  std::map<std::string, std::string> renamedExperiments;
  std::map<std::string, std::string>::iterator renameIt;
  CFitProblem *problem = NULL;

  if (includeData)
    {
      // go through all experiments and find the files and add them to the archive
      // alter COPASI file (temporarily) to reference those files
      problem = dynamic_cast<CFitProblem*>((*getTaskList())[static_cast< size_t >(CTaskEnum::Task::parameterFitting)].getProblem());
      {
        CExperimentSet& experiments = problem->getExperimentSet();

        std::vector<std::string> fileNames = experiments.getFileNames();
        std::vector<std::string>::iterator it = fileNames.begin();

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
                CExperiment* current = experiments.getExperiment(i);

                if (current->getFileName() == renameIt->first)
                  {
                    current->setFileName("." + renameIt->second);
                  }
              }
          }
      }
      {
        CExperimentSet& experiments = problem->getCrossValidationSet();

        std::vector<std::string> fileNames = experiments.getFileNames();
        std::vector<std::string>::iterator it = fileNames.begin();

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
                CExperiment* current = experiments.getExperiment(i);

                if (current->getFileName() == renameIt->first)
                  {
                    current->setFileName("." + renameIt->second);
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
        CExperimentSet& experiments = problem->getExperimentSet();

        for (renameIt = renamedExperiments.begin(); renameIt != renamedExperiments.end(); ++renameIt)
          {
            for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
              {
                CExperiment* current = experiments.getExperiment(i);

                if (current->getFileNameOnly() == "." + renameIt->second)
                  {
                    current->setFileName(renameIt->first);
                  }
              }
          }
      }
      {
        CExperimentSet& experiments = problem->getCrossValidationSet();

        for (renameIt = renamedExperiments.begin(); renameIt != renamedExperiments.end(); ++renameIt)
          {
            for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
              {
                CExperiment* current = experiments.getExperiment(i);

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

  if (includeSBML)
    {
      try
        {
          std::stringstream str; str << exportSBMLToString(pProgressReport, 2, 4);
          archive.addFile(str, "./sbml/model.xml", KnownFormats::lookupFormat("sbml"), !includeCOPASI);
        }
      catch (...)
        {
        }
    }

  if (includeSEDML)
    {
      std::stringstream str; str << exportSEDMLToString(pProgressReport, 1, 2, "../sbml/model.xml");
      archive.addFile(str, "./sedml/simulation.xml", KnownFormats::lookupFormat("sedml"), !includeCOPASI);
    }

  archive.writeToFile(fileName);

  return false;
}

bool CDataModel::openCombineArchive(const std::string & fileName,
                                    CProcessReport * pProgressReport,
                                    const bool & deleteOldData)
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
  CDirEntry::createDir(destinationDir);

  archive.extractTo(destinationDir);
  mTempFolders.push_back(destinationDir);

  // read the master file
  const CaContent* content = archive.getMasterFile();

  // if we don't have one, or we have one we don't understand look for copasi file
  if (content == NULL ||
      (content->getFormat() != KnownFormats::lookupFormat("sbml") &&
       content->getFormat() != KnownFormats::lookupFormat("copasi") &&
       content->getFormat() != KnownFormats::lookupFormat("sedml")))
    content = archive.getEntryByFormat("copasi");

  // otherwise look for an sedml file
  if (content == NULL)
    content = archive.getEntryByFormat("sedml");

  // otherwise look for an sbml file
  if (content == NULL)
    content = archive.getEntryByFormat("sbml");

  if (content == NULL)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "COMBINE archive without COPASI, SBML or SED-ML files.");
      return false;
    }

  if (content->isFormat("copasi"))
    {
      result = this->loadModel(destinationDir + "/" + content->getLocation(), pProgressReport, deleteOldData);

      if (result)
        {
          // figure out whether the file needs experimental data
          CFitProblem* pProblem = dynamic_cast<CFitProblem*>((*getTaskList())[static_cast< size_t >(CTaskEnum::Task::parameterFitting)].getProblem());
          CExperimentSet& experiments = pProblem->getExperimentSet();
          std::vector<std::string> experimentalDataFiles;

          for (size_t i = 0; i < experiments.getExperimentCount(); ++i)
            {
              CExperiment* experiment = experiments.getExperiment(i);
              experimentalDataFiles.push_back(experiment->getFileNameOnly());
            }

          CExperimentSet& crossValidation = pProblem->getCrossValidationSet();
          std::vector<std::string> crossValidationFiles;

          for (size_t i = 0; i < crossValidation.getExperimentCount(); ++i)
            {
              CExperiment* experiment = crossValidation.getExperiment(i);
              crossValidationFiles.push_back(experiment->getFileNameOnly());
            }

          if (crossValidationFiles.size() + experimentalDataFiles.size() > 0)
            {
              // need to save the files when saving the model
              mNeedToSaveExperimentalData = true;
            }

          // update report destinations

          std::string currentDir;
          CDirEntry::dirName(fileName);

          CDataVectorN< CCopasiTask >& tasks = *getTaskList();
          CDataVectorN< CCopasiTask >::iterator taskIt = tasks.begin();

          for (; taskIt != tasks.end(); ++taskIt)
            {
              std::string fileName = taskIt->getReport().getTarget();

              if (fileName.empty())
                continue;

              // if we have a relative filename, or a fileName that
              // points to a non-existing directory
              if (CDirEntry::isRelativePath(fileName) ||
                  !CDirEntry::exist(CDirEntry::dirName(fileName)))
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
    }
  else if (content->isFormat("sedml"))
    {
      result = this->importSEDML(destinationDir + "/" + content->getLocation(), pProgressReport, deleteOldData);
      this->mData.mSEDMLFileName = "";
      this->mData.mSBMLFileName = "";
    }
  else if (content->isFormat("sbml"))
    {
      result = this->importSBML(destinationDir + "/" + content->getLocation(), pProgressReport, deleteOldData);
      this->mData.mSBMLFileName = "";
    }

  this->mData.mSaveFileName = "";
  this->changed();

  return result;
}

#endif

//TODO SEDML
#ifdef COPASI_SEDML
bool CDataModel::importSEDMLFromString(const std::string& sedmlDocumentText,
                                       CProcessReport* pImportHandler,
                                       const bool & deleteOldData)
{
  // During load no objects will be renamed;
  CRegisteredCommonName::setEnabled(false);

  pushData();

  CCopasiMessage::clearDeque();

  SEDMLImporter importer;
  // Right now we always import the COPASI MIRIAM annotation if it is there.
  // Later this will be settable by the user in the preferences dialog
// importer.setImportCOPASIMIRIAM(true);
  importer.setImportHandler(pImportHandler);
  //mCopasi2SBMLMap.clear();
  CModel* pModel = NULL;

  SedDocument * pSEDMLDocument = NULL;
  std::map<CDataObject*, SedBase*> Copasi2SEDMLMap;
  std::map<CDataObject*, SBase*> Copasi2SBMLMap;

  SBMLDocument * pSBMLDocument = NULL;
  CListOfLayouts * pLol = NULL;
  COutputDefinitionVector *pLotList = NULL; // = new COutputDefinitionVector("OutputDefinitions", this);

  try
    {
      pModel = importer.parseSEDML(sedmlDocumentText, pImportHandler, pSBMLDocument, pSEDMLDocument,
                                   Copasi2SEDMLMap, Copasi2SBMLMap, pLol, pLotList, this);
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

  mData.pCurrentSEDMLDocument = pSEDMLDocument;
  mData.mCopasi2SEDMLMap = Copasi2SEDMLMap;
  mData.mFileType = FileType::SEDML;

  commonAfterLoad(pImportHandler, deleteOldData);

  CRegisteredCommonName::setEnabled(true);
  return true;
}

bool CDataModel::importSEDML(const std::string & fileName,
                             CProcessReport* pImportHandler,
                             const bool & deleteOldData)
{
  // During load no objects will be renamed;
  CRegisteredCommonName::setEnabled(false);

  CCopasiMessage::clearDeque();

  std::string PWD;
  COptions::getValue("PWD", PWD);

  std::string FileName = fileName;

  if (CDirEntry::isRelativePath(FileName) &&
      !CDirEntry::makePathAbsolute(FileName, PWD))
    FileName = CDirEntry::fileName(FileName);

  std::ifstream File(CLocaleString::fromUtf8(FileName).c_str());

  SEDMLImporter importer;
  // Later this will be settable by the user in the preferences dialog
  // Later this will be settable by the user in the preferences dialog
//   importer.setImportCOPASIMIRIAM(true);
  importer.setImportHandler(pImportHandler);

  CModel* pModel = NULL;

  SedDocument * pSEDMLDocument = NULL;
  std::map<CDataObject*, SedBase*> Copasi2SEDMLMap;
  std::map<CDataObject*, SBase*> Copasi2SBMLMap;

  SBMLDocument * pSBMLDocument = NULL;
  CTrajectoryTask *trajTask = NULL;
  CListOfLayouts * pLol = NULL;
  COutputDefinitionVector *pLotList = NULL;

  pushData();

  try
    {
      // store the file name and reference dir, so the importer can use it
      mData.mSEDMLFileName = CDirEntry::normalize(FileName);
      mData.mReferenceDir = CDirEntry::dirName(mData.mSEDMLFileName);

      pModel = importer.readSEDML(FileName, pImportHandler, pSBMLDocument, pSEDMLDocument,
                                  Copasi2SEDMLMap, Copasi2SBMLMap, pLol, pLotList, this);
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

  if (pLol != NULL)
    {
      mData.pPlotDefinitionList = pLotList;
      add(mData.pPlotDefinitionList, true);
    }

  commonAfterLoad(pImportHandler, deleteOldData);
  // common after load resets all tasks, so we need to reset them.
  importer.importTasks(Copasi2SEDMLMap);

  mData.pCurrentSEDMLDocument = pSEDMLDocument;
  mData.mCopasi2SEDMLMap = Copasi2SEDMLMap;
  mData.mFileType = FileType::SEDML;

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

SedDocument* CDataModel::getCurrentSEDMLDocument()
{
  return mData.pCurrentSEDMLDocument;
}

bool CDataModel::setSEDMLFileName(const std::string & fileName)
{
  mData.mSEDMLFileName = CDirEntry::normalize(fileName);

  if (CDirEntry::isRelativePath(mData.mSEDMLFileName) &&
      !CDirEntry::makePathAbsolute(mData.mSEDMLFileName, mData.mSaveFileName))
    mData.mSEDMLFileName = CDirEntry::fileName(mData.mSEDMLFileName);

  return true;
}

const std::string & CDataModel::getSEDMLFileName() const
{return mData.mSEDMLFileName;}

std::map<CDataObject*, SedBase*>& CDataModel::getCopasi2SEDMLMap()
{
  return mData.mCopasi2SEDMLMap;
}

std::string CDataModel::exportSEDMLToString(CProcessReport* pExportHandler,
    int sedmlLevel, int sedmlVersion,
    const std::string& modelLocation)
{
  CCopasiMessage::clearDeque();
  SedDocument* pOrigSEDMLDocument = NULL;

  CCopasiMessage::clearDeque();
  static std::string failedCompile("The model cannot be exported, as it failed to compile. \n%s");

  try
    {
      if (!mData.pModel->compileIfNecessary(pExportHandler))
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, failedCompile.c_str(), CCopasiMessage::getAllMessageText().c_str());
          return "";
        }
    }
  catch (CCopasiException&)
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
  std::string str = exporter.exportModelAndTasksToString(*this, modelLocation, sedmlLevel, sedmlVersion);

  // if we have saved the original SEDML model somewhere
  // we have to reset it
  if (pOrigSEDMLDocument != NULL)
    {
      mData.pCurrentSEDMLDocument = pOrigSEDMLDocument;
    }

  return str;
}

bool CDataModel::exportSEDML(const std::string & fileName, bool overwriteFile, int sedmlLevel, int sedmlVersion, bool /*exportIncomplete*/, bool exportCOPASIMIRIAM, CProcessReport* pExportHandler)
{
  CCopasiMessage::clearDeque();

  if (fileName == "") return false;

  std::string PWD;
  COptions::getValue("PWD", PWD);

  std::string FileName = fileName;

  if (CDirEntry::isRelativePath(FileName) &&
      !CDirEntry::makePathAbsolute(FileName, PWD))
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
      if (!mData.pModel->compileIfNecessary(pExportHandler))
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, failedCompile.c_str(), CCopasiMessage::getAllMessageText().c_str());
          return false;
        }
    }
  catch (CCopasiException&)
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
  // exporter.setExportCOPASIMIRIAM(exportCOPASIMIRIAM);
  SedDocument* pOrigSEDMLDocument = NULL;

  //exporter.setExportHandler(pExportHandler);
//  const std::string& SBMLFileName = "";

  std::string sbmlDocument = "";
  sbmlDocument = this->exportSBMLToString(pExportHandler, 2, 3);

  // std::cout<<sbmlDocument<<std::endl; //for debuging
  if (sbmlDocument == "")
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, "No support for exporting SEDML without SBML model");
    }

  if (!exporter.exportModelAndTasks(*this, FileName, sbmlDocument, sedmlLevel, sedmlVersion, overwriteFile)) return false;

  return true;
}
#endif

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

#ifdef COPASI_SEDML
  pdelete(mOldData.pCurrentSEDMLDocument);
#endif
}

const CModel * CDataModel::getModel() const
{return mData.pModel;}

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
  pTask = CTaskFactory::createTask(taskType, mData.pTaskList);

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
        // No default report available.
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

      default:
        return pReport;
    }

  if (pReport) mData.pReportDefinitionList->add(pReport, true);

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
      CReportDefinition* pReportDef = NULL;

      if (mData.pReportDefinitionList->getIndex(CTaskEnum::TaskName[i]) != C_INVALID_INDEX)
        pReportDef = &mData.pReportDefinitionList->operator[](CTaskEnum::TaskName[i]);

      //see if the task exists
      CCopasiTask* pTask = NULL;

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
{return mData.mSaveFileName;}

bool CDataModel::isChanged() const
{return mData.mChanged;}

void CDataModel::changed(const bool & changed)
{
  mData.mChanged = changed;
  mData.mAutoSaveNeeded = changed;
}

SBMLDocument* CDataModel::getCurrentSBMLDocument()
{
  return mData.pCurrentSBMLDocument;
}

bool CDataModel::setSBMLFileName(const std::string & fileName)
{
  mData.mSBMLFileName = CDirEntry::normalize(fileName);

  if (CDirEntry::isRelativePath(mData.mSBMLFileName) &&
      !CDirEntry::makePathAbsolute(mData.mSBMLFileName, mData.mSaveFileName))
    mData.mSBMLFileName = CDirEntry::fileName(mData.mSBMLFileName);

  return true;
}

const std::string & CDataModel::getSBMLFileName() const
{return mData.mSBMLFileName;}

std::map<const CDataObject*, SBase*>& CDataModel::getCopasi2SBMLMap()
{
  return mData.mCopasi2SBMLMap;
}

void CDataModel::removeSBMLIdFromFunctions()
{
  CFunctionDB* pFunDB = CRootContainer::getFunctionList();
  size_t i, iMax = pFunDB->loadedFunctions().size();

  for (i = 0; i < iMax; ++i)
    {
      pFunDB->loadedFunctions()[i].setSBMLId("");
    }
}

bool CDataModel::removeLayout(const std::string & key)
{
  CLayout *pLayout =
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

const std::string& CDataModel::getReferenceDirectory() const
{
  return mData.mReferenceDir;
}

CDataModel::CContent::CContent(const bool & withGUI):
  pModel(NULL),
  pTaskList(NULL),
  pReportDefinitionList(NULL),
  pPlotDefinitionList(NULL),
  pListOfLayouts(NULL),
  pGUI(NULL),
  pCurrentSBMLDocument(NULL),
  mWithGUI(withGUI),
  mpUndoStack(NULL),
  mSaveFileName(),
  mFileType(FileType::unset),
  mChanged(false),
  mAutoSaveNeeded(false),
  mSBMLFileName(""),
  mCopasi2SBMLMap(),
  mReferenceDir("")
#ifdef COPASI_SEDML
  , pCurrentSEDMLDocument(NULL)
  , mCopasi2SEDMLMap()
  , mSEDMLFileName("")
#endif
{}

CDataModel::CContent::CContent(const CContent & src):
  pModel(src.pModel),
  pTaskList(src.pTaskList),
  pReportDefinitionList(src.pReportDefinitionList),
  pPlotDefinitionList(src.pPlotDefinitionList),
  pListOfLayouts(src.pListOfLayouts),
  pGUI(src.pGUI),
  pCurrentSBMLDocument(src.pCurrentSBMLDocument),
  mWithGUI(src.mWithGUI),
  mpUndoStack(src.mpUndoStack),
  mSaveFileName(src.mSaveFileName),
  mFileType(src.mFileType),
  mChanged(src.mChanged),
  mAutoSaveNeeded(src.mAutoSaveNeeded),
  mSBMLFileName(src.mSBMLFileName),
  mCopasi2SBMLMap(src.mCopasi2SBMLMap),
  mReferenceDir(src.mReferenceDir)
#ifdef COPASI_SEDML
  , pCurrentSEDMLDocument(src.pCurrentSEDMLDocument)
  , mCopasi2SEDMLMap(src.mCopasi2SEDMLMap)
  , mSEDMLFileName(src.mSEDMLFileName)
#endif
{}

CDataModel::CContent::~CContent()
{}

CDataModel::CContent & CDataModel::CContent::operator = (const CContent & rhs)
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
      mFileType = rhs.mFileType;
      mChanged = rhs.mChanged;
      mAutoSaveNeeded = rhs.mAutoSaveNeeded;
      mSBMLFileName = rhs.mSBMLFileName;
      mReferenceDir = rhs.mReferenceDir;
      mCopasi2SBMLMap = rhs.mCopasi2SBMLMap;

#ifdef COPASI_SEDML
      pCurrentSEDMLDocument = rhs.pCurrentSEDMLDocument;
      mCopasi2SEDMLMap = rhs.mCopasi2SEDMLMap;
      mSEDMLFileName = rhs.mSEDMLFileName;
#endif
    }

  return *this;
}

bool CDataModel::CContent::isValid() const
{
  return (pModel != NULL &&
          pTaskList != NULL &&
          pReportDefinitionList != NULL &&
          pPlotDefinitionList != NULL &&
          pListOfLayouts != NULL &&
          mpUndoStack != NULL &&
          (pGUI != NULL || mWithGUI == false));
}

void CDataModel::pushData()
{
  bool condition = true;
#ifdef COPASI_SEDML
  condition = mOldData.pCurrentSEDMLDocument == NULL;
#endif
  // make sure the old data has been deleted.
  assert(mOldData.pModel == NULL &&
         mOldData.pTaskList == NULL &&
         mOldData.pReportDefinitionList == NULL &&
         mOldData.pPlotDefinitionList == NULL &&
         mOldData.pListOfLayouts == NULL &&
         mOldData.pGUI == NULL &&
         condition
        );

  mOldData = mData;
  mData = CContent(mData.mWithGUI);
}

void CDataModel::popData()
{
  // Make sure the old data is valid
  assert(mOldData.pModel != NULL &&
         mOldData.pTaskList != NULL &&
         mOldData.pReportDefinitionList != NULL &&
         mOldData.pPlotDefinitionList != NULL &&
         mOldData.pListOfLayouts != NULL &&
         (mOldData.pGUI != NULL || mOldData.mWithGUI == false));

  // TODO CRITICAL We need to clean up mData to avoid memory leaks.

  mData = mOldData;
  mOldData = CContent(mOldData.mWithGUI);
}

void CDataModel::commonAfterLoad(CProcessReport* pProcessReport,
                                 const bool & deleteOldData)
{
  if (mData.pModel == NULL)
    {
      mData.pModel = new CModel(this);
    }

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

  // We have at least one task of every type
  addDefaultTasks();
  addDefaultReports();

  if (mOldData.pModel != NULL &&
      mOldData.pModel != mData.pModel)
    {
      mOldData.pModel->setObjectParent(NULL);
      remove(mOldData.pModel);
    }
  else
    mOldData.pModel = NULL;

  if (mOldData.pTaskList != NULL &&
      mOldData.pTaskList != mData.pTaskList)
    {
      mOldData.pTaskList->setObjectParent(NULL);
      remove(mOldData.pTaskList);
    }
  else
    mOldData.pTaskList = NULL;

  if (mOldData.pReportDefinitionList != NULL &&
      mOldData.pReportDefinitionList != mData.pReportDefinitionList)
    {
      mOldData.pReportDefinitionList->setObjectParent(NULL);
      remove(mOldData.pReportDefinitionList);
    }
  else
    mOldData.pReportDefinitionList = NULL;

  if (mOldData.pPlotDefinitionList != NULL &&
      mOldData.pPlotDefinitionList != mData.pPlotDefinitionList)
    {
      mOldData.pPlotDefinitionList->setObjectParent(NULL);
      remove(mOldData.pPlotDefinitionList);
    }
  else
    mOldData.pPlotDefinitionList = NULL;

  if (mOldData.pListOfLayouts != NULL &&
      mOldData.pListOfLayouts != mData.pListOfLayouts)
    {
      mOldData.pListOfLayouts->setObjectParent(NULL);
      remove(mOldData.pListOfLayouts);
    }
  else
    mOldData.pListOfLayouts = NULL;

  if (mOldData.pGUI != NULL &&
      mOldData.pGUI != mData.pGUI)
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

#ifdef COPASI_SEDML

  if (mOldData.pCurrentSEDMLDocument == mData.pCurrentSEDMLDocument)
    mOldData.pCurrentSEDMLDocument = NULL;

#endif

  if (mData.pModel->isCompileNecessary() &&
      mData.pModel->compileIfNecessary(pProcessReport))
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
          // need initialize, so that all objects are created for the
          // object browser
          it->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);

          // but we should restore any possible changes made to the model
          // by the task, without updating the model
          bool update = it->isUpdateModel();
          it->setUpdateModel(false);
          it->restore();
          it->setUpdateModel(update);
        }

      catch (...) {}
    }

  // Remove error messages created by the task initialization as this may fail
  // due to incomplete task specification at this time.
  while (CCopasiMessage::size() > Size)
    CCopasiMessage::getLastMessage();

  if (mData.pModel)
    {
      mData.pModel->compileIfNecessary(pProcessReport);
      mData.pModel->updateInitialValues(CCore::Framework::ParticleNumbers);
    }

  changed(false);

  if (deleteOldData)
    {
      CDataModel::deleteOldData();
    }
}

void CDataModel::applyData(const CUndoData & data)
{
  // TODO CRITICAL Fix me!
  // To avoid interaction with the existing undo we avoid applying any changes
  // data.apply(*this);
  recordData(data);
}

void CDataModel::recordData(const CUndoData & data)
{
  if (mData.mpUndoStack != NULL)
    {
      mData.mpUndoStack->record(data);
    }
}


const CDataObject *CDataModel::findObjectByDisplayName(const std::string& displayString) const
{
  const CDataModel *dataModel = this;

  if (dataModel == NULL || displayString.empty()) return NULL;

  const CModel *model = dataModel->getModel();

  if (displayString == "Time") return model;

  if (displayString == "Avogadro Constant") return dynamic_cast<const CDataObject *>(model->getObject("Reference=" + displayString));

  if (displayString == "Quantity Conversion Factor") return dynamic_cast<const CDataObject *>(model->getObject("Reference=" + displayString));

  size_t pos = displayString.find("Compartments[");

  if (pos != std::string::npos)
    {
      const CDataVectorN< CCompartment > &compartments = model->getCompartments();

      for (CDataVectorN< CCompartment >::const_iterator it = compartments.begin(); it != compartments.end(); ++it)
        {
          const CCompartment *current = it;

          if (current->getObjectDisplayName() == displayString)
            {
              return current;
            }
          else if (current->getInitialValueReference() != NULL &&
                   current->getInitialValueReference()->getObjectDisplayName() == displayString)
            {
              return current->getInitialValueReference();
            }
          else if (current->getValueReference() != NULL &&
                   current->getValueReference()->getObjectDisplayName() == displayString)
            {
              return current->getValueReference();
            }
          else if (current->getRateReference() != NULL &&
                   current->getRateReference()->getObjectDisplayName() == displayString)
            {
              return current->getRateReference();
            }
        }
    }

  pos = displayString.find("Values[");

  if (pos != std::string::npos)
    {
      const CDataVectorN< CModelValue > &values = model->getModelValues();

      for (CDataVectorN< CModelValue >::const_iterator it = values.begin(); it != values.end(); ++it)
        {
          const CModelValue *current = it;

          if (current->getObjectDisplayName() == displayString)
            {
              return current;
            }
          else if (current->getInitialValueReference() != NULL &&
                   current->getInitialValueReference()->getObjectDisplayName() == displayString)
            {
              return current->getInitialValueReference();
            }
          else if (current->getValueReference() != NULL &&
                   current->getValueReference()->getObjectDisplayName() == displayString)
            {
              return current->getValueReference();
            }
          else if (current->getRateReference() != NULL &&
                   current->getRateReference()->getObjectDisplayName() == displayString)
            {
              return current->getRateReference();
            }
        }
    }

  // no reasonable check for metabolites, so lets just go through them
  {
    const CDataVector< CMetab > &metabs = model->getMetabolites();

    for (CDataVector< CMetab >::const_iterator it = metabs.begin(); it != metabs.end(); ++it)
      {
        const CMetab *current = it;

        if (current->getObjectDisplayName() == displayString || CMetabNameInterface::createUniqueDisplayName(*current, true) == displayString)
          {
            return current;
          }
        else if (current->getInitialValueReference() != NULL &&
                 current->getInitialValueReference()->getObjectDisplayName() == displayString)
          {
            return current->getInitialValueReference();
          }
        else if (current->getInitialConcentrationReference() != NULL &&
                 current->getInitialConcentrationReference()->getObjectDisplayName() == displayString)
          {
            return current->getInitialConcentrationReference();
          }
        else if (current->getValueReference() != NULL &&
                 current->getValueReference()->getObjectDisplayName() == displayString)
          {
            return current->getValueReference();
          }
        else if (current->getConcentrationReference() != NULL &&
                 current->getConcentrationReference()->getObjectDisplayName() == displayString)
          {
            return current->getConcentrationReference();
          }
        else if (current->getRateReference() != NULL &&
                 current->getRateReference()->getObjectDisplayName() == displayString)
          {
            return current->getRateReference();
          }
        else if (current->getConcentrationRateReference() != NULL &&
                 current->getConcentrationRateReference()->getObjectDisplayName() == displayString)
          {
            return current->getConcentrationRateReference();
          }
      }
  }
  return NULL;
}

