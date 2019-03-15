// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CQModelVersionHierarchyDM
#define COPASI_CQModelVersionHierarchyDM

#include <QAbstractTableModel>

class CModelVersion;
class CModelVersionHierarchy;

class CQModelVersionHierarchyDM : public QAbstractTableModel
{
  Q_OBJECT

public:
  enum struct Column
  {
    Index,
    Name,
    Parent,
    Comment,
    AuthorGivenName,
    AuthorFamilyName,
    AuthorOrganization,
    AuthorEmail,
    Time,
    __SIZE
  };

  CQModelVersionHierarchyDM(QObject *parent = 0);
  virtual ~CQModelVersionHierarchyDM();
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole);
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  void setModelVersionHierarchy(CModelVersionHierarchy * pModelVersionHierarchy);

private:
  CModelVersionHierarchy * mpModelVersionHierarchy;
  QList< const CModelVersion * > mVersions;
};

#endif // COPASI_CQModelVersionHierarchyDM
