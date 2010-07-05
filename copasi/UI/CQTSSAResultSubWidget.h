// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/04/27 16:00:44 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQTSSARESULTSUBWIDGET_H
#define CQTSSARESULTSUBWIDGET_H

#include <qvariant.h>

//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3GridLayout>
#include <QPixmap>
#include <Q3VBoxLayout>


#include <QtGui/QDialog>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <Qt3Support/Q3VBoxLayout>
#include <QtGui/QWidget>
#include <QToolButton>


#include "ui_CQTSSAResultSubWidget.h"

#include "CQArrayAnnotationsWidget.h"
#include "CQTSSATimeScaleWidget.h"

#include "CTimeSeriesTable.h"
#include "tssanalysis/CTSSATask.h"
#include "tssanalysis/CTSSAProblem.h"
#include "model/CModel.h"

class CQTSSAResultSubWidget : public CopasiWidget, public Ui::CQTSSAResultSubWidget
{
  Q_OBJECT

public:
  CQTSSAResultSubWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~CQTSSAResultSubWidget();

  CTSSATask* pTSSATask;
  CTSSAProblem* pProblem;
  CTSSAMethod* pMethod;

  CModel* pModel;
  C_INT mpIndex;
  bool mAnnot;
  void displayResult();
  void discardOldResults();

public slots:
  void changeInterval();

protected :

protected slots:
  virtual void languageChange();
  void slotTableChanged();
  void slotTimeOrStepChanged();
  void changeLabelToTime();
  void changeLabelToStep();
  void changeContents();

  void saveDataToFile();
  virtual void init();


};

#endif // CQTSSARESULTSUBWIDGET_H
