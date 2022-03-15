// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

#include <algorithm>
#include <functional>

#include <cctype>

#include <copasi/CopasiDataModel/CDataModel.h>

#include <copasi/model/CModel.h>
#include <copasi/math/CMathContainer.h>

#include <copasi/parameterFitting/CFitItem.h>
#include <copasi/parameterFitting/CFitProblem.h>
#include <copasi/parameterFitting/CFitTask.h>

#include <copasi/optimization/COptItem.h>
#include <copasi/optimization/COptProblem.h>
#include <copasi/optimization/COptTask.h>

#include <copasi/utilities/CCopasiTask.h>
#include <copasi/utilities/CParameterEstimationUtils.h>

void replaceAllSubStringsInPlace(std::string &str, const std::string &from, const std::string &to)
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

std::string sanitizeName(const std::string &name)
{
  if (name.empty()) return name;

  std::string copy(name);
  replaceAllSubStringsInPlace(copy, "\"", "");
  return copy;
}

std::string &sanitizeName(std::string &name)
{
  if (name.empty()) return name;

  replaceAllSubStringsInPlace(name, "\"", "");
  return name;
}

std::string FittingItem::getAffectedExperiments()
{
  std::stringstream str;

  for (std::vector<std::string>::iterator it = mAffectedExperiments.begin(); it != mAffectedExperiments.end(); ++it)
    str << *it << " ";

  return str.str();
}

FittingItem::FittingItem()
  : mName()
  , mStartValue(0)
  , mLowerBound(0)
  , mUpperBound(0)
  , mAffectedExperiments()
{
}

CheckPoint::CheckPoint()
  : mFunctionEvaluations(0)
  , mBestValue(0)
  , mParameters()
{
}

ResultData::ResultData()
  : mIsOptimization(false)
  , mpDataModel(NULL)
  , mFittingItems()
  , mCheckPoints()
{
}

int ResultData::numCheckPoints()
{
  return (int)mCheckPoints.size();
}

int ResultData::numFittingItems()
{
  return (int)mFittingItems.size();
}

ResultData::~ResultData()
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

ResultData::ResultData(const std::vector<FittingItem *> & fittingItems,
                       const std::vector<CheckPoint *> & checkPoints,
                       CDataModel * dataModel,
                       bool isOptimization)
  : mIsOptimization(isOptimization)
  , mpDataModel(dataModel)
  , mFittingItems(fittingItems.begin(), fittingItems.end())
  , mCheckPoints(checkPoints.begin(), checkPoints.end())
{}

bool ResultData::appliesTo(CDataModel * /* dataModel */)
{
  COptTask* task = NULL;

  if (mIsOptimization)
    {
      task = getOptTask();
    }
  else
    {
      task = getFitTask();
    }

  if (task == NULL) return false;

  COptProblem* problem = static_cast<COptProblem*>(task->getProblem());

  size_t taskItems = problem->getOptItemSize();

  if (taskItems > mFittingItems.size())
    return false;

  for (size_t i = 0; i < problem->getOptItemList().size(); ++i)
    {
      COptItem *item = static_cast<COptItem*>(problem->getOptItemList()[i]);
      std::string name = sanitizeName(item->getObjectDisplayName());

      if (mFittingItems[i]->mName != name)
        return false;
    }

  return true;
}

void ResultData::updateFitItems()
{
  if (mIsOptimization)
    updateFitItemsFromOptItems(getOptTask());
  else
    updateFitItemsFromOptItems(getFitTask());
}

CFitTask *ResultData::getFitTask()
{
  if (mpDataModel == NULL) return NULL;

  CDataVectorN<CCopasiTask>& taskList = *mpDataModel->getTaskList();

  for (size_t i = 0; i < taskList.size(); i++)
    {
      CFitTask* task = dynamic_cast<CFitTask*>(&taskList[i]);

      if (task != NULL)
        return task;
    }

  return NULL;
}

COptTask *ResultData::getOptTask()
{
  if (mpDataModel == NULL) return NULL;

  CDataVectorN<CCopasiTask>& taskList = *mpDataModel->getTaskList();

  COptTask* optTask = dynamic_cast<COptTask*>(&taskList["Optimization"]);

  if (optTask != NULL)
    return optTask;

  for (size_t i = 0; i < taskList.size(); i++)
    {
      COptTask* task = dynamic_cast<COptTask*>(&taskList[i]);

      if (task != NULL)
        return task;
    }

  return NULL;
}

void ResultData::updateFitItemsFromOptItems(COptTask *optTask)
{
  if (optTask == NULL)
    return;

  COptProblem *problem = (COptProblem*)optTask->getProblem();

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

void ResultData::applyToModelState(int row, const std::vector<std::string> &priorities)
{
  if (mIsOptimization)
    applyToModelStateFromOptTask(row, getOptTask(), priorities);
  else
    applyToModelStateFromOptTask(row, getFitTask(), priorities);
}

FittingItem *ResultData::getBestItem(const std::vector<FittingItem *> &items, const std::vector<std::string> &priorities)
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

size_t ResultData::getIndex(const std::vector<FittingItem *> &items, const FittingItem *item)
{
  for (size_t i = 0; i < items.size(); ++i)
    if (items[i] == item)
      return i;

  return 0;
}

std::vector<std::string> ResultData::getAllExperiments()
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

std::vector<FittingItem *> ResultData::getItems(const std::string &displayName)
{
  std::string name = sanitizeName(displayName);
  std::vector<FittingItem*> result;

  for (std::vector<FittingItem*>::iterator it = mFittingItems.begin(); it != mFittingItems.end(); ++it)
    if ((*it)->mName == name)
      result.push_back(*it);

  return result;
}

double ResultData::getBestValueFor(const std::string &name, CheckPoint *data, const std::vector<std::string> &priorities)
{
  FittingItem* item = getBestItem(getItems(name), priorities);
  size_t index = getIndex(mFittingItems, item);
  return data->mParameters[index];
}

void ResultData::applyToModelStateFromOptTask(int row, COptTask *task, const std::vector<std::string> &priorities)
{
  if (task == NULL || mpDataModel == NULL)
    return;

  if (row >= (int)mCheckPoints.size())
    return;

  CheckPoint* data = mCheckPoints[row];

  if (data == NULL)
    return;

  COptProblem * pProblem = static_cast<COptProblem*>(task->getProblem());
  CMathContainer  * pContainer = pProblem->getMathContainer();
  CObjectInterface::ContainerList ContainerList;
  ContainerList.push_back(pContainer);
  CObjectInterface::ObjectSet ChangedObjects;

  std::vector< COptItem * >::const_iterator it = pProblem->getOptItemList().begin();
  std::vector< COptItem * >::const_iterator end = pProblem->getOptItemList().end();

  for (; it != end; ++it)
    {
      CObjectInterface * pObjectInterface = CObjectInterface::GetObjectFromCN(ContainerList, (*it)->getObjectCN());

      if (pObjectInterface == NULL) continue;

      double bestValue = getBestValueFor((*it)->getObjectDisplayName(), data, priorities);
      * (C_FLOAT64 *) pObjectInterface->getValuePointer() = bestValue;
      ChangedObjects.insert(pObjectInterface);
    }

  CCore::CUpdateSequence UpdateSequence;
  pContainer->getInitialDependencies().getUpdateSequence(UpdateSequence, CCore::SimulationContext::UpdateMoieties, ChangedObjects, pContainer->getInitialStateObjects());
  pContainer->applyUpdateSequence(UpdateSequence);
  pContainer->pushInitialState();
}

void ResultData::setTaskStartValues(int row)
{
  if (mIsOptimization)
    setOptItemStartValues(row, getOptTask());
  else setOptItemStartValues(row, getFitTask());
}

void ResultData::setOptItemStartValues(int row, COptTask *optTask)
{
  if (optTask == NULL || mpDataModel == NULL)
    return;

  if (row >= (int)mCheckPoints.size())
    return;

  CheckPoint* data = mCheckPoints[row];

  if (data == NULL)
    return;

  COptProblem* problem = (COptProblem*)optTask->getProblem();

  for (size_t i = 0; i < problem->getOptItemList().size(); i++)
    {
      COptItem *item = (COptItem*)(problem->getOptItemList()[i]);
      item->setStartValue(data->mParameters[i]);
    }
}

bool containsOptimization(const std::string &val)
{
  return val.find("Optimization") != std::string::npos;
}

std::string &ResultParser::ltrim(std::string &s)
{
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
  {
    return !std::isspace(ch);
  }));
  return s;
}

std::string &ResultParser::rtrim(std::string &s)
{
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
  {
    return !std::isspace(ch);
  }).base(), s.end());
  return s;
}

std::string &ResultParser::trim_in_place(std::string &s)
{
  return ltrim(rtrim(s));
}

std::string ResultParser::trim(const std::string &s1)
{
  std::string s(s1);
  return ltrim(rtrim(s));
}

std::vector<ResultData *> ResultParser::parseContent(const std::string &content)
{
  std::istringstream ss(content);
  return parseStream(ss);
}

bool ResultParser::skipTo(std::istream &reader, const std::string &lineStart)
{
  bool test;
  return skipTo(reader, lineStart, test);
}

bool ResultParser::skipTo(std::istream &reader, const std::string &lineStart, bool &flag, bool (*eval)(const std::string &))
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

FittingItem *ResultParser::parseItem(const std::string &line)
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

std::vector<FittingItem *> ResultParser::readItems(std::istream &reader, bool &flag)
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

std::vector<std::string> ResultParser::split(const std::string &s, char delim, bool removeEmpty)
{
  std::vector<std::string> elems;
  return split(s, delim, elems, removeEmpty);
}

std::vector<std::string> &ResultParser::split(const std::string &s, char delim, std::vector<std::string> &elems, bool removeEmpty)
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

std::vector<std::string>& ResultParser::split(const std::string& seq, const std::string& delims, std::vector<std::string>& elems)
{
  std::stringstream tmp;

  for (size_t i = 0; i < seq.length(); ++i)
    {
      char cur = seq[i];
      bool shouldContinue = false;

      for (size_t j = 0; j < delims.length(); ++j)
        if (cur == delims[j])
          {
            shouldContinue = true;
            break;
          }

      if (shouldContinue)
        {
          std::string str = tmp.str();

          if (!str.empty())
            {
              elems.push_back(str);
              tmp.str("");
            }

          continue;
        }

      tmp << cur;
    }

  std::string str = tmp.str();

  if (!str.empty())
    {
      elems.push_back(str);
    }

  return elems;
}

double ResultParser::saveToDouble(const std::string &doubleString, double defaultValue)
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

int ResultParser::toInt32(const std::string &str)
{
  std::stringstream ss(str);
  int result = 0; ss >> result;
  return result;
}

CheckPoint *ResultParser::parseValue(const std::string &line)
{
  std::string::size_type firstTab = line.find("\t");

  if (firstTab == std::string::npos) return NULL;

  CheckPoint* result = new CheckPoint();

  result->mFunctionEvaluations = toInt32(line.substr(0, firstTab));
  std::string::size_type open = line.find("(");
  result->mBestValue = saveToDouble((const std::string&)line.substr(firstTab + 1, open - (firstTab + 1)));
  std::vector<std::string> rawValues = split(line.substr(open + 1, line.rfind(')') - (open + 1)), '\t');

  for (std::vector<std::string>::iterator it = rawValues.begin(); it != rawValues.end(); ++it)
    result->mParameters.push_back(saveToDouble(*it));

  return result;
}

std::vector<CheckPoint *> ResultParser::readValues(std::istream &reader)
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

std::vector<ResultData *> ResultParser::parseStream(std::istream &reader, CDataModel *dataModel)
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

std::vector<ResultData *> ResultParser::parseFile(const std::string &fileName, CDataModel *dataModel)
{
  std::ifstream ifs(fileName.c_str(), std::ios_base::in);

  return parseStream(ifs, dataModel);
}

std::vector<ResultData *> ResultParser::fromFile(const std::string &fileName, CDataModel *dataModel)
{
  return parseFile(fileName, dataModel);
}
