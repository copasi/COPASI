// CWriteConfig
// 
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

#include <string>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <assert.h>

#include "CGlobals.h"
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

    SetVariable("Version", "string", &Copasi.Version);
}


CWriteConfig::~CWriteConfig(void)
{
    Commit();
}

long CWriteConfig::Flush(void)
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

long CWriteConfig::Commit(void)
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

long CWriteConfig::Fail()
{
    // return the failure state
    return mFail;
}

long CWriteConfig::SetVariable(const string name, 
                               const string type, 
                               const void *pout)
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
    else if ( type == "long" )
    {
        mBuffer << *(long *) pout;
    }
    else if ( type == "short" )
    {
        mBuffer << *(short *) pout;
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

long CWriteConfig::SetVariable(const string name, 
                               const string type, 
                               const void *pout1, 
                               const void *pout2)
{
    mBuffer << name << "=";
    
    // Return the value depending on the type
    if ( type == "node" )
    {
        mBuffer << (long) (*(char *) pout1) << "," << (long) (*(char *) pout2);
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
