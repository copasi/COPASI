/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ScanScrollView.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/22 15:16:19 $
   End CVS Header */

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
