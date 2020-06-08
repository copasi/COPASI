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

#include "copasi/copasi.h"

#include "CRDFLiteral.h"

CRDFLiteral::CRDFLiteral():
  mType(PLAIN),
  mLanguage(""),
  mDataType(""),
  mLexicalData("")
{}

CRDFLiteral::CRDFLiteral(const CRDFLiteral & src):
  mType(src.mType),
  mLanguage(src.mLanguage),
  mDataType(src.mDataType),
  mLexicalData(src.mLexicalData)
{}

CRDFLiteral::~CRDFLiteral()
{}

void CRDFLiteral::setType(const eLiteralType & type)
{mType = type;}

const CRDFLiteral::eLiteralType & CRDFLiteral::getType() const
{return mType;}

void CRDFLiteral::setLanguage(const std::string & language)
{mLanguage = language;}

const std::string & CRDFLiteral::getLanguage() const
{return mLanguage;}

void CRDFLiteral::setDataType(const std::string & dataType)
{mDataType = dataType;}

const std::string & CRDFLiteral::getDataType() const
{return mDataType;}

void CRDFLiteral::setLexicalData(const std::string & lexicalData)
{mLexicalData = lexicalData;}

const std::string & CRDFLiteral::getLexicalData() const
{return mLexicalData;}

std::ostream & operator << (std::ostream & os, const CRDFLiteral & literal)
{
  os << literal.getLexicalData();
  return os;
}
