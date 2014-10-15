// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CRandomSearchMaster class
 */

#ifndef COPASI_CRandomSearchMaster
#define COPASI_CRandomSearchMaster

/** @dia:pos 18.05,34.05 */
/** @dia:route COptMethod; v,46.9608,16.35,33,32.3332,34.05 */
class CRandomSearchMaster : public COptMethod
{
  friend COptMethod * COptMethod::createMethod(CTaskEnum::Method subType);

  // Operations
private:
  /**
   * Default Constructor
   */
  CRandomSearchMaster();

public:
  /**
   * Copy Constructor
   * @param const CRandomSearchMaster & src
   */
  CRandomSearchMaster(const CRandomSearchMaster & src);

  /**
   * Destructor
   */
  virtual ~CRandomSearchMaster();

  /**
   * Execute the optimization algorithm calling simulation routine
   * when needed. It is noted that this procedure can give feedback
   * of its progress by the callback function set with SetCallback.
   */
  virtual bool optimise();
};

#endif  // COPASI_CRandomSearchMaster
