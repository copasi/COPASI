/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MyTable.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/08/10 13:58:14 $
   End CVS Header */

#ifndef MY_TABLE_H
#define MY_TABLE_H

#include "qtable.h" 
//#include "StretchTable.h"

/*
 Table class to support a signal for delete key (and popups eventually)
 */
class MyTable: public QTable
  {
    Q_OBJECT

  public:
    MyTable (QWidget * parent = 0, const char * name = 0);
    //void mousePressEvent(QMouseEvent *mpe);
    void keyPressEvent (QKeyEvent * e);

  signals:
    void delKeyPressed();
  };

#endif
