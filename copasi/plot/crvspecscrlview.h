/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/crvspecscrlview.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:32:40 $
   End CVS Header */

#include <qscrollview.h>

// a customised scrollview...

class CurveSpecScrollView : public QScrollView
  {
  public:
    CurveSpecScrollView(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
  };
