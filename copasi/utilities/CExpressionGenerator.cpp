// Copyright (C) 2022 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CExpressionGenerator.h"

#include <sstream>

#include <copasi/model/CModel.h>

// static
std::map< std::string, CExpressionGenerator::sOperation > CExpressionGenerator::mOperations =
{
  {"Sum", {" + ", "", "", "", ""}},
  {"Sum of Squares", {" + ", "", "", "", "^2"}},
  {"Sum of Absolutes", {" + ", "", "", "ABS(", ")"}},
  {"Product", {" * ", "", "", "", ""}},
};

// static
std::vector< std::string > CExpressionGenerator::mSupportedTypes =
{
  "Global Quantities",
  "Species",
  "Reactions",
  "Compartments",
};

// static
std::string CExpressionGenerator::escapeDisplayName(const CDataObject * pObject)
{
  std::string name = pObject->getObjectDisplayName();
  // We need to escape >
  std::string::size_type pos = name.find_first_of("}");

  while (pos != std::string::npos)
    {
      name.insert(pos, "\\");
      pos += 2;
      pos = name.find_first_of("}", pos);
    }

  return name;
}

CExpressionGenerator::CExpressionGenerator(
  const std::string & type,
  const std::string & selection,
  const std::string & operation)
  : CDataObject("ExpressionGenerator")
  , mType(type)
  , mSelection(selection)
  , mOperation(operation)
{
}

std::vector< std::string > CExpressionGenerator::getSupportedOperations()
{
  std::vector< std::string > result;

  for (auto & entry : mOperations)
    result.push_back(entry.first);

  return result;
}

bool CExpressionGenerator::isTypeSupported(const std::string & type)
{
  return std::find(mSupportedTypes.begin(), mSupportedTypes.end(), type) != mSupportedTypes.end();
}

std::vector< const CDataObject * > CExpressionGenerator::getObjectsForSelection(const CModel * pModel) const
{
  std::vector< const CDataObject * > result;

  if (!pModel)
    return result;

  if (mType == "Species")
    {
      for (auto & metab : pModel->getMetabolites())
        {
          if (mSelection == "Rates (Particle Numbers)")
            result.push_back(metab.getRateReference());

          if (mSelection == "Rates (Concentrations)")
            result.push_back(metab.getConcentrationRateReference());

          if (mSelection == "Transient Particle Numbers")
            result.push_back(metab.getValueReference());

          if (mSelection == "Transient Concentrations")
            result.push_back(metab.getConcentrationReference());

          if (mSelection == "Initial Particle Numbers")
            result.push_back(metab.getInitialValueReference());

          if (mSelection == "Initial Concentrations")
            result.push_back(metab.getInitialConcentrationReference());
        }
    }

  if (mType == "Global Quantities")
    {
      for (auto & mv : pModel->getModelValues())
        {
          if (mSelection == "Rates")
            result.push_back(mv.getRateReference());

          if (mSelection == "Transient Values")
            result.push_back(mv.getValueReference());

          if (mSelection == "Initial Values")
            result.push_back(mv.getInitialValueReference());
        }
    }

  if (mType == "Compartments")
    {
      for (auto & comp : pModel->getCompartments())
        {
          if (mSelection == "Rates")
            result.push_back(comp.getRateReference());

          if (mSelection == "Transient Volumes")
            result.push_back(comp.getValueReference());

          if (mSelection == "Initial Volumes")
            result.push_back(comp.getInitialValueReference());
        }
    }

  if (mType == "Reactions")
    {
      for (auto & reaction : pModel->getReactions())
        {
          if (mSelection == "Fluxes (Particle Numbers)")
            result.push_back(reaction.getParticleFluxReference());

          if (mSelection == "Fluxes (Amount)")
            result.push_back(reaction.getFluxReference());
        }
    }

  return result;
}

std::string CExpressionGenerator::generateExpressionFor(const CModel * pModel, bool useCn) const
{
  auto operation = mOperations[ mOperation];

  if (!pModel)
    return std::string();

  auto selection = getObjectsForSelection(pModel);

  if (selection.empty())
    return std::string();

  auto entry = *selection.begin();

  std::stringstream result;
  result << operation.surroundStart;

  result << operation.entryStart;

  if (useCn)
    result << "<" << entry->getCN() << ">";
  else
    result << "{" << escapeDisplayName(entry) << "}";

  result << operation.entryEnd;

  for (int i = 1; i < selection.size(); ++i)
    {
      entry = selection[i];

      result << operation.join;
      result << operation.entryStart;

      if (useCn)
        result << "<" << entry->getCN() << ">";
      else
        result << "{" << escapeDisplayName(entry) << "}";

      result << operation.entryEnd;
    }

  result << operation.surroundEnd;

  return result.str();
}

void CExpressionGenerator::setType(const std::string & type)
{
  mType = type;
}

void CExpressionGenerator::setSelection(const std::string & selection)
{
  mSelection = selection;
}

void CExpressionGenerator::setOperation(const std::string & operation)
{
  mOperation = operation;
}
