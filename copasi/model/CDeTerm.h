#ifndef CDETERM_H
#define CDETERM_H

#include <vector>
#include "CSpecLine.h"

using std::vector;
using std::pair;

/**
 * This class describes a term in the differential equation.
 */

class CDeTerm
  {
  public:
    /**
     * The various types of token
     */
    enum Type{NL, PLUS, MINUS, LPAREN, RPAREN, EXPONENT, MULT, DIV, IDENT, NUM};
    /**
     * The constructor
     */
    CDeTerm();
    /**
     * The destructor
     */
    ~CDeTerm();
    /**
     * Set the rate constant
     */
    void setRateConstant(string rate) {mRateConstant = rate; }

    /**
     * Retrieve the rate constant
     */
    string getRateConstant() { return mRateConstant; }

    /**
     * Set the multiplier
     */
    void setMultiplier(C_FLOAT64 multiplier) {mMultiplier = multiplier; }

    /**
     * Get the multiplier
     */
    C_FLOAT64 getMultiplier() { return mMultiplier; }

    /**
     * Set the sign
     */
    void setSign(const char *sign);
    /**
     * Retrieve the sign
     */
    C_INT32 getSign() { return mSign; }

    /**
     * Add an element to the vector of tokens describing the rate
     */
    void addElement(Type type, string token);
    /**
     * Remove an element from the stack
     */
    void deleteElement(C_INT32 index);
    /**
     * Extract the top level metabolites in this DeTerm
     */
    string getTopLevelMetabolite(unsigned C_INT32 pos, C_INT32 &multiplicity);
    /**
     * Return the size of the token stack
     */
    C_INT32 size() { return mTokenStack.size(); }

    /**
     * Access the stack at a given position
     */
    string operator[](unsigned C_INT32 index);
    /**
     * Return the full description string. This will have been modified by the end.
     */
    string getDescription();
    /**
     * Do things like strip out the multiplier and determine the rate constant
     */
    void compile(vector<CNameVal> &rates);
    /**
     * Get the Token Stack
     */
    const vector<pair<Type, string>* > & getTokenStack() const { return mTokenStack; }

  private:
    /**
     * The stack of tokens making up the term
     */
    vector<pair<Type, string>* > mTokenStack;
    /**
     * The top level metabolites in this term. Each metabolite has a name and a multiplicity.
     */
    vector<pair<string, C_INT32>*> mTopLevelMetabolites;
    /**
     * The sign
     */
    C_INT32 mSign;
    /**
     * The multiplier
     */
    C_FLOAT64 mMultiplier;
    /**
     * The rate constant
     */
    string mRateConstant;

    friend ostream & operator<<(ostream &os, const CDeTerm & d)
    {
      os << "RateConstant =   " << d.mRateConstant << endl
      << "Sign =           " << d.mSign << endl
      << "StoiCoeficient = " << d.mMultiplier << endl;
      os << "TokenStack :" << endl;

      unsigned int i;

      for (i = 0; i < d.mTokenStack.size(); i++)
        os << "  " << i << ": Type = '" << d.mTokenStack[i]->first
        << "', String = '" << d.mTokenStack[i]->second << "'" << endl;

      os << "Metabolites :" << endl;

      for (i = 0; i < d.mTopLevelMetabolites.size(); i++)
        os << "  " << i << ": Metabolite = '" << d.mTopLevelMetabolites[i]->first
        << "', Multiplicity = '" << d.mTopLevelMetabolites[i]->second << "'" << endl;

      return os;
    }
  };

#endif // CDETERM_H
