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


long CODESolver::Load(CReadConfig & configbuffer)
{
    long Fail = 0;

    /* check with Stefan how one can read new and old formats */

    /* get version from ReadConfig */

    /* read method number */

    /* then load method-dependent parameters */
    if (Fail = configbuffer.GetVariable("Compartment", "string",
                                        (void *) &mName,
                                        CReadConfig::SEARCH))
        return Fail;

    if (Fail = configbuffer.GetVariable("Volume", "double",
                                        (void *) &mVolume))
        return Fail;
    
    if (configbuffer.GetVersion() < "4") return Fail;
    
    long MetabolitesNo;
    if (Fail = configbuffer.GetVariable("MetabolitesNo", "long",
                                        (void *) &MetabolitesNo))
        return Fail;
    
    Fail = mMetabolites.Load(configbuffer, MetabolitesNo);
    
    return Fail;
}

long CCompartment::Save(CWriteConfig & configbuffer)
{
    long Fail = 0;

    if (Fail = configbuffer.SetVariable("Compartment", "string",
                                        (void *) &mName))
        return Fail;

    if (Fail = configbuffer.SetVariable("Volume", "double",
                                        (void *) &mVolume))
        return Fail;
    
    long size = mMetabolites.Size();
    if (Fail = configbuffer.SetVariable("MetabolitesNo", "long",
                                        (void *) &size))
        return Fail;

    Fail = mMetabolites.Save(configbuffer);
    return Fail;
}

string CCompartment::GetName() {return mName;}

double CCompartment::GetVolume() {return mVolume;}

CCopasiVector < CMetab > & CCompartment::GetMetabolites() {return mMetabolites;}

void CCompartment::SetName(const string & name) 
{
    mName = name;
    if (!IsValidName()) FatalError();
}

void CCompartment::SetVolume(double volume) {mVolume = volume;}

void CCompartment::AddMetabolite(CMetab &metabolite)
{
    metabolite.SetCompartment(this);
    mMetabolites.Add(metabolite);
}

short CCompartment::IsValidName()
{
    return (mName.find_first_of("; ") == string::npos);
}
