// CCopasiMessage
// 
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

#include <string>
#include <iostream>

#include <time.h>
#include <stdio.h>
#include <stdarg.h>

#include "copasi.h"
#include "CCopasiMessage.h"
#include "CCopasiException.h"

static string TimeStamp();
#define INITIALTEXTSIZE 1024

CCopasiMessage::CCopasiMessage(void)
{
    // initialize everything
    mType     = RAW;
    mNumber   = 0;
}

CCopasiMessage::CCopasiMessage(const COPASI_MESSAGE_TYPE type, 
                               const char *format, ...)
{
    long TextSize = INITIALTEXTSIZE;
    long Printed = 0;
    
    char *Text = NULL;
    
    va_list Arguments = NULL;
    va_start(Arguments, format);
    
    Text = new char[TextSize + 1];
    
    Printed = vsnprintf(Text, TextSize + 1, format, Arguments);

    while (Printed < 0 || TextSize < Printed)
    {
        delete [] Text;
        
        (Printed < 0) ? TextSize *= 2: TextSize = Printed;
        Text = new char[TextSize + 1];
        
        Printed = vsnprintf(Text, TextSize, format, Arguments);
    }
    va_end(Arguments);

    mType = type;
    mText = Text;
    mNumber = 0;
    
    if (Text) Handler();
}

CCopasiMessage::CCopasiMessage(const COPASI_MESSAGE_TYPE type, 
                               unsigned long number, ...)
{
    long i = 0;

    long TextSize = INITIALTEXTSIZE;
    long Printed = 0;
    
    char *Text = NULL;

#include "messages.h"

    while (Messages[i].No != number && Messages[i].Text) Messages[i++];
    
    if (!Messages[i].Text) FatalError();
    
    va_list Arguments = NULL;
    va_start(Arguments, number);

    Text = new char[TextSize + 1];
    
    Printed = vsnprintf(Text, TextSize, Messages[i].Text, Arguments);

    while (Printed < 0 || TextSize < Printed)
    {
        delete [] Text;
        
        (Printed < 0) ? TextSize *= 2: TextSize = Printed;
        Text = new char[TextSize + 1];
        
        Printed = vsnprintf(Text, TextSize, Messages[i].Text, Arguments);
    }
    
    va_end(Arguments);
    
    mText = Text;
    mType = type;
    mNumber = number;
 
    Handler();
}
        
void CCopasiMessage::Handler()
{
    string Text = mText;
    
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
    mText += Text;

    LineBreak();
    
    if (mType == ERROR) 
    {
        throw CCopasiException(this);
    }
    else
    {
        cout << mText << endl;
    }
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

long CCopasiMessage::GetType(void)
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

void CCopasiMessage::LineBreak()
{
    string Search("\n");
    string Replace("\n>                           < ");
    string::size_type pos = 0;
    
    while (TRUE)
    {
        pos = mText.find(Search, pos);
        if (pos == string::npos) break;

        mText.replace(pos, Search.length(), Replace);
        pos += Replace.length();
    }
}

