// CReadConfig
// 
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

//#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std ;

#include "CReadConfig.h"

// char *InitInputBuffer(char *name);
static long GetFileSize(const char *name);

CReadConfig::CReadConfig(void)
{
    // initialize everything
    mFilename     = "test.txt";
    mpBufferBegin = NULL;
    mLineNumber   = 0;
    mFail         = 0;

    InitInputBuffer();
}

CReadConfig::CReadConfig(string name)
{
    // initialize everything
    mFilename     = name;
    mpBufferBegin = NULL;
    mLineNumber   = 0;
    mFail         = 0;

    InitInputBuffer();
}

CReadConfig::~CReadConfig(void)
{
    Free();
}

CReadConfig::Free(void)
{
    // if the buffer is initialized we free it and reset the buffer pointer
    if (mpBufferBegin)
    {
        free(mpBufferBegin);
        mpBufferBegin = NULL;
    }
    return mFail;
}

int CReadConfig::Fail()
{
    // return the failure state
    return mFail;
}


int CReadConfig::GetVariable(string name, string type, void * pout)
{
    char* szLine = NULL;
    char* szName = NULL;
    char* szValue= NULL;

    // Assure that the config buffer is initialized
    assert( mpBufferBegin != NULL ); 
    
    // For error messages we keep track of the current line number
    mLineNumber++;

    // Get the current line 
    szLine = strdup(strtok(mpBufferPos, "\n"));
    // Move pointer to the beginning of the next line
    mpBufferPos += strlen(szLine) + 1;
    
    // We expect lines in the format Name=Value
    szName  = strtok(szLine, "=");
    szValue = szName + strlen(szName) + 1;
    
    // Assure that we have the name we are looking for
    if ( name != szName )
    {
        mFail = 1; // Error
    }

    // Return the value depending on the type
    if ( type == "string" )
    {
        *(string *) pout = szValue;
    }
    else if ( type == "double" )
    {
        // may be we should check if Value is really a double
        *(double *) pout = atof(szValue);
    }
    else
    {
        mFail = 1; //Error
    }
    
    // We free the line allocated through strdup
    if (szLine) free(szLine);
    return mFail;
}

int CReadConfig::InitInputBuffer()
{
    long FileSize = 0;

    // get the file size of the configuration file
    FileSize = GetFileSize(mFilename.c_str());
    if (FileSize == 0)
    {
        mFail = 1;  // Error
    }
    // allocate and zero the configuration buffer 
    // add 1 to FileSize for zero terminator
    if (!(mpBufferBegin = (char *) calloc(FileSize + 1, sizeof(char))))
    {
        mFail = 1;  // Error
    }
    // initialze the position pointer to the beginning of the buffer
    mpBufferPos = mpBufferBegin;

    // read the configuration file into the configuration buffer
    ifstream File(mFilename.c_str());
    File.read(mpBufferBegin, FileSize);
    if (FileSize != File.gcount())
    {
        mFail = 1;  // Error
    }
    File.close();

    return mFail;
}

static long GetFileSize(const char *name)
{
    long ByteCnt = 0;
    
    // open the bytes in the configuration file
    ifstream File(name);
    // check whether we were successful
    if (File.fail())
    {
        cout << "Error initilizing configuration file: " 
             << name << endl;
        return 0;
    }
    
    // count the bytes of the configuration file
    while (!File.eof()) 
    {
        File.get();
        ByteCnt++;
    } 
    File.close();
    
    // we overcounted the EOF therefore the byte count is reduced by 1
    return ByteCnt-1;
}

