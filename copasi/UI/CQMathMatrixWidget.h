// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMathMatrixWidget.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/16 15:47:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQMATHMATRIX_H
#define CQMATHMATRIX_H

//#include <qvbox.h>
#include "UI/copasiWidget.h"
#include "CQArrayAnnotationsWidget.h"
#include "utilities/CAnnotatedMatrix.h"
#include "mathematics.h"
//Added by qt3to4:
#include <Q3GridLayout>
#include <QLabel>

class Q3GridLayout;
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

  Q3GridLayout* mWidgetLayout;

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
