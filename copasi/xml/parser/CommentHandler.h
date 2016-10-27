// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CommentHandler
#define COPASI_CommentHandler

#include <sstream>

#include "copasi/xml/parser/CXMLHandler.h"

class CommentHandler : public CXMLHandler
{
private:
  CommentHandler();

public:
  /**
   * Constructor
   * @param CXMLParser & parser
   * @param CXMLParserData & data
   */
  CommentHandler(CXMLParser & parser, CXMLParserData & data);

  /**
   * Destructor
   */
  virtual ~CommentHandler();

  /**
   * Start element handler
   * @param const XML_Char *pszName
   * @param const XML_Char **papszAttrs
   */
  virtual void start(const XML_Char * pszName,
                     const XML_Char ** papszAttrs);

  /**
   * End element handler
   * @param const XML_Char *pszName
   */
  virtual void end(const XML_Char * pszName);

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
   * String stream to handle xhtml comments
   */
  std::ostringstream mXhtml;

  /**
   * Information whether an element is empty
   */
  std::stack< bool > mElementEmpty;
};

#endif //COPASI_CommentHandler
