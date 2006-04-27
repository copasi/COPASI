/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ScanScrollView.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:45 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SCANSCROLLVIEW_H
#define SCANSCROLLVIEW_H

#include <qscrollview.h>
#include "copasiWidget.h"

class ScanScrollView: public QScrollView
  {
    Q_OBJECT
  private:
    CopasiParametersWidget* mParent;
    std::vector<QWidget*>* pSelectedList;
  public:
    void setSelectedList(std::vector<QWidget*>* pNewSelectedList);
    ScanScrollView(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    virtual void contentsMousePressEvent (QMouseEvent * e);
    virtual void resizeEvent (QResizeEvent * e);
    virtual void viewportResizeEvent (QResizeEvent *e);
  };

#endif
