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
   * serializes the given parameter group to JSON
   */
  static nlohmann::json toJson(const CCopasiParameterGroup * group, bool basic_only = true);

  /**
   * overwrites parameters in the given parameter group from the provided JSON object
   */
  static void fromJson(CCopasiParameterGroup * group, const nlohmann::json & object);

};

#endif // CPROFILE_SETTINGS_H
