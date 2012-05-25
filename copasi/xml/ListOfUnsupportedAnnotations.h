// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/ListOfUnsupportedAnnotations.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/25 12:13:29 $
// End CVS Header

// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * ListOfUnsupportedAnnotations.h
 *
 *  Created on: May 24, 2012
 *      Author: shoops
 */

#ifndef COPASI_ListOfUnsupportedAnnotations
#define COPASI_ListOfUnsupportedAnnotations

class UnsupportedAnnotationElement :
    public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
{
private:
  /**
   * Enum of invoked parsers
   */
  enum Element
  {
    UnsupportedAnnotation = 0,
    Content
  };

  // Operations
public:
  /**
   * Constructor
   */
  UnsupportedAnnotationElement(CCopasiXMLParser & parser,
                               SCopasiXMLParserCommon & common);

  /**
   * Destructor
   */
  virtual ~UnsupportedAnnotationElement();

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
   * The level of nested XML elements.
   */
  size_t mLevel;

  /**
   * Information whether an element is empty
   */
  std::stack< bool > mElementEmpty;
};

class ListOfUnsupportedAnnotationsElement:
    public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
{
  // Attributes
private:
  /**
   * Enum of invoked parsers
   */
  enum Element
  {
    ListOfUnsupportedAnnotations = 0,
    UnsupportedAnnotation
  };

  // Operations
public:
  /**
   * Constructor
   */
  ListOfUnsupportedAnnotationsElement(CCopasiXMLParser & parser,
                                      SCopasiXMLParserCommon & common);

  /**
   * Destructor
   */
  virtual ~ListOfUnsupportedAnnotationsElement();

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

  /**
   * Retrieve the unsupported annotations.
   */
  const CAnnotation::UnsupportedAnnotation & getUnsupportedAnnotations() const;

private:
  /**
   * The list of unsupported annotations.
   */
  CAnnotation::UnsupportedAnnotation mUnsupportedAnnotations;

  /**
   * A pointer to the  UnsupportedAnnotation element handler
   */
  UnsupportedAnnotationElement * mpUnsupportedAnnotationElement;
};

#endif // COPASI_ListOfUnsupportedAnnotations
