// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/curve2dwidget.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/15 17:04:47 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CURVE2DWIDGET_H
#define CURVE2DWIDGET_H

#include "copasi/plotUI/ui_curve2dwidget.h"

class CCopasiObject;
class CModel;
class CPlotItem;

class Curve2DWidget : public QWidget, public Ui::Curve2DWidget
{
  Q_OBJECT

public:
  Curve2DWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~Curve2DWidget();

  virtual bool LoadFromCurveSpec(const CPlotItem * curve);
  virtual bool SaveToCurveSpec(CPlotItem * curve) const;
  virtual void setModel(const CModel * model);

protected:
  const CCopasiObject* mpObjectY;
  const CCopasiObject* mpObjectX;
  const CModel* mpModel;

protected slots:

  virtual void buttonPressedX();
  virtual void buttonPressedY();
};

#endif // CURVE2DWIDGET_H
