// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMathMatrixWidget.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/09 16:49:41 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQMATHMATRIX_H
#define CQMATHMATRIX_H

//#include <qvbox.h>
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
    CQMathMatrixWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQMathMatrixWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:

  protected:

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
