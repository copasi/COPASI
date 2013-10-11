// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef HISTOWIDGET_H
#define HISTOWIDGET_H

#include <QtCore/QVariant>

#include "copasi/plotUI/ui_HistoWidget.h"
#include "copasi/plotUI/CQPlotEditWidget.h"

class CCopasiObject;
class CModel;
class CPlotItem;

class HistoWidget : public CQPlotEditWidget, public Ui::HistoWidget
{
  Q_OBJECT

public:
  HistoWidget(QWidget* parent = 0, Qt::WindowFlags fl = 0);
  ~HistoWidget();

  virtual bool LoadFromCurveSpec(const CPlotItem * curve);
  virtual bool SaveToCurveSpec(CPlotItem * curve, const CPlotItem *original = NULL) const;

  /**
   * In multiple edit mode, we don't want to edit name & channels
   */
  virtual void setMultipleEditMode(bool mode);

protected:
  const CCopasiObject* mpObjectX;

protected slots:

  virtual void buttonPressedX();
};

#endif // HISTOWIDGET_H
