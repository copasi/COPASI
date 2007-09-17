// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CObjectLists.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/09/17 19:44:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CObjectLists
#define COPASI_CObjectLists

#include <vector>

class CCopasiObject;
class CModel;

class CObjectLists
  {
  public:

    enum ListType
    {
      EMPTY_LIST = 0,
      SINGLE_OBJECT,

      METABS,
      METAB_INITIAL_CONCENTRATIONS,
      METAB_INITIAL_NUMBERS,
      METAB_CONCENTRATIONS,
      METAB_NUMBERS,
      NON_CONST_METAB_CONCENTRATIONS,
      NON_CONST_METAB_NUMBERS,
      CONST_METAB_CONCENTRATIONS,
      CONST_METAB_NUMBERS,
      ODE_METAB_CONCENTRATIONS,
      ODE_METAB_NUMBERS,
      REACTION_METAB_CONCENTRATIONS,
      REACTION_METAB_NUMBERS,
      ASS_METAB_CONCENTRATIONS,
      ASS_METAB_NUMBERS,
      METAB_CONC_RATES,
      METAB_PART_RATES,
      METAB_TRANSITION_TIME,

      REACTIONS,
      REACTION_CONC_FLUXES,
      REACTION_PART_FLUXES,

      GLOBAL_PARAMETERS,
      GLOBAL_PARAMETER_INITIAL_VALUES,
      GLOBAL_PARAMETER_VALUES,
      NON_CONST_GLOBAL_PARAMETER_VALUES,
      CONST_GLOBAL_PARAMETER_VALUES,
      ODE_GLOBAL_PARAMETER_VALUES,
      ASS_GLOBAL_PARAMETER_VALUES,
      GLOBAL_PARAMETER_RATES,

      COMPARTMENTS,
      COMPARTMENT_INITIAL_VOLUMES,
      COMPARTMENT_VOLUMES,
      NON_CONST_COMPARTMENT_VOLUMES,
      CONST_COMPARTMENT_VOLUMES,
      ODE_COMPARTMENT_VOLUMES,
      ASS_COMPARTMENT_VOLUMES,
      COMPARTMENT_RATES,

      ALL_INITIAL_VALUES,
      ALL_LOCAL_PARAMETER_VALUES,

      ALL_PARAMETER_VALUES,
      ALL_PARAMETER_AND_INITIAL_VALUES,

      ALL_VARIABLES, //
      ALL_ODE_VARIABLES
    };

    static const std::string ListTypeName[];

    static
    std::vector<CCopasiObject*> getListOfObjects(ListType t, const CModel* model);

    static
    std::vector<const CCopasiObject*> getListOfConstObjects(ListType t, const CModel* model);

    static
    bool existsFixedMetab(const CModel* model);

  private:
    typedef std::vector<const CCopasiObject*> ObjectList;

    //TODO: method to select a subset of lists for a specific application (output or parameter)

    //TODO: display names
  };

#endif
