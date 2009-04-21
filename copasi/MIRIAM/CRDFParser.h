// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFParser.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/21 16:16:41 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRDFParser
#define COPASI_CRDFParser

#include <raptor.h>

#include <iostream>

#include "copasi/MIRIAM/CRaptorInit.h"

class CRDFGraph;

class CRDFParser : private CRaptorInit
{
  // Methods
public:
  /**
   * Convert an RDF/XML syntax string to an RDF Graph. If the conversion fails a
   * NULL pointer is returned. Otherwise a pointer to the resulting graph is
   * returned. It is the responsibility of the caller to destroy the created graph.
   * @param const std::string & xml
   * @return CRDFGraph * graphFromXml
   */
  static CRDFGraph * graphFromXml(const std::string & xml);

  /**
   * Default Constructor
   */
  CRDFParser();

  /**
   * Destructor
   */
  ~CRDFParser();

  /**
   * Parse the stream. If the parsing fails a NULL pointer is returned. Otherwise
   * a pointer to the resulting graph is returned. It is the responsibility of the
   * caller to destroy the created graph.
   * &param std::istream & stream
   * @return CRDFGraph * pGraph
   */
  CRDFGraph * parse(std::istream & stream);

  /**
   * A static handler to interface with the C parser library. This is called
   * whenever an RDF triple is created. Its only purpose is to add the triple
   * to the graph which must provide addTriplet(CRDFSubject, std::string, CRDFObject);
   * @param void * pGraph
   * @param const raptor_statement * pTriple
   */
  static void TripleHandler(void * pGraph, const raptor_statement * pTriple);

  /**
   * A static handler to interface with the C parser library. This is called
   * whenever a namespace is declared.
   * @param void * pGraph
   * @param raptor_namespace * pNameSpace
   */
  static void NameSpaceHandler(void * pGraph, raptor_namespace * pNameSpace);

  /**
   * A static handler to interface with the C parser library. This is called
   * whenever a node id needs to be generated.
   * @param void * pGraph
   * @param raptor_genid_type type
   * @param unsigned char * userNodeId
   * @return unsigned char * generatedId
   */
  static unsigned char * GenerateIdHandler(void * pGraph,
      raptor_genid_type type,
      unsigned char * userNodeId);

  /**
   * A static handler to interface with the C parser library. This is called
   * whenever the parser encounters a fatal error;
   * @param void * userdata (ignored)
   * @param raptor_locator * pLocator
   * @param const char * message
   */
  static void FatalErrorHandler(void *, raptor_locator * pLocator, const char * message);

  /**
   * A static handler to interface with the C parser library. This is called
   * whenever the parser encounters an error;
   * @param void * userdata (ignored)
   * @param raptor_locator * pLocator
   * @param const char * message
   */
  static void ErrorHandler(void *, raptor_locator * pLocator, const char * message);

  /**
   * A static handler to interface with the C parser library. This is called
   * whenever the parser encounters a warning;
   * @param void * userdata (ignored)
   * @param raptor_locator * pLocator
   * @param const char * message
   */
  static void WarningHandler(void *, raptor_locator * pLocator, const char * message);

  // Attributes
private:
  /**
   * Pointer to the underlying C parser from the Raptor library
   */
  raptor_parser * mpParser;
};

#endif // COPASI_CRDFParser
