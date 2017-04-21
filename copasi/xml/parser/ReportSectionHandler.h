// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_HeaderHandler
#define COPASI_HeaderHandler

#include <vector>
#include "copasi/xml/parser/CXMLHandler.h"

class CRegisteredCommonName;

class ReportSectionHandler : public CXMLHandler
{
private:
  ReportSectionHandler();

public:
  /**
   * Constructor
   * @param CXMLParser & parser
   * @param CXMLParserData & data
   */
  ReportSectionHandler(CXMLParser & parser, CXMLParserData & data);

  /**
   * Destructor
   */
  virtual ~ReportSectionHandler();

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

  void setSectionContent(std::vector< CRegisteredCommonName > * pSectionContent);

private:
  std::vector< CRegisteredCommonName > * mpSectionContent;
};

#endif //COPASI_HeaderHandler
