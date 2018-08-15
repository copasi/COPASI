// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQParameterResultItemModel_H
#define CQParameterResultItemModel_H

#include <vector>

#include <QBrush>
#include <QColor>
#include <QAbstractTableModel>

#include <copasi/core/CVector.h>

class COptProblem;
class CFitProblem;
class CDataModel;
class COptItem;

Q_DECLARE_METATYPE(Qt::SortOrder)

class CQParameterResultItemModel : public QAbstractTableModel
{
  enum COLUMS
  {
    Parameter,
    LowerBound,
    StartValue,
    Value,
    UpperBound,
    CoeffOfVariation,
    Gradient,
    StdDeviation
  };

protected:
  const COptProblem* mpProblem;
  const CDataModel* mpDataModel;
  QColor mBackgroundColor;
  CVector< C_FLOAT64 > mIgnored;
  const std::vector< COptItem * > & mItems;
  const CVector< C_FLOAT64 > & mSolutions;
  const CVector< C_FLOAT64 > & mStdDeviations;
  const CVector< C_FLOAT64 > & mGradients;
  int mNumRows;
  int mNumCols;

public:

  CQParameterResultItemModel(const CFitProblem* pProblem, QColor backgroundColor, QObject* parent = NULL);

  CQParameterResultItemModel(const COptProblem* pProblem, QColor backgroundColor, QObject* parent = NULL);

  void init();

  virtual ~CQParameterResultItemModel();

  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  virtual QVariant data(const QModelIndex &index, int role) const;

  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // CQParameterResultItemModel
