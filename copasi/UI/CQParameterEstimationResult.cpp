// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QFile>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QCompleter>
#include <QMessageBox>
#include <QListView>
#include <QStandardItemModel>

#include <copasi/CopasiDataModel/CCopasiDataModel.h>
#include <copasi/model/CModel.h>

#include <copasi/parameterFitting/CFitItem.h>
#include <copasi/parameterFitting/CFitProblem.h>
#include <copasi/parameterFitting/CFitTask.h>
#include <copasi/optimization/COptItem.h>
#include <copasi/optimization/COptProblem.h>
#include <copasi/optimization/COptTask.h>
#include <copasi/utilities/CCopasiTask.h>
#include <copasi/utilities/CCopasiVector.h>

#pragma region

void replaceAllSubStrings(std::string& str, const std::string& from, const std::string& to)
{
  if (from.empty())
    return;

  size_t start_pos = 0;

  while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

std::string sanitizeName(const std::string& name)
{
  if (name.empty()) return name;

  std::string copy(name);
  replaceAllSubStrings(copy, "\"", "");
  return copy;
}

std::string& sanitizeName(std::string& name)
{
  if (name.empty()) return name;

  replaceAllSubStrings(name, "\"", "");
  return name;
}

const std::string FUNCTION_EVAL = "[Function Eva";

struct FittingItem
{
  FittingItem()
    : mName()
    , mStartValue(0)
    , mLowerBound(0)
    , mUpperBound(0)
    , mAffectedExperiments()
  {
  }

  std::string mName;
  double mStartValue;
  double mLowerBound;
  double mUpperBound;
  std::vector<std::string> mAffectedExperiments;

  std::string getAffectedExperiments()
  {
    std::stringstream str;

    for (std::vector<std::string>::iterator it = mAffectedExperiments.begin(); it != mAffectedExperiments.end(); ++it)
      str << *it << " ";

    return str.str();
  }
};

struct CheckPoint
{
  CheckPoint()
    : mFunctionEvaluations(0)
    , mBestValue(0)
    , mParameters()
  {
  }

  int mFunctionEvaluations;
  double mBestValue;
  std::vector<double> mParameters;
};

class ResultData
{
public:
  bool mIsOptimization;
  CCopasiDataModel*  mpDataModel;
  std::vector<FittingItem*> mFittingItems;
  std::vector<CheckPoint*> mCheckPoints;

  ResultData()
    : mIsOptimization(false)
    , mpDataModel(NULL)
    , mFittingItems()
    , mCheckPoints()
  {
  }

  ~ResultData()
  {
    std::vector<CheckPoint*>::iterator it = mCheckPoints.begin();

    while (it != mCheckPoints.end())
      {
        delete *it;
        ++it;
      }

    mCheckPoints.clear();

    std::vector<FittingItem*>::iterator it1 = mFittingItems.begin();

    while (it1 != mFittingItems.end())
      {
        delete *it1;
        ++it1;
      }

    mFittingItems.clear();
  }

  ResultData(const std::vector<FittingItem*>& fittingItems,
             const std::vector<CheckPoint*>& checkPoints,
             CCopasiDataModel* dataModel = NULL,
             bool isOptimization = false)

    : mIsOptimization(isOptimization)
    , mpDataModel(dataModel)
    , mFittingItems(fittingItems.begin(), fittingItems.end())
    , mCheckPoints(checkPoints.begin(), checkPoints.end())
  {
  }

  bool appliesTo(CCopasiDataModel* dataModel)
  {
    COptTask* task = NULL;

    if (mIsOptimization) task = getOptTask();
    else task = getFitTask();

    if (task == NULL) return false;

    COptProblem* problem = static_cast<COptProblem*>(task->getProblem());
    problem->setModel(dataModel->getModel());

    uint taskItems = problem->getOptItemSize();

    if (taskItems > mFittingItems.size())
      return false;

    for (int i = 0; i < problem->getOptItemList().size(); ++i)
      {
        COptItem *item = static_cast<COptItem*>(problem->getOptItemList()[i]);
        std::string name = sanitizeName(item->getObjectDisplayName());

        if (mFittingItems[i]->mName != name)
          return false;
      }

    return true;
  }

  void updateFitItems()
  {
    if (mIsOptimization)
      updateFitItemsFromOptItems(getOptTask());
    else
      updateFitItemsFromOptItems(getFitTask());
  }

  CFitTask* getFitTask()
  {
    if (mpDataModel == NULL) return NULL;

    CCopasiVectorN<CCopasiTask>& taskList = *mpDataModel->getTaskList();

    for (uint i = 0; i < taskList.size(); i++)
      {
        CFitTask* task = dynamic_cast<CFitTask*>(taskList[i]);

        if (task != NULL)
          return task;
      }

    return NULL;
  }

  COptTask* getOptTask()
  {
    if (mpDataModel == NULL) return NULL;

    CCopasiVectorN<CCopasiTask>& taskList = *mpDataModel->getTaskList();

    COptTask* optTask = dynamic_cast<COptTask*>(taskList["Optimization"]);

    if (optTask != NULL)
      return optTask;

    for (uint i = 0; i < taskList.size(); i++)
      {
        COptTask* task = dynamic_cast<COptTask*>(taskList[i]);

        if (task != NULL)
          return task;
      }

    return NULL;
  }

  void updateFitItemsFromOptItems(COptTask* optTask)
  {
    if (optTask == NULL)
      return;

    COptProblem *problem = (COptProblem*)optTask->getProblem();
    problem->setModel(mpDataModel->getModel());

    for (size_t i = 0; i < problem->getOptItemList().size(); i++)
      {
        COptItem *item = (COptItem*)(problem->getOptItemList()[i]);

        std::string displayName = sanitizeName(item->getObjectDisplayName());

        FittingItem* currentItem = mFittingItems[i];

        if (currentItem == NULL)
          continue;

        if (currentItem->mName != displayName)
          {
            std::cerr << "Names don't match !" << std::endl;
          }

        currentItem->mStartValue = item->getStartValue();
        currentItem->mLowerBound = *item->getLowerBoundValue();
        currentItem->mUpperBound = *item->getUpperBoundValue();
      }
  }

  void applyToModelState(int row, const std::vector<std::string>& priorities)
  {
    if (mIsOptimization)
      applyToModelStateFromOptTask(row, getOptTask(), priorities);
    else
      applyToModelStateFromOptTask(row, getFitTask(), priorities);
  }

  FittingItem* getBestItem(const std::vector<FittingItem*>& items, const std::vector<std::string>& priorities)
  {
    if (items.empty())
      return NULL;

    std::vector<std::string>::const_iterator it = priorities.begin();
    std::vector<FittingItem*>::const_iterator it2;

    while (it != priorities.end())
      {
        for (it2 = items.begin(); it2 != items.end(); ++it2)
          {
            if (std::find((*it2)->mAffectedExperiments.begin(), (*it2)->mAffectedExperiments.end(), *it) != (*it2)->mAffectedExperiments.end())
              return *it2;
          }

        ++it;
      }

    return items[0];
  }

  size_t getIndex(const std::vector<FittingItem*>& items, const FittingItem* item)
  {
    for (size_t i = 0; i < items.size(); ++i)
      if (items[i] == item)
        return i;

    return 0;
  }

  std::vector<std::string> getAllExperiments()
  {
    std::vector < std::string >  result;
    std::vector <FittingItem* > ::iterator it;

    for (it = mFittingItems.begin(); it != mFittingItems.end(); ++it)
      {
        for (std::vector<std::string>::iterator it2 = (*it)->mAffectedExperiments.begin();
             it2 != (*it)->mAffectedExperiments.end(); ++it2)
          {
            if ((*it2) != "all" && std::find(result.begin(), result.end(), *it2) == result.end())
              result.push_back(*it2);
          }
      }

    return result;
  }

  std::vector<FittingItem*> getItems(const std::string& displayName)
  {
    std::string name = sanitizeName(displayName);
    std::vector<FittingItem*> result;

    for (std::vector<FittingItem*>::iterator it = mFittingItems.begin(); it != mFittingItems.end(); ++it)
      if ((*it)->mName == name)
        result.push_back(*it);

    return result;
  }

  double getBestValueFor(const std::string& name, CheckPoint* data, const std::vector<std::string>& priorities)
  {
    FittingItem* item = getBestItem(getItems(name), priorities);
    size_t index = getIndex(mFittingItems, item);
    return data->mParameters[index];
  }

  void applyToModelStateFromOptTask(int row, COptTask* task, const std::vector<std::string>& priorities)
  {
    if (task == NULL || mpDataModel == NULL)
      return;

    if (row >= (int)mCheckPoints.size())
      return;

    CheckPoint* data = mCheckPoints[row];

    if (data == NULL)
      return;

    COptProblem* problem = static_cast<COptProblem*>(task->getProblem());
    problem->setModel(mpDataModel->getModel());
    std::set< const CCopasiObject * > changedObjects;

    for (unsigned int i = 0; i < problem->getOptItemList().size(); i++)
      {
        COptItem *item = static_cast<COptItem*>(problem->getOptItemList()[i]);
        const CObjectInterface* modelItem = mpDataModel->getObject(item->getObjectCN());
        CCopasiObject *current = mpDataModel->getDataObject(modelItem->getCN());
        double bestValue = getBestValueFor(item->getObjectDisplayName(), data, priorities);

        if (dynamic_cast<CCopasiParameter*>(current) != NULL)
          (static_cast<CCopasiParameter*>(current))->setValue(bestValue);
        else
          {
            current->setObjectValue(bestValue);
            changedObjects.insert(current);
          }
      }

    mpDataModel->getModel()->updateInitialValues(changedObjects);
  }

  void setTaskStartValues(int row)
  {
    if (mIsOptimization)
      setOptItemStartValues(row, getOptTask());
    else setOptItemStartValues(row, getFitTask());
  }

  void setOptItemStartValues(int row, COptTask* optTask)
  {
    if (optTask == NULL || mpDataModel == NULL)
      return;

    if (row >= (int)mCheckPoints.size())
      return;

    CheckPoint* data = mCheckPoints[row];

    if (data == NULL)
      return;

    COptProblem* problem = (COptProblem*)optTask->getProblem();
    problem->setModel(mpDataModel->getModel());

    for (size_t i = 0; i < problem->getOptItemList().size(); i++)
      {
        COptItem *item = (COptItem*)(problem->getOptItemList()[i]);
        item->setStartValue(data->mParameters[i]);
      }
  }
};

bool containsOptimization(const std::string& val)
{
  return val.find("Optimization") != std::string::npos;
}

class ResultParser
{
public:
  // trim from start
  static inline std::string &ltrim(std::string &s)
  {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
  }

  // trim from end
  static inline std::string &rtrim(std::string &s)
  {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
  }

  // trim from both ends
  static inline std::string &trim_in_place(std::string &s)
  {
    return ltrim(rtrim(s));
  }

  static inline std::string trim(const std::string &s1)
  {
    std::string s(s1);
    return ltrim(rtrim(s));
  }

  static std::vector<ResultData*>  parseContent(const std::string& content)
  {
    std::istringstream ss(content);
    return parseStream(ss);
  }

  static bool skipTo(std::istream& reader, const std::string& lineStart)
  {
    bool test;
    return skipTo(reader, lineStart, test);
  }

  static bool skipTo(std::istream& reader, const std::string& lineStart, bool& flag, bool(*eval)(const std::string&) = NULL)
  {
    std::string line;
    flag = false;

    while (reader.good())
      {
        std::getline(reader, line, '\n');
        line = trim(line);

        if (line.find(lineStart) == 0)
          {
            if (eval != NULL)
              flag = eval(line);

            return true;
          }

        continue;
      }

    return  false;
  }

  static FittingItem* parseItem(const std::string& line)
  {
    FittingItem* item = new FittingItem();

    std::string::size_type lastEq = line.rfind("=");

    if (lastEq == std::string::npos)
      return NULL;

    item->mStartValue = saveToDouble(line.substr(lastEq + 1));
    std::string::size_type firstLeq = line.find("<=");

    if (firstLeq == -1)
      return NULL;

    item->mLowerBound = saveToDouble(line.substr(0, firstLeq));
    std::string::size_type lastLeq = line.find("<=", firstLeq + 2);
    std::string::size_type square = line.find("]", firstLeq + 2);

    if (square == -1)
      square = line.find(")", firstLeq + 2);

    std::string::size_type lastSep = line.find(";", square);
    std::string substring = line.substr(lastLeq + 2, lastSep - (lastLeq + 2));
    item->mUpperBound = saveToDouble(substring);
    item->mName = trim(line.substr(firstLeq + 2, lastLeq - (firstLeq + 2)));
    sanitizeName(item->mName);

    return item;
  }

  static std::vector<FittingItem*> readItems(std::istream& reader, bool& flag)
  {
    std::vector<FittingItem*> result;
    std::string line;
    flag = false;
    bool foundStart = skipTo(reader, "List of ", flag,
                             containsOptimization
                            );

    if (!foundStart)
      {
        return result;
      }

    FittingItem *current = NULL;

    while (reader.good())
      {
        std::getline(reader, line, '\n');
        line = trim(line);
readNext:

        if (line.empty())
          return result;

        current = parseItem(line);

        if (current == NULL)
          break;

        if (flag)
          {
            result.push_back(current);
            continue;
          }

        std::getline(reader, line, '\n');

readExp:
        std::string experiments;
        std::getline(reader, experiments, '\n');
        std::string trimmedExperiment = trim(experiments);
        bool isExp = !trimmedExperiment.empty() && trim(experiments.substr(0, 6)).empty();

        if (isExp)
          {
            std::string::size_type index = experiments.find("Affected Cross Validation Experiments");

            if (index != std::string::npos)
              {
                experiments = experiments.substr(0, index);
                std::getline(reader, line, '\n');
              }
            else
              {
                index = experiments.find("Affected Validation Experiments");

                if (index != std::string::npos)
                  {
                    experiments = experiments.substr(0, index);
                    std::getline(reader, line, '\n');
                  }
              }

            current->mAffectedExperiments = split(trim(experiments), ',');
            goto readExp;
          }
        else
          {
            result.push_back(current);
            line = experiments;
            goto readNext;
          }
      }

    return result;
  }
  static std::vector<std::string> split(const std::string &s, char delim, bool removeEmpty = true)
  {
    std::vector<std::string> elems;
    return split(s, delim, elems, removeEmpty);
  }
  static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems, bool removeEmpty = true)
  {
    if (s.empty())
      return elems;

    if (s.find(delim) == std::string::npos)
      {
        elems.push_back(s);
        return elems;
      }

    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim))
      {
        item = trim(item);

        if (!removeEmpty || !item.empty())
          elems.push_back(item);
      }

    return elems;
  }

  static double saveToDouble(const std::string& doubleString, double defaultValue = 0)
  {
    if (doubleString.empty())
      return defaultValue;

    std::string current = trim(doubleString);
    std::transform(current.begin(), current.end(), current.begin(), ::tolower);

    if (current == "inf" || current == "1.#inf")
      return std::numeric_limits<double>::infinity();
    else if (current == "-inf" || current == "-1.#inf")
      return -std::numeric_limits<double>::infinity();
    else if (current == "nan" || current == "1.#nan")
      return std::numeric_limits<double>::quiet_NaN();

    std::stringstream ss(doubleString);
    double result = 0;
    ss >> result;
    return result;
  }

  static int toInt32(const std::string& str)
  {
    std::stringstream ss(str);
    int result = 0; ss >> result;
    return result;
  }

  static CheckPoint* parseValue(const std::string& line)
  {
    CheckPoint* result = new CheckPoint();

    std::string::size_type firstTab = line.find("\t");

    if (firstTab == std::string::npos) return NULL;

    result->mFunctionEvaluations = toInt32(line.substr(0, firstTab));
    std::string::size_type open = line.find("(");
    result->mBestValue = saveToDouble((const std::string&)line.substr(firstTab + 1, open - (firstTab + 1)));
    std::vector<std::string> rawValues = split(line.substr(open + 1, line.rfind(')') - (open + 1)), '\t');

    for (std::vector<std::string>::iterator it = rawValues.begin(); it != rawValues.end(); ++it)
      result->mParameters.push_back(saveToDouble(*it));

    return result;
  }

  static std::vector<CheckPoint*> readValues(std::istream& reader)
  {
    std::vector<CheckPoint*> result;

    std::string line;
    bool foundStart = skipTo(reader, FUNCTION_EVAL);

    if (!foundStart)
      {
        return result;
      }

    while (reader.good())
      {
        std::getline(reader, line, '\n');

        if (line.empty())
          return result;

        CheckPoint* item = parseValue(line);

        if (item == NULL)
          break;

        result.push_back(item);
      }

    return result;
  }

  static std::vector<ResultData*> parseStream(std::istream& reader, CCopasiDataModel* dataModel = NULL)
  {
    std::vector<ResultData*> list;

    while (reader.good())
      {
        bool flag = false;
        std::vector<FittingItem*> items = readItems(reader, flag);
        std::vector<CheckPoint*> values = readValues(reader);

        if (items.empty() || values.empty())
          continue;

        ResultData* result = new ResultData(items, values, dataModel, flag);
        list.push_back(result);
      }

    return list;
  }
  static std::vector<ResultData*> parseFile(const std::string& fileName, CCopasiDataModel* dataModel = NULL)
  {
    std::ifstream ifs(fileName.c_str(), std::ios_base::in);

    return parseStream(ifs, dataModel);
  }

  static std::vector<ResultData*> fromFile(const std::string& fileName, CCopasiDataModel* dataModel = NULL)
  {
    return parseFile(fileName, dataModel);
  }
};

#pragma endregion // reading data

CQParameterEstimationResult::CQParameterEstimationResult(QWidget *parent,
    CCopasiDataModel* dataModel)
  : QDialog(parent)
  , ui(new Ui::CQParameterEstimationResult)
  , mResultData()
  , mpDataModel(dataModel)
{
  ui->setupUi(this);

  QCompleter* completer = new QCompleter(this);
  completer->setCompletionMode(QCompleter::PopupCompletion);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  QFileSystemModel* model = new QFileSystemModel(completer);
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
  ui->lstDataSets->clear();

  for (std::vector<ResultData*>::iterator it = mResultData.begin(); it != mResultData.end(); ++it)
    ui->lstDataSets->addItem(QString("DataSet_%1").arg(ui->lstDataSets->count() + 1));

  ResultData* data = getResult(0);
  ui->tblResults->clear();

  if (data != NULL)
    {
      ui->tblResults->setColumnCount(data->mFittingItems.size() + 2);
      ui->tblResults->setHorizontalHeaderItem(0, new QTableWidgetItem("Function Evaluations"));
      ui->tblResults->setHorizontalHeaderItem(1, new QTableWidgetItem("Best Value"));
      int count = 1;

      for (std::vector<FittingItem*>::iterator it = data->mFittingItems.begin(); it != data->mFittingItems.end(); ++it)
        {
          ui->tblResults->setHorizontalHeaderItem(++count, new QTableWidgetItem((*it)->mName.c_str()));
        }
    }

  if (ui->lstDataSets->count() > 0)
    ui->lstDataSets->setCurrentIndex(ui->lstDataSets->count() - 1);
}

void
CQParameterEstimationResult::deleteData()
{
  std::vector<ResultData*>::iterator it = mResultData.begin();

  while (it != mResultData.end())
    {
      delete *it;
      ++it;
    }

  mResultData.clear();
}

void
CQParameterEstimationResult::loadProtocol(const QString& fileName)
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
  ResultData* data = getResult(ui->lstDataSets->currentIndex());

  if (data == NULL) return;

  data->updateFitItems();

  dataSetChanged();
}

void
CQParameterEstimationResult::setTaskStartValues()
{
  ResultData* data = getResult(ui->lstDataSets->currentIndex());

  if (data == NULL) return;

  QList<QTableWidgetItem*> selectedItems = ui->tblResults->selectedItems();

  if (selectedItems.empty())
    {
      QMessageBox::information(this, "No row selected",
                               "Before setting start values, please select a result row, from which the values should be taken.",
                               QMessageBox::Ok, QMessageBox::Ok);
      return;
    }

  data->setTaskStartValues(selectedItems.at(0)->row());
}

void
CQParameterEstimationResult::applyToModelState()
{
  ResultData* data = getResult(ui->lstDataSets->currentIndex());

  if (data == NULL) return;

  QList<QTableWidgetItem*> selectedItems = ui->tblResults->selectedItems();

  if (selectedItems.empty())
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
      QVBoxLayout* verticalLayout = new QVBoxLayout(dialog);
      QLabel* label = new QLabel(dialog);
      verticalLayout->addWidget(label);
      label->setText("Please drag and drop the experiments into the order in which to apply the values.");
      QListView* listView = new QListView(dialog);
      verticalLayout->addWidget(listView);
      QStandardItemModel* model = new QStandardItemModel(this);

      for (std::vector<std::string>::iterator it = experiments.begin();
           it != experiments.end(); ++it)
        {
          int current = model->rowCount();
          QStandardItem* item = new QStandardItem((*it).c_str());
          item->setFlags(item->flags() ^ Qt::ItemIsDropEnabled);
          model->appendRow(item);
        }

      listView->setModel(model);
      listView->setDragEnabled(true);
      listView->setAcceptDrops(true);
      listView->setDragDropMode(QAbstractItemView::InternalMove);
      listView->showDropIndicator();

      QDialogButtonBox* group = new QDialogButtonBox(dialog);
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

  data->applyToModelState(selectedItems.at(0)->row(), experiments);
}

void
CQParameterEstimationResult::protocolFileChanged(const QString& fileName)
{
  if (!QFile(fileName).exists()) return;

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

ResultData*
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
  int currentIndex = ui->lstDataSets->currentIndex();
  ResultData* data = getResult(currentIndex);

  if (data == NULL) return;

  if (!data->appliesTo(mpDataModel))
    {
      QMessageBox::information(this, "The data set does not match this model",
                               "The protocol you loaded does not apply to this model, as it uses a different set of optimization items. Please load the model that produced the report.",
                               QMessageBox::Ok, QMessageBox::Ok);
    }

  //ui->tblFitItems->clearContents();
  while (ui->tblFitItems->rowCount() > 0)
    ui->tblFitItems->removeRow(0);

  for (std::vector<FittingItem*>::iterator it = data->mFittingItems.begin(); it != data->mFittingItems.end(); ++it)
    {
      FittingItem* item = *it;
      int row = ui->tblFitItems->rowCount();
      ui->tblFitItems->insertRow(row);
      ui->tblFitItems->setItem(row, 0, new QTableWidgetItem(item->mName.c_str()));
      ui->tblFitItems->setItem(row, 1, new QTableWidgetItem(QString::number(item->mLowerBound)));
      ui->tblFitItems->setItem(row, 2, new QTableWidgetItem(QString::number(item->mUpperBound)));
      ui->tblFitItems->setItem(row, 3, new QTableWidgetItem(QString::number(item->mStartValue)));
      ui->tblFitItems->setItem(row, 4, new QTableWidgetItem(item->getAffectedExperiments().c_str()));
    }

  //ui->tblResults->clearContents();
  while (ui->tblResults->rowCount() > 0)
    ui->tblResults->removeRow(0);

  for (std::vector<CheckPoint*>::iterator it1 = data->mCheckPoints.begin();
       it1 != data->mCheckPoints.end(); ++it1)
    {
      CheckPoint* checkPoint = *it1;
      int row = ui->tblResults->rowCount();
      ui->tblResults->insertRow(row);
      ui->tblResults->setItem(row, 0, new QTableWidgetItem(QString::number(checkPoint->mFunctionEvaluations)));
      ui->tblResults->setItem(row, 1, new QTableWidgetItem(QString::number(checkPoint->mBestValue)));

      int count = 1;

      for (std::vector<double>::iterator it2 = checkPoint->mParameters.begin();
           it2 != checkPoint->mParameters.end(); ++it2)
        ui->tblResults->setItem(row, ++count, new QTableWidgetItem(QString::number(*it2)));
    }
}
