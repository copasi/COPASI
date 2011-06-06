// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQDifferentialEquations.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/06/06 16:14:05 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQDIFFERENTIALEQUATIONS_H
#define CQDIFFERENTIALEQUATIONS_H

#include <qvariant.h>
#include <QPixmap>
#include <QLabel>

class QtMmlWidget;

#include <sstream>
#include "copasiWidget.h"

#include "ui_CQDifferentialEquations.h"

class CQDifferentialEquations : public CopasiWidget, public Ui::CQDifferentialEquations
{
  Q_OBJECT

public:
  CQDifferentialEquations(QWidget* parent = 0, const char* name = 0);
  ~CQDifferentialEquations();

public slots:
  virtual void slotUpdateWidget();
  virtual void slotSave();

protected:
  QtMmlWidget * mpMMLWidget;
  std::ostringstream mml;
  virtual bool enterProtected();

protected slots:

private:
  void init();
  virtual void newFunction();
  virtual void saveMML(const QString filename);
  virtual void saveTeX(const QString filename);
};

#endif // CQDIFFERENTIALEQUATIONS_H
