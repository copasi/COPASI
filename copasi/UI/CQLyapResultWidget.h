/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLyapResultWidget.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/10/28 00:20:16 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQLYAPRESULT_H
#define CQLYAPRESULT_H

#include "UI/copasiWidget.h"
//#include "CopasiDataModel/CCopasiDataModel.h"

class QGridLayout;
class QLineEdit;
class QLabel;
class QTable;

class CQLyapResultWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQLyapResultWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQLyapResultWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:

  protected:
    bool loadFromBackend();

    QGridLayout* mWidgetLayout;

    QLabel* mLabelExponents;
    QLabel* mLabelSum;
    QLabel* mLabelDivergence;
    QLabel* mLabelComment;

    QTable* mTableExponents;
    QLineEdit* mLineEditSum;
    QLineEdit* mLineEditDivergence;
  };

#endif
