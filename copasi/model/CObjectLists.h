// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CObjectLists
#define COPASI_CObjectLists

#include <vector>
#include <set>

class CDataObject;
class CModel;
class CModelEntity;
class CMetab;

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
    CONST_GLOBAL_PARAMETER_INITIAL_VALUES,
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
    ALL_ODE_VARIABLES,

    REDUCED_JACOBIAN_EV_RE,
    REDUCED_JACOBIAN_EV_IM
  };

  static const std::string ListTypeName[];

  static
  std::vector< CDataObject * > getListOfObjects(ListType t, const CModel* model);

  static
  std::vector< const CDataObject * > getListOfConstObjects(ListType t, const CModel* model);

  static
  bool existsFixedMetab(const CModel* model);

  /**
   * Create a set of all entities which are event targets
   * @return std::set< const CModelEntity * > eventTargets
   */
  static
  std::set< const CModelEntity * > getEventTargets(const CModel* pModel);
  //TODO: display names

private:
  typedef std::vector< const CDataObject * > ObjectList;
};

#endif
