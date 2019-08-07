// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CKinFunction
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CKinFunction
#define COPASI_CKinFunction

#include <vector>

#include "copasi/function/CFunction.h"

#include "copasi/function/CNodeK.h"
#include "copasi/utilities/CReadConfig.h"

class CDataObject;

/** @dia:pos 61.7476,54.3157 */
/** @dia:route CFunction; v,58.2,35.55,51.6337,82.8684,54.3157 */
class CKinFunction : public CFunction
{
  // Attributes
private:
  /**
   *  The vector of nodes of the binary tree of the function
   *  @supplierCardinality 0..*
   *  @associates <{CNodeK}>
   */
  /** @dia:route 0,2; h,61.7476,54.3157,55.1707,42.4925,46.911 */
  std::vector< CNodeK * > mNodes;

  std::vector<CDataObject*> ObjList;
  /**
   *  Internal variable
   */
  unsigned C_INT32 mNidx;

protected:
  CKinFunction(const CFunction & src);

  // Operations
public:
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CKinFunction(const std::string & name = "NoName",
               const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param "const CFunction &" src
   * @param const CDataContainer * pParent
   * @param "CReadConfig *" configBuffer (Default = NULL)
   */
  CKinFunction(const CFunction & src,
               const CDataContainer * pParent,
               CReadConfig * configBuffer = NULL);

  /**
   * Copy constructor
   * @param "const CKinFunction &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CKinFunction(const CKinFunction & src,
               const CDataContainer * pParent);

  /**
   *  Destructor
   */
  ~CKinFunction();

  /**
   *  Cleanup
   */
  void cleanup();

  /**
   *  Retrieves the nodes of the function
   */
  std::vector< CNodeK * > & getNodes();

private:

  /**
   *  This function creates the parameter description for older file versions
   */
  void createParameters();

  /**
   * Cleanup nodes
   */
  void cleanupNodes();
};

#endif // COPASI_CKinFunction
