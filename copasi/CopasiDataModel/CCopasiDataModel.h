// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiDataModel/CCopasiDataModel.h,v $
//   $Revision: 1.49.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/09/30 17:02:32 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CCopasiDataModel
#define COPASI_CCopasiDataModel

#include <map>

#include "utilities/COutputHandler.h"
#include "utilities/CCopasiTask.h"

class CModel;
class CReportDefinitionVector;
class COutputDefinitionVector;
class CFunctionDB;
class CFunction;
class SCopasiXMLGUI;
class SBMLDocument;
class SBase;
class CProcessReport;
class CConfigurationFile;
class SBMLIncompatibility;
class CListOfLayouts;

// :TODO: remove
class CMetabOld;

template <class CType> class CCopasiVectorS;
template <class CType> class CCopasiVectorN;

//******************************************************************************

#include "report/CRenameHandler.h"
class CCopasiDataModel;

class CDataModelRenameHandler : public CRenameHandler
{
public:
  CDataModelRenameHandler(CCopasiDataModel* dm);

  virtual ~CDataModelRenameHandler() {};

  virtual bool handle(const std::string & oldCN, const std::string & newCN) const;

private:
  CCopasiDataModel * mpDataModel;
};

//******************************************************************************

class CCopasiDataModel: public CCopasiContainer, public COutputHandler
{
  // Operations
public:
  CCopasiDataModel(const bool withGUI = false);

  CCopasiDataModel(const std::string & name,
                   const CCopasiContainer * pParent = NULL,
                   const std::string & type = "CN",
                   bool withGUI = false);

  ~CCopasiDataModel();

  bool loadModel(const std::string & fileName, CProcessReport* pProcessReport);
  bool saveModel(const std::string & fileName, CProcessReport* pProcessReport,
                 bool overwriteFile = false,
                 const bool & autoSave = false);
  bool autoSave();

  bool newModel(CModel * pModel, CProcessReport* pProcessReport, CListOfLayouts * pLol = NULL);

  bool importSBMLFromString(const std::string & sbmlDocumentText, CProcessReport* pImportHandler = NULL);
  bool importSBML(const std::string & fileName, CProcessReport* pImportHandler = NULL);
  std::string exportSBMLToString(CProcessReport* pExportHandler, int sbmlLevel, int sbmlVersion);
  bool exportSBML(const std::string & fileName, bool overwriteFile = false, int sbmlLevel = 2, int sbmlVersion = 1, bool exportIncomplete = false, bool exportCOPASIMIRIAM = true, CProcessReport* pExportHandler = NULL);
  bool exportMathModel(const std::string & fileName, CProcessReport* pProcessReport,
                       const std::string & filter, bool overwriteFile = false);

  CModel * getModel();
  const CModel * getModel() const;
  CCopasiVectorN< CCopasiTask > * getTaskList();
  const CCopasiVectorN< CCopasiTask > * getTaskList() const;
  CCopasiTask * addTask(const CCopasiTask::Type & taskType);
  bool addDefaultTasks();
  /**
   * Appends pointers to tasks, which are dependent on any of the candidates
   * to the list dependentTasks.
   * @param std::set< const CCopasiObject * > candidates
   * @param std::set< const CCopasiObject * > & dependentTasks
   * @return bool functionsAppended
   */
  bool appendDependentTasks(std::set< const CCopasiObject * > candidates,
                            std::set< const CCopasiObject * > & dependentTasks) const;

  CReportDefinitionVector * getReportDefinitionList();
  CReportDefinition * addReport(const CCopasiTask::Type & taskType);
  bool addDefaultReports();

  COutputDefinitionVector * getPlotDefinitionList();

  CListOfLayouts * getListOfLayouts();
  const CListOfLayouts * getListOfLayouts() const;
  bool removeLayout(const std::string& key);

  SCopasiXMLGUI * getGUI();
  const std::string & getFileName() const;

  bool isChanged() const;
  void changed(const bool & changed = true);

  SBMLDocument* getCurrentSBMLDocument();
  bool setSBMLFileName(const std::string & fileName);
  const std::string & getSBMLFileName() const;

  std::map<CCopasiObject*, SBase*>& getCopasi2SBMLMap();

  /**
   * @param const std::vector< CCopasiContainer * > &listOfContainer
   * @param const CCopasiObjectName& objName
   * @return CCopasiObject * pObject
   */
  CCopasiObject * ObjectFromName(const std::vector< CCopasiContainer * > & listOfContainer,
                                 const CCopasiObjectName & objName);

  /**
   * @param const std::vector< CCopasiContainer * > &listOfContainer
   * @param const CCopasiObjectName& objName
   * @return CCopasiObject * pObject
   */
  const CCopasiObject * ObjectFromName(const std::vector< CCopasiContainer * > & listOfContainer,
                                       const CCopasiObjectName & objName) const;

#ifdef USE_CRENDER_EXTENSION
  const std::string& getReferenceDirectory() const;
#endif // USE_CRENDER_EXTENSION

  // Attributes
protected:
  CModel * mpModel;
  CCopasiVectorN< CCopasiTask > * mpTaskList;
  CReportDefinitionVector * mpReportDefinitionList;

  COutputDefinitionVector * mpPlotDefinitionList;

  CListOfLayouts * mpListOfLayouts;

  bool mWithGUI;
  SCopasiXMLGUI * mpGUI;

  std::string mSaveFileName;
  bool mChanged;
  bool mAutoSaveNeeded;
  CDataModelRenameHandler mRenameHandler;

  /**
   * This will hold the SBMLDocument that was imported
   * to create the current Model.
   */
  SBMLDocument* mpCurrentSBMLDocument;

  /**
   * The name of the referenced SBML file
   */
  std::string mSBMLFileName;

  /**
   * This will map each Copasi object to the
   * corresponding SBML object if the current model
   * was created by an SBML import.
   */
  std::map<CCopasiObject*, SBase*> mCopasi2SBMLMap;

#ifdef USE_CRENDER_EXTENSION
  // if we want to display images in the render extension,
  // those images can be png or jpg files with a relative path name.
  // If the path is relative, it is considered to be relative to the
  // path of the filename it came from.
  // Because of this, I need to know the reference directory where
  // the render information came from because it can either come from
  // an imported SBML file or from a loaded cps file.
  std::string mReferenceDir;
#endif // USE_CRENDER_EXTENSION

public:
  /**
   *  This is a hack at the moment to be able to read Gepasi model files
   */
  CCopasiVectorS < CMetabOld > * pOldMetabolites;

protected:
  void removeSBMLIdFromFunctions();
};

#endif // COPASI_CCopasiDataModel
