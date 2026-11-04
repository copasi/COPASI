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

#ifndef COPASI_UnitDefinitionHandler
#define COPASI_UnitDefinitionHandler

#include "copasi/xml/parser/CXMLHandler.h"

class UnitDefinitionHandler : public CXMLHandler
{
private:
  UnitDefinitionHandler();

public:
  /**
   * Constructor
   * @param CXMLParser & parser
   * @param CXMLParserData & data
   */
  UnitDefinitionHandler(CXMLParser & parser, CXMLParserData & data);

  /**
   * Destructor
   */
  virtual ~UnitDefinitionHandler();

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
   * The key as provided in the XML
   */
  std::string mKey;
};

#endif //COPASI_UnitDefinitionHandler
