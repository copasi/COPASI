/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiDataModel/CCopasiDataModel.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/08 16:29:16 $
   End CVS Header */

#ifndef COPASI_CCopasiDataModel
#define COPASI_CCopasiDataModel

class CModel;
class CReportDefinitionVector;
class CPlotSpecification;
class CFunctionDB;

template <class CType> class CCopasiVectorN;

#include "utilities/CCopasiTask.h"

//******************************************************************************

class CCopasiDataModel
  {
  public:
    CCopasiDataModel();

    bool loadModel(const std::string & fileName);
    bool saveModel(const std::string & fileName);
    bool newModel(CModel * pModel = NULL);

    bool importSBML(const std::string & fileName);
    bool exportSBML(const std::string & fileName);

    CModel * getModel();
    CCopasiVectorN< CCopasiTask > * getTaskList();
    CCopasiTask * addTask(const CCopasiTask::Type & taskType);
    bool addDefaultTasks();

    CReportDefinitionVector * getReportDefinitionList();
    CCopasiVectorN< CPlotSpecification > * getPlotDefinitionList();
    CFunctionDB * getFunctionList();

    bool isChanged() const;
    void changed(const bool & changed = true);

  protected:
    CFunctionDB * mpFunctionList;
    CModel * mpModel;
    CCopasiVectorN< CCopasiTask > * mpTaskList;
    CReportDefinitionVector * mpReportDefinitionList;
    CCopasiVectorN< CPlotSpecification > * mpPlotDefinitionList;

    bool mChanged;
  };

#endif // COPASI_CCopasiDataModel
