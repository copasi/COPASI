// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include <QColor>

#include "copasi/versioningUI/CQModelVersionHierarchyDM.h"
#include "copasi/versioning/CModelVersionHierarchy.h"
#include "copasi/UI/qtUtilities.h"

CQModelVersionHierarchyDM::CQModelVersionHierarchyDM(QObject *parent):
  QAbstractTableModel(parent),
  mpModelVersionHierarchy(NULL),
  mVersions()
{}

CQModelVersionHierarchyDM::~CQModelVersionHierarchyDM()
{
  // TODO Auto-generated destructor stub
}

// virtual
QVariant CQModelVersionHierarchyDM::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount())
    return QVariant();

  if (index.column() > (int) Column::Index && role == Qt::ForegroundRole && !(flags(index) & Qt::ItemIsEditable))
    return QColor(Qt::darkGray);

  const CModelVersion * pModelVersion = mVersions.at(index.row());

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      switch ((Column) index.column())
        {
          case Column::Index:
            return QVariant(index.row());
            break;

          case Column::Name:
            if (pModelVersion->getName() == mpModelVersionHierarchy->getCurrentVersion().getName())
              return QVariant(FROM_UTF8(pModelVersion->getName() + " *"));
            else
              return QVariant(FROM_UTF8(pModelVersion->getName()));

            break;

          case Column::Parent:
            return QVariant(FROM_UTF8(pModelVersion->getParentName()));
            break;

          case Column::Comment:
            return QVariant(FROM_UTF8(pModelVersion->getNotes()));
            break;

          case Column::AuthorGivenName:
            return QVariant(FROM_UTF8(pModelVersion->getGivenName()));
            break;

          case Column::AuthorFamilyName:
            return QVariant(FROM_UTF8(pModelVersion->getFamilyName()));
            break;

          case Column::AuthorOrganization:
            return QVariant(FROM_UTF8(pModelVersion->getOrganization()));
            break;

          case Column::AuthorEmail:
            return QVariant(FROM_UTF8(pModelVersion->getEmail()));
            break;

          case Column::Time:
            return QVariant(FROM_UTF8(pModelVersion->getUTCTimeStamp()));
            break;
        }
    }

  return QVariant();
}

// virtual
QVariant CQModelVersionHierarchyDM::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole ||
      orientation != Qt::Horizontal)
    return QVariant();

  switch ((Column) section)
    {
      case Column::Index:
        return QVariant("#");
        break;

      case Column::Name:
        return QVariant("Version");
        break;

      case Column::Parent:
        return QVariant("Parent Version");
        break;

      case Column::Comment:
        return QVariant("Comment");
        break;

      case Column::AuthorGivenName:
        return QVariant("Given Name");
        break;

      case Column::AuthorFamilyName:
        return QVariant("Family Name");
        break;

      case Column::AuthorOrganization:
        return QVariant("Organization");
        break;

      case Column::AuthorEmail:
        return QVariant("Email");
        break;

      case Column::Time:
        return QVariant("Created");
        break;
    }

  return QVariant();
}

// virtual
Qt::ItemFlags CQModelVersionHierarchyDM::flags(const QModelIndex & index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == (int) Column::Comment)
    {
      return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }
  else
    {
      return (QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable) | Qt::ItemIsEnabled;
    }

  return QAbstractTableModel::flags(index);
}

// virtual
bool CQModelVersionHierarchyDM::setData(const QModelIndex & dataIndex, const QVariant & value, int role)
{
  if (!dataIndex.isValid() ||
      dataIndex.column() != (int) Column::Comment)
    return false;

  std::string Version = TO_UTF8(data(index(dataIndex.row(), (int) Column::Name), Qt::DisplayRole).toString());
  mpModelVersionHierarchy->getVersion(Version).setNotes(TO_UTF8(value.toString()));

  return true;
}

// virtual
int CQModelVersionHierarchyDM::rowCount(const QModelIndex & parent) const
{
  return mVersions.size();
}

// virtual
int CQModelVersionHierarchyDM::columnCount(const QModelIndex & parent) const
{
  return (int) Column::__SIZE;
}

void CQModelVersionHierarchyDM::setModelVersionHierarchy(CModelVersionHierarchy * pModelVersionHierarchy)
{
  beginResetModel();

  mVersions.clear();
  mpModelVersionHierarchy = pModelVersionHierarchy;

  if (mpModelVersionHierarchy != NULL)
    {
      CModelVersionHierarchy::iterator itNode = mpModelVersionHierarchy->getNodeIterator();

      while (itNode.next() != itNode.end())
        {
          if (*itNode == NULL)
            {
              continue;
            }

          mVersions.append(&itNode->getData());
        }
    }

  endResetModel();
}
