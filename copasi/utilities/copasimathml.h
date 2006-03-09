/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/copasimathml.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2006/03/09 12:59:18 $
   End CVS Header */

#ifndef COPASI_MATHML
 #define COPASI_MATHML

#define SPC(level) std::string(level, ' ')

class CMathMl
  {
  public:

    static std::string fixName(const std::string & name)
    {
      if (name.find_first_of(" ()") == std::string::npos)
        return name;
      else
        return "\"" + name + "\"";
    }
  };

#endif
