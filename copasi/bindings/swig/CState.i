%{

#include "model/CState.h"

%}


class CState
{
  public:
    CState();
    CState(const CState & src);
    ~CState();

    const C_FLOAT64 & getTime() const;
    void setTime(const C_FLOAT64 & time);

    C_FLOAT64 * beginIndependent();
    C_FLOAT64 * endIndependent();
    C_FLOAT64 * beginDependent();
    C_FLOAT64 * endDependent();
    C_FLOAT64 * beginFixed();
    C_FLOAT64 * endFixed();

    const C_FLOAT64 * beginIndependent() const;
    const C_FLOAT64 * endIndependent() const;
    const C_FLOAT64 * beginDependent() const;
    const C_FLOAT64 * endDependent() const;
    const C_FLOAT64 * beginFixed() const;
    const C_FLOAT64 * endFixed() const;

    unsigned C_INT32 getNumIndependent() const;
    unsigned C_INT32 getNumDependent() const;
    unsigned C_INT32 getNumVariable() const;
    unsigned C_INT32 getNumFixed() const;

    void setUpdateDependentRequired(const bool & required);
    const bool & isUpdateDependentRequired() const;

#ifdef COPASI_DEBUG
//    void check(const std::string & m = "") const;
#endif


};
