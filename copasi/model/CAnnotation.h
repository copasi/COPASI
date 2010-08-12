// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CAnnotation.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/08/12 15:21:35 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CAnnotation
#define COPASI_CAnnotation

#include <string>

class CAnnotation
{
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
};

#endif // COPASI_CAnnotation
