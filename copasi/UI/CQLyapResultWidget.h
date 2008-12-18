/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLyapResultWidget.h,v $
 $Revision: 1.5 $
 $Name:  $
 $Author: shoops $
 $Date: 2008/12/18 19:56:21 $
 End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQLYAPRESULT_H
#define CQLYAPRESULT_H

#include "UI/copasiWidget.h"
//Added by qt3to4:
#include <Q3GridLayout>
#include <QLabel>
//#include "CopasiDataModel/CCopasiDataModel.h"

class Q3GridLayout;
class QLineEdit;
class QLabel;
class Q3Table;

class CQLyapResultWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQLyapResultWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
    ~CQLyapResultWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:

  protected:
    bool loadFromBackend();

    Q3GridLayout* mWidgetLayout;

    QLabel* mLabelExponents;
    QLabel* mLabelSum;
    QLabel* mLabelDivergence;
    QLabel* mLabelComment;

    Q3Table* mTableExponents;
    QLineEdit* mLineEditSum;
    QLineEdit* mLineEditDivergence;
  };

#endif
