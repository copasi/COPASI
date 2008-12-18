// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQCurrentValueTable.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 17:41:15 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQCURRENTVALUETABLE_H_
#define  CQCURRENTVALUETABLE_H_
#include <qwidget.h>

#include <string>
#include <map>

#include "copasi.h"

#include "layoutUI/CDataEntity.h"

class QPushButton;
class Q3Table;
class Q3Header;

class CQCurrentValueTable : public QWidget
  {

    Q_OBJECT        // must include this if you use Qt signals/slots

  protected:
    std::map<int, std::string> mIndexMap;
    Q3Table* mpTable;
    QPushButton* mpCheckAllButton;
    QPushButton* mpUncheckAllButton;

  public:
    CQCurrentValueTable(QWidget *parent = 0, const char *name = 0);
    ~CQCurrentValueTable();

    void setNumRows(int rows);
    void setNumCols(int columns);
    void updateRowInTable(int row, C_FLOAT64 val);
    void setRowInTable(int row, std::string key, std::string s, C_FLOAT64 val);
    int numRows() const;

    Q3Header* verticalHeader();
    std::string getKeyForRow(int row) const;
    bool getValueForRow(int row) const;

  protected:
    void setValue(int row, C_FLOAT64 val);
    void setKeyIndex(std::string key, int row);
    void setAllBoxesChecked(bool checked = true);
    void setAllBoxesUnchecked();
    void init();

  private slots:
    //void mouseClickedOverTable(int row, int col , int button, const QPoint & mousepos);
    void slotCheckAllClicked();
    void slotUncheckAllClicked();
    void tableValueChanged(int row, int column);

  signals:
    void valueChanged(int row);
  };

#endif /*CQCURRENTVALUETABLE_H_*/
