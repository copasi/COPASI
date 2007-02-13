// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLUtils.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/13 16:58:53 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include "copasi.h"

//#include "mathematics.h"

//#include "sbml/SBMLReader.h"
//#include "sbml/SBMLDocument.h"
#include "sbml/Compartment.h"
#include "sbml/Species.h"
#include "sbml/SpeciesReference.h"
#include "sbml/ModifierSpeciesReference.h"
#include "sbml/Reaction.h"
//#include "sbml/KineticLaw.h"
//#include "sbml/math/FormulaFormatter.h"
#include "sbml/Model.h"
//#include "sbml/UnitKind.h"
//#include "sbml/Unit.h"
#include "sbml/Parameter.h"
//#include "sbml/Rule.h"
//#include "sbml/RateRule.h"
//#include "sbml/AssignmentRule.h"
#include "sbml/FunctionDefinition.h"
#include "sbml/Event.h"
//#include "sbml/xml/ParseMessage.h"

#include "SBMLUtils.h"

//static
std::string SBMLUtils::getIdFromSBase(const SBase* pS)
{
  if (!pS) return "";

  std::string id;

  SBMLTypeCode_t type = pS->getTypeCode();
  switch (type)
    {
    case SBML_COMPARTMENT:
      id = getId(dynamic_cast<const Compartment*>(pS));
      break;
    case SBML_EVENT:
      id = getId(dynamic_cast<const Event*>(pS));
      break;
    case SBML_FUNCTION_DEFINITION:
      id = getId(dynamic_cast<const FunctionDefinition*>(pS));
      break;
    case SBML_MODEL:
      id = getId(dynamic_cast<const Model*>(pS));
      break;
    case SBML_PARAMETER:
      id = getId(dynamic_cast<const Parameter*>(pS));
      break;
    case SBML_REACTION:
      id = getId(dynamic_cast<const Reaction*>(pS));
      break;
    case SBML_SPECIES:
      id = getId(dynamic_cast<const Species*>(pS));
      break;
    case SBML_SPECIES_REFERENCE:
    case SBML_MODIFIER_SPECIES_REFERENCE:
      id = "";
      //id = getId(dynamic_cast<const SimpleSpeciesReference*>(pS));
      //the above should work if layout support is compiled into libsbml
      break;

      //case SBML_COMPARTMENT_TYPE:
      //case SBML_SPECIES_TYPE:
    default:
      id = "";
    }

  return id;
}

//static
template<class CType>
std::string SBMLUtils::getId(const CType * pA, C_INT32 level)
{
  if (!pA) return "";

  if (level == 1)
    return pA->getName();
  else
    return pA->getId();
}
