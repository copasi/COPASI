/**
 * CODESolver
 * 
 * (C) Pedro Mendes 2001, based on code in Gepasi (C) Pedro Mendes 1990-2000
 */

#include "copasi.h"
#include "CODESolver.h"

CODESolver::CODESolver()
{
    // initialize everything
    mName   = "ODE solvers";
    mMethod = 1;
}


CODESolver::~CODESolver() 
{
    cout << "~CODESolver " << mName << endl;
}


C_INT32 CODESolver::Load(CReadConfig & configbuffer)
{
    C_INT32 Fail = 0;

    /* check with Stefan how one can read new and old formats */

    /* get version from ReadConfig */

    /* read method number */

    /* then load method-dependent parameters */
    if (Fail = configbuffer.GetVariable("Compartment", "string",
                                        (void *) &mName,
                                        CReadConfig::SEARCH))
        return Fail;

    if (Fail = configbuffer.GetVariable("Volume", "C_FLOAT64",
                                        (void *) &mVolume))
        return Fail;
    
    if (configbuffer.GetVersion() < "4") return Fail;
    
    C_INT32 MetabolitesNo;
    if (Fail = configbuffer.GetVariable("MetabolitesNo", "C_INT32",
                                        (void *) &MetabolitesNo))
        return Fail;
    
    Fail = mMetabolites.Load(configbuffer, MetabolitesNo);
    
    return Fail;
}

C_INT32 CCompartment::Save(CWriteConfig & configbuffer)
{
    C_INT32 Fail = 0;

    if (Fail = configbuffer.SetVariable("Compartment", "string",
                                        (void *) &mName))
        return Fail;

    if (Fail = configbuffer.SetVariable("Volume", "C_FLOAT64",
                                        (void *) &mVolume))
        return Fail;
    
    C_INT32 size = mMetabolites.Size();
    if (Fail = configbuffer.SetVariable("MetabolitesNo", "C_INT32",
                                        (void *) &size))
        return Fail;

    Fail = mMetabolites.Save(configbuffer);
    return Fail;
}

string CCompartment::GetName() {return mName;}

C_FLOAT64 CCompartment::GetVolume() {return mVolume;}

CCopasiVector < CMetab > & CCompartment::GetMetabolites() {return mMetabolites;}

void CCompartment::SetName(const string & name) 
{
    mName = name;
    if (!IsValidName()) FatalError();
}

void CCompartment::SetVolume(C_FLOAT64 volume) {mVolume = volume;}

void CCompartment::AddMetabolite(CMetab &metabolite)
{
    metabolite.SetCompartment(this);
    mMetabolites.Add(metabolite);
}

C_INT16 CCompartment::IsValidName()
{
    return (mName.find_first_of("; ") == string::npos);
}
