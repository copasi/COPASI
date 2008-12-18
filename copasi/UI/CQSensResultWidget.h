// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSensResultWidget.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:10 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQSENSRESULT_H
#define CQSENSRESULT_H

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
//class QTable;

class QTabWidget;

class CQSensResultWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQSensResultWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
    ~CQSensResultWidget();

    void newResult();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:

  protected:
    //bool loadFromBackend();
    void clearArrays();

    Q3GridLayout* mWidgetLayout;

    QLabel* mLabelTitle;

    QTabWidget* mpTab;

    CQArrayAnnotationsWidget* mArrayWidget;
    CQArrayAnnotationsWidget* mArrayWidgetScaled;
    CQArrayAnnotationsWidget* mArrayWidgetCollapsed;

    const CArrayAnnotation * mpResult;
    const CArrayAnnotation * mpScaledResult;
    const CArrayAnnotation * mpCollapsedResult;
  };

#endif
