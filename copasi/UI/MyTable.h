#ifndef MY_TABLE_H
#define MY_TABLE_H

#include <qtable.h>

class MyTable: public QTable
  {
  public:
    MyTable (QWidget * parent = 0, const char * name = 0);
    MyTable (int numRows, int numCols, QWidget * parent = 0, const char * name = 0);
    //void mousePressEvent(QMouseEvent *mpe);
    //void keyPressEvent (QKeyEvent * e);
    //void setDeleteConfirmation(bool enable);
    //void removeRow(int row);
    //void removeSelectedRows(bool full = FALSE);
    //void insertRows(long, long) {}

    //virtual void setSorting (bool b, bool wholeRows = TRUE);

  protected:
    bool deleteConfirmation;
  };

#endif
