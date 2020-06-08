// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <sstream>
#include <string.h>

#include "copasi/copasi.h"

#include "CRDFParser.h"
#include "CRDFGraph.h"
#include "CRDFSubject.h"
#include "CRDFObject.h"
#include "CRDFLiteral.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CCopasiMessage.h"

// static
CRDFGraph * CRDFParser::graphFromXml(const std::string & xml)
{
  CRDFParser Parser;

  std::istringstream XML;
  XML.str(xml);

  return Parser.parse(XML);
}

CRDFParser::CRDFParser() :
  CRaptorInit(),
  mpParser(NULL)
{
  mpParser = raptor_new_parser("rdfxml");

  raptor_set_fatal_error_handler(mpParser, NULL, &CRDFParser::FatalErrorHandler);
  raptor_set_error_handler(mpParser, NULL, &CRDFParser::ErrorHandler);
  raptor_set_warning_handler(mpParser, NULL, &CRDFParser::WarningHandler);
}

CRDFParser::~CRDFParser()
{
  if (mpParser != NULL)
    raptor_free_parser(mpParser);
}

CRDFGraph * CRDFParser::parse(std::istream & stream)
{
  bool success = true;
  bool done = false;

  stream.imbue(std::locale::classic());
  stream.precision(std::numeric_limits<double>::digits10 + 2);

  // Create the new graph
  CRDFGraph * pGraph = new CRDFGraph;

  unsigned C_INT32 BUFFER_SIZE = 0xfffe;
  char * pBuffer = new char[BUFFER_SIZE + 1];

  stream.get(pBuffer, BUFFER_SIZE, 0);

  if (stream.gcount() != 0)
    {
      raptor_uri * pURI = raptor_new_uri((unsigned char *) "#");

      if (raptor_start_parse(mpParser, pURI))
        fatalError();

      raptor_set_statement_handler(mpParser, pGraph, &CRDFParser::TripleHandler);
      raptor_set_namespace_handler(mpParser, pGraph, &CRDFParser::NameSpaceHandler);
      raptor_set_generate_id_handler(mpParser, pGraph, &CRDFParser::GenerateIdHandler);

      while (!done)
        {
          if (stream.eof()) done = true;

          if (stream.fail() && !done)
            fatalError();

          if (raptor_parse_chunk(mpParser,
                                 (unsigned char *) pBuffer,
                                 strlen(pBuffer),
                                 done ? 1 : 0))
            {
              done = true;
              success = false;
            }

          stream.get(pBuffer, BUFFER_SIZE, 0);
        }

      pRaptorFreeUri(pURI);
    }

  delete [] pBuffer;

  if (!success)
    {
      pdelete(pGraph);
      return NULL;
    }

  if (pGraph)
    pGraph->guessGraphRoot();

  return pGraph;
}

// static
void CRDFParser::TripleHandler(void * pGraph, const raptor_statement * pTriple)
{
  // We need to create a CRDFSubject, Predicate, and CRDFObject
  CRDFSubject Subject;
  std::string Predicate;
  CRDFObject Object;
  CRDFLiteral Literal;

  switch (pTriple->subject_type)
    {
      case RAPTOR_IDENTIFIER_TYPE_RESOURCE:
        Subject.setType(CRDFSubject::RESOURCE);
        Subject.setResource((char *) raptor_uri_as_string((raptor_uri *) pTriple->subject),
                            CRaptorInit::isLocalURI((raptor_uri *) pTriple->subject));
        break;

      case RAPTOR_IDENTIFIER_TYPE_ANONYMOUS:
        Subject.setType(CRDFSubject::BLANK_NODE);
        Subject.setBlankNodeId((char *) pTriple->subject);
        break;

      default:
        fatalError();
    }

  switch (pTriple->predicate_type)
    {
      case RAPTOR_IDENTIFIER_TYPE_RESOURCE:
        Predicate = (char *) raptor_uri_as_string((raptor_uri *) pTriple->predicate);
        break;

      default:
        fatalError();
    }

  switch (pTriple->object_type)
    {
      case RAPTOR_IDENTIFIER_TYPE_ORDINAL:
      case RAPTOR_IDENTIFIER_TYPE_RESOURCE:
        Object.setType(CRDFObject::RESOURCE);
        Object.setResource((char *) raptor_uri_as_string((raptor_uri *) pTriple->object),
                           CRaptorInit::isLocalURI((raptor_uri *) pTriple->object));
        break;

      case RAPTOR_IDENTIFIER_TYPE_ANONYMOUS:
        Object.setType(CRDFObject::BLANK_NODE);
        Object.setBlankNodeId((char *) pTriple->object);
        break;

      case RAPTOR_IDENTIFIER_TYPE_LITERAL:
        Object.setType(CRDFObject::LITERAL);

        if (pTriple->object_literal_datatype != NULL)
          {
            Literal.setType(CRDFLiteral::TYPED);
            Literal.setDataType((const char *) raptor_uri_as_string(pTriple->object_literal_datatype));
          }
        else
          {
            Literal.setType(CRDFLiteral::PLAIN);

            if (pTriple->object_literal_language != NULL)
              Literal.setLanguage((const char *) pTriple->object_literal_language);
          }

        Literal.setLexicalData((char *) pTriple->object);
        Object.setLiteral(Literal);
        break;

      default:
        fatalError();
    }

  // Add the triplet to the graph
  static_cast<CRDFGraph *>(pGraph)->addTriplet(Subject, Predicate, Object);
}

// static
void CRDFParser::NameSpaceHandler(void * pGraph, raptor_namespace * pNameSpace)
{
  const unsigned char * pURI =
    raptor_uri_as_string(raptor_namespace_get_uri(pNameSpace));
  std::string URI("");

  if (pURI) URI = (const char *) pURI;

  const unsigned char * pPrefix =
    raptor_namespace_get_prefix(pNameSpace);
  std::string Prefix("");

  if (pPrefix) Prefix = (const char *) pPrefix;

  static_cast<CRDFGraph *>(pGraph)->addNameSpace(Prefix, URI);
}

// static
unsigned char * CRDFParser::GenerateIdHandler(void * pGraph,
    raptor_genid_type /* type */,
    unsigned char * existingNodeId)
{
  std::string NodeId;

  if (existingNodeId != NULL)
    NodeId = static_cast<CRDFGraph *>(pGraph)->generatedNodeId((char *) existingNodeId).c_str();
  else
    NodeId = static_cast<CRDFGraph *>(pGraph)->generatedNodeId().c_str();

  return (unsigned char *) strdup(NodeId.c_str());
}

// static
void CRDFParser::FatalErrorHandler(void *, raptor_locator * pLocator, const char * message)
{
  CCopasiMessage(CCopasiMessage::ERROR, MCAnnotation + 1,
                 raptor_locator_line(pLocator),
                 raptor_locator_column(pLocator),
                 message);
}

// static
void CRDFParser::ErrorHandler(void *, raptor_locator * pLocator, const char * message)
{
  CCopasiMessage(CCopasiMessage::ERROR, MCAnnotation + 1,
                 raptor_locator_line(pLocator),
                 raptor_locator_column(pLocator),
                 message);
}

// static
void CRDFParser::WarningHandler(void *, raptor_locator * pLocator, const char * message)
{
  CCopasiMessage(CCopasiMessage::WARNING, MCAnnotation + 1,
                 raptor_locator_line(pLocator),
                 raptor_locator_column(pLocator),
                 message);
}
