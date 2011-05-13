// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskBtnWidget.h,v $
//   $Revision: 1.9.2.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/13 21:46:58 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQTaskBtnWidget
#define COPASI_CQTaskBtnWidget

#include <qvariant.h>

#include "copasi/UI/ui_CQTaskBtnWidget.h"

class CQTaskBtnWidget: public QWidget, public Ui::CQTaskBtnWidget
{
  Q_OBJECT

public:
  CQTaskBtnWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);

  virtual ~CQTaskBtnWidget();

protected slots:

};

#endif // COPASI_CQTaskBtnWidget
