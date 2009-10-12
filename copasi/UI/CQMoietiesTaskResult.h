// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQMoietiesTaskResult.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/16 15:47:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMOIETIESTASKRESULT_H
#define CQMOIETIESTASKRESULT_H

#include "ui_CQMoietiesTaskResult.h"

#include <qvariant.h>
//Added by qt3to4:
#include <QPixmap>
//#include <Q3GridLayout>
#include <QLabel>

class QSignalMapper;
class CMoietiesTask;
/*
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GridLayout>
 */
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include "CQArrayAnnotationsWidget.h"
#include "copasiWidget.h"

class CQMoietiesTaskResult : public CopasiWidget, public Ui::CQMoietiesTaskResult
{
  Q_OBJECT

public:
  CQMoietiesTaskResult(QWidget* parent = 0, const char* name = 0);
  ~CQMoietiesTaskResult();

  void clear();
  virtual bool leave();
  void load();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

protected:
  virtual bool enterProtected();
  QPixmap mToolBtn;
  QSignalMapper * mpToolBtnMap;
  CMoietiesTask * mpMoietiesTask;

protected slots:
  virtual void languageChange();

private:
  void init();

private slots:
  void slotSave(void);
  void slotCreateGlobalQuantity(int row);
};

#endif // CQMOIETIESTASKRESULT_H
