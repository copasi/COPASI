// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMergingData.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/06/20 16:07:08 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMERGINGDATA_H
#define CQMERGINGDATA_H

#include <string>
#include <vector>

#include <QPixmap>

class QSignalMapper;

#include <QtGui/QDialog>
#include <QtGui/QWidget>
#include <QToolButton>

#include "model/CModel.h"

#include "ui_CQMergingData.h"

class CQMergingData : public QDialog, public Ui::CQMergingData
{
  Q_OBJECT

public:
  CQMergingData(QWidget* parent = 0, Qt::WindowFlags fl = 0);
  ~CQMergingData();

  std::vector< std::string > mObjectKey;
  std::vector< std::string > mColumnKey;
  std::vector< std::string > mColumnName;

protected:
  QPixmap mCopasi;
  QSignalMapper * mpBtnMap;
  QSignalMapper * mpComboMap;
  QStringList ColumnTypes;
  CModel* pModel;

protected slots:
  void slotModelObject(int row);
  void slotTypeChanged(int row);

private:
  std::string findMetaboliteKeyByName(std::string name);
//  void init();
  void load();
//  void save();
//  void destroy();
private slots:
  void slotBtnMerge();
  void slotBtnCancel();
};

#endif // CQMERGINGDATA_H
