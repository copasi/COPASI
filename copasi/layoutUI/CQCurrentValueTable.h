// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQCurrentValueTable.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/04 14:15:34 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQCURRENTVALUETABLE_H_
#define  CQCURRENTVALUETABLE_H_

#include <string>
#include <map>

#include "copasi.h"

#include <qtable.h>

#include "layoutUI/CDataEntity.h"

class CQCurrentValueTable : public QTable
  {

    Q_OBJECT        // must include this if you use Qt signals/slots

    std::map<int, std::string> indexMap;

  public:
    CQCurrentValueTable(QWidget *parent = 0, const char *name = 0);
    ~CQCurrentValueTable();

    void setRowInTable(int row, std::string key, std::string s, C_FLOAT64 val);
    void updateRowInTable(int row, C_FLOAT64 val);

    void setValue(int row, C_FLOAT64 val);

    void setAllBoxesChecked();
    void setAllBoxesUnchecked();
    void init();

    void setKeyIndex(std::string key, int row);
    std::string getKeyForRow(int row);

  private slots:
    //void mouseClickedOverTable(int row, int col , int button, const QPoint & mousepos);
    void valChanged(int row, int col);

  signals:
    void changed();
  };

#endif /*CQCURRENTVALUETABLE_H_*/
