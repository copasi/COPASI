#ifndef UnitConversionFactory_hpp__
#define UnitConversionFactory_hpp__

#include "sbml/UnitDefinition.hpp"
#include "sbml/Unit.hpp"
#include "sbml/ListOf.hpp"
#include <vector>
#include <string>


class UnitConversionFactory{
   public:

      /*
       * Converts a Unit into the corresponding UnitDefinition that consists
       * only of SI units.
       * Possible offsets are ignored.
       * Freeing the memory for the returned UnitDefinition is up to the
       * receiver.
       * On failure a NULL pointer is returned.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertToSI(const Unit& unit);     

      /*
       * Converts a UnitDefinition into the corresponding UnitDefinition that consists
       * only of SI units.
       * Possible offsets are ignored.
       * Freeing the memory for the returned UnitDefinition is up to the
       * receiver.
       * On failure a NULL pointer is returned.
       * @param const UnitDefinition& uDef
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertToSI(const UnitDefinition& uDef);

      /*
       * Checks if two UnitDefinitions are equivalent, i.e. wether they are
       * interconvertible.
       * This is the case if they consist of the same set of units after being
       * converted to SI units.
       * If the offset of two equivalent units differ, false is returned.
       * @param const UnitDefinition& uDef1
       * @param const UnitDefinition& uDef2
       * @return bool areEquivalent
       */
      LIBSBML_EXTERN
      static bool areEquivalent(const UnitDefinition& uDef1,const UnitDefinition& uDef2);  
     
      /*
       * Converts the given value from the given source UnitDefinition to the
       * given destination UnitDefinition if the two UnitDefinitions are
       * equivalent.
       * The original value is changed. On success the functions returns true,
       * otherwise it returns false.
       * @param const double* value
       * @param const UnitDefinition& srcUdef
       * @param const UnitDefinition& destUdef
       * @return bool success
       */
      LIBSBML_EXTERN
      static bool convertValue(double *value,const UnitDefinition& srcUdef,const UnitDefinition& destUdef);  
      
      /*
       * The functions determins wether the given UnitDefinition contains only
       * units from the list given as the second argument.
       * @param const UnitDefinition& uDef
       * @param const ListOf& unitList
       * @return bool containsOnlyGivenUnits
       */
      LIBSBML_EXTERN
      static bool containsOnlyGivenUnits(const UnitDefinition& uDef,const ListOf& unitList);
      
      /*
       * Returns a string representation of the given Unit. THis function is
       * only for debugging purposes.
       * @param const Unit& unit
       * @return std::string unitRepresentation
       */
      LIBSBML_EXTERN
      static std::string toString(const Unit& unit);
      
      /*
       * Returns a string representation of the given Unit. THis function is
       * only for debugging purposes.
       * @param const UnitDefinition& uDef
       * @return std::string unitDefinitionRepresentation
       */
      LIBSBML_EXTERN
      static std::string toString(const UnitDefinition& uDef);
          
   protected:
      /*
       * Vector that holds the ids for UnitDefinitions that have been created
       * by the conversion framework so that no two UnitDefinitions produced
       * have the same id.
       * Something like that should be put into libsbml because here it is only
       * of limited use.
       */
      static std::vector<std::string> usedIds;

      /*
       * Checks wether a given id is has already been used by the conversion
       * framework.
       * @param const std::string id
       * @return bool isUnused
       */
      LIBSBML_EXTERN
      static bool isIdUnused(const std::string& id);
    
      /*
       * Converts an Ampere Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertAmpereToSI(const Unit& unit);  
      
      /*
       * Converts a frequency Unit into the corresponding UnitDefinition
       * consisting only of SI units. This could be e.g. a Hertz or Bequerel unit. 
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertFrequencyToSI(const Unit& unit);
      
      /*
       * Converts a Candela Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertCandelaToSI(const Unit& unit);
      
      /*
       * Converts a Celsius Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertCelsiusToSI(const Unit& unit);
      
      /*
       * Converts a Coulomb Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertCoulombToSI(const Unit& unit);
      
      /*
       * Converts a "Dimensionless" Unit into the corresponding UnitDefinition
       * consisting only of SI units. This would include e.g. the Radian unit.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertDimensionlessToSI(const Unit& unit);
      
      /*
       * Converts a Farad Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertFaradToSI(const Unit& unit);
      
      /*
       * Converts a Kilogram Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertKilogramToSI(const Unit& unit);
      
      /*
       * Converts a dose Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * Dose units are e.g. gray and sievert.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertDoseToSI(const Unit& unit);
      
      /*
       * Converts a Henry Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertHenryToSI(const Unit& unit);
      
      /*
       * Converts a Joule Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertJouleToSI(const Unit& unit);
      
      /*
       * Converts a Katal Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertKatalToSI(const Unit& unit);
      
      /*
       * Converts a Kelvin Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertKelvinToSI(const Unit& unit);
      
      /*
       * Converts a Lumen Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertLumenToSI(const Unit& unit);
      
      /*
       * Converts a Lux Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertLuxToSI(const Unit& unit);
      
       /*
       * Converts a Meter Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
     LIBSBML_EXTERN
      static UnitDefinition* convertMeterToSI(const Unit& unit);
      
       /*
       * Converts a Mole Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
     LIBSBML_EXTERN
      static UnitDefinition* convertMoleToSI(const Unit& unit);
      
       /*
       * Converts a Newton Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertNewtonToSI(const Unit& unit);
      
       /*
       * Converts a Ohm Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertOhmToSI(const Unit& unit);
      
       /*
       * Converts a Pascal Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertPascalToSI(const Unit& unit);
      
       /*
       * Converts a Second Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertSecondToSI(const Unit& unit);
      
       /*
       * Converts a Siemens Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
     LIBSBML_EXTERN
      static UnitDefinition* convertSiemensToSI(const Unit& unit);
      
       /*
       * Converts a Tesla Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertTeslaToSI(const Unit& unit);
      
      /*
       * Converts a Volt Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertVoltToSI(const Unit& unit);
      
      /*
       * Converts a Watt Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertWattToSI(const Unit& unit);
      
      /*
       * Converts a Weber Unit into the corresponding UnitDefinition
       * consisting only of SI units.
       * If the given unit does not have the correct kind, a NULL pointer is
       * returned.
       * It is up to the receiver to free the memory of the returned
       * UnitDefinition.
       * @param const Unit& unit
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* convertWeberToSI(const Unit& unit);

      /*
      LIBSBML_EXTERN
      static UnitDefinition* normalize(const UnitDefinition& uDef);  
      */
      
      /*
       * Combines two UnitDefinitions by combining the equivalent units from
       * both UnitDefinitions.
       * A new UnitDefinition containing the combination is returned.
       * If two eqivalent units have a different offset, the function returns a
       * NULL pointer.
       * It is up to the receiver to free the memory of the returned UnitDefinition.
       * @param const UnitDefinition& uDef1
       * @param const UnitDefinition& uDef2
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* combine(const UnitDefinition& uDef1,const UnitDefinition& uDef2);  
      
      /*
       * Eliminate all dimensionless units from the given UnitDefinition.
       * A new UnitDefinition without the dimensionless units is returned.
       * The scale and multiplier are preserved. If the UnitDefinition has only
       * one unit the is a dimensionless, it is not deleted.
       * @param UnitDefinition* pUdef
       * @return UnitDefinition* result
       */
      LIBSBML_EXTERN
      static UnitDefinition* eliminateDimensionless(UnitDefinition* pUdef);
      
};

#endif /* UnitConversionFactory_hpp__ */
