// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEXPANDMODELDATA_H
#define CQEXPANDMODELDATA_H

#include <QtCore/QVariant>
#include <string>
#include <vector>

class QTreeWidgetItem;

class CModel;
class CCompartment;
class CMetab;

#include "ui_CQExpandModelData.h"

class CQExpandModelData : public QDialog, public Ui::CQExpandModelData
{
  Q_OBJECT

public:
  CQExpandModelData(QWidget* parent, CModel* pModel);
  ~CQExpandModelData();

protected:

  std::map<QTreeWidgetItem*, const CCompartment*> mItemCompartmentMap;
  std::map<QTreeWidgetItem*, const CMetab*> mItemMetabMap;
  CModel* mpModel;

protected slots:

  /// handles activation or deactivation of a compartment
  void slotCompartmentActivated(QTreeWidgetItem* pItem, int col);

  /// handles change of linear/rectangular mode
  void slotMode();

private:

  void load();

private slots:

  void slotOK();
  void slotCancel();
};

#endif // CQEXPANDMODELDATA_H
