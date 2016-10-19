// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "SBMLReferenceHandler.h"

/**
 * Replace SBMLReference with the name type of the handler and implement the
 * three methods below.
 */
SBMLReferenceHandler::SBMLReferenceHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::SBMLReference)
{
  init();
}

// virtual
SBMLReferenceHandler::~SBMLReferenceHandler()
{}

// virtual
CXMLHandler * SBMLReferenceHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool SBMLReferenceHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case COPASI:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * SBMLReferenceHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"SBMLReference", SBMLReference, {BEFORE}},
    {"BEFORE", BEFORE, {SBMLReference, BEFORE}}
  };

  return Elements;
}
