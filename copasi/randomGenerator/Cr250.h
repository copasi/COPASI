/**
 * Cr250 class implementing the R250 random number generator, by W. L. Maier
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_Cr250
#define COPASI_Cr250

class Cr250 : private CRandom
  {
    friend CRandom * CRandom::createGenerator(CRandom::Type type,
        unsigned C_INT32 seed);

    // Attributes
  private:
    C_INT32 mIndex;

    unsigned C_INT32 mSeed;

    unsigned C_INT16 mBuffer[250];

    // Operations
  private:
    /**
     * Default/Named constructor.
     * Seeds the random number generator with the given seed.
     * @param C_INT32 seed 
     */
    Cr250(unsigned C_INT32 seed);

  public:
    /**
     * The destructor.
     */
    ~Cr250();

    /**
     * Initialize or reinitialize the random number generator with 
     * the given seed.
     * Note: seed = 12345 gives the default initilization as in W. L. Maier code
     * @param unsigned C_INT32 seed (default system seed)
     */
    void initialize(unsigned C_INT32 seed = CRandom::getSystemSeed());

    /**
     * Get a random number in 0 <= n <= Modulus
     * @return unsigned C_INT32 random
     */
    unsigned C_INT32 getRandomU();

    /**
     * Get a random number in 0 <= n <= (Modulus & 0x7ffffff)
     * @return C_INT32 random
     */
    C_INT32 getRandomS();

    /**
     * Produces a uniformly distributed random number in 0 <= x <= 1.
     * @return C_FLOAT64 random
     */
    C_FLOAT64 getRandomCC();

    /**
     * Produces a uniformly distributed random number in 0 <= x < 1.
     * Note: 0 < x <= 1 may be achieved by 1.0 - getRandomCO().
     * @return const C_FLOAT64 & random
     */
    C_FLOAT64 getRandomCO();

    /**
     * Produces a uniformly distributed random number in 0 < x < 1.
     * @return const C_FLOAT64 & random
     */
    C_FLOAT64 getRandomOO();

  private:
    /**
     * Number returned by r250() is in the interval 0 <= k <= 65535.
     * @return unsigned C_INT32 random
     */
    unsigned C_INT32 r250(void);

    /**
     * Number returned by r250() is in the interval 0 <= k < max.
     * @param unsigned C_INT16 max
     * @return unsigned C_INT32 random
     */
    unsigned C_INT32 r250n(const unsigned C_INT16 & max);

    /**
     * Number returned by dr250() is in range [0,1)
     * @return C_FLOAT64 random
     */
    C_FLOAT64 dr250(void);

    /**
     * Linear congruent pseudorandom number generator for initialization.
     * Return a pseudorandom number in the interval 0 <= n <= 32767.
     */
    unsigned C_INT16 myrand();
  };
#endif // COPASI_Cr250
