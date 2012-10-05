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

#define USE_LAYOUT 1

#include <sbml/SBMLDocument.h>

#include "copasi.h"
#include "CCopasiDataModel.h"

#include "copasi/report/CCopasiTimer.h"
#include "commandline/COptions.h"
#include "commandline/CConfigurationFile.h"
#include "commandline/CLocaleString.h"
#include "function/CFunctionDB.h"
#include "model/CModel.h"
#include "optimization/COptTask.h"
#include "parameterFitting/CFitTask.h"
#include "plot/COutputDefinitionVector.h"
#include "report/CKeyFactory.h"
#include "report/CReportDefinitionVector.h"
#include "sbml/CSBMLExporter.h"
#include "sbml/SBMLImporter.h"
#include "sbml/SBMLIncompatibility.h"
#include "scan/CScanTask.h"
#include "elementaryFluxModes/CEFMTask.h"
#include "steadystate/CMCATask.h"
#include "steadystate/CMCAProblem.h"
#include "lna/CLNATask.h"
#include "lna/CLNAProblem.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "sensitivities/CSensTask.h"
#include "tssanalysis/CTSSATask.h"
#include "crosssection/CCrossSectionTask.h"
#include "lyap/CLyapTask.h"
#include "tss/CODEExporter.h"
#include "tss/CODEExporterC.h"
#include "tss/CODEExporterBM.h"
#include "tss/CODEExporterXPPAUT.h"
#include "moieties/CMoietiesTask.h"

#include "utilities/CCopasiException.h"
#include "utilities/CCopasiProblem.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CCopasiVector.h"
#include "utilities/CDirEntry.h"
#include "xml/CCopasiXML.h"

#include "layout/CListOfLayouts.h"
#include "layout/CLayoutInitializer.h"
#include "report/CCopasiRootContainer.h"

#ifdef COPASI_NONLIN_DYN
#include "crosssection/CCrossSectionTask.h"
#endif

CDataModelRenameHandler::CDataModelRenameHandler()
{}

bool CDataModelRenameHandler::handle(const std::string & oldCN, const std::string & newCN) const
{
  const std::set<CRegisteredObjectName*> nameSet = CRegisteredObjectName::getSet();

  std::set<CRegisteredObjectName*>::const_iterator it, itEnd = nameSet.end();

  for (it = nameSet.begin(); it != itEnd; ++it)
    {
      // We need to make sure that we not change partial names
      if (((*it)->size() == oldCN.size() ||
           ((*it)->size() > oldCN.size() && (**it)[oldCN.size()] == ',')) &&
          oldCN.compare(0, oldCN.size(), **it, 0, oldCN.size()) == 0)
        {
          (**it).replace(0, oldCN.size(), newCN);
        }
    }

  return true;
}

//********************************************************************

CCopasiDataModel::CCopasiDataModel(const bool withGUI):
  CCopasiContainer("Root", NULL, "CN", CCopasiObject::DataModel),
  COutputHandler(),
  mData(withGUI),
  mOldData(withGUI),
  mRenameHandler(),
  pOldMetabolites(new CCopasiVectorS < CMetabOld >)
{
  newModel(NULL, true);
  CCopasiObject::setRenameHandler(&mRenameHandler);
  new CCopasiTimer(CCopasiTimer::WALL, this);
  new CCopasiTimer(CCopasiTimer::PROCESS, this);
}

CCopasiDataModel::CCopasiDataModel(const std::string & name,
                                   const CCopasiContainer * pParent,
                                   const std::string & type,
                                   bool withGUI):
  CCopasiContainer(name, pParent, type, CCopasiObject::DataModel),
  COutputHandler(),
  mData(withGUI),
  mOldData(withGUI),
  mRenameHandler(),
  pOldMetabolites(new CCopasiVectorS < CMetabOld >)
{
  newModel(NULL, true);
  CCopasiObject::setRenameHandler(&mRenameHandler);
  new CCopasiTimer(CCopasiTimer::WALL, this);
  new CCopasiTimer(CCopasiTimer::PROCESS, this);
}

CCopasiDataModel::~CCopasiDataModel()
{
  CCopasiObject::setRenameHandler(NULL);
  pdelete(pOldMetabolites);
}

bool CCopasiDataModel::loadModel(std::istream & in,
                                 const std::string & pwd,
                                 CProcessReport* pProcessReport,
                                 const bool & deleteOldData)
{
  CCopasiMessage::clearDeque();

  std::string Line;
  in >> Line;

  if (!Line.compare(0, 8, "Version="))
    {
      in.seekg(0, std::ios_base::beg);

      CReadConfig inbuf(in);

      if (inbuf.getVersion() >= "4")
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         "Can't handle Gepasi Files with Version>=4.");
          return false;
        }

      newModel(NULL, deleteOldData);
      mData.mFileType = Gepasi;

      if (mData.pModel->load(inbuf))
        {
          popData();
          return false;
        }

      static_cast<CTrajectoryTask *>((*mData.pTaskList)["Time-Course"])->load(inbuf);

      static_cast<CSteadyStateTask *>((*mData.pTaskList)["Steady-State"])->load(inbuf);
    }
  else if (!Line.find("<?xml") != std::string::npos)
    {
      in.seekg(0, std::ios_base::beg);
      pushData();
      mData.mFileType = CopasiML;

      CCopasiXML XML;
      XML.setFunctionList(&CCopasiRootContainer::getFunctionList()->loadedFunctions());
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
  else
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCXML + 13);
      return false;
    }

  commonAfterLoad(pProcessReport, deleteOldData);

  return true;
}

bool CCopasiDataModel::loadModel(const std::string & fileName,
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

  std::ifstream File(CLocaleString::fromUtf8(FileName).c_str());

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
      case CopasiML:
        mData.mSaveFileName = CDirEntry::normalize(FileName);
        // we have to store the reference directory
        mData.mReferenceDir = CDirEntry::dirName(mData.mSaveFileName);
        break;

      case Gepasi:
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
    }

  return true;
}

bool CCopasiDataModel::saveModel(const std::string & fileName, CProcessReport* pProcessReport,
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
    }

  catch (...)
    {
      return false;
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

bool CCopasiDataModel::autoSave()
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

bool CCopasiDataModel::newModel(CProcessReport* pProcessReport,
                                const bool & deleteOldData)
{
  //deal with the CModel
  pushData();

  commonAfterLoad(pProcessReport, deleteOldData);

  return true;
}

bool CCopasiDataModel::importSBMLFromString(const std::string& sbmlDocumentText,
    CProcessReport* pImportHandler,
    const bool & deleteOldData)
{
  pushData();

  CCopasiMessage::clearDeque();

  SBMLImporter importer;
  // Right now we always import the COPASI MIRIAM annotation if it is there.
  // Later this will be settable by the user in the preferences dialog
  importer.setImportCOPASIMIRIAM(true);
  importer.setImportHandler(pImportHandler);
  //mCopasi2SBMLMap.clear();
  CModel* pModel = NULL;

  SBMLDocument * pSBMLDocument = NULL;
  std::map<CCopasiObject*, SBase*> Copasi2SBMLMap;

  CListOfLayouts * pLol = NULL; //

  try
    {
      pModel = importer.parseSBML(sbmlDocumentText, CCopasiRootContainer::getFunctionList(),
                                  pSBMLDocument, Copasi2SBMLMap, pLol, this);
    }

  catch (CCopasiException & except)
    {
      importer.restoreFunctionDB();
      importer.deleteCopasiModel();
      popData();

      throw except;
    }

  if (pModel == NULL)
    {
      importer.restoreFunctionDB();
      importer.deleteCopasiModel();
      popData();

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
  mData.mFileType = SBML;

  commonAfterLoad(pImportHandler, deleteOldData);

  return true;
}

bool CCopasiDataModel::importSBML(const std::string & fileName,
                                  CProcessReport* pImportHandler,
                                  const bool & deleteOldData)
{
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
  std::map<CCopasiObject*, SBase*> Copasi2SBMLMap;

  CListOfLayouts * pLol = NULL;

  pushData();

  try
    {
      pModel = importer.readSBML(FileName, CCopasiRootContainer::getFunctionList(),
                                 pSBMLDocument, Copasi2SBMLMap, pLol, this);
    }

  catch (CCopasiException & except)
    {
      importer.restoreFunctionDB();
      importer.deleteCopasiModel();
      popData();

      throw except;
    }

  if (pModel == NULL)
    {
      importer.restoreFunctionDB();
      importer.deleteCopasiModel();
      popData();

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
  mData.mFileType = SBML;

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

  return true;
}

std::string CCopasiDataModel::exportSBMLToString(CProcessReport* /*pExportHandler*/, int sbmlLevel, int sbmlVersion)
{
  CCopasiMessage::clearDeque();
  SBMLDocument* pOrigSBMLDocument = NULL;

#if LIBSBML_VERSION >= 40100

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

#endif // LIBSBML_VERSION

  CSBMLExporter exporter;
  // Per default export COPASIs MIRIAM annotation.
  // This should eventually be determined by a setting in the preferences
  // dialog.
  exporter.setExportCOPASIMIRIAM(true);
  std::string str = exporter.exportModelToString(*this, sbmlLevel, sbmlVersion);

  // only get the new model if it is not a Level 1 model
  // During export to Level 1 the function definitions have been deleted and therefore
  // all information assiociated with the function definitions will be gone if the user exports
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
      std::map<const CCopasiObject*, SBase*>::const_iterator it = exporter.getCOPASI2SBMLMap().begin();
      std::map<const CCopasiObject*, SBase*>::const_iterator endit = exporter.getCOPASI2SBMLMap().end();

      while (it != endit)
        {
          mData.mCopasi2SBMLMap.insert(std::pair<CCopasiObject*, SBase*>(const_cast<CCopasiObject*>(it->first), it->second));
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

bool CCopasiDataModel::exportSBML(const std::string & fileName, bool overwriteFile, int sbmlLevel, int sbmlVersion, bool /*exportIncomplete*/, bool exportCOPASIMIRIAM, CProcessReport* pExportHandler)
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

  try
    {
      if (!mData.pModel->compileIfNecessary(pExportHandler))
        return false;
    }

  catch (...)
    {
      return false;
    }

  CSBMLExporter exporter;
  exporter.setExportCOPASIMIRIAM(exportCOPASIMIRIAM);
  SBMLDocument* pOrigSBMLDocument = NULL;

#if LIBSBML_VERSION >= 40100

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

#endif // LIBSBML_VERSION

  //exporter.setExportHandler(pExportHandler);
  if (!exporter.exportModel(*this, FileName, sbmlLevel, sbmlVersion, overwriteFile)) return false;

  // only get the new model if it is not a Level 1 model
  // During export to Level 1 the function definitions have been deleted and therefore
  // all information assiociated with the function definitions will be gone if the user exports
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
      std::map<const CCopasiObject*, SBase*>::const_iterator it = exporter.getCOPASI2SBMLMap().begin();
      std::map<const CCopasiObject*, SBase*>::const_iterator endit = exporter.getCOPASI2SBMLMap().end();

      while (it != endit)
        {
          mData.mCopasi2SBMLMap.insert(std::pair<CCopasiObject*, SBase*>(const_cast<CCopasiObject*>(it->first), it->second));
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

std::string CCopasiDataModel::exportMathModelToString(CProcessReport* pProcessReport, const std::string & filter)
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

  CCopasiVector< CModelValue >::const_iterator it = mData.pModel->getModelValues().begin();
  CCopasiVector< CModelValue >::const_iterator end = mData.pModel->getModelValues().end();

  for (; it != end; ++it)
    if ((*it)->isUsed()) break;

  if (it != end)
    CCopasiMessage(CCopasiMessage::WARNING, MCODEExporter + 2);

  std::ostringstream os;

  if (!pExporter->exportToStream(this, os))
    {
      return "";
    }

  return os.str();
}

bool CCopasiDataModel::exportMathModel(const std::string & fileName, CProcessReport* pProcessReport,
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

  CCopasiVector< CModelValue >::const_iterator it = mData.pModel->getModelValues().begin();
  CCopasiVector< CModelValue >::const_iterator end = mData.pModel->getModelValues().end();

  for (; it != end; ++it)
    if ((*it)->isUsed()) break;

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

void CCopasiDataModel::deleteOldData()
{
  pdelete(mOldData.pModel);
  pdelete(mOldData.pTaskList);
  pdelete(mOldData.pReportDefinitionList);
  pdelete(mOldData.pPlotDefinitionList);
  pdelete(mOldData.pListOfLayouts);
  pdelete(mOldData.pGUI);
  pdelete(mOldData.pCurrentSBMLDocument);
}

const CModel * CCopasiDataModel::getModel() const
{return mData.pModel;}

CModel * CCopasiDataModel::getModel()
{
  if (mData.isValid())
    return mData.pModel;

  return mOldData.pModel;
}

CCopasiVectorN< CCopasiTask > * CCopasiDataModel::getTaskList()
{
  if (mData.isValid())
    return mData.pTaskList;

  return mOldData.pTaskList;
}

const CCopasiVectorN< CCopasiTask > * CCopasiDataModel::getTaskList() const
{
  if (mData.isValid())
    return mData.pTaskList;

  return mOldData.pTaskList;
}

CCopasiTask * CCopasiDataModel::addTask(const CCopasiTask::Type & taskType)
{
  CCopasiTask * pTask = NULL;

  switch (taskType)
    {
      case CCopasiTask::steadyState:
        pTask = new CSteadyStateTask(mData.pTaskList);
        break;

      case CCopasiTask::timeCourse:
        pTask = new CTrajectoryTask(mData.pTaskList);
        break;

      case CCopasiTask::scan:
        pTask = new CScanTask(mData.pTaskList);
        break;

      case CCopasiTask::fluxMode:
        pTask = new CEFMTask(mData.pTaskList);
        break;

      case CCopasiTask::optimization:
        pTask = new COptTask(taskType, mData.pTaskList);
        break;

      case CCopasiTask::parameterFitting:
        pTask = new CFitTask(taskType, mData.pTaskList);
        break;

      case CCopasiTask::mca:
        pTask = new CMCATask(mData.pTaskList);
        static_cast< CMCAProblem * >(pTask->getProblem())->setSteadyStateRequested(true);
        break;

      case CCopasiTask::lna:
        pTask = new CLNATask(mData.pTaskList);
        static_cast< CLNAProblem * >(pTask->getProblem())->setSteadyStateRequested(true);
        break;

      case CCopasiTask::lyap:
        pTask = new CLyapTask(mData.pTaskList);
        break;

      case CCopasiTask::sens:
        pTask = new CSensTask(mData.pTaskList);
        break;

      case CCopasiTask::tssAnalysis:
        pTask = new CTSSATask(mData.pTaskList);
        break;

      case CCopasiTask::moieties:
        pTask = new CMoietiesTask(taskType, mData.pTaskList);
        break;

#ifdef COPASI_NONLIN_DYN

      case CCopasiTask::crosssection:
        pTask = new CCrossSectionTask(mData.pTaskList);
        break;
#endif

      default:
        return pTask;
    }

  pTask->getProblem()->setModel(mData.pModel);
  mData.pTaskList->add(pTask);

  return pTask;
}

bool CCopasiDataModel::addDefaultTasks()
{
  size_t i;

  for (i = 0; CCopasiTask::TypeName[i] != ""; i++)
    if (mData.pTaskList->getIndex(CCopasiTask::TypeName[i]) == C_INVALID_INDEX)
      addTask((CCopasiTask::Type) i);

  return true;
}

bool CCopasiDataModel::appendDependentTasks(std::set< const CCopasiObject * > candidates,
    std::set< const CCopasiObject * > & dependentTasks) const
{
  size_t Size = dependentTasks.size();

  std::set< const CCopasiObject * >::const_iterator it = candidates.begin();
  std::set< const CCopasiObject * >::const_iterator end = candidates.end();

  CCopasiVectorN< CCopasiTask >::const_iterator itTask = mData.pTaskList->begin();
  CCopasiVectorN< CCopasiTask >::const_iterator endTask = mData.pTaskList->end();

  for (; it != end; ++it)
    {
      const CReportDefinition * pReportDefinition = dynamic_cast< const CReportDefinition * >(*it);

      if (pReportDefinition == NULL)
        continue;

      itTask = mData.pTaskList->begin();

      for (; itTask != endTask; ++itTask)
        {
          if ((*itTask)->getReport().getReportDefinition() == pReportDefinition)
            {
              dependentTasks.insert(*itTask);
            }
        }
    }

  return Size < dependentTasks.size();
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
        pReport->getFooterAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Steady-State]"));
        break;

      case CCopasiTask::timeCourse:
        // No default report available.
        break;

      case CCopasiTask::scan:
        // No default report available.
        break;

      case CCopasiTask::fluxMode:
        pReport = new CReportDefinition(CCopasiTask::TypeName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setSeparator(CCopasiReportSeparator("\t"));
        pReport->getFooterAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Elementary Flux Modes],Object=Result"));
        break;

      case CCopasiTask::optimization:
        pReport = new CReportDefinition(CCopasiTask::TypeName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator(CCopasiReportSeparator("\t"));

        // Header
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Optimization],Object=Description"));
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("String=\\[Function Evaluations\\]"));
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("Separator=\t"));
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("String=\\[Best Value\\]"));
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("Separator=\t"));
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("String=\\[Best Parameters\\]"));

        // Body
        pReport->getBodyAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations"));
        pReport->getBodyAddr()->push_back(CCopasiObjectName("Separator=\t"));
        pReport->getBodyAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Value"));
        pReport->getBodyAddr()->push_back(CCopasiObjectName("Separator=\t"));
        pReport->getBodyAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Parameters"));

        // Footer
        pReport->getFooterAddr()->push_back(CCopasiObjectName("String=\n"));
        pReport->getFooterAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Optimization],Object=Result"));
        break;

        //**************************************************************************
      case CCopasiTask::parameterFitting:
        pReport = new CReportDefinition(CCopasiTask::TypeName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator(CCopasiReportSeparator("\t"));

        // Header
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Parameter Estimation],Object=Description"));
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("String=\\[Function Evaluations\\]"));
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("Separator=\t"));
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("String=\\[Best Value\\]"));
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("Separator=\t"));
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("String=\\[Best Parameters\\]"));

        // Body
        pReport->getBodyAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Function Evaluations"));
        pReport->getBodyAddr()->push_back(CCopasiObjectName("Separator=\t"));
        pReport->getBodyAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Best Value"));
        pReport->getBodyAddr()->push_back(CCopasiObjectName("Separator=\t"));
        pReport->getBodyAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Parameter Estimation],Problem=Parameter Estimation,Reference=Best Parameters"));

        // Footer
        pReport->getFooterAddr()->push_back(CCopasiObjectName("String=\n"));
        pReport->getFooterAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Parameter Estimation],Object=Result"));
        break;

        //**************************************************************************
      case CCopasiTask::lyap:
        pReport = new CReportDefinition(CCopasiTask::TypeName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator(CCopasiReportSeparator("\t"));

        // Header
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Description"));

        // Footer
        pReport->getFooterAddr()->push_back(CCopasiObjectName("String=\n"));
        pReport->getFooterAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Lyapunov Exponents],Object=Result"));
        break;

        //**************************************************************************
      case CCopasiTask::mca:
        pReport = new CReportDefinition(CCopasiTask::TypeName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator(CCopasiReportSeparator("\t"));

        // Header
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Description"));

        // Footer
        pReport->getFooterAddr()->push_back(CCopasiObjectName("String=\n"));
        pReport->getFooterAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Metabolic Control Analysis],Object=Result"));
        break;

        //**************************************************************************
      case CCopasiTask::lna:
        pReport = new CReportDefinition(CCopasiTask::TypeName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator(CCopasiReportSeparator("\t"));

        // Header
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Linear Noise Approximation],Object=Description"));

        // Footer
        pReport->getFooterAddr()->push_back(CCopasiObjectName("String=\n"));
        pReport->getFooterAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Linear Noise Approximation],Object=Result"));
        break;

        //**************************************************************************
      case CCopasiTask::sens:
        pReport = new CReportDefinition(CCopasiTask::TypeName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator(CCopasiReportSeparator("\t"));

        // Header
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Sensitivities],Object=Description"));

        // Footer
        pReport->getFooterAddr()->push_back(CCopasiObjectName("String=\n"));
        pReport->getFooterAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Sensitivities],Object=Result"));
        break;

        //**************************************************************************
      case CCopasiTask::tssAnalysis:
        pReport = new CReportDefinition(CCopasiTask::TypeName[taskType]);
        pReport->setTaskType(taskType);
        pReport->setComment("Automatically generated report.");
        pReport->setIsTable(false);
        pReport->setTitle(false);
        pReport->setSeparator(CCopasiReportSeparator("\t"));

        // Header
        pReport->getHeaderAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Time Scale Separation Analysis],Object=Description"));

        // Footer
        pReport->getFooterAddr()->push_back(CCopasiObjectName("String=\n"));
        pReport->getFooterAddr()->push_back(CCopasiObjectName("CN=Root,Vector=TaskList[Time Scale Separation Analysis],Object=Result"));
        break;

      default:
        return pReport;
    }

  if (pReport) mData.pReportDefinitionList->add(pReport, true);

  return pReport;
}

bool CCopasiDataModel::addDefaultReports()
{
  size_t i;

  for (i = 0; CCopasiTask::TypeName[i] != ""; i++)
    {
      //try to create the report if it doesn't exist
      if (mData.pReportDefinitionList->getIndex(CCopasiTask::TypeName[i]) == C_INVALID_INDEX)
        {
          addReport((CCopasiTask::Type) i);
        }

      //see if the report exists now
      CReportDefinition* pReportDef = NULL;

      if (mData.pReportDefinitionList->getIndex(CCopasiTask::TypeName[i]) != C_INVALID_INDEX)
        pReportDef = (*mData.pReportDefinitionList)[CCopasiTask::TypeName[i]];

      //see if the task exists
      CCopasiTask* pTask = NULL;

      if (mData.pTaskList->getIndex(CCopasiTask::TypeName[i]) != C_INVALID_INDEX)
        pTask = (*mData.pTaskList)[CCopasiTask::TypeName[i]];

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

const CReportDefinitionVector * CCopasiDataModel::getReportDefinitionList() const
{
  if (mData.isValid())
    return mData.pReportDefinitionList;

  return mOldData.pReportDefinitionList;
}

CReportDefinitionVector * CCopasiDataModel::getReportDefinitionList()
{
  if (mData.isValid())
    return mData.pReportDefinitionList;

  return mOldData.pReportDefinitionList;
}

const COutputDefinitionVector * CCopasiDataModel::getPlotDefinitionList() const
{
  if (mData.isValid())
    return mData.pPlotDefinitionList;

  return mOldData.pPlotDefinitionList;
}

COutputDefinitionVector * CCopasiDataModel::getPlotDefinitionList()
{
  if (mData.isValid())
    return mData.pPlotDefinitionList;

  return mOldData.pPlotDefinitionList;
}

const CListOfLayouts * CCopasiDataModel::getListOfLayouts() const
{
  if (mData.isValid())
    return mData.pListOfLayouts;

  return mOldData.pListOfLayouts;
}

CListOfLayouts * CCopasiDataModel::getListOfLayouts()
{
  if (mData.isValid())
    return mData.pListOfLayouts;

  return mOldData.pListOfLayouts;
}

SCopasiXMLGUI * CCopasiDataModel::getGUI()
{
  if (mData.isValid())
    return mData.pGUI;

  return mOldData.pGUI;
}

const std::string & CCopasiDataModel::getFileName() const
{return mData.mSaveFileName;}

bool CCopasiDataModel::isChanged() const
{return mData.mChanged;}

void CCopasiDataModel::changed(const bool & changed)
{
  mData.mChanged = changed;
  mData.mAutoSaveNeeded = changed;
}

SBMLDocument* CCopasiDataModel::getCurrentSBMLDocument()
{
  return mData.pCurrentSBMLDocument;
}

bool CCopasiDataModel::setSBMLFileName(const std::string & fileName)
{
  mData.mSBMLFileName = CDirEntry::normalize(fileName);

  if (CDirEntry::isRelativePath(mData.mSBMLFileName) &&
      !CDirEntry::makePathAbsolute(mData.mSBMLFileName, mData.mSaveFileName))
    mData.mSBMLFileName = CDirEntry::fileName(mData.mSBMLFileName);

  return true;
}

const std::string & CCopasiDataModel::getSBMLFileName() const
{return mData.mSBMLFileName;}

std::map<CCopasiObject*, SBase*>& CCopasiDataModel::getCopasi2SBMLMap()
{
  return mData.mCopasi2SBMLMap;
}

void CCopasiDataModel::removeSBMLIdFromFunctions()
{
  CFunctionDB* pFunDB = CCopasiRootContainer::getFunctionList();
  size_t i, iMax = pFunDB->loadedFunctions().size();

  for (i = 0; i < iMax; ++i)
    {
      pFunDB->loadedFunctions()[i]->setSBMLId("");
    }
}

bool CCopasiDataModel::removeLayout(const std::string & key)
{
  CLayout *pLayout =
    dynamic_cast< CLayout * >(CCopasiRootContainer::getKeyFactory()->get(key));

  if (!pLayout)
    return false;

  //Check if Layout with that name exists
  size_t index =
    mData.pListOfLayouts->CCopasiVector< CLayout >::getIndex(pLayout);

  if (index == C_INVALID_INDEX)
    return false;

  mData.pListOfLayouts->CCopasiVector< CLayout >::remove(index);

  return true;
}

CObjectInterface * CCopasiDataModel::ObjectFromCN(const std::vector< CCopasiContainer * > & listOfContainer,
    const CCopasiObjectName & objName) const
{
  const CObjectInterface * pObject = NULL;
  const CCopasiContainer* pContainer;
  CCopasiObjectName ContainerName;
  size_t containerIndex;
  std::string::size_type pos;

  //favor to search the list of container first
  for (containerIndex = 0;
       containerIndex < listOfContainer.size() && !pObject;
       containerIndex++)
    {
      pContainer = listOfContainer[containerIndex];
      ContainerName = pContainer->getCN();

      while (ContainerName.getRemainder() != "")
        {
          ContainerName = ContainerName.getRemainder();
        }

      if ((pos = objName.find(ContainerName)) == std::string::npos)
        continue;

      if (pos + ContainerName.length() == objName.length())
        pObject = pContainer;
      else
        pObject = pContainer->getObject(objName.substr(pos + ContainerName.length() + 1));
    }

  // If we have not found the object in the context we search the whole data model.
  if (pObject == NULL)
    {
      pObject = getObject(objName);
    }

  // if still not found search the function database in the root container
  if (!pObject)
    pObject = CCopasiRootContainer::getFunctionList()->getObject(objName);

  return const_cast< CObjectInterface * >(pObject);
}

CCopasiObject * CCopasiDataModel::ObjectFromName(const std::vector< CCopasiContainer * > & listOfContainer,
    const CCopasiObjectName & objName) const
{
  // TODO CRITICAL This does not work for math as object ObjectFromCN only returns a CObjectInterface.
  return static_cast< CCopasiObject * >(ObjectFromCN(listOfContainer, objName));
}

CCopasiObject * CCopasiDataModel::getDataObject(const CCopasiObjectName & CN) const
{
  return dynamic_cast< CCopasiObject *>(const_cast< CObjectInterface * >(getObject(CN)));
}

const std::string& CCopasiDataModel::getReferenceDirectory() const
{
  return mData.mReferenceDir;
}

CCopasiDataModel::CData::CData(const bool & withGUI):
  pModel(NULL),
  pTaskList(NULL),
  pReportDefinitionList(NULL),
  pPlotDefinitionList(NULL),
  pListOfLayouts(NULL),
  pGUI(NULL),
  pCurrentSBMLDocument(NULL),
  mWithGUI(withGUI),
  mSaveFileName(),
  mFileType(unset),
  mChanged(false),
  mAutoSaveNeeded(false),
  mSBMLFileName(""),
  mReferenceDir("")
{}

CCopasiDataModel::CData::CData(const CData & src):
  pModel(src.pModel),
  pTaskList(src.pTaskList),
  pReportDefinitionList(src.pReportDefinitionList),
  pPlotDefinitionList(src.pPlotDefinitionList),
  pListOfLayouts(src.pListOfLayouts),
  pGUI(src.pGUI),
  pCurrentSBMLDocument(src.pCurrentSBMLDocument),
  mWithGUI(src.mWithGUI),
  mSaveFileName(src.mSaveFileName),
  mFileType(src.mFileType),
  mChanged(src.mChanged),
  mAutoSaveNeeded(src.mAutoSaveNeeded),
  mSBMLFileName(src.mSBMLFileName),
  mReferenceDir(src.mReferenceDir)
{}

CCopasiDataModel::CData::~CData()
{}

CCopasiDataModel::CData & CCopasiDataModel::CData::operator = (const CData & rhs)
{
  pModel = rhs.pModel;
  pTaskList = rhs.pTaskList;
  pReportDefinitionList = rhs.pReportDefinitionList;
  pPlotDefinitionList = rhs.pPlotDefinitionList;
  pListOfLayouts = rhs.pListOfLayouts;
  pGUI = rhs.pGUI;
  pCurrentSBMLDocument = rhs.pCurrentSBMLDocument;
  mWithGUI = rhs.mWithGUI,
  mSaveFileName = rhs.mSaveFileName;
  mFileType = rhs.mFileType;
  mChanged = rhs.mChanged;
  mAutoSaveNeeded = rhs.mAutoSaveNeeded;
  mSBMLFileName = rhs.mSBMLFileName;
  mReferenceDir = rhs.mReferenceDir;

  return *this;
}

bool CCopasiDataModel::CData::isValid() const
{
  return (pModel != NULL &&
          pTaskList != NULL &&
          pReportDefinitionList != NULL &&
          pPlotDefinitionList != NULL &&
          pListOfLayouts != NULL &&
          (pGUI != NULL || mWithGUI == false));
}

void CCopasiDataModel::pushData()
{
  // make sure the old data has been deleted.
  assert(mOldData.pModel == NULL &&
         mOldData.pTaskList == NULL &&
         mOldData.pReportDefinitionList == NULL &&
         mOldData.pPlotDefinitionList == NULL &&
         mOldData.pListOfLayouts == NULL &&
         mOldData.pGUI == NULL &&
         mOldData.pCurrentSBMLDocument == NULL);

  mOldData = mData;
  mData = CData(mData.mWithGUI);
}

void CCopasiDataModel::popData()
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
  mOldData = CData(mOldData.mWithGUI);
}

void CCopasiDataModel::commonAfterLoad(CProcessReport* pProcessReport,
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
      mData.pTaskList = new CCopasiVectorN< CCopasiTask >("TaskList", this);
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

  // We need to initialize all the task so that results are available

  // We suppress all errors and warnings
  size_t Size = CCopasiMessage::size();

  CCopasiVectorN< CCopasiTask >::iterator it = mData.pTaskList->begin();
  CCopasiVectorN< CCopasiTask >::iterator end = mData.pTaskList->end();

  for (; it != end; ++it)
    {
      try
        {
          (*it)->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
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
      mData.pModel->updateInitialValues();
#ifdef COPASI_PARAMETER_SETS
      mData.pModel->applyActiveParameterSet();
#endif // COPASI_PARAMTER_SETS
    }

  changed(false);

  if (deleteOldData)
    {
      CCopasiDataModel::deleteOldData();
    }
}
