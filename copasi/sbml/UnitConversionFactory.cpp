/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/UnitConversionFactory.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/02/16 09:05:41 $
   End CVS Header */

class UnitDefinition;

#include "UnitConversionFactory.hpp"
#include "sbml/UnitKind.h"
#include <math.h>
#include <sstream>

std::vector<std::string> UnitConversionFactory::usedIds = std::vector<std::string>();

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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertAmpereToSI(const Unit& unit)
{
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertFrequencyToSI(const Unit& unit)
{
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setKind(UNIT_KIND_SECOND);
  pU->setOffset(0.0);
  pU->setExponent(-1*pU->getExponent());
  return pUdef;
}

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertCandelaToSI(const Unit& unit)
{
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertCelsiusToSI(const Unit& unit)
{
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setKind(UNIT_KIND_KELVIN);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertCoulombToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertDimensionlessToSI(const Unit& unit)
{
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setKind(UNIT_KIND_DIMENSIONLESS);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertFaradToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertKilogramToSI(const Unit& unit)
{
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertDoseToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertHenryToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertJouleToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertKatalToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertKelvinToSI(const Unit& unit)
{
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertLumenToSI(const Unit& unit)
{
  Unit* pU = new Unit(unit);
  pU->setKind(UNIT_KIND_CANDELA);
  UnitDefinition* pUdef = convertCandelaToSI(*pU);
  delete pU;
  return pUdef;
}

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertLuxToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertMeterToSI(const Unit& unit)
{
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertMoleToSI(const Unit& unit)
{
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertNewtonToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertOhmToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertPascalToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertSecondToSI(const Unit& unit)
{
  UnitDefinition* pUdef = new UnitDefinition();
  Unit* pU = new Unit(unit);
  pU->setOffset(0.0);
  pUdef->addUnit(*pU);
  return pUdef;
}

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertSiemensToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertTeslaToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertVoltToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertWattToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
UnitDefinition* UnitConversionFactory::convertWeberToSI(const Unit& unit)
{
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

LIBSBML_EXTERN
bool UnitConversionFactory::containsOnlyCopasiUnits(const UnitDefinition& uDef)
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
          if ((kind != UNIT_KIND_METER) && kind != (UNIT_KIND_SECOND) && (kind != UNIT_KIND_MOLE))
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
