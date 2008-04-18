// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMmlScrollView.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/04/18 08:28:40 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/*!
 \file CQMmlScrollView.cpp
 \brief Implementation file of class CQMmlScrollView
 */

#include "CQMmlScrollView.h"

#include "mml/qtmmlwidget.h"

///  Constructor
CQMmlScrollView::CQMmlScrollView(QWidget* parent, const char* name, WFlags fl)
    : QScrollView(parent, name, fl)
{
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  mpMmlWidget = new QtMmlWidget(viewport(), "mpMmlWidget");
  mpMmlWidget->setMinimumSize(QSize(0, 0));
  mpMmlWidget->setBaseFontPointSize(this->fontInfo().pointSize());
  mpMmlWidget->setFontName(QtMmlWidget::NormalFont, this->fontInfo().family());

  addChild(mpMmlWidget);
  setResizePolicy(QScrollView::AutoOneFit);
}

/// Destructor
CQMmlScrollView::~CQMmlScrollView()
{
  // no need to delete child widgets, Qt does it all for us
}

/// Function to update the MathML widget
void CQMmlScrollView::updateWidget(std::ostringstream &mml)
{
  mpMmlWidget->setContent(FROM_UTF8(mml.str()));

  resizeContents(mpMmlWidget->sizeHint().width(), mpMmlWidget->sizeHint().height());
  setMinimumHeight(mpMmlWidget->sizeHint().height() + 30);
}
