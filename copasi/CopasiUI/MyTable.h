/*
base class modifided to StretchTable
by Liang Xu
to support re size functions
 */
#ifndef MY_TABLE_H
#define MY_TABLE_H

#include "StretchTable.h"

class MyTable: public StretchTable
  {
  public:
    MyTable (QWidget * parent = 0, const char * name = 0);
    //void mousePressEvent(QMouseEvent *mpe);
    void keyPressEvent (QKeyEvent * e);
    void setDeleteConfirmation(bool enable);
    void removeRow(int row);
    void removeSelectedRows(bool full = false);
    void insertRows(long, long) {}

    virtual void setSorting (bool b, bool wholeRows = true);

  protected:
    bool deleteConfirmation;
  };

#endif
