// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "function/CFunctionAnalyzer.h"

class CModel;
class CReaction;

class CModelAnalyzer
{
public:

  CModelAnalyzer(const CModel* model);

  void writeReport(std::ostream & os, bool rt, bool verbose) const;

  class ReactionResult
  {
  public:
    ReactionResult()
      : mKineticUnspecifiedReversibility(false)
      , mReversibilityMismatch(false)
    {}

    /**
    * writes a text report about the function to the stream. The return value
    * indicates if a problem was reported.
    */
    bool writeResult(std::ostream & os, bool rt, bool verbose) const;

    const std::string& getName() const { return mReactionName;  }

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

  const std::vector<ReactionResult>& getReactionResults() const
  {
    return mReactionResults;
  }

protected:
  void checkModel(const CModel* model);

  ReactionResult checkReaction(const CReaction* reaction);

  //data

  const CModel* mpModel;

  std::vector<ReactionResult> mReactionResults;
};

#endif
