#include "CFunctionDB.h"

CFunctionDB::CFunctionDB() {mLoadedFunctions = NULL;}

void CFunctionDB::Init() 
{
    if (!mLoadedFunctions)
        mLoadedFunctions = new CCopasiVector < CKinFunction >;

    for (long i = 0; i < mLoadedFunctions->Size(); i++)
        (*mLoadedFunctions)[i].Init();
}

CFunctionDB::~CFunctionDB() {}

void CFunctionDB::Delete()
{
    if (mLoadedFunctions)
    {
        for (long i = 0; i < mLoadedFunctions->Size(); i++)
            (*mLoadedFunctions)[i].Delete();
        delete mLoadedFunctions;
    }
    mLoadedFunctions = NULL;
}

void CFunctionDB::SetFilename(const string & filename) {mFilename = filename;}
    
string CFunctionDB::GetFilename() {return mFilename;}

CKinFunction & CFunctionDB::DBLoad(const string & functionName) 
{
    C_INT32 Index = mLoadedFunctions->Size();
    C_INT32 Fail = 0;
    
    mLoadedFunctions->Add(CKinFunction());
    
    CReadConfig inbuf(mFilename);
    
    while (functionName != (*mLoadedFunctions)[Index].GetName())
    {
        (*mLoadedFunctions)[Index].Delete();
        Fail = (*mLoadedFunctions)[Index].Load(inbuf);
    }

    return (*mLoadedFunctions)[Index];
}

void CFunctionDB::Add(CKinFunction & function)
{
    mLoadedFunctions->Add(function);
}

void CFunctionDB::DBDelete(const string & functionName)
{
}

CKinFunction & CFunctionDB::FindFunction(const string & functionName)
{
    C_INT32 i;
    
    for (i = 0; i < mLoadedFunctions->Size(); i++)
        if (functionName == (*mLoadedFunctions)[i].GetName())
            return (*mLoadedFunctions)[i];

    return DBLoad(functionName);
}

