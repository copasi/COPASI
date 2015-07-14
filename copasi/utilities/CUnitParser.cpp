// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CUnitParser.h"

CUnitParserBase::CUnitParserBase():
  mPosition(0),
  mpUnit(NULL),
  mAvogadro(CUnit::Avogadro),
  mSymbols()
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

void CUnitParserBase::setAvogadro(const C_FLOAT64 & avogadro)
{
  mAvogadro = avogadro;
}

void CUnitParserBase::correctErrorPosition()
{return;}

int CUnitParser::yywrap()
{return 1;}
