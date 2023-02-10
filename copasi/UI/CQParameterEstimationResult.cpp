// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include "CQParameterEstimationResult.h"
#include "ui_CQParameterEstimationResult.h"

#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#include <QVector>
#include <QFile>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QCompleter>
#include <QMessageBox>
#include <QListView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

#include <copasi/UI/copasiui3window.h>
#include <copasi/UI/listviews.h>
#include <copasi/UI/DataModelGUI.h>
#include "qtUtilities.h"
#include <copasi/CopasiDataModel/CDataModel.h>
#include <copasi/model/CModel.h>

#include <copasi/parameterFitting/CFitItem.h>
#include <copasi/parameterFitting/CFitProblem.h>
#include <copasi/parameterFitting/CFitTask.h>
#include <copasi/optimization/COptItem.h>
#include <copasi/optimization/COptProblem.h>
#include <copasi/optimization/COptTask.h>
#include <copasi/utilities/CCopasiTask.h>
#include "copasi/core/CDataVector.h"

#include <copasi/utilities/CParameterEstimationUtils.h>

class CheckPointModel : public QAbstractTableModel
{
  QVector<CheckPoint *> mData;
  std::vector<QString> mHeaders;
public:

  CheckPointModel(QObject *parent, ResultData *data)
    : QAbstractTableModel(parent)
    , mData()
    , mHeaders()
  {
    mHeaders.push_back("Function Evaluations");
    mHeaders.push_back("Best Value");

    if (data != NULL)
      for (std::vector<FittingItem *>::iterator it = data->mFittingItems.begin(); it != data->mFittingItems.end(); ++it)
        {
          mHeaders.push_back((*it)->mName.c_str());
        }
  }

  int rowCount(const QModelIndex &) const {return mData.count();}

  int columnCount(const QModelIndex &) const {return (int)mHeaders.size();}

  QVariant data(const QModelIndex &index, int role) const
  {
    if (role != Qt::DisplayRole && role != Qt::EditRole) return QVariant();

    const CheckPoint *checkPoint = mData[index.row()];

    if (index.column() == 0)
      {
        return checkPoint->mFunctionEvaluations;
      }

    if (index.column() == 1)
      {
        return checkPoint->mBestValue;
      }

    if (index.column() < (int)checkPoint->mParameters.size() + 2)
      {
        return checkPoint->mParameters[index.column() - 2];
      }

    return QVariant();
  }

  QVariant headerData(int section, Qt::Orientation orientation, int role) const
  {
    if (orientation != Qt::Horizontal) return QVariant();

    if (role != Qt::DisplayRole) return QVariant();

    if (section < (int)mHeaders.size())
      return mHeaders[section];

    return QVariant();
  }

  void removeAllRows()
  {
    beginResetModel();
    mData.clear();
    endResetModel();
    //reset();
  }

  void append(std::vector<CheckPoint *> &checkPoints)
  {
    beginInsertRows(QModelIndex(), mData.count(), mData.count() + checkPoints.size() - 1);

    for (std::vector<CheckPoint *>::iterator it1 = checkPoints.begin();
         it1 != checkPoints.end(); ++it1)
      {
        mData.append(*it1);
      }

    endInsertRows();
  }

  void append(CheckPoint *checkPoint)
  {
    beginInsertRows(QModelIndex(), mData.count(), mData.count());
    mData.append(checkPoint);
    endInsertRows();
  }
};

CQParameterEstimationResult::CQParameterEstimationResult(QWidget *parent,
    CDataModel *dataModel)
  : QDialog(parent)
  , ui(new Ui::CQParameterEstimationResult)
  , mResultData()
  , mpDataModel(dataModel)
  , mpDataModelGUI(NULL)
  , mpCheckPointModel(NULL)
  , mpProxy(NULL)
  , mInitializing(true)
{
  ui->setupUi(this);

  CopasiUI3Window * pMainWindow = dynamic_cast< CopasiUI3Window * >(parent);

  if (pMainWindow != NULL)
    {
      mpDataModelGUI = pMainWindow->getDataModel();
    }

  QCompleter* completer = new QCompleter(this);
  completer->setCompletionMode(QCompleter::PopupCompletion);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  QFileSystemModel *model = new QFileSystemModel(completer);
  completer->setModel(model);
  ui->txtProtocol->setCompleter(completer);
  QObject::connect(ui->txtProtocol, SIGNAL(textChanged(QString)), completer, SLOT(complete()));
}

CQParameterEstimationResult::~CQParameterEstimationResult()
{
  delete ui;
  deleteData();
}

void
CQParameterEstimationResult::updateUI()
{
  mInitializing = true;
  ui->lstDataSets->clear();

  for (std::vector<ResultData *>::iterator it = mResultData.begin(); it != mResultData.end(); ++it)
    ui->lstDataSets->addItem(QString("DataSet_%1").arg(ui->lstDataSets->count() + 1));

  ResultData *data = getResult(0);
  ui->tblResults->setModel(NULL);

  if (mpCheckPointModel != NULL)
    {
      mpProxy->deleteLater();
      mpProxy = NULL;
      mpCheckPointModel->deleteLater();
      mpCheckPointModel = NULL;
    }

  mpProxy = new QSortFilterProxyModel(this);
  mpCheckPointModel = new CheckPointModel(this, data);
  mpProxy->setSourceModel(mpCheckPointModel);
  ui->tblResults->setModel(mpProxy);
  mInitializing = false;

  if (ui->lstDataSets->count() > 0)
    {
      ui->lstDataSets->setCurrentIndex(ui->lstDataSets->count() - 1);
      dataSetChanged();
    }
}

void
CQParameterEstimationResult::deleteData()
{
  std::vector<ResultData *>::iterator it = mResultData.begin();

  while (it != mResultData.end())
    {
      delete *it;
      ++it;
    }

  mResultData.clear();
}

void
CQParameterEstimationResult::loadProtocol(const QString &fileName)
{
  deleteData();
  ui->txtProtocol->setText(fileName);
  mResultData = ResultParser::fromFile(fileName.toStdString(), mpDataModel);
  updateUI();
}

void
CQParameterEstimationResult::loadProtocol()
{
  protocolFileChanged(ui->txtProtocol->text());
}

void
CQParameterEstimationResult::updateFitItems()
{
  ResultData *data = getResult(ui->lstDataSets->currentIndex());

  if (data == NULL) return;

  data->updateFitItems();
  dataSetChanged();
}

void
CQParameterEstimationResult::setTaskStartValues()
{
  ResultData *data = getResult(ui->lstDataSets->currentIndex());

  if (data == NULL) return;

  QItemSelectionModel *select = ui->tblResults->selectionModel();

  if (select->selectedRows().empty())
    {
      QMessageBox::information(this, "No row selected",
                               "Before setting start values, please select a result row, from which the values should be taken.",
                               QMessageBox::Ok, QMessageBox::Ok);
      return;
    }
  
  auto mappedIndex = mpProxy->mapToSource(select->selectedRows().at(0));

  data->setTaskStartValues(mappedIndex.row());
}

void
CQParameterEstimationResult::applyToModelState()
{
  ResultData *data = getResult(ui->lstDataSets->currentIndex());

  if (data == NULL) return;

  QItemSelectionModel *select = ui->tblResults->selectionModel();

  if (!select->hasSelection())
    {
      QMessageBox::information(this, "No row selected",
                               "Before setting start values, please select a result row, from which the values should be taken.",
                               QMessageBox::Ok, QMessageBox::Ok);
      return;
    }

  std::vector<std::string> experiments = data->getAllExperiments();

  if (experiments.size() > 1)
    {
      // let the user sort the experiments
      QDialog *dialog = new QDialog(this);
      QVBoxLayout *verticalLayout = new QVBoxLayout(dialog);
      QLabel *label = new QLabel(dialog);
      verticalLayout->addWidget(label);
      label->setText("Please drag and drop the experiments into the order in which to apply the values.");
      QListView *listView = new QListView(dialog);
      verticalLayout->addWidget(listView);
      QStandardItemModel *model = new QStandardItemModel(this);

      for (std::vector<std::string>::iterator it = experiments.begin();
           it != experiments.end(); ++it)
        {
          int current = model->rowCount();
          QStandardItem *item = new QStandardItem((*it).c_str());
          item->setFlags(item->flags() ^ Qt::ItemIsDropEnabled);
          model->appendRow(item);
        }

      listView->setModel(model);
      listView->setDragEnabled(true);
      listView->setAcceptDrops(true);
      listView->setDragDropMode(QAbstractItemView::InternalMove);
      listView->showDropIndicator();
      QDialogButtonBox *group = new QDialogButtonBox(dialog);
      group->setOrientation(Qt::Horizontal);
      group->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
      QObject::connect(group, SIGNAL(accepted()), dialog, SLOT(accept()));
      QObject::connect(group, SIGNAL(rejected()), dialog, SLOT(reject()));
      verticalLayout->addWidget(group);

      if (dialog->exec() != QDialog::Accepted)
        return;

      std::vector<std::string> newOrder;

      for (int i = 0; i < model->rowCount(); ++i)
        {
          newOrder.push_back(model->item(i)->text().toStdString());
        }

      experiments = newOrder;
    }

  auto mappedIndex = mpProxy->mapToSource(select->selectedRows().at(0));

  data->applyToModelState(mappedIndex.row(), experiments);

  if (mpDataModelGUI != NULL &&
      mpDataModel != NULL)
    {
      mpDataModelGUI->notify(ListViews::ObjectType::STATE, ListViews::CHANGE, mpDataModel->getModel()->getKey());
    }
}

void
CQParameterEstimationResult::protocolFileChanged(const QString &fileName)
{
  QFileInfo info(fileName);

  if (!info.exists() || !info.isFile()) return;

  loadProtocol(fileName);
}

void
CQParameterEstimationResult::browseForProtocol()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Open Protocol", "", "TXT files (*.txt);;All files (*.*)");

  if (!fileName.isEmpty())
    loadProtocol(fileName);
}

void
CQParameterEstimationResult::toggleFitItems()
{
  ui->tblFitItems->setVisible(!ui->chkHideFitItems->isChecked());
}

ResultData *
CQParameterEstimationResult::getResult(int index)
{
  if (mResultData.empty()) return NULL;

  if (index == -1)
    {
      return mResultData.back();
    }

  if (index > (int)mResultData.size()) return NULL;

  return mResultData[index];
}

void
CQParameterEstimationResult::dataSetChanged()
{
  if (mInitializing) return;

  int currentIndex = ui->lstDataSets->currentIndex();
  ResultData *data = getResult(currentIndex);

  if (data == NULL) return;

  if (!data->appliesTo(mpDataModel))
    {
      QMessageBox::information(this, "The data set does not match this model",
                               "The protocol you loaded does not apply to this model, as it uses a different set of optimization items. Please load the model that produced the report.",
                               QMessageBox::Ok, QMessageBox::Ok);
    }

  while (ui->tblFitItems->rowCount() > 0)
    ui->tblFitItems->removeRow(0);

  for (std::vector<FittingItem *>::iterator it = data->mFittingItems.begin(); it != data->mFittingItems.end(); ++it)
    {
      FittingItem *item = *it;
      int row = ui->tblFitItems->rowCount();
      ui->tblFitItems->insertRow(row);
      ui->tblFitItems->setItem(row, 0, new QTableWidgetItem(item->mName.c_str()));
      ui->tblFitItems->setItem(row, 1, new QTableWidgetItem(convertToQString(item->mLowerBound)));
      ui->tblFitItems->setItem(row, 2, new QTableWidgetItem(convertToQString(item->mUpperBound)));
      ui->tblFitItems->setItem(row, 3, new QTableWidgetItem(convertToQString(item->mStartValue)));
      ui->tblFitItems->setItem(row, 4, new QTableWidgetItem(item->getAffectedExperiments().c_str()));
    }

  if (mpCheckPointModel != NULL)
    {
      mpCheckPointModel->removeAllRows();
      mpCheckPointModel->append(data->mCheckPoints);
    }
}
