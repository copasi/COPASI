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

C_INT32 CFunctionDB::Load(CReadConfig &configbuffer)
{
    CKinFunction * pFunction = NULL;
    C_INT32 Size = 0;
    C_INT32 Fail = 0;

    if (Fail = configbuffer.GetVariable("TotalUDKinetics", "C_INT32", &Size,
                                        CReadConfig::LOOP))
        return Fail;
    
    for (C_INT32 i = 0; i < Size; i++)
    {
        // We should really read the function type first before we allocate,
        // but since we currently have only one type this will do.
        pFunction = new CKinFunction;
        if (Fail = pFunction->Load(configbuffer)) return Fail;
        mLoadedFunctions.Add(pFunction);
    }
    return Fail;
}

C_INT32 CFunctionDB::Save(CWriteConfig &configbuffer)
{
    C_INT32 Size = mLoadedFunctions.Size();
    C_INT32 Fail = 0;
    
    if (Fail = configbuffer.SetVariable("TotalUDKinetics", "C_INT32", &Size))
        return Fail;

    for (C_INT32 i = 0; i < Size; i++)
        if (Fail = mLoadedFunctions[i]->Save(configbuffer)) return Fail;

    return Fail;
}

void CFunctionDB::SetFilename(const string & filename) {mFilename = filename;}
    
string CFunctionDB::GetFilename() const {return mFilename;}

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
        Fail = pFunction->Load(inbuf);
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
