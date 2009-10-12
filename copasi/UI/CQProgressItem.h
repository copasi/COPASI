// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/14 11:09:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQPROGRESSITEM_H
#define CQPROGRESSITEM_H

#include "ui_CQProgressItem.h"

#include <qvariant.h>

//#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include "utilities/CProcessReport.h"
#include "utilities/CVector.h"

class CQProgressItem : public QWidget, public Ui::CQProgressItem
{
  Q_OBJECT

public:
  CQProgressItem(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~CQProgressItem();

  virtual bool initFromProcessReportItem(CProcessReportItem * pItem);
  virtual bool process();
  virtual bool reset();

protected:
  CProcessReportItem * mpItem;

protected slots:
  virtual void languageChange();
};

#endif // CQPROGRESSITEM_H
