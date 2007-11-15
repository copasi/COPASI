// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/incompatibilities.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/11/15 14:57:13 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef INCOMPATIBILITES_H__
#define INCOMPATIBILITES_H__

const INCOMPATIBILITY Incompatibilities[] =
  {
    {0, 0, 0, SBMLIncompatibility::UNDEFINED, "", ""},
    {1, 0, 0, SBMLIncompatibility::ERROR, "SBML Incompatibility (1): Object that refers to the \"%s\" of %s \"%s\" has been referenced in a mathematical expression that can not be expressed in SBML.", "Mathematical Expressions in SBML files can only reference the transient values of compartments, species, global parameters and reaction fluxes. In COPASI references to other objects, e.g. the initial value of a species, are also allowed and these references can not be expressed in an SBML file."},
    {2, 0, 0, SBMLIncompatibility::ERROR, "SBML Incompatibility (2): Call to function \"%s\" used in mathematical expression for %s \"%s\" which can not be exported to SBML."
     , "Some functions that can be used in mathematical expressions in COPASI models do not have equivalents in MathML or the subset of MathML used by SBML and there is not easy way to convert the function call to something that is SBML compatible. The random distribution functions available in COPASI are an example for this."},
    {3, 0, 0, SBMLIncompatibility::WARNING, "SBMLIncompatibility (3): Species \"%s\" is defined via an ODE Rule and it is located in compartment \"%s\" which has a variable volume."
     , "The interpretation of ODE rules for metabolites in compartments with variable volume is slightly different between COPASI and SBML. Those rules can be exported, but another Simulation programm will likely come up with different results."},
    {4, 2, 1, SBMLIncompatibility::ERROR, "SBMLIncompatibility (4): Rule found for %s \"%s\".", "Rules were introduced to SBML Level 2 Version 1. Prior versions of SBML do not support this feature and therefor models using rules can not be exported to SBML Level 1"},
    {5, 2, 2, SBMLIncompatibility::ERROR, "SBMLIncompatibility (5): InitialAssignment found for %s \"%s\".", "InitialAssignments were introduced to SBML Level 2 Version 2. Prior versions of SBML do not support this feature and therefor models using rules can not be exported to SBML Level 1 or SBML Level 2 Version 1."},
    // This must be the last element of the message list! Do not delete!
    {9999, 0, 0, SBMLIncompatibility::UNDEFINED, NULL, NULL}
  };

#endif // INCOMPATIBILITES_H__
