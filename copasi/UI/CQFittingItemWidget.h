// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQFITTINGITEMWIDGET_H
#define CQFITTINGITEMWIDGET_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQFittingItemWidget.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>

#include <QLabel>
#include <QPixmap>

class CDataModel;
class CCopasiSelectionDialog;
class COptItem;
class CDataObject;
class CCommonName;
class CQValidatorBound;
class CQValidatorNotEmpty;
class QColor;
class CExperimentSet;
class CCopasiParameterGroup;
class CCrossValidationSet;
class CObjectInterface;

class CQFittingItemWidget : public QWidget, public Ui::CQFittingItemWidget
{
  Q_OBJECT

public:
  CQFittingItemWidget(QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags());
  ~CQFittingItemWidget();

  enum ItemType {OPT_ITEM = 0, OPT_CONSTRAINT, FIT_ITEM, FIT_CONSTRAINT};

  virtual bool load(CDataModel * pDataModel,
                    CCopasiParameterGroup * pItems,
                    const std::map<std::string, std::string> * pExperimentMap,
                    const std::map<std::string, std::string> * pCrossValidationMap);
  virtual bool save(const std::map<std::string, std::string> * pExperimentMap,
                    const std::map<std::string, std::string> * pCrossValidationMap);
  void setItemType(const ItemType & type);
  void setExperimentSet(const CExperimentSet * & pExperimentSet);
  void setCrossValidationSet(const CCrossValidationSet * & pCrossValidationSet);

signals:
  void numberChanged(int);

protected:
  const CDataModel * mpDataModel;
  const CCrossValidationSet **mppCrossValidationSet;
  std::set< size_t > mSelection;
  size_t mCurrentRow;
  std::vector< COptItem * > * mpItemsCopy;
  ItemType mItemType;
  QColor mChangedColor;
  QColor mSavedColor;
  bool mUpperInfChanged;
  bool mLowerInfChanged;
  CQValidatorBound * mpUpperValidator;
  CQValidatorBound * mpLowerValidator;
  CQValidatorNotEmpty * mpObjectValidator;
  const CObjectInterface* mpUpperObject;
  const CObjectInterface* mpLowerObject;
  CCommonName* mpObjectCN;
  const CExperimentSet ** mppExperimentSet;
  CCopasiParameterGroup * mpItems;

protected slots:

private:
  void init();
  void destroy();
  void setTableText(const int & row, const COptItem * pItem);
  size_t currentRow();
  void loadSelection();
  void saveSelection();
  void selectRow(const size_t & row);
  void setItemSelection(const std::set<size_t> & selection);

private slots:
  void slotCheckLowerInf(bool checked);
  void slotCheckUpperInf(bool checked);
  void slotLowerEdit();
  void slotUpperEdit();
  void slotParamEdit();
  void slotExperiments();
  void slotExperimentChanged();
  void slotDelete();
  void slotCopy();
  void slotUp();
  void slotDown();
  void slotDuplicatePerExperiment();
  void slotNew();
  void slotSelectionChanged();
  void slotLowerLostFocus();
  void slotUpperLostFocus();
  void slotReset();
  void slotStartLostFocus();
  void slotCrossValidations();
  void slotCrossValidationChanged();
  void slotCheckAllCrossValidations(bool checked);
  void slotCheckAllExperiments(bool checked);
};

#endif // CQFITTINGITEMWIDGET_H
