// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQExpressionMmlWidgetStack.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/02/17 19:32:58 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQExpressionMmlWidgetStack.h"

#include <QApplication>

//#include <qvariant.h>
//#include <qtextedit.h>
//#include <qpushbutton.h>
//#include <qlayout.h>
//#include <qtooltip.h>
//#include <qwhatsthis.h>
#include <q3vbox.h>
#include <q3scrollview.h>

#include "qtUtilities.h"  // for FROM_UTF8

#ifdef HAVE_MML
#include "mml/qtmmlwidget.h"
#endif // HAVE_MML

#include "CQExpressionWidget.h"

#include "utilities/CCopasiException.h"

/*!
    Constructs a CQExpressionMmlWidgetStack as a child of 'parent', with
 name 'name' and widget flags set to 'f'.
 */

CQExpressionMmlWidgetStack::CQExpressionMmlWidgetStack(QWidget* parent, const char* name, Qt::WFlags fl)
    : Q3WidgetStack(parent, name, fl)
{
  // set
  if (!name)
    setName("CQExpressionMmlWidgetStack");

  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  // Page 1: a text edit of type CQExpressionWidget to type the mathematical formula
  mpEditExpression = new CQExpressionWidget(this, "mpEditExpression");
  addWidget(mpEditExpression, 0);
  raiseWidget(0);

#ifdef HAVE_MML

  // Page 2: a box of type QVBox, containing the MathMML ScrollView with the formula
  //         and a button to switch to the text edit (ie. back to Page 1)
  mpVBox = new Q3VBox(this, "mpVBox");
  mpVBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  mScrollView = new Q3ScrollView(mpVBox, "mmlScrollView");
  mScrollView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  addWidget(mpVBox, 1);

  mMmlWidget = new QtMmlWidget(mScrollView->viewport());
  mScrollView->addChild(mMmlWidget);

  mScrollView->setResizePolicy(Q3ScrollView::AutoOneFit);

#endif // HAVE_MML
}

/*!
    Destroys the object and frees any allocated resources
 */
CQExpressionMmlWidgetStack::~CQExpressionMmlWidgetStack()
{}

/*!
    The function to update the display widget of the mathematical expression
    by means of MathMML.
 */
void CQExpressionMmlWidgetStack::updateExpressionWidget()
{
#ifdef HAVE_MML

  // Since the mathematical expression is already validated, then we can go easily further

  std::ostringstream mml;
  std::vector<std::vector<std::string> > params;

  raiseWidget(mpVBox);

  if (mpEditExpression->text().isEmpty())
    raiseWidget(mpEditExpression);
  else
    ((CQExpressionWidget *)widget(0))->mpValidator->getExpression()->writeMathML(mml, false, 0);

  mMmlWidget->setContent(FROM_UTF8(mml.str()));
  mMmlWidget->setBaseFontPointSize(qApp->font().pointSize());
  mMmlWidget->setFontName(QtMmlWidget::NormalFont, qApp->font().family());

  mScrollView->resizeContents(mMmlWidget->sizeHint().width(), mMmlWidget->sizeHint().height());
  mScrollView->setMinimumHeight(mMmlWidget->sizeHint().height() + 30);

#endif // HAVE_MML
}

/*!
    The slot to activate the text edit of type CQExpressionWidget
    for typing a new mathematical expression or editing the existing one
 */
void CQExpressionMmlWidgetStack::slotEditExpression()
{
  // activate editor page of the Expression widget stack
  raiseWidget(mpEditExpression);
}
