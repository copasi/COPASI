// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

%{

#include "copasi/CopasiDataModel/CDataModel.h"

#include "copasi/sbml/SBMLImporter.h"
#include "copasi/sbml/CSBMLExporter.h"
#include "copasi/sedml/SEDMLImporter.h"
#include "copasi/sedml/CSEDMLExporter.h"
#include "copasi/sedml/SEDMLUtils.h"

%}

#include <string>

%ignore CDataModelRenameHandler;
%ignore CRenameHandler;

%ignore CDataModel::CDataModel(const bool);
%ignore CDataModel::autoSave();
%ignore CDataModel::mLastAddedObjects;
%ignore CDataModel::pOldMetabolites;
%ignore CDataModel::print;
%ignore CDataModel::loadModel(const std::string& fileName,CProcessReport* pProcessReport,
                 const bool & deleteOldData = true);
%ignore CDataModel::loadModel(std::istream & in,
                 const std::string & pwd,
                 CProcessReport* pProcessReport,
                 const bool & deleteOldData = true);

%ignore CDataModel::getCurrentSEDMLDocument;
%ignore CDataModel::getCopasi2SEDMLMap;

                 
//%ignore CDataModel::saveModel(const std::string& fileName,CProcessReport* pProcessReport, bool overwriteFile=false , const bool& autoSave=false);
//%ignore CDataModel::newModel;
//%ignore CDataModel::importSBMLFromString(const std::string& sbmlDocumentText,CProcessReport* pImportHandler,
//                 const bool & deleteOldData = true);
//%ignore CDataModel::importSBML(const std::string& fileName,CProcessReport* pImportHandler,
//                 const bool & deleteOldData = true);
//%ignore CDataModel::exportSBML(const std::string& fileName,bool overwriteFile,int sbmlLevel, int sbmlVersion,bool exportIncomplete ,bool exportCOPASIMIRIAM=false,CProcessReport* pExportHandler = NULL );
//%ignore CDataModel::exportSBMLToString(CProcessReport* pExportHandler,int sbmlLevel, int sbmlVersion);
//%ignore CDataModel::exportMathModel(const std::string & fileName, CProcessReport* pProcessReport, const std::string & filter, bool overwriteFile = //false);
%ignore CDataModel::exportMathModelToString(CProcessReport* pProcessReport, const std::string & filter);
%ignore CDataModel::getModel() const;
%ignore CDataModel::getTaskList() const;
%ignore CDataModel::getListOfLayouts() const;
%ignore CDataModel::listTaskDependentOnReport(const std::string & key);
%ignore CDataModel::addReport(const CCopasiTask::Type & taskType);
%ignore CDataModel::getPlotDefinitionList();
%ignore CDataModel::getGUI();
//%ignore CDataModel::getConfiguration();
%ignore CDataModel::isChanged() const;
%ignore CDataModel::changed(const bool & changed = true);
%ignore CDataModel::getCurrentSBMLDocument();
//%ignore CDataModel::setSBMLFileName(const std::string & fileName);
%ignore CDataModel::getCopasi2SBMLMap();
%ignore CDataModel::isSBMLCompatible(int sbmlLevel = 2, int sbmlVersion = 1) const;
%ignore CDataModel::removeSBMLIdFromFunctions();
%ignore CDataModel::pOldMetabolites;
%ignore CDataModel::mCopasi2SBMLMap;
%ignore CDataModel::mSBMLFileName;
%ignore CDataModel::mpCurrentSBMLDocument;
%ignore CDataModel::mRenameHandler;
%ignore CDataModel::mAutoSaveNeeded;
%ignore CDataModel::mChanged;
%ignore CDataModel::mSaveFileName;
%ignore CDataModel::mpConfiguration;
%ignore CDataModel::mpGUI;
%ignore CDataModel::mWithGUI;
%ignore CDataModel::mpVersion;
%ignore CDataModel::mpFunctionList;
%ignore CDataModel::mpModel;
%ignore CDataModel::mpTaskList;
%ignore CDataModel::mpReportDefinitionList;
%ignore CDataModel::mpPlotDefinitionList;
%ignore CDataModel::ObjectFromName(std::vector<CDataContainer * > const &,CCommonName const &) const;
%ignore CDataModel::getReportDefinitionList() const;

%catches(CCopasiException, ...) CDataModel::newModel;
%catches(CCopasiException, ...) CDataModel::newModel;
%catches(CCopasiException, ...) CDataModel::importSBMLFromString;
%catches(CCopasiException, ...) CDataModel::importSBML;
%catches(CCopasiException, ...) CDataModel::importSBMLFromString;
%catches(CCopasiException, ...) CDataModel::openCombineArchive;
%catches(CCopasiException, ...) CDataModel::importSEDML;
%catches(CCopasiException, ...) CDataModel::importSEDMLFromString;
%catches(CCopasiException, SBMLConstructorException, ...) CDataModel::exportSBMLToString;
%catches(CCopasiException, SBMLConstructorException, ...) CDataModel::exportSBML;
%catches(CCopasiException, SBMLConstructorException, ...) CDataModel::exportSEDMLToString;
%catches(CCopasiException, SBMLConstructorException, ...) CDataModel::exportSEDML;
%catches(CCopasiException, SBMLConstructorException, std::exception, ...) CDataModel::exportCombineArchive;

// suppress warnings on multiple inheritance
%warnfilter(813) CDataModel;

%include "copasi/CopasiDataModel/CDataModel.h"
%include "copasi/sbml/SBMLImporter.h"
%include "copasi/sbml/CSBMLExporter.h"
%include "copasi/sedml/SEDMLImporter.h"
%include "copasi/sedml/CSEDMLExporter.h"
%include "copasi/sedml/SEDMLUtils.h"
%include "copasi/sedml/SedmlImportOptions.h"

%rename(newModel) CDataModel::newModel;

%extend CDataModel
{
  bool importSBMLFromString(const std::string& content)
  {
    try
    {
      return self->importSBMLFromString(content, NULL);
    }
    catch(...)
    {
      return false;
    }
  }

  bool loadModelFromString(const std::string& content, const std::string& path)
  {
    try
    {
      std::istringstream is(content);
      return $self->loadModel(is,
                 path,
                 NULL);
    }
    catch(...)
    {
      return false;
    }
  }
    bool loadModel(const std::string& fileName)
    {
        return $self->loadModel(fileName,NULL);
    }

    bool saveModel(const std::string& fileName,bool overwriteFile=false)
    {
        return $self->saveModel(fileName,NULL,overwriteFile,false);
    }

    std::string exportSBMLToString(int sbmlLevel, int sbmlVersion)
    {
      try
      {
        return $self->exportSBMLToString(NULL,sbmlLevel,sbmlVersion);
      }
      catch (...)
      {
        return "";
      }
    }

    /* this is for backwards compatibility. */
    std::string exportSBMLToString()
    {
      try
      {
        return $self->exportSBMLToString(NULL,3,1);
      }
      catch (...)
      {
        return "";
      }
    }

    std::string exportMathModelToString(const std::string& filter)
    {
        try
        {
          return $self->exportMathModelToString(NULL,filter);
        }
        catch (...)
        {
          return "";
        }
    }

    bool newModel()
    {
        return $self->newModel(NULL,false);
    }

    unsigned C_INT32 getNumReportDefinitions()
    {
     return (unsigned C_INT32) self->getReportDefinitionList()->size();
    }
    
    bool removeReportDefinition(unsigned C_INT32 index)
    {
      CDataVector< CReportDefinition > * pReportList = self->getReportDefinitionList();
      CReportDefinition * pReport = &(*pReportList)[index];

      if (pReport == NULL)
        return false;


      CDataObject::DataObjectSet Tasks;
      CDataObject::ObjectSet DeletedObjects;
      DeletedObjects.insert(pReport);

      if (self->appendDependentTasks(DeletedObjects, Tasks))
        {
          std::set< const CDataObject * >::iterator it = Tasks.begin();
          std::set< const CDataObject * >::iterator end = Tasks.end();

          for (; it != end; ++it)
            {
              const CCopasiTask * pTask = static_cast< const CCopasiTask *>(*it);
              const_cast< CCopasiTask * >(pTask)->getReport().setReportDefinition(NULL);
            }
        }

      pReportList->remove(pReport);
      return true;
    }
    
    bool removePlotSpecification(unsigned C_INT32 index)
    {
      CDataVector< CPlotSpecification > * pPlotList = self->getPlotDefinitionList();

      CPlotSpecification * pPlot = &(*pPlotList)[index];

      if (pPlot == NULL)
        return false;

      pPlotList->remove(pPlot);
      return true;
    }
    
    unsigned C_INT32 getNumPlotSpecifications()
    {
     return (unsigned C_INT32) self->getPlotDefinitionList()->size();
    }
    
    CReportDefinition* getReportDefinition(unsigned C_INT32 index)
    {
      try
      {
        return &(*$self->getReportDefinitionList())[index];
      }
      catch(...)
      {
        return NULL;
      }
    }

    CReportDefinition* getReportDefinition(const std::string& name)
    {
      try
      {
        return &(*$self->getReportDefinitionList())[name];
      }
      catch(...)
      {
        return NULL;
      }
    }
    
    CPlotSpecification* getPlotSpecification(unsigned C_INT32 index)
    {
      try
      {
        return &(*$self->getPlotDefinitionList())[index];
      }
      catch(...)
      {
        return NULL;
      }
    }

    CPlotSpecification* getPlotSpecification(const std::string& name)
    {
      try
      {
        return &(*$self->getPlotDefinitionList())[name];
      }
      catch(...)
      {
        return NULL;
      }
    }

    unsigned C_INT32 getNumTasks()
    {
     return (unsigned C_INT32) self->getTaskList()->size();
    } 
    
    CCopasiTask* getTask(unsigned C_INT32 index)
    {
      try
      {
        return &(*$self->getTaskList())[index];
      }
      catch(...)
      {
        return NULL;
      }
    }

    CCopasiTask* getTask(const std::string& name)
    {
      try
      {
         return &(*$self->getTaskList())[name];
      }
      catch(...)
      {
         return NULL;
      }
    }

#ifdef SWIGJAVA
    // needed for CellDesigner
    static CDataModel* Global_get()
    {
        std::cerr << "Calling static method getGlobal on CDataModel is obsolete, please see the documentation for CRootContainer on how to handle this in newer versions of the COPASI API." << std::endl;
        // check if there is a model and if not, create one
        CDataModel* pDatamodel=NULL;
        if(CRootContainer::getDatamodelList()->size() != 0)
        {
            pDatamodel=&(*CRootContainer::getDatamodelList())[0];
        }
        else
        {
            pDatamodel=CRootContainer::addDatamodel();
        }
        assert(pDatamodel != NULL);
        return pDatamodel;
    }

    // needed for CellDesigner
    const CVersion* getVersion() const
    {
        std::cerr << "Calling static method getVersion on CDataModel is obsolete, please use static method getVERSION() from CVersion instead." << std::endl;
        return &CVersion::VERSION;
    }

    // needed for CellDesigner
    static CDataModel* getGlobal()
    {
        std::cerr << "Calling static method getGlobal on CDataModel is obsolete, please see the documentation for CRootContainer on how to handle this in newer versions of the COPASI API."  << std::endl;
        // check if there is a model and if not, create one
        CDataModel* pDatamodel=NULL;
        if(CRootContainer::getDatamodelList()->size() != 0)
        {
            pDatamodel=&(*CRootContainer::getDatamodelList())[0];
        }
        else
        {
            pDatamodel=CRootContainer::addDatamodel();
        }
        assert(pDatamodel != NULL);
        return pDatamodel;

    }
#endif // SWIGJAVA
};


