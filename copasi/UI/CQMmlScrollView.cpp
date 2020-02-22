// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

/*!
 \file CQMmlScrollView.cpp
 \brief Implementation file of class CQMmlScrollView
 */

#include <QApplication>

#include "copasi/copasi.h"
#include "qtUtilities.h"

#ifdef HAVE_MML
# include <qtmmlwidget.h>
#endif // HAVE_MML

#include "CQMmlScrollView.h"

///  Constructor
CQMmlScrollView::CQMmlScrollView(QWidget* parent, const char* /* name */, Qt::WindowFlags /* fl */)
  : QScrollArea(parent)
{
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

#ifdef HAVE_MML
  mpMmlWidget = new QtMmlWidget();
  mpMmlWidget->setObjectName(QString::fromUtf8("mpMmlWidget"));
  QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(mpMmlWidget->sizePolicy().hasHeightForWidth());
  mpMmlWidget->setSizePolicy(sizePolicy);
  mpMmlWidget->setMinimumSize(QSize(0, 0));
  setWidget(mpMmlWidget);
#endif // HAVE_MML
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
  mpMmlWidget->setContent(FROM_UTF8(mml.str()));
  mpMmlWidget->setBaseFontPointSize(qApp->font().pointSize());
  mpMmlWidget->setFontName(QtMmlWidget::NormalFont, qApp->font().family());
  mpMmlWidget->resize(mpMmlWidget->sizeHint().width(), mpMmlWidget->sizeHint().height());
#endif // HAVE_MML
}
