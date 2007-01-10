// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.



%{

#include "CopasiDataModel/CCopasiDataModel.h"

%}

#include <string>

%ignore CCopasiDataModel::CCopasiDataModel(const bool);
%ignore CCopasiDataModel::saveModel(const std::string& fileName,bool overwriteFile , const bool& autoSave);
%ignore CCopasiDataModel::newModel(CModel* pModel);
%ignore CCopasiDataModel::importSBMLFromString(const std::string& sbmlDocumentText,CProcessReport* pImportHandler);
%ignore CCopasiDataModel::importSBML(const std::string& fileName,CProcessReport* pImportHandler);
%ignore CCopasiDataModel::exportSBML(const std::string& fileName,bool overwriteFile,int sbmlLevel, int sbmlVersion,bool exportIncomplete = false, CProcessReport* pExportHandler);
%ignore CCopasiDataModel::exportSBMLToString(CProcessReport* pExportHandler);

%immutable CCopasiDataModel::Global;

class CCopasiDataModel 
{
  public:
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
    
    bool addDefaultTasks();

    CReportDefinitionVector * getReportDefinitionList();
    
    bool addDefaultReports();

    const std::string& getFileName() const; 
    const std::string& getSBMLFileName() const; 
    
    CFunctionDB * getFunctionList();

    %extend
    {
      CReportDefinition* getReportDefinition(unsigned C_INT32 index)
      {
        return (*self->getReportDefinitionList())[index];
      }

      CCopasiTask* getTask(unsigned C_INT32 index)
      {
        return (*self->getTaskList())[index];
      }
    }
};



