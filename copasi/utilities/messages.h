// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_MESSAGES_H
#define COPASI_MESSAGES_H

const MESSAGES Messages[] =
{
  // MCopasiBase
  {MCopasiBase + 1, "CVector (1): Memory allocation failed for '%d' bytes."},

  // CReadConfig
  {MCReadConfig + 1, "CReadConfig (1): Variable '%s' not found in '%s(%d)'."},
  {MCReadConfig + 2, "CReadConfig (2): Cannot open file '%s'."},
  {MCReadConfig + 3, "CReadConfig (3): Cannot read file '%s'."},
  {MCReadConfig + 4, "CReadConfig (4): Cannot close file '%s'."},
  {MCReadConfig + 5, "CReadConfig (5): Invalid type '%s' for  Variable '%s'."},

  // CKinFunction
  {
    MCKinFunction + 1, "CKinFunction (1): Cannot find identifier '%s'"
    " in function '%s'."
  },
  {MCKinFunction + 2, "CKinFunction (2): Missing operand in function '%s'."},

  // CRange
  {MCRange + 1, "CRange (1): Invalid range ('%d', '%d')."},

  // CDataVector
  {MCDataVector + 1, "CDataVector (1): Object '%s' not found."},
  {MCDataVector + 2, "CDataVector (2): Object '%s' already exists."},
  {MCDataVector + 3, "CDataVector (3): Index '%d' out of range (0, '%d')."},

  // CFunctionParameters
  {
    MCFunctionParameters + 1, "CFunctionParameters (1): The usage '%s' "
    "is not unique for a vector type parameter ('%d')."
  },
  {
    MCFunctionParameters + 2, "CFunctionParameters (2): No parameter with "
    "usage '%s' with index >= '%ld'."
  },

  // CMassAction
  {
    MCMassAction + 1, "CMassAction (1): The function Mass Action reversibility "
    "must be either TRUE or FALSE."
  },

  // CCopasiMethod
  {
    MCCopasiMethod + 1, "CCopasiMethod (1): No parameter list "
    "found for name '%s' and type '%s'."
  },
  {MCCopasiMethod + 2, "CCopasiMethod (2): Problem is not set."},
  {MCCopasiMethod + 3, "CCopasiMethod (3): Model is not set in problem."},
  {MCCopasiMethod + 4, "CCopasiMethod (4): Event exists. Current task '%s' is not suitable with the event."},

  // CReaction
  {MCReaction + 1, "CReaction (1): Function '%s' not found."},
  {MCReaction + 2, "CReaction (2): In Reaction '%s' the compartment could not be guessed."},
  {MCReaction + 3, "CReaction (3): Reaction '%s' has no substrates and no products."},
  {MCReaction + 4, "CReaction (4): Only Species, Compartments or Parameter object nodes are allowed in kinetic functions."},
  {MCReaction + 5, "CReaction (5): Nodes of type '%s' are not implemented yet."},
  {MCReaction + 6, "CReaction (6): Nodes of type VARIABLE must not appear in an expression."},
  {MCReaction + 7, "CReaction (7): Species object '%s' is neither substrate, product nor modifier to reaction '%s' but it is used in the kinetic law."},
  {MCReaction + 8, "CReaction (8): Could not find variable with name '%s'."},
  {MCReaction + 9, "CReaction (9): Could not find object for key '%s'."},
  {MCReaction + 10, "CReaction (10): Parameter '%s' is a vector."},
  {MCReaction + 11, "CReaction (11): Reaction '%s' refers to unusable Function '%s'."},
  {
    MCReaction + 12, "CReaction (12): The reversible Reaction '%s' could not be split into two irreversible "
    "Reactions due to the Structure of the Kinetic Law '%s'."
  },

  // CChemEq
  {MCChemEq + 1, "CChemEq (1): No Substrates and no Products."},
  {MCChemEq + 2, "CChemEq (2): Substrates in different Compartments."},
  {MCChemEq + 3, "CChemEq (3): No Substrates and Products are in different compartments."},

  // CMethodParameter
  {
    MCParameter + 1, "CCopasiParameter (1): Invalid value '%f' for '%s' "
    "which is of type '%s'."
  },
  {MCParameter + 2, "CCopasiParameter (2): Elevation failed, since no parameter is provided."},
  {MCParameter + 3, "CCopasiParameter (3): Elevation failed, since the parameter is not of the required source type."},
  {MCParameter + 4, "CCopasiParameter (4): Elevation failed, since elevation of children failed."},
  {MCParameter + 5, "CCopasiParameter (5): Elevation failed, since the parameter is not member of this group."},

  // CTrajectoryMethod
  {
    MCTrajectoryMethod + 1, "CTrajectoryMethod (1): Hybrid simulation not "
    "applicable, since the stoichiometry contains a non-integer."
  },
  {
    MCTrajectoryMethod + 2, "CTrajectoryMethod (2): Hybrid simulation not "
    "applicable, since reversible reactions exists."
  },
  {
    MCTrajectoryMethod + 3, "CTrajectoryMethod (3): Hybrid simulation not "
    "applicable, since more than one compartment is involved."
  },
  {MCTrajectoryMethod + 4, "CTrajectoryMethod (4): Lower Limit '%.2f' is greater than Upper Limit '%.2f'."},
  {
    MCTrajectoryMethod + 6, "CTrajectoryMethod (6): Deterministic integration failed:"
    "\n%s \n\nPlease see result for indications of numerical instability."
  },
  {MCTrajectoryMethod + 7, "CTrajectoryMethod (7): Problem is not set."},
  {MCTrajectoryMethod + 8, "CTrajectoryMethod (8): Problem is not a trajectory problem."},
  {MCTrajectoryMethod + 9, "CTrajectoryMethod (9): Negative time steps not possible with stochastic simulation."},
  {MCTrajectoryMethod + 10, "CTrajectoryMethod (10): The tau-Leap Method encountered numerical problems.\nYou can try to reduce the epsilon value."},
  {MCTrajectoryMethod + 11, "CTrajectoryMethod (11): Invalid tau-value ('%.2f'). Tau must have a positive value."},
  {MCTrajectoryMethod + 12, "CTrajectoryMethod (12): Internal step limit exceeded."},
  {MCTrajectoryMethod + 13, "CTrajectoryMethod (13): Runge Kutta Step size must be positive in hybrid method."},
  {MCTrajectoryMethod + 14, "CTrajectoryMethod (14): Use Random Seed should be 0 or 1 since it is a boolean parameter."},
  {MCTrajectoryMethod + 15, "CTrajectoryMethod (15): Max Internal Steps needs to be positive."},
  {MCTrajectoryMethod + 16, "CTrajectoryMethod (16): Numerical Error encountered."},
  {MCTrajectoryMethod + 17, "CTrajectoryMethod (17): At least one reaction is necessary to perform stochastic simulation."},
  {MCTrajectoryMethod + 18, "CTrajectoryMethod (18): The model contains a global quantity with an ODE rule.\nStochastic simulation is not possible."},
  {MCTrajectoryMethod + 19, "CTrajectoryMethod (19): The model contains a global quantity with an assignment rule. \nThe value of the quantity is used in the model. \nStochastic simulation of such models is not possible with this version of COPASI."}, //obsolete
  {MCTrajectoryMethod + 20, "CTrajectoryMethod (20): The model contains a species with an ODE rule.\nStochastic simulation is not possible."},
  {MCTrajectoryMethod + 21, "CTrajectoryMethod (21): The model contains a compartment with an ODE rule.\nStochastic simulation is not possible."},
  {MCTrajectoryMethod + 23, "CTrajectoryMethod (23): The model contains events. Simulation with '%s' is not possible with this version of COPASI."},
  {MCTrajectoryMethod + 24, "CTrajectoryMethod (24): The model contains a species with an assignment. Hybrid simulation is not possible with this version of COPASI."},
  {MCTrajectoryMethod + 25, "CTrajectoryMethod (25): Invalid state at time '%f'."},
  {MCTrajectoryMethod + 26, "CTrajectoryMethod (26): A tau-Leap step encountered numerical problems.\nPlease check whether some particle numbers are large."},
  {MCTrajectoryMethod + 27, "CTrajectoryMethod (27): Numerical problem: a propensity is NaN."},
  {MCTrajectoryMethod + 28, "CTrajectoryMethod (28): The model contains an ODE rule.\nStochastic simulation is not possible."},
  {MCTrajectoryMethod + 29, "CTrajectoryMethod (29): NMAX limit reached during Radau5 integration."},
  {MCTrajectoryMethod + 30, "CTrajectoryMethod (30): Step size became too small during Radau5 integration."},
  {MCTrajectoryMethod + 31, "CTrajectoryMethod (31): The model contains events. Radau5 integration is not possible with this version of COPASI."},
  {MCTrajectoryMethod + 32, "CTrajectoryMethod (32): No values provided for output."},

  // XML Package
  {MCXML + 1, "XML (1): Required attribute '%s' not found (line: '%d')."},
  {MCXML + 2, "XML (2): XML error (line: '%d', column: '%d'): '%s'."},
  {MCXML + 3, "XML (3): Unknown element '%s' encountered at line '%d'."},
  {MCXML + 4, "XML (4): Unknown parameter '%s' encountered at line '%d'."},
  {MCXML + 5, "XML (5): Unknown task type '%s' encountered at line '%d'."},
  {MCXML + 6, "XML (6): Invalid function '%s' encountered at line '%d'."},
  {MCXML + 7, "XML (7): Unknown function '%s' in reaction '%s' encountered at line '%d'."},
  {
    MCXML + 8, "XML (8): Unknown variable '%s' in function '%s' encountered at line '%d'. "
    "A possible reason is that the variable is a reserved string within the function description."
  },
  {
    MCXML + 9, "XML (9): The content is created with a newer version '%s' of COPASI.\n"
    "This means it might include features your version of COPASI does not support.\n"
    "To assure full compatibility please download the newest version at http://www.copasi.org."
  },
  {MCXML + 10, "XML (10): Invalid element '<%s>' expecting '<%s>' encountered at line '%d'."},
  {MCXML + 11, "XML (11): Invalid closing element '</%s>' expecting '</%s>' encountered at line '%d'."},
  {MCXML + 12, "XML (12): Order '%d' out of range for variable '%s' in function '%s' encountered at line '%d'. "},
  {MCXML + 13, "XML (13): Unrecognized content format."},
  {
    MCXML + 14, "XML (14): Local reaction parameters may no longer be used in any expression in the model. "
    " The following automatic corrections have been applied:\n%s"
    " Please note: Tasks, reports, and plots may have been affected by these changes and may no longer work as expected."
  },
  {
    MCXML + 15, "XML (15): Multiple events with order '%d' encountered. The problem has been fixed."
    "Please verify that the automatic correction represents the intended behavior."
  },
  {MCXML + 16, "XML (16): Unknown parameter '%s' with type '%s' encountered at line '%d'."},
  {MCXML + 17, "XML (17): Invalid initial state specification encountered at line '%d'."},
  {MCXML + 18, "XML (18): Unknown method '%s' encountered at line '%d' selecting default '%s'."},
  {MCXML + 19, "XML (19): %s with key '%s' references a model element that no longer exists. The reference has been deleted and the element might not be displayed correctly in the layout."},
  {MCXML + 20, "XML (20): Could not determine text for TextGlyph with key '%s'. \"unset\" will be displayed instead."},
  {MCXML + 21, "XML (21): One or more layout elements reference model objects that no longer exists. These references have been deleted."},
  {MCXML + 22, "XML (22): Duplicate XML Id '%s' encountered in line '%d'."},
  {MCXML + 23, "XML (23): Duplicate Unit Definition '%s' encountered in line '%d'."},
  {MCXML + 24, "XML (24): At least one of the following elements '%s' is missing in line '%d'."},

  // CCopasiMessage
  {MCCopasiMessage + 1, "Message (1): No more messages."},

  // Configuration
  {
    MCConfiguration + 1, "Configuration (1): COPASI directory is not set. Some features might not be working correctly.\n"
    "Please set the environment variable COPASIDIR or use the "
    "command-line options \"-c COPASIDIR\" or \"--copasidir COPASIDIR\" "
    "to point to the COPASI installation directory."
  },
  {MCConfiguration + 2, "Configuration (2): Configuration file '%s' found but is not readable."},

  // Optimization
  {MCOptimization + 1, "Optimization (1): Object '%s' not found."},
  {MCOptimization + 2, "Optimization (2): Lower Bound '%s' not found."},
  {MCOptimization + 3, "Optimization (3): Upper Bound '%s' not found."},
  {MCOptimization + 4, "Optimization (4): Invalid Interval ('%f', '%f') specified for Object: '%s'."},
  {MCOptimization + 5, "Optimization (5): Invalid Objective Functions."},
  {MCOptimization + 6, "Optimization (6): No adjustable Parameters specified."},
  {MCOptimization + 7, "Optimization (7): No Task Type specified."},
  {MCOptimization + 8, "Optimization (8): '%d' Function Evaluations out of '%d' failed."},
  {MCOptimization + 9, "Optimization (9): '%d' Constraint Checks out of '%d' failed."},
  {MCOptimization + 10, "Optimization (10): Object '%s' is not an initial value."},
  {MCOptimization + 11, "Optimization (11): Object '%s' lower bound '%s' is not an initial value."},
  {MCOptimization + 12, "Optimization (12): Object '%s' upper bound '%s' is not an initial value."},
  {MCOptimization + 13, "Optimization (13): Failed to adjust start values to create valid intervals."},

  // SBML
  {MCSBML + 1, "SBML (1): SBML currently does not support initial times different from 0. This information will be lost in the exported file."},
  {MCSBML + 2, "SBML (2): The SBML document contains no model."},
  {MCSBML + 3, "SBML (3): The SBML document contains algebraic rules that were ignored. Entities determined by those rules are probably undetermined now."},
  {MCSBML + 4, "SBML (4): The SBML document contains events that were ignored."},
  {MCSBML + 5, "SBML (5): Compartment %s referenced by species %s does not exist."},
  {MCSBML + 6, "SBML (6): Annotations in SBase element of SBML Level 1 files, this is invalid and has been ignored."},
  {MCSBML + 7, "SBML (7): No initial value or initial assignment set for compartment \"%s\"."},
  {MCSBML + 8, "SBML (8): Expression tree for kinetic law of reaction '%s' could not be converted."},
  {MCSBML + 9, "SBML (9): Could not set function from expression in reaction '%s'."},
  {MCSBML + 10, "SBML (10): COPASI does not support stoichiometric expressions."},
  {MCSBML + 11, "SBML (11): Function '%s' does not start with a Lambda element."},
  {MCSBML + 12, "SBML (12): Function '%s' contains invalid parameter list."},
  {MCSBML + 13, "SBML (13): Could not read function definition for function '%s'."},
  {MCSBML + 14, "SBML (14): Could not import function with id '%s'."},
  {MCSBML + 15, "SBML (15): Could not find function with id '%s'."},
  {MCSBML + 16, "SBML (16): Loop found in function. That means a function calls itself either directly or indirectly."},
  {MCSBML + 17, "SBML (17): One or more single compartment reactions found where the kinetic law does not include a multiplication by the volume:\n%s"},
  {MCSBML + 18, "SBML (18): Support for 'hasOnlySubstanceUnit' flag on species is experimental. Species in compartments of dimension 0 are also considered to have this flag set."},
  {MCSBML + 19, "SBML (19): Spatial size units on species \"%s\" is not the same as the volume unit in the model and has been ignored."},
  {MCSBML + 20, "SBML (20): Setting an initial concentration on species %s which has the 'hasOnlySubstanceUnits' flag set is not allowed."},
  {MCSBML + 21, "SBML (21): Setting an initial concentration on species '%s' which is in a compartment with spatial dimensions 0 is not allowed."},
  {MCSBML + 22, "SBML (22): Current versions of COPASI only supports three dimensional compartments. '%s' will be considered to be three dimensional."},
  {MCSBML + 23, "SBML (23): Compartment '%s' has spatial dimensions of 0, setting dimensions to 3.\nConsidering all species in that compartment to have \"hasOnlySubstanceUnits\" flag set."}, // OBSOLETE
  {MCSBML + 24, "SBML (24): Units for some compartments were ignored. Units might be displayed incorrectly.\nCompartments: %s"},
  {MCSBML + 25, "SBML (25): Units for some species were ignored. Units might be displayed incorrectly.\nSpecies: %s"},
  {MCSBML + 26, "SBML (26): Units for some parameters were ignored. Units might be displayed incorrectly.\nParameters: %s"},
  {MCSBML + 27, "SBML (27): Error in kinetic law for reaction '%s'."},
  {MCSBML + 28, "SBML (28): Error in function definition with id '%s'."},
  {MCSBML + 29, "SBML (29): Unable to handle reactions with the 'fast' flag set.\nThe flag has been set to false in the following reactions:\n%s"},
  {MCSBML + 30, "SBML (30): Can't handle units of type item with scale set to 1.\n If this file was created with COPASI RC1 or older please see the COPASI FAQ."},
  {MCSBML + 31, "SBML (31): %s are currently only supported for global parameters."}, // OBSOLETE
  {MCSBML + 32, "SBML (32): Error in %s variable id '%s' does not specify a compartment, species or global parameter."},
  {MCSBML + 33, "SBML (33): Error: %s is not allowed for local parameter '%s'."},
  {MCSBML + 34, "SBML (34): Error: %s is not allowed for local constant '%s' identified by id '%s'."},
  {MCSBML + 35, "SBML (35): Error: Only one AssignmentRule or RateRule is allowed for id '%s'."},
  {MCSBML + 36, "SBML (36): COPASI does not support time delays. Calculations on this model will most likely lead to unusable results."},
  {MCSBML + 37, "SBML (37): The id '%s' is used in the expression of a rule, although it is later defined by a rule itself."},
  {MCSBML + 38, "SBML (38): Only references to compartment volumes, species concentrations, global parameter values or the time are allowed in SBML rule expressions."},
  {MCSBML + 39, "SBML (39): Object with id \"%s\" referenced in kinetic law, but no object with that id found in model."},
  {MCSBML + 40, "SBML (40): LIBSBML %s %d at line %d column %d: %s."},
  {MCSBML + 41, "SBML (41): No initial value set for species \"%s\". Setting initial concentration to 1.0."},
  {MCSBML + 42, "SBML (42): No initial value set for local parameter \"%s\"."},
  {MCSBML + 43, "SBML (43): No initial value set for global parameter \"%s\". Setting initial value to 1.0"},
  {MCSBML + 44, "SBML (44): Substance unit in kinetic law for some reactions were ignored. Units might be displayed incorrectly.\nReactions: %s"},
  {MCSBML + 45, "SBML (45): Compartment \"%s\" does not set the initial volume. Volume has been set to 1.0."},
  {MCSBML + 46, "SBML (46): COPASI has changed the following function definitions to take the time as an additional argument instead of the function being directly or indirectly dependent on time:\n \"%s\" ."},
  {MCSBML + 47, "SBML (47): COPASI found a call to the function \"%s\" which has not been defined."},
  {MCSBML + 48, "SBML (48): Initial assignments ignored because they are not supported yet."}, // OBSOLETE
  {MCSBML + 49, "SBML (49): Constraints ignored because they are not supported yet."},
  {MCSBML + 50, "SBML (50): Could not open file \"%s\"."},
  {MCSBML + 51, "SBML (51): The species \"%s\" is defined by a rate rule and its compartments volume is variable. COPASI will probably interpret this incorrectly."},
  {MCSBML + 52, "SBML (52): The species \"%s\" is defined by a rate expression and its compartments volume is variable. The way COPASI interprets this is differently from the way SBML does."},
  {MCSBML + 53, "SBML (53): The time units of kinetic laws in some reactions were ignored. Units might be displayed incorrectly.\nReactions: %s"},
  {MCSBML + 54, "SBML (54): Error while importing %s unit with id \"%s\"."},
  {MCSBML + 55, "SBML (55): Could not find unit definition for unit with id \"%s\" used in \"%s\" attribute of %s with id \"%s\"."},
  {MCSBML + 56, "SBML (56): There was a problem with the kinetic law in reaction \"%s\". Make sure the math element is not empty."},
  {MCSBML + 57, "SBML (57): %s defined for object with id \"%s\", but the corresponding object could not be found. Ignoring assignment."},
  {MCSBML + 58, "SBML (58): %s for object with id \"%s\" does not set a mathematical expression. Ignoring assignment."},
  {MCSBML + 59, "SBML (59): Error while importing InitialAssignment for object with id \"%s\". Ignoring assignment."},
  {MCSBML + 60, "SBML (60): Error while exporting %s for %s with name \"%s\"."},
  {MCSBML + 61, "SBML (61): Error while expanding function calls in mathematical expression for %s."},
  {MCSBML + 62, "SBML (62): Error while replacing unsupported elements in mathematical expression for %s."},
  {MCSBML + 63, "SBML (63): Initial assignment for %s \"%s\" can not be exported to SBML Level 2 Version 1."},
  {MCSBML + 64, "SBML (64): One or more stoichiometric expressions were evaluated and converted to constants values."},
  {MCSBML + 65, "SBML (65): The stoichiometric expression for a species reference for species \"%s\" in reaction \"%s\" could not be evaluated. The value has therefore been set to 1.0."},
  {MCSBML + 66, "SBML (66): COPASI was not able to import the global %s unit. Unit has been set to %s."},
  {MCSBML + 67, "SBML (67): Metaid \"%s\" is not unique, please check the metaids."},
  {MCSBML + 68, "SBML (68): Id \"%s\" is not unique, please check the ids in your SBML file."},
  {MCSBML + 69, "SBML (69): MIRIAM annotations can't currently be exported to SBML.\nIf you have added new MIRIAM annotations to model elements or changed existing annotations, those changes will not be present in the exported SBML file.\nTo conserve your changes, please consider saving the model as a COPASI file."},
  {MCSBML + 70, "SBML (70): Could not export mathematical expression for %s in %s with name \"%s\"."},
  {MCSBML + 71, "SBML (71): The time units of some events were ignored. Since ids on event are optional, only those events with ids are listed below. Units might be displayed incorrectly.\nEvents: %s"},
  {MCSBML + 72, "SBML (72): Error in event assignment. Event assignments may only assign values to compartments, species or global parameters, object with id \"%s\" is neither compartment, species or global parameter. Ignoring assignment."},
  {MCSBML + 73, "SBML (73): Could not export %s. %s has been ignored."},
  {MCSBML + 74, "SBML (74): Invalid id \"%s\" found in an expression."},
  {MCSBML + 75, "SBML (75): Invalid id RDF/XML found and corrected."},
  {MCSBML + 76, "SBML (76): Unable to resolve dependencies for the following function definitions:\n%s."},
  {MCSBML + 77, "SBML (77): Event \"%s\" is defined to calculate the event assignments after the delay. This can not be expressed in SBML Level %d Version %d. Exporting to this version of SBML will change the semantics of the model."},
  {MCSBML + 78, "SBML (78): All %s units that are used in the file are identical, but they differ from the global default %s unit. Global default %s unit is therefore being used."},
  {MCSBML + 79, "SBML (79): COPASI was not able to handle the %s unit for %s with id \"%s\". The unit has been ignored."},
  {MCSBML + 80, "SBML (80): Reaction \"%s\" referenced in an expression, although the reaction has no kinetic law."},
  {MCSBML + 81, "SBML (81): Reference to reaction with id \"%s\" found in a mathematical expression. This is only valid in SBML Level 2 Version 2 or newer."},
  {MCSBML + 82, "SBML (82): SBML compartment with id \"%s\" has invalid spatial dimensions value."},
  {MCSBML + 83, "SBML (83): SBML species \"%s\" is located in zero dimensional compartment and can not have the spatialDimensionsUnits attribute set."},
  {MCSBML + 84, "SBML (84): The spatialSizeUnit attribute was deleted from some species because the attribute is not compatible with the exported version of SBML. This might have changed the model. Changed species: %s"},
  {MCSBML + 85, "SBML (85): Call to delay function used in function definition \"%s\". COPASI can't import this model."},
  {MCSBML + 86, "SBML (86): COPASI found calls to the delay function in one or more reaction kinetics. These calls have been replaced by a reference to a global parameter which has an expression that corresponds to the original delay call."},
  {MCSBML + 87, "SBML (87): Reactions with references to local kinetic parameters found in delay calls.\nLocal parameters in the following reactions have been converted to global variables:\n%s"},
  {MCSBML + 88, "SBML (88): Reaction with id \"%s\" referenced in kinetic law for reaction with id \"%s\".\nCOPASI can not handle references to reaction fluxes in kinetic laws.\nPlease modify your model to use global parameters which reference the reaction id instead of referencing the reaction id directly."},
  {MCSBML + 89, "SBML (89): Reaction with id \"%s\" has non-integer dimensionality. This is currently not supported by COPASI. COPASI will assume that the compartment is three dimensional."},
  {MCSBML + 90, "SBML (90): Reaction with id \"%s\" has no spatial dimensions set. COPASI will assume that the compartment is three dimensional."},
  {MCSBML + 91, "SBML (91): The default %s unit has not been set in the model. COPASI will use %s as the default %s unit."},
  {MCSBML + 92, "SBML (92): The default extent unit has not been set in the model or differs from the substance default units. COPASI will assume that the extent units are the same as the substance units."},
  {MCSBML + 93, "SBML (93): The model uses units on numbers which COPASI currently can't handle. Please be aware that the display of units in COPASI might therefore be incorrect,"},
  {MCSBML + 94, "SBML (94): %s for species reference found in model. Only initial assignments and assignment rules to species references are currently supported in COPASI. The %s has been ignored. The results produced by this model might therefore not be what you expect."},
  {MCSBML + 95, "SBML (95): The model uses species reference ids in mathematical expressions. COPASI does not support this, and will only evaluate them during import."},
  {MCSBML + 96, "SBML (96): The Model requires one or more packages that are unknown to COPASI, the model is imported but likely incomplete. Those package(s) are: %s "},
  {MCSBML + 97, "SBML (97): COPASI can't handle the initial value on event triggers yet, COPASI will set the initial values of event triggers to \"true\". This may change results for time course simulations."},
  {MCSBML + 98, "SBML (98): COPASI can't handle event priorities yet, COPASI removed all priorities. This may change results for time course simulations."},
  {MCSBML + 99, "SBML (99): COPASI can't handle non-persistent event triggers, the persistent flag on all triggers has been set to true. This may change results of time course simulations."},
  {MCSBML + 100, "SBML (100): Model with conversion factors encountered. In order to calculate correct results with this model COPASI has changed the stoichiometries of all species with conversion factors. Exporting this model again will lead to a model with changed stoichiometries."},
  {MCSBML + 101, "SBML (101): Assignment rule for species reference \"%s\" imported. Please be aware that COPASI does not support stoichiometries that change over time. The imported expression has therefore been converted to a constant value."},
  {MCSBML + 102, "SBML (102): The SBML document you are trying to load uses SBML Level %d Version %d. This version is not yet supported by this version of COPASI, COPASI will attempt to read as much of the model as it can." },
  {MCSBML + 103, "SBML (103): The SBML compartment \"%s\" with dimension %.1f has an incompatible unit \"%s\" using default unit."},
  {MCSBML + 104, "SBML (104): The SBML %s \"%s\" has an invalid %s unit \"%s\" using default unit."},

  // SEDML To be completed
  {MCSEDML + 1, "SEDML (1): SEDML contains no simulation."},
  {MCSEDML + 2, "SEDML (2): The SEDML document contains no model."},
  {MCSEDML + 3, "SEDML (3): Presently only SBML model encoding is supported"},
  {MCSEDML + 4, "SEDML (4): Could not open file \"%s\". Note: The reference SBML model in SEDML document must be saved in the same directory as the SEDML document using the source attribute value as the file name ."},
  {MCSEDML + 5, "SEDML (5): Could not open file \"%s\"."},
  {MCSEDML + 6, "SEDML (40): LIBSEDML %s %d at line %d column %d: %s."},

  {MCTrajectoryProblem + 1, "CTrajectoryProblem (1): Invalid step size = '%f'."},
  {
    MCTrajectoryProblem + 2, "CTrajectoryProblem (2): The step number '%f' "
    "exceeds the limit. The step number and step size have been adjusted to avoid over flow."
  },
  {
    MCTrajectoryProblem + 3, "CTrajectoryProblem (3): The step size '%f' "
    "is to small for the machine accuracy. The step number and step size have been adjusted."
  },

  // Directory Entries
  {MCDirEntry + 1, "DirEntry (1): Directory entry '%s' already exists."},
  {MCDirEntry + 2, "DirEntry (2): Directory entry '%s' is read-only."},
  {MCDirEntry + 3, "DirEntry (3): Opening file '%s' for writing failed."},

  // MathML
  {MCMathML + 1, "MathML (1): Unsupported element '%s'."},
  {MCMathML + 2, "MathML (2): Unknown element in MathML expression."},
  {MCMathML + 3, "MathML (3): MINUS operator can only have one or two arguments."},
  {MCMathML + 4, "MathML (4): DIVIDE and POWER operator can only have 2 arguments."},

  // Function
  {MCFunction + 1, "Function (1): Parser error near character position: '%d'."},
  {MCFunction + 2, "Function (2): Lexer error near character position: '%d'."},
  {MCFunction + 3, "Function (3): Compile error in function '%s' near character position: '%d'."},
  {MCFunction + 4, "Function (4): Circular dependency detected."},

  {MCEvaluationNodeObject + 1, "CEvaluationNodeObject (1): Only references to compartment, species, parameters and reaction are allowed in expression."},

  {MCCopasiTask + 1, "CCopasiTask (1): No problem defined for task '%s'."},
  {MCCopasiTask + 2, "CCopasiTask (2): No model associated for task '%s'."},
  {MCCopasiTask + 3, "CCopasiTask (3): No method defined for task '%s'."},
  {MCCopasiTask + 4, "CCopasiTask (4): Error compiling model '%s'."},
  {MCCopasiTask + 5, "CCopasiTask (5): No output file defined for report of task '%s'."},
  {MCCopasiTask + 6, "CCopasiTask (6): Requested output object:\n '%s'\n not found. It will be ignored."},
  {MCCopasiTask + 7, "CCopasiTask (7): Problems compiling output."},
  {MCCopasiTask + 8, "CCopasiTask (8): '%d' Function Evaluations out of '%d' failed."},
  {MCCopasiTask + 9, "CCopasiTask (9): Recursive call to '%s' through tasks '%s'."},

  {
    MCSteadyState + 1, "CSteadyState (1): The model is explicitly time dependent. "
    "Therefore, the calculation of a steady state using the Newton method is not very meaningful."
  },

  {
    MCFitting + 1, "CFitting (1): Failed to determine work area size for matrix inversion. "
    "dsytrf returned with error '%d'."
  },
  {
    MCFitting + 2, "CFitting (2): Failed to invert Fisher information matrix. "
    "dsytrf returned with error '%d'."
  },
  {MCFitting + 3, "CFitting (3): No column with type 'Time' specified for a time course experiment '%s'."},
  {MCFitting + 4, "CFitting (4): Insufficient experimental data (columns requested '%d', columns found '%d')."},
  {MCFitting + 5, "CFitting (5): Incomplete data mapping, column '%d' must be mapped."},
  {MCFitting + 6, "CFitting (6): Object '%s' in column '%d' has no numeric value."},
  {MCFitting + 7, "CFitting (7): Insufficient experimental data (rows requested '%d', rows found '%d')."},
  {MCFitting + 8, "CFitting (8): Failure reading file '%s'."},
  {MCFitting + 9, "CFitting (9): Experiment '%s' has no data rows."},
  {MCFitting + 10, "CFitting (10): Experiment '%s' has no dependent data."},
  {MCFitting + 11, "CFitting (11): Missing independent data for Experiment '%s' in row '%d', column '%d'."},
  {
    MCFitting + 12, "CFitting (12): The Fisher information matrix is singular. Therefore, the "
    "correlation matrix can not be calculated."
  },
  {MCFitting + 13, "CFitting (13): Not enough memory available to calculate the Fisher Information Matrix."},
  {MCFitting + 14, "CFitting (14): Failed to calculate the Eigen values and Eigen vectors of the Fisher Information Matrix."},
  {MCFitting + 15, "CFitting (15): Failed to calculate the Eigen values and Eigen vectors of the scaled Fisher Information Matrix."},

  // CDataObject
  {MCObject + 1, "CObject (1): Circular dependencies detected for object '%s'."},

  // Lyapunov exponents
  {MCLyap + 1, "CLyapMethod (1): Problem is not a Lyapunov exponent problem."},
  {MCLyap + 2, "CLyapMethod (2): Neither an exponent nor divergence is requested. Nothing to do."},
  {MCLyap + 3, "CLyapMethod (3): Only %d exponents can be calculated for this model because the model has only %d independent variables."},
  {MCLyap + 4, "CLyapMethod (4): Transient time is larger than overall time."},
  {MCLyap + 5, "CLyapMethod (5): Orthonormalization interval is larger than overall time."},
  {MCLyap + 6, "CLyapMethod (6): Internal step size exceeded."},

  // CODEExporter
  {MCODEExporter + 1, "CODEExporter (1): Length of exporting line exceeds 1000 characters."},
  {
    MCODEExporter + 2, "CODEExporter (2): The export was incomplete since the model depends on model"
    "quantities, which can currently not be exported."
  },

  {MCRegistration + 1, "CRegistration (1): Invalid registration code."},
  {MCRegistration + 2, "CRegistration (2): Email and/or user name do not match registration code."},
  {MCRegistration + 3, "CRegistration (3): Trial license expired on: '%s'."},

  // CTSSAMethod
  {
    MCTSSAMethod + 1, "CTSSAMethod (1): Deterministic integration failed:"
    "\n%s \n\nPlease see result for indications of numerical instability."
  },
  {MCTSSAMethod + 2, "CTSSAMethod (2): Problem is not a time scale separation analysis problem."},
  {MCTSSAMethod + 3, "CTSSAMethod (3): Internal step limit exceeded."},
  {MCTSSAMethod + 4, "CTSSAMethod (4): Numerical Error encountered."},
  {MCTSSAMethod + 5, "CILDMMethod (5): Problems with calculation of Jacobi matrix at time t='%f'."},
  {MCTSSAMethod + 6, "CILDMMethod (6): At time t='%f' all eigen values are positive. No reduction is possible."},
  {MCTSSAMethod + 7, "CILDMMethod (7): Problems with calculation of Sylvester equation for the mode number '%d' at time t='%f'."},
  {MCTSSAMethod + 8, "CILDMMethod (8): At time t='%f' no reduction is possible"},
  {MCTSSAMethod + 9, "CTSSAMethod (9): Problems with calculation of Jacobi matrix at time t='%f'."},
  {MCTSSAMethod + 10, "CILDMModifiedMethod (10): At time t='%f'  all eigen values are positive. No reduction is possible."},
  {MCTSSAMethod + 11, "CILDMModifiedMethod (11): At time t='%f'  no reduction is possible."},
  {MCTSSAMethod + 12, "CCSPMethod (12): At time t='%f'  no reduction is possible."},
  {MCTSSAMethod + 13, "CTSSAMethod (13): Number of compartments has to be exactly one. "},
  {MCTSSAMethod + 14, "CTSSAMethod (14): The problem is not valid for this method: the metabolites determined by assignments or ODE are presenting. "},
  {MCTSSAMethod + 15, "CTSSAMethod (15): At time t='%f': there are negative time scales. "},
  {MCTSSAMethod + 16, "CTSSAMethod (16): This method is not applicable for a system with more than one compartment. "},
  {MCTSSAMethod + 17, "CTSSAMethod (17): In this version of Copasi the CSP Method only supports  compartments with equal size  "},
  {MCTSSAMethod + 18, "CTSSAMethod (18): TSSA requires metabolites to be present." },

  // CTSSAProblem
  {MCTSSAProblem + 1, "CTSSAProblem (1): Invalid step size = '%f'."},
  {
    MCTSSAProblem + 2, "CTSSAProblem (2): The step number '%f' "
    "exceeds the limit. The step number and step size have been adjusted to avoid over flow."
  },
  {
    MCTSSAProblem + 3, "CTSSAProblem (3): The step size '%f' "
    "is to small for the machine accuracy. The step number and step size have been adjusted."
  },

  {MCEigen + 1, "CEigen (1): Invalid argument '%d' for dgees."},
  {MCEigen + 2, "CEigen (2): Failed to compute Eigen value with index '%d'."},
  {MCEigen + 3, "CEigen (3): Unable to sort Eigen values."},
  {MCEigen + 4, "CEigen (4): Eigen values do not satisfy selection criteria after reordering."},

  {MCAnnotation + 1, "CAnnotation (1): Problem parsing RDF at line '%d', column '%d':\n %s"},
  {MCAnnotation + 2, "CAnnotation (2): Namespace prefix redefinition for '%s' from '%s' to '%s'."},
  {
    MCAnnotation + 3, "CAnnotation (3): Updating the MIRIRAM resource information failed. "
    "Please try again. The server responded:   \n%s   \n%s"
  },
  {
    MCAnnotation + 4, "CAnnotation (4): The MIRIAM resource '%s' is unknown to COPASI. "
    "Please try to update the list of resources by running Update MIRIAM from the tools menu."
  },
  {MCAnnotation + 5, "CAnnotation (5): The annotation '%s' contains invalid XML."},
  {MCAnnotation + 6, "CAnnotation (6): An annotation with then name '%s' already exists."},
  {MCAnnotation + 7, "CAnnotation (7): The name of an annotation must not be empty."},
  {MCAnnotation + 8, "CAnnotation (8): An annotation with the name '%s' already exists."},

  // Messages generated by the mathematical model an all its classes.
  {
    MCMathModel + 1, "CMathModel (1): Simultaneous event assignments encountered. The simulation cannot "
    "continue."
  },
  {
    MCMathModel + 2, "CMathModel (2): The execution time '%d' of an event is before the current"
    " time '%d' due to a negative delay."
  },
  {MCMathModel + 3, "CMathModel (3): Recursive prerequisites encountered for object '%s'."},

  //CModelMerging
  {MCModelMerging + 1, "CModelMerging (1): An error has occurred while constructing the temporary (joined)  data model."},
  {MCModelMerging + 2, "CModelMerging (2): Failed while merging the  species  \"%s\" with the species  \"%s\" . "},

  //CModelExpansion
  {MCModelExpansion + 1, "CModelExpansion (1): An error has occurred while creation of the array of compartments."},
  {MCModelExpansion + 2, "CModelExpansion (2): Negative number of copies ."},

  //CEFMAnalysis
  {MCEFMAnalysis + 1, "CEFMAnalysis (1): Invalid task."},
  {MCEFMAnalysis + 2, "CEFMAnalysis (2): Invalid problem."},
  {MCEFMAnalysis + 3, "CEFMAnalysis (3): Non integer stoichiometry found for reaction '%s'."},

  {MCLayout + 1, "CLayout (1): Could not open image file '%s'."},

  {MCScan + 1, "CScan (1): The scan item '%s' set the initial value of a state variable and is ignored when Continue from Current State is checked."},

  {MCMCA + 1, "CMCA (1): Numerical instabilities encountered, at least one of the the Summation Theorems is violated."},

  // Unit
  {MCUnit + 1, "CUnit (1): Parser error near character position: '%d'."},
  {MCUnit + 2, "CUnit (2): Lexer error near character position: '%d'."},
  {MCUnit + 3, "CUnit (3): Problem parsing: '%s'."},

  // UnitDefinition
  {MCUnitDefinition + 1, "CUnitDefinition (1): CUnitDefintion needs to be child of a CUnitDefinitionDB."},
  {MCUnitDefinition + 2, "CUnitDefinition (2): Symbol '%s' is already in use."},

  // Jit Compilation
  {MCJitCompilation + 1, "CJitCompiler (1): Unhandled error occurred in '%s' when compiling '%s'."},
  {MCJitCompilation + 2, "CJitCompiler (2): Unhandled node when compiling '%s'."},
  {MCJitCompilation + 3, "CJitCompiler (3): Unhandled error occurred: '%s'."},

  // This must be the last element of the message list! Do not delete!
  {0, NULL}
};

#endif //COPASI_MESSAGES_H
