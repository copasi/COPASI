// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExpandModelData.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:42 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEXPANDMODELDATA_H
#define CQEXPANDMODELDATA_H

#include <QtCore/QVariant>
#include <string>
#include <vector>

class QSignalMapper;

#include "model/CModel.h"

#include "ui_CQExpandModelData.h"

class CQExpandModelData : public QDialog, public Ui::CQExpandModelData
{
  Q_OBJECT

public:
  CQExpandModelData(QWidget* parent = 0, Qt::WindowFlags fl = 0);
  ~CQExpandModelData();

  std::vector< std::string > mCompartmentName;
  std::vector< std::string > mMetaboliteName;
protected:
  QCheckBox* pCheckBox;
  QSignalMapper * mpComboMap;
  CModel* pModel;

protected slots:
  void slotCompartmentChanged(/* int row */);
  void slotApplyDiffusion(bool show);

private:
  void load();
private slots:
  void slotOK();
  void slotCancel();
};

#endif // CQEXPANDMODELDATA_H
