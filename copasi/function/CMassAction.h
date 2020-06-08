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
 * CMassAction
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CMassAction
#define COPASI_CMassAction

#include "copasi/function/CFunction.h"

/** @dia:pos 62.0314,41.4407 */
/** @dia:route CFunction; v,58.2,35.55,39.4413,82.281,41.4407 */
class CMassAction : public CFunction
{
  // Static Attributes
public:
  static const char * Infix[];

protected:
  CMassAction(const CMassAction & src);

  // Operations
public:
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMassAction(const std::string & name = "NoName",
              const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param "const CFunction &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMassAction(const CFunction & src,
              const CDataContainer * pParent);

  /**
   * Specified constructor
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMassAction(const TriLogic & reversible,
              const CDataContainer * pParent = NO_PARENT);

  /**
   *  Destructor
   */
  ~CMassAction();

  /**
   *  Calculates the value of the function
   *  @param const CCallParameters<C_FLOAT64> & callParameters
   *  @return const C_FLOAT64 & result
   */
  virtual const C_FLOAT64 &
  calcValue(const CCallParameters<C_FLOAT64> & callParameters);

  /**
   * Set the infix description of the tree and compile it.
   * @param const std::string & infix
   * @return CIssue issue
   */
  virtual CIssue setInfix(const std::string & infix);

  /**
   * Compile the evaluation tree.
   */
  virtual CIssue compile();

  virtual std::string writeMathML(const std::vector< std::vector< std::string > > & variables,
                                  bool expand = true, bool fullExpand = true) const;
};

#endif // COPASI_CMassAction
