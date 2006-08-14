/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/messages.h,v $
   $Revision: 1.74 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/08/14 20:56:08 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

const MESSAGES Messages[] =
  {
    // CReadConfig
    {MCReadConfig + 1, "CReadConfig (1): Variable '%s' not found in '%s(%d)'."},
    {MCReadConfig + 2, "CReadConfig (2): Cannot open file '%s'."},
    {MCReadConfig + 3, "CReadConfig (3): Cannot read file '%s'."},
    {MCReadConfig + 4, "CReadConfig (4): Cannot close file '%s'."},
    {MCReadConfig + 5, "CReadConfig (5): Invalid type '%s' for  Variable '%s'."},

    // CKinFunction
    {MCKinFunction + 1, "CKinFunction (1): Cannot find identifier '%s'"
     " in function '%s'."},
    {MCKinFunction + 2, "CKinFunction (2): Missing operant in function '%s'."},

    // CRange
    {MCRange + 1, "CRange (1): Invalid range ('%d', '%d')."},

    // CCopasiVector
    {MCCopasiVector + 1, "CCopasiVector (1): Object '%s' not found."},
    {MCCopasiVector + 2, "CCopasiVector (2): Object '%s' already exists."},

    // CFunctionParameters
    {MCFunctionParameters + 1, "CFunctionParameters (1): The usage '%s' "
     "is not unique for a vector type parameter ('%d')."},
    {MCFunctionParameters + 2, "CFunctionParameters (2): No parameter with "
     "usage '%s' with index >= '%ld'."},

    // CMassAction
    {MCMassAction + 1, "CMassAction (1): The function Mass Action reversibility "
     "must be either TRUE or FALSE."},

    // CCopasiMethod
    {MCCopasiMethod + 1, "CCopasiMethod (1): No parameter list "
     "found for name '%s' and type '%s'."},
    {MCCopasiMethod + 2, "CCopasiMethod (2): pProblem == NULL"},
    {MCCopasiMethod + 3, "CCopasiMethod (3): Model is not set in problem"},

    // CReaction
    {MCReaction + 1, "CReaction (1): Function '%s' not found."},
    {MCReaction + 2, "CReaction (2): In Reaction '%s' the compartment could not be guessed."},
    {MCReaction + 3, "CReaction (3): Reaction '%s' has no substrates and no products."},
    {MCReaction + 4, "CReaction (4): Only Metabolites, Compartments or Parameter object nodes are allowed in kinetic functions."},
    {MCReaction + 5, "CReaction (5): Nodes of type '%s' are not implemented yet."},
    {MCReaction + 6, "CReaction (6): Nodes of type VARIABLE must not appear in an expression."},
    {MCReaction + 7, "CReaction (7): CMetab object '%s' is neither substrate, product nor modifier to reaction '%s' but it is used in the kinetic law."},
    {MCReaction + 8, "CReaction (8): Could not find variable with name '%s'."},
    {MCReaction + 9, "CReaction (9): Could not find object for key '%s'."},
    {MCReaction + 10, "CReaction (10): Parameter '%s' is a vector."},

    // CChemEq
    {MCChemEq + 1, "CChemEq (1): No Substrates and no Products."},
    {MCChemEq + 2, "CChemEq (2): Substrates in different Compartments."},
    {MCChemEq + 3, "CChemEq (3): No Substrates and Products are in different compartments."},

    // CMethodParameter
    {MCParameter + 1, "CCopasiParameter (1): Invalid value '%f' for '%s' "
     "which is of type '%s'."},
    {MCParameter + 2, "CCopasiParameter (2): Elevation failed, since no parameter is provided."},
    {MCParameter + 3, "CCopasiParameter (3): Elevation failed, since the parameter is not of the required source type."},
    {MCParameter + 4, "CCopasiParameter (4): Elevation failed, since elevation of children failed."},
    {MCParameter + 5, "CCopasiParameter (5): Elevation failed, since the parameter is not member of this group."},

    // CTrajectoryMethod
    {MCTrajectoryMethod + 1, "CTrajectoryMethod (1): Hybrid simulation not "
     "applicable, since the stoichiometry contains a non-integer."},
    {MCTrajectoryMethod + 2, "CTrajectoryMethod (2): Hybrid simulation not "
     "applicable, since reversible reactions exists."},
    {MCTrajectoryMethod + 3, "CTrajectoryMethod (3): Hybrid simulation not "
     "applicable, since more than one compartment is involved."},
    {MCTrajectoryMethod + 4, "CTrajectoryMethod (4): Lower Limit '%.2f' is greater than Upper Limit '%.2f'."},
    {MCTrajectoryMethod + 6, "CTrajectoryMethod (6): Deterministic integration failed. "
     "LSODA reported:\n%s \n\nPlease see result for indications of numerical instability."},
    {MCTrajectoryMethod + 7, "CTrajectoryMethod (7): pProblem == NULL"},
    {MCTrajectoryMethod + 8, "CTrajectoryMethod (8): Problem is not a trajectory problem."},
    {MCTrajectoryMethod + 9, "CTrajectoryMethod (9): Negative time steps not possible with stochastic simulation."},
    {MCTrajectoryMethod + 10, "CTrajectoryMethod (10): The tau-Leap Method encountered numerical problems.\nYou can try to reduce the tau-value."},
    {MCTrajectoryMethod + 11, "CTrajectoryMethod (11): Invalid tau-value ('%.2f'). Tau must have a positive value."},
    {MCTrajectoryMethod + 12, "CTrajectoryMethod (12): Internal step limit exceeded."},
    {MCTrajectoryMethod + 13, "CTrajectoryMethod (13): Runge Kutta Stepsize must be positive in hybrid method."},
    {MCTrajectoryMethod + 14, "CTrajectoryMethod (14): Use Random Seed should be 0 or 1 since it is a boolean parameter."},
    {MCTrajectoryMethod + 15, "CTrajectoryMethod (15): Max Internal Steps needs to be positive."},

    // XML Package
    {MCXML + 1, "XML (1): Required attribute '%s' not found (line: '%d')."},
    {MCXML + 2, "XML (2): XML error (line: '%d', column: '%d'): '%s'."},
    {MCXML + 3, "XML (3): Unknown element '%s' encountered at line '%d'."},
    {MCXML + 4, "XML (4): Unknown parameter '%s' encountered at line '%d'."},
    {MCXML + 5, "XML (5): Unknown task type '%s' encountered at line '%d'."},
    {MCXML + 6, "XML (6): Invalid function '%s' encountered at line '%d'."},
    {MCXML + 7, "XML (7): Unknown function '%s' in reaction '%s' encountered at line '%d'."},
    {MCXML + 8, "XML (8): Unknown variable '%s' in function '%s' encountered at line '%d'. "
     "A possible reason is that the variable is a reserved string within the function description."},

    // CCopasiMessage
    {MCCopasiMessage + 1, "Message (1): No more messages."},

    // Configuration
    {MCConfiguration + 1, "Configuration (1): COPASI directory is not set. Some features might not be working correctly.\n"
     "                   Please set the environment variable COPASIDIR or use the\n"
     "                   commandline options -c COPASIDIR or --copasidir COPASIDIR\n"
     "                   to point to the COPASI installation directory."},
    {MCConfiguration + 2, "Configuration (2): Configuration file '%s' found but is not readable."},

    // Optimization
    {MCOptimization + 1, "Optimization (1): Object '%s' not found."},
    {MCOptimization + 2, "Optimization (2): Lower Bound '%s' not found."},
    {MCOptimization + 3, "Optimization (3): Upper Bound '%s' not found."},
    {MCOptimization + 4, "Optimization (4): Empty Interval ('%f', '%f') specified."},
    {MCOptimization + 5, "Optimization (5): Invalid Objective Functions."},
    {MCOptimization + 6, "Optimization (6): No adjustable Parameters specified."},
    {MCOptimization + 7, "Optimization (7): No Task Type specified."},
    {MCOptimization + 8, "Optimization (8): '%d' Function Evaluation out of '%d' failed."},

    // SBML
    {MCSBML + 1, "SBML (1): SBML Level2 Version1 does not support initial times different from 0. This information will be lost in the exported file."},
    {MCSBML + 2, "SBML (2): The SBML document contains no model."},
    {MCSBML + 3, "SBML (3): The SBML document contains unsupported rules that were ignored.\nOnly rate and assignment rules for global parameters are currently supported."},
    {MCSBML + 4, "SBML (4): The SBML document contains events that were ignored."},
    {MCSBML + 5, "SBML (5): Compartment %s referenced by species %s does not exist."},
    {MCSBML + 6, "SBML (6): Annotations in SBase element of SBML Level 1 files, this is invalid and has been ignored."},
    {MCSBML + 7, "SBML (7): One or more model values have not been set."},
    {MCSBML + 8, "SBML (8): Expression tree for kinetic of reaction '%s' could not be converted."},
    {MCSBML + 9, "SBML (9): Could not set function from expression in reaction '%s'."},
    {MCSBML + 10, "SBML (10): Copasi does not support stoichiometric expressions yet."},
    {MCSBML + 11, "SBML (11): Function '%s' does not start with a Lambda element."},
    {MCSBML + 12, "SBML (12): Function '%s' contains invalid parameter list."},
    {MCSBML + 13, "SBML (13): Could not read function definition for function '%s'."},
    {MCSBML + 14, "SBML (14): Could not import function with id '%s'."},
    {MCSBML + 15, "SBML (15): Could not find function with id '%s'."},
    {MCSBML + 16, "SBML (16): Loop found in function. That means a function calls itself either directly or indirectly."},
    {MCSBML + 17, "SBML (17): Single compartment reaction found where the kinetic law does not include a multiplication by the volume."},
    {MCSBML + 18, "SBML (18): Support for 'hasOnlySubstanceUnit' flag on species is experimental. Species in compartments of dimension 0 are also considered to have this flag set."},
    {MCSBML + 19, "SBML (19): spatialSizeUnits on species %s ignored."},
    {MCSBML + 20, "SBML (20): Setting an initial concentration on species %s which has the 'hasOnlySubstanceUnits' flag set is not allowed."},
    {MCSBML + 21, "SBML (21): Setting an initial concentration on species '%s' which is in a compartment with spatial dimensions 0 is not allowed."},
    {MCSBML + 22, "SBML (22): Current versions of Copasi only supports three dimensional compartments. '%s' will be converted to three dimensions."},
    {MCSBML + 23, "SBML (23): Unable to handle compartment '%s' which has spatial dimensions of 0."},
    {MCSBML + 24, "SBML (24): Units for compartment '%s' ignored."},
    {MCSBML + 25, "SBML (25): Units for species '%s' ignored."},
    {MCSBML + 26, "SBML (26): Units for parameter '%s' ignored."},
    {MCSBML + 27, "SBML (27): Error in kinetic law for reaction '%s'."},
    {MCSBML + 28, "SBML (28): Error in function definition with id '%s'."},
    {MCSBML + 29, "SBML (29): Unable to handle reactions with the 'fast' flag set.\nThe flag has been set to false."},
    {MCSBML + 30, "SBML (30): Can't handle units of type item with scale set to 1.\n If this file was created with COPASI RC1 or older please see the COPASI FAQ."},
    {MCSBML + 31, "SBML (31): %s are currently only supported for global parameters."},
    {MCSBML + 32, "SBML (32): Error in %s variable id '%s' does not specify a Compartment, Species or global Parameter."},
    {MCSBML + 33, "SBML (33): Error: %s is not allowed for local parameter '%s'."},
    {MCSBML + 34, "SBML (34): Error: %s is not allowed for local constant %s identified by id '%s'."},
    {MCSBML + 35, "SBML (35): Error: Only one AssignmentRule or RateRule is allowed for id '%s'."},
    {MCSBML + 36, "SBML (36): COPASI can not handle models that use the delay function."},
    {MCSBML + 37, "SBML (37): The id '%s' is used in the expression of a rule, although it is later defined by a rule itself."},

    {MCTrajectoryProblem + 1, "CTrajectoryProblem (1): Invalid step size = '%f'."},
    {MCTrajectoryProblem + 2, "CTrajectoryProblem (2): The step number '%f' "
     "exceeds the limit. The step number and step size have been adjusted to avoid over flow."},
    {MCTrajectoryProblem + 3, "CTrajectoryProblem (3): The step size '%f' "
     "is to small for the machine accuracy. The step number and step size have been adjusted."},

    // Directory Entries
    {MCDirEntry + 1, "DirEntry (1): Directory entry '%s' already exists."},
    {MCDirEntry + 2, "DirEntry (2): Directory entry '%s' is read-only."},

    // MathML
    {MCMathML + 1, "MathML (1): Unsupported element '%s'."},
    {MCMathML + 2, "MathML (2): Unknown element in MathML expression."},
    {MCMathML + 3, "MathML (3): MINUS operator can only have one or two arguments."},
    {MCMathML + 4, "MathML (4): DIVIDE and POWER operator can only have 2 arguments."},

    // Function
    {MCFunction + 1, "Function (1): Parser error after position: '%d'."},
    {MCFunction + 2, "Function (2): Lexer error after position: '%d'."},
    {MCFunction + 3, "Function (3): Compile error after position: '%d'."},
    {MCFunction + 4, "Function (4): Circular dependency detected."},

    {MCEvaluationNodeObject + 1, "CEvaluationNodeObject (1): Only references to compartment, species, parameters and reaction are allowed in expression."},

    {MCCopasiTask + 1, "CCopasiTask (1): No problem defined for Task '%s'."},
    {MCCopasiTask + 2, "CCopasiTask (2): No model associated for Task '%s'."},
    {MCCopasiTask + 3, "CCopasiTask (3): No method defined for Task '%s'."},
    {MCCopasiTask + 4, "CCopasiTask (4): Error compiling Model '%s'."},
    {MCCopasiTask + 5, "CCopasiTask (5): No output file defined for report."},
    {MCCopasiTask + 6, "CCopasiTask (6): Problems compiling Report '%s'."},
    {MCCopasiTask + 7, "CCopasiTask (7): Problems compiling Plots."},

    {MCSteadyState + 1, "CSteadyState (1): The model is explicitly time dependent. "
     "Therefore, the calculation of a steady state is not very meaningful."},

    {MCFitting + 1, "CFitting (1): Failed to determine work area size for matrix inversion. "
     "dsytrf returned with error '%d'."},
    {MCFitting + 2, "CFitting (2): Failed to invert Fisher information matrix. "
     "dsytrf returned with error '%d'."},
    {MCFitting + 3, "CFitting (3): No column with type 'Time' specified for a time course experiment."},
    {MCFitting + 4, "CFitting (4): Insufficient experimental data (columns requested '%d', columns found '%d')."},
    {MCFitting + 5, "CFitting (5): Incomplete data mapping, column '%d' must be mapped."},
    {MCFitting + 6, "CFitting (6): Object '%s' in column '%d' has no numeric value."},
    {MCFitting + 7, "CFitting (7): Insufficient experimental data (rows requested '%d', rows found '%d')."},
    {MCFitting + 8, "CFitting (8): Failure reading file '%s'."},

    // CCopasiObject
    {MCObject + 1, "CObject (1): Circular dependencies detected for object '%s'."},

    // Lyapunov exponents
    {MCLyap + 1, "CLyapMethod (1): Problem is not a lyapunov exponent problem."},
    {MCLyap + 2, "CLyapMethod (2): Number of exponents needs to be at least one."},
    {MCLyap + 3, "CLyapMethod (3): Only %d exponents can be calculated for this model because the model has only %d independent variables."},
    {MCLyap + 4, "CLyapMethod (4): Transient time is larger than overall time."},
    {MCLyap + 5, "CLyapMethod (5): Orthonormalization interval is larger than overall time."},

    // This must be the last element of the message list! Do not delete!
    {0, NULL}
  };
