// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQ_PLOT_EDIT_WIDGET_H
#define CQ_PLOT_EDIT_WIDGET_H

#include <QWidget>

class CModel;
class CPlotItem;

class CQPlotEditWidget : public QWidget
{
public:
  CQPlotEditWidget(QWidget* parent = NULL, Qt::WindowFlags fl = Qt::WindowFlags());
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
