// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMmlScrollView.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:42 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QScrollArea>

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
