// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

static char DataModeltxt[] =
  "0:1:Model\n"
  "1:11:Biochemical\n"
  "11:111:Compartments\n"
  "11:112:Species\n"
  "11:114:Reactions\n"
  "11:115:Global Quantities\n"
  "11:116:Events\n"
  "11:118:Parameter Overview\n"
  "11:119:Parameter Sets\n"
  "1:12:Mathematical\n"
  //"12:122:Used Functions\n"
#ifdef HAVE_MML
  "12:126:Differential Equations\n"
#endif // HAVE_MML
  "12:127:Matrices\n"
#ifdef COPASI_DEBUG
  "12:128:Update order\n"
#endif // COPASI_DEBUG
  "1:13:Diagrams\n"
  "0:2:Tasks\n"
  "2:21:Steady-State\n"
  "21:211:Result\n"
  "2:22:Stoichiometric Analysis\n"
  "22:221:Elementary Modes\n"
  "221:2211:Result\n"
  "22:222:Mass Conservation\n"
  "222:2221:Result\n"
  "2:23:Time Course\n"
  "23:231:Result\n"
  "2:24:Metabolic Control Analysis\n"
  "24:241:Result\n"
  "2:26:Lyapunov Exponents\n"
  "26:261:Result\n"
  "2:27:Time Scale Separation Analysis\n"
  "27:271:Result\n"
#ifdef COPASI_NONLIN_DYN
  "2:28:Cross Section\n"
  "28:281:Result\n"
#endif
#ifdef COPASI_NONLIN_DYN_OSCILLATION
  "2:29:Oscillation\n"
#endif
  //  "0:3:Multiple Task\n"
  "2:31:Parameter Scan\n"
  "2:32:Optimization\n"
  "32:321:Result\n"
  "2:33:Parameter Estimation\n"
  "33:331:Result\n"
  "2:34:Sensitivities\n"
  "34:341:Result\n"
  "2:35:Linear Noise Approximation\n"
  "35:351:Result\n"
  "0:4:Output Specifications\n"
  "4:42:Plots\n"
  "4:43:Report Templates\n"
  "0:5:Functions\n"
  ;
