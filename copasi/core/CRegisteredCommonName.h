// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CRegisteredCommonName
#define COPASI_CRegisteredCommonName

#include "copasi/core/CCommonName.h"

// Uncomment to disable the deprecated construct from std::string
// #define DEPRECATE_CONSTRUCTOR 1

class CDataModel;
class CObjectInterface;

class CRegisteredCommonName: public CCommonName
{
public:
static void ResolveAll(const CDataContainer * pContainer);

  /**
   * Default Constructor
   */
  CRegisteredCommonName();

  /**
   * Constructor from base class
   * @param const CCommonName & name
   */
  CRegisteredCommonName(const CCommonName & name);

  /**
   * Copy Constructor
   * @param const CRegisteredCommonName & src
   */
  CRegisteredCommonName(const CRegisteredCommonName & src);

  /**
   * Destructor
   */
  virtual ~CRegisteredCommonName();

  CRegisteredCommonName & operator=(const CCommonName & rhs);
  CRegisteredCommonName & operator=(const CRegisteredCommonName & rhs);

  const CObjectInterface * resolve(const CDataContainer * pContainer) const override;

private:
  static std::set< const CRegisteredCommonName * > UnresolvedCNs;
};

#endif // COPASI_CRegisteredCommonName
