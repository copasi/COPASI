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


    unsigned C_INT32 getNumIndependent() const;
    unsigned C_INT32 getNumDependent() const;
    unsigned C_INT32 getNumVariable() const;
    unsigned C_INT32 getNumFixed() const;

    void setUpdateDependentRequired(const bool & required);
    const bool & isUpdateDependentRequired() const;



};


