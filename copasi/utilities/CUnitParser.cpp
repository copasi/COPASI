// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "CUnitParser.h"

CUnitParserBase::CUnitParserBase():
  mPosition(0),
  mpUnit(NULL),
  mpCurrentUnitDef(NULL),
  mSymbols(),
  mOldSymbol(),
  mNewSymbol(),
  mReplacedExpression()
{}

CUnitParserBase::~CUnitParserBase()
{pdelete(mpUnit)}

const std::set< CUnitComponent > & CUnitParserBase::getComponents() const
{
  if (mpUnit != NULL)
    {
      return mpUnit->getComponents();
    }

  static std::set< CUnitComponent > Components;
  return Components;
}

const std::set< std::string > & CUnitParserBase::getSymbols() const
{
  return mSymbols;
}

void CUnitParserBase::replaceSymbol(const std::string & oldSymbol, const std::string & newSymbol)
{
  mOldSymbol = oldSymbol;
  mNewSymbol = newSymbol;
}

const std::string & CUnitParserBase::getReplacedExpression() const
{
  return mReplacedExpression;
}

void CUnitParserBase::correctErrorPosition()
{return;}

int CUnitParser::yywrap()
{return 1;}
