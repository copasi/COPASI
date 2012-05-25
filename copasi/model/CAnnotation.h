// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CAnnotation.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/25 12:12:29 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CAnnotation
#define COPASI_CAnnotation

#include <string>
#include <map>

class CAnnotation
{
public:
  typedef std::map< std::string, std::string > UnsupportedAnnotation;

  // Operations
public:
  /**
   * Default constructor
   */
  CAnnotation();

  /**
   * Copy constructor
   * @param const CAnnotation & src
   */
  CAnnotation(const CAnnotation & src);

  /**
   * Destructor
   */
  ~CAnnotation();

  /**
   * Set the RDF/XML representation of the MIRIAM annotation
   * @param const std::string & miriamAnnotation
   * @param const std::string & newId
   * @param const std::string & oldId
   */
  void setMiriamAnnotation(const std::string & miriamAnnotation,
                           const std::string & newId,
                           const std::string & oldId);

  /**
   * Retrieve the RDF/XML representation of the MIRIAM annotation
   * @return const std::string & miriamAnnotation
   */
  const std::string & getMiriamAnnotation() const;

  /**
   * Set the XHTML Notes
   * @param const std::string & notes
   */
  void setNotes(const std::string & notes);

  /**
   * Retrieve the XHTML notes
   * @return const std::string & notes
   */
  const std::string & getNotes() const;

  /**
   * Comparison operator
   * @param const CAnnotation & rhs
   * @return bool equal
   */
  bool operator == (const CAnnotation & rhs) const;


  /**
   * Retrieve the unsupported annotations in xml format.
   * @return std::map< std::string, std::string > & unsupportedAnnotations
   */
  UnsupportedAnnotation & getUnsupportedAnnotations();
  const UnsupportedAnnotation & getUnsupportedAnnotations() const;

  /**
   * Add an unsupported annotation
   * @param const std::string & name
   * @param const std::string & xml
   * @return bool success
   */
  bool addUnsupportedAnnotation(const std::string & name, const std::string & xml);

  /**
   * Replace an unsupported annotation
   * @param const std::string & name
   * @param const std::string & xml
   * @return bool success
   */
  bool replaceUnsupportedAnnotation(const std::string & name, const std::string & xml);

  /**
   * Remove an unsupported annotation
   * @param const std::string & name
   * @return bool success
   */
  bool removeUnsupportedAnnotation(const std::string & name);

private:
  static bool isValidXML(const std::string & xml);

  // Attributes
private:
  /**
   * Notes in XHTML format
   */
  std::string mNotes;

  /**
   * MIRIAM compliant annotation in RDF/XML format
   */
  std::string mMiriamAnnotation;

  /**
   * The XMLId used in the about statement
   */
  std::string mXMLId;

  /**
   * The annotations which are not supported by COPASI. Note,
   * the name is enforced to be unique.
   */
  UnsupportedAnnotation mUnsupportedAnnotations;
};

#endif // COPASI_CAnnotation
