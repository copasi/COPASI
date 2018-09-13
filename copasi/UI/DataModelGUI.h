// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef DATAMODELGUI_H
#define DATAMODELGUI_H

#include <QtCore/QVariant>

#include <QtCore/QObject>
#include <QApplication>

#include "copasi/UI/listviews.h"

//class CMathModel;
class QTimer;
class CMIRIAMResources;
class CQThread;
class CProgressBar;
class CQBrowserPaneDM;
class QNetworkReply;
class COutputDefinitionVector;
class COutputHandlerPlot;
class CDataModel;

#include "copasi/core/CCore.h"
#include "copasi/core/CCommonName.h"
#include "copasi/undo/CUndoStack.h"

class DataModelGUI: public QObject
{
  Q_OBJECT
private:
  void linkDataModelToGUI();

public:
  DataModelGUI(QObject * parent, CDataModel * pDataModel);
  virtual ~DataModelGUI();

  bool createModel();
  void loadModel(const std::string & fileName);
  void saveModel(const std::string & fileName, bool overwriteFile = false);

  void addModel(const std::string & fileName);
  void addModelRun();

  void saveFunctionDB(const std::string & fileName);
  void loadFunctionDB(const std::string & fileName);

  void saveModelParameterSets(const std::string & fileName);
  void loadModelParameterSets(const std::string & fileName);


  void importSBML(const std::string & fileName);
  void exportSBML(const std::string & fileName, bool overwriteFile , int sbmlLevel, int sbmlVersion, bool exportIncomplete, bool exportCOPASIMIRIAM = true);
  void importSBMLFromString(const std::string & sbmlDocumentText);
  void exportSBMLToString(std::string & sbmlDocumentText);
  void exportMathModel(const std::string & fileName, const std::string & filter, bool overwriteFile = false);
  void importCellDesigner();

  void openCombineArchive(const std::string & fileName);
  void exportCombineArchive(const std::string & fileName, bool overwriteFile = false);
  void openCombineArchiveRun();
  void exportCombineArchiveRun();

  // SEDML
  void exportSEDML(const std::string & fileName, bool overwriteFile , int sedmlLevel, int sedmlVersion, bool exportIncomplete, bool exportCOPASIMIRIAM = true);
  void exportSEDMLToString(std::string & sedmlDocumentText);
  void importSEDML(const std::string & fileName);
  void importSEDMLFromString(const std::string & sedmlDocumentText);

  void importSEDMLRun();
  void exportSEDMLRun();
  void importSEDMLFromStringRun();
  void exportSEDMLToStringRun();

  void loadModelRun();
  void saveModelRun();
  void importSBMLRun();
  void exportSBMLRun();
  void importSBMLFromStringRun();
  void exportSBMLToStringRun();
  void exportMathModelRun();

public slots:
  void loadModelFinished();
  void saveModelFinished();
  void importSBMLFinished();
  void exportSBMLFinished();
  void importSBMLFromStringFinished();
  void exportSBMLToStringFinished();
  void exportMathModelFinished();
  void importCombineFinished();
  void exportCombineFinished();

  void addModelFinished();

  void miriamDownloadFinished(QNetworkReply*);
  void miriamDownloadProgress(qint64 received, qint64 total);

  //SEDML
  void importSEDMLFinished();
  void exportSEDMLFinished();
  void importSEDMLFromStringFinished();
  void exportSEDMLToStringFinished();

public:
  bool updateMIRIAM(CMIRIAMResources & miriamResources);

  COutputDefinitionVector & getPlotDefinitionList();

  //CMathModel * getMathModel() {return mpMathModel;}
  //bool updateMathModel();
  //bool scheduleMathModelUpdate(const bool & update = true);

  bool notify(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn = std::string());
  void notifyChanges(const CUndoData::ChangeSet & changes);

  void registerListView(ListViews * pListView);
  void deregisterListView(ListViews * pListView);

  void refreshInitialValues();
  void setFramework(int framework);
  void updateMIRIAMResourceContents();
  void commit();

protected:
private:
  void threadFinished();

signals:
  void updateCompleteView();
  void notifyView(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  void finished(bool success);

private:
  CDataModel * mpDataModel;
  COutputHandlerPlot * mpOutputHandlerPlot;
  std::set< ListViews * > mListViews;
  int mFramework;

  CQThread * mpThread;
  CProgressBar * mpProgressBar;
  bool mSuccess;
  std::string mSBMLImportString;
  std::string * mpSBMLExportString;
  std::string mFileName;
  bool mOverWrite;
  int mSBMLLevel;
  int mSBMLVersion;
  bool mSBMLExportIncomplete;
  bool mSBMLExportCOPASIMIRIAM;
  std::string mExportFormat;
  CMIRIAMResources* mpMiriamResources;
  unsigned int mDownloadedBytes;
  unsigned int mDownloadedTotalBytes;
  size_t mUpdateItem;

  //SEDML
  std::string mSEDMLImportString;
  std::string * mpSEDMLExportString;
  int mSEDMLLevel;
  int mSEDMLVersion;
  bool mSEDMLExportIncomplete;
  bool mSEDMLExportCOPASIMIRIAM;
};

#endif
