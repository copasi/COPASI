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

    typedef struct ELEMENT {double Value; CMetab * Metab;};
    vector < ELEMENT > mEquation;
    
// Operations
public:
    CMoiety();
    CMoiety(const string & name);
    ~CMoiety();
    long Add(double value, CMetab & metabolite);
    long Add(double value, CMetab * metabolite);
    long Delete();
    long Delete(const string & name);
    long Delete(long index);
    long Change(long index,
		double value);
    long Change(const string & name,
		double value);
    string GetName();
    string GetDescription();
    double Value();
};

#endif // COPASI_CMoiety
