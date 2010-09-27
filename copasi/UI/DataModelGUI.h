// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DataModelGUI.h,v $
//   $Revision: 1.33.2.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/09/27 13:44:57 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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

class DataModelGUI : public QAbstractItemModel
{
  Q_OBJECT
private:
  IndexedTree mTree; // create the  object of the tree

  //CMathModel * mpMathModel;
  //bool mMathModelUpdateScheduled;

  QApplication *mpApp;

  COutputHandlerPlot mOutputHandlerPlot;

  void linkDataModelToGUI();

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

  bool loadModel(const std::string & fileName);
  bool createModel();
  bool saveModel(const std::string & fileName, bool overwriteFile = false);
#ifdef WITH_MERGEMODEL
  bool addModel(const std::string & fileName);
#endif

  bool updateMIRIAM(CMIRIAMResources & miriamResources);

  bool importSBMLFromString(const std::string & sbmlDocumentText);
  bool importSBML(const std::string & fileName);
  std::string exportSBMLToString();
  bool exportSBML(const std::string & fileName, bool overwriteFile , int sbmlLevel, int sbmlVersion, bool exportIncomplete, bool exportCOPASIMIRIAM = true);
  bool exportMathModel(const std::string & fileName, const std::string & filter, bool overwriteFile = false);

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
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QModelIndex findIndexFromId(int id);
  QModelIndex findIndexFromKey(const std::string& key);
  bool notify(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");

protected:
  bool insertRow(int parentId, const std::string &key);
  bool removeRow(const std::string &key);
  void changeRow(const std::string &key);

signals:
  void updateCompleteView();
  void notifyView(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");
};

#endif
