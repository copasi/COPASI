// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQDifferentialEquations.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/06/19 08:27:46 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQDIFFERENTIALEQUATIONS_H
#define CQDIFFERENTIALEQUATIONS_H

#include <qvariant.h>
//Added by qt3to4:
#include <QPixmap>
#include <Q3GridLayout>
#include <Q3VBoxLayout>
#include <QLabel>

class QtMmlWidget;
/*
#include <Qt3Support/Q3ScrollView>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QComboBox>
#include <Qt3Support/Q3GridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
 */
#include <q3scrollview.h>
#include <sstream>
#include "copasiWidget.h"
#include "Qt3Support/Q3ScrollView"

#include "ui_CQDifferentialEquations.h"

class CQDifferentialEquations : public CopasiWidget, public Ui::CQDifferentialEquations
{
  Q_OBJECT

public:
  CQDifferentialEquations(QWidget* parent = 0, const char* name = 0);
  ~CQDifferentialEquations();

  virtual bool enter(const std::string &);

public slots:
  virtual void slotUpdateWidget();
  virtual void slotSave();

protected:
  QtMmlWidget * mpMMLWidget;
  std::ostringstream mml;

protected slots:
  virtual void languageChange();

private:
  void init();
  virtual void newFunction();
  virtual void saveMML(const QString filename);
  virtual void saveTeX(const QString filename);
};

#endif // CQDIFFERENTIALEQUATIONS_H
