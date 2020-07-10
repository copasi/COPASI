// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQDEPENDENCIESWIDGET_H
#define CQDEPENDENCIESWIDGET_H

#include <QWidget>
#include <QGridLayout>

#include <copasi/UI/copasiWidget.h>
#include <copasi/UI/CQDependencyWidget.h>
#include "copasi/UI/ui_CQDependenciesWidget.h"

class QScrollArea;

class CQDependenciesWidget : public CopasiWidget, public Ui::CQDependenciesWidget
{
  Q_OBJECT

public:
  explicit CQDependenciesWidget(QWidget * parent = 0, const char * name = 0, Qt::WindowFlags f = Qt::WindowFlags());
  virtual ~CQDependenciesWidget();

  /**
   * Initializes all the dependency widgets for the specified types
   *
   * @param types combination of various CDependencyType elements
   */
  void setVisibleDependencies(int types);

  /**
   * @return current selection of dependency elements
   */
  int getVisibleDependencies() const;

  /**
   * sets the width of all eneabled dependency widgets
   * @param width the width to be set
   */
  void setLabelWidth(int width);

  /**
   * @return the width of the first enabled dependency widget
   */
  int getLabelWidth() const;

  /**
   * loads data from the given object
   *
   * @param pObject the object whose dependencies to display
   */
  void loadFrom(const CDataObject *pObject);

  void setResizeTableToRows(bool resizeTable);

  bool getResizeTableToRows() const;

  bool haveDependencies() const;

  int getNumDependencies() const;

  virtual bool enterProtected();

private:
  int mVisibleModes;
};

#endif // CQDEPENDENCIESWIDGET_H
