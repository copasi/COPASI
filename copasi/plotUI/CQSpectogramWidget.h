// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQSPECTOGRAMWIDGET_H
#define CQSPECTOGRAMWIDGET_H

#include <QtCore/QVariant>

#include "copasi/plotUI/ui_CQSpectogramWidget.h"
#include "copasi/plotUI/CQPlotEditWidget.h"

class CDataObject;
class CModel;
class CPlotItem;

class CQSpectogramWidget : public CQPlotEditWidget, public Ui::CQSpectogramWidget
{
  Q_OBJECT

public:
  CQSpectogramWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CQSpectogramWidget();

  virtual bool LoadFromCurveSpec(const CPlotItem * curve);
  virtual bool SaveToCurveSpec(CPlotItem * curve, const CPlotItem *original = NULL) const;

  /**
   * In multiple edit mode, we don't want to edit name & channels
   */
  virtual void setMultipleEditMode(bool mode);

protected:
  const CDataObject* mpObjectX;
  const CDataObject* mpObjectY;
  const CDataObject* mpObjectZ;

protected slots:

  virtual void buttonPressedX();
  virtual void buttonPressedY();
  virtual void buttonPressedZ();
};

#endif // CQSPECTOGRAMWIDGET_H
