/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MyTable.h,v $
   $Revision: 1.20 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/11/11 21:14:11 $
   End CVS Header */

#ifndef MY_TABLE_H
#define MY_TABLE_H

#include <vector>
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
    //void keyPressEvent (QKeyEvent * e);

  public slots:
    //virtual void setNumCols(int c);
    //virtual void insertColumns(int index, int count = 1);
    //virtual void removeColumn(int col);
    //virtual void removeColumns(const QMemArray<int> & cols);

  protected:
    //virtual void resizeEvent(QResizeEvent* e);
    //virtual int getOptimalColumnWidth(int index);
    //virtual void scaleColumns(double factor);
    //virtual QSize headerSectionSizeHint(int section) const;

    //bool firstTime;
    //std::vector<double> exactColumnWidth;

  signals:
    //  void delKeyPressed();
  };

#endif
