// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFWriter.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/10 20:31:11 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CRDFWriter
#define COPASI_CRDFWriter

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
#endif // COPASI_CRDFWriter
