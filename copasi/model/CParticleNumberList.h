#ifndef COPASI_CParticleNumberList
#define COPASI_CParticleNumberList

#include "utilities/CVector.h"

class CParticleNumberList
  {
  protected:
    // Associations

    // Attributes
    /**
     * The size of the particle number list
     */
    unsigned C_INT32 mSize;

    /**
     * The particle numbers stored as C_FLOAT64
     */
    CVector< C_FLOAT64 > mDbl;

    /**
     * The particle numbers stored as C_INT32
     */
    CVector< C_INT32 > mInt;

    // Operations
  public:
    /**
     * Default constructor
     * @param const unsigned C_INT32 & size (default 0)
     */
    CParticleNumberList(const unsigned C_INT32 & size = 0);

    /**
     * Copy constructor
     * @param const CParticleNumberList & src
     */
    CParticleNumberList(const CParticleNumberList & src);

    /**
     * Destructor
     */
    ~CParticleNumberList();

    /**
     * Assignement operator
     * @param const CParticleNumberList & rhs
     * @retrun CParticleNumberList & lhs
     */
    CParticleNumberList & operator =(const CParticleNumberList & rhs);

    /**
     * Resize the particle number list
     * @param const unsigned C_INT32 & size
     */
    void resize(const unsigned C_INT32 & size);

    /**
     * Retreive the size of the particle number list
     * @return const unsigned C_INT32 & size
     */
    const unsigned C_INT32 & size() const;

    /**
     * Set the indexed particle number to value
     * @param const unsigned C_INT32 & index
     * @param const C_FLOAT64 & value
     */
    void set(const unsigned C_INT32 & index, const C_FLOAT64 & value);

    /**
     * Retreive the indexed particle number as C_FLOAT64
     * @param const unsigned C_INT32 & index
     * @return const C_FLOAT64 & value
     */
    const C_FLOAT64 & getDbl(const unsigned C_INT32 & index) const;

    /**
     * Set the indexed particle number to value
     * @param const unsigned C_INT32 & index
     * @param const C_FLOAT64 & value
     */
    void set(const unsigned C_INT32 & index, const C_INT32 & value);

    /**
     * Retreive the indexed particle number as C_INT32
     * @param const unsigned C_INT32 & index
     * @return const C_INT32 & value
     */
    const C_INT32 & getInt(const unsigned C_INT32 & index) const;

    /**
     * Set all particle numbers at once
     * @param const CVector< C_FLOAT64 > & vector
     */
    void setVector(const CVector< C_FLOAT64 > & vector);

    /**
     * Retreive all particle numbers as C_FLOAT64
     * @return const CVector< C_FLOAT64 > & vector
     */
    const CVector< C_FLOAT64 > & getVectorDbl() const;

    /**
     * Set all particle numbers at once
     * @param const CVector< C_INT32 > & vector
     */
    void setVector(const CVector< C_INT32 > & vector);

    /**
     * Retreive all particle numbers as C_INT32
     * @return const CVector< C_INT32 > & vector
     */
    const CVector< C_INT32 > & getVectorInt() const;

    friend std::ostream & operator << (std::ostream & os,
                                       const CParticleNumberList & A)
    {
      os << "Particle List: " << std::endl;
      os << "  Dbl: " << A.mDbl << std::endl;
      os << "  Int: " << A.mInt << std::endl;

      return os;
    }
  };

#endif // COPASI_CParticleNumberList
