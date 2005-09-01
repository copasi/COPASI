/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqParser.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/01 01:49:50 $
   End CVS Header */

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

const std::vector< std::string > & CChemEqParserBase::getProductNames() const
  {return mProductNames;}

const std::vector< C_FLOAT64 > & CChemEqParserBase::getProductMulitplicities() const
  {return mProductMult;}

const std::vector< std::string > & CChemEqParserBase::getModifierNames() const
  {return mModifierNames;}

const std::vector< C_FLOAT64 > & CChemEqParserBase::getModifierMulitplicities() const
  {return mModifierMult;}

void CChemEqParserBase::correctErrorPosition()
{return;}
