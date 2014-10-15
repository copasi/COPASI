// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 



























%{

#include "CopasiDataModel/CCopasiDataModel.h"

%}

#include <string>

%ignore CDataModelRenameHandler;
%ignore CRenameHandler;

%ignore CCopasiDataModel::CCopasiDataModel(const bool);
%ignore CCopasiDataModel::autoSave();
%ignore CCopasiDataModel::mLastAddedObjects;
%ignore CCopasiDataModel::pOldMetabolites;
%ignore CCopasiDataModel::print;
%ignore CCopasiDataModel::loadModel(const std::string& fileName,CProcessReport* pProcessReport,
                 const bool & deleteOldData = true);
%ignore CCopasiDataModel::loadModel(std::istream & in,
                 const std::string & pwd,
                 CProcessReport* pProcessReport,
                 const bool & deleteOldData = true);

%ignore CCopasiDataModel::saveModel(const std::string& fileName,CProcessReport* pProcessReport, bool overwriteFile=false , const bool& autoSave=false);
%ignore CCopasiDataModel::newModel;
%ignore CCopasiDataModel::importSBMLFromString(const std::string& sbmlDocumentText,CProcessReport* pImportHandler,
                 const bool & deleteOldData = true);
%ignore CCopasiDataModel::importSBML(const std::string& fileName,CProcessReport* pImportHandler,
                 const bool & deleteOldData = true);
%ignore CCopasiDataModel::exportSBML(const std::string& fileName,bool overwriteFile,int sbmlLevel, int sbmlVersion,bool exportIncomplete ,bool exportCOPASIMIRIAM=false,CProcessReport* pExportHandler = NULL );
%ignore CCopasiDataModel::exportSBMLToString(CProcessReport* pExportHandler,int sbmlLevel, int sbmlVersion);
%ignore CCopasiDataModel::exportMathModel(const std::string & fileName, CProcessReport* pProcessReport, const std::string & filter, bool overwriteFile = false);
%ignore CCopasiDataModel::exportMathModelToString(CProcessReport* pProcessReport, const std::string & filter);
%ignore CCopasiDataModel::getModel() const;
%ignore CCopasiDataModel::getTaskList() const;
%ignore CCopasiDataModel::getListOfLayouts() const;
%ignore CCopasiDataModel::listTaskDependentOnReport(const std::string & key);
%ignore CCopasiDataModel::addReport(const CCopasiTask::Type & taskType);
%ignore CCopasiDataModel::getPlotDefinitionList();
%ignore CCopasiDataModel::getGUI();
%ignore CCopasiDataModel::getConfiguration();
%ignore CCopasiDataModel::isChanged() const;
%ignore CCopasiDataModel::changed(const bool & changed = true);
%ignore CCopasiDataModel::getCurrentSBMLDocument();
%ignore CCopasiDataModel::setSBMLFileName(const std::string & fileName);
%ignore CCopasiDataModel::getCopasi2SBMLMap();
%ignore CCopasiDataModel::isSBMLCompatible(int sbmlLevel = 2, int sbmlVersion = 1) const;
%ignore CCopasiDataModel::removeSBMLIdFromFunctions();
%ignore CCopasiDataModel::pOldMetabolites;
%ignore CCopasiDataModel::mCopasi2SBMLMap;
%ignore CCopasiDataModel::mSBMLFileName;
%ignore CCopasiDataModel::mpCurrentSBMLDocument;
%ignore CCopasiDataModel::mRenameHandler;
%ignore CCopasiDataModel::mAutoSaveNeeded;
%ignore CCopasiDataModel::mChanged;
%ignore CCopasiDataModel::mSaveFileName;
%ignore CCopasiDataModel::mpConfiguration;
%ignore CCopasiDataModel::mpGUI;
%ignore CCopasiDataModel::mWithGUI;
%ignore CCopasiDataModel::mpVersion;
%ignore CCopasiDataModel::mpFunctionList;
%ignore CCopasiDataModel::mpModel;
%ignore CCopasiDataModel::mpTaskList;
%ignore CCopasiDataModel::mpReportDefinitionList;
%ignore CCopasiDataModel::mpPlotDefinitionList;
%ignore CCopasiDataModel::ObjectFromName(std::vector<CCopasiContainer * > const &,CCopasiObjectName const &) const;
%ignore CCopasiDataModel::getReportDefinitionList() const;

%catches(CCopasiException) CCopasiDataModel::newModel();
%catches(CCopasiException) CCopasiDataModel::newModel(CProcessReport* pProcessReport,const bool& deleteOldData);
%catches(CCopasiException) CCopasiDataModel::importSBMLFromString(const std::string& sbmlDocumentText,CProcessReport* pImportHandler = NULL,const bool& deleteOldData = true);
%catches(CCopasiException) CCopasiDataModel::importSBML(const std::string&,CProcessReport*,const bool& deleteOldData = true);
%catches(CCopasiException) CCopasiDataModel::importSBMLFromString(const std::string&,CProcessReport*,const bool& deleteOldData = true);
%catches(CCopasiException) CCopasiDataModel::exportSBMLToString(CProcessReport* pExportHandler , int sbmlLevel,int sbmlVersion);
%catches(CCopasiException) CCopasiDataModel::exportSBML(const std::string& fileName, bool overwriteFile=false, int sbmlLevel = 2, int sbmlVersion = 1, bool exportIncomplete = false, bool exportCOPASIMIRIAM, CProcessReport* pExportHandler = NULL);

#if SWIGPYTHON
%exception importSBML {
   try {
      $action
   } catch (...) {
      PyErr_SetString(PyExc_IndexError, "Unknown exception");
      return false;
   }
}
#endif // SWIGPYTHON

// suppress warnings on multiple inheritance
%warnfilter(813) CCopasiDataModel;

%include "CopasiDataModel/CCopasiDataModel.h"

%rename(newModel) CCopasiDataModel::newModel;

%extend CCopasiDataModel
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
        return $self->exportSBMLToString(NULL,sbmlLevel,sbmlVersion);
    }

    /* this is for backwards compatibility. */
    std::string exportSBMLToString()
    {
        return $self->exportSBMLToString(NULL,2,1);
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
      CCopasiVector< CReportDefinition > * pReportList = self->getReportDefinitionList();
      CReportDefinition * pReport = (*pReportList)[index];

      if (pReport == NULL)
        return false;


      std::set< const CCopasiObject * > Tasks;
      std::set< const CCopasiObject * > DeletedObjects;
      DeletedObjects.insert(pReport);

      if (self->appendDependentTasks(DeletedObjects, Tasks))
        {
          std::set< const CCopasiObject * >::iterator it = Tasks.begin();
          std::set< const CCopasiObject * >::iterator end = Tasks.end();

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
      CCopasiVector< CPlotSpecification > * pPlotList = self->getPlotDefinitionList();

      CPlotSpecification * pPlot = (*pPlotList)[index];

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
        return (*$self->getReportDefinitionList())[index];
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
        return (*$self->getReportDefinitionList())[name];
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
        return (*$self->getPlotDefinitionList())[index];
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
        return (*$self->getPlotDefinitionList())[name];
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
        return (*$self->getTaskList())[index];
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
         return (*$self->getTaskList())[name];
      }
      catch(...)
      {
         return NULL;
      }
    }

#ifdef SWIGJAVA
    // needed for CellDesigner
    static CCopasiDataModel* Global_get()
    {
        std::cerr << "Calling static method getGlobal on CCopasiDataModel is obsolete, please see the documentation for CCopasiRootContainer on how to handle this in newer versions of the COPASI API." << std::endl;
        // check if there is a model and if not, create one
        CCopasiDataModel* pDatamodel=NULL;
        if(CCopasiRootContainer::getDatamodelList()->size() != 0)
        {
            pDatamodel=(*CCopasiRootContainer::getDatamodelList())[0];
        }
        else
        {
            pDatamodel=CCopasiRootContainer::addDatamodel();
        }
        assert(pDatamodel != NULL);
        return pDatamodel;
    }

    // needed for CellDesigner
    const CVersion* getVersion() const
    {
        std::cerr << "Calling static method getVersion on CCopasiDataModel is obsolete, please use static method getVERSION() from CVersion instead." << std::endl;
        return &CVersion::VERSION;
    }

    // needed for CellDesigner
    static CCopasiDataModel* getGlobal()
    {
        std::cerr << "Calling static method getGlobal on CCopasiDataModel is obsolete, please see the documentation for CCopasiRootContainer on how to handle this in newer versions of the COPASI API." << std::endl;
        // check if there is a model and if not, create one
        CCopasiDataModel* pDatamodel=NULL;
        if(CCopasiRootContainer::getDatamodelList()->size() != 0)
        {
            pDatamodel=(*CCopasiRootContainer::getDatamodelList())[0];
        }
        else
        {
            pDatamodel=CCopasiRootContainer::addDatamodel();
        }
        assert(pDatamodel != NULL);
        return pDatamodel;

    }
#endif // SWIGJAVA
};


