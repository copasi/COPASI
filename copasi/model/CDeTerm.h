#ifndef CDETERM_H
#define CDETERM_H

#include <vector>
#include "CSpecLine.h"

/**
 * This class describes a term in the differential equation.
 */

/** @dia:pos 29.688,68.0665 */
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
    void setRateConstant(std::string rate) {mRateConstant = rate;}

    /**
     * Retrieve the rate constant
     */
    std::string getRateConstant() const {return mRateConstant;}

    /**
     * Set the multiplier
     */
    void setMultiplier(C_FLOAT64 multiplier) {mMultiplier = multiplier;}

    /**
     * Get the multiplier
     */
    C_FLOAT64 getMultiplier() const {return mMultiplier;}

    /**
     * Set the sign
     */
    void setSign(const char *sign);
    /**
     * Retrieve the sign
     */
    C_INT32 getSign() const {return mSign;}

    /**
     * Add an element to the vector of tokens describing the rate
     */
    void addElement(Type type, std::string token);
    /**
     * Remove an element from the stack
     */
    void deleteElement(std::vector< std::pair <Type, std::string>*>::iterator it);
    /**
     * Extract the top level metabolites in this DeTerm
     */
    std::string getTopLevelMetabolite(unsigned C_INT32 pos, C_INT32 &multiplicity) const;
    /**
     * Return the size of the token stack
     */
    C_INT32 size() const {return mTokenStack.size();}

    /**
     * Access the stack at a given position
     */
    std::string operator[](unsigned C_INT32 index);
    /**
     * Return the full description string. This will have been modified by the end.
     */
    std::string getDescription() const;
    /**
     * Do things like strip out the multiplier and determine the rate constant
     */
    void compile(std::vector< CNameVal> &rates);
    /**
     * Get the Token Stack
     */
    const std::vector< std::pair< Type, std::string>* > & getTokenStack() const {return mTokenStack;}

  private:
    /**
     * The stack of tokens making up the term
     */
    std::vector< std::pair< Type, std::string>* > mTokenStack;
    /**
     * The top level metabolites in this term. Each metabolite has a name and a multiplicity.
     */
    std::vector< std::pair< std::string, C_INT32>*> mTopLevelMetabolites;
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
    std::string mRateConstant;

    friend std::ostream & operator<<(std::ostream &os, const CDeTerm & d)
    {
      os << "RateConstant =   " << d.mRateConstant << std::endl
      << "Sign =           " << d.mSign << std::endl
      << "StoiCoeficient = " << d.mMultiplier << std::endl;
      os << "TokenStack :" << std::endl;

      unsigned int i;

      for (i = 0; i < d.mTokenStack.size(); i++)
        os << "  " << i << ": Type = '" << d.mTokenStack[i]->first
        << "', String = '" << d.mTokenStack[i]->second << "'" << std::endl;

      os << "Metabolites :" << std::endl;

      for (i = 0; i < d.mTopLevelMetabolites.size(); i++)
        os << "  " << i << ": Metabolite = '" << d.mTopLevelMetabolites[i]->first
        << "', Multiplicity = '" << d.mTopLevelMetabolites[i]->second << "'" << std::endl;

      return os;
    }
  };

#endif // CDETERM_H
