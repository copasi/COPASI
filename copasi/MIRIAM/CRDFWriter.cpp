// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

#include <stdlib.h>

#include <sstream>

#include "copasi/copasi.h"

#include "CRDFWriter.h"
#include "CRDFGraph.h"
#include "CRDFSubject.h"
#include "CRDFObject.h"
#include "CRDFLiteral.h"

#include "copasi/utilities/CCopasiMessage.h"

//static
std::string CRDFWriter::xmlFromGraph(const CRDFGraph * pGraph)
{
  CRDFWriter Writer;

  char * pXML = Writer.CRDFWriter::write(pGraph);

  if (pXML != NULL)
    {
      std::string XML = pXML;
      free(pXML);

      return XML;
    }

  return "";
}

CRDFWriter::CRDFWriter():
  CRaptorInit(),
  mpWriter(NULL),
  mpGraph(NULL)
{
  mpWriter = raptor_new_serializer("rdfxml-abbrev");

  // We do not want <?xml version="1.0" encoding="utf-8"?>
  raptor_serializer_set_feature(mpWriter, RAPTOR_FEATURE_WRITER_XML_DECLARATION, 0);

  // Remove any empty elements
  raptor_serializer_set_feature(mpWriter, RAPTOR_FEATURE_WRITER_AUTO_EMPTY, 1);
}

CRDFWriter::~CRDFWriter()
{
  if (mpWriter != NULL)
    {
      raptor_free_serializer(mpWriter);
      mpWriter = NULL;
    }
}

void CRDFWriter::initNamespaces(const CRDFGraph * pGraph)
{
  std::map< std::string, std::string >::const_iterator it =
    pGraph->getNameSpaceMap().begin();
  std::map< std::string, std::string >::const_iterator end =
    pGraph->getNameSpaceMap().end();

  raptor_uri* pURI = NULL;

  for (; it != end; ++it)
    {
      pURI = raptor_new_uri((const unsigned char *) it->second.c_str());
      raptor_serialize_set_namespace(mpWriter, pURI, (const unsigned char *) it->first.c_str());
      pRaptorFreeUri(pURI);
    }
}

char * CRDFWriter::write(const CRDFGraph * pGraph)
{
  if (pGraph == NULL
      || pGraph->empty())
    return NULL;

  bool success = true;

  void * XML;     /* destination for string */
  size_t Length;  /* length of constructed string */

  initNamespaces(pGraph);

  raptor_uri * pURI = raptor_new_uri((const unsigned char *) "");

  if (raptor_serialize_start_to_string(mpWriter, pURI, & XML, & Length))
    fatalError();

  // We need to add all triplets
  std::set< CRDFTriplet >::const_iterator it = pGraph->getTriplets().begin();
  std::set< CRDFTriplet >::const_iterator end = pGraph->getTriplets().end();

  raptor_uri * pSubjectURI = NULL;
  raptor_uri * pPredicateURI = NULL;
  raptor_uri * pObjectURI = NULL;
  raptor_uri * pLiteralDataTypeURI = NULL;

  raptor_statement Triplet;

  for (; it != end; ++it)
    {
      // Set the subject of the triplet
      const CRDFSubject & Subject = it->pSubject->getSubject();

      switch (Subject.getType())
        {
          case CRDFSubject::RESOURCE:
            Triplet.subject_type = RAPTOR_IDENTIFIER_TYPE_RESOURCE;
            pSubjectURI = raptor_new_uri((const unsigned char *) Subject.getResource().c_str());
            Triplet.subject = pSubjectURI;
            break;

          case CRDFSubject::BLANK_NODE:
            Triplet.subject_type = RAPTOR_IDENTIFIER_TYPE_ANONYMOUS;
            Triplet.subject = Subject.getBlankNodeID().c_str();
            break;
        }

      // Set the predicate of the triplet
      Triplet.predicate_type = RAPTOR_IDENTIFIER_TYPE_RESOURCE;

      if (it->Predicate.getURI() != "")
        pPredicateURI = raptor_new_uri((const unsigned char *) it->Predicate.getURI().c_str());
      else
        pPredicateURI = NULL;

      Triplet.predicate = pPredicateURI;

      // Set the object of the triplet
      const CRDFObject & Object = it->pObject->getObject();

      switch (Object.getType())
        {
          case CRDFObject::RESOURCE:
            Triplet.object_type = RAPTOR_IDENTIFIER_TYPE_RESOURCE;
            pObjectURI = raptor_new_uri((const unsigned char *) Object.getResource().c_str());
            Triplet.object = pObjectURI;
            break;

          case CRDFObject::BLANK_NODE:
            Triplet.object_type = RAPTOR_IDENTIFIER_TYPE_ANONYMOUS;
            Triplet.object = Object.getBlankNodeID().c_str();
            break;

          case CRDFObject::LITERAL:
            Triplet.object_type = RAPTOR_IDENTIFIER_TYPE_LITERAL;
            const CRDFLiteral & Literal = Object.getLiteral();

            switch (Literal.getType())
              {
                case CRDFLiteral::TYPED:
                  pLiteralDataTypeURI = raptor_new_uri((const unsigned char *) Literal.getDataType().c_str());
                  Triplet.object_literal_datatype = pLiteralDataTypeURI;
                  Triplet.object_literal_language = NULL;
                  break;

                case CRDFLiteral::PLAIN:
                  Triplet.object_literal_datatype = NULL;

                  if (Literal.getLanguage() != "")
                    Triplet.object_literal_language = (const unsigned char *) Literal.getLanguage().c_str();
                  else
                    Triplet.object_literal_language = NULL;

                  break;
              }

            Triplet.object = Literal.getLexicalData().c_str();
            break;
        }

      if (raptor_serialize_statement(mpWriter, &Triplet))
        success = false;

      pRaptorFreeUri(pPredicateURI);
      pRaptorFreeUri(pObjectURI);
      pRaptorFreeUri(pLiteralDataTypeURI);
      pRaptorFreeUri(pSubjectURI);
    }

  if (raptor_serialize_end(mpWriter))
    fatalError();

  return static_cast< char * >(XML);
}
