#ifndef COPASI_CRandom
#define COPASI_CRandom

#include <string>

class CRandom
  {
    friend class Cr250;

    // Attributes
  public:
    /**
     *  The valid types of a function
     */
    enum Type
    {
      R250 = 0
    };

  public:
    static const string TypeName[];

  protected:
    CRandom::Type mType;
    unsigned C_INT32 mNumber;
    C_FLOAT64 mFloat;
    unsigned C_INT32 mModulus;

    // Operations
  private:
    /**
     * Default/Named constructor.
     * Seeds the random number generator with the given seed.
     * @param C_INT32 seed (default implementation dependent seed)
     */
    CRandom(C_INT32 seed = 0);

    /**
     * get a system dependend seed (hopefully random)
     */
    static unsigned C_INT32 getSystemSeed();

  public:
    /**
     * Create a Generator. 
     * Note: the returned object has to be released after use with delete
     * @param CRandom::Type type
     * @param const C_INT32 & seed (default system generated seed)
     * @return CRandom * randomGenerator
     */
    static CRandom * createGenerator(CRandom::Type type,
                                     unsigned C_INT32 seed = 0);

    /**
     * The destructor.
     */
    virtual ~CRandom();

    /**
     * Initialize or reinitialize the random number generator with the given seed.
     * @param C_INT32 seed (default system seed)
     */
    virtual void initialize(C_INT32 seed = 0);

    /**
     * Get a random number in 0 <= n < getModulus()
     * @return const unsigned C_INT32 & n
     */
    virtual const unsigned C_INT32 & getRandom();

    /**
     * Get a random number in 0 <= n < modulus
     * @param const unsigned C_INT32 & modulus
     * @return const unsigned C_INT32 & n
     */
    virtual const unsigned C_INT32 & getRandom(const unsigned C_INT32 & modulus);

    /**
     * Retreive the method dependend modulus
     * @return const unsigned C_INT32 & modulus
     */
    virtual const unsigned C_INT32 & getModulus() const;

    /**
     * Produces a uniformly distributed random number in 0 <= x < 1.
     * @return const unsigned C_INT32 & x
     */
    virtual const C_FLOAT64 & getRandomF();
  };

#include "Cr250.h"

#endif // COPASI_CRandom
