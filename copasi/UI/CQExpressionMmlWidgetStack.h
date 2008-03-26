// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQExpressionMmlWidgetStack.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/03/26 02:42:42 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEXPRESSIONMMLWIDGETSTACK_H
#define CQEXPRESSIONMMLWIDGETSTACK_H

//#include <qvariant.h>
//#include <qwidget.h>
#include <qwidgetstack.h>

class QVBox;
//class QVBoxLayout;
//class QHBoxLayout;
//class QGridLayout;
//class QSpacerItem;
//class QTextEdit;
//class QPushButton;
class CQExpressionWidget;
class QScrollView;

class QtMmlWidget;

/*!
   \brief The class for editing and displaying a mathematical expression.

   This class inherits QWidgetStack to provide an ability for editing and displaying
   a mathematical expression by switching between CQExpressionWidget and QtMMLWidget.
 */

class CQExpressionMmlWidgetStack : public QWidgetStack
  {
    Q_OBJECT

  public:
    /// Constructor
    CQExpressionMmlWidgetStack(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    /// Destructor
    ~CQExpressionMmlWidgetStack();
    /// Update the mathematical expression widget
    void updateExpressionWidget();

    CQExpressionWidget* mpEditExpression;

    QScrollView *mScrollView;
    QtMmlWidget *mMmlWidget;

    QVBox *mpVBox;

  private slots:
    /// Slot for being activated whenever Edit Expression button is clicked
    void slotEditExpression();
  };

#endif // CQExpressionMmlWidgetStack_H
