// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_ListOfHandler
#define COPASI_ListOfHandler

#include "copasi/xml/parser/CXMLHandler.h"

class ListOfHandler : public CXMLHandler
{
private:
  ListOfHandler();

public:
  /**
   * Constructor
   * @param const CXMLHandler::sProcessLogic & listLogic
   * @param const CXMLHandler::sProcessLogic & contentLogic
   * @param CXMLParser & parser
   * @param CXMLParserData & data
   */
  ListOfHandler(const sProcessLogic & listLogic,
                const sProcessLogic & contentLogic,
                CXMLParser & parser,
                CXMLParserData & data);

  /**
   * Destructor
   */
  virtual ~ListOfHandler();

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
  sProcessLogic mListLogic;
  sProcessLogic mContentLogic;
};

#endif //COPASI_ListOfHandler
