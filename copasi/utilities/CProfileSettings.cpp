// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CProfileSettings.h"

#include <limits>

#include <copasi/utilities/CTaskEnum.h>
#include <copasi/copasi.h>
#include <copasi/commandline/COptions.h>

#include <copasi/utilities/CCopasiParameter.h>
#include <copasi/utilities/CCopasiParameterGroup.h>

/**
 * Returns the values from the given parameter group as dictionary
 *
 *  :param group: the copasi parameter group
 *  :param basic_only: boolean indicating, whether only basic parameters should be returned (default)
 *
 *  :return: json object with the values
 */
nlohmann::json CProfileSettings::toJson(const CCopasiParameterGroup * group, bool basic_only /*= true*/)
{
  nlohmann::json result = {};
  if (!group)
    return result;

  for (size_t i = 0; i < group->size(); i++)
    {
      const CCopasiParameter * param = group->getParameter(i);
      auto name = param->getObjectName();
      auto param_type = param->getType();

      if (param_type == CCopasiParameter::Type::GROUP)
        {
          const auto * childGroup = dynamic_cast< const CCopasiParameterGroup * >(param);
          auto child = toJson(childGroup, basic_only);
          if (result.contains(name))
            {
              auto & existing = result[name];
              if (!existing.is_array())
                {
                  result[name] = nlohmann::json::array({existing, child});
                }
              else
                {
                  result[name].emplace_back(child);
                }
            }
          else
            {
              result[name] = child;
            }
          continue;
        }

      if (!param->isEditable())
        continue;

      if (!param->isBasic() && basic_only)
        continue;

      if (param_type == CCopasiParameter::Type::STRING || param_type == CCopasiParameter::Type::KEY || param_type == CCopasiParameter::Type::FILE)
        {
          auto child = param->getValue< std::string >();
        if (result.contains(name))
        {
            auto & existing = result[name];
            if (!existing.is_array())
              {
                result[name] = nlohmann::json::array({existing, child});
              }
            else
              {
                result[name].emplace_back(child);
              }
         }
        else
          {
          result[name] = child;
          }
        }
      else if (param_type == CCopasiParameter::Type::INT)
        result[name] = param->getValue< C_INT32 >();
      else if (param_type == CCopasiParameter::Type::UINT)
        result[name] = param->getValue< C_UINT32 >();
      else if (param_type == CCopasiParameter::Type::DOUBLE)
        result[name] = param->getValue< C_FLOAT64 >();
      else if (param_type == CCopasiParameter::Type::UDOUBLE)
        result[name] = param->getValue< C_FLOAT64 >();
      else if (param_type == CCopasiParameter::Type::BOOL)
        result[name] = param->getValue< bool >();
      else if (param_type == CCopasiParameter::Type::CN)
        {
          auto cn = param->getValue< CCommonName >();
          auto child = cn.c_str();
          if (result.contains(name))
            {
              auto & existing = result[name];
              if (!existing.is_array())
                {
                  result[name] = nlohmann::json::array({existing, child});
                }
              else
                {
                  result[name].emplace_back(child);
                }
            }
          else
            {
              result[name] = child;
            }
        }
    }
  return result;
}

/*static */void
CProfileSettings::fromJson(CCopasiParameterGroup* group, const nlohmann::json& object)
{
  bool basic_only = false;

  if (!group)
    return;

  for (size_t i = 0; i < group->size(); i++)
    {
      CCopasiParameter * param = group->getParameter(i);
      auto name = param->getObjectName();
      if (!object.contains(name))
        continue;
      auto param_type = param->getType();

      if (param_type == CCopasiParameter::Type::GROUP)
        {
          // skip for now
          continue;
        }

      if (!param->isEditable())
        continue;

      if (!param->isBasic() && basic_only)
        continue;

      if (param_type == CCopasiParameter::Type::STRING || param_type == CCopasiParameter::Type::KEY || param_type == CCopasiParameter::Type::FILE)
        {
          param->setValue< std::string >(object.at(name).get< std::string >());
        }
      else if (param_type == CCopasiParameter::Type::INT)
        param->setValue< C_INT32 >(object.at(name).get< C_INT32 >());
      else if (param_type == CCopasiParameter::Type::UINT)
        param->setValue< C_UINT32 >(object.at(name).get< C_UINT32 >());
      else if (param_type == CCopasiParameter::Type::DOUBLE)
        param->setValue< C_FLOAT64 >(object.at(name).get< C_FLOAT64 >());
      else if (param_type == CCopasiParameter::Type::UDOUBLE)
        param->setValue< C_FLOAT64 >(object.at(name).get< C_FLOAT64 >());
      else if (param_type == CCopasiParameter::Type::BOOL)
        param->setValue< bool >(object.at(name).get< bool >());
      else if (param_type == CCopasiParameter::Type::CN)
        {
          param->setValue< CRegisteredCommonName >(CRegisteredCommonName(object.at(name).get< std::string >()));
        }
      else
      {
        continue;
      }
  }
}

CProfileSettings::CProfileSettings()
	: nlohmann::json()
{
  std::string tmpDir;
  COptions::getValue("Tmp", tmpDir);
  (*this)["Directory"] = tmpDir;
  (*this)["CopasiSE"] = std::string("CopasiSE");
  (*this)["IsParameterEstimation"] = true;
  (*this)["Run Statistics"] = true;
  (*this)["Delete Existing"] = true;
  (*this)["Prefix"] = std::string("_");

  // settings for model generation
  (*this)["Generate"]["Method"] = (int) CTaskEnum::Method::LevenbergMarquardt;
  (*this)["Generate"]["Iterations"] = 50;
  (*this)["Generate"]["Scan Interval"] = 40;
  (*this)["Generate"]["Lower Adjustment"] = std::string("-50%");
  (*this)["Generate"]["Upper Adjustment"] = std::string("+50%");
  (*this)["Generate"]["Disable Other Tasks"] = true;
  (*this)["Generate"]["Disable Other Plots"] = true;
  (*this)["Generate"]["Logarithmic"] = false;
  (*this)["Generate"]["Continue from current State"] = false;

  // process settings
  (*this)["Num Processes"] = 4;

  // plot settings
  (*this)["Plot"]["Scale Top"] = std::numeric_limits< double >::quiet_NaN();
  (*this)["Plot"]["Scale Bottom"] = 0;
  (*this)["Plot"]["Thresholds"] = std::string("copasi_68;copasi_95");
  (*this)["Plot"]["Vertical Lines"] = std::string("VALUE;1SD;2SD");

  // restore settings from file
  load();
}

CProfileSettings::CProfileSettings(const CProfileSettings & other)
: nlohmann::json(other)
{
}
	

std::string CProfileSettings::getDirectory() const
{
  return (*this)["Directory"];
}

std::string CProfileSettings::getCopasiSE() const
{
  return (*this)["CopasiSE"];
}

void CProfileSettings::save() const
{
  // Save the settings to a '.profileSettings' file in the COPASI directory
  std::string copasiDir = COptions::getConfigDir();
  std::ofstream outFile(copasiDir + "/.profileSettings");

  // copy subset of data to be stored
  nlohmann::json data;
  data["Directory"] = (*this)["Directory"];
  data["CopasiSE"] = (*this)["CopasiSE"];
  data["Prefix"] = (*this)["Prefix"];
  if (outFile)
  {
      outFile << data.dump(4);
  }
}

void CProfileSettings::load()
{
  // Load the settings from a file or other storage
  std::string copasiDir = COptions::getConfigDir();
  std::ifstream inFile(copasiDir + "/.profileSettings");
  if (inFile)
    {
      nlohmann::json data;
      try
        {
          inFile >> data;
        }
      catch (...)
        {
          return; // ignore errors
        }

      if (data.contains("Directory"))
        {
          (*this)["Directory"] = data["Directory"];
        }
      if (data.contains("CopasiSE"))
        {
          (*this)["CopasiSE"] = data["CopasiSE"];
        }
       if (data.contains("Prefix"))
        {
          (*this)["Prefix"] = data["Prefix"];
        }
    }
}

CProfileSettings
CProfileSettings::fromFile(const std::string & fileName)
{
  auto settings = CProfileSettings();
  settings.load();

  std::ifstream inFile(fileName);
  if (inFile)
    {
      nlohmann::json data;
      inFile >> data;

      // iterate through properties and set them in the settings
      for (auto & [key, value] : data.items())
        {
          settings[key] = value;
        }
    }
  return settings;
}

void CProfileSettings::saveToFile(const std::string & fileName) const
{
  std::ofstream outFile(fileName);
  if (outFile)
    {
      outFile << this->dump(4);
    }
}
