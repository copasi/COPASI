#ifndef UnitConversionFactory_hpp__
#define UnitConversionFactory_hpp__

#include "sbml/UnitDefinition.hpp"
#include "sbml/Unit.hpp"
#include "sbml/ListOf.hpp"
#include <vector>
#include <string>


class UnitConversionFactory{
   public:
      LIBSBML_EXTERN
      static UnitDefinition* convertToSI(const Unit& unit);     

      LIBSBML_EXTERN
      static UnitDefinition* convertToSI(const UnitDefinition& uDef);

      LIBSBML_EXTERN
      static bool areEquivalent(const UnitDefinition& uDef1,const UnitDefinition& uDef2);  
     
      LIBSBML_EXTERN
      static bool convertValue(double *value,const UnitDefinition& srcUdef,const UnitDefinition& destUdef);  
      
      LIBSBML_EXTERN
      static bool containsOnlyGivenUnits(const UnitDefinition& uDef,const ListOf& unitList);
      
      LIBSBML_EXTERN
      static std::string toString(const Unit& unit);
      
      LIBSBML_EXTERN
      static std::string toString(const UnitDefinition& uDef);
          
   protected:
      static std::vector<std::string> usedIds;

      LIBSBML_EXTERN
      static bool isIdUnused(const std::string& id);
    
      LIBSBML_EXTERN
      static UnitDefinition* convertAmpereToSI(const Unit& unit);  
      
      LIBSBML_EXTERN
      static UnitDefinition* convertFrequencyToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertCandelaToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertCelsiusToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertCoulombToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertDimensionlessToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertFaradToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertKilogramToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertDoseToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertHenryToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertJouleToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertKatalToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertKelvinToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertLumenToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertLuxToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertMeterToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertMoleToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertNewtonToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertOhmToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertPascalToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertSecondToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertSiemensToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertTeslaToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertVoltToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertWattToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* convertWeberToSI(const Unit& unit);
      
      LIBSBML_EXTERN
      static UnitDefinition* normalize(const UnitDefinition& uDef);  
     
      LIBSBML_EXTERN
      static UnitDefinition* combine(const UnitDefinition& uDef1,const UnitDefinition& uDef2);  
      LIBSBML_EXTERN
      static UnitDefinition* eliminateDimensionless(UnitDefinition* pUdef);
      
};

#endif /* UnitConversionFactory_hpp__ */
