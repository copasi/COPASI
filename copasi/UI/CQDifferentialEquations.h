// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQDIFFERENTIALEQUATIONS_H
#define CQDIFFERENTIALEQUATIONS_H

#include <QtCore/QVariant>
#include <QPixmap>
#include <QLabel>

class QtMmlWidget;

#include <sstream>
#include "copasiWidget.h"

#ifdef fatalError
#undef fatalError
#endif // fatalError

#include "copasi/UI/ui_CQDifferentialEquations.h"

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
  std::ostringstream mml;
  virtual bool enterProtected();

protected slots:

private:
  void init();
  virtual void newFunction();
  virtual void saveMML(const QString& filename);
  virtual void savePNG(const QString& filename);
  virtual void savePDF(const QString& filename);
  virtual void saveTeX(const QString& filename);
};

#endif // CQDIFFERENTIALEQUATIONS_H
