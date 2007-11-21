// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFLiteral.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/21 16:15:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

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
