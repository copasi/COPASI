// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

#ifndef COPASI_CRDFWriter
#define COPASI_CRDFWriter

#include <copasi/copasi.h>

#ifdef COPASI_USE_RAPTOR

#include <raptor.h>

#include <iostream>

#include "copasi/MIRIAM/CRaptorInit.h"

class CRDFGraph;
class CRDFNode;

class CRDFWriter: private CRaptorInit
  {
    // Operations
  public:
    /**
     * Constructor
     */
    CRDFWriter();

    /**
     * Destructor
     */
    ~CRDFWriter();

    /**
     * Convert an RDF graph to an XML string
     * @param  const CRDFGraph * pGraph
     * @return std::string
     */
    static std::string xmlFromGraph(const CRDFGraph * pGraph);

    /**
     * Convert an RDF graph to an XML string. It is the repsonsibility of
     * user to free the allocate memory for the string. If the conversion fails
     * a NULL pointer is returned.
     * @param  const CRDFGraph * pGraph
     * @return char * XML
     */
    char * write(const CRDFGraph * pGraph);

  private:
    /**
     * This adds the default name spaces to the writer
     * @param const CRDFGraph * pGraph
     */
    void initNamespaces(const CRDFGraph * pGraph);

    // Attributes
  private:
    /**
     * Pointer to the underlying C serializer from the Raptor library
     */
    raptor_serializer * mpWriter;

    /**
     * A pointer to the created RDF graph
     */
    CRDFGraph * mpGraph;
  };

#endif // COPASI_USE_RAPTOR

#endif // COPASI_CRDFWriter
