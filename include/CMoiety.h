/**
 *  CMoiety
 *  
 *  New class created for Copasi by Stefan Hoops
 *  (C) Stefan Hoops 2001
 */

#ifndef COPASI_CMoiety
#define COPASI_CMoiety

#include <string>
#include <vector>

#include "CMetab.h"

class CMoiety
{
// Attributes
private:
    /**
     *
     */
    string mName;

    /**
     *  Number of Particles of Moietiy.
     */
    C_FLOAT64 mNumber;

    /**
     *  Initial Number of Particles of Moietiy.
     */
    C_FLOAT64 mINumber;


    typedef struct ELEMENT {C_FLOAT64 mValue; CMetab * mMetab;};
    vector < ELEMENT > mEquation;
    
// Operations
public:
    CMoiety();
    CMoiety(const string & name);
    ~CMoiety();
    C_INT32 Load(CReadConfig & configBuffer);
    C_INT32 Save(CWriteConfig & configBuffer);
    
    void Add(C_FLOAT64 value, CMetab & metabolite);
    void Add(C_FLOAT64 value, CMetab * metabolite);
    void Delete();
    void Delete(const string & name);
    void Delete(C_INT32 index);
    void Change(C_INT32 index,
		C_FLOAT64 value);
    void Change(const string & name,
		C_FLOAT64 value);
    void SetName(const string name);
    void SetInitialValue();
    string GetName() const;
    string GetDescription() const;
    C_FLOAT64 DependentNumber();
};

#endif // COPASI_CMoiety
