// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMathMatrixWidget.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/08/01 17:11:34 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQMATHMATRIX_H
#define CQMATHMATRIX_H

#include "UI/copasiWidget.h"
#include "CQArrayAnnotationsWidget.h"
#include "utilities/CAnnotatedMatrix.h"
#include "mathematics.h"

class QGridLayout;
//class QLineEdit;
class QLabel;
class QTabWidget;

class CQMathMatrixWidget : public CopasiWidget
{
  Q_OBJECT

public:
  CQMathMatrixWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CQMathMatrixWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected slots:

protected:
  virtual bool enterProtected();
  void loadMatrices();
  void clearArrays();

  QGridLayout* mWidgetLayout;

  QLabel* mLabelTitle;

  QTabWidget* mpTab;

  CQArrayAnnotationsWidget* mArrayWidget1;
  CQArrayAnnotationsWidget* mArrayWidget2;
  CQArrayAnnotationsWidget* mArrayWidget3;

  const CArrayAnnotation * mpArrayAnn1;
  const CArrayAnnotation * mpArrayAnn2;
  const CArrayAnnotation * mpArrayAnn3;
};

#endif
