// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiDataModel/CCopasiDataModel.h,v $
//   $Revision: 1.36 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/05/07 20:03:29 $
// End CVS Header

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

class CVersion;
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

#ifdef WITH_LAYOUT
class CListOfLayouts;
#endif

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

    virtual ~CDataModelRenameHandler(){};

    virtual bool handle(const std::string & oldCN, const std::string & newCN) const;

  private:
    CCopasiDataModel * mpDataModel;
  };

//******************************************************************************

class CCopasiDataModel: public COutputHandler
  {
    // Operations
  public:
    CCopasiDataModel(const bool withGUI = false);
    ~CCopasiDataModel();

    bool loadModel(const std::string & fileName, CProcessReport* pProcessReport);
    bool saveModel(const std::string & fileName, CProcessReport* pProcessReport,
                   bool overwriteFile = false,
                   const bool & autoSave = false);
    bool autoSave();

    bool newModel(CModel * pModel, CProcessReport* pProcessReport
#ifdef WITH_LAYOUT
                  , CListOfLayouts * pLol = NULL
#endif
);

    bool importSBMLFromString(const std::string & sbmlDocumentText, CProcessReport* pImportHandler = NULL);
    bool importSBML(const std::string & fileName, CProcessReport* pImportHandler = NULL);
    std::string exportSBMLToString(CProcessReport* pExportHandler = NULL, int sbmlLevel, int sbmlVersion);
    bool exportSBML(const std::string & fileName, bool overwriteFile = false, int sbmlLevel = 2, int sbmlVersion = 1, bool exportIncomplete = false, CProcessReport* pExportHandler = NULL);
    bool exportMathModel(const std::string & fileName, CProcessReport* pProcessReport,
                         const std::string & filter, bool overwriteFile = false);

    CModel * getModel();
    const CModel * getModel() const;
    CCopasiVectorN< CCopasiTask > * getTaskList();
    CCopasiTask * addTask(const CCopasiTask::Type & taskType);
    bool addDefaultTasks();
    std::set<std::string> listTaskDependentOnReport(const std::string & key);

    CReportDefinitionVector * getReportDefinitionList();
    CReportDefinition * addReport(const CCopasiTask::Type & taskType);
    bool addDefaultReports();

    COutputDefinitionVector * getPlotDefinitionList();

#ifdef WITH_LAYOUT
    CListOfLayouts * getListOfLayouts();
#endif

    CFunctionDB * getFunctionList();
    SCopasiXMLGUI * getGUI();
    CConfigurationFile * getConfiguration();
    CVersion * getVersion();
    const std::string & getFileName() const;

    bool isChanged() const;
    void changed(const bool & changed = true);

    SBMLDocument* getCurrentSBMLDocument();
    bool setSBMLFileName(const std::string & fileName);
    const std::string & getSBMLFileName() const;

    std::map<CCopasiObject*, SBase*>& getCopasi2SBMLMap();

    /**
     * Retrieve the pointer for the function used for importing the
     * unsupported SBML symbol delay
     * @return CFunction * pUnsupportedDelay
     */
    CFunction * getUnsupportedDelay();

    // Attributes
  protected:
    CVersion * mpVersion;
    CFunctionDB * mpFunctionList;
    CModel * mpModel;
    CCopasiVectorN< CCopasiTask > * mpTaskList;
    CReportDefinitionVector * mpReportDefinitionList;

    COutputDefinitionVector * mpPlotDefinitionList;

#ifdef WITH_LAYOUT
    CListOfLayouts * mpListOfLayouts;
#endif

    bool mWithGUI;
    SCopasiXMLGUI * mpGUI;
    CConfigurationFile * mpConfiguration;

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

    /**
     * Pointer to a function created for supporting the load SBML models
     * using the delay symbol
     */
    CFunction * mpUnsupportedDelay;

  public:
    static CCopasiDataModel * Global;
    CFunction * mpUndefined;

    /**
     *  This is a hack at the moment to be able to read Gepasi model files
     */
    CCopasiVectorS < CMetabOld > * pOldMetabolites;

  protected:
    void removeSBMLIdFromFunctions();
  };

#endif // COPASI_CCopasiDataModel
