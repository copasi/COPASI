// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiDataModel.i,v $ 
//   $Revision: 1.18 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/06/02 11:15:11 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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
%ignore CCopasiDataModel::loadModel(const std::string& fileName,CProcessReport* pProcessReport);
%ignore CCopasiDataModel::saveModel(const std::string& fileName,CProcessReport* pProcessReport, bool overwriteFile=false , const bool& autoSave=false);
%ignore CCopasiDataModel::newModel(CModel* pModel,CProcessReport* pProcessReport);
%ignore CCopasiDataModel::importSBMLFromString(const std::string& sbmlDocumentText,CProcessReport* pImportHandler);
%ignore CCopasiDataModel::importSBML(const std::string& fileName,CProcessReport* pImportHandler);
%ignore CCopasiDataModel::exportSBML(const std::string& fileName,bool overwriteFile,int sbmlLevel, int sbmlVersion,bool exportIncomplete = false,CProcessReport* pExportHandler = NULL );
%ignore CCopasiDataModel::exportSBMLToString(CProcessReport* pExportHandler,int sbmlLevel, int sbmlVersion);
%ignore CCopasiDataModel::exportMathModel(const std::string & fileName, CProcessReport* pProcessReport, const std::string & filter, bool overwriteFile = false);
%ignore CCopasiDataModel::getModel() const;
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
%ignore CCopasiDataModel::mpUndefined;
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

%immutable CCopasiDataModel::Global;

%catches(CCopasiException) CCopasiDataModel::newModel();
%catches(CCopasiException) CCopasiDataModel::importSBMLFromString(const std::string& sbmlDocumentText,CProcessReport* pImportHandler = NULL);
%catches(CCopasiException) CCopasiDataModel::importSBML(const std::string&,CProcessReport*);
%catches(CCopasiException) CCopasiDataModel::exportSBMLToString(CProcessReport* pExportHandler , int sbmlLevel,int sbmlVersion);
%catches(CCopasiException) CCopasiDataModel::exportSBML(const std::string& fileName, bool overwriteFile=false, int sbmlLevel = 2, int sbmlVersion = 1, bool exportIncomplete = false, CProcessReport* pExportHandler = NULL);

%include "CopasiDataModel/CCopasiDataModel.h"

%extend CCopasiDataModel
{
    bool loadModel(const std::string& fileName)
    {
        return $self->loadModel(fileName,NULL);
    };

    bool saveModel(const std::string& fileName,bool overwriteFile=false)
    {
        return $self->saveModel(fileName,NULL,overwriteFile,false);
    };

    std::string exportSBMLToString(int sbmlLevel, int sbmlVersion)
    {
        return $self->exportSBMLToString(NULL,sbmlLevel,sbmlVersion);
    };

    /* this is for backwards compatibility. */  
    std::string exportSBMLToString()
    {
        return $self->exportSBMLToString(NULL,2,1);
    };

    bool newModel()
    {
        return $self->newModel(NULL,NULL);
    };

    CReportDefinition* getReportDefinition(unsigned C_INT32 index)
    {
      return (*$self->getReportDefinitionList())[index];
    };

    CCopasiTask* getTask(unsigned C_INT32 index)
    {
      return (*$self->getTaskList())[index];
    };
};


