// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMathMatrixWidget.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 17:52:38 $
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

#ifndef COPASI_CQMathMatrixWidget
#define COPASI_CQMathMatrixWidget

#include <QtCore/QVariant>

#include "copasi/UI/copasiWidget.h"
#include "copasi/UI/ui_CQMathMatrixWidget.h"

class CArrayAnnotation;

class CQMathMatrixWidget : public CopasiWidget, public Ui::CQMathMatrixWidget
{
  Q_OBJECT

public:
  CQMathMatrixWidget(QWidget* parent = 0);
  ~CQMathMatrixWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected slots:

protected:
  virtual bool enterProtected();
  void loadMatrices();
  void clearArrays();

  QLabel* mLabelTitle;

  const CArrayAnnotation * mpArrayAnn1;
  const CArrayAnnotation * mpArrayAnn2;
  const CArrayAnnotation * mpArrayAnn3;
};

#endif // COPASI_CQMathMatrixWidget
