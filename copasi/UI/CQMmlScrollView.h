// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/*!
 \file CQMmlScrollView.h
 \brief Header file of class CQMmlScrollView
 */

#ifndef CQMMLSCROLLVIEW_H
#define CQMMLSCROLLVIEW_H

#include <sstream>   // for ostringstream

#include <QtGui/QScrollArea>

class QtMmlWidget;

/*!
   \brief The class for nicely displaying QtMmlWidget.

   This class inherits QScrollView to nicely display an object of class QtMmlWidget.
 */
class CQMmlScrollView : public QScrollArea
{
  Q_OBJECT

public:
  CQMmlScrollView(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CQMmlScrollView();

  void updateWidget(std::ostringstream &mml);

#ifdef HAVE_MML
  QtMmlWidget* mpMmlWidget;
#endif // HAVE_MML
};

#endif // CQSMMLSCROLLVIEW_H
