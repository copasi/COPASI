// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_UnsupportedAnnotationHandler
#define COPASI_UnsupportedAnnotationHandler

#include <sstream>

#include "copasi/xml/parser/CXMLHandler.h"

class UnsupportedAnnotationHandler : public CXMLHandler
{
private:
  UnsupportedAnnotationHandler();

public:
  /**
   * Constructor
   * @param CXMLParser & parser
   * @param CXMLParserData & data
   */
  UnsupportedAnnotationHandler(CXMLParser & parser, CXMLParserData & data);

  /**
   * Destructor
   */
  virtual ~UnsupportedAnnotationHandler();

  /**
   * Retrieve the name
   * @return const std::string & name
   */
  const std::string & getName() const;

  /**
   * Retrieve the XML
   * @return std::string XML
   */
  std::string getXML() const;

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
   * The name of the unsupported annotation
   */
  std::string mName;

  /**
   * String stream to handle XML content
   */
  std::ostringstream mXML;

  /**
   * Information whether an element is empty
   */
  std::stack< bool > mElementEmpty;
};

#endif //COPASI_UnsupportedAnnotationHandler
