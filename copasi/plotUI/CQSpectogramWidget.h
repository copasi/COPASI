// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQSPECTOGRAMWIDGET_H
#define CQSPECTOGRAMWIDGET_H

#include <QtCore/QVariant>

#include "copasi/plotUI/ui_CQSpectogramWidget.h"
#include "copasi/plotUI/CQPlotEditWidget.h"

class CCopasiObject;
class CModel;
class CPlotItem;

class CQSpectogramWidget : public CQPlotEditWidget, public Ui::CQSpectogramWidget
{
  Q_OBJECT

public:
  CQSpectogramWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~CQSpectogramWidget();

  virtual bool LoadFromCurveSpec(const CPlotItem * curve);
  virtual bool SaveToCurveSpec(CPlotItem * curve, const CPlotItem *original = NULL) const;

  /**
   * In multiple edit mode, we don't want to edit name & channels
   */
  virtual void setMultipleEditMode(bool mode);

protected:
  const CCopasiObject* mpObjectX;
  const CCopasiObject* mpObjectY;
  const CCopasiObject* mpObjectZ;

protected slots:

  virtual void buttonPressedX();
  virtual void buttonPressedY();
  virtual void buttonPressedZ();
};

#endif // CQSPECTOGRAMWIDGET_H
