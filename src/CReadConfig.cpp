// CReadConfig
// 
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

//#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

#include <assert.h>

#include "copasi.h"
#include "CReadConfig.h"

// char *InitInputBuffer(char *name);
static long GetFileSize(const char *name);

CReadConfig::CReadConfig(void)
{
    // initialize everything
    mFilename     = "";
    mLineNumber   = 0;
    mMode         = 0;
    mFail         = 0;

    InitInputBuffer();
}

CReadConfig::CReadConfig(string name)
{
    // initialize everything
    mFilename     = name;
    mLineNumber   = 0;
    mMode         = 0;
    mFail         = 0;

    InitInputBuffer();
}

CReadConfig::~CReadConfig(void)
{
}

int CReadConfig::Fail()
{
    // return the failure state
    return mFail;
}


int CReadConfig::GetVariable(string name, string type, void * pout)
{
    char c[] = " ";
    int equal = 0;
    int Mode = mMode;    
    string Line;
    string Name;
    string Value;

    // Get the current line 
    while (true)
    {
        // For error messages we keep track of the current line number
        // but mBuffer >> is to smart and skips empty lines.
        // while(mBuffer.peek() == '\n') 
        // {
        //     mLineNumber++;
        //     mBuffer.seekg(1, ios::cur);
        // }
        mLineNumber++;

        Line.erase();
        while (true)
        {
            mBuffer.read(c, 1);
            if ( *c == '\n' || mBuffer.eof()) break;
            Line += c;
        }

        // mBuffer >> Line;

        equal = Line.find('=');
        Name  = Line.substr(0, equal);
        Value = Line.substr(equal + 1);

        if (Mode & CReadConfig_SEARCH &&
            name == "Compartment"     &&
            Name == "Compartment")
        {
            if ( LookAhead() != "Volume" )
            {
                Name = "<CONTINUE>";
            }
        }

        if (name == Name) break;

        if (Mode & CReadConfig_SEARCH) 
        {
            if (mBuffer.eof())
            {
                if (!(Mode & CReadConfig_LOOP)) FatalError();
                // Rewind the buffer                
                Mode ^= CReadConfig_LOOP;
                mBuffer.clear();
                mBuffer.seekg(0);
                mLineNumber = 0;
            }
        //    mBuffer.seekg(1, ios::cur); // Skip line break
            continue;
        }
        
        FatalError();
    }
    
    // mBuffer.seekg(1, ios::cur);         // Skip line break
    // Return the value depending on the type
    if ( type == "string" )
    {
        *(string *) pout = Value;
    }
    else if ( type == "double" )
    {
        // may be we should check if Value is really a double
        *(double *) pout = atof(Value.c_str());
    }
    else if ( type == "int" )
    {
        // may be we should check if Value is really a integer
        *(int *) pout = atoi(Value.c_str());
    }
    else
    {
        FatalError();
        mFail = 1; //Error
    }
    
    // We free the line allocated through strdup
    // pfree(szLine);
    return mFail;
}

void CReadConfig::SetMode(int mode)
{
    switch (mode)
    {
    case  CReadConfig_SEARCH:
        mMode |= CReadConfig_SEARCH;
        break;
    case -CReadConfig_SEARCH:
        if (mMode & CReadConfig_SEARCH) mMode ^= CReadConfig_SEARCH;
        break;
    case  CReadConfig_LOOP:
        mMode |= CReadConfig_LOOP;
        break;
    case -CReadConfig_LOOP:
        if (mMode & CReadConfig_LOOP) mMode ^= CReadConfig_LOOP;
        break;
    default:
        // Invalid Mode
        FatalError();
        break;
    }
}

int CReadConfig::InitInputBuffer()
{
    char c[] = " ";
    
    // read the configuration file into the configuration buffer
    ifstream File(mFilename.c_str());
    if (File.fail()) FatalError();

    while (true)
    {
        File.read(c, 1);
        if (File.eof()) break;
        if (File.fail()) FatalError();
        mBuffer << c;
    }
    File.clear();
    
    File.close();
    if (File.fail()) FatalError();
    
    return mFail;
}

string CReadConfig::LookAhead()
{
    streampos pos = mBuffer.tellg();
    
    string Line;
    mBuffer >> Line;
    mBuffer.seekg(pos);
    
    return Line.substr(0, Line.find("="));
}

    
    
