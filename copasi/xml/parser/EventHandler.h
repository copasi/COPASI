// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

#ifndef COPASI_EventHandler
#define COPASI_EventHandler

#include "copasi/xml/parser/CXMLHandler.h"

class EventHandler : public CXMLHandler
{
private:
  EventHandler();

public:
  /**
   * Constructor
   * @param CXMLParser & parser
   * @param CXMLParserData & data
   */
  EventHandler(CXMLParser & parser, CXMLParserData & data);

  /**
   * Destructor
   */
  virtual ~EventHandler();

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
   * The original key of the event.
   */
  std::string mKey;
};

#endif //COPASI_EventHandler
