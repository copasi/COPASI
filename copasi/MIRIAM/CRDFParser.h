// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFParser.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/16 20:52:36 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRDFParser
#define COPASI_CRDFParser

#include <raptor.h>

#include <iostream>

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
    virtual ~CRDFParser();

    /**
     * Parse the stream
     * &param std::istream & stream
     * @return bool success
     */
    bool parse(std::istream & stream);

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
    virtual void TripleHandler(const raptor_statement * pTriple);

    // Attributes
  private:
    /**
     * Pointer to the underlying C parser from the Raptor library
     */
    raptor_parser * mpParser;

    static bool Initialized;
  };

#endif // COPASI_CRDFParser
