// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CChemEqParser.h"

CChemEqParserBase::CChemEqParserBase()
  : mpData(NULL)
{}

CChemEqParserBase::~CChemEqParserBase()
{}

const bool & CChemEqParserBase::isReversible() const
{return mReversibility;}

const std::vector< std::string > & CChemEqParserBase::getSubstrateNames() const
{return mSubstrateNames;}

const std::vector< C_FLOAT64 > & CChemEqParserBase::getSubstrateMulitplicities() const
{return mSubstrateMult;}

const std::vector< std::string > & CChemEqParserBase::getSubstrateCompartments() const
{return mSubstrateCompartments;}

const std::vector< std::string > & CChemEqParserBase::getProductNames() const
{return mProductNames;}

const std::vector< C_FLOAT64 > & CChemEqParserBase::getProductMulitplicities() const
{return mProductMult;}

const std::vector< std::string > & CChemEqParserBase::getProductCompartments() const
{return mProductCompartments;}

const std::vector< std::string > & CChemEqParserBase::getModifierNames() const
{return mModifierNames;}

const std::vector< C_FLOAT64 > & CChemEqParserBase::getModifierMulitplicities() const
{return mModifierMult;}

const std::vector< std::string > & CChemEqParserBase::getModifierCompartments() const
{return mModifierCompartments;}

void CChemEqParserBase::correctErrorPosition()
{return;}

int CChemEqParser::yywrap()
{return 1;}
