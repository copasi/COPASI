// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQCurrentValueTable.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/09 09:16:26 $
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
class QTable;
class QHeader;

class CQCurrentValueTable : public QWidget
  {

    Q_OBJECT        // must include this if you use Qt signals/slots

  protected:
    std::map<int, std::string> mIndexMap;
    QTable* mpTable;
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
    QHeader* verticalHeader();

  protected:
    void setValue(int row, C_FLOAT64 val);
    void setKeyIndex(std::string key, int row);
    std::string getKeyForRow(int row);
    void setAllBoxesChecked(bool checked = true);
    void setAllBoxesUnchecked();
    void init();

  private slots:
    //void mouseClickedOverTable(int row, int col , int button, const QPoint & mousepos);
    void valChanged(int row, int col);
    void slotCheckAllClicked();
    void slotUncheckAllClicked();

  signals:
    void changed();
  };

#endif /*CQCURRENTVALUETABLE_H_*/
