// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExperimentData.h,v $
//   $Revision: 1.20 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/13 17:38:26 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQEXPERIMENTDATA_H
#define CQEXPERIMENTDATA_H

#include "ui_CQExperimentData.h"

class CExperimentSet;
class CExperimentFileInfo;
class CExperiment;
class CQExperimentDataValidator;
class QSignalMapper;
class CCrossValidationSet;
class CCopasiDataModel;
class CQComboDelegate;

class CQExperimentData : public QDialog, public Ui::CQExperimentData
{
  Q_OBJECT

public:
  CQExperimentData(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~CQExperimentData();

  friend class CQExperimentDataValidator;

  virtual bool load(CExperimentSet * pExperimentSet , CCopasiDataModel * pDataModel);

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
  size_t mShown;
  CQExperimentDataValidator * mpValidatorName;
  bool mCrossValidation;
  bool mShowError;
  CCopasiDataModel * mpDataModel;
  CQComboDelegate * mpComboDelegate;
  QStringList mTypeItems;
  QStringList mTypeWithoutTimeItems;

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
  void slotCheckTab(bool checked);
  void slotCheckHeader(bool checked);
  void slotExperimentAdd();
  void slotExperimentChanged(QListWidgetItem * pCurrentItem, QListWidgetItem * pPreviousItem);
  void slotExperimentDelete();
  void slotFileAdd();
  void slotFileChanged(QListWidgetItem * pCurrentItem, QListWidgetItem * pPreviousItem);
  void slotFileDelete();
  void slotCancel();
  void slotOK();
  void slotUpdateTable();
  void slotModelObject(int row);
  void slotTypeChanged(int row, int index);
  void slotSeparator();
  void slotCheckFrom(bool checked);
  void slotCheckTo(bool checked);


private:
  void init();
  void destroy();
  void setTypeItems(const int & timeRow);

private slots:
  void slotWeightMethod(int weightMethod);

};

#endif // CQEXPERIMENTDATA_H
