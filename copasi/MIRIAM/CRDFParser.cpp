// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFParser.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/21 18:37:22 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <sstream>

#include "copasi.h"

#include "CRDFParser.h"
#include "CRDFGraph.h"
#include "CRDFSubject.h"
#include "CRDFObject.h"
#include "CRDFLiteral.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiMessage.h"

// static
bool CRDFParser::Initialized = false;

// static
CRDFGraph * CRDFParser::graphFromXml(const std::string & xml)
{
  CRDFParser Parser;

  std::istringstream XML;
  XML.str(xml);

  return Parser.parse(XML);
}

CRDFParser::CRDFParser() :
    mpParser(NULL),
    mpGraph(NULL)
{
  if (!Initialized)
    {
      raptor_init();
      Initialized = true;
    }

  mpParser = raptor_new_parser("rdfxml");

  raptor_set_statement_handler(mpParser, this, &CRDFParser::TripleHandler);
}

CRDFParser::~CRDFParser()
{
  if (mpParser) raptor_free_parser(mpParser);
}

CRDFGraph * CRDFParser::parse(std::istream & stream)
{
  bool success = true;
  bool done = false;

  stream.imbue(std::locale::classic());
  stream.precision(16);

  std::string URI = "file:///home/shoops.local/eclipse/COPASI-gcc3-32/gps/TestKinetics/MassAction.cps";
  raptor_uri * pURI = raptor_new_uri((unsigned char *) URI.c_str());

  if (raptor_start_parse(mpParser, pURI))
    fatalError();

  // Create the new graph
  mpGraph = new CRDFGraph;

  unsigned C_INT32 BUFFER_SIZE = 0xfffe;
  char * pBuffer = new char[BUFFER_SIZE + 1];

  while (!done)
    {
      stream.get(pBuffer, BUFFER_SIZE, 0);

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

          fatalError();
        }
    }

  delete [] pBuffer;

  if (!success)
    pdelete(mpGraph);

  CRDFGraph * pGraph = mpGraph;
  mpGraph = NULL;

  return pGraph;
}

// static
void CRDFParser::TripleHandler(void * pRdfParser, const raptor_statement * pTriple)
{static_cast< CRDFParser *>(pRdfParser)->TripleHandler(pTriple);}

void CRDFParser::TripleHandler(const raptor_statement * pTriple)
{
  raptor_print_statement(pTriple, stdout);
  fprintf(stdout, "\n");
  fflush(stdout);

  // We need to create a CRDFSubject, Predicate, and CRDFObject
  CRDFSubject Subject;
  std::string Predicate;
  CRDFObject Object;
  CRDFLiteral Literal;

  switch (pTriple->subject_type)
    {
    case RAPTOR_IDENTIFIER_TYPE_RESOURCE:
      Subject.setType(CRDFSubject::RESOURCE);
      Subject.setResource((char *) pTriple->subject);
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
      Predicate = (char *) pTriple->predicate;
      break;

    default:
      fatalError();
    }

  switch (pTriple->object_type)
    {
    case RAPTOR_IDENTIFIER_TYPE_RESOURCE:
      Object.setType(CRDFObject::RESOURCE);
      Object.setResource((char *) pTriple->object);
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
          Literal.setDataType((char *) pTriple->object_literal_datatype);
        }
      else
        {
          Literal.setType(CRDFLiteral::PLAIN);
          if (pTriple->object_literal_language != NULL)
            Literal.setLanguage((char *) pTriple->object_literal_language);
        }

      Literal.setLexicalData((char *) pTriple->object);
      Object.setLiteral(Literal);
      break;

    default:
      fatalError();
    }

  // Add the triplet to the graph
  mpGraph->addTriplet(Subject, Predicate, Object);
}
