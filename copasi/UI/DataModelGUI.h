// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DataModelGUI.h,v $
//   $Revision: 1.34 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:37:54 $
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

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <qobject.h>
#include <qapplication.h>

#include "UI/Tree.h"
#include "plotUI/COutputHandlerPlot.h"
#include "listviews.h"


//class CMathModel;
class QTimer;
class CMIRIAMResources;
class CQThread;
class CProgressBar;

class DataModelGUI : public QAbstractItemModel
{
  Q_OBJECT
private:
  void linkDataModelToGUI();

  IndexedNode* getItem(const QModelIndex &index) const;

  QString getNameWithObjectNo(const IndexedNode *node) const;

public:
  DataModelGUI(QObject* parent);

  void populateData();

  void updateCompartments();
  void updateMetabolites();
  void updateReactions();
  void updateModelValues();
  void updateFunctions();
  void updateEvents();
  void updateReportDefinitions();
  void updatePlots();
  void updateAllEntities();

  const IndexedNode * getRootNode() const;
  const IndexedNode * getNode(int id);

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

  QVariant data(const QModelIndex &index, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const;
  QModelIndex parent(const QModelIndex &index) const;
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QModelIndex findIndexFromId(size_t id);
  QModelIndex findIndexFromKey(const std::string& key);
  size_t getId(const QModelIndex &index) const;
  std::string getKey(const QModelIndex &index) const;
  bool notify(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");

  void registerListView(ListViews * pListView);
  void deregisterListView(ListViews * pListView);

  void refreshInitialValues();
  void buildChangedObjects();
  void setFramework(int framework);
  void updateMIRIAMResourceContents();
  void commit();


protected:
  bool insertRow(int parentId, const std::string &key);
  bool removeRow(const std::string &key);

private:
  void threadFinished();

signals:
  void updateCompleteView();
  void notifyView(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");
  void finished(bool success);

private:
  IndexedTree mTree; // create the  object of the tree
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
