#include "CFunctionDB.h"

CFunctionDB::CFunctionDB() {}

CFunctionDB::~CFunctionDB() {}

void CFunctionDB::SetFilename(const string & filename) {mFilename = filename;}
    
string CFunctionDB::GetFilename() {return mFilename;}

CKinFunction & CFunctionDB::DBLoad(const string & functionName) 
{
    C_INT32 index = 0;    

    CReadConfig inbuf(mFilename);

    return (*mLoadedFunctions)[index];
}

void CFunctionDB::DBAdd(CKinFunction & function)
{
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

