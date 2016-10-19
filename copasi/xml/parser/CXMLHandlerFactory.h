// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CXMLHandlerFactory
#define COPASI_CXMLHandlerFactory

#include "copasi/utilities/CVector.h"
#include "copasi/xml/parser/CXMLHandler.h"

class CXMLParser;
class CXMLParserData;

class CXMLHandlerFactory : private CVector< CXMLHandler * >
{
private:
  /**
   * Constructor
   */
  CXMLHandlerFactory();

public:
  /**
   * Constructor
   * @param CXMLParser & parser
   * @param CXMLParserData & data
   */
  CXMLHandlerFactory(CXMLParser & parser,
                     CXMLParserData & data);

  /**
   * Destructor
   */
  ~CXMLHandlerFactory();

  /**
   * Retrieve the handler of for the given type
   */
  CXMLHandler * getHandler(const CXMLHandler::Type & type);

private:
  /**
   * Create the handler of for the given type
   */
  CXMLHandler * createHandler(const CXMLHandler::Type & type);

  /**
   * The underlying parser.
   */
  CXMLParser * mpParser;

  /**
   * The shared elements between all element handlers of a parser
   */
  CXMLParserData * mpData;
};
#endif // COPASI_CXMLHandlerFactory
