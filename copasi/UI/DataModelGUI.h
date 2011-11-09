// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DataModelGUI.h,v $
//   $Revision: 1.36 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/11/09 15:08:57 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef DATAMODELGUI_H
#define DATAMODELGUI_H

#include <QVariant>

#include <QtCore/QObject>
#include <qapplication.h>

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
  bool addModel(const std::string & fileName);
#endif

  void importSBML(const std::string & fileName);
  void exportSBML(const std::string & fileName, bool overwriteFile , int sbmlLevel, int sbmlVersion, bool exportIncomplete, bool exportCOPASIMIRIAM = true);
  void importSBMLFromString(const std::string & sbmlDocumentText);
  void exportSBMLToString(std::string & sbmlDocumentText);
  void exportMathModel(const std::string & fileName, const std::string & filter, bool overwriteFile = false);
#ifdef CELLDESIGNER_IMPORT
  void importCellDesigner();
#endif /* CELLDESIGNER_IMPORT */

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

public:
  bool updateMIRIAM(CMIRIAMResources & miriamResources);

  COutputDefinitionVector & getPlotDefinitionList();

  //CMathModel * getMathModel() {return mpMathModel;}
  //bool updateMathModel();
  //bool scheduleMathModelUpdate(const bool & update = true);

  void setQApp(QApplication* app);
  QApplication* getQApp() const;

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
  void notifyView(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");
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
};

#endif
