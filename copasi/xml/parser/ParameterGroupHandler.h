// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_ParameterGroupHandler
#define COPASI_ParameterGroupHandler

#include "copasi/xml/parser/CXMLHandler.h"

class CCopasiParameterGroup;

class ParameterGroupHandler : public CXMLHandler
{
private:
  ParameterGroupHandler();

public:
  /**
   * Constructor
   * @param CXMLParser & parser
   * @param CXMLParserData & data
   */
  ParameterGroupHandler(CXMLParser & parser, CXMLParserData & data);

  /**
   * Destructor
   */
  virtual ~ParameterGroupHandler();

  /**
   * Set the derived element for which the handler is called such as methods and problems
   * @param const XML_Char * pszName,
   * @param CCopasiParameterGroup * pDerivedElement
   */
  void setDerivedElement(const XML_Char * pszName, CCopasiParameterGroup * pDerivedElement);

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
  bool isUniqueParameter() const;

  /**
   * A flag indicating whether the current element is derived from
   * a parameter group.
   */
  std::string mDerivedElement;

  /**
   * A stack of groups which contains the hierarchy of currently
   * processed groups.
   */
  std::stack< CCopasiParameterGroup * > mParameterGroupStack;

  /**
   * A map listing parameters for which the uniqueness is not enforced
   */
  std::map< std::string, std::set< std::string > > mNonUniqueParameters;
};

#endif //COPASI_ParameterGroupHandler
