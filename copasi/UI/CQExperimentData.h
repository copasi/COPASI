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

#ifndef CQEXPERIMENTDATA_H
#define CQEXPERIMENTDATA_H

#include <QtCore/QVariant>

#include "ui_CQExperimentData.h"

class CExperimentSet;
class CExperimentFileInfo;
class CExperiment;
class CQExperimentDataValidator;
class QSignalMapper;
class CCrossValidationSet;
class CDataModel;
class CQComboDelegate;

class CQExperimentData : public QDialog, public Ui::CQExperimentData
{
  Q_OBJECT

public:
  CQExperimentData(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CQExperimentData();

  friend class CQExperimentDataValidator;

  virtual bool load(CExperimentSet * pExperimentSet, CDataModel * pDataModel);

  void loadFromCopy();

public slots:
  virtual void loadTable(CExperiment * pExperiment, const bool & guess);

signals:
  void experimentChanged();

protected:
  unsigned int mOldWeightMethod;
  CQExperimentDataValidator * mpValidatorHeader;
  CQExperimentDataValidator * mpValidatorLast;
  CExperiment * mpExperiment;
  CExperimentFileInfo * mpFileInfo;
  CExperimentSet * mpExperimentSet;
  CExperimentSet * mpExperimentSetCopy;
  std::map<std::string, std::string> mKeyMap;
  std::map<std::string, std::string> mFileMap;
  CQExperimentDataValidator * mpValidatorFirst;
  int mShown;
  CQExperimentDataValidator * mpValidatorName;
  bool mCrossValidation;
  bool mShowError;
  CDataModel * mpDataModel;
  CQComboDelegate * mpComboDelegate;
  QStringList mTypeItems;
  QStringList mTypeWithoutTimeItems;
  int mModelObjectRow;

  virtual bool loadExperiment(CExperiment * pExperiment);
  bool saveExperiment(CExperiment * pExperiment, const bool & full);
  void syncExperiments();
  bool saveTable(CExperiment * pExperiment);
  bool isLikePreviousExperiment(CExperiment * pExperiment);
  void enableEdit(const bool & enable);

protected slots:

  void slotRevert();
  void slotFirst();
  void slotLast();
  void slotHeader();
  void slotExprimentType(bool isSteadyState);
  void slotCheckNormalizeWeightsPerExperiment(bool flag);
  void slotCheckTab(bool checked);
  void slotCheckHeader(bool checked);
  void slotExperimentAdd();
  void slotExperimentChanged(QListWidgetItem * pCurrentItem, QListWidgetItem * pPreviousItem);
  void slotExperimentDelete();
  void slotFileAdd();
  void slotFileChanged(QListWidgetItem * pCurrentItem, QListWidgetItem * pPreviousItem);
  void slotFileEdit();
  void slotFileDelete();
  void slotCancel();
  void slotOK();
  void slotUpdateTable();
  void slotModelObject(const QModelIndex & index);
  void slotModelObjectDelayed();
  void slotTypeChanged(int row, int index);
  void slotSeparator();
  void slotCheckFrom(bool checked);
  void slotCheckTo(bool checked);
  void slotCheckToAll(bool checked);

private:
  void init();
  void destroy();
  void setTypeItems(const int & timeRow);
  void selectModelObject(const int & row);
  void updateScales();

private slots:
  void slotWeightMethod(int weightMethod);
};

#endif // CQEXPERIMENTDATA_H
