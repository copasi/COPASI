#ifndef STRETCH_TABLE_H
#define STRETCH_TABLE_H

#include <qtable.h>

class StretchTable: public QTable
  {
  public:
    StretchTable (QWidget * parent = 0, const char * name = 0);
    StretchTable (int numRows, int numCols, QWidget * parent = 0, const char * name = 0);

    void columnWidthChanged (int col);
    void setNumCols (int c);
    void setNumRows (int r);

    int numColumn;
    int* minColWidth;
    void DisableColWidthUpdate();
    void EnableColWidthUpdate();

  private:
    bool systemUpdate;
    bool* binitialized;
  };

#endif
