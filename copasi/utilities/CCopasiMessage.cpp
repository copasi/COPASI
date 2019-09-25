// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// CCopasiMessage
//
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

#include <string>
#include <iostream>

#include <time.h>
#include <stdio.h>
#include <stdarg.h>

#include "copasi/copasi.h"
#include "CCopasiMessage.h"
#include "messages.h"
#include "CCopasiException.h"
#include "utility.h"

#include "copasi/commandline/COptionParser.h"
#include "copasi/commandline/COptions.h"

#define INITIALTEXTSIZE 1024

#ifdef WIN32
/**
 * The stack of messages. Each message created with one of
 * the specific constructors is automatically added to the stack.
 */
static std::deque< CCopasiMessage > mMessageDeque;
#else
std::deque< CCopasiMessage > CCopasiMessage::mMessageDeque;
#endif

// static
bool CCopasiMessage::IsGUI = false;

const CCopasiMessage & CCopasiMessage::peekFirstMessage()
{
  if (mMessageDeque.empty())
    CCopasiMessage(CCopasiMessage::RAW,
                   MCCopasiMessage + 1);

  return mMessageDeque.front();
}

const CCopasiMessage & CCopasiMessage::peekLastMessage()
{
  if (mMessageDeque.empty())
    CCopasiMessage(CCopasiMessage::RAW,
                   MCCopasiMessage + 1);

  return mMessageDeque.back();
}

CCopasiMessage CCopasiMessage::getFirstMessage()
{
  if (mMessageDeque.empty())
    CCopasiMessage(CCopasiMessage::RAW,
                   MCCopasiMessage + 1);

  CCopasiMessage Message(mMessageDeque.front());
  mMessageDeque.pop_front();

  return Message;
}

CCopasiMessage CCopasiMessage::getLastMessage()
{
  if (mMessageDeque.empty())
    CCopasiMessage(CCopasiMessage::RAW,
                   MCCopasiMessage + 1);

  CCopasiMessage Message(mMessageDeque.back());
  mMessageDeque.pop_back();

  return Message;
}

std::string CCopasiMessage::getAllMessageText(const bool & chronological)
{
  std::string Text = "";
  CCopasiMessage(*getMessage)() = chronological ? getFirstMessage : getLastMessage;

  while (!mMessageDeque.empty())
    {
      if (Text != "") Text += "\n";

      Text += getMessage().getText();
    }

  return Text;
}

void CCopasiMessage::clearDeque()
{
  mMessageDeque.clear();
  return;
}

size_t CCopasiMessage::size()
{
  return mMessageDeque.size();
}

CCopasiMessage::Type CCopasiMessage::getHighestSeverity()
{
  CCopasiMessage::Type HighestSeverity = RAW;
  std::deque< CCopasiMessage >::const_iterator it = mMessageDeque.begin();
  std::deque< CCopasiMessage >::const_iterator end = mMessageDeque.end();

  for (; it != end; ++it)
    if (it->getType() > HighestSeverity) HighestSeverity = it->getType();

  return HighestSeverity;
}

bool CCopasiMessage::checkForMessage(const size_t & number)
{
  std::deque< CCopasiMessage >::const_iterator it = mMessageDeque.begin();
  std::deque< CCopasiMessage >::const_iterator end = mMessageDeque.end();

  for (; it != end; ++it)
    if (it->getNumber() == number) return true;

  return false;
}

// static
void CCopasiMessage::setIsGUI(const bool & isGUI)
{
  IsGUI = isGUI;
}

CCopasiMessage::CCopasiMessage(void):
  mText(),
  mType(CCopasiMessage::RAW),
  mNumber(0)
{}

CCopasiMessage::CCopasiMessage(const CCopasiMessage & src):
  mText(src.mText),
  mType(src.mType),
  mNumber(src.mNumber)
{}

CCopasiMessage::CCopasiMessage(CCopasiMessage::Type type,
                               const char *format, ...)
{
  C_INT32 TextSize = INITIALTEXTSIZE;
  C_INT32 Printed = 0;

  char *Text = NULL;
  Text = new char[TextSize + 1];

  va_list Arguments; // = NULL;
  va_start(Arguments, format);
  Printed = vsnprintf(Text, TextSize, format, Arguments);
  va_end(Arguments);

  while (Printed < 0 || TextSize < Printed)
    {
      delete [] Text;

      (Printed < 0) ? TextSize *= 2 : TextSize = Printed;
      Text = new char[TextSize + 1];

      va_list Arguments; // = NULL;
      va_start(Arguments, format);
      Printed = vsnprintf(Text, TextSize, format, Arguments);
      va_end(Arguments);
    }

  mText = Text;
  delete[] Text;
  mType = type;
  mNumber = 0;

  handler();
}

CCopasiMessage::CCopasiMessage(CCopasiMessage::Type type,
                               size_t number, ...)
{
  C_INT32 i = 0;

  C_INT32 TextSize = INITIALTEXTSIZE;
  C_INT32 Printed = 0;

  while (Messages[i].No != number && Messages[i].Text)
    i++;

  if (!Messages[i].Text)
    fatalError();

  char *Text = NULL;
  Text = new char[TextSize + 1];

  va_list Arguments; // = NULL;
  va_start(Arguments, number);
  Printed = vsnprintf(Text, TextSize, Messages[i].Text, Arguments);
  va_end(Arguments);

  while (Printed < 0 || TextSize < Printed)
    {
      delete [] Text;

      (Printed < 0) ? TextSize *= 2 : TextSize = Printed;
      Text = new char[TextSize + 1];

      va_list Arguments; // = NULL;
      va_start(Arguments, number);
      Printed = vsnprintf(Text, TextSize, Messages[i].Text, Arguments);
      va_end(Arguments);
    }

  mText = Text;
  delete [] Text;

  mType = type;
  mNumber = number;

  handler();
}

void CCopasiMessage::handler(const bool & /* _throw */)
{
  std::string Text = mText;

  switch (mType)
    {
      case RAW:
        mText = "";
        break;

      case TRACE:
        mText = ">TRACE ";
        mText += LocalTimeStamp();
        mText += "<\n";
        break;

      case WARNING:
        mText = ">WARNING ";
        mText += LocalTimeStamp();
        mText += "<\n";
        break;

      case COMMANDLINE:
        if (IsGUI)
          {
            mText = ">WARNING ";
          }
        else
          {
            mText = ">ERROR ";
          }

        mText += LocalTimeStamp();
        mText += "<\n";
        break;

      case ERROR:
        mText = ">ERROR ";
        mText += LocalTimeStamp();
        mText += "<\n";
        break;

      case EXCEPTION:
        mText = ">EXCEPTION ";
        mText += LocalTimeStamp();
        mText += "<\n";
        break;

      case RAW_FILTERED:
        mText = ">RAW(filtered) ";
        mText += LocalTimeStamp();
        mText += "<\n";
        break;

      case TRACE_FILTERED:
        mText = ">TRACE(filtered) ";
        mText += LocalTimeStamp();
        mText += "<\n";
        break;

      case COMMANDLINE_FILTERED:
        mText = ">COMMANDLINE(filtered) ";
        mText += LocalTimeStamp();
        mText += "<\n";
        break;

      case WARNING_FILTERED:
        mText = ">WARNING(filtered) ";
        mText += LocalTimeStamp();
        mText += "<\n";
        break;

      case ERROR_FILTERED:
        mText = ">ERROR(filtered) ";
        mText += LocalTimeStamp();
        mText += "<\n";
        break;

      case EXCEPTION_FILTERED:
        mText = ">EXCEPTION(filtered) ";
        mText += LocalTimeStamp();
        mText += "<\n";
        break;
    }

  mText += Text;

  if (mType != RAW) lineBreak();

  // Remove the message: No more messages.
  if (mMessageDeque.size() == 1 &&
      mMessageDeque.back().getNumber() == MCCopasiMessage + 1)
    getLastMessage();

  mMessageDeque.push_back(*this);

  // All messages are printed to std::cerr
  if (COptions::compareValue("Verbose", true) &&
      mNumber != MCCopasiMessage + 1)
    {
      std::cerr << mText << std::endl;

#ifdef COPASI_DEBUG_TRACE
      DebugFile << mText << std::endl;
#endif // COPASI_DEBUG_TRACE
    }

  if (mType == EXCEPTION)
    throw CCopasiException(*this);
}

// overload assignment operator
CCopasiMessage &CCopasiMessage::operator=(const CCopasiMessage & RHS)
{
  if (this == &RHS)
    return *this;

  mText = RHS.mText;
  mType = RHS.mType;
  mNumber = RHS.mNumber;

  return *this;
}
CCopasiMessage::~CCopasiMessage(void) {}
const std::string & CCopasiMessage::getText(void) const {return mText;}
const CCopasiMessage::Type & CCopasiMessage::getType(void) const {return mType;}
const size_t & CCopasiMessage::getNumber(void) const {return mNumber;}

void CCopasiMessage::lineBreak()
{
  std::string Search("\n");
  std::string Replace("\n  ");
  std::string::size_type pos = 0;

  while (true)
    {
      pos = mText.find(Search, pos);

      if (pos == std::string::npos)
        break;

      mText.replace(pos, Search.length(), Replace);

      pos += Replace.length();
    }
}
