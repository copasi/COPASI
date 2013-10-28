// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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
#include <QtGui/QApplication>

#include "copasi/plotUI/COutputHandlerPlot.h"
#include "copasi/UI/listviews.h"

//class CMathModel;
class QTimer;
class CMIRIAMResources;
class CQThread;
class CProgressBar;
class CQBrowserPaneDM;

class DataModelGUI: public QObject
{
  Q_OBJECT
private:
  void linkDataModelToGUI();

public:
  DataModelGUI(QObject * parent);
  virtual ~DataModelGUI();

  bool createModel();
  void loadModel(const std::string & fileName);
  void saveModel(const std::string & fileName, bool overwriteFile = false);

#ifdef WITH_MERGEMODEL
  void addModel(const std::string & fileName);
  void addModelRun();
#endif

  void saveFunctionDB(const std::string & fileName);
  void loadFunctionDB(const std::string & fileName);

  void importSBML(const std::string & fileName);
  void exportSBML(const std::string & fileName, bool overwriteFile , int sbmlLevel, int sbmlVersion, bool exportIncomplete, bool exportCOPASIMIRIAM = true);
  void importSBMLFromString(const std::string & sbmlDocumentText);
  void exportSBMLToString(std::string & sbmlDocumentText);
  void exportMathModel(const std::string & fileName, const std::string & filter, bool overwriteFile = false);
  void importCellDesigner();

  //TODO SEDML
#ifdef COPASI_SEDML
  void exportSEDML(const std::string & fileName, bool overwriteFile , int sedmlLevel, int sedmlVersion, bool exportIncomplete, bool exportCOPASIMIRIAM = true);
  void exportSEDMLToString(std::string & sedmlDocumentText);
  void importSEDML(const std::string & fileName);
  void importSEDMLFromString(const std::string & sedmlDocumentText);

  void importSEDMLRun();
  void exportSEDMLRun();
  void importSEDMLFromStringRun();
  void exportSEDMLToStringRun();
#endif

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
#ifdef WITH_MERGEMODEL
  void addModelFinished();
#endif

  //TODO SEDML
#ifdef COPASI_SEDML
  void importSEDMLFinished();
  void exportSEDMLFinished();
  void importSEDMLFromStringFinished();
  void exportSEDMLToStringFinished();
#endif

public:
  bool updateMIRIAM(CMIRIAMResources & miriamResources);

  COutputDefinitionVector & getPlotDefinitionList();

  //CMathModel * getMathModel() {return mpMathModel;}
  //bool updateMathModel();
  //bool scheduleMathModelUpdate(const bool & update = true);

  bool notify(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");

  void registerListView(ListViews * pListView);
  void deregisterListView(ListViews * pListView);

  void refreshInitialValues();
  void buildChangedObjects();
  void setFramework(int framework);
  void updateMIRIAMResourceContents();
  void commit();

protected:
private:
  void threadFinished();

signals:
  void updateCompleteView();
  void notifyView(ListViews::ObjectType objectType, ListViews::Action action, std::string key = "");
  void finished(bool success);

private:
  QApplication *mpApp;
  COutputHandlerPlot mOutputHandlerPlot;
  std::set< ListViews * > mListViews;
  int mFramework;
  std::vector< Refresh * > mUpdateVector;
  std::set< const CCopasiObject * > mChangedObjects;

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

  //TODO SEDML
#ifdef COPASI_SEDML
  std::string mSEDMLImportString;
  std::string * mpSEDMLExportString;
  int mSEDMLLevel;
  int mSEDMLVersion;
  bool mSEDMLExportIncomplete;
  bool mSEDMLExportCOPASIMIRIAM;
#endif
};

#endif
