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
    mFileName     = "NULL";
    mLineNumber   = 0;
    mFail         = 0;

    mBuffer.setf(ios::scientific); 
}

CWriteConfig::CWriteConfig(string name)
{
    // initialize everything
    mFileName     = name;
    mLineNumber   = 0;
    mFail         = 0;

    mBuffer.setf(ios::scientific); 
}


CWriteConfig::~CWriteConfig(void)
{
    Commit();
}

CWriteConfig::Commit(void)
{
#ifdef WIN32
    ofstream ConfigFile(mFileName.c_str(), COPASI__msbug ios::binary );
#else
    ofstream ConfigFile(mFileName.c_str());
#endif

    ConfigFile.write(mBuffer.str(), mBuffer.pcount());
    if( mBuffer.pcount() != ConfigFile.tellp())
    {
        mFail = 1;
    }

    return mFail;
}

int CWriteConfig::Fail()
{
    // return the failure state
    return mFail;
}

int CWriteConfig::SetVariable(string name, string type, void * pout)
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
        mFail = 1; //Error
    }
    
    mBuffer << endl;
    mLineNumber++;

    return mFail;
}



