#include "CProfileSettings.h"

#include <limits>

#include <copasi/utilities/CTaskEnum.h>
#include <copasi/commandline/COptions.h>

CProfileSettings::CProfileSettings()
	: CCopasiParameterGroup("ProfileSettings")
{
  std::string tmpDir; 
  COptions::getValue("Tmp", tmpDir);
  assertParameter("Directory", CCopasiParameter::Type::STRING, tmpDir);
  assertParameter("CopasiSE", CCopasiParameter::Type::STRING, std::string("CopasiSE"));
  assertParameter("IsParameterEstimation", CCopasiParameter::Type::BOOL, true);
  assertParameter("Run Statistics", CCopasiParameter::Type::BOOL, true);
  assertParameter("Delete Existing", CCopasiParameter::Type::BOOL, true);

  // settings for model generation
  auto * pGroup = assertGroup("Generate");
  pGroup->assertParameter("Prefix", CCopasiParameter::Type::STRING, std::string("_"));
  pGroup->assertParameter("Method", CCopasiParameter::Type::INT, (int)CTaskEnum::Method::LevenbergMarquardt);
  pGroup->assertParameter("Iterations", CCopasiParameter::Type::INT, 50);
  pGroup->assertParameter("Scan Interval", CCopasiParameter::Type::INT, 40);
  pGroup->assertParameter("Lower Adjustment", CCopasiParameter::Type::STRING, std::string("-50%"));
  pGroup->assertParameter("Upper Adjustment", CCopasiParameter::Type::STRING, std::string("+50%"));
  pGroup->assertParameter("Disable Other Tasks", CCopasiParameter::Type::BOOL, true);
  pGroup->assertParameter("Disable Other Plots", CCopasiParameter::Type::BOOL, true);
  

  // process settings
  assertParameter("Num Processes", CCopasiParameter::Type::INT, 4);

  // plot settings

  pGroup = assertGroup("Plot");
  pGroup->assertParameter("Scale Top", CCopasiParameter::Type::DOUBLE, std::numeric_limits< double >::quiet_NaN());
  pGroup->assertParameter("Scale Bottom", CCopasiParameter::Type::DOUBLE, std::numeric_limits< double >::quiet_NaN());
  pGroup->assertParameter("Thresholds", CCopasiParameter::Type::STRING, std::string("copasi_68;copasi_95"));
  pGroup->assertParameter("Vertical Lines", CCopasiParameter::Type::STRING, std::string("VALUE;1SD;2SD"));

}

CProfileSettings::CProfileSettings(const CProfileSettings & other)
: CCopasiParameterGroup(other)
{
}
	

std::string CProfileSettings::getDirectory() const
{
  return getValue< std::string >("Directory");
}

std::string CProfileSettings::getCopasiSE() const
{
  return getValue< std::string >("CopasiSE");
}
