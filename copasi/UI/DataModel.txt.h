// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DataModel.txt.h,v $
//   $Revision: 1.35 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2007/04/12 12:33:20 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

static char DataModeltxt[] =
  "0:1:Model\n"
  "1:11:Biochemical\n"
  "11:111:Compartments\n"
  "11:112:Metabolites\n"
  "11:113:Moiety\n"
  "11:114:Reactions\n"
  "11:115:Global Quantities\n"
  "11:116:Parameter Overview\n"
  "1:12:Mathematical\n"
  //"12:122:Used Functions\n"
#ifdef HAVE_MML
  "12:126:Differential Equations\n"
#endif // HAVE_MML
  "12:127:Matrices\n"
#ifdef WITH_LAYOUT
  "1:13:Graphical\n"
  "13:131:Layout\n"
#endif
  "0:2:Tasks\n"
  "2:21:Steady-State\n"
  "21:211:Result\n"
  "2:22:Stoichiometry\n"
  "22:221:Elementary Modes\n"
  "22:222:Mass Conservation\n"
#ifdef COPASI_SSA
  "22:223:Stoichiometric Stability Analysis\n"
#endif // COPASI_SSA
  "2:23:Time Course\n"
  "23:231:Result\n"
  "2:24:Metabolic Control Analysis\n"
  "24:241:Result\n"
#ifdef COPASI_TSS
  "2:25:Time Scale Separation\n"
#endif
  "2:26:Lyapunov Exponents\n"
  "26:261:Result\n"
#ifdef COPASI_DEBUG
  "2:27:Time Scale Separation Analysis\n"
  "27:271:Result\n"
#endif
  "0:3:Multiple Task\n"
  "3:31:Parameter Scan\n"
  "3:32:Optimization\n"
  "32:321:Result\n"
  "3:33:Parameter Estimation\n"
  "33:331:Result\n"
  "3:34:Sensitivities\n"
  "34:341:Result\n"
  "0:4:Output\n"
  "4:42:Plots\n"
  "4:43:Reports\n"
  "0:5:Functions\n"
;
