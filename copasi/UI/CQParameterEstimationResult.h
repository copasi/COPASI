// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQPARAMETER_ESTIMATION_RESULT_H
#define CQPARAMETER_ESTIMATION_RESULT_H

#include <QDialog>

#include <vector>

namespace Ui
{
class CQParameterEstimationResult;
}

class ResultData;
class CDataModel;
class DataModelGUI;
class CheckPointModel;

class QSortFilterProxyModel;

class CQParameterEstimationResult : public QDialog
{
  Q_OBJECT

public:
  explicit CQParameterEstimationResult(QWidget *parent, CDataModel* dataModel);
  ~CQParameterEstimationResult();

protected:
  void deleteData();
  ResultData* getResult(int index);

public slots:
  void updateUI();
  void loadProtocol();
  void loadProtocol(const QString& fileName);
  void updateFitItems();
  void setTaskStartValues();
  void applyToModelState();
  void protocolFileChanged(const QString& fileName);
  void browseForProtocol();
  void toggleFitItems();
  void dataSetChanged();

private:
  Ui::CQParameterEstimationResult *ui;
  std::vector<ResultData*> mResultData;
  CDataModel* mpDataModel;
  DataModelGUI * mpDataModelGUI;
  CheckPointModel* mpCheckPointModel;
  QSortFilterProxyModel* mpProxy;
  bool mInitializing;
};

#endif // CQPARAMETER_ESTIMATION_RESULT_H
