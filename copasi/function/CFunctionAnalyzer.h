// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionAnalyzer.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/21 16:15:07 $
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

class CFunctionAnalyzer
  {
  public:
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

      protected:
        CValue invert() const;

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
        void orValue(const double & value) {Or(CValue(value)); /*  mDouble = value; Or(known);*/};

      private:
        Status mStatus;
        double mDouble;

        /**
          * insert operator
          */
        friend std::ostream & operator<<(std::ostream &os, const CValue & v);
      };

    class Result
      {
      public:
        std::vector<std::vector<CValue> > mSubstrateZero;
      };

    static Result checkKineticFunction(const CFunction * f, const CReaction * reaction = NULL, const CModel * model = NULL);

  protected:

    static CValue evaluateNode(const CEvaluationNode * node, const std::vector<CValue> & callParameters);

    static void constructCallParameters(const CFunctionParameters & fp, std::vector<CValue> & callParameters, bool posi);

    static void constructCallParametersActualValues(std::vector<CValue> & callParameters, /*const CModel* model,*/ const CReaction* reaction);
  };

class CModelAnalyzer
  {
  public:

    static void checkModel(const CModel* model);

    static void checkReaction(const CReaction* reaction, const CModel* model);
  };

#endif
