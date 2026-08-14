// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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
   * Start element handler
   * @param const XML_Char *pszName
   * @param const XML_Char **papszAttrs
   */
  void start(const XML_Char * pszName,
             const XML_Char ** papszAttrs) override;

  /**
   * End element handler
   * @param const XML_Char *pszName
   */
  void end(const XML_Char * pszName) override;

protected:

  /**
   * Process the start of an element
   * @param const XML_Char *pszName
   * @param const XML_Char **papszAttrs
   * @return CXMLHandler * pHandlerToCall
   */
  CXMLHandler * processStart(const XML_Char * pszName,
                             const XML_Char ** papszAttrs) override;

  /**
   * Process the end of an element
   * @param const XML_Char *pszName
   * @return bool finished
   */
  bool processEnd(const XML_Char * pszName) override;

  /**
   * Retrieve the structure containing the process logic for the handler.
   * @return sElementInfo *
   */
  sProcessLogic * getProcessLogic() const override;

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
