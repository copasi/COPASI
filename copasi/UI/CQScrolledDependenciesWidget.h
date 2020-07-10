// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CQScrolledDependenciesWidget
#define COPASI_CQScrolledDependenciesWidget

#include <QWidget>
#include <QGridLayout>

#include <copasi/UI/copasiWidget.h>
#include "copasi/UI/ui_CQScrolledDependenciesWidget.h"
class QScrollArea;

class CQScrolledDependenciesWidget : public CopasiWidget, public Ui::CQScrolledDependenciesWidget
{
  Q_OBJECT

public:
  explicit CQScrolledDependenciesWidget(QWidget * parent = 0, const char * name = 0, Qt::WindowFlags f = Qt::WindowFlags());
  virtual ~CQScrolledDependenciesWidget();

  virtual QSize minimumSizeHint() const;

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

protected:
  virtual bool enterProtected();
};

#endif // COPASI_CQScrolledDependenciesWidget
