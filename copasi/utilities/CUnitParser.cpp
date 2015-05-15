// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CUnitParser.h"

CUnitParserBase::CUnitParserBase()
{}

CUnitParserBase::~CUnitParserBase()
{
  pdelete(mData.pUnit);
}

const CUnit & CUnitParserBase::getUnit() const
{return *mData.pUnit;}

void CUnitParserBase::correctErrorPosition()
{return;}

int CUnitParser::yywrap()
{return 1;}
