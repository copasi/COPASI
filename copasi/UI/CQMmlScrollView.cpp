// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMmlScrollView.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/09/23 11:51:40 $
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

#ifdef HAVE_MML
# include "mml/qtmmlwidget.h"
#endif // HAVE_MML

///  Constructor
CQMmlScrollView::CQMmlScrollView(QWidget* parent, const char* name, Qt::WFlags fl)
//    : Q3ScrollView(parent, name, fl)
    : QScrollArea(parent)
{
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

#ifdef HAVE_MML
  mpMmlWidget = new QtMmlWidget(viewport() /*, "mpMmlWidget"*/);
  mpMmlWidget->setMinimumSize(QSize(0, 0));
  mpMmlWidget->setBaseFontPointSize(this->fontInfo().pointSize());
  mpMmlWidget->setFontName(QtMmlWidget::NormalFont, this->fontInfo().family());
  setWidget(mpMmlWidget);
#endif // HAVE_MML

//  setResizePolicy(Q3ScrollView::AutoOneFit);
  setWidgetResizable(true);
}

/// Destructor
CQMmlScrollView::~CQMmlScrollView()
{
  // no need to delete child widgets, Qt does it all for us
}

/// Function to update the MathML widget
void CQMmlScrollView::updateWidget(std::ostringstream &mml)
{
#ifdef HAVE_MML
  qDebug() << "mml.str() = " << FROM_UTF8(mml.str());
  mpMmlWidget->setContent(FROM_UTF8(mml.str()));

//  resizeContents(mpMmlWidget->sizeHint().width(), mpMmlWidget->sizeHint().height());
  mpMmlWidget->resize(mpMmlWidget->sizeHint().width(), mpMmlWidget->sizeHint().height());
  setMinimumHeight(mpMmlWidget->sizeHint().height() + 30);
#endif // HAVE_MML
}
