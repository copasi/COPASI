// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/********************************************************
 Author: Liang Xu
 Version : 1.xx  <first>
 Description:
 Date: 04/03
 Comment : CopasiWidget: Provide base class for all widget: for resizable/minimize
 Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#ifndef COPASI_WIDGET_H
#define COPASI_WIDGET_H

#include <QWidget>

#include "copasi/UI/listviews.h"

class DataModelGUI;
class QResizeEvent;
class ListViews;
class CDataModel;
class CQBaseDataModel;
class CDataObject;
class CQSortFilterProxyModel;

#include "copasi/core/CCore.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/undo/CUndoStack.h"

class CopasiWidget : public QWidget
{
  Q_OBJECT

public:
  CopasiWidget(QWidget *parent = 0, const char *name = 0, Qt::WindowFlags = Qt::WindowFlags());

  /**
   * leaves the widget and enters it again
   */
  virtual void refresh();

  bool enter(const CCommonName & cn);
  bool update(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  bool leave();

  virtual void setFramework(int framework);
  bool getIgnoreUpdates();
  void setIgnoreUpdates(bool v);
  CDataModel *getDataModel() const;

  /**
   * @return the pointer to the current object
   */
  const CDataObject * getObject() const;

  /**
   * This method returns the data model from all the overview widgets.
   * @return data model of this widget (or NULL if it does not have one)
   */
  virtual CQBaseDataModel* getCqDataModel();

  static void setFilterExpression(CQSortFilterProxyModel * model, bool empty, QString Filter);

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

  void initContext();

  ListViews *mpListView;
  CDataObject *mpObject;
  CDataModel *mpDataModel;
  ListViews::ObjectType mObjectType;
  CRegisteredCommonName mObjectCN;

  bool mIgnoreUpdates;
  int mFramework;

private:
  CCommonName mOldCN;

protected slots:
  virtual bool protectedNotify(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn = std::string());

public slots:
  virtual void slotNotifyChanges(const CUndoData::CChangeSet & changes);
};

#endif // !defined(COPASI_WIDGET_H)
