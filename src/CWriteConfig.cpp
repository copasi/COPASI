// CWriteConfig
// 
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

#include <string>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <assert.h>

#include "copasi.h"
#include "CWriteConfig.h"


CWriteConfig::CWriteConfig(void)
{
    // initialize everything
    mFileName     = "";
    mOpenMode     = ios::out;
    mLineNumber   = 0;
    mFail         = 0;

    mBuffer.setf(ios::scientific); 
    mBuffer.precision(16);
}

CWriteConfig::CWriteConfig(const string& name)
{
    // initialize everything
    mFileName     = name;
    mOpenMode     = ios::out;
    mLineNumber   = 0;
    mFail         = 0;

    mBuffer.setf(ios::scientific);
    mBuffer.precision(16);
}


CWriteConfig::~CWriteConfig(void)
{
    Commit();
}

int CWriteConfig::Flush(void)
{
    if (Commit())
    {
        FatalError();
        return mFail;
    }
    
    mBuffer.freeze(0);
    mBuffer.seekp(0);

    return mFail;
}

int CWriteConfig::Commit(void)
{
#ifdef WIN32
    mOpenMode |= ios::binary;
#endif

    ofstream ConfigFile(mFileName.c_str(), mOpenMode );
    if (ConfigFile.fail())
    {
        FatalError();
        return mFail = 1;
    }

    ConfigFile.write(mBuffer.str(), mBuffer.pcount());
    if (ConfigFile.fail())
    {
        FatalError();
        return mFail = 1;
    }

    mOpenMode |= ios::app;
    return mFail;
}

int CWriteConfig::Fail()
{
    // return the failure state
    return mFail;
}

int CWriteConfig::SetVariable(const string name, 
                              const string type, 
                              void *pout)
{
    mBuffer << name << "=";
    
    // Return the value depending on the type
    if ( type == "string" )
    {
        mBuffer << *(string *) pout;
    }
    else if ( type == "double" )
    {
        mBuffer << *(double *) pout;
    }
    else if ( type == "int" )
    {
        mBuffer << *(int *) pout;
    }
    else
    {
        FatalError();
        mFail = 1; //Error
    }
    
    mBuffer << endl;
    mLineNumber++;

    return mFail;
}

int CWriteConfig::SetVariable(const string name, 
                              const string type, 
                              void *pout1, 
                              void *pout2)
{
    mBuffer << name << "=";
    
    // Return the value depending on the type
    if ( type == "node" )
    {
        mBuffer << (int) (*(char *) pout1) << "," << (int) (*(char *) pout2);
    }
    else
    {
        FatalError();
        mFail = 1; //Error
    }
    
    mBuffer << endl;
    mLineNumber++;

    return mFail;
}
