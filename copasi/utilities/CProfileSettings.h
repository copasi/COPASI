#ifndef CPROFILE_SETTINGS_H
#define CPROFILE_SETTINGS_H

#include <copasi/utilities/CCopasiParameter.h>
#include <copasi/utilities/CCopasiParameterGroup.h>

class CProfileSettings : public CCopasiParameterGroup
{
protected:
public:
  CProfileSettings();
  CProfileSettings(const CProfileSettings & other);

  std::string getDirectory() const;
  std::string getCopasiSE() const;
};

#endif // CPROFILE_SETTINGS_H
