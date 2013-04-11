// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
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

#ifndef COPASI_CCopasiDataModel
#define COPASI_CCopasiDataModel

#include <map>

#include "utilities/COutputHandler.h"
#include "utilities/CCopasiTask.h"

class CModel;
class CReportTemplateVector;
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

#include "copasi/report/CRenameHandler.h"
class CCopasiDataModel;

class CDataModelRenameHandler : public CRenameHandler
{
public:
  CDataModelRenameHandler();

  virtual ~CDataModelRenameHandler() {};

  virtual bool handle(const std::string & oldCN, const std::string & newCN) const;
};

//******************************************************************************

class CCopasiDataModel: public CCopasiContainer, public COutputHandler
{
  enum FileType
  {
    CopasiML = 0,
    SBML,
    Gepasi,
    unset
  };

private:
  class CData
  {
  public:

    CData(const bool & withGUI = false);

    CData(const CData & src);

    ~CData();

    CData & operator = (const CData & rhs);
    bool isValid() const;

    CModel * pModel;
    CCopasiVectorN< CCopasiTask > * pTaskList;
    CReportTemplateVector * pReportTemplateList;
    COutputDefinitionVector * pPlotDefinitionList;
    CListOfLayouts * pListOfLayouts;
    SCopasiXMLGUI * pGUI;
    SBMLDocument* pCurrentSBMLDocument;

    bool mWithGUI;

    std::string mSaveFileName;
    FileType mFileType;
    bool mChanged;
    bool mAutoSaveNeeded;

    /**
     * The name of the referenced SBML file
     */
    std::string mSBMLFileName;

    /**
     * This will map each COPASI object to the
     * corresponding SBML object if the current model
     * was created by an SBML import.
     */
    std::map<CCopasiObject*, SBase*> mCopasi2SBMLMap;

    // if we want to display images in the render extension,
    // those images can be png or jpg files with a relative path name.
    // If the path is relative, it is considered to be relative to the
    // path of the filename it came from.
    // Because of this, I need to know the reference directory where
    // the render information came from because it can either come from
    // an imported SBML file or from a loaded cps file.
    std::string mReferenceDir;
  };

  // Operations
public:
  CCopasiDataModel(const bool withGUI = false);

  CCopasiDataModel(const std::string & name,
                   const CCopasiContainer * pParent = NULL,
                   const std::string & type = "CN",
                   bool withGUI = false);

  virtual ~CCopasiDataModel();

  bool loadModel(std::istream & in,
                 const std::string & pwd,
                 CProcessReport* pProcessReport,
                 const bool & deleteOldData = true);

  bool loadModel(const std::string & fileName,
                 CProcessReport* pProcessReport,
                 const bool & deleteOldData = true);

  bool saveModel(const std::string & fileName,
                 CProcessReport* pProcessReport,
                 bool overwriteFile = false,
                 const bool & autoSave = false);

  bool autoSave();

  bool newModel(CProcessReport* pProcessReport,
                const bool & deleteOldData);

  bool importSBMLFromString(const std::string & sbmlDocumentText,
                            CProcessReport* pImportHandler = NULL,
                            const bool & deleteOldData = true);

  bool importSBML(const std::string & fileName,
                  CProcessReport* pImportHandler = NULL,
                  const bool & deleteOldData = true);

  std::string exportSBMLToString(CProcessReport* pExportHandler, int sbmlLevel, int sbmlVersion);
  bool exportSBML(const std::string & fileName, bool overwriteFile = false, int sbmlLevel = 2, int sbmlVersion = 1, bool exportIncomplete = false, bool exportCOPASIMIRIAM = true, CProcessReport* pExportHandler = NULL);

  std::string exportMathModelToString(CProcessReport* pProcessReport, const std::string & filter);
  bool exportMathModel(const std::string & fileName, CProcessReport* pProcessReport,
                       const std::string & filter, bool overwriteFile = false);

  void deleteOldData();

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

  const CReportTemplateVector * getReportTemplateList() const;
  CReportTemplateVector * getReportTemplateList();
  CReportTemplate * addReport(const CCopasiTask::Type & taskType);
  bool addDefaultReports();

  const COutputDefinitionVector * getPlotDefinitionList() const;
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
   * Retrieve the object with the given CN
   * @param const std::vector< CCopasiContainer * > &listOfContainer
   * @param const CCopasiObjectName& objName
   * @return CObjectInterface * pObject
   */
  CObjectInterface * ObjectFromCN(const std::vector< CCopasiContainer * > & listOfContainer,
                                  const CCopasiObjectName & objName) const;

  /**
   * Retrieve the data object with the given CN
   * @param const std::vector< CCopasiContainer * > &listOfContainer
   * @param const CCopasiObjectName& CN
   * @return CCopasiObject * pObject
   */
  CCopasiObject * ObjectFromName(const std::vector< CCopasiContainer * > & listOfContainer,
                                 const CCopasiObjectName & CN) const;

  /**
   * Retrieve the data object with the given CN
   * @param const CCopasiObjectName & CN
   * @return CCopasiObject * pObject
   */
  CCopasiObject * getDataObject(const CCopasiObjectName & CN) const;

  const std::string& getReferenceDirectory() const;

protected:
  void pushData();
  void popData();
  void commonAfterLoad(CProcessReport* pProcessReport,
                       const bool & deleteOldData);

  // Attributes
protected:
  CData mData;
  CData mOldData;
  CDataModelRenameHandler mRenameHandler;

public:
  /**
   *  This is a hack at the moment to be able to read Gepasi model files
   */
  CCopasiVectorS < CMetabOld > * pOldMetabolites;

protected:
  void removeSBMLIdFromFunctions();
};

#endif // COPASI_CCopasiDataModel
