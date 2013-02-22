// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQParameterSetsDM
#define COPASI_CQParameterSetsDM

#include "CQBaseDataModel.h"

#define COL_ROW_NUMBER   0
#define COL_NAME         1
#define TOTAL_COLS       2

class CModelParameterSet;
template <class CType> class CCopasiVectorN;

class CQParameterSetsDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQParameterSetsDM(QObject *parent = 0);
  virtual ~CQParameterSetsDM();

  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole);
  virtual bool isDefaultRow(const QModelIndex& i) const;
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());
  void setListOfModelParameterSets(CCopasiVectorN< CModelParameterSet > * pListOfModelParameterSets);

  virtual bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());

  virtual bool clear();

protected:
  virtual bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

private:
  CCopasiVectorN< CModelParameterSet > * mpListOfParameterSets;
};

#endif // COPASI_CQParameterSetsDM
