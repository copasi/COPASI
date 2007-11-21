// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFParser.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/21 16:15:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRDFParser
#define COPASI_CRDFParser

#include <raptor.h>

#include <iostream>

class CRDFGraph;

class CRDFParser
  {
    // Methods
  public:
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
     * caller to destroy the created graph/
     * &param std::istream & stream
     * @return CRDFGraph * pGraph
     */
    CRDFGraph * parse(std::istream & stream);

    /**
     * A stantic handler to interface with the C parser library. This is called
     * whenever an RDF triple is created. Its only purpose is to call the TripleHandler
     * class method.
     * @param void * pRdfParser
     * @param const raptor_statement * pTriple
     */
    static void TripleHandler(void * pRdfParser, const raptor_statement * pTriple);

    /**
     * This method is executed whenever a triple is created by the underlying parser
     * @param const raptor_statement * pTriple
     */
    void TripleHandler(const raptor_statement * pTriple);

    // Attributes
  private:
    /**
     * Pointer to the underlying C parser from the Raptor library
     */
    raptor_parser * mpParser;

    /**
     * A pointer to the created RDF graph
     */
    CRDFGraph * mpGraph;

    /**
     * This attribute indicates whether the rapor library is initialized
     */
    static bool Initialized;
  };

#endif // COPASI_CRDFParser
