// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CModelAnalyzer
#define COPASI_CModelAnalyzer

#include <vector>
#include <string>

#include "copasi/function/CFunctionAnalyzer.h"

class CModel;
class CReaction;

class CReactionResult
{
public:
  CReactionResult();
  virtual ~CReactionResult();

  /**
  * writes a text report about the function to the stream. The return value
  * indicates if a problem was reported.
  *
  * @param rt use html wrapping / colors
  * @param verbose add more information
  * @param writeToStream boolean indicating whether results should be
  *               written to stream (default), or only checked whether there was an issue
  *
  * @return boolean indicating whether there was an issue or not
  */
  bool writeResult(std::ostream& os, bool rt, bool verbose, bool writeToStream = true) const;

  /**
   * @return true, if the analysis showed there was an issue with the reaction
   *         false otherwise
   */
  bool hasIssue() const;

  /**
   * @param rt use html wrapping / colors
   * @param verbose add more information
   *
   * @return the string representation of the result
   */
  std::string getResultString(bool rt, bool verbose) const;

  /**
   * @return the name of the reaction for this result
   */
  const std::string& getName() const;

protected:
  std::string mReactionName;
  bool mKineticUnspecifiedReversibility;
  bool mReversibilityMismatch;
  std::vector<std::string> mChemEqSubs;
  std::vector<std::string> mChemEqProds;
  std::vector<std::string> mChemEqMods;

  std::vector<std::string> mNotMetabolite;
  std::vector<std::string> mFunctionParametersSubs;
  std::vector<std::string> mFunctionParametersProds;
  std::vector<std::string> mFunctionParametersMods;
  std::vector<std::string> mFunctionParametersParams;
  std::vector<std::string> mFunctionParametersVol;
  std::vector<std::string> mFunctionParametersTime;
  std::vector<std::string> mFunctionParametersVar;

  CFunctionAnalyzer::Result mFunctionResult;

  friend class CModelAnalyzer;
};


class CModelAnalyzer
{
public:

  CModelAnalyzer(const CModel* model);

  void writeReport(std::ostream & os, bool rt, bool verbose) const;

  const std::vector<CReactionResult>& getReactionResults() const;

protected:
  void checkModel(const CModel* model);

  CReactionResult checkReaction(const CReaction* reaction);

  //data

  const CModel* mpModel;

  std::vector<CReactionResult> mReactionResults;
};

#endif
