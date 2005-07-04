/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiDataModel/CCopasiDataModel.h,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/07/04 15:26:45 $
   End CVS Header */

#ifndef COPASI_CCopasiDataModel
#define COPASI_CCopasiDataModel

class CVersion;
class CModel;
class CReportDefinitionVector;
class COutputDefinitionVector;
//class CPlotSpecification;
class CFunctionDB;
class CFunction;
class SCopasiXMLGUI;
class SBMLDocument;
class SBase;

// :TODO: remove
class CMetabOld;
template <class CType> class CCopasiVectorS;

template <class CType> class CCopasiVectorN;

#include <map>

#include "utilities/CCopasiTask.h"

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

class CCopasiDataModel
  {
    // Operations
  public:
    CCopasiDataModel(const bool withGUI = false);
    ~CCopasiDataModel();

    bool loadModel(const std::string & fileName);
    bool saveModel(const std::string & fileName,
                   bool overwriteFile = false,
                   const bool & autoSave = false);
    bool autoSave();

    bool newModel(CModel * pModel = NULL);

    bool importSBML(const std::string & fileName);
    bool exportSBML(const std::string & fileName, bool overwriteFile = false);

    CModel * getModel();
    CCopasiVectorN< CCopasiTask > * getTaskList();
    CCopasiTask * addTask(const CCopasiTask::Type & taskType);
    bool addDefaultTasks();
    std::set<std::string> listTaskDependentOnReport(const std::string & key);

    CReportDefinitionVector * getReportDefinitionList();
    CReportDefinition * addReport(const CCopasiTask::Type & taskType);
    bool addDefaultReports();

    COutputDefinitionVector * getPlotDefinitionList();

    CFunctionDB * getFunctionList();
    SCopasiXMLGUI * getGUI();
    CVersion * getVersion();
    const std::string & getFileName() const;

    bool isChanged() const;
    void changed(const bool & changed = true);

    SBMLDocument* getCurrentSBMLDocument();

    std::map<CCopasiObject*, SBase*>& getCopasi2SBMLMap();

    // Attributes
  protected:
    CVersion * mpVersion;
    CFunctionDB * mpFunctionList;
    CModel * mpModel;
    CCopasiVectorN< CCopasiTask > * mpTaskList;
    CReportDefinitionVector * mpReportDefinitionList;

    //CCopasiVectorN<CPlotSpecification> * mpPlotDefinitionList;
    COutputDefinitionVector * mpPlotDefinitionList;

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
     * This will map each Copasi object to the
     * corresponding SBML object if the current model
     * was created by an SBML import.
     */
    std::map<CCopasiObject*, SBase*> mCopasi2SBMLMap;

  public:
    static CCopasiDataModel * Global;
    CFunction * mpUndefined;

    /**
     *  This is a hack at the moment to be able to read old configuration files
     */
    CCopasiVectorS < CMetabOld > * pOldMetabolites;
  };

#endif // COPASI_CCopasiDataModel
