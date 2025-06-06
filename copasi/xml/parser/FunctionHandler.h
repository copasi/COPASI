// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_FunctionHandler
#define COPASI_FunctionHandler

#include "copasi/xml/parser/CXMLHandler.h"

class FunctionHandler : public CXMLHandler
{
private:
  FunctionHandler();

public:
  /**
   * Constructor
   * @param CXMLParser & parser
   * @param CXMLParserData & data
   */
  FunctionHandler(CXMLParser & parser, CXMLParserData & data);

  /**
   * Destructor
   */
  virtual ~FunctionHandler();

protected:

  /**
   * Process the start of an element
   * @param const XML_Char *pszName
   * @param const XML_Char **papszAttrs
   * @return CXMLHandler * pHandlerToCall
   */
  virtual CXMLHandler * processStart(const XML_Char * pszName,
                                     const XML_Char ** papszAttrs);

  /**
   * Process the end of an element
   * @param const XML_Char *pszName
   * @return bool finished
   */
  virtual bool processEnd(const XML_Char * pszName);

  /**
   * Retrieve the structure containing the process logic for the handler.
   * @return sElementInfo *
   */
  virtual sProcessLogic * getProcessLogic() const;

private:
  /**
   * The key in the CopasiML file
   */
  std::string mKey;

  /**
   * The infix expression of the function
   */
  std::string mInfix;

  /**
   * The index of a function with the same name
   */
  std::set< size_t > mExistingFunctionIndex;
};

#endif //COPASI_FunctionHandler
