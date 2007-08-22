// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelAnalyzer.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/22 23:59:49 $
// End CVS Header

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

    void writeReport(std::ostream & os, bool rt, bool longText) const;

  protected:
    class ReactionResult
      {
      public:
        ReactionResult()
            : mKineticUnspecifiedReversibility(false),
            mReversibilityMismatch(false)
        {}

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

        /**
         * writes a text report about the function to the stream. The return value
         * indicates if a problem was reported.
         */
        bool writeResult(std::ostream & os, bool rt, bool longText) const;
      };

    void checkModel(const CModel* model);

    ReactionResult checkReaction(const CReaction* reaction);

    //data

    const CModel* mpModel;

    std::vector<ReactionResult> mReactionResults;
  };

#endif
