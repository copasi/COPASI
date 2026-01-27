#ifndef CQPROFILE_WIDGET_H
#define CQPROFILE_WIDGET_H

class CProfileSettings;
class CQProfileWidget
{
public:
  /**
     * loads the settings from the given profile settings
     */
  virtual void loadSettings(const CProfileSettings * pSettings) = 0;

  /**
     * save the settings to the given profile settings
     */
  virtual void saveSettings(CProfileSettings * pSettings) = 0;
};

#endif // CQPROFILE_WIDGET_H
