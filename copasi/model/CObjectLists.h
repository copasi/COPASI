/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CObjectLists.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/05 14:04:44 $
   End CVS Header */

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
      ALL_METABS,
      NON_CONST_METABS,
      ALL_METAB_CONCENTRATIONS,
      NON_CONST_METAB_CONCENTRATIONS,
      ALL_METAB_NUMBERS,
      NON_CONST_METAB_NUMBERS,
      NON_CONST_METAB_CONC_RATES,
      NON_CONST_METAB_PART_RATES,
      ALL_METAB_INITIAL_CONCENTRATIONS,
      ALL_METAB_INITIAL_NUMBERS,

      REACTIONS,
      REACTION_CONC_FLUXES,
      REACTION_PART_FLUXES,

      GLOBAL_PARAMETERS,
      GLOBAL_PARAMETER_VALUES,
      //GLOBAL_PARAMETER_INITIAL_VALUES,
      //GLOBAL_PARAMETER_RATES,

      COMPARTMENTS,
      COMPARTMENT_VOLUMES,
      //COMPARTMENT_INITIAL_VOLUMES,
      //COMPARTMENT_RATES,

      ALL_LOCAL_PARAMETER_VALUES,

      ALL_PARAMETER_VALUES,
      ALL_PARAMETER_AND_INITIAL_VALUES
    };

    static
    std::vector<CCopasiObject*> getListOfObjects(ListType t, const CModel* model);

    static
    std::vector<const CCopasiObject*> getListOfConstObjects(ListType t, const CModel* model);

    static
    bool existsFixedMetab(const CModel* model);

  private:
    typedef std::vector<CCopasiObject*> ObjectList;

    //TODO: method to select a subset of lists for a specific application (output or parameter)

    //TODO: display names
  };

#endif
