/**
 * Cr250 class implementing the R250 random number generator, by W. L. Maier
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_Cr250
#define COPASI_Cr250

#include "CRandom.h"

/*** Class definition for R250 random number generator ***/

class Cr250 : public CRandom
  {
    // Attributes
  private:
    static unsigned C_INT32 mInitialBuffer[250];

    C_INT32 mIndex;

    unsigned C_INT32 mSeed;

    unsigned C_INT16 mBuffer[250];

    // Operations
  public:
    /**
     * Default/Named constructor.
     * Seeds the random number generator with the given seed.
     * @param C_INT32 seed (default system seed)
     */
    Cr250(C_INT32 seed = 0);

    /**
     * The destructor.
     */
    ~Cr250();

    /**
     * Initialize or reinitialize the random number generator with the given seed.
     * @param C_INT32 seed (default system seed)
     */
    void initialize(C_INT32 seed = 0);

    /**
     * Get a random number in 0 <= n < getModulus()
     * @return const unsigned C_INT32 & n
     */
    const unsigned C_INT32 & getRandom();

    /**
     * Get a random number in 0 <= n < modulus
     * @param const unsigned C_INT32 & modulus
     * @return const unsigned C_INT32 & n
     */
    const unsigned C_INT32 & getRandom(const unsigned C_INT32 & modulus);

    /**
     * Produces a uniformly distributed random number in 0 <= x < 1.
     * @return const unsigned C_INT32 & x
     */
    const C_FLOAT64 & getRandomF();

    /**
     * Number returned by r250() is in the interval 0 <= k < 65536.
     * @return const unsigned C_INT16 & random
     */
    const unsigned C_INT16 & r250(void);

    /**
     * Number returned by r250() is in the interval 0 <= k < max.
     * @param unsigned C_INT16 max
     * @return const unsigned C_INT16 & random
     */
    const unsigned C_INT16 & r250n(const unsigned C_INT16 & max);

    /**
     * Number returned by dr250() is in range [0,1)
     * @return C_FLOAT64 random
     */
    const C_FLOAT64 & dr250(void);

  private:
    /**
     * This is used for the initialization of r250
     */
    unsigned C_INT16 myrand();

    /**
     * Default buffer assignement
     */
    void initBuffer();
  };
#endif // COPASI_Cr250
