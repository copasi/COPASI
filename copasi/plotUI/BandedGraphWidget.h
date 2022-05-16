// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef BANDEDGRAPHWIDGET_H
#define BANDEDGRAPHWIDGET_H

#include <QtCore/QVariant>

#include "copasi/plotUI/ui_BandedGraphWidget.h"
#include "copasi/plotUI/CQPlotEditWidget.h"

class CDataObject;
class CModel;
class CPlotItem;

class BandedGraphWidget : public CQPlotEditWidget, public Ui::BandedGraphWidget
{
  Q_OBJECT

public:
  BandedGraphWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  ~BandedGraphWidget();

  virtual bool LoadFromCurveSpec(const CPlotItem * curve);
  virtual bool SaveToCurveSpec(CPlotItem * curve, const CPlotItem *original = NULL) const;

  /**
   * In multiple edit mode, we don't want to edit name & channels
   */
  virtual void setMultipleEditMode(bool mode);

protected:
  const CDataObject* mpObjectYone;
  const CDataObject* mpObjectYtwo;
  const CDataObject* mpObjectX;

protected slots:

  virtual void buttonPressedX();
  virtual void buttonPressedY() {buttonPressedYone();};
  void buttonPressedYone();
  void buttonPressedYtwo();

  virtual void typeChanged(int linetype);
};

#endif // BANDEDGRAPHWIDGET_H
