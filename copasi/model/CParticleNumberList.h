#ifndef COPASI_CParticleNumberList
#define COPASI_CParticleNumberList

#include "utilities/CVector.h"

class CParticleNumberList
  {
  protected:
    // Associations

    // Attributes
    unsigned C_INT32 mSize;
    CVector< C_FLOAT64 > mDbl;
    CVector< C_INT32 > mInt;

    // Operations
  public:
    CParticleNumberList(unsigned C_INT32 size = 0);
    CParticleNumberList(const CParticleNumberList & src);
    ~CParticleNumberList();
    void resize(const unsigned C_INT32 & size);
    void set(const unsigned C_INT32 & index, const C_FLOAT64 & value);
    const C_FLOAT64 & getDbl(const unsigned C_INT32 & index) const;
    void set(const unsigned C_INT32 & index, const C_INT32 & value);
    const C_INT32 & getInt(const unsigned C_INT32 & index) const;
    void setArray(const CVector< C_FLOAT64 > & values);
    const CVector< C_FLOAT64 > & getDblArray() const;
    void setArray(const CVector< C_INT32 > & values);
    const CVector< C_INT32 > & getIntArray() const;
    const unsigned C_INT32 & size() const;
  };

#endif // COPASI_CParticleNumberList
