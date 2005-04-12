/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiDataModel/CCopasiDataModel.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/04/12 14:09:40 $
   End CVS Header */

#ifndef COPASI_CCopasiDataModel
#define COPASI_CCopasiDataModel

class CVersion;
class CModel;
class CReportDefinitionVector;
class CPlotSpecification;
class CFunctionDB;
class SCopasiXMLGUI;

// :TODO: remove
class CMetabOld;
template <class CType> class CCopasiVectorS;

template <class CType> class CCopasiVectorN;

#include "utilities/CCopasiTask.h"

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

    CReportDefinitionVector * getReportDefinitionList();
    CCopasiVectorN<CPlotSpecification> * getPlotDefinitionList();

    CFunctionDB * getFunctionList();
    SCopasiXMLGUI * getGUI();
    CVersion * getVersion();

    bool isChanged() const;
    void changed(const bool & changed = true);

    // Attributes
  protected:
    CVersion * mpVersion;
    CFunctionDB * mpFunctionList;
    CModel * mpModel;
    CCopasiVectorN< CCopasiTask > * mpTaskList;
    CReportDefinitionVector * mpReportDefinitionList;
    CCopasiVectorN<CPlotSpecification> * mpPlotDefinitionList;
    bool mWithGUI;
    SCopasiXMLGUI * mpGUI;

    std::string mSaveFileName;
    bool mChanged;
    bool mAutoSaveNeeded;

  public:
    static CCopasiDataModel * Global;

    /**
     *  This is a hack at the moment to be able to read old configuration files
     */
    CCopasiVectorS < CMetabOld > * pOldMetabolites;
  };

#endif // COPASI_CCopasiDataModel
