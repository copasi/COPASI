// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/incompatibilities.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/03/16 18:57:03 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef INCOMPATIBILITES_H__
#define INCOMPATIBILITES_H__

const INCOMPATIBILITY Incompatibilities[] =
{
  {
    0, 0, 0, SBMLIncompatibility::UNDEFINED,
    "",
    ""
  },
  {
    1, 0, 0, SBMLIncompatibility::ERROR,
    "SBML Incompatibility (1): Object that refers to the \"%s\" of %s \"%s\" has been referenced in a mathematical expression that can not be expressed in SBML.",
    "Mathematical Expressions in SBML files can only reference the transient values of compartments, species, global parameters and reaction fluxes. In COPASI references to other objects, e.g. the initial value of a species, are also allowed and these references can not be expressed in an SBML file."
  },
  {
    2, 0, 0,
    SBMLIncompatibility::ERROR, "SBML Incompatibility (2): Call to function \"%s\" used in mathematical expression for %s which can not be exported to SBML.",
    "Some functions that can be used in mathematical expressions in COPASI models do not have equivalents in MathML or the subset of MathML used by SBML and there is not easy way to convert the function call to something that is SBML compatible. The random distribution functions available in COPASI are an example for this."
  },
  {
    3, 0, 0, SBMLIncompatibility::WARNING,
    "SBMLIncompatibility (3): Species \"%s\" is defined via an ODE Rule and it is located in compartment \"%s\" which has a variable volume.",
    "The interpretation of ODE rules for metabolites in compartments with variable volume is slightly different between COPASI and SBML. Those rules can be exported, but another Simulation programm will likely come up with different results."
  },
  {
    4, 2, 1, SBMLIncompatibility::ERROR,
    "SBMLIncompatibility (4): Rule found for %s \"%s\".",
    "Rules were introduced to SBML Level 2 Version 1. Prior versions of SBML do not support this feature and therefor models using rules can not be fully exported to SBML Level 1"
  },
  {
    5, 2, 2, SBMLIncompatibility::ERROR,
    "SBMLIncompatibility (5): InitialAssignment found for %s \"%s\".",
    "InitialAssignments were introduced to SBML Level 2 Version 2. Prior versions of SBML do not support this feature and therefor models using rules can not be exported to SBML Level 1 or SBML Level 2 Version 1."
  },
  {
    6, 0, 0, SBMLIncompatibility::ERROR,
    "SBMLIncompatibility (6): SBML Level %d Version %d is not supported.",
    "COPASI only supports export to SBML Level 1 Version 2, SBML Level 2 Version 1 and SBML Level 2 Version 3."
  },
  {
    7, 2, 1, SBMLIncompatibility::ERROR,
    "SBMLIncompatibility (7): One or more events found.",
    "Events were introduced to SBML Level 2 Version 1. Prior versions of SBML do not support this feature and therefore models using events can not be fully exported to SBML Level 1"
  },
  {
    8, 2, 1, SBMLIncompatibility::ERROR,
    "SBMLIncompatibility (8): Piecewise function definition found in %s with name \"%s\".",
    "Piecewise function definitions were introduced in SBML Level 2 Version 1. Expressions using them can not be exported to SBML Level 1."
  },
  {
    9, 0, 0, SBMLIncompatibility::ERROR,
    "SBMLIncompatibility (9): Assignment to object called \"%s\" found in %s, which is not a compartment, species or global parameter.",
    "Since SBML only allows assignments (rules and events) to compartments, species and global parameters, the assignment can not be exported to SBML."
  },
  {
    10, 0, 0, SBMLIncompatibility::ERROR,
    "SBML Incompatibility (10): Object that refers the \"%s\" of %s \"%s\" has been referenced in a mathematical expression. This is only allowed for SBML Level 2 Version 2 or above.",
    "Mathematical Expressions in SBML Level 1 or Level 2 Version 1 files can only reference the transient values of compartments, species and global parameters. Referencing reaction fluxes is only supported for SBML Level 2 Version 2 or newer."
  },
  {
    11, 2, 3, SBMLIncompatibility::WARNING,
    "SBML Incompatibility (11): Warning. The spatialSizeUnits attribute needs to be removed from the following species: %s",
    "SBML Version before L2V3 allowed the user to set the spatialSizeUnits attribute on a species. When converting such a model to SBML L2V3 or higher, the attribute has to be removed. If the units given in the attribute are the same as the ones given for the compartment of the species, the model does not change when the attribute is removed. In some cases COPASI thinks that the units given in the attribute are different from the units of the compartment. In these cases you will see this warning."
  },
  // This must be the last element of the message list! Do not delete!
  {9999, 0, 0, SBMLIncompatibility::UNDEFINED, NULL, NULL}
};

#endif // INCOMPATIBILITES_H__
