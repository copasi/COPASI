// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_PARAMETER_ESTIMATION_UTILS_H
#define COPASI_PARAMETER_ESTIMATION_UTILS_H

#include <string>
#include <vector>

class CCopasiDataModel;
class CFitTask;
class COptTask;

void replaceAllSubStringsInPlace(std::string& str, const std::string& from, const std::string& to);

std::string sanitizeName(const std::string& name);

std::string& sanitizeName(std::string& name);

const std::string FUNCTION_EVAL = "[Function Eva";

struct FittingItem
{
  FittingItem();

  std::string mName;
  double mStartValue;
  double mLowerBound;
  double mUpperBound;
  std::vector<std::string> mAffectedExperiments;

  std::string getAffectedExperiments();
};

struct CheckPoint
{
  CheckPoint();

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

  ResultData();

  int numCheckPoints();

  int numFittingItems();

  ~ResultData();

  ResultData(const std::vector<FittingItem*>& fittingItems,
             const std::vector<CheckPoint*>& checkPoints,
             CCopasiDataModel* dataModel = NULL,
             bool isOptimization = false);

  bool appliesTo(CCopasiDataModel* dataModel);

  void updateFitItems();

  CFitTask* getFitTask();

  COptTask* getOptTask();

  void updateFitItemsFromOptItems(COptTask* optTask);

  void applyToModelState(int row, const std::vector<std::string>& priorities);

  FittingItem* getBestItem(const std::vector<FittingItem*>& items, const std::vector<std::string>& priorities);

  size_t getIndex(const std::vector<FittingItem*>& items, const FittingItem* item);

  std::vector<std::string> getAllExperiments();

  std::vector<FittingItem*> getItems(const std::string& displayName);

  double getBestValueFor(const std::string& name, CheckPoint* data, const std::vector<std::string>& priorities);

  void applyToModelStateFromOptTask(int row, COptTask* task, const std::vector<std::string>& priorities);

  void setTaskStartValues(int row);

  void setOptItemStartValues(int row, COptTask* optTask);
};

bool containsOptimization(const std::string& val);

class ResultParser
{
public:
  // trim from start
  static inline std::string &ltrim(std::string &s);

  // trim from end
  static inline std::string &rtrim(std::string &s);

  // trim from both ends
  static inline std::string &trim_in_place(std::string &s);

  static inline std::string trim(const std::string &s1);

  static std::vector<ResultData*>  parseContent(const std::string& content);

  static bool skipTo(std::istream& reader, const std::string& lineStart);

  static bool skipTo(std::istream& reader, const std::string& lineStart, bool& flag, bool(*eval)(const std::string&) = NULL);

  static FittingItem* parseItem(const std::string& line);

  static std::vector<FittingItem*> readItems(std::istream& reader, bool& flag);
  static std::vector<std::string> split(const std::string &s, char delim, bool removeEmpty = true);
  static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems, bool removeEmpty = true);

  static double saveToDouble(const std::string& doubleString, double defaultValue = 0);

  static int toInt32(const std::string& str);

  static CheckPoint* parseValue(const std::string& line);

  static std::vector<CheckPoint*> readValues(std::istream& reader);

  static std::vector<ResultData*> parseStream(std::istream& reader, CCopasiDataModel* dataModel = NULL);
  static std::vector<ResultData*> parseFile(const std::string& fileName, CCopasiDataModel* dataModel = NULL);

  static std::vector<ResultData*> fromFile(const std::string& fileName, CCopasiDataModel* dataModel = NULL);
};

#endif //COPASI_PARAMETER_ESTIMATION_UTILS_H
