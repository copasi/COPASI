// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"
#include "utilities/COutputHandler.h"
#include "utilities/CCopasiTask.h"

class CModel;
class CReportDefinitionVector;
class COutputDefinitionVector;
class CFunctionDB;
class CFunction;
class SCopasiXMLGUI;
LIBSBML_CPP_NAMESPACE_BEGIN
class SBMLDocument;
class SBase;
LIBSBML_CPP_NAMESPACE_END
class CProcessReport;
class CConfigurationFile;
class SBMLIncompatibility;
class CListOfLayouts;
class CUndoStack;
class CUndoData;

//TODO SEDML
#ifdef COPASI_SEDML
LIBSEDML_CPP_NAMESPACE_BEGIN
class SedBase;
class SedDocument;
LIBSEDML_CPP_NAMESPACE_END
class CPlotItem;
#endif

#ifdef WITH_COMBINE_ARCHIVE
class CombineArchive;
#endif // WITH_COMBINE_ARCHIVE

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

  virtual void handle(const std::string & oldCN, const std::string & newCN) const;

  /**
   * Enable and disable the rename handler
   * @param const bool & enabled
   */
  virtual void setEnabled(const bool & enabled);
  virtual bool isEnabled() const;

private:
  /**
   * Flag whether the rename handler is enable or not
   */
  bool mEnabled;
};

//******************************************************************************

class CCopasiDataModel: public CCopasiContainer, public COutputHandler
{
  enum FileType
  {
    CopasiML = 0,
    SBML,
    SEDML,
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
    CReportDefinitionVector * pReportDefinitionList;
    COutputDefinitionVector * pPlotDefinitionList;
    CListOfLayouts * pListOfLayouts;
    SCopasiXMLGUI * pGUI;
    SBMLDocument* pCurrentSBMLDocument;
    bool mWithGUI;
    CUndoStack * mpUndoStack;
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
    std::map<const CCopasiObject*, SBase*> mCopasi2SBMLMap;

    // if we want to display images in the render extension,
    // those images can be png or jpg files with a relative path name.
    // If the path is relative, it is considered to be relative to the
    // path of the filename it came from.
    // Because of this, I need to know the reference directory where
    // the render information came from because it can either come from
    // an imported SBML file or from a loaded cps file.
    std::string mReferenceDir;

    //TODO SEDML
#ifdef COPASI_SEDML
    SedDocument* pCurrentSEDMLDocument;

    /**
     * This will map each COPASI object to the
     * corresponding SEDML object if the current model
     * was created by an SEDML import.
     */
    std::map<CCopasiObject*, SedBase*> mCopasi2SEDMLMap;

    /**
     * The name of the referenced SEDML file
     */
    std::string mSEDMLFileName;

#endif
  };

  // Operations
public:
  static CCopasiDataModel * create(const ::CData & data);

  CCopasiDataModel(const bool withGUI = false);

  CCopasiDataModel(const std::string & name,
                   const CCopasiContainer * pParent = NO_PARENT,
                   const std::string & type = "CN",
                   bool withGUI = false);

  CCopasiDataModel(const CCopasiDataModel & src,
                   const CCopasiContainer * pParent);

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

  std::string saveModelToString(CProcessReport* pProcessReport = NULL);

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

#ifdef WITH_COMBINE_ARCHIVE
  /**
   * Moves the experimental data referenced in the model to the specified
   * path and update the referenced filenames to match it. Should the folder
   * already have an experimental data file in there with the name, a new
   * name will be chosen.
   *
   * @param path the target directory for the experimental data.
   */
  void copyExperimentalDataTo(const std::string& path);

  bool exportCombineArchive(std::string fileName,
                            bool includeCOPASI = true,
                            bool includeSBML = true,
                            bool includeData = true,
                            bool includeSEDML = false,
                            bool overwriteFile = false,
                            CProcessReport* pProgressReport = NULL);

  /**
   * adds the current COPASI model to the archive with the given
   * target name
   *
   * @param archive the COMBINE archive
   * @param targetName the name and path that the COPASI file should have in the archive
   * @param pProgressReport optional pointer to the progress report
   */
  void addCopasiFileToArchive(CombineArchive *archive,
                              const std::string& targetName = "./copasi/model.cps",
                              CProcessReport * pProgressReport = NULL
                             );

  bool openCombineArchive(const std::string& fileName, CProcessReport* pProgressReport = NULL,
                          const bool & deleteOldData = true);

#endif

  void deleteOldData();

  CModel * getModel();
  const CModel * getModel() const;
  CCopasiVectorN< CCopasiTask > * getTaskList();
  const CCopasiVectorN< CCopasiTask > * getTaskList() const;
  CCopasiTask * addTask(const CTaskEnum::Task & taskType);
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

  const CReportDefinitionVector * getReportDefinitionList() const;
  CReportDefinitionVector * getReportDefinitionList();
  CReportDefinition * addReport(const CTaskEnum::Task & taskType);
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

  std::map<const CCopasiObject*, SBase*>& getCopasi2SBMLMap();

public:
  const std::string& getReferenceDirectory() const;

  //TODO SEDML by JO Dada
#ifdef COPASI_SEDML
  bool importSEDMLFromString(const std::string & sedmlDocumentText,
                             CProcessReport* pImportHandler = NULL,
                             const bool & deleteOldData = true);

  bool importSEDML(const std::string & fileName,
                   CProcessReport* pImportHandler = NULL,
                   const bool & deleteOldData = true);

  /**
   * exports the SED-ML with given level and version to a string. NOTE: the
   * SBML model will not be exported, instead it is assumed to be available
   * at the location provided in modelLocation
   *
   * @param pExportHandler export handler
   * @param sedmlLevel the level to export
   * @param sedmlVersion the version to export
   * @param modelLocation the location where the SBML file has been written,
   *                      defaults to 'model.xml'
   *
   * @return the SED-ML string.
   */
  std::string exportSEDMLToString(CProcessReport* pExportHandler,
                                  int sedmlLevel, int sedmlVersion,
                                  const std::string& modelLocation = "model.xml"
                                 );

  bool exportSEDML(const std::string & fileName, bool overwriteFile = false, int sedmlLevel = 1, int sedmlVersion = 1, bool exportIncomplete = false, bool exportCOPASIMIRIAM = true, CProcessReport* pExportHandler = NULL);

  SedDocument* getCurrentSEDMLDocument();
  bool setSEDMLFileName(const std::string & fileName);
  const std::string & getSEDMLFileName() const;

  std::map<CCopasiObject*, SedBase*>& getCopasi2SEDMLMap();

#endif

  void applyData(const CUndoData & data);
  void recordData(const CUndoData & data);

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
  std::vector<std::string> mTempFolders;
  bool mNeedToSaveExperimentalData;

public:
  /**
   *  This is a hack at the moment to be able to read Gepasi model files
   */
  CCopasiVectorS < CMetabOld > * pOldMetabolites;

  //the objects that were added by the last model adding action.
  std::set< const CCopasiObject * > mLastAddedObjects;

protected:
  void removeSBMLIdFromFunctions();
};

#endif // COPASI_CCopasiDataModel
