/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/MyTable.h,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/08/12 16:02:09 $
   End CVS Header */

#ifndef MY_TABLE_H
#define MY_TABLE_H

#include "qtable.h"
#include <qevent.h> 
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

  protected:
    virtual void showEvent(QShowEvent* e);

    bool firstTime;

  signals:
    void delKeyPressed();
  };

#endif
