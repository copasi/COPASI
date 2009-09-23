// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMmlScrollView.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/09/23 11:51:40 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/*!
 \file CQMmlScrollView.h
 \brief Header file of class CQMmlScrollView
 */

#ifndef MMLSCROLLVIEW_H
#define MMLSCROLLVIEW_H

#include <sstream>   // for ostringstream

//#include <q3scrollview.h>
#include <QScrollArea>
#include "qtUtilities.h" // for FROM_UTF8
#include <QtDesigner/QDesignerExportWidget>

class QtMmlWidget;

/*!
   \brief The class for nicely displaying QtMmlWidget.

   This class inherits QScrollView to nicely display an object of class QtMmlWidget.
 */
//class CQMmlScrollView : public Q3ScrollView
class QDESIGNER_WIDGET_EXPORT CQMmlScrollView : public QScrollArea
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

#endif // MMLSCROLLVIEW_H
