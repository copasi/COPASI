// CCopasiMessage
// 
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

#include <string>

#include <time.h>
#include <stdio.h>

#include "copasi.h"
#include "CCopasiMessage.h"
#include "CCopasiException.h"

static string TimeStamp();

CCopasiMessage::CCopasiMessage(void)
{
    // initialize everything
    mText     = "";
    mType     = RAW;
}

CCopasiMessage::CCopasiMessage(string text, enum COPASI_MESSAGE_TYPE type)
{
    
    
    mType     = type;
    switch (mType)
    {
    case RAW:
        break;
    case TRACE:
        mText = ">TRACE   ";
        mText += TimeStamp();
        mText += "< ";
        break;
    case WARNING:
        mText = ">WARNING ";
        mText += TimeStamp();
        mText += "< ";
        break;
    case ERROR:
        mText = ">ERROR   ";
        mText += TimeStamp();
        mText += "< ";
        break;
    }
    
    // initialize everything
    mText += text;

    if (mType == ERROR) throw CCopasiException(this);
}

// overload assignment operator
CCopasiMessage &CCopasiMessage::operator=(CCopasiMessage &RHS)
{
    mText   = RHS.mText;
    mType   = RHS.mType;
    
    return *this;
}
CCopasiMessage::~CCopasiMessage(void)
{
}

string CCopasiMessage::GetText(void)
{
    return mText;
}

enum COPASI_MESSAGE_TYPE CCopasiMessage::GetType(void)
{
    return mType;
}

string TimeStamp()
{
    time_t Time;
    tm     *sTime = NULL;
    char str[20];

    time( &Time );
    sTime = localtime(&Time);

    if (sTime)
    {
        sprintf(str, "%d-%.2d-%.2d %.2d:%.2d:%.2d",
                sTime->tm_year + 1900,
                sTime->tm_mon + 1,
                sTime->tm_mday,
                sTime->tm_hour,
                sTime->tm_min,
                sTime->tm_sec);
    }
    else
    {
        sprintf(str, "0000-00-00 00:00:00");
    }
    

    return (string) str;
}
