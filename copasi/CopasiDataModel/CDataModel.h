// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CDataModel
#define COPASI_CDataModel

#include <map>

#include "copasi/copasi.h"

#include "copasi/core/CDataContainer.h"
#include "copasi/output/COutputHandler.h"
#include "copasi/utilities/CTaskEnum.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/undo/CUndoStack.h"

class CInfo;
class CModel;
class CModelParameter;
class CReportDefinition;
class CReportDefinitionVector;
class COutputDefinitionVector;
class CFunctionDB;
class CFunction;
class SCopasiXMLGUI;
class SedmlImportOptions;

LIBSBML_CPP_NAMESPACE_BEGIN
class SBMLDocument;
class SBase;
class XMLNamespaces;
LIBSBML_CPP_NAMESPACE_END
class CProcessReport;
class CConfigurationFile;
class SBMLIncompatibility;
class CListOfLayouts;
class CUndoData;
class CCopasiTask;
class CModelVersionHierarchy;

// SEDML
LIBSEDML_CPP_NAMESPACE_BEGIN
class SedBase;
class SedDocument;
LIBSEDML_CPP_NAMESPACE_END
class CPlotItem;

#include <omex/common/libcombine-namespace.h>
LIBCOMBINE_CPP_NAMESPACE_BEGIN
class CombineArchive;
LIBCOMBINE_CPP_NAMESPACE_END

// :TODO: remove
class CMetabOld;

template <class CType> class CDataVectorS;
template <class CType> class CDataVectorN;

//******************************************************************************

class CDataModel: public CDataContainer, public COutputHandler
{
  // Operations
public:
  enum struct ContentType
  {
    COPASI,
    GEPASI,
    SBML,
    SEDML,
    OMEX,
    __SIZE
  };

  /**
   * String representation of the valid model types.
   */
  static const CEnumAnnotation< std::string, ContentType > ContentTypeNames;

  /**
   * Determine the content type of the given content stream
   * @param std::istream content
   * @return ContentType contentType
   */
  static ContentType contentType(std::istream & content);

  class CContent
  {
  public:

    CContent(const bool & withGUI = false);

    CContent(const CContent & src);

    ~CContent();

    CContent & operator = (const CContent & rhs);
    bool isValid() const;

    CModel * pModel;
    CDataVectorN< CCopasiTask > * pTaskList;
    CReportDefinitionVector * pReportDefinitionList;
    COutputDefinitionVector * pPlotDefinitionList;
    CListOfLayouts * pListOfLayouts;
    SCopasiXMLGUI * pGUI;
    SBMLDocument* pCurrentSBMLDocument;
    bool mWithGUI;
    CUndoStack * mpUndoStack;
    std::string mSaveFileName;
    ContentType mContentType;
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
    std::map<const CDataObject*, SBase*> mCopasi2SBMLMap;

    // if we want to display images in the render extension,
    // those images can be png or jpg files with a relative path name.
    // If the path is relative, it is considered to be relative to the
    // path of the filename it came from.
    // Because of this, I need to know the reference directory where
    // the render information came from because it can either come from
    // an imported SBML file or from a loaded cps file.
    std::string mReferenceDir;

    // SEDML
    SedDocument* pCurrentSEDMLDocument;

    /**
     * This will map each COPASI object to the
     * corresponding SEDML object if the current model
     * was created by an SEDML import.
     */
    std::map<CDataObject*, SedBase*> mCopasi2SEDMLMap;

    /**
     * The name of the referenced SEDML file
     */
    std::string mSEDMLFileName;

#ifdef COPASI_Versioning
    CModelVersionHierarchy * mpModelVersionHierarchy;
#endif // COPASI_Versioning
  };

  // Operations
public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CDataModel * pDataObject
   */
  static CDataModel * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  CDataModel(const bool withGUI = false);

  CDataModel(const std::string & name,
             const CDataContainer * pParent = NO_PARENT,
             const std::string & type = "CN",
             bool withGUI = false);

  CDataModel(const CDataModel & src,
             const CDataContainer * pParent);

  virtual ~CDataModel();

  /**
   * Load the model from the content which may be any supported type
   * @param const std::string & content
   * @param std::string referenceDir = pwd()
   * @param CProcessReport *pProcessReport = NULL
   * @param const bool & deleteOldData = true
   */
  bool loadFromString(const std::string & content,
                      std::string referenceDir = "",
                      CProcessReport *pProcessReport = NULL,
                      const bool & deleteOldData = true);

  /**
   * Load the model from the file which may be any supported type
   * @param const std::string & fileName
   * @param CProcessReport *pProcessReport = NULL
   * @param const bool & deleteOldData = true
   */
  bool loadFromFile(const std::string & fileName,
                    CProcessReport *pProcessReport = NULL,
                    const bool & deleteOldData = true);

  bool loadModel(std::istream & in,
                 const std::string & pwd,
                 CProcessReport * pProcessReport,
                 const bool & deleteOldData = true);

  bool loadModel(const std::string & fileName,
                 CProcessReport * pProcessReport,
                 const bool & deleteOldData = true);

  /**
   * Loads the model contained in the specified file and adds it to the
   * current one
   *
   * @param fileName the copasi file to add to this model
   * @param pProcessReport optional progress handler
   *
   * @return true, if a model was successfully added, false otherwise
   */
  bool addModel(const std::string & fileName,
                CProcessReport *pProcessReport = NULL);

  bool loadModelParameterSets(const std::string & fileName,
                              CProcessReport *pProcessReport = NULL);

  bool saveModelParameterSets(const std::string & fileName);

  bool saveModel(const std::string & fileName,
                 CProcessReport * pProcessReport,
                 bool overwriteFile = false,
                 const bool & autoSave = false);

  std::string saveModelToString(CProcessReport *pProcessReport = NULL);

  bool autoSave();

  bool newModel(CProcessReport * pProcessReport,
                const bool & deleteOldData);

  bool importSBMLFromString(const std::string & sbmlDocumentText,
                            CProcessReport *pProcessReport = NULL,
                            const bool & deleteOldData = true);

  bool importSBML(const std::string & fileName,
                  CProcessReport *pProcessReport = NULL,
                  const bool & deleteOldData = true);

  std::string exportSBMLToString(CProcessReport * pProcessReport, int sbmlLevel, int sbmlVersion);

  bool exportSBML(const std::string & fileName, bool overwriteFile = false, int sbmlLevel = 2, int sbmlVersion = 1, bool exportIncomplete = false, bool exportCOPASIMIRIAM = true, CProcessReport  * pProcessReport = NULL);

  std::string exportMathModelToString(CProcessReport * pProcessReport, const std::string & filter);

  bool exportMathModel(const std::string & fileName, CProcessReport * pProcessReport,
                       const std::string & filter, bool overwriteFile = false);

  /**
   * Resolves the provided display string and returns a data object for it if it can be found
   *
   * @param displayString the display name of the object to find
   *
   * @return the data object for the display name if found, NULL otherwise
   */
  const CDataObject *findObjectByDisplayName(const std::string& displayString) const;

  /**
   * Moves the experimental data referenced in the model to the specified
   * path and update the referenced filenames to match it. Should the folder
   * already have an experimental data file in there with the name, a new
   * name will be chosen.
   *
   * @param path the target directory for the experimental data.
   */
  void copyExperimentalDataTo(const std::string& path);

  /**
   * Exports the current model as COMBINE archive
   *
   * @param fileName the archive filename to create
   * @param includeCOPASI whether to include COPASI models (defaults to true)
   * @param includeSBML whether to include SBML models (defaults to true)
   * @param includeData whether to include experimental data files (if any)
   * @param includeSEDML whether to include SEDML documents (defaults to false)
   * @param overWriteFile whether to overwrite files if already present (false)
   *
   */
  bool exportCombineArchive(std::string fileName,
                            bool includeCOPASI = true,
                            bool includeSBML = true,
                            bool includeData = true,
                            bool includeSEDML = false,
                            bool overwriteFile = false,
                            CProcessReport *pProcessReport = NULL,
                            int sbmlLevel = 2,
                            int sbmlVersion = 4,
                            int sedmlLevel = 1,
                            int sedmlVersion = 4);

  bool exportShinyArchive(std::string fileName,
                          bool includeCOPASI = true,
                          bool includeData = true,
                          bool overwriteFile = false,
                          CProcessReport *pProcessReport = NULL);

  /**
   * adds the current COPASI model to the archive with the given
   * target name
   *
   * @param archive the COMBINE archive
   * @param targetName the name and path that the COPASI file should have in the archive
   * @param pProgressReport optional pointer to the progress report
   */
  void addCopasiFileToArchive(LIBCOMBINE_CPP_NAMESPACE_QUALIFIER CombineArchive *archive,
                              const std::string& targetName = "./copasi/model.cps",
                              CProcessReport *pProcessReport = NULL);

  bool openCombineArchive(const std::string& fileName, CProcessReport *pProcessReport = NULL,
                          const bool & deleteOldData = true,
                          const SedmlImportOptions * pOptions = NULL);

  void deleteOldData();

  CUndoStack * getUndoStack();
  CModel * getModel();
  const CModel * getModel() const;
  const ContentType & getContentType() const;
  CDataVectorN< CCopasiTask > * getTaskList();
  const CDataVectorN< CCopasiTask > * getTaskList() const;
  CCopasiTask * addTask(const CTaskEnum::Task & taskType);
  bool addDefaultTasks();
  /**
   * Appends pointers to tasks, which are dependent on any of the candidates
   * to the list dependentTasks.
   * @param CDataObject::ObjectSet candidates
   * @param CDataObject::DataObjectSet & dependentTasks
   * @return bool functionsAppended
   */
  bool appendDependentTasks(ObjectSet candidates,
                            DataObjectSet & dependentTasks) const;

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
  void  setFileName(const std::string& fileName);

  std::string getDefaultFileName(const std::string & suffix) const;

  bool isChanged() const;
  void changed(const bool & changed = true);

  SBMLDocument* getCurrentSBMLDocument();
  bool setSBMLFileName(const std::string & fileName);
  const std::string & getSBMLFileName() const;

  std::map<const CDataObject*, SBase*>& getCopasi2SBMLMap();

public:
  const std::string& getReferenceDirectory() const;

  // SEDML
  bool importSEDMLFromString(const std::string & sedmlDocumentText,
                             std::string referenceDir = "",
                             CProcessReport *pProcessReport = NULL,
                             const bool & deleteOldData = true,
                             const SedmlImportOptions * pOptions = NULL);

  bool importSEDML(const std::string & fileName,
                   CProcessReport *pProcessReport = NULL,
                   const bool & deleteOldData = true,
                   const SedmlImportOptions * pOptions = NULL);

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
   * @param pAdditionalNamespaces additional namespaces to be added to the
   *        SED-ML document
   *
   * @return the SED-ML string.
   */
  std::string exportSEDMLToString(CProcessReport * pProcessReport,
                                  int sedmlLevel, int sedmlVersion,
                                  const std::string& modelLocation = "model.xml",
                                  const XMLNamespaces* pAdditionalNamespaces = NULL
                                 );

  /**
   * Exports the current model as SEDML document
   *
   * @param fileName the filename to create
   * @param sedmlLevel the level of the SEDML to export (defaults to 1)
   * @param sedmlVersion the version of SEDML to export (defaults to 4)
   *
   */
  bool exportSEDML(const std::string & fileName,
                   bool overwriteFile = false,
                   int sedmlLevel = 1,
                   int sedmlVersion = 4,
                   bool exportIncomplete = false,
                   bool exportCOPASIMIRIAM = true,
                   CProcessReport * pProcessReport = NULL);

  SedDocument* getCurrentSEDMLDocument();
  bool setSEDMLFileName(const std::string & fileName);
  const std::string & getSEDMLFileName() const;

  std::map<CDataObject*, SedBase*>& getCopasi2SEDMLMap();

  CUndoData::CChangeSet applyData(const CUndoData & data);
  CUndoData::CChangeSet recordData(const CUndoData & data);

  /**
   * changes the provided model element to the given double value
   */
  static bool changeModelParameter(CDataObject* element, double value);

  /**
   * updates the data model with values from the provided ini file.
   * This file should have the simple syntax, of one of more statements:
   *
   *    name = value
   *
   * where name is a valid DisplayName of a model object, and value a double
   * value to be assigned. To indicate a comment, use the semicolon ';' after
   * which the remaining line will be disregarded.
   *
   * @param fileName the fileName of the ini file
   */
  void reparameterizeFromIniFile(const std::string& fileName);

#ifdef COPASI_Versioning
  CModelVersionHierarchy * getModelVersionHierarchy();
#endif // COPASI_Versioning

protected:
  void pushData();
  void popData();
  void commonAfterLoad(CProcessReport * pProcessReport,
                       const bool & deleteOldData);

  void replaceCnInGroup(CModelParameter* pParam,
                        const std::string &oldCn, const std::string& newCN);

  // Attributes
protected:
  CContent mData;
  CContent mOldData;
  CInfo * mpInfo;
  std::vector<std::string> mTempFolders;
  bool mNeedToSaveExperimentalData;

public:
  /**
   *  This is a hack at the moment to be able to read Gepasi model files
   */
  CDataVectorS < CMetabOld > * pOldMetabolites;

  //the objects that were added by the last model adding action.
  std::set< const CDataObject * > mLastAddedObjects;

protected:
  void removeSBMLIdFromFunctions();
};

#endif // COPASI_CDataModel
