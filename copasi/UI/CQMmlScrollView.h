// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMmlScrollView.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/04/18 08:28:59 $
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

#include <qscrollview.h>
#include "qtUtilities.h" // for FROM_UTF8

class QtMmlWidget;

/*!
   \brief The class for nicely displaying QtMmlWidget.

   This class inherits QScrollView to nicely display an object of class QtMmlWidget.
 */
class CQMmlScrollView : public QScrollView
  {
    Q_OBJECT

  public:
    CQMmlScrollView(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQMmlScrollView();

    void updateWidget(std::ostringstream &mml);

    QtMmlWidget* mpMmlWidget;
  };

#endif // MMLSCROLLVIEW_H
