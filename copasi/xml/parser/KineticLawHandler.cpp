// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "KineticLawHandler.h"

/**
 * Replace KineticLaw with the name type of the handler and implement the
 * three methods below.
 */
KineticLawHandler::KineticLawHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::KineticLaw)
{
  init();
}

// virtual
KineticLawHandler::~KineticLawHandler()
{}

// virtual
CXMLHandler * KineticLawHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool KineticLawHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case KineticLaw:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * KineticLawHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"KineticLaw", KineticLaw, {BEFORE}},
    {"BEFORE", BEFORE, {KineticLaw, BEFORE}}
  };

  return Elements;
}
