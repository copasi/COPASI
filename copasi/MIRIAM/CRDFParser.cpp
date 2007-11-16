// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFParser.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/16 20:52:36 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CRDFParser.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiMessage.h"

// static
bool CRDFParser::Initialized = false;

CRDFParser::CRDFParser() :
    mpParser(NULL)
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

bool CRDFParser::parse(std::istream & stream)
{
  bool success = true;
  bool done = false;

  stream.imbue(std::locale::classic());
  stream.precision(16);

  std::string URI = "file:///home/shoops.local/eclipse/COPASI-gcc3-32/gps/TestKinetics/MassAction.cps";
  raptor_uri * pURI = raptor_new_uri((unsigned char *) URI.c_str());

  if (raptor_start_parse(mpParser, pURI))
    fatalError();

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

  return success;
}

// static
void CRDFParser::TripleHandler(void * pRdfParser, const raptor_statement * pTriple)
{static_cast< CRDFParser *>(pRdfParser)->TripleHandler(pTriple);}

// virtual
void CRDFParser::TripleHandler(const raptor_statement * pTriple)
{
  raptor_print_statement(pTriple, stdout);
  fprintf(stdout, "\n");
  fflush(stdout);
}
