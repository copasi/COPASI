// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CTabWidget.h,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/03 13:58:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CTABWIDGET_H
#define CTABWIDGET_H

#include <qtabwidget.h>

#include "UI/listviews.h"

#include "copasiWidget.h"

/**This class is the container for two or more widgets.
 */
class CTabWidget : public CopasiWidget
  {
  public:
    CTabWidget(const QString & label, CopasiWidget * pCopasiWidget,
               QWidget* parent = 0, const char* name = 0, WFlags f = 0);

    ~CTabWidget();

    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected:
    QTabWidget *mTabWidget;
    std::vector< CopasiWidget * > mPages;
  };

#endif // CTABWIDGET_H
