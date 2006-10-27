

%{

#include "CopasiDataModel/CCopasiDataModel.h"

%}

#include <string>

%ignore CCopasiDataModel::CCopasiDataModel(const bool);
%ignore CCopasiDataModel::saveModel(const std::string& fileName,bool overwriteFile = false, const bool& autoSave);
%ignore CCopasiDataModel::newModel(CModel* pModel);
%ignore CCopasiDataModel::importSBMLFromString(const std::string& sbmlDocumentText,CProcessReport* pImportHandler);
%ignore CCopasiDataModel::importSBML(const std::string& fileName,CProcessReport* pImportHandler);
%ignore CCopasiDataModel::exportSBML(const std::string& fileName,bool overwriteFile=false,int sbmlLevel, int sbmlVersion,bool exportIncomplete = false, CProcessReport* pExportHandler);
%ignore CCopasiDataModel::exportSBMLToString(CProcessReport* pExportHandler);

#ifndef COPASI_DEBUG

%nodefaultctor
%nodefaultdtor

#endif /* !COPASI_DEBUG */


class CCopasiDataModel 
{
  public:
#ifdef COPASI_DEBUG
    CCopasiDataModel(const bool withGUI = false);
    ~CCopasiDataModel();
#endif /* COPASI_DEBUG */  
    bool loadModel(const std::string& fileName);
    bool saveModel(const std::string& fileName,
                   bool overwriteFile = false,
                   const bool& autoSave = false);

    bool newModel(CModel* pModel = NULL);
    
    bool importSBMLFromString(const std::string& sbmlDocumentText,CProcessReport* pImportHandler = NULL);
    bool importSBML(const std::string& fileName, CProcessReport* pImportHandler = NULL);
    
    std::string exportSBMLToString(CProcessReport* pExportHandler = NULL);
    bool exportSBML(const std::string& fileName,
                    bool overwriteFile=false,
                    int sbmlLevel = 2,
                    int sbmlVersion = 1,
                    bool exportIncomplete = false,
                    CProcessReport* pExportHandler = NULL);
    
    CModel* getModel();

    CVersion* getVersion();

    static CCopasiDataModel * Global;

    CCopasiVectorN<CCopasiTask>* getTaskList();
    
    CCopasiTask * addTask(const CCopasiTask::Type & taskType);

    bool addDefaultTasks();

    CReportDefinitionVector * getReportDefinitionList();
    
    CReportDefinition * addReport(const CCopasiTask::Type & taskType);
    
    bool addDefaultReports();

    const std::string& getFileName() const; 
    const std::string& getSBMLFileName() const; 
};

#ifndef COPASI_DEBUG

%clearnodefaultctor
%clearnodefaultdtor

#endif /* !COPASI_DEBUG */


CCopasiDataModel* CCopasiDataModel::Global=NULL;

