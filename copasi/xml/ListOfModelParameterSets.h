// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/ListOfModelParameterSets.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/25 12:13:30 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_ListOfModelParameterSets
#define COPASI_ListOfModelParameterSets

class ModelParameterElement:
    public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
{
  // Attributes
private:
  /**
   * Enum of invoked parsers
   */
  enum Element
  {
    ModelParameter = 0,
    InitialExpression
  };

  // Operations
public:
  /**
   * Constructor
   */
  ModelParameterElement(CCopasiXMLParser & parser,
                        SCopasiXMLParserCommon & common);

  /**
   * Destructor
   */
  virtual ~ModelParameterElement();

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
};

class ModelParameterGroupElement:
    public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
{
  // Attributes
private:
  /**
   * Enum of invoked parsers
   */
  enum Element
  {
    ModelParameterGroup = 0,
    Content
  };

  // Operations
public:
  /**
   * Constructor
   */
  ModelParameterGroupElement(CCopasiXMLParser & parser,
                             SCopasiXMLParserCommon & common);

  /**
   * Destructor
   */
  virtual ~ModelParameterGroupElement();

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
   * A pointer to the ModelParameterGroup Element handler
   */
  ModelParameterGroupElement * mpModelParameterGroupElement;

  /**
   * A pointer to the  ModelParameterElement handler
   */
  ModelParameterElement * mpModelParameterElement;
};

class ModelParameterSetElement:
    public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
{
  // Attributes
private:
  /**
   * Enum of invoked parsers
   */
  enum Element
  {
    ModelParameterSet = 0,
    MiriamAnnotation,
    Comment,
    ListOfUnkownAnnotations,
    Content
  };

  // Operations
public:
  /**
   * Constructor
   */
  ModelParameterSetElement(CCopasiXMLParser & parser,
                           SCopasiXMLParserCommon & common);

  /**
   * Destructor
   */
  virtual ~ModelParameterSetElement();

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

  /**
   * A pointer to the ModelParameterGroup element handler
   */
  ModelParameterGroupElement * mpModelParameterGroupElement;

  /**
   * A pointer to the  ModelParameter element handler
   */
  ModelParameterElement * mpModelParameterElement;
};

class ListOfModelParameterSetsElement:
    public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
{
  // Attributes
private:
  /**
   * Enum of invoked parsers
   */
  enum Element
  {
    ListOfModelParameterSets = 0,
    ModelParameterSet
  };

  // Operations
public:
  /**
   * Constructor
   */
  ListOfModelParameterSetsElement(CCopasiXMLParser & parser,
                                  SCopasiXMLParserCommon & common);

  /**
   * Destructor
   */
  virtual ~ListOfModelParameterSetsElement();

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
   * The key of the active parameter set
   */
  std::string mActiveSet;

  /**
   * A pointer to the  ModelParameterSet element handler
   */
  ModelParameterSetElement * mpModelParameterSetElement;
};

#endif // COPASI_ListOfModelParameterSets
