// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQDEPENDENCYWIDGET_H
#define CQDEPENDENCYWIDGET_H

#include <QWidget>

#include <copasi/UI/copasiWidget.h>
#include "copasi/UI/ui_CQDependencyWidget.h"

namespace Ui
{
class CQDependencyWidget;
}

enum CDependencyType
{
  COMPARTMENT = 1,
  SPECIES = 2,
  REACTION = 4,
  PARAMETERS = 8,
  EVENT = 16,
  ALL_DEPENDENCIES = REACTION | EVENT | SPECIES | PARAMETERS | COMPARTMENT,
  UNKNOWN = 128
};

class CDataObject;
class CModel;

class CQDependencyWidget : public CopasiWidget, public Ui::CQDependencyWidget
{
  Q_OBJECT

public:

  explicit CQDependencyWidget(QWidget * parent = 0, const char * name = 0, Qt::WindowFlags f = Qt::WindowFlags());
  virtual ~CQDependencyWidget();

  virtual QSize minimumSizeHint() const;

  /**
   * updates this widget from the given dependency objects
   * @param dependencies set of copasi objects to display
   * @param pModel the current model
   */
  void updateFromDependencies(std::set< const CDataObject * >& elements,
                              std::set< const CDataObject * >& dependencies, const CModel* pModel);

  /**
   * sets the width of the label
   *
   * @param width the width to set
   */
  void setLabelWidth(int width);

  /**
   * @return the width of the label
   */
  int getLabelWidth() const;

  /**
   * sets the dependency type that will be used to populate the table
   *
   * @param type the dependency type
   */
  void setDependencyType(CDependencyType type);

  /**
   * @return this widgets dependency type
   */
  CDependencyType getDependencyType() const;

  void setResizeTableToRows(bool resizeTable);
  bool getResizeTableToRows() const;

  /**
   * @return number of rows in dependency table
   */
  int getNumDependencies() const;

protected:
  /**
   * construct a string that provides more detail on where the dependency occurs
   */
  std::string getDetailsFor(const CDataObject * pObject, std::set< const CDataObject * >& elements);
  virtual void resizeEvent(QResizeEvent * pEvent);

  void resizeTable();

public slots:

  void rowDoubleClicked(int, int);

private:
  CDependencyType mType;
  const CModel* mpModel;
  bool mResizeTableToRows;
};

#endif // CQDEPENDENCYWIDGET_H
