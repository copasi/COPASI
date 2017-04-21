// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CQMathMatrixWidget
#define COPASI_CQMathMatrixWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQMathMatrixWidget.h"
#include "copasi/UI/copasiWidget.h"

class CDataArray;

class CQMathMatrixWidget : public CopasiWidget, public Ui::CQMathMatrixWidget
{
  Q_OBJECT

public:
  CQMathMatrixWidget(QWidget* parent = 0);
  ~CQMathMatrixWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected slots:

  /// This contains code for displaying test results for symbolic differentiation
  void slotDerivButtonPressed();

protected:
  virtual bool enterProtected();
  void loadMatrices();
  void clearArrays();

  QLabel* mLabelTitle;

  const CDataArray * mpArrayAnn1;
  const CDataArray * mpArrayAnn2;
  const CDataArray * mpArrayAnn3;
};

#endif // COPASI_CQMathMatrixWidget
