// CCompartment
// 
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#ifndef COPASI_CComparment
#define COPASI_CComparment

class CCompartment
{
public:
    CCompartment();
    CCompartment(string name, double volume);
    ~CCompartment();
    CCompartment &operator=(CCompartment &);
    // string GetName(void);
    // void SetName(string *name);
    // double GetVolume(void);
    // void SetVolume(double volume);
    int Save(ostream *pfout);
    int Load(CReadConfig *pconfigbuffer);
    int Fail();

private:
    string mName;               // compartment name
    double mVolume;             // the volume of the compartment
    int    mFail;               // failure status
};
#endif // COPASI_CComparment
