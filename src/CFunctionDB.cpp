#include "CFunctionDB.h"
#include "CMassAction.h"

CFunctionDB::CFunctionDB() {}

void CFunctionDB::Init() 
{
    CMassAction *MassActionReversible   = new CMassAction(TRUE);
    mBuiltinFunctions.push_back((CBaseFunction *)MassActionReversible);
    
    CMassAction *MassActionIrreversible = new CMassAction(FALSE);
    mBuiltinFunctions.push_back((CBaseFunction *)MassActionIrreversible);
}

CFunctionDB::~CFunctionDB() {}

void CFunctionDB::Delete()
{
    C_INT32 i;
    
    mLoadedFunctions.Delete();
    
    for (i = 0; i < mBuiltinFunctions.size(); i++)
        delete mBuiltinFunctions[i];
    mBuiltinFunctions.clear();
}

void CFunctionDB::SetFilename(const string & filename) {mFilename = filename;}
    
string CFunctionDB::GetFilename() {return mFilename;}

CBaseFunction & CFunctionDB::DBLoad(const string & functionName) 
{
    C_INT32 Index = mLoadedFunctions.Size();
    C_INT32 Fail = 0;
    
    CKinFunction *pFunction = new CKinFunction;
    mLoadedFunctions.Add(pFunction);
    
    CReadConfig inbuf(mFilename);
    
    while (functionName != pFunction->GetName())
    {
        pFunction->Delete();
        Fail = pFunction->Load(inbuf, CReadConfig::SEARCH);
    }

    return *mLoadedFunctions[Index];
}

void CFunctionDB::Add(CKinFunction & function)
{
    CKinFunction *Function = new CKinFunction;
    Function->Init();
    Function->Copy(function);
        
    mLoadedFunctions.Add(Function);
}

void CFunctionDB::DBDelete(const string & functionName)
{
}

CBaseFunction & CFunctionDB::FindFunction(const string & functionName)
{
    C_INT32 i;
    
    for (i = 0; i < mLoadedFunctions.Size(); i++)
        if (functionName == mLoadedFunctions[i]->GetName())
            return *mLoadedFunctions[i];

    for (i = 0; i < mBuiltinFunctions.size(); i++)
        if (functionName == mBuiltinFunctions[i]->GetName())
            return *mBuiltinFunctions[i];
    
    return DBLoad(functionName);
}

CCopasiVectorP < CBaseFunction * > & CFunctionDB::LoadedFunctions()
{return mLoadedFunctions;}
