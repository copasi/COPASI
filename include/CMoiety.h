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
     */
    string mName;
    string mDescription;

    typedef struct ELEMENT {C_FLOAT64 Value; CMetab * Metab;};
    vector < ELEMENT > mEquation;
    
// Operations
public:
    CMoiety();
    CMoiety(const string & name);
    ~CMoiety();
    void Add(C_FLOAT64 value, CMetab & metabolite);
    void Add(C_FLOAT64 value, CMetab * metabolite);
    void Delete();
    void Delete(const string & name);
    void Delete(C_INT32 index);
    void Change(C_INT32 index,
		C_FLOAT64 value);
    void Change(const string & name,
		C_FLOAT64 value);
    string GetName();
    string GetDescription();
    C_FLOAT64 Value();
};

#endif // COPASI_CMoiety
