#include "CFunctionDB.h"

CFunctionDB::CFunctionDB() {}

CFunctionDB::~CFunctionDB() {}

void CFunctionDB::SetName(const string & filename) {mFilename = filename;}
    
string CFunctionDB::GetName() {return mFilename;}

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
    
    for (i = 0; i < Size(); i++)
        if (functionName == mLoadedFunction[i].GetName())
            return mLoadedFunction[i];

    return DBLoad(functionName);
}

