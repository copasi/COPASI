// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CPROFILEGENERATOR_H
#define CPROFILEGENERATOR_H

#include <string>
#include <sstream>
#include <vector>

class CProfileSettings;
class CDataModel;
class COptTask;
class COptProblem;
class CCopasiParameterGroup;

struct CCurrentSolution
{
  bool mIsParameterEstimation;
  double mObjectiveValue;

  int mNumParameters;
  int mNumDataPoints;

  // now the opt items
  std::vector< double > mParameterValues;
  std::vector< double > mParameterSDs;
  std::vector< std::string > mParameterCNs;
  std::vector< std::string > mParameterNames;
};

struct CPLOptItem {
  std::string mCN;
  std::string mLower;
  std::string mUpper;
  std::string mCurrent;
};

class CProfileGenerator
{
  private:
    CDataModel* mpDM;
    CProfileSettings* mpSettings;
    std::stringstream mMessages;
    std::string mCpsModelFile;
    CCurrentSolution mCurrentSolution;
    COptTask* mpOptTask;
    COptProblem* mpOptProblem;

    std::string mPrefix;
    std::string mDirectory;

    std::string mLowerAdjustment;
    std::string mUpperAdjustment;

    void getCurrentSolution();

    void saveBaseModel();

    /**
     adjusts the given value according to the multiplier

     :param value: the value to be adjusted

     :param adjustment: the adjustment to be made to the value
         adjustment is a float: the value will be adjusted to `value * adjustment`
         adjustment is a string starting with '+', the value will be adjusted to `value + value * adjustment`
         adjustment contains a '%', the adjustment value is adjusted by dividing by 100
         adjustment starts with '=', the value will be adjusted to `adjustment`
         adjustment is None, or 'default': the explicit value given will be used

     :param explicitValue: the explicit value to be used if adjustment is empty or 'default'

     :return: the adjusted value
     */
    double getValueAdjustment(double value, std::string adjustment, double explicitValue=0.0, double std_dev=0.0);

  public:
    CProfileGenerator();
    virtual ~CProfileGenerator();
    void generateProfiles(CProfileSettings* pSettings, CDataModel* pDM);
    std::string getMessages() const;
};

#endif // CPROFILEGENERATOR_H
