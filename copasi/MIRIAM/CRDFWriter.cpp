// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFWriter.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/29 15:00:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <sstream>

#include "copasi.h"

#include "CRDFWriter.h"
#include "CRDFGraph.h"
#include "CRDFNode.h"
#include "CRDFEdge.h"
#include "CRDFSubject.h"
#include "CRDFObject.h"
#include "CRDFLiteral.h"

#include "utilities/CCopasiMessage.h"

//static
std::string CRDFWriter::xmlFromGraph(const CRDFGraph * pGraph)
{
  CRDFWriter Writer;

  char * XML = Writer.CRDFWriter::write(pGraph);

  if (XML != NULL)
    return XML;

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

  initNamespaces();
}

CRDFWriter::~CRDFWriter()
{
  if (mpWriter != NULL)
    raptor_free_serializer(mpWriter);
}

void CRDFWriter::initNamespaces()
{
  raptor_uri* pURI = NULL;

  pURI = raptor_new_uri((const unsigned char *) "http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  raptor_serialize_set_namespace(mpWriter, pURI, (const unsigned char *) "rdf");

  pURI = raptor_new_uri((const unsigned char *) "http://purl.org/dc/elements/1.1/");
  raptor_serialize_set_namespace(mpWriter, pURI, (const unsigned char *) "dc");

  pURI = raptor_new_uri((const unsigned char *) "http://purl.org/dc/terms/");
  raptor_serialize_set_namespace(mpWriter, pURI, (const unsigned char *) "dcterms");

  pURI = raptor_new_uri((const unsigned char *) "http://www.w3.org/2001/vcard-rdf/3.0#");
  raptor_serialize_set_namespace(mpWriter, pURI, (const unsigned char *) "vcard");

  pURI = raptor_new_uri((const unsigned char *) "http://biomodels.net/biology-qualifiers/");
  raptor_serialize_set_namespace(mpWriter, pURI, (const unsigned char *) "bqbiol");

  pURI = raptor_new_uri((const unsigned char *) "http://biomodels.net/model-qualifiers/");
  raptor_serialize_set_namespace(mpWriter, pURI, (const unsigned char *) "bqmodel");
}

char * CRDFWriter::write(const CRDFGraph * pGraph)
{
  bool success = true;

  char * XML;  /* destination for string */
  size_t Length;  /* length of constructed string */

  raptor_uri * pURI = raptor_new_uri((const unsigned char *) "");

  if (raptor_serialize_start_to_string(mpWriter, pURI, (void **) & XML, & Length))
    fatalError();

  // We need do add all subject nodes.
  // This means we need to iterate over all Resource and BlankID nodes
  std::map< std::string, CRDFNode * >::const_iterator itMap;
  std::map< std::string, CRDFNode * >::const_iterator endMap;

  itMap = pGraph->getBlankNodeMap().begin();
  endMap = pGraph->getBlankNodeMap().end();
  for (; itMap != endMap; ++itMap)
    if (itMap->second->isSubjectNode())
      success &= addSubjectNode(itMap->second);

  itMap = pGraph->getLocalResourceNodeMap().begin();
  endMap = pGraph->getLocalResourceNodeMap().end();
  for (; itMap != endMap; ++itMap)
    if (itMap->second->isSubjectNode())
      success &= addSubjectNode(itMap->second);

  // We might be describing a remote resource
  std::vector< CRDFNode *>::const_iterator itVector;
  std::vector< CRDFNode *>::const_iterator endVector;
  for (itVector = pGraph->getRemoteResourceNodes().begin(), endVector = pGraph->getRemoteResourceNodes().end();
       itVector != endVector; ++itVector)
    if ((*itVector)->isSubjectNode())
      success &= addSubjectNode((*itVector));

  if (raptor_serialize_end(mpWriter))
    fatalError();

  return XML;
}

bool CRDFWriter::addSubjectNode(const CRDFNode * pSubjectNode)
{
  bool success = true;

  raptor_uri * pSubjectURI = NULL;
  raptor_uri * pPredicateURI = NULL;
  raptor_uri * pObjectURI = NULL;
  raptor_uri * pLiteralDataTypeURI = NULL;

  raptor_statement Triplet;

  // Set the subject of the triplet
  const CRDFSubject & Subject = pSubjectNode->getSubject();
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

  std::vector< CRDFEdge >::const_iterator it = pSubjectNode->getEdges().begin();
  std::vector< CRDFEdge >::const_iterator end = pSubjectNode->getEdges().end();

  for (; it != end; ++it)
    {
      // Set the predicate of the triplet
      Triplet.predicate_type = RAPTOR_IDENTIFIER_TYPE_RESOURCE;
      pPredicateURI = raptor_new_uri((const unsigned char *) it->getPredicate().c_str());
      Triplet.predicate = pPredicateURI;

      // Set the object of the triplet
      const CRDFNode * pProperty = it->getPropertyNode();
      if (!pProperty->isObjectNode())
        {
          success = false;
          continue;
        }

      const CRDFObject & Object = pProperty->getObject();
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
    }

  pRaptorFreeUri(pSubjectURI);

  return success;
}
