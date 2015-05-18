// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CUnitParser.h"

CUnitParserBase::CUnitParserBase():
  mPosition(0),
  mUnit()
{}

CUnitParserBase::~CUnitParserBase()
{}

const std::set< CUnitComponent > & CUnitParserBase::getComponents() const
{return mUnit.getComponents();}

void CUnitParserBase::correctErrorPosition()
{return;}

int CUnitParser::yywrap()
{return 1;}
