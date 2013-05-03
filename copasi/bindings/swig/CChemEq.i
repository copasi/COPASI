// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 





%{

#include "model/CChemEq.h"

%}

%ignore CChemEq::getSmallestCompartment() const; // this has not been implemented
%ignore CChemEq::reverse(); // this has not been implemented
%catches(CCopasiException) CChemEq::getLargestCompartment() const;

%include "model/CChemEq.h"


%extend CChemEq
{
    CChemEqElement* getSubstrate(unsigned C_INT32 index)
    {
	try
	{
      return self->getSubstrates()[index];
	}
	catch(...)
	{
	return NULL;
	}
    }

    CChemEqElement* getProduct(unsigned C_INT32 index)
    {
	try
	{
      return self->getProducts()[index];
	  }
	catch(...)
	{
	return NULL;
	}
    }

    CChemEqElement* getModifier(unsigned C_INT32 index)
    {
	try
	{
      return self->getModifiers()[index];
	  }
	catch(...)
	{
	return NULL;
	}
    }

    CChemEqElement const* getBalance(unsigned C_INT32 index)
    {
	try
	{
      return self->getBalances()[index];
	  }
	catch(...)
	{
	return NULL;
	}
    }
}




