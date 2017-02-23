// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQDEPENDENCIESWIDGET_H
#define CQDEPENDENCIESWIDGET_H

#include <QWidget>
#include <QGridLayout>

#include <copasi/UI/copasiWidget.h>
#include <copasi/UI/CQDependencyWidget.h>

namespace Ui
{
class CQDependenciesWidget;
}

class CQDependenciesWidget : public CopasiWidget
{
  Q_OBJECT

public:
  explicit CQDependenciesWidget(QWidget * parent = 0, const char * name = 0, Qt::WFlags f = 0);
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
  void loadFrom(CCopasiObject *pObject);

  void setResizeTableToRows(bool resizeTable);

  bool getResizeTableToRows() const;

  bool haveDependencies() const;

  int getNumDependencies() const;

protected:
  /**
   * removes the given dependency widget from the current layout
   *
   * @param pWidget the widget to remove
   * @return NULL
   */
  CQDependencyWidget* clearWidget(CQDependencyWidget* pWidget);

  /**
   * adds a new dependency widget of the given type to the current layout
   *
   * @param type CDependencyType to add
   *
   * @return pointer to the newly constructed widget
   */
  CQDependencyWidget *addWidget(CDependencyType type);

  virtual bool enterProtected();

private:
  Ui::CQDependenciesWidget *ui;
  int mVisibleModes;
  CQDependencyWidget* mpCompartmentWidget;
  CQDependencyWidget* mpSpeciesWidget;
  CQDependencyWidget* mpParameterWidget;
  CQDependencyWidget* mpReactionWidget;
  CQDependencyWidget* mpEventWidget;
  //QGridLayout* mpLayout;
  QVBoxLayout* mpLayout;
};

#endif // CQDEPENDENCIESWIDGET_H
