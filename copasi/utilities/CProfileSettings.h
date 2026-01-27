// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
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

  /**
   * loads settings from the given file
   */
  static CProfileSettings fromFile(const std::string & fileName);

  /**
   * saves the current settings to the given file
   */
  void saveToFile(const std::string & fileName) const;

  /**
   * serializes the given parameter group to JSON
   */
  static nlohmann::json toJson(const CCopasiParameterGroup * group, bool basic_only = true);

  /**
   * overwrites parameters in the given parameter group from the provided JSON object
   */
  static void fromJson(CCopasiParameterGroup * group, const nlohmann::json & object);

  /**
   * @return the property value as double (or default if not present / wrong type)
   */
  double dblValue(const std::string & key, const std::string & property = "", double defaultValue = std::numeric_limits<double>::quiet_NaN()) const;

  /**
   * @return the property value as string (or default if not present / wrong type)
   */
  std::string strValue(const std::string & key, const std::string & property = "", const std::string & defaultValue = "") const;

  /**
   * @return the property value as bool (or default if not present / wrong type)
   */
  bool boolValue(const std::string & key, const std::string & property = "", bool defaultValue = false) const;

  /**
   * @return the property value as int (or default if not present / wrong type)
   */
  int intValue(const std::string & key, const std::string & property = "", int defaultValue = 0) const;
};

#endif // CPROFILE_SETTINGS_H
