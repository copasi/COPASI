// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingWidget.h,v $
//   $Revision: 1.16 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/17 13:10:18 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQFITTINGWIDGET_H
#define CQFITTINGWIDGET_H

#include <qvariant.h>

#include "ui_CQFittingWidget.h"

#include <QHBoxLayout>

/*
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3GridLayout>
#include <QPixmap>
#include <Q3VBoxLayout>
#include "TaskWidget.h"

class CExperimentSet;
class CQFittingItemWidget;
class CCrossValidationSet;

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
 */

class CExperimentSet;
class CQFittingItemWidget;
class CCrossValidationSet;

#include "TaskWidget.h"

class CQFittingWidget : public TaskWidget, public Ui::CQFittingWidget
{
  Q_OBJECT

public:
  CQFittingWidget(QWidget* parent = 0, const char* name = 0);
  ~CQFittingWidget();

  virtual bool runTask();

public slots:
  void slotParameterNumberChanged(int number);
  void slotConstraintNumberChanged(int number);

protected:
  CQFittingItemWidget * mpCurrentList;
  CExperimentSet * mpExperimentSet;
  std::map<std::string, std::string> mExperimentKeyMap;
  CCrossValidationSet * mpCrossValidationSet;
  std::map<std::string, std::string> mCrossValidationKeyMap;

  virtual bool saveTask();
  virtual bool loadTask();
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

protected slots:

  void slotExperimentData();
  void slotPageChange(QWidget * currentPage);
  void slotCrossValidationData();

private:
  void init();
  void destroy();
};

#endif // CQFITTINGWIDGET_H
