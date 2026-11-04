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

#ifndef COPASI_GradientStopHandler
#define COPASI_GradientStopHandler

#include "copasi/xml/parser/CXMLHandler.h"

class GradientStopHandler : public CXMLHandler
{
private:
  GradientStopHandler();

public:
  /**
   * Constructor
   * @param CXMLParser & parser
   * @param CXMLParserData & data
   */
  GradientStopHandler(CXMLParser & parser, CXMLParserData & data);

  /**
   * Destructor
   */
  virtual ~GradientStopHandler();

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
};

#endif //COPASI_GradientStopHandler
