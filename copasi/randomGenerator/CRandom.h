#ifndef COPASI_CRandom
#define COPASI_CRandom

#include <string>
using std::string;

class CRandom
  {
    //    friend class Cr250;
    //    friend class Cmt19937;

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
     * A userfriendly string representation for the above enum
     */
    static const string TypeName[];

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
     * @param unsigned C_INT32 seed
     */
    CRandom();

  public:
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
     * @return const unsigned C_INT32 & random
     */
    virtual const unsigned C_INT32 & getRandomU();

    /**
     * Get a random number in 0 <= n <= (Modulus & 0x7ffffff)
     * @return const C_INT32 & random
     */
    virtual const C_INT32 & getRandomS();

    /**
     * Get a random number in 0 <= n <= max
     * Note: max must be smaller than Modulus (no check for performance)
     * @param const unsigned C_INT32 & max
     * @return const unsigned C_INT32 & random
     */
    virtual const unsigned C_INT32 & getRandomU(const unsigned C_INT32 & max);

    /**
     * Get a random number in 0 <= n <= max
     * Note: max must be smaller than Modulus (no check for performance)
     * @param const C_INT32 & max
     * @return const C_INT32 & random
     */
    virtual const C_INT32 & getRandomS(const C_INT32 & max);

    /**
     * Produces a uniformly distributed random number in 0 <= x <= 1.
     * @return const C_FLOAT64 & random
     */
    virtual const C_FLOAT64 & getRandomCC();

    /**
     * Produces a uniformly distributed random number in 0 <= x < 1.
     * Note: 0 < x <= 1 may be achieved by 1.0 - getRandomCO().
     * @return const C_FLOAT64 & random
     */
    virtual const C_FLOAT64 & getRandomCO();

    /**
     * Produces a uniformly distributed random number in 0 < x < 1.
     * @return const C_FLOAT64 & random
     */
    virtual const C_FLOAT64 & getRandomOO();

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
