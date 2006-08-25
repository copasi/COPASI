/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqParser.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/25 18:13:23 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CChemEqParser.h"

CChemEqParserBase::CChemEqParserBase()
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
