// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQParameterResultItemModel.h"

#include <copasi/CopasiDataModel/CDataModel.h>
#include <copasi/optimization/COptProblem.h>
#include <copasi/parameterFitting/CFitProblem.h>

#include "qtUtilities.h"

CQParameterResultItemModel::CQParameterResultItemModel(const CFitProblem * pProblem, QColor backgroundColor, QObject * parent)
  : QAbstractTableModel(parent)
  , mpProblem(pProblem)
  , mpDataModel(pProblem->getObjectDataModel())
  , mBackgroundColor(backgroundColor)
  , mIgnored()
  , mItems(pProblem->getOptItemList())
  , mSolutions(pProblem->getSolutionVariables())
  , mStdDeviations(pProblem->getVariableStdDeviations())
  , mGradients(pProblem->getVariableGradients())
  , mNumRows(0)
  , mNumCols(8)
{
  init();
}

CQParameterResultItemModel::CQParameterResultItemModel(const COptProblem * pProblem, QColor backgroundColor, QObject * parent)
  : QAbstractTableModel(parent)
  , mpProblem(pProblem)
  , mpDataModel(pProblem->getObjectDataModel())
  , mBackgroundColor(backgroundColor)
  , mIgnored()
  , mItems(pProblem->getOptItemList())
  , mSolutions(pProblem->getSolutionVariables())
  , mStdDeviations(mIgnored)
  , mGradients(pProblem->getVariableGradients())
  , mNumRows(0)
  , mNumCols(7)
{
  init();
}

void
CQParameterResultItemModel::init()
{
  if (mpProblem->getFunctionEvaluations() > 0)
    mNumRows = (int)mItems.size();

  int h, s, v;
  mBackgroundColor.getHsv(&h, &s, &v);

  if (s < 20)
    {
      s = 20;
    }

  mBackgroundColor.setHsv(0, s, v);
}

CQParameterResultItemModel::~CQParameterResultItemModel() {}

int
CQParameterResultItemModel::rowCount(const QModelIndex &) const
{
  return mNumRows;
}

int
CQParameterResultItemModel::columnCount(const QModelIndex &) const
{
  return mNumCols;
}

QVariant
CQParameterResultItemModel::data(const QModelIndex & index, int role) const
{
  if (!index.isValid()) return QVariant();

  size_t row = index.row();
  int column = index.column();

  const COptItem *current = row < mItems.size() ? mItems[row] : NULL;
  const C_FLOAT64 & Solution = row < mSolutions.size() ? mSolutions[row] : std::numeric_limits<double>::quiet_NaN();

  if (role == Qt::BackgroundRole && current != NULL)
    {
      switch (column)
        {
          case LowerBound:
          {
            if (current->getLowerBoundValue() != NULL && 1.01 * *current->getLowerBoundValue() > Solution)
              {
                return QBrush(mBackgroundColor);
              }

            break;
          }

          case UpperBound:
          {
            if (current->getUpperBoundValue() != NULL && 0.99 * *current->getUpperBoundValue() < Solution)
              {
                return QBrush(mBackgroundColor);
              }

            break;
          }
        }

      return QVariant();
    }

  if (role == Qt::DisplayRole && current != NULL)
    {

      switch ((CQParameterResultItemModel::COLUMS)column)
        {
          case Parameter:
          {
            const CDataObject *pObject =
              CObjectInterface::DataObject(mpDataModel->getObjectFromCN(mItems[row]->getObjectCN()));

            if (pObject)
              {
                if (dynamic_cast<const CFitProblem*>(mpProblem) != NULL)
                  {
                    std::string Experiments =
                      static_cast<CFitItem *>(mItems[row])->getExperiments();

                    if (Experiments != "")
                      Experiments = "; {" + Experiments + "}";

                    return FROM_UTF8(pObject->getObjectDisplayName() + Experiments);
                  }

                return FROM_UTF8(pObject->getObjectDisplayName());
              }

            return "Not Found";
          }

          case LowerBound:
            return FROM_UTF8(current->getLowerBound());

          case StartValue:
            return current->getLastStartValue();

          case Value:
            return Solution;

          case UpperBound:
            return FROM_UTF8(current->getUpperBound());

          case StdDeviation:
            return row < mStdDeviations.size() ? mStdDeviations[row] : std::numeric_limits<double>::quiet_NaN();

          case CoeffOfVariation:
            return row < mStdDeviations.size() ? fabs(100 * mStdDeviations[row] / Solution) : std::numeric_limits<double>::quiet_NaN();

          case Gradient:
          {
            return row < mGradients.size() ? mGradients[row] : std::numeric_limits<double>::quiet_NaN();
          }
        }
    }

  return QVariant();
}

QVariant
CQParameterResultItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal)
    {
      switch ((CQParameterResultItemModel::COLUMS)section)
        {
          case Parameter:
            return "Parameter";

          case LowerBound:
            return "Lower Bound";

          case StartValue:
            return "Start Value";

          case Value:
            return "Value";

          case UpperBound:
            return "Upper Bound";

          case StdDeviation:
            return "Std. Deviation";

          case CoeffOfVariation:
            return "Coeff. of Variation [%]";

          case Gradient:
            return "Gradient";
        }
    }
  else
    {
      // for the vertical headers use just the section numbers
      return section + 1;
    }

  return QVariant();
}
