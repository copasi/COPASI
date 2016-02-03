// Copyright (C) 2012 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_ListOfUnitDefinitions
#define COPASI_ListOfUnitDefinitions

//class CUnitDefinition;

class UnitDefinitionElement:
  public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
{
  // Attributes
private:
  /**
   * Enum of invoked parsers
   */
  enum Element
  {
    UnitDefinition = 0,
    MiriamAnnotation,
    Comment,
    ListOfUnsupportedAnnotations,
    Expression
  };

  // Operations
public:
  /**
   * Constructor
   */
  UnitDefinitionElement(CCopasiXMLParser & parser,
                           SCopasiXMLParserCommon & common);

  /**
   * Destructor
   */
  virtual ~UnitDefinitionElement();

  /**
   * Start element handler
   * @param const XML_Char *pszName
   * @param const XML_Char **papszAttrs
   */
  virtual void start(const XML_Char *pszName,
                     const XML_Char **papszAttrs);

  /**
   * End element handler
   * @param const XML_Char *pszName
   */
  virtual void end(const XML_Char *pszName);

private:
  /**
   * The key as provided in the XML
   */
  std::string mKey;

//  /**
//   * Pointer shared with the creation of a
//   * UnitDefinition (with name and symbol)
//   * and setting the expression.
//   */
//  CUnitDefinition * mpUnitDefinition;
};

class ListOfUnitDefinitionsElement:
  public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
{
  // Attributes
private:
  /**
   * Enum of invoked parsers
   */
  enum Element
  {
    ListOfUnitDefinitions = 0,
    UnitDefinition
  };

  // Operations
public:
  /**
   * Constructor
   */
  ListOfUnitDefinitionsElement(CCopasiXMLParser & parser,
                                  SCopasiXMLParserCommon & common);

  /**
   * Destructor
   */
  virtual ~ListOfUnitDefinitionsElement();

  /**
   * Start element handler
   * @param const XML_Char *pszName
   * @param const XML_Char **papszAttrs
   */
  virtual void start(const XML_Char *pszName,
                     const XML_Char **papszAttrs);

  /**
   * End element handler
   * @param const XML_Char *pszName
   */
  virtual void end(const XML_Char *pszName);

private:
//  /**
//   * The key of the active parameter set
//   */
//  std::string mActiveSet;
  /**
   * A pointer to the  UnitDefinition element handler
   */
  UnitDefinitionElement * mpUnitDefinitionElement;

};

#endif // COPASI_ListOfUnitDefinitions
