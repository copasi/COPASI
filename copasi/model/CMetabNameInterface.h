//
//
// C++ Interface: $MODULE$
//
// Description:
//
//
// Author: sven <sven@ares>, (C) 2003
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef COPASI_CMetabNameInterface
#define COPASI_CMetabNameInterface

#include <string>

class CModel;
class CMetab;

/**
 *
 */
class CMetabNameInterface
  {
  public:
    CMetabNameInterface();

    ~CMetabNameInterface();

    static const std::string & getDisplayName(const std::string & key);
    static const std::string & getDisplayName(const CMetab & metab);

    static std::string getMetaboliteKey(const CModel* model, const std::string & name);
    static CMetab * getMetabolite(const CModel* model, const std::string & name);

  private:
    static std::string empty_string;
  };

#endif
