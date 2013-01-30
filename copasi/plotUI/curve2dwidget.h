// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CURVE2DWIDGET_H
#define CURVE2DWIDGET_H

#include "copasi/plotUI/CQPlotEditWidget.h"
#include "copasi/plotUI/ui_curve2dwidget.h"

class CCopasiObject;
class CModel;
class CPlotItem;

class Curve2DWidget : public CQPlotEditWidget, public Ui::Curve2DWidget
{
  Q_OBJECT

public:
  Curve2DWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~Curve2DWidget();

  virtual bool LoadFromCurveSpec(const CPlotItem * curve);
  virtual bool SaveToCurveSpec(CPlotItem * curve, const CPlotItem *original = NULL) const;

#if USE_NEW_PLOTSUBWIDGET
  /**
   * In multiple edit mode, we don't want to edit name & channels
   */
  virtual void setMultipleEditMode(bool mode);
#endif

protected:
  const CCopasiObject* mpObjectY;
  const CCopasiObject* mpObjectX;

protected slots:

  virtual void buttonPressedX();
  virtual void buttonPressedY();
  virtual void typeChanged(int linetype);
};

#endif // CURVE2DWIDGET_H
