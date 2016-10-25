// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_ListOfUnsupportedAnnotationsHandler
#define COPASI_ListOfUnsupportedAnnotationsHandler

#include "copasi/xml/parser/CXMLHandler.h"
#include "copasi/model/CAnnotation.h"

class ListOfUnsupportedAnnotationsHandler : public CXMLHandler
{
private:
  ListOfUnsupportedAnnotationsHandler();

public:
  /**
   * Constructor
   * @param CXMLParser & parser
   * @param CXMLParserData & data
   */
  ListOfUnsupportedAnnotationsHandler(CXMLParser & parser, CXMLParserData & data);

  /**
   * Destructor
   */
  virtual ~ListOfUnsupportedAnnotationsHandler();

  /**
   * Retrieve the list of unsupported annotations.
   * @return
   */
  const CAnnotation::UnsupportedAnnotation & getUnsupportedAnnotations() const;

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
   * The list of unsupported annotations.
   */
  CAnnotation::UnsupportedAnnotation mUnsupportedAnnotations;
};

#endif //COPASI_ListOfUnsupportedAnnotationsHandler
