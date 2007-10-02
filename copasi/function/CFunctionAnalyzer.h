// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionAnalyzer.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/10/02 18:18:03 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CFunctionAnalyzer
#define COPASI_CFunctionAnalyzer

#include <vector>

class CEvaluationNode;
class CModel;
class CReaction;
class CFunction;
class CFunctionParameters;

/**
 * This class performs an analysis of a kinetic function. The function
 * to analyze is passed to the constructor. The result can be retrieved
 * with the getResult() method. The Result class has methods for reporting.
 * The reporting methods may assume that the function (and possibly the reaction)
 * still exists, so don't delete the function between the analysis and the
 * reporting of the results!
 */
class CFunctionAnalyzer
  {
  public:
    /**
    * This is the base class of the arithmetics of the function analyzer. It describes possibilities for values.
    * It basically consists of some flags that tell whether the value can be positive, can be negative, can
    * be zero, or invalid, or if an actual exact numerical value is known.
    * The usual arithmetic operators are defined for this class, the most important functions need to be
    * implemented still. The missing functions are not critical since there is a save fallback: If you do not
    * know how to perform a specific operation on CValues, the result should be (unknown|invalid).
    */
    class CValue
      {
      public:
        enum Status
        {
          novalue = 0,
          negative = 1,
          zero = 2,
          positive = 4,
          invalid = 8,
          known = 16,
          unknown = 7
        };

        CValue()
            : mStatus(Status(novalue)), mDouble(0.0) {};

        CValue(Status status)
            : mStatus(status), mDouble(0.0) {};

        CValue(const double & d)
            : mStatus(known), mDouble(d) {};

        const double & getValue() const {return mDouble;};

        /**
         * set value to be the only possible value
         */
        void setValue(const double & value) {mDouble = value; mStatus = known;};

        const Status & getStatus() const {return mStatus;};

        void setStatus(const Status & status) {mStatus = status;};

        CValue operator*(const CValue & rhs) const;
        CValue operator/(const CValue & rhs) const;
        CValue operator+(const CValue & rhs) const;
        CValue operator-(const CValue & rhs) const;
        CValue operator^(const CValue & rhs) const;

        bool isPositive() const;
        bool containsPositive() const;
        bool isZero() const;
        bool containsZero() const;
        bool isNegative() const;
        bool containsNegative() const;
        bool isInvalid() const;
        bool containsInvalid() const;

        bool operator==(const CValue & rhs) const;
        CValue invert() const;

      protected:

        /**
         * convert a CValue with status "known" to a more general status.
         */
        //      CValue generalize() const;

        static CValue generalize(const double & d);

        void Or(int s) {mStatus = Status(mStatus | s);};
        void Or(const CValue & v); //  {mStatus = Status(mStatus | s);};

        /**
         * add the value to the set off possible values
         */
#ifdef WIN32 // To prevent a fatal compiler error in Visual Studio C++ 6.0
        void orValue(const double value) {Or(CValue(value)); /*  mDouble = value; Or(known);*/};
#else
        void orValue(const double & value) {Or(CValue(value)); /*  mDouble = value; Or(known);*/};
#endif

      private:
        Status mStatus;
        double mDouble;

        /**
          * insert operator
          */
        friend std::ostream & operator<<(std::ostream &os, const CValue & v);
      };

    /**
     * This class contains the result of the analysis of one function.
     */
    class Result
      {
      public:

        /**
         * This contains low level infomation about one function. The Result class contains
         * three instances of this structure: For the complete function and for the forward and
         * backwards part of a reversible function
         */
        struct FunctionInformation
          {
            std::vector<CValue> mUnchangedParameters;
            std::vector<std::pair<std::pair<int, std::string>, std::vector<CValue> > > mSubstrateZero;
            std::vector<std::pair<std::pair<int, std::string>, std::vector<CValue> > > mProductZero;

            void writeTable(std::ostream & os, bool rt) const;

            /**
             * This writes a (hopefully) user understandable interpretation of the results to os.
             * The return value indicates if a problem was reported.
             */
            bool writeAnalysis(std::ostream & os, bool rt, bool reversible) const;
          };

        Result();
        void clear() {*this = Result();};

        /**
         * writes a text report about the function to the stream. The return value
         * indicates if a problem was reported.
         */
        bool writeResult(std::ostream & os, bool rt, bool verbose) const;

        //void writeTable(std::ostream & os, bool rt) const;

        const CFunction * mpFunction;
        bool mIrreversibleKineticsWithProducts;

        FunctionInformation mOriginalFunction;

        bool mReversibleNonSplitable;
        FunctionInformation mFPart;
        FunctionInformation mBPart;
      };

    void checkKineticFunction(const CFunction * f, const CReaction * reaction = NULL);

    CFunctionAnalyzer(const CFunction * f, const CReaction * reaction = NULL)
    {checkKineticFunction(f, reaction);};

    const Result & getResult() const {return mResult;};

    static CValue evaluateNode(const CEvaluationNode * node, const std::vector<CValue> & callParameters);

    static void constructCallParameters(const CFunctionParameters & fp, std::vector<CValue> & callParameters, bool posi);

  protected:

    Result mResult;

    static void constructCallParametersActualValues(std::vector<CValue> & callParameters, /*const CModel* model,*/ const CReaction* reaction);

  public:
    //convenience function to help with writing the reports
    //static std::string write(int level, bool rt, const std::string & text);
    static std::string write(int level, bool rt, const std::string & text, const std::string & longText);
  };

#endif
