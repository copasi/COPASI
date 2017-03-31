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

#include <QtGui/QWidget>

#include "copasi/UI/listviews.h"

class DataModelGUI;
class QResizeEvent;
class ListViews;
class CCopasiDataModel;
class CCopasiObject;
class QUndoStack;

class CopasiWidget : public QWidget
{
  Q_OBJECT

public:
  CopasiWidget(QWidget * parent = 0, const char * name = 0, Qt::WFlags f = 0);
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

  /**
   * leaves the widget and enters it again
   */
  virtual void refresh();

  bool enter(const std::string & key);
  virtual void setFramework(int framework);
  bool getIgnoreUpdates();
  void setIgnoreUpdates(bool v);
  CCopasiDataModel * getDataModel() const;

  void setUndoStack(QUndoStack* undoStack);
  QUndoStack* getUndoStack();

  /**
   * @return the current key of the widget
   */
  const std::string& getKey() const;

  /**
   * @return the pointer to the current object
   */
  const CCopasiObject* getObject() const;

protected:
  virtual bool enterProtected();

  QUndoStack *mpUndoStack;

  ListViews * mpListView;
  std::string mKey;
  CCopasiObject * mpObject;
  CCopasiDataModel * mpDataModel;

  bool mIgnoreUpdates;
  int mFramework;

protected slots:
  virtual bool protectedNotify(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");
};

#endif // !defined(COPASI_WIDGET_H)
