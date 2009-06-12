// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFunctionDM.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/06/12 19:58:25 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QString>
#include <QList>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "function/CFunctionDB.h"

#include "CQMessageBox.h"
#include "CQFunctionDM.h"
#include "qtUtilities.h"

CQFunctionDM::CQFunctionDM(QObject *parent)
    : CQBaseDataModel(parent)

{
}

int CQFunctionDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return CCopasiRootContainer::getFunctionList()->loadedFunctions().size() + 1;
}
int CQFunctionDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
{
  return TOTAL_COLS_FUNCTIONS;
}

Qt::ItemFlags CQFunctionDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (!isDefaultRow(index) && isFunctionReadOnly(index))
    return QAbstractItemModel::flags(index);

  if (index.column() == COL_NAME_FUNCTIONS)
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  else
    return QAbstractItemModel::flags(index);
}

bool CQFunctionDM::isFunctionReadOnly(const QModelIndex &index) const
{
  const CEvaluationTree *pFunc = CCopasiRootContainer::getFunctionList()->loadedFunctions()[index.row()];

  switch (pFunc->getType())
    {
      case CEvaluationTree::PreDefined:
      case CEvaluationTree::MassAction:
        return true;
        break;
      case CEvaluationTree::UserDefined:
      case CEvaluationTree::Function:
      case CEvaluationTree::Expression:
      case CEvaluationTree::Boolean:
        return false;
        break;
    }

  return true;
}

QVariant CQFunctionDM::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount())
    return QVariant();

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      if (isDefaultRow(index))
        {
          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);
              case COL_NAME_FUNCTIONS:
                return QVariant(QString("No Name"));
              case COL_TYPE_FUNCTIONS:
                return QVariant(QString(FROM_UTF8(CEvaluationTree::TypeName[4])));
              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          const CFunction *pFunc = dynamic_cast<CFunction *>(CCopasiRootContainer::getFunctionList()->loadedFunctions()[index.row()]);

          if (pFunc == NULL)
            return QVariant();

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_FUNCTIONS:
                return QVariant(QString(FROM_UTF8(pFunc->getObjectName())));

              case COL_TYPE_FUNCTIONS:
                return QVariant(QString(FROM_UTF8(CEvaluationTree::TypeName[pFunc->getType()])));

              case COL_MATH_DESC_FUNCTIONS:
                return QVariant(QString(FROM_UTF8(pFunc->getInfix())));

              case COL_SBML_ID_FUNCTIONS:
                return QVariant();
            }
        }
    }

  return QVariant();
}

QVariant CQFunctionDM::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal)
    {
      switch (section)
        {
          case COL_ROW_NUMBER:
            return QVariant(QString("#"));
          case COL_NAME_FUNCTIONS:
            return QVariant(QString("Name"));
          case COL_TYPE_FUNCTIONS:
            return QVariant(QString("Type"));
          case COL_MATH_DESC_FUNCTIONS:
            return QVariant(QString("Mathematical Description"));
          case COL_SBML_ID_FUNCTIONS:
            return QVariant(QString("SBML ID"));
          default:
            return QVariant();
        }
    }
  else
    return QString("%1").arg(section + 1);
}

bool CQFunctionDM::setData(const QModelIndex &index, const QVariant &value,
                           int role)
{
  if (index.isValid() && role == Qt::EditRole)
    {
      bool defaultRow = isDefaultRow(index);

      if (defaultRow)
        {
          if (index.data() != value)
            insertRow();
          else
            return false;
        }

      CFunction *pFunc = dynamic_cast<CFunction *>(CCopasiRootContainer::getFunctionList()->loadedFunctions()[index.row()]);

      if (pFunc == NULL)
        return false;

      if (index.column() == COL_NAME_FUNCTIONS)
        pFunc->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_TYPE_FUNCTIONS)
        {
          if (index.data() != value)
            {
              QString msg;
              msg = "Type must not be changed for '" + FROM_UTF8(pFunc->getObjectName()) + "'.\n";

              CQMessageBox::information(NULL,
                                        "Unable to change Function Type",
                                        msg,
                                        QMessageBox::Ok, QMessageBox::Ok);
            }
        }
      else if (index.column() == COL_MATH_DESC_FUNCTIONS)
        {
          if (index.data() != value)
            {
              if (!pFunc->setInfix(TO_UTF8(value.toString())))
                {
                  QString msg;
                  msg = "Incorrect  mathematical description'" + FROM_UTF8(pFunc->getObjectName()) + "'.\n";

                  CQMessageBox::information(NULL,
                                            "Unable to change mathematical description",
                                            msg,
                                            QMessageBox::Ok, QMessageBox::Ok);
                }
            }
        }

      if (defaultRow && this->index(index.row(), COL_NAME_FUNCTIONS).data().toString() == "No Name")
        pFunc->setObjectName(TO_UTF8(createNewName("Function", COL_NAME_FUNCTIONS)));

      emit dataChanged(index, index);
    }

  return true;
}

bool CQFunctionDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CCopasiRootContainer::getFunctionList()->add(new CKinFunction(""), true);
    }

  endInsertRows();
  return true;
}

bool CQFunctionDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  for (int row = rows - 1; row >= 0; --row)
    {
      if (!isFunctionReadOnly(this->index(position + row, 0)))
        {
          beginRemoveRows(QModelIndex(), position + row, position + row);
          CCopasiRootContainer::getFunctionList()->removeFunction(position + row);
          endRemoveRows();
        }
    }

  return true;
}

bool CQFunctionDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  if (pModel == NULL)
    return false;

//Build the list of pointers to items to be deleted
//before actually deleting any item.
  QList <CEvaluationTree *> pFunctions;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && CCopasiRootContainer::getFunctionList()->loadedFunctions()[(*i).row()])
        pFunctions.append(CCopasiRootContainer::getFunctionList()->loadedFunctions()[(*i).row()]);
    }

  QList <CEvaluationTree *>::const_iterator j;

  for (j = pFunctions.begin(); j != pFunctions.end(); ++j)
    {
      CEvaluationTree * pFunction = *j;

      unsigned C_INT32 delRow =
        CCopasiRootContainer::getFunctionList()->loadedFunctions().CCopasiVector< CEvaluationTree >::getIndex(pFunction);

      if (delRow != C_INVALID_INDEX)
        {
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, pModel, "function",
                                        FROM_UTF8(pFunction->getObjectName()),
                                        pFunction->getDeletedObjects());

          if (choice == QMessageBox::Ok)
            removeRow(delRow);
        }
    }

  return true;
}
