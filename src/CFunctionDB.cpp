#include "CFunctionDB.h"

CFunctionDB::CFunctionDB() {}

CFunctionDB::~CFunctionDB() {}

void CFunctionDB::SetFilename(const string & filename) {mFilename = filename;}
    
string CFunctionDB::GetFilename() {return mFilename;}

CKinFunction & CFunctionDB::DBLoad(const string & functionName) 
{
    CReadConfig inbuf(mFilename);
}

long CFunctionDB::DBAdd(CKinFunction & function)
{
}

long CFunctionDB::DBDelete(const string & functionName)
{
}

CKinFunction & CFunctionDB::FindFunction(const string & functionName)
{
    long i;
    
    for (i = 0; i < mLoadedFunctions.Size(); i++)
        if (functionName == mLoadedFunctions[i].GetName())
            return mLoadedFunctions[i];

    return DBLoad(functionName);
}

