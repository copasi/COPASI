// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CRegisteredCommonName
#define COPASI_CRegisteredCommonName

#include "copasi/core/CCommonName.h"

class CRegisteredCommonName: public CCommonName
{
public:
  /**
   * Default Constructor
   */
  CRegisteredCommonName();

  /**
   * Copy Constructor
   * @param const CRegisteredCommonName & src
   */
  CRegisteredCommonName(const CRegisteredCommonName & src);

  /**
   * Destructor
   */
  ~CRegisteredCommonName();

  /**
   * Constructor from base class
   * @param const std::string & name
   */
  CRegisteredCommonName(const std::string & name);

  /**
   * Enable and disable the rename handler
   * @param const bool & enabled
   */
  static void setEnabled(const bool & enabled);

  /**
   * Check whether the rename handler is enabled
   * @return const bool & enabled
   */
  static const bool & isEnabled();

  /**
   * Update all registered common names which contain
   * the oldCN
   * @param const std::string & oldCN
   * @param const std::string & newCN
   */
  static void handle(const std::string & oldCN,
                     const std::string & newCN);

private:
  /**
   * A set which contains all registered comon names
   */
  static std::set<CRegisteredCommonName*> mSet;

  /**
   * A flag indicating whether renaming is enabled.
   */
  static bool mEnabled;
};

#endif // COPASI_CRegisteredCommonName
