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
    void Add(double value, CMetab & metabolite);
    void Add(double value, CMetab * metabolite);
    void Delete();
    void Delete(const string & name);
    void Delete(long index);
    void Change(long index,
		double value);
    void Change(const string & name,
		double value);
    string GetName();
    string GetDescription();
    double Value();
};

#endif // COPASI_CMoiety
