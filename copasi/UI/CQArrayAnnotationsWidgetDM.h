// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQArrayAnnotationsWidgetDM
#define COPASI_CQArrayAnnotationsWidgetDM

#include <QStringList>

#include <QAbstractTableModel>
#include <vector>

class CColorScale;
class CArrayAnnotation;

class CQArrayAnnotationsWidgetDM: public QAbstractTableModel
{
  Q_OBJECT

public:
  CQArrayAnnotationsWidgetDM(QObject *parent = 0);
  virtual ~CQArrayAnnotationsWidgetDM();
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
  virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;

  void setContext(const CColorScale * pColorScale,
                  const CArrayAnnotation * pArray,
                  const std::vector< size_t > & index,
                  const size_t & row,
                  const size_t & column);

private:
  const CColorScale * mpColorScale;
  const CArrayAnnotation * mpArray;
  mutable std::vector< size_t > mIndex;
  size_t mRow;
  size_t mColumn;
  QStringList * mHeaderData;
};

#endif // COPASI_CQArrayAnnotationsWidgetDM
