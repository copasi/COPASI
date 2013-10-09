// Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQ_PLOT_EDIT_WIDGET_H
#define CQ_PLOT_EDIT_WIDGET_H

#include <QtGui/QWidget>

class CPlotItem;
class CModel;

class CQPlotEditWidget : public QWidget
{
public:
  CQPlotEditWidget(QWidget* parent = NULL, Qt::WindowFlags fl = 0);
  virtual ~CQPlotEditWidget();

  virtual bool LoadFromCurveSpec(const CPlotItem * curve) = 0;
  virtual bool SaveToCurveSpec(CPlotItem * curve, const CPlotItem *original = NULL) const = 0;
  virtual void setModel(const CModel * model);

  /**
   * In multiple edit mode, we don't want to edit name & channels
   */
  virtual void setMultipleEditMode(bool mode) = 0;

protected:
  const CModel* mpModel;
};

#endif //CQ_PLOT_EDIT_WIDGET_H
