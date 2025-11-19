// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CPROFILE_SETTINGS_H
#define CPROFILE_SETTINGS_H

#include <copasi/utilities/json.hpp>

class CCopasiParameterGroup;

class CProfileSettings : public nlohmann::json
{
protected:

public:
  CProfileSettings();
  CProfileSettings(const CProfileSettings & other);

  std::string getDirectory() const;
  std::string getCopasiSE() const;

  void save() const;
  void load();

  static CProfileSettings fromFile(const std::string & fileName);
  void saveToFile(const std::string & fileName) const;

  /**
   * serializes the given parameter group to JSON
   */
  static nlohmann::json toJson(const CCopasiParameterGroup * group, bool basic_only = true);

  /**
   * overwrites parameters in the given parameter group from the provided JSON object
   */
  static void fromJson(CCopasiParameterGroup * group, const nlohmann::json & object);
};

#endif // CPROFILE_SETTINGS_H
