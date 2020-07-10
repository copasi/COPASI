// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CURVE2DWIDGET_H
#define CURVE2DWIDGET_H

#include "copasi/plotUI/CQPlotEditWidget.h"
#include "copasi/plotUI/ui_curve2dwidget.h"

class CDataObject;
class CModel;
class CPlotItem;

class Curve2DWidget : public CQPlotEditWidget, public Ui::Curve2DWidget
{
  Q_OBJECT

public:
  Curve2DWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  ~Curve2DWidget();

  virtual bool LoadFromCurveSpec(const CPlotItem * curve);
  virtual bool SaveToCurveSpec(CPlotItem * curve, const CPlotItem *original = NULL) const;

  /**
   * In multiple edit mode, we don't want to edit name & channels
   */
  virtual void setMultipleEditMode(bool mode);

protected:
  const CDataObject* mpObjectY;
  const CDataObject* mpObjectX;

protected slots:

  virtual void buttonPressedX();
  virtual void buttonPressedY();
  virtual void typeChanged(int linetype);
};

#endif // CURVE2DWIDGET_H
