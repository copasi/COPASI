// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskMethodWidget.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/01/06 19:13:44 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQTaskMethodWidget
#define COPASI_CQTaskMethodWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQTaskMethodWidget.h"

class CCopasiTask;
class CCopasiMethod;

class CQTaskMethodWidget: public QWidget, public Ui::CQTaskMethodWidget
{
  Q_OBJECT

public:
  CQTaskMethodWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);

  virtual ~CQTaskMethodWidget();

  void setTask(CCopasiTask * pTask);

  void setValidMethods(const unsigned int * validMethods);

  void showMethodParameters(const bool & show);

  bool loadMethod();

  bool saveMethod();


protected slots:

  void changeMethod(int);

protected:
  CCopasiTask * mpTask;
  CCopasiMethod * mpMethod;
  bool mShowMethods;
  bool mShowMethodParameters;
};

#endif // COPASI_CQTaskMethodWidget
