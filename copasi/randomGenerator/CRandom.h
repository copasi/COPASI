/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/randomGenerator/CRandom.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/12 16:46:00 $
   End CVS Header */

#ifndef COPASI_CRandom
#define COPASI_CRandom

#include <string>

class CRandom
  {
    // Attributes
  public:
    /**
     * The valid types of a function
     */
    enum Type
    {
      r250 = 0,
      mt19937
    };

    /**
     * String literals for the GUI to display type names of random number
     * generators known to COPASI.
     */
    static const std::string TypeName[];

    /**
     * XML type names of random number generators known to COPASI.
     */
    static const char * XMLType[];

  protected:
    /**
     * A unsigned 32-bit integer random number.
     */
    unsigned C_INT32 mNumberU;

    /**
     * A singned 32-bit integer random number.
     */
    C_INT32 mNumberS;

    /**
     * A 64-bit floating point random number.
     */
    C_FLOAT64 mFloat;

    /**
     * The type of the generator
     */
    CRandom::Type mType;

    /**
     *
     */
    unsigned C_INT32 mModulus;

    /**
     *
     */
    C_FLOAT64 mModulusInv;

    /**
     *
     */
    C_FLOAT64 mModulusInv1;

    // Operations
  protected:
    /**
     * Default/Named constructor.
     * Seeds the random number generator with the given seed.
     */
    CRandom();

  public:
    /**
     * Convert a TypeName to the matching enum value.
     * Returns CRandom::mt19937 if no match is found.
     * @param (const std::string & typeName)
     * @return CRandom::Type type
     */
    static CRandom::Type TypeNameToEnum(const std::string & typeName);

    /**
     * Convert a XMLSubType to the matching enum value
     * Returns CRandom::mt19937 if no match is found.
     * @param (const char * xmlTypeName)
     * @return CRandom::SubType type
     */
    static CRandom::Type XMLNameToEnum(const char * xmlTypeName);

    /**
     * get a system dependend seed (hopefully random)
     */
    static unsigned C_INT32 getSystemSeed();

    /**
     * Create a Generator. 
     * Note: the returned object has to be released after use with delete
     * @param CRandom::Type type (default Mersenne Twister)
     * @param const C_INT32 & seed (default system generated seed)
     * @return CRandom * randomGenerator
     */
    static CRandom * createGenerator(CRandom::Type type = CRandom::mt19937,
                                     unsigned C_INT32 seed = 0);

    /**
     * The destructor.
     */
    virtual ~CRandom();

    /**
     * Retreive the type of the generator
     * @return const CRandom::Type & type
     */
    const CRandom::Type & getType() const;

    /**
     * Retreive the method dependend modulus
     * @return const unsigned C_INT32 & modulus
     */
    const unsigned C_INT32 & getModulus() const;

    /**
     * Initialize or reinitialize the random number generator with 
     * the given seed.
     * @param unsigned C_INT32 seed (default system seed)
     */
    virtual void initialize(unsigned C_INT32 seed = CRandom::getSystemSeed());

    /**
     * Get a random number in 0 <= n <= Modulus
     * @return unsigned C_INT32 random
     */
    virtual unsigned C_INT32 getRandomU();

    /**
     * Get a random number in 0 <= n <= (Modulus & 0x7ffffff)
     * @return C_INT32 random
     */
    virtual C_INT32 getRandomS();

    /**
     * Get a random number in 0 <= n <= max
     * Note: max must be smaller than Modulus (no check for performance)
     * @param const unsigned C_INT32 & max
     * @return unsigned C_INT32 random
     */
    virtual unsigned C_INT32 getRandomU(const unsigned C_INT32 & max);

    /**
     * Get a random number in 0 <= n <= max
     * Note: max must be smaller than Modulus (no check for performance)
     * @param const C_INT32 & max
     * @return C_INT32 random
     */
    virtual C_INT32 getRandomS(const C_INT32 & max);

    /**
     * Produces a uniformly distributed random number in 0 <= x <= 1.
     * @return C_FLOAT64 random
     */
    virtual C_FLOAT64 getRandomCC();

    /**
     * Produces a uniformly distributed random number in 0 <= x < 1.
     * Note: 0 < x <= 1 may be achieved by 1.0 - getRandomCO().
     * @return C_FLOAT64 random
     */
    virtual C_FLOAT64 getRandomCO();

    /**
     * Produces a uniformly distributed random number in 0 < x < 1.
     * @return C_FLOAT64 random
     */
    virtual C_FLOAT64 getRandomOO();

    /**
     * Produces a Normally distributed random number with mean=0 and SD=1
     * @return C_FLOAT64 random
     */
    virtual C_FLOAT64 getRandomNormal01();

    /**
     * Produces a Normally distributed random number with Mean=mean and SD=sd
     * @param const C_FLOAT64 & mean
     * @param const C_FLOAT64 & sd
     * @return C_FLOAT64 random
     */
    virtual C_FLOAT64 getRandomNormal(const C_FLOAT64 & mean,
                                      const C_FLOAT64 & sd);

    /**
     * Produces a Strictly Positive Normally distributed random number
     * with Mean=mean and SD=sd
     * @param const C_FLOAT64 & mean
     * @param const C_FLOAT64 & sd
     * @return C_FLOAT64 random
     */
    virtual C_FLOAT64 getRandomNormalPositive(const C_FLOAT64 & mean,
        const C_FLOAT64 & sd);

    /**
     * Produces a Normally distributed random number with Mean=mean and SD=sd
     * in Logarithmic scale
     * @return C_FLOAT64 random
     */
    virtual C_FLOAT64 getRandomNormalLog(const C_FLOAT64 & mean,
                                         const C_FLOAT64 & sd);

  protected:
    /**
     * Set the Modulus
     * @param 
     */
    void setModulus(const unsigned C_INT32 & modulus);
  };

#include "Cr250.h"
#include "Cmt19937.h"

#endif // COPASI_CRandom
