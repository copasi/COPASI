/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/UnitConversionFactory.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/02/18 07:57:53 $
   End CVS Header */

class UnitDefinition;

#include "UnitConversionFactory.hpp"
#include "sbml/UnitKind.h"
#include <math.h>
#include <sstream>

/*
 * Vector that holds the ids for UnitDefinitions that have been created
 * by the conversion framework so that no two UnitDefinitions produced
 * have the same id.
 */
std::vector<std::string> UnitConversionFactory::usedIds = std::vector<std::string>();

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
UnitDefinition* UnitConversionFactory::convertToSI(const Unit& unit)
{
  UnitDefinition* pUdef = NULL;
  Unit* pU = NULL;
  if (!unit.isSetKind()) return pUdef;
  UnitKind_t uKind = unit.getKind();
  switch (uKind)
    {
    case UNIT_KIND_AMPERE:
      pUdef = convertAmpereToSI(unit);
      break;

    case UNIT_KIND_BECQUEREL:
    case UNIT_KIND_HERTZ:
      pUdef = convertFrequencyToSI(unit);
      break;

    case UNIT_KIND_CANDELA:
      pUdef = convertCandelaToSI(unit);
      break;

    case UNIT_KIND_CELSIUS:
      pUdef = convertCelsiusToSI(unit);
      break;

    case UNIT_KIND_COULOMB:
      pUdef = convertCoulombToSI(unit);
      break;

    case UNIT_KIND_DIMENSIONLESS:
    case UNIT_KIND_ITEM:
    case UNIT_KIND_RADIAN:
    case UNIT_KIND_STERADIAN:
      pUdef = convertDimensionlessToSI(unit);
      break;

    case UNIT_KIND_FARAD:
      pUdef = convertFaradToSI(unit);
      break;

    case UNIT_KIND_GRAM:
      pU = new Unit(unit);
      pU->setScale(pU->getScale() - 3);
      pU->setKind(UNIT_KIND_KILOGRAM);
      pUdef = convertKilogramToSI(*pU);
      delete pU;
      break;

    case UNIT_KIND_GRAY:
    case UNIT_KIND_SIEVERT:
      pUdef = convertDoseToSI(unit);
      break;

    case UNIT_KIND_HENRY:
      pUdef = convertHenryToSI(unit);
      break;

    case UNIT_KIND_JOULE:
      pUdef = convertJouleToSI(unit);
      break;

    case UNIT_KIND_KATAL:
      pUdef = convertKatalToSI(unit);
      break;

    case UNIT_KIND_KELVIN:
      pUdef = convertKelvinToSI(unit);
      break;

    case UNIT_KIND_KILOGRAM:
      pUdef = convertKilogramToSI(unit);
      break;

    case UNIT_KIND_LITER:
    case UNIT_KIND_LITRE:
      pU = new Unit(unit);
      pU->setKind(UNIT_KIND_METER);
      pU->setExponent(pU->getExponent()*3);
      pU->setScale(pU->getScale() - 3);
      pUdef = convertMeterToSI(*pU);
      delete pU;
      break;

    case UNIT_KIND_LUMEN:
      pUdef = convertLumenToSI(unit);
      break;

    case UNIT_KIND_LUX:
      pUdef = convertLuxToSI(unit);
      break;

    case UNIT_KIND_METER:
    case UNIT_KIND_METRE:
      pUdef = convertMeterToSI(unit);
      break;

    case UNIT_KIND_MOLE:
      pUdef = convertMoleToSI(unit);
      break;

    case UNIT_KIND_NEWTON:
      pUdef = convertNewtonToSI(unit);
      break;

    case UNIT_KIND_OHM:
      pUdef = convertOhmToSI(unit);
      break;

    case UNIT_KIND_PASCAL:
      pUdef = convertPascalToSI(unit);
      break;

    case UNIT_KIND_SECOND:
      pUdef = convertSecondToSI(unit);
      break;

    case UNIT_KIND_SIEMENS:
      pUdef = convertSiemensToSI(unit);
      break;

    case UNIT_KIND_TESLA:
      pUdef = convertTeslaToSI(unit);
      break;

    case UNIT_KIND_VOLT:
      pUdef = convertVoltToSI(unit);
      break;

    case UNIT_KIND_WATT:
      pUdef = convertWattToSI(unit);
      break;

    case UNIT_KIND_WEBER:
      pUdef = convertWeberToSI(unit);
      break;

    case UNIT_KIND_INVALID:
      delete pUdef;
      pUdef = NULL;
      break;
    }
  if (pUdef != NULL)
    {
      unsigned int num = 1;
      std::stringstream ss;
      ss << "UnitDefinition_" << num;
      while (!UnitConversionFactory::isIdUnused(ss.str()))
        {
          ++num;
          ss.str("");
          ss << "UnitDefinition_" << num;
        }
      std::string id = ss.str();
      usedIds.push_back(id);
      pUdef->setId(id);
      UnitKind_t uKind = unit.getKind();
      pUdef->setName(UnitKind_toString(uKind));
    }
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertAmpereToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_AMPERE) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertFrequencyToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_HERTZ && uKind != UNIT_KIND_BECQUEREL) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setKind(UNIT_KIND_SECOND);
  pU->setOffset(0.0);
  pU->setExponent(-1*pU->getExponent());
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertCandelaToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_CANDELA) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertCelsiusToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_CELSIUS) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setKind(UNIT_KIND_KELVIN);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertCoulombToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_COULOMB) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setKind(UNIT_KIND_AMPERE);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  pU = new Unit();
  pU->setKind(UNIT_KIND_SECOND);
  pU->setExponent(unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertDimensionlessToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_DIMENSIONLESS && uKind != UNIT_KIND_ITEM && uKind != UNIT_KIND_RADIAN && uKind != UNIT_KIND_STERADIAN) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setKind(UNIT_KIND_DIMENSIONLESS);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertFaradToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_FARAD) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pU->setKind(UNIT_KIND_AMPERE);
  pU->setExponent(2*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_KILOGRAM);
  pU->setExponent(-1*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_METER);
  pU->setExponent(-2*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_SECOND);
  pU->setExponent(4*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertKilogramToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_KILOGRAM) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertDoseToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_GRAM && uKind != UNIT_KIND_SIEVERT) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pU->setKind(UNIT_KIND_METER);
  pU->setExponent(2*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_SECOND);
  pU->setExponent(-2*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertHenryToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_HENRY) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pU->setKind(UNIT_KIND_AMPERE);
  pU->setExponent(-2*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_KILOGRAM);
  pU->setExponent(unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_METER);
  pU->setExponent(2*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_SECOND);
  pU->setExponent(-2*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertJouleToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_JOULE) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pU->setKind(UNIT_KIND_KILOGRAM);
  pU->setExponent(unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_METER);
  pU->setExponent(2*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_SECOND);
  pU->setExponent(-2*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertKatalToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_KATAL) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pU->setKind(UNIT_KIND_MOLE);
  pU->setExponent(unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_SECOND);
  pU->setExponent(-1*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertKelvinToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_KELVIN) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertLumenToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_LUMEN) return NULL;
  Unit* pU = new Unit(unit);
  pU->setKind(UNIT_KIND_CANDELA);
  UnitDefinition* pUdef = convertCandelaToSI(*pU);
  delete pU;
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertLuxToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_LUX) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setKind(UNIT_KIND_CANDELA);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_METER);
  pU->setExponent(-2*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertMeterToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_METER) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertMoleToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_MOLE) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertNewtonToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_NEWTON) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pU->setKind(UNIT_KIND_KILOGRAM);
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_METER);
  pU->setExponent(unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_SECOND);
  pU->setExponent(-2*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertOhmToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_OHM) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pU->setKind(UNIT_KIND_AMPERE);
  pU->setExponent(-2*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_KILOGRAM);
  pU->setExponent(unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_METER);
  pU->setExponent(2*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_SECOND);
  pU->setExponent(-3*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertPascalToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_PASCAL) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setKind(UNIT_KIND_KILOGRAM);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_METER);
  pU->setExponent(-1*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_SECOND);
  pU->setExponent(-2*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertSecondToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_SECOND) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertSiemensToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_SIEMENS) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pU->setKind(UNIT_KIND_AMPERE);
  pU->setExponent(2*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_KILOGRAM);
  pU->setExponent(-1*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_METER);
  pU->setExponent(-2*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_SECOND);
  pU->setExponent(3*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertTeslaToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_TESLA) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pU->setKind(UNIT_KIND_AMPERE);
  pU->setExponent(-1*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_KILOGRAM);
  pU->setExponent(unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_SECOND);
  pU->setExponent(-2*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertVoltToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_VOLT) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pU->setKind(UNIT_KIND_AMPERE);
  pU->setExponent(-1*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_KILOGRAM);
  pU->setExponent(unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_METER);
  pU->setExponent(2*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_SECOND);
  pU->setExponent(-3*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertWattToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_WATT) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pU->setKind(UNIT_KIND_KILOGRAM);
  pU->setExponent(unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_METER);
  pU->setExponent(2*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_SECOND);
  pU->setExponent(-3*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

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
UnitDefinition* UnitConversionFactory::convertWeberToSI(const Unit& unit)
{
  UnitKind_t uKind = unit.getKind();
  if (uKind != UNIT_KIND_WATT) return NULL;
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pU->setKind(UNIT_KIND_AMPERE);
  pU->setExponent(-1*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_KILOGRAM);
  pU->setExponent(unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_METER);
  pU->setExponent(2*unit.getExponent());
  pUdef->addUnit(*pU);
  pU = new Unit(UNIT_KIND_SECOND);
  pU->setExponent(-2*unit.getExponent());
  pUdef->addUnit(*pU);
  return pUdef;
}

/*
   LIBSBML_EXTERN
   UnitDefinition* UnitConversionFactory::normalize(const UnitDefinition& uDef)
   {
// convert all units to SI units
// see if units other then the first one have a scale and/or a multiplier
// if so, combine those with the scale and/or multiplier of the first unit
UnitDefinition* pResult = NULL;
unsigned int maxUnits = uDef.getNumUnits();
unsigned int counter = 0;
while (counter < maxUnits)
{
Unit* pU = uDef.getUnit(counter);
UnitDefinition* pTempUdef = UnitConversionFactory::convertToSI(*pU);
if (pTempUdef == NULL)
{
pResult = NULL;
break;
}
UnitDefinition* pTempUdef2 = UnitConversionFactory::combine(*pResult, *pTempUdef);
delete pTempUdef;
delete pResult;
pResult = pTempUdef2;
if (pResult == NULL)
{
break;
}
++counter;
}
if (pResult != NULL)
{
pResult->setName(uDef.getName());
pResult->setId(uDef.getId());
maxUnits = pResult->getNumUnits();
counter = 1;
if (maxUnits > 0)
{
Unit* pFirst = pResult->getUnit(0);
while (counter < maxUnits)
{
Unit* pU = pResult->getUnit(counter);
int scale = pU->getScale();
if (scale != 0)
{
pFirst->setScale(scale + pFirst->getScale());
}
double multiplier = pU->getMultiplier();
if (multiplier != 1.0)
{
// if the multiplier is 0, the unit definition does not make sense
// we treat this as an error rather than returning a dimensionless
// UnitDefinition
if (multiplier == 0.0)
{
delete pResult;
pResult = NULL;
break;
}
pFirst->setMultiplier(multiplier*pFirst->getMultiplier());
}
++counter;
}
}
}
return pResult;
}
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
UnitDefinition* UnitConversionFactory::combine(const UnitDefinition& uDef1, const UnitDefinition& uDef2)
{
  // take all Units from the first UnitDefinition make copies and put them into the new UnitDefinition
  // go through all Units in the second UnitDefinition, if the same unit already exists in the new
  // UnitDefinition combine them, else add a copy of the Unit to the new UnitDefinition
  UnitDefinition* pResult = new UnitDefinition();
  unsigned int maxUnits = uDef1.getNumUnits();
  unsigned int i;
  for (i = 0; i < maxUnits;++i)
    {
      Unit* pSrcUnit = uDef1.getUnit(i);
      unsigned int maxUnits2 = pResult->getNumUnits();
      unsigned int j;
      bool exists = false;
      for (j = 0; j < maxUnits2;++j)
        {
          Unit* pResultUnit = pResult->getUnit(j);
          if (pResultUnit->getKind() == pSrcUnit->getKind())
            {
              exists = true;
              // if the offsets are different, we can not combine the units
              if (pResultUnit->getOffset() != pSrcUnit->getOffset())
                {
                  delete pResult;
                  return NULL;
                }
              pResultUnit->setMultiplier(pResultUnit->getMultiplier()*pSrcUnit->getMultiplier()*pow(10, pResultUnit->getScale() - pSrcUnit->getScale()));
              pResultUnit->setExponent(pResultUnit->getExponent() + pSrcUnit->getExponent());
              // if the resulting scale is 0, the units have canceled each other out
              // and we set the kind to dimensionless so that it can be eliminated
              // later on
              if (pResultUnit->getExponent() == 0)
                {
                  pResultUnit->setKind(UNIT_KIND_DIMENSIONLESS);
                }
            }
        }
      if (!exists)
        {
          Unit* tmpUnit = new Unit(*pSrcUnit);
          pResult->addUnit(*tmpUnit);
        }
    }
  maxUnits = uDef2.getNumUnits();
  for (i = 0; i < maxUnits;++i)
    {
      Unit* pSrcUnit = uDef2.getUnit(i);
      unsigned int maxUnits2 = pResult->getNumUnits();
      unsigned int j;
      bool exists = false;
      for (j = 0; j < maxUnits2;++j)
        {
          Unit* pResultUnit = pResult->getUnit(j);
          if (pResultUnit->getKind() == pSrcUnit->getKind())
            {
              exists = true;
              // if the offsets are different, we can not combine the units
              if (pResultUnit->getOffset() != pSrcUnit->getOffset())
                {
                  delete pResult;
                  return NULL;
                }
              pResultUnit->setMultiplier(pResultUnit->getMultiplier()*pSrcUnit->getMultiplier()*pow(10, pResultUnit->getScale() - pSrcUnit->getScale()));
              pResultUnit->setExponent(pResultUnit->getExponent() + pSrcUnit->getExponent());
              // if the resulting scale is 0, the units have canceled each other out
              // and we set the kind to dimensionless so that it can be eliminated
              // later on
              if (pResultUnit->getExponent() == 0)
                {
                  pResultUnit->setKind(UNIT_KIND_DIMENSIONLESS);
                }
            }
        }
      if (!exists)
        {
          Unit* tmpUnit = new Unit(*pSrcUnit);
          pResult->addUnit(*tmpUnit);
        }
    }
  UnitDefinition* pTmp = UnitConversionFactory::eliminateDimensionless(pResult);
  if (pTmp)
    {
      delete pResult;
      pResult = pTmp;
    }
  return pResult;
}

/*
 * Eliminate all dimensionless units from the given UnitDefinition.
 * A new UnitDefinition without the dimensionless units is returned.
 * The scale and multiplier are preserved. If the UnitDefinition has only
 * one unit the is a dimensionless, it is not deleted.
 * @param UnitDefinition* pUdef
 * @return UnitDefinition* result
 */
LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::eliminateDimensionless(UnitDefinition* pUdef)
{
  unsigned int maxUnits = pUdef->getNumUnits();
  UnitDefinition* pTmpUdef = NULL;
  Unit* pU = NULL;
  if (maxUnits > 1)
    {
      int scale = 0;
      double multiplier = 1.0;
      unsigned int i = 0;
      pTmpUdef = new UnitDefinition();
      while (i < maxUnits)
        {
          pU = new Unit(*(pUdef->getUnit(i)));
          if (pU->getKind() != UNIT_KIND_DIMENSIONLESS)
            {
              pTmpUdef->addUnit(*pU);
            }
          else
            {
              // conserve scale and multiplier
              scale = scale + pU->getScale();
              multiplier = multiplier * pU->getMultiplier();
            }
          ++i;
        }
      i = pTmpUdef->getNumUnits();
      if (i > 0 && i < maxUnits)
        {
          pTmpUdef->setName(pUdef->getName());
          pTmpUdef->setId(pUdef->getId());
          pU = pTmpUdef->getUnit(0);
          pU->setScale(pU->getScale() + scale);
          pU->setMultiplier(pU->getMultiplier()*multiplier);
        }
      else
        {
          delete pTmpUdef;
          pTmpUdef = NULL;
        }
    }
  return pTmpUdef;
}

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
UnitDefinition* UnitConversionFactory::convertToSI(const UnitDefinition& uDef)
{
  // convert all contained units to SI units
  // combine the resulting unitdefinitions
  UnitDefinition* pResult = NULL;
  UnitDefinition* pTmpDef = NULL;
  unsigned int i;
  unsigned int maxUnits = uDef.getNumUnits();
  if (maxUnits > 0)
    {
      pTmpDef = UnitConversionFactory::convertToSI(*(uDef.getUnit(0)));
      pResult = pTmpDef;
      for (i = 1; i < maxUnits;++i)
        {
          UnitDefinition* pTmpDef2 = UnitConversionFactory::convertToSI(*(uDef.getUnit(i)));
          pResult = UnitConversionFactory::combine(*pTmpDef, *pTmpDef2);
          delete pTmpDef;
          delete pTmpDef2;
          // stop if the result was a NULL pointer
          if (!pResult) break;
          pTmpDef = pResult;
        }
    }
  return pResult;
}

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
bool UnitConversionFactory::areEquivalent(const UnitDefinition& uDef1, const UnitDefinition& uDef2)
{
  bool equivalent = true;
  UnitDefinition* pTmpUdef1 = UnitConversionFactory::convertToSI(uDef1);
  UnitDefinition* pTmpUdef2 = UnitConversionFactory::convertToSI(uDef2);
  if (pTmpUdef1 && pTmpUdef2)
    {
      unsigned int maxUnits = pTmpUdef1->getNumUnits();
      if (maxUnits == pTmpUdef2->getNumUnits())
        {
          unsigned int i;
          // for all units the UnitKind and the exponent must be the same for the unit
          // definitions to be interconvertible
          for (i = 0; i < maxUnits;++i)
            {
              Unit* pUnit1 = pTmpUdef1->getUnit(i);
              Unit* pUnit2 = pTmpUdef2->getUnit(i);
              if (pUnit1->getKind() != pUnit2->getKind())
                {
                  equivalent = false;
                  break;
                }
              if (pUnit1->getExponent() != pUnit2->getExponent())
                {
                  equivalent = false;
                  break;
                }
            }
        }
      else
        {
          equivalent = false;
        }
      delete pTmpUdef1;
      delete pTmpUdef2;
    }
  else
    {
      equivalent = false;
    }
  return equivalent;
}

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
bool UnitConversionFactory::convertValue(double *value, const UnitDefinition& srcUdef, const UnitDefinition& destUdef)
{
  bool success = true;
  if (UnitConversionFactory::areEquivalent(srcUdef, destUdef))
    {
      UnitDefinition* pTmpUdef1 = UnitConversionFactory::convertToSI(srcUdef);
      UnitDefinition* pTmpUdef2 = UnitConversionFactory::convertToSI(destUdef);
      // both UnitDefinitions should only differ in the multiplier of the first unit
      double factor = pTmpUdef1->getUnit(0)->getMultiplier() / pTmpUdef2->getUnit(0)->getMultiplier();
      int scaleDiff = pTmpUdef1->getUnit(0)->getScale() - pTmpUdef2->getUnit(0)->getScale();
      factor = factor * pow(10, scaleDiff);;
      *value = (*value) * factor;
      delete pTmpUdef1;
      delete pTmpUdef2;
    }
  else
    {
      success = false;
    }
  return success;
}

/*
 * The functions determins wether the given UnitDefinition contains only
 * units from the list given as the second argument.
 * @param const UnitDefinition& uDef
 * @param const ListOf& unitList
 * @return bool containsOnlyGivenUnits
 */
LIBSBML_EXTERN
bool UnitConversionFactory::containsOnlyGivenUnits(const UnitDefinition& uDef, const ListOf& unitList)
{
  bool result = true;
  UnitDefinition* pTmpUdef = UnitConversionFactory::convertToSI(uDef);
  if (pTmpUdef)
    {
      unsigned int i;
      unsigned int maxUnits = pTmpUdef->getNumUnits();
      for (i = 0; i < maxUnits;++i)
        {
          Unit* pU = pTmpUdef->getUnit(i);
          UnitKind_t kind = pU->getKind();
          unsigned int j;
          unsigned int maxUnits2 = unitList.getNumItems();
          bool found = false;
          for (j = 0; j < maxUnits2;++j)
            {
              Unit* pU2 = dynamic_cast<Unit*>(unitList.get(j));
              if (!pU2) break;
              if (pU2->getKind() == kind)
                {
                  found = true;
                  break;
                }
            }
          if (!found)
            {
              result = false;
              break;
            }
        }
      delete pTmpUdef;
    }
  else
    {
      result = false;
    }
  return result;
}

/*
 * Checks wether a given id is has already been used by the conversion
 * framework.
 * @param const std::string id
 * @return bool isUnused
 */
LIBSBML_EXTERN
bool UnitConversionFactory::isIdUnused(const std::string& id)
{
  bool unused = true;
  unsigned int i;
  unsigned int maxIds = usedIds.size();
  for (i = 0; i < maxIds;++i)
    {
      if (id == usedIds[i])
        {
          unused = false;
          break;
        }
    }
  return unused;
}

/*
 * Returns a string representation of the given Unit. THis function is
 * only for debugging purposes.
 * @param const UnitDefinition& uDef
 * @return std::string unitDefinitionRepresentation
 */
LIBSBML_EXTERN
std::string UnitConversionFactory::toString(const UnitDefinition& uDef)
{
  unsigned int maxUnits = uDef.getNumUnits();
  unsigned int i;
  std::stringstream ss;
  for (i = 0; i < maxUnits;++i)
    {
      ss << "(" << UnitConversionFactory::toString(*(uDef.getUnit(i))) << ") ";
    }
  return ss.str();
}

/*
 * Returns a string representation of the given Unit. THis function is
 * only for debugging purposes.
 * @param const Unit& unit
 * @return std::string unitRepresentation
 */
LIBSBML_EXTERN
std::string UnitConversionFactory::toString(const Unit& unit)
{
  double multiplier = unit.getMultiplier();
  double offset = unit.getOffset();
  int scale = unit.getScale();
  int exponent = unit.getExponent();
  UnitKind_t kind = unit.getKind();
  std::stringstream ss;
  ss << multiplier << " * (" << UnitKind_toString(kind) << " * 10^" << scale << " + " << offset << ")^" << exponent;
  return ss.str();
}
